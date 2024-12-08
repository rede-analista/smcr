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

     uint8_t aU8_ControlMsgMod[vI8_aU8_ControlMsg][vU8_totPinos]

# Array aU8_ControlMsgAss para controle de execução de rotinas (não salvo).
     Controle o envio de menssagens para assistentes

     aU8_ControlMsgAss[Propriedade][Pino]
     aU8_ControlMsgAss[0][x] = Enviar Assistentes Array 1 Acao
     aU8_ControlMsgAss[1][x] = Enviar Assistentes Array 2 Acao
     aU8_ControlMsgAss[2][x] = Enviar Assistentes Array 3 Acao

     uint8_t aU8_ControlMsgAss[vI8_aU8_ControlMsg][vU8_totPinos]

# Array aU8_ControlMsgTelegram para controle de execução de rotinas (não salvo).
     Controle o envio de menssagens para telegram

     aU8_ControlMsgTelegram[Propriedade][Pino]
     aU8_ControlMsgTelegram[0][x] = Enviar Telegram Array 1 Acao
     aU8_ControlMsgTelegram[1][x] = Enviar Telegram Array 2 Acao
     aU8_ControlMsgTelegram[2][x] = Enviar Telegram Array 3 Acao

     uint8_t aU8_ControlMsgTelegram[vI8_aU8_ControlMsg][vU8_totPinos]

# Array aU8_ControlMsgMqTT para controle de execução de rotinas (não salvo).
     Controle o envio de menssagens para broker mqtt

     aU8_ControlMsgMqTT[0][x] = Enviar Telegram Array 1 Acao
     aU8_ControlMsgMqTT[1][x] = Enviar Telegram Array 2 Acao
     aU8_ControlMsgMqTT[2][x] = Enviar Telegram Array 3 Acao

     uint8_t aU8_ControlMsgMqTT[vI8_aU8_ControlMsg][vU8_totPinos]

# Array aU16_ControlAcoesGroups para controle de execução de rotinas (não salvo).
     Controle de acoes para mesmo pino destino (Grupo)

     aU16_ControlAcoesGroups[0][vU8_totPinos] = Pino (que vai sofrer a acao)
     aU16_ControlAcoesGroups[1][vU8_totPinos] = Referencia pinos de origem (que vão disparar a acao)

     uint16_t aU16_ControlAcoesGroups[vI8_ControlAcoesGroups][vU8_totPinos]

# Array aU16_ControlHS para controle de execução de rotinas (não salvo).
     Controle de alerta de handshake para inter modulos

     aU16_ControlHS[0][vU8_totPinos] = Controle do Tempo de Handshake
     aU16_ControlHS[1][vU8_totPinos] = Status handshake
     aU16_ControlHS[2][vU8_totPinos] = Controle de Resposta de Handshake

     uint16_t aU16_ControlHS[vI8_aU16_InterModHA][vU8_totPinos]

# Array de dados aS_InterMod (carregado da flash)
     Usado para cadastro dos modulos (Inter Modulos)
     
     aS_InterMod[Propriedade][Modulo]
     aS_InterMod[0][x] = Nome Modulo
     aS_InterMod[1][x] = IP Modulo

     String aS_InterMod[vI8_aS_InterMod][vU8_totPinos]

# Array de dados aS_InterMod (carregado da flash)
     Usado para cadastro dos pinos de handhsake e habilitar envio de handshake (Inter Modulos)

     aU8_InterMod[Propriedade][Modulo]
     aU8_InterMod[0][x] = Pino HandShake
     aU8_InterMod[1][x] = Envia HandShake

     uint8_t aU8_InterMod[vI8_aU8_InterMod][vU8_totPinos]

