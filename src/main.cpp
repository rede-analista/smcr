#include "include.h"
#include "globals.h"

/*
  SKETCH: SMCR MODULAR
  DESCRICAO: Realizar leitura de pinos de entrada acionando pinos de saida e
             enviando a outro modulo ESP(RECEPTOR) as informacoes dos pinos de entrada.
             O ESP  receptor funcionara como uma extensao do ESP  transmissor e/ou
             como se fosse um modulo central.
*/

/*---- Variaveis Globais e Controles Internos ----*/
String vS_nomeDispositivo, vS_nomeWifi, vS_senhaWifi, vS_nomeAP_Wifi, vS_senhaAP_Wifi, 
       vS_api_Telegram, vS_chat_Telegram, vS_user_Telegram, vS_mqttTopico, 
       vS_mqttDiscovery, vS_mqttServer, vS_mqttUser, vS_mqttSenha, 
       vS_mqttIdUnico, vS_assNomeGoogle, vS_assNomeAlexa, vS_assLinguagem, 
       vS_ass_Alerta, vS_ass_Normal, vS_corStatus1, vS_corStatus0, 
       vS_ntpServer1, vS_ntpServer2, vS_timeZone, vS_userWeb, vS_passWeb, vS_uri, GET_SERVIDOR, vS_payload,
       ULTIMOS_GET_RECEBIDOS, ULTIMOS_GET_SERVIDOR, vS_payrec = "";

uint8_t vU8_tentativaConexoes, vI_cicloHandshake, vU8_crtl_ModHist, vU8_colunasTabelas, vU8_colINICIO, vU8_colFIM,
       vU8_tempoRefresh, vU8_estado, vI8_ControlAcoesGroups = 0;

uint16_t vU16_bot_MTBS, vU16_mqttPorta, vU16_mqtt_MTBS, vI_U16_portaWebAsync,
         vU16_ass_MTBS, vU16_modulos_HandShake, vU16_modulos_MTBS_Acoes, vU16_clockESP32, vU16_ulimoModRecebido = 0;

uint32_t vU32_mqtt_disc_MTBS, vU32_tempoWatchDog = 0;

uint64_t check_acoes_mod_lasttime, envia_acoes_mod_lasttime, check_mod_lasttime, check_acoes_mqtt_lasttime = 0;

int16_t vU16_linhaPagCad, vI_httpResponseCode, vI_controleCicloHandshake, vI_respostaHTTP = 0;

bool vB_exec_Telegram, vB_modoAP, vB_exec_MqTT, vB_exec_Assistente, vB_exec_Modulos, VB_mostra_Status,
     vB_executaReboot, vB_filesysIniciado, vB_exec_WatchDog, vB_emExecucaoWDog, vB_emExecucaoWS,
     vB_rodando, vB_envia_Historico, vB_pausaEXECs, request_in_progress, VB_mostra_Interm,
     vB_pedeAutentica = false;

size_t vU8_totTask = 0; // Total de tasks em execucao
hw_timer_t *vHW_timer = NULL;  // Faz o controle do temporizador (interrupcao por tempo)
bool aB_restartRotinas[5] = {0,0,0,0,0};
String** aS_Preference = nullptr;
uint8_t vI8_aS_Preference_ROW = 1;
uint8_t vI8_aS_Preference_COL = 60;
//----------------------------------------------//

/*---- Inicia variaveis e arrays dias da semana e meses ----*/
uint8_t vU8_diasDaSemana = 7;
uint8_t vU8_meses = 12;
String* aU8_diasDaSemana = nullptr;
String* aU8_meses = nullptr;

/*---- Inicia variaveis e arrays dos pinos ----*/
size_t vU8_totPinos = 0; // Total de colunas do array cadastro de pinos (aU16_Pinos)
size_t vI8_aU16_Pinos = 6; // Total de linhas do array cadastro de pinos (aU16_Pinos)
size_t vI8_aS8_Pinos = 1; // Total de linhas do array cadastro de pinos (nome)
uint16_t** aU16_Pinos = nullptr;//Cadastro de pinos (parametros)
String** aS8_Pinos = nullptr; // Cadastro de pinos (nome)
uint16_t** aU16_Pinos_Status = nullptr; // Cadastro de pinos (status)
String** aS16_PinosMenu = nullptr; // Menu para cadastro de pinos
uint8_t** aU8_IgnoraPino = nullptr;
//----------------------------------------------//

