

#ifndef INCLUDE_H
#define INCLUDE_H

/*=======================================
Definições para uso em bibliotecas e programa
*/
#define HTTP_PARSER_NO_STDIO
#define HTTP_PARSER_NO_GETADDRINFO
#define MAX_JSON_SIZE 6000
#define FORMAT_SPIFFS_IF_FAILED true
#define LITTLE_FS 0
#define SPIFFS_FS 1
#define FILESYSTYPE SPIFFS_FS
#define FILEBUFSIZ 4096
#define FILESYS LittleFS
#define DEST_FS_USES_LITTLEFS

#ifndef ARRAY_MESES
#define ARRAY_MESES 12
#endif

#ifndef ARRAY_PREFERENCE_COL
#define ARRAY_PREFERENCE_COL 255
#endif

#ifndef ARRAY_DIA_SEMANA
#define ARRAY_DIA_SEMANA 7
#endif

#ifndef ARRAY_STRING
#define ARRAY_STRING 50
#endif

#ifndef ARRAY_UINT32
#define ARRAY_UINT32 3
#endif

#ifndef ARRAY_BOOL
#define ARRAY_BOOL 4
#endif

#ifndef ARRAY_UINT64
#define ARRAY_UINT64 4
#endif

#ifndef ARRAY_INT32
#define ARRAY_INT32 50
#endif

/*=======================================
Inclusão de bibliotecas
*/
#include <Arduino.h>
#include <stdint.h>
#include <Preferences.h>
#include <FS.h>
#include "SPIFFS.h" // Use apenas SPIFFS ou LittleFS
#include "LittleFS.h"
#include <nvs_flash.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <time.h>
#include <esp_sntp.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncHTTPUpdateServer.h>
#include <asyncHTTPrequest.h>
#include <cmath>
#include <map>
#include <functional>
#include <AsyncWebSocket.h>
#include <variant>
#include <string.h>
#include <ESP32-targz.h>
//#include "globals.h"
#include "WEB_Gerencia_Arquivos.h"

/*=======================================
Declaracao de Funcoes
*/
void fV_mapaFuncoes();
void fsList(void);
bool initFS(bool format, bool force);
uint16_t fU16_pinosUsados();
void compactarArquivos(AsyncWebServerRequest* request, String arquivos);
void handleFileDownload(AsyncWebServerRequest *request);
void handleFileDelete(AsyncWebServerRequest *request);
void fV_recebeDados(AsyncWebServerRequest *request);
uint16_t fU16_retornaIndicePino(uint16_t pino);
uint8_t fU8_retornaIndiceHS(String modulo);
int fI_retornaModulo(String modulo);
void fV_checkHandShake();
String fS_retornaIpModulo(uint16_t modulo);
uint16_t fU16_retornaIndiceModulo(uint16_t modulo);
int fI_enviaModulo(uint16_t idmodulo, String acao, String pino, String valor);
void fV_enviaAcoesModulos();
void fV_restartTasks();
void fV_mudaExec();
void fV_Preference(String op = "L",bool force = false);
bool fB_verificaPrimeiraExec(bool force = false);
bool fV_regModHist(uint16_t idmodulo, uint16_t acao, uint16_t pino, uint16_t valor);
void fV_checkAcoesModulos();
void fV_checkSerialInput();
template<typename T>
void registerVariable(const String& name, T& variable);
VarType getVariableType(const String& varName);
bool setVariable(const String& varName, const String& value);
String fS_retornaTipoVariavel(const VarType& var);
bool fB_alteraVariavel(const String& varName, const String& value);
void fV_handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void fV_onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
void fV_sendSerialData(String message);
void fV_gravaPino(uint16_t tipo, uint16_t pino, uint16_t valor);
bool fB_retornaStatusGrupoAcao(String pinos, uint8_t status);
String fS_retornaGrupoAcao(uint16_t pino);
uint16_t fU16_lePino(uint16_t tipo, uint16_t invert, uint16_t pino);
String fS_traduzAcoes(uint16_t cod);
uint16_t fU16_retornaIndicePino(uint16_t pino);
bool fB_atualizaHora();
void fV_grupoAcoes(bool force);
void fV_formataFLASH ();
uint64_t fU64_stringToULong64(const String& str);
void fV_configuraWatchDog(const bool force = false);
void fV_resetarWatchdog();
void IRAM_ATTR fV_resetModule();
void fV_iniciaAcoes(bool force);
void fV_iniciaInterModulos();
void fV_configuraModulos(bool force);
void fV_salvarFlash();
String fS_calculaBytes(const size_t bytes);
String processor(const String& var);
bool fB_configuraServidorWEB(const uint16_t& porta = 65535, bool force = false);
bool fV_apagaTodosArquivosSPIFFS() ;
void fV_iniciaPreference(bool force);
void fV_iniciaPinos(bool force);
void f_cria_MDNS(String nome, IPAddress ip, uint16_t porta);
void fV_configNTP();
void fV_callbackNTP(struct timeval *t);
void fV_modoAP(String wifi, String senha, uint16_t portaap);
uint8_t fU8_configuraWifi();
String fS_listaArquivosFilesys(bool ishtml);
String fS_listDir(const char * dirname, uint8_t levels);
String fS_DataHora();
String fS_Uptime();
int32_t fI32_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const int32_t padrao = 65535);
uint32_t fU32_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const uint32_t& padrao = 65535);
uint16_t fU16_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const uint16_t& padrao = 65535);
uint8_t fU8_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const uint8_t& padrao = 255);
String fS_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const String& padrao = "");
bool fB_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const bool& padrao = false);
String fS_idPlaca();
bool fB_montaLittleFS();
void fV_salvaFILESYS_AS1D(const char* fileName, String* arr, uint8_t size);
void fV_carregaFILESYS_AS1D(const char* fileName, String*& arr, uint8_t& size, String sol = "");
void fV_salvaFILESYS_AS2D(const char* fileName, String** arr, size_t rows, size_t cols);
void fV_carregaFILESYS_AS2D(const char* fileName, String**& arr, size_t rows, size_t cols, String sol = "");
void fV_salvaFlash_AUint(const char* filename, uint16_t** arr, size_t rows, size_t cols);
void fV_carregaFlash_AUint(const char* filename, uint16_t**& array, size_t rows, size_t cols, String sol = "");
void fV_geraValoresArray2D_S(String** array, size_t rows, size_t cols);
void fV_imprimirArray2D_S(String** array, size_t rows, size_t cols, bool linha = false);
void fV_geraValoresArray2D_U16(uint16_t** array, size_t rows, size_t cols);
void fV_imprimirArray2D_U16(uint16_t** array, size_t rows, size_t cols, bool linha = false);
String fS_limpaEspacoFimLinha(const String& str);
void fV_salvaFlash_AUint(const char* filename, uint8_t** arr, size_t rows, size_t cols);
void fV_carregaFlash_AUint(const char* filename, uint8_t**& array, size_t rows, size_t cols, String sol = "");
void fV_imprimeSerial(uint8_t nivelLog, const String& mensagem, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, const char* mensagem, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, int valor, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, size_t valor, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, uint8_t valor, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, uint16_t valor, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, bool valor, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, float valor, bool pularLinha = true, int casasDecimais = 2);
void fV_imprimeSerial(uint8_t nivelLog, double valor, bool pularLinha = true, int casasDecimais = 2);
void fV_imprimeSerial(uint8_t nivelLog, String mensagem, uint16_t numero, bool pularLinha);
void fV_imprimeSerial(uint8_t nivelLog, const uint16_t** array, size_t rows, size_t cols, bool pularLinha = true);
void fV_imprimeSerial(uint8_t nivelLog, const String** array, size_t rows, size_t cols, bool pularLinha = true);

