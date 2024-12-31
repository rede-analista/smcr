#include "include.h"
#include "globals.h"

/*========================================
Funcao para tratar manseagens recebidas pela serial
*/
void fV_handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        String message = String((char *)data).substring(0, len); // Converte os dados para string

        if (message.startsWith("SET_VAR ")) {
            int spaceIndex = message.indexOf(' ', 8);
//            if (spaceIndex > 0) {
//                String varName = message.substring(8, spaceIndex);
//                String value = message.substring(spaceIndex + 1);
//
//                if (setVariable(varName, value)) {
//                    fV_imprimeSerial(1,"Variável alterada e removida: " + varName + " = " + value);
//                } else {
//                    fV_imprimeSerial(1,"Nome da variável inválido: " + varName);
//                }
//            }
//        } else if (message.startsWith("GET_TYPE ")) {
//            int spaceIndex = message.indexOf(' ', 9);
//            if (spaceIndex > 0) {
//                String varName = message.substring(9, spaceIndex);
//                VarType type = getVariableType(varName);
//                
//                switch (type) {
//                    case VarType::STRING: fV_imprimeSerial(1,varName + " é do tipo STRING"); break;
//                    case VarType::UINT8: fV_imprimeSerial(1,varName + " é do tipo UINT8"); break;
//                    case VarType::UINT16: fV_imprimeSerial(1,varName + " é do tipo UINT16"); break;
//                    case VarType::UINT32: fV_imprimeSerial(1,varName + " é do tipo UINT32"); break;
//                    case VarType::UINT64: fV_imprimeSerial(1,varName + " é do tipo UINT64"); break;
//                    case VarType::INT16: fV_imprimeSerial(1,varName + " é do tipo INT16"); break;
//                    case VarType::BOOL: fV_imprimeSerial(1,varName + " é do tipo BOOL"); break;
//                    default: fV_imprimeSerial(1,varName + " tem tipo desconhecido"); break;
//                }
//            }
        } else if (message.startsWith("ALT_PINO(")) {
            // Extrair os parâmetros
            int startIdx = message.indexOf('(');
            int endIdx = message.indexOf(')');
            if (startIdx != -1 && endIdx != -1) {
                String parametros = message.substring(startIdx + 1, endIdx); // Extrai os parâmetros
                int prop, pino, valor;

                // Dividir os parâmetros pelo delimitador ','
                int firstComma = parametros.indexOf(',');
                int secondComma = parametros.indexOf(',', firstComma + 1);

                if (firstComma != -1 && secondComma != -1) {
                    prop = parametros.substring(0, firstComma).toInt();
                    pino = parametros.substring(firstComma + 1, secondComma).toInt();
                    valor = parametros.substring(secondComma + 1).toInt();

                    // Verificar limites de índices
                    if (prop >= 0 && prop < vI8_aU16_Pinos && pino >= 0 && pino < fU16_carregaConfigGeral(39, 15)) {
                        aU16_Pinos[prop][pino] = valor; // Alterar o valor no array
                        fV_imprimeSerial(1,"Array alterado: [" + String(prop) + "][" + String(pino) + "] = " + String(valor));
                    } else {
                        fV_imprimeSerial(1,"Erro: Indices fora dos limites!");
                    }
                } else {
                    fV_imprimeSerial(1,"Erro: Parâmetros inválidos!");
                }
            } else {
                fV_imprimeSerial(1,"Erro: Sintaxe inválida!");
            }
        } else if (message.startsWith("ALT_STATUS(")) {
            // Extrair os parâmetros
            int startIdx = message.indexOf('(');
            int endIdx = message.indexOf(')');
            if (startIdx != -1 && endIdx != -1) {
                String parametros = message.substring(startIdx + 1, endIdx); // Extrai os parâmetros
                int prop, pino, valor;

                // Dividir os parâmetros pelo delimitador ','
                int firstComma = parametros.indexOf(',');
                int secondComma = parametros.indexOf(',', firstComma + 1);

                if (firstComma != -1 && secondComma != -1) {
                    prop = parametros.substring(0, firstComma).toInt();
                    pino = parametros.substring(firstComma + 1, secondComma).toInt();
                    valor = parametros.substring(secondComma + 1).toInt();

                    // Verificar limites de índices
                    if (prop == 0 && pino >= 0 && pino < fU16_carregaConfigGeral(39, 15)) {
                        aU16_Pinos_Status[prop][pino] = valor; // Alterar o valor no array
                        fV_imprimeSerial(1,"Array alterado: [" + String(prop) + "][" + String(pino) + "] = " + String(valor));
                    } else {
                        fV_imprimeSerial(1,"Erro: Indices fora dos limites!");
                    }
                } else {
                    fV_imprimeSerial(1,"Erro: Parâmetros inválidos!");
                }
            } else {
                fV_imprimeSerial(1,"Erro: Sintaxe inválida!");
            }

        } else if (message.startsWith("ALT_ENVIO(")) {
            // Extrair os parâmetros
            int startIdx = message.indexOf('(');
            int endIdx = message.indexOf(')');
            if (startIdx != -1 && endIdx != -1) {
                String parametros = message.substring(startIdx + 1, endIdx); // Extrai os parâmetros
                int prop, pino, valor;

                // Dividir os parâmetros pelo delimitador ','
                int firstComma = parametros.indexOf(',');
                int secondComma = parametros.indexOf(',', firstComma + 1);

                if (firstComma != -1 && secondComma != -1) {
                    prop = parametros.substring(0, firstComma).toInt();
                    pino = parametros.substring(firstComma + 1, secondComma).toInt();
                    valor = parametros.substring(secondComma + 1).toInt();

                    // Verificar limites de índices
                    if (prop >= 0 && prop < aU32_Variaveis[8] && pino >= 0 && pino < fU16_carregaConfigGeral(47, 65535)) {
                        aI16_InterMod_CTRL_HandShake[prop][pino] = valor; // Alterar o valor no array
                        fV_imprimeSerial(1,"Array alterado: [" + String(prop) + "][" + String(pino) + "] = " + String(valor));
                    } else {
                        fV_imprimeSerial(1,"Erro: Indices fora dos limites!");
                    }
                } else {
                    fV_imprimeSerial(1,"Erro: Parâmetros inválidos!");
                }
            } else {
                fV_imprimeSerial(1,"Erro: Sintaxe inválida!");
            } 
        } else {
            fV_imprimeSerial(1,message); // Se não for um comando reconhecido, apenas imprime na Serial
        } 
    }
}