# Array de dados aU16_Pinos (carregado da flash)
     Usado para cadastro de porta (pinos fisicos)

     aU16_Pinos[Propriedade][Pino]
     aU16_Pinos[0][x] = Fisico - Mapeamento dos pinos fisicos
     aU16_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO / 254=REMOTO
     aU16_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / REMOTO=254
     aU16_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO
     aU16_Pinos[4][x] = Status 0=LOW / 1=HIGH
     aU16_Pinos[5][x] = Retencao 0=NAO / 1=SIM
     aU16_Pinos[6][x] = Tempo Retencao 0 a 255

     size_t vU8_totPinos = 5
     size_t vI8_aU16_Pinos = 6
     uint16_t aU16_Pinos[vI8_aU8_Pinos][vU8_totPinos]

# Array de dados aS8_Pinos (carregado da flash)
     Usado para cadastro do nome(descricao) dos pinos

     aS8_Pinos[Propriedade][Pino]
     aS8_Pinos[0][x] = Nome/descricao

     size_t vI8_aS8_Pinos = 1
     String aS8_Pinos[vI8_aS8_Pinos][vU8_totPinos]


# Array de dados aU16_AcaoX (carregado da flash)
     Usado para cadastro de acoes, eventos quando uma porta(pino) e acionada

     aU16_Acao[Propriedade][Pino]
     aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
     aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
     aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Delay / 3=Pisca / 4=Pulso / 5=Pulso Delay
     aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
     aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
     aU16_Acao[5][x] = Acionamento Alto=1 / Baixo=0

     uint16_t aU16_Acao1[vI8_aU16_Acao][vU8_totPinos]
     uint16_t aU16_Acao2[vI8_aU16_Acao][vU8_totPinos]
     uint16_t aU16_Acao3[vI8_aU16_Acao][vU8_totPinos]
     
# Array de dados aU16_AcaoRedeX (carregado da flash)
     Usado para cadastro de acoes, eventos de rede quando uma porta(pino) e acionada

     aU16_AcaoRede[Propriedade][Pino]
     aU16_AcaoRede[0][x] = Envia ao Modulo 0=Nao / 1 a 254=Sim, ID do módulo
     aU16_AcaoRede[1][x] = Envia ao Telegram 0=Nao / 1=Sim
     aU16_AcaoRede[2][x] = Envia ao MqTT 0=Nao / 1=Sim
     aU16_AcaoRede[3][x] = Notifica Assitente 0=Nao / 1=Sim

     uint16_t aU16_AcaoRede1[vI8_aU16_AcaoRede][vU8_totPinos]
     uint16_t aU16_AcaoRede2[vI8_aU16_AcaoRede][vU8_totPinos]
     uint16_t aU16_AcaoRede3[vI8_aU16_AcaoRede][vU8_totPinos]

# Array de dados aS8_AcaoX (carregado da flash)
     Usado para cadastro de acoes, eventos quando uma porta(pino) e acionada

     aS8_Acao[Propriedade][Pino]
     aS8_Acao[0][x] = Classe da acao para o MqTT
     aS8_Acao[1][x] = Icone da acao para o MqTT

     String aS8_Acao1[vI8_aS8_Acao][vU8_totPinos]
     String aS8_Acao2[vI8_aS8_Acao][vU8_totPinos]
     String aS8_Acao3[vI8_aS8_Acao][vU8_totPinos]

