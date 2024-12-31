# Conceitos e termos do sistema SMCR.
- SMCR == Sistema de Monitoramento e Controle Remoto.<br>
- Pino == Porta
- Pino Origem == Porta Origem == Pino de Entrada == Porta de Entrada == Pino de Sensor (botão, reed switch, etc.).<br>
- Pino Destino == Porta Destino == Pino de Saída == Porta de Saída == Pino de Controle (buzzer, led, relé, etc.).<br>
- Cadastro de Pino == Cadastro de Porta
  - Tipo do Pino == Tipo de Porta
    - 0=Sem Uso
    - 1=Digital
    - 192=Analógico
    - 65534=Remoto
  - Pino Mode()
    - 0=SEM USO ou PINO VIRTUAL
    - 1=INPUT
    - 3=OUTPUT
    - 4=PULLUP
    - 5=INPUT_PULLUP
    - 8=PULLDOWN
    - 9=INPUT_PULLDOWN
    - 10=OPEN_DRAIN
    - 12=OUTPUT_OPEN_DRAIN
    - 192=ANALOG<br>
- Cadastro de Ações
  - Ação
    - 0= NENHUMA
    - 1=LIGA
    - 2=LIGA DELAY
    - 3=PISCA
    - 4=PULSO
    - 5=PULSO DELAY
    - 65534=SÓ ENVIO DE STATUS

# Carregar tarefas no setup
- Conforme o valor do campo serão carregadas as tasks durante o setup
  - 0 = Não carrega nenhuma tarefa
  - 1 = Carrega tarefa de leitura de pinos [TaskLeituraPinos]
  - 2 = Carrega tarefa anteriores e mais a tarefa de 1ª ação [TaskAcoes1Pinos]
  - 3 = Carrega tarefa anteriores e mais a tarefa de 2ª ação [TaskAcoes1Pinos]
  - 4 = Carrega tarefa anteriores e mais a tarefa de 3ª ação [TaskAcoes1Pinos]
  - 5 = Carrega tarefa anteriores e mais a tarefa de 4ª ação [TaskAcoes1Pinos]

# Definição em esp32-hal-gpio.h
     //GPIO FUNCTIONS
     #define INPUT             0x01
     #define OUTPUT            0x03 
     #define PULLUP            0x04
     #define INPUT_PULLUP      0x05
     #define PULLDOWN          0x08
     #define INPUT_PULLDOWN    0x09
     #define OPEN_DRAIN        0x10
     #define OUTPUT_OPEN_DRAIN 0x12
     #define ANALOG            0xC0

     //Interrupt Modes
     #define DISABLED  0x00
     #define RISING    0x01
     #define FALLING   0x02
     #define CHANGE    0x03
     #define ONLOW     0x04
     #define ONHIGH    0x05
     #define ONLOW_WE  0x0C
     #define ONHIGH_WE 0x0D


# Definição dos pinos em pins_arduino.h
     static const uint8_t TX = 1;
     static const uint8_t RX = 3;

     static const uint8_t SDA = 21;
     static const uint8_t SCL = 22;

     static const uint8_t SS    = 5;
     static const uint8_t MOSI  = 23;
     static const uint8_t MISO  = 19;
     static const uint8_t SCK   = 18;

     static const uint8_t A0 = 36;
     static const uint8_t A3 = 39;
     static const uint8_t A4 = 32;
     static const uint8_t A5 = 33;
     static const uint8_t A6 = 34;
     static const uint8_t A7 = 35;
     static const uint8_t A10 = 4;
     static const uint8_t A11 = 0;
     static const uint8_t A12 = 2;
     static const uint8_t A13 = 15;
     static const uint8_t A14 = 13;
     static const uint8_t A15 = 12;
     static const uint8_t A16 = 14;
     static const uint8_t A17 = 27;
     static const uint8_t A18 = 25;
     static const uint8_t A19 = 26;

     static const uint8_t T0 = 4;
     static const uint8_t T1 = 0;
     static const uint8_t T2 = 2;
     static const uint8_t T3 = 15;
     static const uint8_t T4 = 13;
     static const uint8_t T5 = 12;
     static const uint8_t T6 = 14;
     static const uint8_t T7 = 27;
     static const uint8_t T8 = 33;
     static const uint8_t T9 = 32;

     static const uint8_t DAC1 = 25;
     static const uint8_t DAC2 = 26;