/*=======================================
Declaracao de Funcoes TASKS
*/
void TaskLeituraPinos(void *pvParameters);
void TaskAcoes1Pinos(void *pvParameters);
void TaskAcoes2Pinos(void *pvParameters);
void TaskAcoes3Pinos(void *pvParameters);
void TaskAcoes4Pinos(void *pvParameters);

/*=======================================
Declaracao de Funcoes HTML
*/
void fV_enviarArquivo(const char* ipDestino, const char* nomeArquivo);
void f_handle_SerialOutput(AsyncWebServerRequest *request);
void f_handle_SerialWeb(AsyncWebServerRequest *request);
void f_handle_OpcoesFuncoes(AsyncWebServerRequest *request);
void f_handle_salvarCadastroGeral(AsyncWebServerRequest *request);
void f_handle_CadastroGeral(AsyncWebServerRequest *request);
void handle_Update();
void handleFileDownload(AsyncWebServerRequest *request);
void handleFileUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
void executarFuncaoSim();
void executarFuncaoNao();
void fV_resposta(AsyncWebServerRequest *request);
void f_handle_SalvaFlash(AsyncWebServerRequest *request);
String fS_cabecaHTML(String TIT, String H1, String url = "/", String ajuda = "");
String fS_rodapeHTML(String url = "/", String ajuda = "");
void fV_salvarRede(AsyncWebServerRequest *request);
void fV_salvarPinos(AsyncWebServerRequest *request);
void fV_cadastraPino(AsyncWebServerRequest *request);
size_t f_handle_ConfiguraPortas(unsigned char *data, size_t len, bool final);
void fV_salvarAcoes(AsyncWebServerRequest *request);
void fV_cadastraAcoes(AsyncWebServerRequest *request);
size_t f_handle_ConfiguraAcoes(unsigned char *data, size_t len, bool final);
void fV_restart();
void f_handle_OTA(AsyncWebServerRequest *request);
void f_limpaFLASH(AsyncWebServerRequest *request);
void f_handle_OpcoesGerais(AsyncWebServerRequest *request);
void f_handle_ConfiguraWifi(AsyncWebServerRequest *request);
void f_handle_SalvarWifiInicio(AsyncWebServerRequest *request);
void f_handle_Index(AsyncWebServerRequest *request);
void f_handle_ConfiguraWifiInicio(AsyncWebServerRequest *request);
void f_handle_NotFound(AsyncWebServerRequest *request);
void fV_salvarModulos(AsyncWebServerRequest *request);
void fV_salvarInterModulos(AsyncWebServerRequest *request);
void fV_cadastraModulo(AsyncWebServerRequest *request);
size_t f_handle_ConfiguraModulos(unsigned char *data, size_t len, bool final);

#endif // INCLUDE_H