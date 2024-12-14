// globals.h

#ifndef GLOBALS_H
#define GLOBALS_H

#include "include.h"

// Variáveis de configuração
extern String vS_nomeDispositivo, vS_nomeWifi, vS_senhaWifi, vS_nomeAP_Wifi, vS_senhaAP_Wifi, 
            vS_api_Telegram, vS_chat_Telegram, vS_user_Telegram, vS_mqttTopico, 
            vS_mqttDiscovery, vS_mqttServer, vS_mqttUser, vS_mqttSenha, 
            vS_mqttIdUnico, vS_assNomeGoogle, vS_assNomeAlexa, vS_assLinguagem, 
            vS_ass_Alerta, vS_ass_Normal, vS_corStatus1, vS_corStatus0, 
            vS_ntpServer1, vS_ntpServer2, vS_timeZone, vS_userWeb, vS_passWeb,
            vS_logStr, vS_uri, GET_SERVIDOR, vS_payload, ULTIMOS_GET_RECEBIDOS,
            ULTIMOS_GET_SERVIDOR, vS_payrec;

extern uint8_t vU8_tentativaConexoes, vI_cicloHandshake, vU8_crtl_ModHist, vU8_bitsProc, vU8_PinosCadastrados,
            vU8_ciclosAmostra, vI8_ControlAcoesGroups, vU8_colunasTabelas, vI8_aS_InterMod, vI8_aU16_InterModHA,
            vI8_aS8_Acao, vU8_colINICIO, vU8_colFIM, vU8_estado, vU8_diasDaSemana, vU8_meses, vU8_tempoRefresh,
            vI8_aU16_InterMod, vI8_aB_InterMod, vI8_aU16_Acao, vI8_aU8_AcaoRede, vI8_aU8_ControlMsgHist,
            vI8_aU8_ControlMsg, vI8_aS_Preference_ROW, vI8_aS_Preference_COL, vI8_aS16_InterModFila_EnviaModulo;

extern uint16_t vU16_bot_MTBS, vU16_mqttPorta, vU16_mqtt_MTBS, vU8_ultimoModEnviado, vI_U16_portaWebAsync,
            vU16_ass_MTBS, vU16_modulos_HandShake, vU16_modulos_MTBS_Acoes, vU16_clockESP32, vU16_ulimoModRecebido;

extern int16_t vU16_linhaPagCad, vI_httpResponseCode, vI_controleCicloHandshake;

extern uint32_t vU32_mqtt_disc_MTBS, vU32_tempoWatchDog;

extern uint64_t vU64_ota_progress_millis, check_acoes_mod_lasttime, envia_acoes_mod_lasttime, check_mod_lasttime,
            check_acoes_mqtt_lasttime;

extern bool vB_exec_Telegram, vB_modoAP, vB_exec_MqTT, vB_exec_Assistente, vB_exec_Modulos, vB_emExecucaoWifi,
            vB_finalizaModoAP, VB_mostra_Status, vB_executaReboot, vB_filesysIniciado, vB_exec_WatchDog, 
            vB_emExecucaoWDog, vB_emExecucaoWS, vB_rodando, vB_envia_Historico, vB_pausaEXECs, request_in_progress,
            VB_mostra_Interm, vB_pedeAutentica;

extern String* aU8_diasDaSemana;
extern String* aU8_meses;
extern File jsonFile;
extern hw_timer_t *vHW_timer;  // Faz o controle do temporizador (interrupcao por tempo)
extern bool aB_restartRotinas[5]; // Reiniciar rotinas e tasks
extern String** aS_Preference;  // Guarda as configuracoes (substitui preferences)
extern size_t vU8_totTask;

/*---- Variáveis e arrays dos pinos ----*/
extern size_t vU8_totPinos;          // Total de colunas do array cadastro de pinos
extern size_t vI8_aU16_Pinos;        // Total de linhas do array cadastro de pinos
extern size_t vI8_aS8_Pinos;         // Total de linhas do array cadastro de pinos (String)
extern uint16_t** aU16_Pinos;        // Cadastro de pinos (parâmetros)
extern String** aS8_Pinos;           // Cadastro de pinos (nome)
extern uint16_t** aU16_Pinos_Status; // Cadastro de pinos (status)
extern String** aS16_PinosMenu;      // Menu do cadastro de pinos
extern uint8_t** aU8_IgnoraPino;

/*---- Variáveis e arrays das acoes ----*/
extern uint16_t** aU16_ControlAcoesGroups; // Grupos de acoes, identifica se o pinos tem mais de uma acao configurada
extern String** aS8_Acao1;
extern String** aS8_Acao2;
extern String** aS8_Acao3;
extern String** aS8_Acao4;
extern uint16_t** aU16_Acao1;
extern uint16_t** aU16_Acao2;
extern uint16_t** aU16_Acao3;
extern uint16_t** aU16_Acao4;
extern uint16_t** aU8_AcaoRede1;
extern uint16_t** aU8_AcaoRede2;
extern uint16_t** aU8_AcaoRede3;
extern uint16_t** aU8_AcaoRede4;
extern String** aS8_AcoesMenu;
extern String** aS8_AcoesRedeMenu;
extern String** aS8_AcoesStringMenu;

/*---- Variáveis e arrays dos Inter Modulos ----*/
extern size_t vU8_totModulos;
extern String** aS_InterModMenu; // Menu do cadasro de intermodulos
extern String** aU16_InterModMenu;
extern String** aSB_InterModMenu;
extern String** aS_InterMod;     // Cadastro de intermodulos
extern String** aS16_InterModMenu_CTRL_HandShake;
extern String** aS8_ControlMsgModHist;
extern uint16_t** aU16_InterMod;
extern uint16_t** aI16_InterMod_CTRL_HandShake;
extern uint8_t** aB_InterMod;
extern uint16_t** aS16_InterModFila_EnviaModulo;
extern uint16_t** aS16_InterModControleRepeticao_EnviaModulo;

/*---- Inicia objetos, tipos e estruturas ----*/
enum class VarType {
    STRING,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    INT16,
    BOOL,
    UNKNOWN
};
struct Variable {
    std::function<void(String)> setter;
    VarType type;
};
extern std::map<String, Variable> variables;

typedef std::function<void()> Funcao;        // Tipo para ponteiros de funcoes sem parametros
extern std::map<String, Funcao> mapaFuncoesSemParam; // Mapa para funcoes sem parametros
extern std::map<String, std::function<void(AsyncWebServerRequest*)>> mapaFuncoesComParam;  // Mapa para funcoes com parametros
extern struct tm timeinfo;
struct Config {                // Gerencia de Arquivos
    String ssid;               // wifi ssid
    String wifipassword;       // wifi password
    String httpuser;           // username to access web admin
    String httppassword;       // password to access web admin
    int webserverporthttp;};   // http port number for web admin
extern Preferences CONFIG_FLASH;     
extern AsyncWebServer* SERVIDOR_WEB_ASYNC;
extern ESPAsyncHTTPUpdateServer* SERVIDOR_UPDATE;
extern AsyncWebSocket* ws;
extern Config config;
extern asyncHTTPrequest* CLIENTE_WEB_ASYNC;

extern char aC_bufferTemp[256];
extern char aC_filesysName[];
extern File vF_arquivoUpload;

#endif // GLOBALS_H