# Retorno Serial da Função f_enviaModulo()
     Usada para enviar informações entre os módulos de status dos pinos e enviuo de handshake.<br>
     Valor do campo CTRL_Resposta.
     
     "int f_enviaModulo(uint8_t idmodulo, String acao, String pino, String valor)"
     
     HTTPC_ERROR_CONNECTION_REFUSED  (-1)
     HTTPC_ERROR_SEND_HEADER_FAILED  (-2)
     HTTPC_ERROR_SEND_PAYLOAD_FAILED (-3)
     HTTPC_ERROR_NOT_CONNECTED       (-4)
     HTTPC_ERROR_CONNECTION_LOST     (-5)
     HTTPC_ERROR_NO_STREAM           (-6)
     HTTPC_ERROR_NO_HTTP_SERVER      (-7)
     HTTPC_ERROR_TOO_LESS_RAM        (-8)
     HTTPC_ERROR_ENCODING            (-9)
     HTTPC_ERROR_STREAM_WRITE        (-10)
     HTTPC_ERROR_READ_TIMEOUT        (-11)

# Retorno Serial da Função f_reconnectMQTT()
       Usada para conexão com servidor broker mqtt.

     "void f_reconnectMQTT()"

     MQTT_CONNECTION_TIMEOUT     -4
     MQTT_CONNECTION_LOST        -3
     MQTT_CONNECT_FAILED         -2
     MQTT_DISCONNECTED           -1
     MQTT_CONNECTED               0
     MQTT_CONNECT_BAD_PROTOCOL    1
     MQTT_CONNECT_BAD_CLIENT_ID   2
     MQTT_CONNECT_UNAVAILABLE     3
     MQTT_CONNECT_BAD_CREDENTIALS 4
     MQTT_CONNECT_UNAUTHORIZED    5
     MQTTCONNECT     1 << 4  // Client request to connect to Server
     MQTTCONNACK     2 << 4  // Connect Acknowledgment
     MQTTPUBLISH     3 << 4  // Publish message
     MQTTPUBACK      4 << 4  // Publish Acknowledgment
     MQTTPUBREC      5 << 4  // Publish Received (assured delivery part 1)
     MQTTPUBREL      6 << 4  // Publish Release (assured delivery part 2)
     MQTTPUBCOMP     7 << 4  // Publish Complete (assured delivery part 3)
     MQTTSUBSCRIBE   8 << 4  // Client Subscribe request
     MQTTSUBACK      9 << 4  // Subscribe Acknowledgment
     MQTTUNSUBSCRIBE 10 << 4 // Client Unsubscribe request
     MQTTUNSUBACK    11 << 4 // Unsubscribe Acknowledgment
     MQTTPINGREQ     12 << 4 // PING Request
     MQTTPINGRESP    13 << 4 // PING Response
     MQTTDISCONNECT  14 << 4 // Client is Disconnecting
     MQTTReserved    15 << 4 // Reserved

# Retorno Serial da Função f_configuraWIFI()
     Usada para conexão com wifi

     "uint8_t  f_configuraWIFI()"
  
     WL_NO_SHIELD        = 255   // for compatibility with WiFi Shield library
     WL_IDLE_STATUS      = 0
     WL_NO_SSID_AVAIL    = 1
     WL_SCAN_COMPLETED   = 2
     WL_CONNECTED        = 3
     WL_CONNECT_FAILED   = 4
     WL_CONNECTION_LOST  = 5
     WL_DISCONNECTED     = 6

# Parâmetros Recebidos Servidor WEB
     Argumento 0 = Nome do Dispositivo
     Argumento 1 = Acao
     Argumento 2 = Pino (pino prigem do módulo transmissor)
     Argumento 3 = Status do Pino

# Array aU8_ControlMsgMod para controle de execução de rotinas (não salvo).
     Controle o envio de menssagens entre os modulos ESP

     aU8_ControlMsgMod[Propriedade][Pino]
     aU8_ControlMsgMod[0][x] = Enviar Receptor Array 1 Acao
     aU8_ControlMsgMod[1][x] = Enviar Receptor Array 2 Acao
     aU8_ControlMsgMod[2][x] = Enviar Receptor Array 3 Acao

     uint8_t aU8_ControlMsgMod[aU32_Variaveis[20]][fU16_carregaConfigGeral(39, 15)]