//========================================
void fV_checkSerialInput() {
    static unsigned long lastCheckTime = 0; // Armazena o último tempo em que a serial foi verificada
    unsigned long currentTime = millis();

    if (currentTime - lastCheckTime >= 1000) {
        if (Serial.available()) {
            String serialData = Serial.readString();//Until('\n');
            if (serialData.length() > 0) { 
                fV_sendSerialData(serialData);
            }
        }
        ws->cleanupClients();
        lastCheckTime = currentTime;
    }
}

//========================================
// Conjunto de funcoes
//========================================
//template<typename T>
//struct VariableSetter {
//    static void set(T& variable, const String& value);
//};
//
//// Especializações para cada tipo
//template<>
//struct VariableSetter<String> {
//    static void set(String& variable, const String& value) {
//        variable = value;
//    }
//};
//
//template<>
//struct VariableSetter<uint8_t> {
//    static void set(uint8_t& variable, const String& value) {
//        variable = static_cast<uint8_t>(value.toInt());
//    }
//};
//
//template<>
//struct VariableSetter<uint16_t> {
//    static void set(uint16_t& variable, const String& value) {
//        variable = static_cast<uint16_t>(value.toInt());
//    }
//};
//
//template<>
//struct VariableSetter<uint32_t> {
//    static void set(uint32_t& variable, const String& value) {
//        variable = static_cast<uint32_t>(value.toInt());
//    }
//};
//
//template<>
//struct VariableSetter<uint64_t> {
//    static void set(uint64_t& variable, const String& value) {
//        variable = static_cast<uint64_t>(value.toInt());
//    }
//};
//
//template<>
//struct VariableSetter<int16_t> {
//    static void set(int16_t& variable, const String& value) {
//        variable = static_cast<int16_t>(value.toInt());
//    }
//};
//
//template<>
//struct VariableSetter<bool> {
//    static void set(bool& variable, const String& value) {
//        variable = (value == "true");
//    }
//};
//
//template<typename T>
//void registerVariable(const String& name, T& variable) {
//    VarType type;
//
//    // Determinar o tipo
//    if (std::is_same<T, String>::value) {
//        type = VarType::STRING;
//    } else if (std::is_same<T, uint8_t>::value) {
//        type = VarType::UINT8;
//    } else if (std::is_same<T, uint16_t>::value) {
//        type = VarType::UINT16;
//    } else if (std::is_same<T, uint32_t>::value) {
//        type = VarType::UINT32;
//    } else if (std::is_same<T, uint64_t>::value) {
//        type = VarType::UINT64;
//    } else if (std::is_same<T, int16_t>::value) {
//        type = VarType::INT16;
//    } else if (std::is_same<T, bool>::value) {
//        type = VarType::BOOL;
//    }
//
//    variables[name] = Variable{
//        .setter = [&variable](String value) {
//            VariableSetter<T>::set(variable, value); // Usar a especialização para setar
//        },
//        .type = type
//    };
//}

//========================================
//VarType getVariableType(const String& varName) {
//    auto it = variables.find(varName);
//    if (it != variables.end()) {
//        return it->second.type;
//    }
//    return VarType::UNKNOWN; // Nome da variável inválido
//}

//========================================
//bool setVariable(const String& varName, const String& value) {
//    auto it = variables.find(varName);
//    if (it != variables.end()) {
//        it->second.setter(value);
//        variables.erase(varName);  // Remove a variável do mapa após a alteração
//        return true;
//    }
//    return false; // Nome da variável inválido
//}

//========================================
void fV_onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
      fV_sendSerialData("Conectado WebSocket Serial!");
  } else if (type == WS_EVT_DISCONNECT) {

  } else if (type == WS_EVT_DATA) {
      fV_handleWebSocketMessage(arg, data, len);
  }
}

/*========================================
Envia informações para serial web.
*/
void fV_sendSerialData(String message) {
  if (aB_Variaveis[5]) { //Se o servidor web estiver em execução.
    if (message.length() > 0) {
      ws->textAll(message);
    }
  }
}
