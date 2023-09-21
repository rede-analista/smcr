#include <Preferences.h>
#include <nvs_flash.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <PubSubClient.h>
#include <esp8266-google-home-notifier.h>
#include <Espalexa.h>
#include <ArduinoJson.h>

/*
  SKETCH: SMCR MODULAR
  DESCRICAO: Realizar leitura de pinos de entrada acionando pinos de saida e
             enviando a outro ESP(RECEPTOR) as informacoes dos pinos de entrada.
             O ESP  receptor funcionara como uma extensao do ESP  transmissor.

  Possiveis codigos da conexao wifi
            0	WL_IDLE_STATUS	temporary status assigned when WiFi.begin() is called
            1	WL_NO_SSID_AVAIL	 when no SSID are available
            2	WL_SCAN_COMPLETED	scan networks is completed
            3	WL_CONNECTED	when connected to a WiFi network
            4	WL_CONNECT_FAILED	when the connection fails for all the attempts
            5	WL_CONNECTION_LOST	when the connection is lost
            6	WL_DISCONNECTED	when disconnected from a network
*/

/*---- Variaveis Globais ----*/

String vS_nomeDispositivo, vS_nomeWifi, vS_senhaWifi, vS_nomeAP_Wifi, vS_senhaAP_Wifi, vS_ipReceptor, vS_api_Telegram, vS_chat_Telegram,
vS_user_Telegram, vS_mqttTopico, vS_mqttDiscovery, vS_mqttServer, vS_mqttUser, vS_mqttSenha, vS_mqttIdUnico, vS_assNomeGoogle, vS_assNomeAlexa,
vS_assLinguagem, vS_ass_Alerta, vS_ass_Normal, ULTIMOS_GET_SERVIDOR, GET_SERVIDOR, vS_payload, vS_nomeReceptor;
uint8_t vU8_tentativaConexoes;
uint16_t vU16_portaWeb, vU16_portaWebReceptor, vU16_bot_MTBS, vU16_mqttPorta, vU16_mqtt_MTBS, vU16_ass_MTBS, vU16_rec_MTBS;
uint32_t vU32_mqtt_disc_MTBS, RESPONSE_TIMEOUT;
bool vB_emAlerta, vB_exec_Telegram, vB_modoAP, vB_exec_MqTT, vB_exec_Assistente, vB_exec_Receptor;

/*---- Controles Internos ----*/
/* NÃO ALTERAR ESSES VALORES */
bool vB_finalizaModoAP = false;
const uint8_t vU8_totPinos = 23;
uint64_t alertas_lasttime, mqtt_lasttime, telegram_lasttime, check_acoes_telegram_lasttime, check_acoes_mqtt_lasttime, discovery_mqtt_lasttime, check_acoes_ass_lasttime, check_acoes_rec_lasttime;
#define ESP32
/*
vI8_aU8_ControlMsgRec = 3;
aU8_ControlMsgRec[3][23]
aU8_ControlMsgRec[Propriedade][Pino]
aU8_ControlMsgRec[0][x] = Enviar Receptor Acao1
aU8_ControlMsgRec[1][x] = Enviar Receptor Acao2
aU8_ControlMsgRec[2][x] = Enviar Receptor Acao3
*/
uint8_t vI8_aU8_ControlMsgRec = 3;
uint8_t aU8_ControlMsgRec[3][23]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
/*
vI8_aU8_ControlMsgAss = 3;
aU8_ControlMsgAss[3][23]
aU8_ControlMsgAss[Propriedade][Pino]
aU8_ControlMsgAss[0][x] = Enviar Assistentes Acao1
aU8_ControlMsgAss[1][x] = Enviar Assistentes Acao2
aU8_ControlMsgAss[2][x] = Enviar Assistentes Acao3
*/
uint8_t vI8_aU8_ControlMsgAss = 3;
uint8_t aU8_ControlMsgAss[3][23]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
/*
vI8_aU8_ControlMsgTelegram = 3;
aU8_ControlMsgTelegram[3][23]
aU8_ControlMsgTelegram[Propriedade][Pino]
aU8_ControlMsgTelegram[0][x] = Enviar Telegram Acao1
aU8_ControlMsgTelegram[1][x] = Enviar Telegram Acao2
aU8_ControlMsgTelegram[2][x] = Enviar Telegram Acao3
*/
uint8_t vI8_aU8_ControlMsgTelegram = 3;
uint8_t aU8_ControlMsgTelegram[3][23]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
/*
vI8_aU8_ControlMsgMqTT = 3;
aU8_ControlMsgMqTT[3][23]
aU8_ControlMsgMqTT[Propriedade][Pino]
aU8_ControlMsgMqTT[0][x] = Enviar Telegram Acao1
aU8_ControlMsgMqTT[1][x] = Enviar Telegram Acao2
aU8_ControlMsgMqTT[2][x] = Enviar Telegram Acao3
*/
uint8_t vI8_aU8_ControlMsgMqTT = 3;
uint8_t aU8_ControlMsgMqTT[3][23]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