# Array aU8_ControlMsgAss para controle de execução de rotinas (não salvo).
     Controle o envio de menssagens para assistentes

     aU8_ControlMsgAss[Propriedade][Pino]
     aU8_ControlMsgAss[0][x] = Enviar Assistentes Array 1 Acao
     aU8_ControlMsgAss[1][x] = Enviar Assistentes Array 2 Acao
     aU8_ControlMsgAss[2][x] = Enviar Assistentes Array 3 Acao

     uint8_t aU8_ControlMsgAss[aU32_Variaveis[20]][fU16_carregaConfigGeral(39, 15)]

# Array aU8_ControlMsgTelegram para controle de execução de rotinas (não salvo).
     Controle o envio de menssagens para telegram

     aU8_ControlMsgTelegram[Propriedade][Pino]
     aU8_ControlMsgTelegram[0][x] = Enviar Telegram Array 1 Acao
     aU8_ControlMsgTelegram[1][x] = Enviar Telegram Array 2 Acao
     aU8_ControlMsgTelegram[2][x] = Enviar Telegram Array 3 Acao

     uint8_t aU8_ControlMsgTelegram[aU32_Variaveis[20]][fU16_carregaConfigGeral(39, 15)]

# Array aU8_ControlMsgMqTT para controle de execução de rotinas (não salvo).
     Controle o envio de menssagens para broker mqtt

     aU8_ControlMsgMqTT[0][x] = Enviar Telegram Array 1 Acao
     aU8_ControlMsgMqTT[1][x] = Enviar Telegram Array 2 Acao
     aU8_ControlMsgMqTT[2][x] = Enviar Telegram Array 3 Acao

     uint8_t aU8_ControlMsgMqTT[aU32_Variaveis[20]][fU16_carregaConfigGeral(39, 15)]

# Array aU16_ControlAcoesGroups para controle de execução de rotinas (não salvo).
     Controle de acoes para mesmo pino destino (Grupo)

     aU16_ControlAcoesGroups[0][fU16_carregaConfigGeral(39, 15)] = Pino (que vai sofrer a acao)
     aU16_ControlAcoesGroups[1][fU16_carregaConfigGeral(39, 15)] = Referencia pinos de origem (que vão disparar a acao)

     uint16_t aU16_ControlAcoesGroups[aU32_Variaveis[5]][fU16_carregaConfigGeral(39, 15)]

# Array aU16_ControlHS para controle de execução de rotinas (não salvo).
     Controle de alerta de handshake para inter modulos

     aI16_InterMod_CTRL_HandShake[Propriedade][Modulo]
     aI16_InterMod_CTRL_HandShake[0][x] = Controle do ciclo de Handshake
     aI16_InterMod_CTRL_HandShake[1][x] = Status handshake
     aI16_InterMod_CTRL_HandShake[2][x] = Resposta de HTTP do módulo receptor
     aI16_InterMod_CTRL_HandShake[3][x] = Pausa no envio para o receptor

     uint16_t aU16_ControlHS[aU32_Variaveis[8]][fU16_carregaConfigGeral(47, 65535)]

# Array de dados aS_InterMod (carregado da flash)
     Usado para cadastro dos modulos (Inter Modulos)
     
     aS_InterMod[Propriedade][Modulo]
     aS_InterMod[0][x] = Nome Modulo
     aS_InterMod[1][x] = IP Modulo

     String aS_InterMod[aU32_Variaveis[7]][fU16_carregaConfigGeral(39, 15)]

# Array de dados aS_InterMod (carregado da flash)
     Usado para cadastro dos pinos de handhsake e habilitar envio de handshake (Inter Modulos)

     aU8_InterMod[Propriedade][Modulo]
     aU8_InterMod[0][x] = Pino HandShake
     aU8_InterMod[1][x] = Envia HandShake

     uint8_t aU8_InterMod[vI8_aU8_InterMod][fU16_carregaConfigGeral(39, 15)]

