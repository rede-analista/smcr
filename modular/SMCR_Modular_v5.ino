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
             O ESP  receptor funcionara como uma extensao do ESP  transmissor e/ou
             como se fosse um modulo central.
*/
/*---- Variaveis Globais ----*/
String vS_nomeDispositivo, vS_nomeWifi, vS_senhaWifi, vS_nomeAP_Wifi, vS_senhaAP_Wifi, vS_api_Telegram, vS_chat_Telegram,
vS_user_Telegram, vS_mqttTopico, vS_mqttDiscovery, vS_mqttServer, vS_mqttUser, vS_mqttSenha, vS_mqttIdUnico, vS_assNomeGoogle, vS_assNomeAlexa,
vS_assLinguagem, vS_ass_Alerta, vS_ass_Normal;
uint8_t vU8_tentativaConexoes, vI_cicloHandshake;
uint16_t vU16_portaWeb, vU16_portaWebModulos, vU16_bot_MTBS, vU16_mqttPorta, vU16_mqtt_MTBS, vU16_ass_MTBS, vU16_modulos_MTBS;
uint32_t vU32_mqtt_disc_MTBS, RESPONSE_TIMEOUT;
bool vB_emAlerta, vB_exec_Telegram, vB_modoAP, vB_exec_MqTT, vB_exec_Assistente, vB_exec_Modulos;

/*---- Controles Internos ----*/
bool vB_finalizaModoAP = false;
bool vB_AlertaHandshake = false;
uint8_t vU8_ultimoModEnviado = 0;
String vS_uri, ULTIMOS_GET_SERVIDOR, GET_SERVIDOR, vS_payload, ULTIMOS_GET_RECEBIDOS;
int vI_httpResponseCode, vI_controleCicloHandshake;
//--------------------------------------------------------------------
const uint8_t vI8_aU8_Pinos = 7; // Total de linhas do array cadastro de pinos (uint8_t)
const uint8_t vU8_totPinos = 44; // Total de pinos(colunas), variarvel usada nos arrays de acoes, menssagens, controles e laços de repeticao
const uint8_t vI8_aS8_Pinos = 1; // Total de linhas do array cadastro de pinos (String)
String aS8_PinosMenu[1][vI8_aU8_Pinos] = {"Pino","Tipo","Modo","XoR","Status","Retenção","Tempo_Retenção"};
//--------------------------------------------------------------------
const uint8_t vI8_aU16_Acao = 6; // Total de "linhas" dos arrays de acoes (uint16_t)
const uint8_t vI8_aU16_AcaoRede = 4; // Total de "linhas" dos arrays de acoes rede (uint16_t)
const uint8_t vI8_aS8_Acao = 2; // Total de "linhas" dos arrays de acoes (String)
String aS8_AcoesMenu[1][vI8_aU16_Acao] = {"Pino_Origem","Pino_Destino","Ação","Tempo_ON","Tempo_OFF","Nível_Acion."};
String aS8_AcoesRedeMenu[1][vI8_aU16_AcaoRede] = {"Envia_Módulo","Envia_Telegram","Notif_Assist.","Envia_MqTT"};
String aS8_AcoesStringMenu[1][vI8_aS8_Acao] = {"Classe_MqTT","Ícone_MqTT"};
//--------------------------------------------------------------------
const uint8_t vI8_aU8_ControlMsg = 3; // Total de "linhas" dos arrays de controle de envio de menssagens
const uint8_t vI8_aS_InterMod = 2; // Total de "linhas" do array de inter modulos (String)
uint64_t mqtt_lasttime, telegram_lasttime, check_acoes_telegram_lasttime, check_acoes_mqtt_lasttime, discovery_mqtt_lasttime, check_acoes_ass_lasttime, check_acoes_mod_lasttime;
#define ESP32

/////////////////////////////////////////////////////////
//---- Arrays para controle de execucao de rotinas ----//
/////////////////////////////////////////////////////////
/*
aU8_ControlMsgMod[Propriedade][Pino]
aU8_ControlMsgMod[0][x] = Enviar Receptor Acao1
aU8_ControlMsgMod[1][x] = Enviar Receptor Acao2
aU8_ControlMsgMod[2][x] = Enviar Receptor Acao3
*/
uint8_t aU8_ControlMsgMod[vI8_aU8_ControlMsg][vU8_totPinos];
/*
aU8_ControlMsgAss[Propriedade][Pino]
aU8_ControlMsgAss[0][x] = Enviar Assistentes Acao1
aU8_ControlMsgAss[1][x] = Enviar Assistentes Acao2
aU8_ControlMsgAss[2][x] = Enviar Assistentes Acao3
*/
uint8_t aU8_ControlMsgAss[vI8_aU8_ControlMsg][vU8_totPinos];
/*
aU8_ControlMsgTelegram[Propriedade][Pino]
aU8_ControlMsgTelegram[0][x] = Enviar Telegram Acao1
aU8_ControlMsgTelegram[1][x] = Enviar Telegram Acao2
aU8_ControlMsgTelegram[2][x] = Enviar Telegram Acao3
*/
uint8_t aU8_ControlMsgTelegram[vI8_aU8_ControlMsg][vU8_totPinos];
/*
aU8_ControlMsgMqTT[0][x] = Enviar Telegram Acao1
aU8_ControlMsgMqTT[1][x] = Enviar Telegram Acao2
aU8_ControlMsgMqTT[2][x] = Enviar Telegram Acao3
*/
uint8_t aU8_ControlMsgMqTT[vI8_aU8_ControlMsg][vU8_totPinos];
/*---- FIM Arrays para controle de execucao de rotinas ----*/

