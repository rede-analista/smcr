#ifndef GLOBALS_H
#define GLOBALS_H

/*=======================================
Inclusão de bibliotecas
*/
#include "include.h"

/*=======================================
Variáveis de configuração
*/
extern String ULTIMOS_GET_SERVIDOR, ULTIMOS_GET_RECEBIDOS;
/*=======================================
Variáveis de configuracao para uso durante execucao
*/
extern hw_timer_t *vHW_timer;  //Faz o controle do temporizador (interrupcao por tempo)
extern bool aB_restartRotinas[5]; //Reiniciar rotinas e tasks
extern String* aS_Preference;  //Guarda as configuracoes (substitui preferences)

/*=======================================
Arrays de configuracao para uso durante execucao
*/
extern String* aU8_diasDaSemana; //Contem dias da semana
extern String* aU8_meses;        //Contem nome dos meses
extern String* aS_Variaveis;     //Contem valores de variaveis string
extern uint32_t aU32_Variaveis[ARRAY_UINT32]; //Contem valores de variaveis uint8_t, uint16_t e uint32_t
extern bool aB_Variaveis[ARRAY_BOOL];         //Contem valores de variaveis bool
extern uint64_t aU64_Variaveis[ARRAY_UINT64]; //Contem valores de variaveis uint64_t
extern int32_t aI32_Variaveis[ARRAY_INT32];   //Contem valores de variaveis int8_t, int16_t e int32_t

/*=======================================
Variáveis e arrays dos pinos
*/
extern size_t vI8_aU16_Pinos;        //Total de linhas do array cadastro de pinos
extern size_t vI8_aS8_Pinos;         //Total de linhas do array cadastro de pinos (String)
extern uint16_t** aU16_Pinos;        //Cadastro de pinos (parâmetros)
extern String** aS8_Pinos;           //Cadastro de pinos (nome)
extern uint16_t** aU16_Pinos_Status; //Cadastro de pinos (status)
extern String** aS16_PinosMenu;      //Menu do cadastro de pinos
extern uint8_t** aU8_IgnoraPino;

/*=======================================
Variáveis e arrays das acoes
*/
extern uint16_t** aU16_ControlAcoesGroups; //Grupos de acoes, identifica se o pinos tem mais de uma acao configurada
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

/*=======================================
Variáveis e arrays dos Inter Modulos
*/
extern String** aS_InterModMenu; //Menu do cadasro de intermodulos
extern String** aU16_InterModMenu;
extern String** aSB_InterModMenu;
extern String** aS_InterMod;     //Cadastro de intermodulos
extern String** aS16_InterModMenu_CTRL_HandShake;
extern String** aS8_ControlMsgModHist;
extern uint16_t** aU16_InterMod;
extern uint16_t** aI16_InterMod_CTRL_HandShake;
extern uint8_t** aB_InterMod;
extern uint16_t** aS16_InterModFila_EnviaModulo;
extern uint16_t** aS16_InterModControleRepeticao_EnviaModulo;

/*=======================================
Inicia objetos, tipos e estruturas
*/
//enum class VarType {
//    STRING,
//    UINT8,
//    UINT16,
//    UINT32,
//    UINT64,
//    INT16,
//    BOOL,
//    UNKNOWN
//};
//struct Variable {                                           //Mapeamento funções para comandos via serial/get
//    std::function<void(String)> setter;
//    VarType type;
//};
//extern std::map<String, Variable> variables;                //Mapeamento funções para comandos via serial/get
typedef std::function<void()> Funcao;                       //Tipo para ponteiros de funcoes sem parametros
extern std::map<String, Funcao> mapaFuncoesSemParam;        //Mapa para funcoes sem parametros
extern std::map<String, std::function<void(AsyncWebServerRequest*)>> mapaFuncoesComParam; //Mapa para funcoes com parametros
extern struct tm timeinfo;                                  //Hora do módulo
extern AsyncWebServer* SERVIDOR_WEB_ASYNC;                  //Servidor web assíncrono
extern ESPAsyncHTTPUpdateServer* SERVIDOR_UPDATE;           //Servidor web para upgrade de firmware
extern AsyncWebSocket* ws;                                  //Websocket para serial web
extern asyncHTTPrequest* CLIENTE_WEB_ASYNC;                 //Cliente web para arquivos
extern HTTPClient CLIENTE_WEB_SYNC;                        //Cliente web para intermódulos
extern char aC_bufferTemp[256];                             //Usado para gerência dos arquivos da flash
extern File vF_arquivoUpload;                               //Usado para gerência dos arquivos da flash

#endif // GLOBALS_H
