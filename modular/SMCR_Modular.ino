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
#include <time.h>
#include <esp_sntp.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoWebsockets.h>
#include "FS.h"
#include "SPIFFS.h"
#include <type_traits>
#include "uptime.h"

/*
  SKETCH: SMCR MODULAR
  DESCRICAO: Realizar leitura de pinos de entrada acionando pinos de saida e
             enviando a outro modulo ESP(RECEPTOR) as informacoes dos pinos de entrada.
             O ESP  receptor funcionara como uma extensao do ESP  transmissor e/ou
             como se fosse um modulo central.
*/

/*---- Variaveis Globais e Controles Internos ----*/
String vS_nomeDispositivo, vS_nomeWifi, vS_senhaWifi, vS_nomeAP_Wifi, vS_senhaAP_Wifi, vS_api_Telegram, vS_chat_Telegram,
  vS_user_Telegram, vS_mqttTopico, vS_mqttDiscovery, vS_mqttServer, vS_mqttUser, vS_mqttSenha, vS_mqttIdUnico, vS_assNomeGoogle, vS_assNomeAlexa,
  vS_assLinguagem, vS_ass_Alerta, vS_ass_Normal, vS_corStatus1, vS_corStatus0, vS_ntpServer1, vS_ntpServer2, vS_timeZone;
uint8_t vU8_tentativaConexoes, vI_cicloHandshake, vU8_crtl_ModHist;
uint16_t vU16_portaWeb, vU16_bot_MTBS, vU16_mqttPorta, vU16_mqtt_MTBS, vU16_ass_MTBS, vU16_modulos_HandShake, vU16_modulos_MTBS_Acoes;  //vU16_portaWebModulos
uint32_t vU32_mqtt_disc_MTBS;
bool vB_exec_Telegram, vB_modoAP, vB_exec_MqTT, vB_exec_Assistente, vB_exec_Modulos;
/*---- Declaracao Funcoes ----*/
uint16_t f_carregaConfi(String ref, bool force);
/*---- FIM Declaracao Funcoes ----*/
/*---- Inicia objetos ----*/
Preferences CONFIG_FLASH;
WebServer SERVIDOR_WEB;
HTTPClient CLIENTE_WEB;
enum tipoMensagem { alerta,
                    aviso,
                    informacao,
                    sucesso };