# Array de dados aS_Preference (carregado da flash)
     Usado para cadastro de configurações, guarda informações de configurações gerais do sistema.

     aS_Preference[Propriedade][Valor]
     aS_Preference[0][0] = "wifi" = Nome do wifi(ssid) que o módulo deve usar.
     aS_Preference[0][1] = "12345678" = Senha do wifi que o módulo deve usar.
     aS_Preference[0][2] = "4" = Número de tentativas de conexões.
     aS_Preference[0][3] = "8080" = Porta de escuta do servidor web.
     aS_Preference[0][4] = "esp32modularx" = Hostname do módulo.
     aS_Preference[0][5] = "admin" = Usuário de acesso a interface web.
     aS_Preference[0][6] = "admin" = Senha de acesso a interface web.
     aS_Preference[0][7] = aS_Preference[0][4] + " Ponto de Acesso" = Nome do ponto de acesso(SSID) para primeira configuraçao.
     aS_Preference[0][8] = "senha12345678" = Senha do ponto de acesso para primeira configuração.
     aS_Preference[0][9] = "true" = Habilita modo AP(ponto de acesso) caso não consiga conectar no wifi.
     aS_Preference[0][10] = "pool.ntp.br" = Servidor NTP.
     aS_Preference[0][11] = "pool.ntp.org" = Servidor NTP.
     aS_Preference[0][12] = "<-03>3" = Fuso horário NTP.
     aS_Preference[0][13] = "Tomato" = Cor para status com alerta.
     aS_Preference[0][14] = "LightGreen" = Cor para status sem alerta.
     aS_Preference[0][15] = "false" = Executa rotinas para telegram.
     aS_Preference[0][16] = "" = Chave da API do telegram.
     aS_Preference[0][17] = "" = ID do chat do telegram.
     aS_Preference[0][18] = "" = Usuário do telegram.
     aS_Preference[0][19] = "65535" = Tempo de verificação da rotina do telegram.
     aS_Preference[0][20] = "false" = Executa rotinas do MQTT.
     aS_Preference[0][21] = "pubsub" = Tópico MQTT.
     aS_Preference[0][22] = "" = Servidor MQTT.
     aS_Preference[0][23] = "" = Usuário MQTT.
     aS_Preference[0][24] = "" = Senha MQTT.
     aS_Preference[0][25] = "65535" = Tempo de verificação das rotinas do MQTT.
     aS_Preference[0][26] = "65535" = Tempo de envio de descoberta do MQTT.
     aS_Preference[0][27] = "1833" = Porta de escuta do servidor MQTT.
     aS_Preference[0][28] = "false" = Executa rotinas dos assistentes.
     aS_Preference[0][29] = "65535" = Tempo de verificação das rotinas dos assistentes.
     aS_Preference[0][30] = "" = Nome das caixas de som do goolge assistente.
     aS_Preference[0][31] = "" = Nome das caixas de som da alexa assistente.
     aS_Preference[0][32] = "pt_br" = Linguagem dos assistentes.
     aS_Preference[0][33] = "" = Frase inicial de alerta para os assistentes.
     aS_Preference[0][34] = "" = Frase final de alerta para os assistentes.
     aS_Preference[0][35] = "false" = Executa inter módulos.
     aS_Preference[0][36] = "65535" = Tempo de handshake do inter módulos.
     aS_Preference[0][37] = "65535" = Tempo de verificação das rotinas dos inter módulos.
     aS_Preference[0][38] = "10" = Ciclo de handshake.
     aS_Preference[0][39] = "15" = Total de pinos (portas do ESP) !!!! ATENÇÃO !!!!.
     aS_Preference[0][40] = "7" = Número de colunas das tabelas na interface web.
     aS_Preference[0][41] = "120" = Tempo  de refresh da tela pincipal (página de status).
     aS_Preference[0][42] = "80" = Tempo de clock do ESP32 em Mhz para whactdog.
     aS_Preference[0][43] = "false" = Executa rotinas de whachdog.
     aS_Preference[0][44] = "300000000" = Tempo em microsegundos  (µs) de reset do watchdog .
     aS_Preference[0][45] = "12" = Quantidade de bits do processador (usado para pinos analógicos).
     aS_Preference[0][46] = "8" = Ciclos de amostra para pinos analógicos.
     aS_Preference[0][47] = "7" = Total de módulos para cadastro.
     aS_Preference[0][48] = "false" = Mostra status na página inicial.
     aS_Preference[0][49] = "false" = Mostra status inter módulos na página inicial.
     aS_Preference[0][50] = "1" = Quantidade de tasks de açãoes ativas.