# Array de dados aU16_Pinos (carregado da flash)
     Usado para cadastro de porta (pinos fisicos)

     aU16_Pinos[Propriedade][Pino]
     aU16_Pinos[0][x] = Fisico - Mapeamento dos pinos fisicos
     aU16_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO / 65534=REMOTO
     aU16_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / REMOTO=65534
     aU16_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO
     aU16_Pinos[4][x] = Status 0=LOW / 1=HIGH
     aU16_Pinos[5][x] = Retencao 0=NAO / 1=SIM
     aU16_Pinos[6][x] = Tempo Retencao 0 a 65535

     size_t fU16_carregaConfigGeral(39, 15) = 5
     size_t vI8_aU16_Pinos = 6
     uint16_t aU16_Pinos[vI8_aU8_Pinos][fU16_carregaConfigGeral(39, 15)]

# Array de dados aS8_Pinos (carregado da flash)
     Usado para cadastro do nome(descricao) dos pinos

     aS8_Pinos[Propriedade][Pino]
     aS8_Pinos[0][x] = Nome/descricao

     size_t vI8_aS8_Pinos = 1
     String aS8_Pinos[vI8_aS8_Pinos][fU16_carregaConfigGeral(39, 15)]


# Array de dados aU16_AcaoX (carregado da flash)
     Usado para cadastro de acoes, eventos quando uma porta(pino) e acionada

     aU16_Acao[Propriedade][Pino]
     aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
     aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
     aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Delay / 3=Pisca / 4=Pulso / 5=Pulso Delay
     aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
     aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
     aU16_Acao[5][x] = Acionamento Alto=1 / Baixo=0

     uint16_t aU16_Acao1[aU32_Variaveis[17]][fU16_carregaConfigGeral(39, 15)]
     uint16_t aU16_Acao2[aU32_Variaveis[17]][fU16_carregaConfigGeral(39, 15)]
     uint16_t aU16_Acao3[aU32_Variaveis[17]][fU16_carregaConfigGeral(39, 15)]
     
# Array de dados aU16_AcaoRedeX (carregado da flash)
     Usado para cadastro de acoes, eventos de rede quando uma porta(pino) e acionada

     aU16_AcaoRede[Propriedade][Pino]
     aU16_AcaoRede[0][x] = Envia ao Modulo 0=Nao / 1 a 254=Sim, ID do módulo
     aU16_AcaoRede[1][x] = Envia ao Telegram 0=Nao / 1=Sim
     aU16_AcaoRede[2][x] = Envia ao MqTT 0=Nao / 1=Sim
     aU16_AcaoRede[3][x] = Notifica Assitente 0=Nao / 1=Sim

     uint16_t aU16_AcaoRede1[aU32_Variaveis[17]Rede][fU16_carregaConfigGeral(39, 15)]
     uint16_t aU16_AcaoRede2[aU32_Variaveis[17]Rede][fU16_carregaConfigGeral(39, 15)]
     uint16_t aU16_AcaoRede3[aU32_Variaveis[17]Rede][fU16_carregaConfigGeral(39, 15)]

# Array de dados aS8_AcaoX (carregado da flash)
     Usado para cadastro de acoes, eventos quando uma porta(pino) e acionada

     aS8_Acao[Propriedade][Pino]
     aS8_Acao[0][x] = Classe da acao para o MqTT
     aS8_Acao[1][x] = Icone da acao para o MqTT

     String aS8_Acao1[aU32_Variaveis[9]][fU16_carregaConfigGeral(39, 15)]
     String aS8_Acao2[aU32_Variaveis[9]][fU16_carregaConfigGeral(39, 15)]
     String aS8_Acao3[aU32_Variaveis[9]][fU16_carregaConfigGeral(39, 15)]

