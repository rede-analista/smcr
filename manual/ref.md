# Retorno Serial da Função f_enviaModulo()
     Usada para enviar informações entre os módulos de status dos pinos e enviuo de handshake.
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
     Argumento 2 = Indice do Pino
     Argumento 3 = Status do Pino

# Arrays para controle de execução de rotinas (não são salvos).
/* -----------------------------------------------------------<br>
Controle o envio de menssagens entre os modulos ESP<br>
aU8_ControlMsgMod[Propriedade][Pino]<br>
aU8_ControlMsgMod[0][x] = Enviar Receptor Array 1 Acao<br>
aU8_ControlMsgMod[1][x] = Enviar Receptor Array 2 Acao<br>
aU8_ControlMsgMod[2][x] = Enviar Receptor Array 3 Acao<br>
*/<br>
uint8_t aU8_ControlMsgMod[vI8_aU8_ControlMsg][vU8_totPinos];<br>

/* -----------------------------------------------------------<br>
Controle o envio de menssagens para assistentes<br>
aU8_ControlMsgAss[Propriedade][Pino]<br>
aU8_ControlMsgAss[0][x] = Enviar Assistentes Array 1 Acao<br>
aU8_ControlMsgAss[1][x] = Enviar Assistentes Array 2 Acao<br>
aU8_ControlMsgAss[2][x] = Enviar Assistentes Array 3 Acao<br>
*/<br>
uint8_t aU8_ControlMsgAss[vI8_aU8_ControlMsg][vU8_totPinos];<br>

/* -----------------------------------------------------------<br>
Controle o envio de menssagens para telegram<br>
aU8_ControlMsgTelegram[Propriedade][Pino]<br>
aU8_ControlMsgTelegram[0][x] = Enviar Telegram Array 1 Acao<br>
aU8_ControlMsgTelegram[1][x] = Enviar Telegram Array 2 Acao<br>
aU8_ControlMsgTelegram[2][x] = Enviar Telegram Array 3 Acao<br>
/*<br>
uint8_t aU8_ControlMsgTelegram[vI8_aU8_ControlMsg][vU8_totPinos];<br>

/* -----------------------------------------------------------<br>
Controle o envio de menssagens para broker mqtt<br>
aU8_ControlMsgMqTT[0][x] = Enviar Telegram Array 1 Acao<br>
aU8_ControlMsgMqTT[1][x] = Enviar Telegram Array 2 Acao<br>
aU8_ControlMsgMqTT[2][x] = Enviar Telegram Array 3 Acao<br>
/*<br>
uint8_t aU8_ControlMsgMqTT[vI8_aU8_ControlMsg][vU8_totPinos];<br>

/* -----------------------------------------------------------<br>
Controle de acoes para mesmo pino destino (Grupo)<br>
aU16_ControlAcoesGroups[0][vU8_totPinos] = Pino (que vai sofrer a acao)<br>
aU16_ControlAcoesGroups[1][vU8_totPinos] = Referencia pinos de origem (que vão disparar a acao)<br>
/*<br>
uint16_t aU16_ControlAcoesGroups[vI8_ControlAcoesGroups][vU8_totPinos] = {};<br>

/* -----------------------------------------------------------<br>
Controle de alerta de handshake para inter modulos<br>
aU16_ControlHS[0][vU8_totPinos] = Controle do Tempo de Handshake<br>
aU16_ControlHS[1][vU8_totPinos] = Status handshake<br>
aU16_ControlHS[2][vU8_totPinos] = Controle de Resposta de Handshake<br>
/*<br>
uint16_t aU16_ControlHS[vI8_aU16_InterModHA][vU8_totPinos];<br>



# Arrays de dados em tempo de execução (foram carregados da flash)
/* -----------------------------------------------------------<br>
Usado para cadastro dos modulos (Inter Modulos)<br>
aS_InterMod[Propriedade][Modulo]<br>
aS_InterMod[0][x] = Nome Modulo<br>
aS_InterMod[1][x] = IP Modulo<br>
/*<br>
String aS_InterMod[vI8_aS_InterMod][vU8_totPinos];<br>

/* -----------------------------------------------------------<br>
Usado para cadastro dos pinos de handhsake e habilitar envio de handshake (Inter Modulos)<br>
aU8_InterMod[0][x] = Pino HandShake<br>
aU8_InterMod[1][x] = Envia HandShake<br>
*/<br>
uint8_t aU8_InterMod[vI8_aU8_InterMod][vU8_totPinos];<br>

/* -----------------------------------------------------------<br>
Usado para cadastro de porta (pinos fisicos)<br>
aU8_Pinos[Propriedade][Pino]<br>
aU8_Pinos[0][x] = Fisico - Mapeamento dos pinos fisicos<br>
aU8_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO / 254=REMOTO<br>
aU8_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0<br>
aU8_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO<br>
aU8_Pinos[4][x] = Status 0=LOW / 1=HIGH<br>
aU8_Pinos[5][x] = Retencao 0=NAO / 1=SIM<br>
aU8_Pinos[6][x] = Tempo Retencao 0 a 255<br>
/*<br>
uint8_t aU8_Pinos[vI8_aU8_Pinos][vU8_totPinos];<br>

/* -----------------------------------------------------------<br>
Usado para cadastro do nome(descricao) dos pinos<br>
aS8_Pinos[Propriedade][Pino]<br>
aS8_Pinos[0][x] = Nome/descricao<br>
*/<br>
String aS8_Pinos[vI8_aS8_Pinos][vU8_totPinos];<br>

  
