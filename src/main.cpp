/*=======================================
Inclusão de bibliotecas
*/
#include "include.h"
#include "globals.h"

/*
  SKETCH: SMCR MODULAR
  DESCRICAO: Realizar leitura de pinos de entrada acionando pinos de saida e
             enviando a outro modulo ESP(RECEPTOR) as informacoes dos pinos de entrada.
             O ESP  receptor funcionara como uma extensao do ESP  transmissor e/ou
             como se fosse um modulo central.
*/

/*=======================================
Variaveis Globais e Controles Internos
*/
String ULTIMOS_GET_SERVIDOR, ULTIMOS_GET_RECEBIDOS = "";
/*=======================================
variáveis de controle para uso durante execucao
*/
hw_timer_t *vHW_timer = NULL;  //Faz o controle do temporizador (interrupcao por tempo)
bool aB_restartRotinas[5] = {0,0,0,0,0}; //Indica qual task deve se auto reconfigurar

/*=======================================
Arrays de configuracao para uso durante execucao
*/
String* aS_Variaveis = nullptr; //Contem valores de variaveis string
uint32_t aU32_Variaveis[ARRAY_UINT32] = {}; //Contem valores de variaveis uint32_t
bool aB_Variaveis[ARRAY_BOOL] = {}; //Contem valores de variaveis bool
uint64_t aU64_Variaveis[ARRAY_UINT64] = {}; //Contem valores de variaveis uint64_t
int32_t aI32_Variaveis[ARRAY_INT32] = {}; //Contem valores de variaveis uint64_t
uint8_t vU8_meses = ARRAY_MESES; //Tamanho do array meses do ano
String* aU8_diasDaSemana = nullptr; //Contem o índice do dia da semana 0 a 6
String* aU8_meses = nullptr; //Contem o índice do mês 0 a 11

/*=======================================
Arrays de cadastro e controle de configurações gerais
*/
String* aS_Preference = nullptr;

/*=======================================
Arrays de cadastro e controle dos pinos
*/
size_t vI8_aU16_Pinos = 6; //Total de linhas do array cadastro de pinos (aU16_Pinos)
size_t vI8_aS8_Pinos = 1; //Total de linhas do array cadastro de pinos (nome)
uint16_t** aU16_Pinos = nullptr;//Cadastro de pinos (parametros)
String** aS8_Pinos = nullptr; //Cadastro de pinos (nome)
uint16_t** aU16_Pinos_Status = nullptr; //Cadastro de pinos (status)
String** aS16_PinosMenu = nullptr; //Menu para cadastro de pinos
uint8_t** aU8_IgnoraPino = nullptr;

/*=======================================
Arrays de cadastro e controle dos modulos
*/
String** aS_InterModMenu = nullptr; //Menu do cadastro de Intermodulos
String** aU16_InterModMenu = nullptr;
String** aSB_InterModMenu = nullptr;
String** aS8_ControlMsgModHist = nullptr;
String** aS_InterMod = nullptr;  //Cadastro de Intermodulos (Nome e IP)
uint16_t** aU16_InterMod = nullptr; //Cadastro de Intermodulos (ID e Porta)
uint8_t** aB_InterMod = nullptr;  //Cadastro de Intermodulos (Envia HandShake)
String** aS16_InterModMenu_CTRL_HandShake = nullptr; //Menu do array de controle de comunicacao Intermodulos
uint16_t** aI16_InterMod_CTRL_HandShake = nullptr; //Controle de alerta de handshake para Intermodulos
uint16_t** aS16_InterModFila_EnviaModulo = nullptr; //Controle o envio de menssagens entre os modulos ESP
uint16_t** aS16_InterModControleRepeticao_EnviaModulo = nullptr; //Controle o envio de menssagens entre os modulos ESP

/*=======================================
Arrays de cadastro e controle das acoes
*/
String** aS8_Acao1 = nullptr;  //Cadastro de acoes 1
String** aS8_Acao2 = nullptr;  //Cadastro de acoes 2
String** aS8_Acao3 = nullptr;  //Cadastro de acoes 3
String** aS8_Acao4 = nullptr;  //Cadastro de acoes 4
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
uint16_t** aU16_ControlAcoesGroups = nullptr; //Grupos de acoes, identifica se o pinos tem mais de uma acao configurada