# Array de dados aS_Preference (carregado da flash)
     Usado para cadastro de configurações, guarda informações de configurações gerais do sistema.

     aS_Preference[Propriedade][Valor]
     aS_Preference[0] = "wifi" = Nome do wifi(ssid) que o módulo deve usar.
     aS_Preference[1] = "12345678" = Senha do wifi que o módulo deve usar.
     aS_Preference[2] = "4" = Número de tentativas de conexões.
     aS_Preference[3] = "4080" = Porta de escuta do servidor web.
     aS_Preference[4] = "esp32modularx" = Hostname do módulo.
     aS_Preference[5] = "admin" = Usuário de acesso a interface web.
     aS_Preference[6] = "admin" = Senha de acesso a interface web.
     aS_Preference[7] = aS_Preference[4] + "_" + aS_Preference[54] = Nome do ponto de acesso(SSID) para primeira configuraçao.
     aS_Preference[8] = "senha12345678" = Senha do ponto de acesso para primeira configuração.
     aS_Preference[9] = "true" = Habilita modo AP(ponto de acesso) caso não consiga conectar no wifi.
     aS_Preference[10] = "pool.ntp.br" = Servidor NTP.
     aS_Preference[11] = "pool.ntp.org" = Servidor NTP.
     aS_Preference[12] = "<-03>3" = Fuso horário NTP.
     aS_Preference[13] = "Tomato" = Cor para status com alerta.
     aS_Preference[14] = "LightGreen" = Cor para status sem alerta.
     aS_Preference[15] = "false" = Executa rotinas para telegram.
     aS_Preference[16] = "" = Chave da API do telegram.
     aS_Preference[17] = "" = ID do chat do telegram.
     aS_Preference[18] = "" = Usuário do telegram.
     aS_Preference[19] = "65535" = Tempo de verificação da rotina do telegram.
     aS_Preference[20] = "false" = Executa rotinas do MQTT.
     aS_Preference[21] = "pubsub" = Tópico MQTT.
     aS_Preference[22] = "" = Servidor MQTT.
     aS_Preference[23] = "" = Usuário MQTT.
     aS_Preference[24] = "" = Senha MQTT.
     aS_Preference[25] = "65535" = Tempo de verificação das rotinas do MQTT.
     aS_Preference[26] = "65535" = Tempo de envio de descoberta do MQTT.
     aS_Preference[27] = "1833" = Porta de escuta do servidor MQTT.
     aS_Preference[28] = "false" = Executa rotinas dos assistentes.
     aS_Preference[29] = "65535" = Tempo de verificação das rotinas dos assistentes.
     aS_Preference[30] = "" = Nome das caixas de som do goolge assistente.
     aS_Preference[31] = "" = Nome das caixas de som da alexa assistente.
     aS_Preference[32] = "pt_br" = Linguagem dos assistentes.
     aS_Preference[33] = "" = Frase inicial de alerta para os assistentes.
     aS_Preference[34] = "" = Frase final de alerta para os assistentes.
     aS_Preference[35] = "false" = Executa inter módulos.
     aS_Preference[36] = "65535" = Tempo de handshake do inter módulos.
     aS_Preference[37] = "65535" = Tempo de verificação das rotinas dos inter módulos.
     aS_Preference[38] = "10" = Ciclo de handshake.
     aS_Preference[39] = "15" = Total de pinos (portas do ESP) !!!! ATENÇÃO !!!!.
     aS_Preference[40] = "7" = Número de colunas das tabelas na interface web.
     aS_Preference[41] = "120" = Tempo  de refresh da tela pincipal (página de status).
     aS_Preference[42] = "80" = Tempo de clock do ESP32 em Mhz para whactdog.
     aS_Preference[43] = "false" = Executa rotinas de whachdog.
     aS_Preference[44] = "2147483647" = Tempo em microsegundos  (µs) de reset do watchdog .
     aS_Preference[45] = "12" = Quantidade de bits do processador (usado para pinos analógicos).
     aS_Preference[46] = "8" = Ciclos de amostra para pinos analógicos.
     aS_Preference[47] = "7" = Total de módulos para cadastro.
     aS_Preference[48] = "false" = Mostra status na página inicial.
     aS_Preference[49] = "false" = Mostra status inter módulos na página inicial.
     aS_Preference[50] = "5" = Quantidade de tasks de açãoes ativas.
     aS_Preference[51] = "30" = Tamanho da fila de histórico de envio de alertas para outros módulos.
     aS_Preference[52] = "2" = Nível de debug do log
     aS_Preference[53] = "25" = Tempo de delay nas tasks
     aS_Preference[54] = "12345" = ID único MQTT
     aS_Preference[55] = "false" = Autenticação para acesso web


# Array de dados aS_Variaveis (carregado da flash)
     Usado para carregar configurações string salvas na flash e utilizar em tempo de execução.
     
     aS_Variaveis[Propriedade][Valor]
     aS_Variaveis[0] = //Log
     aS_Variaveis[1] = //URI
     aS_Variaveis[2] = 
     aS_Variaveis[3] = //Payload http
     aS_Variaveis[4] = 
     aS_Variaveis[5] = 
     aS_Variaveis[6] = //Payload recebido
     aS_Variaveis[7] = //Session start:\n