WiFiClientSecure CLIENT_TELEGRAM;
UniversalTelegramBot bot(vS_api_Telegram, CLIENT_TELEGRAM);
WiFiClient W_CLIENT_MQTT;
PubSubClient CLIENT_MQTT(W_CLIENT_MQTT);
GoogleHomeNotifier CLIENT_ASS_GOOGLE;
Espalexa CLIENT_ASS_ALEXA;
const uint16_t vI_U16_portaWebAsync = f_carregaConfi("ASYNC", false);
AsyncWebServer SERVIDOR_WEB_ASYNC(vI_U16_portaWebAsync);
/*---- FIM Inicia objetos ----*/
//--------------------------------------------------------------------
const uint8_t vU8_totPinos = 52;
const uint8_t vI8_aU16_Pinos = 6;  // Total de linhas do array cadastro de pinos (uint8_t)
const uint8_t vI8_aS8_Pinos = 1;   // Total de linhas do array cadastro de pinos (String)
String aS16_PinosMenu[1][vI8_aU16_Pinos] = { "Pino", "Tipo", "pinMode()", "XoR", "Nível_Acionamento", "Tempo_Retenção" };
//--------------------------------------------------------------------
const uint8_t vI8_aU16_Acao = 6;     // Total de "linhas" dos arrays de acoes (uint16_t)
const uint8_t vI8_aU8_AcaoRede = 4;  // Total de "linhas" dos arrays de acoes rede (uint16_t)
//const uint8_t vI8_aS8_Acao = 1;      // Total de "linhas" dos arrays de acoes (String)
String aS8_AcoesMenu[1][vI8_aU16_Acao] = { "Pino_Origem", "Pino_Destino", "Ação", "Tempo_ON", "Tempo_OFF", "Pino_Dest_Rem_(Mask)" };
String aS8_AcoesRedeMenu[1][vI8_aU8_AcaoRede] = { "Envia_Para_Módulo", "Envia_Telegram", "Notif_Assist.", "Envia_MqTT" };
//String aS8_AcoesStringMenu[1][vI8_aS8_Acao] = { "Classe_MqTT" };  // ,"Ícone_MqTT"
//--------------------------------------------------------------------
const uint8_t vI8_aS_InterMod = 2;  // Total de "linhas" do array de inter modulos (String)
String aS_InterModMenu[1][vI8_aS_InterMod] = { "Nome", "IP" };
const uint8_t vI8_aU16_InterMod = 2;  // Total de "linhas" do array de inter modulos (uint8_t)
String aU16_InterModMenu[1][vI8_aU16_InterMod] = { "ID-Pino_HandShake", "Porta_Receptor" };
const uint8_t vI8_aB_InterMod = 1;  // Total de "linhas" do array 
String aSB_InterModMenu[1][vI8_aB_InterMod] = { "Enviar_Handshake" };
const uint8_t vI8_aU16_InterModHA = 4;  // Total de "linhas" do array de inter modulos controle handshake e status handshake
String aS16_InterModHA[1][vI8_aU16_InterModHA] = { "Ciclo", "Status", "CTRL_Resposta", "Envio_Pausado" };
//--------------------------------------------------------------------
const uint8_t vI8_aU8_ControlMsg = 3;      // Total de "linhas" dos arrays de controle de envio de menssagens
const uint8_t vI8_aU8_ControlMsgHist = 4;  // Total de "linhas" dos arrays de historico de envio de menssagens
String aS8_ControlMsgModHist[1][vI8_aU8_ControlMsgHist] = { "Módulo", "Ação", "Pino", "Valor" };
const uint8_t vI8_ControlAcoesGroups = (vU8_totPinos * 3) + 1;  // Total de "linhas" do array de grupos de acos mesmo destino
//--------------------------------------------------------------------
/*---- Variaveis Controles de Execucao ----*/
uint64_t envia_acoes_mod_lasttime, check_mod_lasttime, hora_lasttime, mqtt_lasttime, telegram_lasttime, check_acoes_telegram_lasttime, check_acoes_mqtt_lasttime, discovery_mqtt_lasttime, check_acoes_ass_lasttime, check_acoes_mod_lasttime;
#define ESP32
#define MAX_JSON_SIZE 6000
#define FORMAT_SPIFFS_IF_FAILED true
File jsonFile;
char jsonData[MAX_JSON_SIZE];
size_t jsonDataSize = 0;
struct tm timeinfo;
bool vB_finalizaModoAP = false;
bool vB_emExecucaoWifi = false;
bool vB_envia_Historico = false;
bool VB_mostra_Status = false;
uint8_t vU8_PinosCadastrados = 0;
uint16_t vU8_ultimoModEnviado = 0;
uint8_t vU8_bitsProc = 12;
uint8_t vU8_ciclosAmostra = 8;
const uint8_t vU8_colunasTabelas = 7;
String vS_uri, ULTIMOS_GET_SERVIDOR, GET_SERVIDOR, vS_payload, ULTIMOS_GET_RECEBIDOS;
String aS_traduzDiaSemana[1][7] = { "Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado" };
String aS_traduzMes[1][12] = { "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" };
int vI_httpResponseCode, vI_controleCicloHandshake;
/*---- FIM Variaveis Globais e Controles Internos ----*/