/*---- Pinos Utilizados ----*/
/*
vI8_aU8_Pinos = 7;
aU8_Pinos[7][23]
aU8_Pinos[Propriedade][Pino]
aU8_Pinos[0][x] = Fisico Mapeamento dos pinos fisicos
aU8_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO
aU8_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0
aU8_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO
aU8_Pinos[4][x] = Status 0=LOW / 1=HIGH
aU8_Pinos[5][x] = Retencao 0=NAO / 1=SIM
aU8_Pinos[6][x] = Tempo Retencao 0 a 254
*/
uint8_t vI8_aU8_Pinos = 7;
uint8_t aU8_Pinos[7][23]= {{2,4,5,12,13,14,15,16,17,18,19,21,22,23,25,26,27,32,33,34,35,36,39},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}};
/*
vI8_aS8_Pinos = 1;
aS8_Pinos[1][23]
aS8_Pinos[Propriedade][Pino]
aS8_Pinos[0][x] = Nome ou descricao
*/
uint8_t vI8_aS8_Pinos = 1;
String aS8_Pinos[1][vU8_totPinos]= {{"D02","D04","D05","D12","D13","D14","D15","D16","D17","D18","D19",
"D21","D22","D23","D25","D26","D27","D32","D33","D34","D35","D36","D39"}};
/*---- FINAL Pinos Utilizados ----*/


/*---- Acoes Configuradas ----*/
/*
vI16_aU16_Acao = 10;
aU16_Acao[10][23]
aU16_Acao[Propriedade][Pino]
aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Delay / 3=Pisca / 4=Pulso / 5=Pulso Delay
aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[5][x] = Envia ao Receptor 0=Nao / 1=Sim
aU16_Acao[6][x] = Envia ao Telegram 0=Nao / 1=Sim
aU16_Acao[7][x] = Envia ao MqTT 0=Nao / 1=Sim
aU16_Acao[8][x] = Notifica Assitente 0=Nao / 1=Sim
aU16_Acao[9][x] = Acionamento Alto=1 / Baixo=0

vI8_aS8_Acao = 0;
aS8_Acao1[2][23]
aS8_Acao1[Propriedade][Pino]
aS8_Acao1[0][x] = Classe da acao para o MqTT
aS8_Acao1[1][x] = Icone da acao para o MqTT
*/
uint8_t vI8_aU16_Acao = 10;
uint8_t vI8_aS8_Acao = 2;
uint16_t aU16_Acao1[10][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
String aS8_Acao1[2][vU8_totPinos]= {{"A02","A04","A05","A12","A13","A14","A15","A16","A17","A18","A19","A21","A22","A23","A25","A26","A27","A32","A33","A34","A35","A36","A39"},
{"I02","I04","I05","I12","I13","I14","I15","I16","I17","I18","I19","I21","I22","I23","I25","I26","I27","I32","I33","I34","I35","I36","I39"}};


uint16_t aU16_Acao2[10][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
String aS8_Acao2[2][vU8_totPinos]= {{"A02","A04","A05","A12","A13","A14","A15","A16","A17","A18","A19","A21","A22","A23","A25","A26","A27","A32","A33","A34","A35","A36","A39"},
{"I02","I04","I05","I12","I13","I14","I15","I16","I17","I18","I19","I21","I22","I23","I25","I26","I27","I32","I33","I34","I35","I36","I39"}};

uint16_t aU16_Acao3[10][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
String aS8_Acao3[2][vU8_totPinos]= {{"A02","A04","A05","A12","A13","A14","A15","A16","A17","A18","A19","A21","A22","A23","A25","A26","A27","A32","A33","A34","A35","A36","A39"},
{"I02","I04","I05","I12","I13","I14","I15","I16","I17","I18","I19","I21","I22","I23","I25","I26","I27","I32","I33","I34","I35","I36","I39"}};
/*---- FINAL Acoes Configuradas ----*/


/*---- Inicia objetos ----*/
Preferences CONFIG_FLASH;
WebServer SERVIDOR_WEB;
enum tipoMensagem { alerta, aviso, informacao, sucesso };
WiFiClientSecure CLIENT_TELEGRAM;
UniversalTelegramBot bot(vS_api_Telegram, CLIENT_TELEGRAM); 
WiFiClient W_CLIENT_MQTT;
PubSubClient CLIENT_MQTT(W_CLIENT_MQTT);
GoogleHomeNotifier CLIENT_ASS_GOOGLE;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  f_idPlaca();
  Serial.println("---- Iniciando SETUP ----");

  f_iniciaPinos(false);

  //Configuracao WIFI e MODO AP
  f_configuraWIFI();

  //Configuracao Servidor WEB e OTA
  f_configuraWEB();

  f_configuraTELEGRAM(false);

  f_iniciaAcoes(false);

  Serial.print("Iniciando tarefas... ");
  xTaskCreate(TaskLeituraPinos, "t_LePinos", 2048, NULL, 2, NULL);
  delay(100);
  xTaskCreate(TaskAcoesPinos, "t_AcPinos", 2048, NULL, 2, NULL);
  delay(100);
  xTaskCreate(TaskAcoesPg2Pinos, "t_AcPg2Pinos", 2048, NULL, 2, NULL);
  delay(100);
  xTaskCreate(TaskAcoesPg3Pinos, "t_AcPg3Pinos", 2048, NULL, 2, NULL);
  delay(100);
  Serial.println("OK");

  f_configuraMQTT(false);

  f_configuraReceptor(false);

  f_configuraAssistente(false);

  Serial.println("!!!! SETUP FINALIZADO !!!!");
}

void loop() {

  if (vB_exec_Telegram) {
    f_checkAcoesTelegram();
    f_recebeTelegram();
  }
  if (vB_exec_MqTT) {
    f_checkAcoesMqTT();
    f_enviaMqTTDiscovery();
  }
  if (vB_exec_Assistente) {
    f_checkAcoesAssistentes();
  }
  if (vB_exec_Receptor) {
    f_checkAcoesReceptor();
  }
  SERVIDOR_WEB.handleClient();
  delay(2);

}