/*=======================================
Declaração de objetos, tipos e structs
*/
//File jsonFile;
std::map<String, Funcao> mapaFuncoesSemParam;
std::map<String, std::function<void(AsyncWebServerRequest*)>> mapaFuncoesComParam;
//std::map<String, Variable> variables;
//Preferences CONFIG_FLASH;
AsyncWebServer* SERVIDOR_WEB_ASYNC = nullptr;
asyncHTTPrequest* CLIENTE_WEB_ASYNC = nullptr;
HTTPClient CLIENTE_WEB_SYNC; 
ESPAsyncHTTPUpdateServer* SERVIDOR_UPDATE = nullptr;
AsyncWebSocket* ws = nullptr;
//Config config;
struct tm timeinfo;
char aC_bufferTemp[256];
char aC_filesysName[] = "LittleFS";
File vF_arquivoUpload;

/*=======================================
SETUP() - Configurações iniciais
*/
void setup() {
  Serial.begin(115200); //Configura serial com velocidade de 115200
  delay(3000);
  Serial.println("Executando verificacoes iniciais.");
  aB_Variaveis[3] = fB_montaLittleFS();  //Monta LittleFS (FILESYS)
  if (fB_verificaPrimeiraExec(false)) { //Verifica se existem os arquivos de configurações se não existir cria
    fV_Preference("LER"); //Carrega configuracoes do filesys
    fV_imprimeSerial(1,"||||---- INICIANDO SETUP ----||||",true);  
    fS_infoPlaca(); //Imprime na serial informacoes da placa
    fV_infoMemoria(); //Imprime na serial informações da memória    
    fV_mapaFuncoes();  //Mapeia funcoes para uso nos GETS/POSTS
    fV_carregaFILESYS_AS1D("/aU8_diasDaSemana.txt",aU8_diasDaSemana,ARRAY_DIA_SEMANA);  //Carrega array com os dias da semana
    fV_carregaFILESYS_AS1D("/aU8_meses.txt",aU8_meses,vU8_meses);  //Carrega array com os meses
    fV_imprimeSerial(1,fS_DataHora(),true); //Imprime na serial data e hora
    fS_listDir("/",4); //Lista arquivos em salvos em SPIFFS(LittleFS)
    fV_iniciaControles(false); //Inicia configurações dos pinos
    fV_iniciaPinos(false); //Inicia configurações dos pinos
    fV_iniciaAcoes(false);  //Inicia configuracoes das acoes
    fU8_configuraWifi(); //Configurar o wifi
    fU8_verificaWifi(); //Conecta o módulo no wifi ou coloca em modo AP(se habilitado) caso nao consiga conexao com wifi
    fB_configuraServidorWEB(false); //Configura servidor web para acesso ao esp32
    fV_configuraModulos(false);  //Configura intermodulos
    fV_imprimeSerial(1,"Iniciando tarefas... ");
    xTaskCreate(TaskLeituraPinos, "t_LePinos", 2560, NULL, 3, NULL); //Inicia tarefa(task) para execução continua de leitura de portas(pinos)
    fV_imprimeSerial(1," - ativando task leitura pinos - ");
    delay(600);
    switch (fU8_carregaConfigGeral(50,5)) {
      case 0:
        fV_imprimeSerial(1," - sem tasks ativas - ");
      case 1:
        xTaskCreate(TaskAcoes1Pinos, "t_Ac1Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 1
        fV_imprimeSerial(1," - ativando task acoes 1 - ");
        break;
      case 2:
        xTaskCreate(TaskAcoes2Pinos, "t_Ac2Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 2
        fV_imprimeSerial(1," - ativando task acoes 2 - ");
        break;
      case 3:
        xTaskCreate(TaskAcoes3Pinos, "t_Ac3Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 3
        fV_imprimeSerial(1," - ativando task acoes 3 - ");
        break;
      case 4:
        xTaskCreate(TaskAcoes4Pinos, "t_Ac4Pinos", 2560, NULL, 2, NULL); //Inicia tarefa(task) para execução continua de das acoes 4
        fV_imprimeSerial(1," - ativando task acoes 4 - ");
        break;
      case 5:
        fV_imprimeSerial(1," - ativando tasks acoes 1 a 4 - ");
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
    fV_configuraWatchDog(false);  //Configura watchdog
    if (fB_carregaConfigGeral(35, false)) { //Se intermodulos estiver habilitado marca para enviar histórico de alertas
        aB_Variaveis[7] = true;
    }
    fV_imprimeSerial(1,"!!!!---- SETUP FINALIZADO ----!!!!",true);
    aB_Variaveis[0] = true;
  } else { //Reboota se faltou algum arquivo de configuração e precisou ser recriado
    Serial.print("Arquivos de configuracao nao encontrados e foram criados. Reiniciando o modulo.");
    delay(2000);
    fV_restart();
  }
}

/*=======================================
LOOP() - Execução contínua
*/
void loop() {
  fB_atualizaHora();
  fV_resetarWatchdog();
  fV_checkSerialInput();
  fV_checkAcoesModulos();
  fV_enviaAcoesModulos();
  fV_checkHandShake();
  delay(2);
}