/*---- Inicia variaveis e arrays do InterModulos ----*/
size_t vU8_totModulos = 0; // Total de colunas do array cadastro de modulos 
uint8_t vI8_aU16_InterMod = 2;
uint8_t vI8_aB_InterMod = 1;
uint8_t vI8_aS_InterMod = 2;  // Total de "linhas" do array de inter modulos (String)
uint8_t vI8_aU8_ControlMsg = 3;  // Total de "linhas" dos arrays de controle de envio de menssagens
uint8_t vI8_aU8_ControlMsgHist = 4; // Total de "linhas" dos arrays de historico de envio de menssagens
uint8_t vI8_aU16_InterModHA = 4; // Total de "linhas" do array de inter modulos controle handshake e status handshake
String** aS_InterModMenu = nullptr; // Menu do cadastro de Intermodulos
String** aU16_InterModMenu = nullptr;
String** aSB_InterModMenu = nullptr;
String** aS8_ControlMsgModHist = nullptr;
String** aS_InterMod = nullptr;  // Cadastro de Intermodulos (Nome e IP)
uint16_t** aU16_InterMod = nullptr; // Cadastro de Intermodulos (Controles)
uint8_t** aB_InterMod = nullptr;  // Cadastro de Intermodulos (Envia HandShake)
String** aS16_InterModHA = nullptr; // Menu do array de controle de comunicacao Intermodulos
uint16_t** aI16_ControlHS = nullptr; // Controle de alerta de handshake para Intermodulos
uint16_t** aU16_ControlMsgModHist = nullptr;
uint16_t** aU16_ControlMsgMod = nullptr;
//----------------------------------------------//

/*---- Inicia variaveis e arrays das acoes ----*/
uint8_t vI8_aU16_Acao = 6;
uint8_t vI8_aU8_AcaoRede = 4;
uint8_t vI8_aS8_Acao = 2; // Total de "linhas" dos arrays de acoes (String)
String** aS8_Acao1 = nullptr;  // Cadastro de acoes 1
String** aS8_Acao2 = nullptr;  // Cadastro de acoes 2
String** aS8_Acao3 = nullptr;  // Cadastro de acoes 3
String** aS8_Acao4 = nullptr;  // Cadastro de acoes 4
uint16_t** aU16_Acao1 = nullptr;
uint16_t** aU16_Acao2 = nullptr;
uint16_t** aU16_Acao3 = nullptr;
uint16_t** aU16_Acao4 = nullptr;
uint16_t** aU8_AcaoRede1 = nullptr;
uint16_t** aU8_AcaoRede2 = nullptr;
uint16_t** aU8_AcaoRede3 = nullptr;
uint16_t** aU8_AcaoRede4 = nullptr;
String** aS8_AcoesMenu = nullptr;
String** aS8_AcoesRedeMenu = nullptr;
String** aS8_AcoesStringMenu = nullptr;
uint16_t** aU16_ControlAcoesGroups = nullptr; // Grupos de acoes, identifica se o pinos tem mais de uma acao configurada
//----------------------------------------------//

/*---- Variaveis Controles de Execucao ----*/
bool vB_emExecucaoWifi = false;
bool vB_finalizaModoAP = false;
uint8_t vU8_PinosCadastrados = 0;
uint8_t vU8_bitsProc = 12; // 
uint8_t vU8_ciclosAmostra = 8;
uint16_t vU8_ultimoModEnviado = 0;  // ID do modulo que foi enviado por ultimo
File jsonFile;
uint64_t vU64_ota_progress_millis = 0;
//----------------------------------------------//


/*---- Inicia objetos, tipos e estruturas ----*/
std::map<String, Funcao> mapaFuncoesSemParam;
std::map<String, std::function<void(AsyncWebServerRequest*)>> mapaFuncoesComParam;
std::map<String, Variable> variables;
Preferences CONFIG_FLASH;
AsyncWebServer* SERVIDOR_WEB_ASYNC = nullptr;
asyncHTTPrequest* CLIENTE_WEB_ASYNC = nullptr;
ESPAsyncHTTPUpdateServer* SERVIDOR_UPDATE = nullptr;
AsyncWebSocket* ws = nullptr;
Config config;
struct tm timeinfo;
//----------------------------------------------//