/////////////////////////////////////////////////////////
//---- Arrays para controle de execucao de rotinas ----//
/////////////////////////////////////////////////////////
/* -----------------------------------------------------------
Controle o envio de menssagens entre os modulos ESP
aU16_ControlMsgMod[Propriedade][Pino]
aU16_ControlMsgMod[0][x] = Confirmado enviao Receptor Acao1
aU16_ControlMsgMod[1][x] = Confirmado enviao Receptor Acao2
aU16_ControlMsgMod[2][x] = Confirmado enviao Receptor Acao3
--------------------------------------------------------------------
aU16_ControlMsgModHist[0][x] = Modulo
aU16_ControlMsgModHist[1][x] = Acao
aU16_ControlMsgModHist[2][x] = Pino
aU16_ControlMsgModHist[3][x] = Valor
*/
uint16_t aU16_ControlMsgMod[vI8_aU8_ControlMsg][vU8_totPinos] = {};
uint16_t aU16_ControlMsgModHist[vI8_aU8_ControlMsgHist][vU8_totPinos] = {};
/* -----------------------------------------------------------
Controle o envio de menssagens para assistentes
aU8_ControlMsgAss[Propriedade][Pino]
aU8_ControlMsgAss[0][x] = Enviar Assistentes Acao1
aU8_ControlMsgAss[1][x] = Enviar Assistentes Acao2
aU8_ControlMsgAss[2][x] = Enviar Assistentes Acao3
*/
uint8_t aU8_ControlMsgAss[vI8_aU8_ControlMsg][vU8_totPinos] = {};
/* -----------------------------------------------------------
Controle o envio de menssagens para telegram
aU8_ControlMsgTelegram[Propriedade][Pino]
aU8_ControlMsgTelegram[0][x] = Enviar Telegram Acao1
aU8_ControlMsgTelegram[1][x] = Enviar Telegram Acao2
aU8_ControlMsgTelegram[2][x] = Enviar Telegram Acao3
*/
uint8_t aU8_ControlMsgTelegram[vI8_aU8_ControlMsg][vU8_totPinos] = {};
/* -----------------------------------------------------------
Controle o envio de menssagens para broker mqtt
aU8_ControlMsgMqTT[0][x] = Enviar Telegram Acao1
aU8_ControlMsgMqTT[1][x] = Enviar Telegram Acao2
aU8_ControlMsgMqTT[2][x] = Enviar Telegram Acao3
/* -----------------------------------------------------------
*/
uint8_t aU8_ControlMsgMqTT[vI8_aU8_ControlMsg][vU8_totPinos] = {};
/* -----------------------------------------------------------
Controle de acoes para mesmo pino destino (Grupo)
aU16_ControlAcoesGroups[0][vU8_totPinos] = Pino (que vai sofre acao)
aU16_ControlAcoesGroups[1][vU8_totPinos] = Referencia pinos de origem (quem vai disparar a acao)
/* -----------------------------------------------------------
*/
uint16_t aU16_ControlAcoesGroups[vI8_ControlAcoesGroups][vU8_totPinos] = {};
/* -----------------------------------------------------------
Controle de alerta de handshake para inter modulos
aI16_ControlHS[0][vU8_totPinos] = Controle tempo Ciclo
aI16_ControlHS[1][vU8_totPinos] = Status handshake
aI16_ControlHS[2][vU8_totPinos] = Controle de Resposta HS
aI16_ControlHS[3][vU8_totPinos] = Envio pausado
/* -----------------------------------------------------------
*/
int16_t aI16_ControlHS[vI8_aU16_InterModHA][vU8_totPinos];
/*---- FIM Arrays para controle de execucao de rotinas ----*/


////////////////////////////////////////
//---- Inter Modulos Configurados ----//
////////////////////////////////////////
/*
Usado para cadastro dos modulos (Inter Modulos)
aS_InterMod[Propriedade][Modulo]
aS_InterMod[0][x] = Nome Modulo
aS_InterMod[1][x] = IP Modulo
--------------------------------------------------------------------
aU16_InterMod[0][x] = Pino HandShake
aU16_InterMod[1][x] = Porta ESP Remoto
--------------------------------------------------------------------
aB_InterMod[0][x] = Envia HandShake
*/
String aS_InterMod[vI8_aS_InterMod][vU8_totPinos];
uint16_t aU16_InterMod[vI8_aU16_InterMod][vU8_totPinos];
bool aB_InterMod[vI8_aB_InterMod][vU8_totPinos];
/*---- FIM Inter Modulos Configurados ----*/

////////////////////////////////
///---- Pinos Utilizados ----///
////////////////////////////////
/*
Usado para cadastro de porta (pinos fisicos)
aU16_Pinos[Propriedade][Pino]
aU16_Pinos[0][x] = Fisico - Mapeamento dos pinos fisicos
aU16_Pinos[1][x] = Tipo 0=SEM USO / 1=DIGITAL / 192=ANALOGICO / 65534=REMOTO
aU16_Pinos[2][x] = Modo NONE ou VIRTUAL=0 / INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=192
aU16_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO
aU16_Pinos[4][x] = Nivel de Acionamento
aU16_Pinos[5][x] = Tempo Retencao 0 a 65535
--------------------------------------------------------------------
Usado para cadastro do nome(descricao) dos pinos
aS8_Pinos[Propriedade][Pino]
aS8_Pinos[0][x] = Nome/descricao
--------------------------------------------------------------------
Usado para registrar o status dos pinos
aU16_Pinos_StatusPropriedade][Pino]
aU16_Pinos_Status[0][x] = Status/Valor
*/
uint16_t aU16_Pinos[vI8_aU16_Pinos][vU8_totPinos];
String aS8_Pinos[vI8_aS8_Pinos][vU8_totPinos];
uint16_t aU16_Pinos_Status[1][vU8_totPinos] = {};
/*---- FIM Pinos Utilizados ----*/