# Array de dados aU32_Variaveis (carregado da flash)
     Usado para carregar configurações até uint32_t salvas na flash e utilizar em tempo de execução.
     
     aU32_Variaveis[Propriedade][Valor]
     aU32_Variaveis[2] = //Controle de histórico de envio
     aU32_Variaveis[5] = //Tamanho array de grupo de ações

     aU32_Variaveis[7] = //Total de "linhas" do array de inter modulos (String)
     aU32_Variaveis[8] =  //Total de "linhas" do array de inter modulos controle handshake e status handshake
     aU32_Variaveis[9] = //Total de "linhas" dos arrays de acoes (String)
     aU32_Variaveis[10] = //Início da coluna das tabelas de cadastro
     aU32_Variaveis[11] = //Final da coluna das tabelas de cadastro
     aU32_Variaveis[12] = //Controle de montagem de páginas HTML
     aU32_Variaveis[13] = //Tamanho do array dias da semana
     aU32_Variaveis[14] = //Tempo de refresh da página
     aU32_Variaveis[15] = //Total de "linhas" do array de inter modulos (uint_16)
     aU32_Variaveis[16] = //Total de "linhas" do array de inter modulos (Boolean)
     aU32_Variaveis[17] = //Total de "linhas" do array de ações (uint_16)
     aU32_Variaveis[18] = //Total de "linhas" do array de ações rede (uint_16)
     aU32_Variaveis[19] = //Total de "linhas" dos arrays de historico de envio de menssagens
     aU32_Variaveis[20] = //Total de "linhas" dos arrays de controle de envio de menssagens
     aU32_Variaveis[21] = //Controle do tempo de watchdog
     aU32_Variaveis[22] = //Intervalo de discovery do mqtt
     aU32_Variaveis[25] = //Intervalo de verificação do bot telegram
     aU32_Variaveis[26] = //Porta do servidor MQTT
     aU32_Variaveis[27] = //Intervalo de envio MQTT
     aU32_Variaveis[28] = //ID do último módulo que foi enviado informações de intermodulos
     aU32_Variaveis[30] = //Intervalo de verificção dos assistantes
     aU32_Variaveis[33] = //Clock do ESP32
     aU32_Variaveis[34] = //ID do último módulo recebido
     aU32_Variaveis[39] = //ID único para tópico MqTT


# Array de dados aB_Variaveis (carregado da flash)
     Usado para carregar configurações boleanas salvas na flash e utilizar em tempo de execução.

     aB_Variaveis[Propriedade][Valor]
     aB_Variaveis[0] = //Indica se o wifi está conectado.
     aB_Variaveis[1] = //Indica se o setup foi encerrado e o módulo está em execução.
     aB_Variaveis[2] = //Se é para rebootar o módulos
     aB_Variaveis[3] = //Se o filesys está montado
     aB_Variaveis[4] = //Se o whatchdog está em execução
     aB_Variaveis[5] = //Se o servidor web está em execução
     aB_Variaveis[6] = //Indica se o modo AP pode ser encerrado, se já foi configurado as informações iniciais do wifi. 
     aB_Variaveis[7] = //Se envia histórico de stauts a outro módulo
     aB_Variaveis[8] = //Pausa na execução de tasks e rotinas
     aB_Variaveis[9] = //Requisição em progresso



# Array de dados aI32_Variaveis (carregado da flash)
     Usado para carregar configurações inteiras salvas na flash e utilizar em tempo de execução.

     aI32_Variaveis[Propriedade][Valor]
     aI32_Variaveis[0] = //Controle de linha nos cadastros
     aI32_Variaveis[1] = //Código HTTP de resposta do intermodulos
     aI32_Variaveis[2] = //Controle handshake durante execução

# Array de dados aU64_Variaveis (carregado da flash)
     Usado para carregar configurações até uint64_t salvas na flash e utilizar em tempo de execução.
     
     aU64_Variaveis[Propriedade][Valor]
     aU64_Variaveis[0] = //Controle de loop para verificação de ações intermodulos
     aU64_Variaveis[1] = //Controle de loop para envio de ações intermodulos
     aU64_Variaveis[2] = //Controle de loop para verificação e envio de handshack
     aU64_Variaveis[3] = //Controle de loop para verificação de ações mqtt