String vS_logStr = "Session start:\n";
char aC_bufferTemp[256];
char aC_filesysName[] = "LittleFS";
File vF_arquivoUpload;

void setup() {
    Serial.begin(115200);
    delay(3000);
    fV_imprimeSerial("||||---- INICIANDO SETUP ----||||",true);
    vB_filesysIniciado = fB_montaLittleFS();  // Monta LittleFS (FILESYS)
    if (fB_verificaPrimeiraExec(false)) {
        fV_mapaFuncoes();  // Mapeia funcoes para uso nos GETS/POSTS
        fS_idPlaca(); // Imprime na serial informacoes da placa
        fV_Preference("L",false); // Carrega configuracoes do filesys
        fV_carregaFILESYS_AS1D("/aU8_diasDaSemana.txt",aU8_diasDaSemana,vU8_diasDaSemana);  // Carregar array com os dias da semana
        fV_carregaFILESYS_AS1D("/aU8_meses.txt",aU8_meses,vU8_meses);  // // Carregar array com os meses
        fV_imprimeSerial(fS_DataHora(),true); // Imprime na seria data e hora
        fS_listDir("/",4); // Lista arquivos em salvos em SPIFFS
        fV_iniciaPreference(false); // Inicia configurações dos pinos
        fV_iniciaPinos(false); // Inicia configurações dos pinos
        fV_iniciaAcoes(false);  // Inicia configuracoes das acoes
        fU8_configuraWifi(); // Configurar o wifi ou colocar em modo AP caso nao consiga conexao com wifi
        fB_configuraServidorWEB(false); // Configura servidor web para acesso ao esp32
        fV_configuraModulos(false);  // Configura intermodulos
        fV_imprimeSerial("Iniciando tarefas... ");
        xTaskCreate(TaskLeituraPinos, "t_LePinos", 2560, NULL, 3, NULL); //Inicia tarefa(task) para execução continua de leitura de portas(pinos)
        fV_imprimeSerial(" - ativando task leitura pinos - ");
        delay(600);
        switch (vU8_totTask) {
          case 0:
            fV_imprimeSerial(" - sem tasks ativas - ");
          case 1:
            xTaskCreate(TaskAcoes1Pinos, "t_Ac1Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 1
            fV_imprimeSerial(" - ativando task acoes 1 - ");
            break;
          case 2:
            xTaskCreate(TaskAcoes2Pinos, "t_Ac2Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 2
            fV_imprimeSerial(" - ativando task acoes 2 - ");
            break;
          case 3:
            xTaskCreate(TaskAcoes3Pinos, "t_Ac3Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 3
            fV_imprimeSerial(" - ativando task acoes 3 - ");
            break;
          case 4:
            xTaskCreate(TaskAcoes4Pinos, "t_Ac4Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 4
            fV_imprimeSerial(" - ativando task acoes 4 - ");
            break;
          case 5:
            fV_imprimeSerial(" - ativando tasks acoes 1 a 4 - ");
            xTaskCreate(TaskAcoes1Pinos, "t_Ac1Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 1
            delay(600);
            xTaskCreate(TaskAcoes2Pinos, "t_Ac2Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 2
            delay(600);
            xTaskCreate(TaskAcoes3Pinos, "t_Ac3Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 3
            delay(600);
            xTaskCreate(TaskAcoes4Pinos, "t_Ac4Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 4
            delay(600);
            break;            
        }
        fV_configuraWatchDog(false);  // Configura watchdog
        if (vB_exec_Modulos) {
            vB_envia_Historico = true;
        }
    } else {
        fV_imprimeSerial("Arquivos de configuracao nao encontrados. Reiniciando o modulo.");
        delay(2000);
    }
    fV_imprimeSerial("!!!!---- SETUP FINALIZADO ----!!!!",true);
}

void loop() {
    fB_atualizaHora();
    fV_resetarWatchdog();
    fV_checkSerialInput();
    fV_checkAcoesModulos();
    fV_enviaAcoesModulos();
    fV_checkHandShake();
    delay(2);
    vB_rodando = true;
}