////////////////////////////////////////
//---- Inter Modulos Configurados ----//
////////////////////////////////////////
/*
aS_ControlInterMod[Propriedade][Pino]
aS_ControlInterMod[0][x] = Nome Modulo
aS_ControlInterMod[1][x] = IP Modulo
*/
String aS_InterMod[vI8_aS_InterMod][vU8_totPinos];
/*---- FIM Inter Modulos Configurados ----*/

////////////////////////////////
///---- Pinos Utilizados ----///
////////////////////////////////
/*
aU8_Pinos[Propriedade][Pino]
aU8_Pinos[0][x] = Fisico Mapeamento dos pinos fisicos
aU8_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO / 254=REMOTO
aU8_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0
aU8_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO
aU8_Pinos[4][x] = Status 0=LOW / 1=HIGH
aU8_Pinos[5][x] = Retencao 0=NAO / 1=SIM
aU8_Pinos[6][x] = Tempo Retencao 0 a 254
--------------------------------------------------------------------
aS8_Pinos[Propriedade][Pino]
aS8_Pinos[0][x] = Nome ou descricao
*/
uint8_t aU8_Pinos[vI8_aU8_Pinos][vU8_totPinos];
String aS8_Pinos[vI8_aS8_Pinos][vU8_totPinos];
/*---- FIM Pinos Utilizados ----*/

////////////////////////////////
//---- Acoes Configuradas ----//
////////////////////////////////
/*
aU16_Acao[Propriedade][Pino]
aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Delay / 3=Pisca / 4=Pulso / 5=Pulso Delay
aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[5][x] = Acionamento Alto=1 / Baixo=0
--------------------------------------------------------------------
aU16_AcaoRede[Propriedade][Pino]
aU16_AcaoRede[0][x] = Envia ao Modulo 0=Nao / 1=Sim
aU16_AcaoRede[1][x] = Envia ao Telegram 0=Nao / 1=Sim
aU16_AcaoRede[2][x] = Envia ao MqTT 0=Nao / 1=Sim
aU16_AcaoRede[3][x] = Notifica Assitente 0=Nao / 1=Sim
--------------------------------------------------------------------
aS8_Acao[Propriedade][Pino]
aS8_Acao[0][x] = Classe da acao para o MqTT
aS8_Acao[1][x] = Icone da acao para o MqTT
*/
uint16_t aU16_Acao1[vI8_aU16_Acao][vU8_totPinos];
uint16_t aU16_AcaoRede1[vI8_aU16_AcaoRede][vU8_totPinos];
String aS8_Acao1[vI8_aS8_Acao][vU8_totPinos];

uint16_t aU16_Acao2[vI8_aU16_Acao][vU8_totPinos];
uint16_t aU16_AcaoRede2[vI8_aU16_AcaoRede][vU8_totPinos];
String aS8_Acao2[vI8_aS8_Acao][vU8_totPinos];

uint16_t aU16_Acao3[vI8_aU16_Acao][vU8_totPinos];
uint16_t aU16_AcaoRede3[vI8_aU16_AcaoRede][vU8_totPinos];
String aS8_Acao3[vI8_aS8_Acao][vU8_totPinos];
/*---- FIM Acoes Configuradas ----*/


/*---- Inicia objetos ----*/
Preferences CONFIG_FLASH;
WebServer SERVIDOR_WEB;
enum tipoMensagem { alerta, aviso, informacao, sucesso };
WiFiClientSecure CLIENT_TELEGRAM;
UniversalTelegramBot bot(vS_api_Telegram, CLIENT_TELEGRAM); 
WiFiClient W_CLIENT_MQTT;
PubSubClient CLIENT_MQTT(W_CLIENT_MQTT);
GoogleHomeNotifier CLIENT_ASS_GOOGLE;
/*---- FIM Inicia objetos ----*/

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("");
  delay(1000);
  f_idPlaca();
  Serial.println("---- Iniciando SETUP ----");

  f_iniciaPinos(false); // Le da flash os pinos cadastrados

  f_iniciaAcoes(false); // Le da flash as acoes cadastradas

  f_configuraWIFI(); //Configuracao WIFI e MODO AP

  f_configuraWEB(); //Configuracao Servidor WEB e OTA

  f_configuraTELEGRAM(false);

  f_configuraMQTT(false);

  f_configuraModulos(false);

  f_configuraAssistenteGH(false);

  Serial.print("Iniciando tarefas... ");
  xTaskCreate(TaskLeituraPinos, "t_LePinos", 2048, NULL, 2, NULL);
  delay(300);
  xTaskCreate(TaskAcoesPinos, "t_AcPinos", 2048, NULL, 2, NULL);
  delay(300);
  xTaskCreate(TaskAcoesPg2Pinos, "t_AcPg2Pinos", 2048, NULL, 2, NULL);
  delay(300);
  xTaskCreate(TaskAcoesPg3Pinos, "t_AcPg3Pinos", 2048, NULL, 2, NULL);
  delay(300);
  Serial.println("OK");

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
  if (vB_exec_Modulos) {
    f_checkAcoesModulos();
  }
  SERVIDOR_WEB.handleClient();
  delay(2);

}