////////////////////////////////
//---- Acoes Configuradas ----//
////////////////////////////////
/*
Usado para cadastro de acoes, eventos quando uma porta(pino) e acionada
aU16_Acao[Propriedade][Pino]
aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Delay / 3=Pisca / 4=Pulso / 5=Pulso Delay
aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[5][x] = Mask Pino Destino
--------------------------------------------------------------------
Usado para cadastro de acoes, eventos quando uma porta(pino) e acionada
aU16_AcaoRede[Propriedade][Pino]
aU16_AcaoRede[0][x] = Envia ao Modulo 0=Nao / 1=Sim
aU16_AcaoRede[1][x] = Envia ao Telegram 0=Nao / 1=Sim
aU16_AcaoRede[2][x] = Envia ao MqTT 0=Nao / 1=Sim
aU16_AcaoRede[3][x] = Notifica Assitente 0=Nao / 1=Sim
--------------------------------------------------------------------
Usado para cadastro de acoes, eventos quando uma porta(pino) e acionada
aS8_Acao[Propriedade][Pino]
aS8_Acao[0][x] = Classe da acao para o MqTT
*/
uint16_t aU16_Acao1[vI8_aU16_Acao][vU8_totPinos];
uint16_t aU8_AcaoRede1[vI8_aU8_AcaoRede][vU8_totPinos];
//String aS8_Acao1[vI8_aS8_Acao][vU8_totPinos];

uint16_t aU16_Acao2[vI8_aU16_Acao][vU8_totPinos];
uint16_t aU8_AcaoRede2[vI8_aU8_AcaoRede][vU8_totPinos];
//String aS8_Acao2[vI8_aS8_Acao][vU8_totPinos];

uint16_t aU16_Acao3[vI8_aU16_Acao][vU8_totPinos];
uint16_t aU8_AcaoRede3[vI8_aU8_AcaoRede][vU8_totPinos];
//String aS8_Acao3[vI8_aS8_Acao][vU8_totPinos];
/*---- FIM Acoes Configuradas ----*/

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("");
  delay(1000);
  f_idPlaca();
  Serial.println("---- Iniciando SETUP ----");

  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar o sistema de arquivos SPIFFS");
  } else {
    Serial.println("Sistema de arquivos SPIFFS montado com sucesso.");
    listDir(SPIFFS, "/", 0);
  }

  f_iniciaPinos(false);  // Le da flash os pinos cadastrados e configura pinmode()

  f_iniciaAcoes(false);  // Le da flash as acoes cadastradas e configura

  f_configuraWIFI();  //Le da flash Configuracao WIFI e MODO AP

  f_configuraWEB();  //Le da flash e configura Servidor WEB e OTA

  f_configuraTELEGRAM(false);  //Le da flash e configura conexao com telegram

  f_configuraMQTT(false);  //Le da flash e configura conexao com mqtt

  f_configuraModulos(false);  //Le da flash e configura comunicacao entre modulos

  f_configuraAssistenteGH(false);  //Le da flash e configura comunicacao com assistentes

  f_configuraAssistenteALX(false);  //Le da flash e configura comunicacao com assistentes

  Serial.print("Iniciando tarefas... ");  //Inicia tarefas(tasks) para execução continua de leitura de portas(pinos) e acoes
  xTaskCreate(TaskLeituraPinos, "t_LePinos", 2560, NULL, 2, NULL);
  delay(300);
  xTaskCreate(TaskAcoes1Pinos, "t_Ac1Pinos", 2560, NULL, 2, NULL);
  delay(300);
  xTaskCreate(TaskAcoes2Pinos, "t_Ac2Pinos", 2560, NULL, 2, NULL);
  delay(300);
  xTaskCreate(TaskAcoes3Pinos, "t_Ac3Pinos", 2560, NULL, 2, NULL);
  delay(300);
  Serial.println("OK");
  vB_emExecucaoWifi = true;
  vB_envia_Historico = true;
  Serial.println("!!!! SETUP FINALIZADO !!!!");
}

void loop() {

  if (vB_exec_Telegram) {
    f_checkAcoesTelegram();  //Verificar se tem informacoes para enviar ao telegram
    f_recebeTelegram();      //Verificar se tem informacoes para receber do telegram
  }
  if (vB_exec_MqTT) {
    f_checkAcoesMqTT();      //Verificar se tem informacoes para enviar ao mqtt
    f_enviaMqTTDiscovery();  //Verificar se tem informacoes de discovery para enviar ao mqtt
  }
  if (vB_exec_Assistente) {
    CLIENT_ASS_ALEXA.loop();
    f_checkAcoesAssistentes();  //Verificar se tem informacoes para enviar aos assistentes
  }
  if (vB_exec_Modulos) {
    f_checkAcoesModulos();  //Verificar se tem informacoes para enviar a outro modulo
    f_enviaAcoesModulos();
    f_checkHandShake();  //Verificar se tem comunicacao com outro modulo
  }
  f_atualizaHora();
  SERVIDOR_WEB.handleClient();  //Servidor WEB trata acesso ao modulo pelo navegador(browse)
  delay(2);
}
