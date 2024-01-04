//========================================
String f_upTime() {

}

//========================================
void f_importarDoBackup() {
  Serial.print("Importando configuração do backup JSON ");
  File jsonFile = SPIFFS.open("/temp.json", FILE_READ);

  if (!jsonFile) {
    Serial.println("Erro ao abrir o arquivo JSON para leitura");
    return;
  }

  // Tamanho do arquivo
  size_t size = jsonFile.size();
  Serial.print("Tamanho arquivo: ");
  Serial.println(jsonFile.size());

  // Aloca um buffer para o conteúdo do arquivo
  std::unique_ptr<char[]> buf(new char[size]);

  // Lê o conteúdo do arquivo para o buffer
  jsonFile.readBytes(buf.get(), size);
  
  // Fecha o arquivo
  jsonFile.close();

  //Serial.println("Conteudo do buffer: ");
  //Serial.println(buf.get());
  //Serial.println("FIM do conteudo do buffer");

  // Criar um objeto JSON para armazenar os valores
  DynamicJsonDocument doc(ESP.getMaxAllocHeap());
  //StaticJsonDocument<4096> doc;
  //DynamicJsonDocument doc(6000);
  Serial.print("Tamanho maximo do DOC: ");
  Serial.println(doc.capacity());


  Serial.println("Memória livre antes da desserialização: " + String(ESP.getFreeHeap()));
  // Deserializar o JSON a partir da string
  Serial.println("Deserealizando JSON");
  try {
    deserializeJson(doc, buf.get());
  } catch (const std::exception& e) {
    Serial.println("Erro durante a desserialização JSON: " + String(e.what()));
    // Lide com o erro aqui, se necessário
  }
  Serial.println("Memória livre após a desserialização: " + String(ESP.getFreeHeap()));

  // Atribuir valores às variáveis
  vS_nomeWifi = doc["nome_wifi"].as<String>();
  vS_senhaWifi = doc["senha_wifi"].as<String>();
  vU8_tentativaConexoes = doc["tenta_conect"];
  vU16_portaWeb = doc["porta_srvweb"];
  vS_nomeDispositivo = doc["nome_disp"].as<String>();
  vS_nomeAP_Wifi = doc["nome_wifi_ap"].as<String>();
  vS_senhaAP_Wifi = doc["senha_wifi_ap"].as<String>();
  vB_modoAP = doc["modo_wifi_ap"];
  vS_ntpServer1 = doc["ntp_srv1"].as<String>();
  vS_ntpServer2 = doc["ntp_srv2"].as<String>();
  vS_timeZone = doc["ntp_timez"].as<String>();
  vB_exec_Telegram = doc["exe_teleg"];
  vS_api_Telegram = doc["api_teleg"].as<String>();
  vS_chat_Telegram = doc["chat_teleg"].as<String>();
  vS_user_Telegram = doc["boot_teleg"].as<String>();
  vU16_bot_MTBS = doc["time_teleg"];
  vB_exec_MqTT = doc["exe_mqtt"];
  vS_mqttTopico = doc["top_mqtt"].as<String>();
  vS_mqttServer = doc["srv_mqtt"].as<String>();
  vS_mqttUser = doc["usr_mqtt"].as<String>();
  vS_mqttSenha = doc["pss_mqtt"].as<String>();
  vU16_mqttPorta = doc["porta_mqtt"];
  vU16_mqtt_MTBS = doc["time_mqtt"];
  vU32_mqtt_disc_MTBS = doc["disc_mqtt"];
  vB_exec_Assistente = doc["exe_ass"];
  vS_assNomeGoogle = doc["ass_google"].as<String>();
  vS_assNomeAlexa = doc["ass_alexa"].as<String>();
  vS_assLinguagem = doc["ass_ling"].as<String>();
  vU16_ass_MTBS = doc["ass_time"];
  vS_ass_Alerta = doc["ass_alerta"].as<String>();
  vS_ass_Normal = doc["ass_normal"].as<String>();
  vB_exec_Modulos = doc["exe_mod"];
  vU16_modulos_MTBS = doc["time_mod"];
  //vU16_portaWebModulos = doc["porta_mod"];
  vI_cicloHandshake = doc["ciclo_mod"];
  //vU8_totPinos = doc["qnt_pinos"];

 // Atribuir valores aos arrays
  for (int i = 0; i < vI8_aS_InterMod; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aS_InterMod[i][j] = doc["aS_InterMod"][i][j].as<String>();
    }
  }

  for (int i = 0; i < vI8_aU16_InterMod; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU16_InterMod[i][j] = doc["aU16_InterMod"][i][j];
    }
  }

  for (int i = 0; i < vI8_aU8_Pinos; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU8_Pinos[i][j] = doc["aU8_Pinos"][i][j];
    }
  }

  for (int i = 0; i < vI8_aS8_Pinos; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aS8_Pinos[i][j] = doc["aS8_Pinos"][i][j].as<String>();
    }
  }

  for (int i = 0; i < vI8_aU16_Acao; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU16_Acao1[i][j] = doc["aU16_Acao1"][i][j].as<uint16_t>();
    }
  }

  for (int i = 0; i < vI8_aU16_AcaoRede; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU8_AcaoRede1[i][j] = doc["aU8_AcaoRede1"][i][j].as<uint16_t>();
    }
  }

  for (int i = 0; i < vI8_aS8_Acao; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aS8_Acao1[i][j] = doc["aS8_Acao1"][i][j].as<String>();
    }
  }

  for (int i = 0; i < vI8_aU16_Acao; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU16_Acao2[i][j] = doc["aU16_Acao2"][i][j].as<uint16_t>();
    }
  }

  for (int i = 0; i < vI8_aU16_AcaoRede; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU8_AcaoRede2[i][j] = doc["aU8_AcaoRede2"][i][j].as<uint16_t>();
    }
  }

  for (int i = 0; i < vI8_aS8_Acao; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aS8_Acao2[i][j] = doc["aS8_Acao2"][i][j].as<String>();
    }
  }

  for (int i = 0; i < vI8_aU16_Acao; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU16_Acao3[i][j] = doc["aU16_Acao3"][i][j].as<uint16_t>();
    }
  }

  for (int i = 0; i < vI8_aU16_AcaoRede; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aU8_AcaoRede3[i][j] = doc["aU8_AcaoRede3"][i][j].as<uint16_t>();
    }
  }

  for (int i = 0; i < vI8_aS8_Acao; i++) {
    for (int j = 0; j < vU8_totPinos; j++) {
      aS8_Acao3[i][j] = doc["aS8_Acao3"][i][j].as<String>();
    }
  }
  //doc.clear();
  //delete &doc;
}

//========================================
String f_exportarParaBackup() {
  // Criar um objeto JSON para armazenar as variáveis
  DynamicJsonDocument doc(JSON_OBJECT_SIZE(1) +
                          JSON_OBJECT_SIZE(35) +  // número de variáveis não array
                          vI8_aS_InterMod * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aU16_InterMod * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aU8_Pinos * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aS8_Pinos * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aU16_Acao * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aU16_AcaoRede * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aS8_Acao * JSON_ARRAY_SIZE(vU8_totPinos) + 
                          vI8_aU16_Acao * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aU16_AcaoRede * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aS8_Acao * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aU16_Acao * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aU16_AcaoRede * JSON_ARRAY_SIZE(vU8_totPinos) +
                          vI8_aS8_Acao * JSON_ARRAY_SIZE(vU8_totPinos));                          
  
  // Criar um objeto JSON com a capacidade necessária
  DynamicJsonDocument docExport(doc.capacity());
  Serial.print("Criando JSON com tamanho: ");
  Serial.println(doc.capacity());

  JsonObject root = docExport.to<JsonObject>();

  root["nome_wifi"] = vS_nomeWifi;
  root["senha_wifi"] = vS_senhaWifi;
  root["tenta_conect"] = vU8_tentativaConexoes;
  root["porta_srvweb"] = vU16_portaWeb;
  root["nome_disp"] = vS_nomeDispositivo;
  root["nome_wifi_ap"] = vS_nomeAP_Wifi;
  root["senha_wifi_ap"] = vS_senhaAP_Wifi;
  root["modo_wifi_ap"] = vB_modoAP;
  root["ntp_srv1"] = vS_ntpServer1;
  root["ntp_srv2"] = vS_ntpServer2;
  root["ntp_timez"] = vS_timeZone;
  root["exe_teleg"] = vB_exec_Telegram;
  root["api_teleg"] = vS_api_Telegram;
  root["chat_teleg"] = vS_chat_Telegram;
  root["boot_teleg"] = vS_user_Telegram;
  root["time_teleg"] = vU16_bot_MTBS;
  root["exe_mqtt"] = vB_exec_MqTT;
  root["top_mqtt"] = vS_mqttTopico;
  root["srv_mqtt"] = vS_mqttServer;
  root["usr_mqtt"] = vS_mqttUser;
  root["pss_mqtt"] = vS_mqttSenha;
  root["porta_mqtt"] = vU16_mqttPorta;
  root["time_mqtt"] = vU16_mqtt_MTBS;
  root["disc_mqtt"] = vU32_mqtt_disc_MTBS;
  root["exe_ass"] = vB_exec_Assistente;
  root["ass_google"] = vS_assNomeGoogle;
  root["ass_alexa"] = vS_assNomeAlexa;
  root["ass_ling"] = vS_assLinguagem;
  root["ass_time"] = vU16_ass_MTBS;
  root["ass_alerta"] = vS_ass_Alerta;
  root["ass_normal"] = vS_ass_Normal;
  root["exe_mod"] = vB_exec_Modulos;
  root["time_mod"] = vU16_modulos_MTBS;
  //root["porta_mod"] = vU16_portaWebModulos;
  root["ciclo_mod"] = vI_cicloHandshake;
  root["qnt_pinos"] = vU8_totPinos;

  // Adicionar arrays ao objeto JSON
  serializeArray(aS_InterMod, "aS_InterMod", vI8_aS_InterMod, vU8_totPinos, docExport);
  serializeArray(aU16_InterMod, "aU16_InterMod", vI8_aU16_InterMod, vU8_totPinos, docExport);
  serializeArray(aU8_Pinos, "aU8_Pinos", vI8_aU8_Pinos, vU8_totPinos, docExport);
  serializeArray(aS8_Pinos, "aS8_Pinos", vI8_aS8_Pinos, vU8_totPinos, docExport);
  serializeArray(aU16_Acao1, "aU16_Acao1", vI8_aU16_Acao, vU8_totPinos, docExport);
  serializeArray(aU8_AcaoRede1, "aU8_AcaoRede1", vI8_aU16_AcaoRede, vU8_totPinos, docExport);
  serializeArray(aS8_Acao1, "aS8_Acao1", vI8_aS8_Acao, vU8_totPinos, docExport);
  serializeArray(aU16_Acao2, "aU16_Acao2", vI8_aU16_Acao, vU8_totPinos, docExport);
  serializeArray(aU8_AcaoRede2, "aU8_AcaoRede2", vI8_aU16_AcaoRede, vU8_totPinos, docExport);
  serializeArray(aS8_Acao2, "aS8_Acao2", vI8_aS8_Acao, vU8_totPinos, docExport);
  serializeArray(aU16_Acao3, "aU16_Acao3", vI8_aU16_Acao, vU8_totPinos, docExport);
  serializeArray(aU8_AcaoRede3, "aU8_AcaoRede3", vI8_aU16_AcaoRede, vU8_totPinos, docExport);
  serializeArray(aS8_Acao3, "aS8_Acao3", vI8_aS8_Acao, vU8_totPinos, docExport);


  // Serializar o JSON para uma string
  String jsonString;
  serializeJson(docExport, jsonString);
  return jsonString;
}

//========================================
// Função principal para serializar arrays no objeto JSON
template <typename T>
//JsonArray serializeArray(T array[], uint8_t rows, uint8_t cols, JsonDocument& doc) {
JsonArray serializeArray(T array[], const char* key, uint8_t rows, uint8_t cols, JsonDocument& doc) {  
  //JsonArray jsonArray = doc.to<JsonArray>();
  JsonArray jsonArray = doc.createNestedArray(key);

  for (uint8_t i = 0; i < rows; i++) {
    //JsonArray row = doc.createNestedArray();
    JsonArray row = jsonArray.createNestedArray();
    for (uint8_t j = 0; j < cols; j++) {
      row.add(array[i][j]);
    }
    //jsonArray.add(row);
  }

  return jsonArray;
}

// Versão especializada para arrays de String
template <size_t Size>
JsonArray serializeArray(String (&array)[Size][vU8_totPinos], uint8_t rows, JsonDocument& doc) {
  return serializeArray(array, rows, vU8_totPinos, doc);
}

// Versão especializada para arrays de uint8_t
template <size_t Size>
JsonArray serializeArray(uint8_t (&array)[Size][vU8_totPinos], uint8_t rows, JsonDocument& doc) {
  return serializeArray(array, rows, vU8_totPinos, doc);
}

// Versão especializada para arrays de uint16_t
template <size_t Size>
JsonArray serializeArray(uint16_t (&array)[Size][vU8_totPinos], uint8_t rows, JsonDocument& doc) {
  return serializeArray(array, rows, vU8_totPinos, doc);
}



//========================================
uint8_t f_retornaIndiceHS(String modulo) {
  uint8_t resultado = 0;
  for (uint8_t x=0; x<vU8_totPinos; x++) {
    if (aS_InterMod[0][x] == modulo) {
      resultado = x;
    }
  }
  return resultado;
}

//========================================
bool f_retornaStatusGrupoAcao(String pinos, uint8_t status) {
  bool resultado = false;
  String xpin = "";
  int xstat = 0;
  for (int x=0; x<=pinos.length();x++) {
    if (pinos[x] == 44) {
      xstat += aU8_Pinos_Status[0][f_retornaIndicePino(xpin.toInt())];
      xpin = "";
    } else {
      xpin += pinos[x];
    }
  }
  xstat += aU8_Pinos_Status[0][f_retornaIndicePino(xpin.toInt())];
  if (xstat == 0 && status) {
    resultado = true;
  } else if (xstat == 1 && status) {
    resultado = true;
  } else if (xstat > 1 && status) {
    resultado = false;    
  } else if (xstat > 1 && !status) {
    resultado = false;
  } else if (xstat == 1 && !status) {
    resultado = false;
  } else if (xstat == 0 && !status) {
    resultado = true;
  } else {
    resultado = false;
  }
  return resultado;
}

//========================================
String f_retornaGrupoAcao(uint8_t pino) {
  String resultado = "";
  int cont = 0;
  for (uint8_t x=1; x<vI8_ControlAcoesGroups; x++){
    if (aU16_ControlAcoesGroups[x][f_retornaIndicePino(pino)] >0 ) {
      resultado += String(aU16_ControlAcoesGroups[x][f_retornaIndicePino(pino)]);
      resultado += ",";
      cont++;
    }
  }
  if (cont < 2) {
    resultado = "";
  } else {
    resultado = resultado.substring(0,resultado.length()-1);
  }
  return resultado;
}

//========================================
uint8_t f_retornaIndicePino(uint8_t pino) {
  uint8_t resultado = 255;
  for (uint8_t x=0; x<vU8_totPinos; x++) {
    if (aU8_Pinos[0][x] == pino) {
      resultado = x;
    }
  }
  return resultado;
}

//========================================
void f_iniciaInterModulos() {
  Serial.print("Iniciando configuracao inter modulos... ");
  CONFIG_FLASH.begin("confiGeral", true);
  String aSBuffer[vI8_aS_InterMod][vU8_totPinos];
  uint16_t aU16Buffer[vI8_aU16_InterMod][vU8_totPinos] = {};  

  CONFIG_FLASH.getBytes("paS_InterMod", aSBuffer, CONFIG_FLASH.getBytesLength("paS_InterMod"));
  CONFIG_FLASH.getBytes("paU16_InterMod", aU16Buffer, CONFIG_FLASH.getBytesLength("paU16_InterMod"));
  CONFIG_FLASH.end();

  for (uint8_t x=0; x<vI8_aS_InterMod; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aS_InterMod[x][y] = aSBuffer[x][y];
    }
  }
  for (uint8_t x=0; x<vI8_aU16_InterMod; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU16_InterMod[x][y] = aU16Buffer[x][y];
    }
  }
  for (uint8_t y=0; y<vU8_totPinos; y++) {
    aU16_ControlHS[0][y] = vI_cicloHandshake;
  }  
  Serial.println("OK");
}

//========================================
void f_recebeDados() {
/*
 Argumento 0 = Nome do Dispositivo
 Argumento 1 = Acao
 Argumento 2 = Indice do Pino
 Argumento 3 = Status do Pino
*/
  vS_uri = SERVIDOR_WEB.uri();
  if (SERVIDOR_WEB.args() == 4) {

    if (ULTIMOS_GET_RECEBIDOS.length() > 260) {
      ULTIMOS_GET_RECEBIDOS = "";
    }
    ULTIMOS_GET_RECEBIDOS += vS_uri + "?" + SERVIDOR_WEB.argName(0) + "=" + SERVIDOR_WEB.arg(0) + "&" + SERVIDOR_WEB.argName(1) + "=" + SERVIDOR_WEB.arg(1) + "&" + SERVIDOR_WEB.argName(2) + "=" + SERVIDOR_WEB.arg(2) + "&" + SERVIDOR_WEB.argName(3) + "=" + SERVIDOR_WEB.arg(3);
    ULTIMOS_GET_RECEBIDOS += "<br><br>";
    String validacao = "_SEM_DADOS_";
    if (f_retornaModulo(SERVIDOR_WEB.arg(0)) > 0) {
      Serial.println("Recebido dados da placa " + SERVIDOR_WEB.arg(0));
      switch (SERVIDOR_WEB.arg(1).toInt()) {
        case 0: // Parametro acao = 0(Nenhuma)
          aU16_ControlHS[0][f_retornaIndiceHS(SERVIDOR_WEB.arg(0))] = vI_cicloHandshake;
          aU8_Pinos_Status[0][f_retornaIndicePino(SERVIDOR_WEB.arg(2).toInt())] = SERVIDOR_WEB.arg(3).toInt();
          validacao = "OK_DADO_RECEBIDO";
          break;
        case 255: // Parametro acao = 255(sincronismo)
          aU16_ControlHS[0][f_retornaIndiceHS(SERVIDOR_WEB.arg(0))] = vI_cicloHandshake;
          aU16_ControlHS[1][f_retornaIndiceHS(SERVIDOR_WEB.arg(0))] = SERVIDOR_WEB.arg(3).toInt();
          aU8_Pinos_Status[0][f_retornaIndicePino(SERVIDOR_WEB.arg(2).toInt())] = aU16_ControlHS[1][f_retornaIndiceHS(SERVIDOR_WEB.arg(0))];
          validacao = "OK_DADO_RECEBIDO";
          break;
        default:
          aU16_ControlHS[0][f_retornaIndiceHS(SERVIDOR_WEB.arg(0))] = vI_cicloHandshake;
          aU8_Pinos_Status[0][f_retornaIndicePino(SERVIDOR_WEB.arg(2).toInt())] = SERVIDOR_WEB.arg(3).toInt();
          validacao = "OK_DADO_RECEBIDO";
          break;
      }
      Serial.println("Acao/Indice/Status " + SERVIDOR_WEB.arg(1) + " " + SERVIDOR_WEB.arg(2) + " " + SERVIDOR_WEB.arg(3));
      SERVIDOR_WEB.send(200, "text/plain", validacao);
    } else {
      Serial.println("Rejeite dados da placa " + SERVIDOR_WEB.arg(0));
      Serial.println("Acao/Indice/Status " + SERVIDOR_WEB.arg(1) + " " + SERVIDOR_WEB.arg(2) + " " + SERVIDOR_WEB.arg(3));
      SERVIDOR_WEB.send(401, "text/plain", "ERRO - PLACA NAO CADASTRADA\n");
    }
  } else {
    Serial.println("Erro dados da placa " + SERVIDOR_WEB.arg(0));
    Serial.println("Acao/Indice/Status " + SERVIDOR_WEB.arg(1) + " " + SERVIDOR_WEB.arg(2) + " " + SERVIDOR_WEB.arg(3));
    SERVIDOR_WEB.send(400, "text/plain", "ERRO - PARAMETROS INVALIDOS\n");
  }
}

//========================================
int f_retornaIndiceModulo(uint8_t modulo) {
  int resultado = 0;
  if (modulo > 0) {
    for (int x=0; x<vU8_totPinos; x++) {
      if (modulo == aU16_InterMod[0][x]) {
        resultado = x;
        break;
      }
    }
  }
  return resultado;
}

//========================================
String f_retornaIpModulo(uint8_t modulo) {
  String resultado = "";
  if (modulo > 0) {
    for (int x=0; x<vU8_totPinos; x++) {
      if (modulo == aU16_InterMod[0][x]) {
        resultado = aS_InterMod[1][x];
        break;
      }
    }
  }
  return resultado;
}

//========================================
int f_retornaModulo(String modulo) {
  int resultado = 256;
  if (modulo.length() > 0) {
    for (int x=0; x<vU8_totPinos; x++) {
      if (modulo == aS_InterMod[0][x]) {
        resultado = x;
        break;
      }
    }
  }
  return resultado;
}

//========================================
void f_configuraModulos(bool force) {
  if (!vB_exec_Modulos) {
    f_carregaConfi("MODULOS",force);
    f_iniciaInterModulos();
  } else if (force) {
    vB_exec_Modulos = true;
  }
}

//========================================
void f_checkAcoesModulos() {
  uint64_t agora = millis();
  if ((agora - check_acoes_mod_lasttime) > vU16_modulos_MTBS) {
    for (uint8_t x=0; x<vU8_totPinos; x++) {
      if ((aU8_AcaoRede1[0][x] >0 ) && aU8_Pinos_Status[0][x] && !aU8_ControlMsgMod[0][x]) {
        if (f_enviaModulo(aU8_AcaoRede1[0][x],String(aU16_Acao1[2][x]), String(aU16_Acao1[5][x]), String(aU8_Pinos_Status[0][x])) == 200) {
        //if (f_enviaModulo(aU8_AcaoRede1[0][x],String(aU16_Acao1[2][x]), String(aU8_Pinos[0][x]), String(aU8_Pinos_Status[0][x])) == 200) {  
          aU8_ControlMsgMod[0][x] = 1;
        }
      } else if ((aU8_AcaoRede1[0][x] >0 ) && !aU8_Pinos_Status[0][x] && aU8_ControlMsgMod[0][x]){
        if (f_enviaModulo(aU8_AcaoRede1[0][x],String(aU16_Acao1[2][x]), String(aU16_Acao1[5][x]), String(aU8_Pinos_Status[0][x])) == 200) {
        //if (f_enviaModulo(aU8_AcaoRede1[0][x],String(aU16_Acao1[2][x]), String(aU8_Pinos[0][x]), String(aU8_Pinos_Status[0][x])) == 200) {  
          aU8_ControlMsgMod[0][x] = 0;
        }
      }
      if ((aU8_AcaoRede2[0][x] >0 ) && aU8_Pinos_Status[0][x] && !aU8_ControlMsgMod[1][x]) {
        if (f_enviaModulo(aU8_AcaoRede2[0][x],String(aU16_Acao2[2][x]), String(aU16_Acao1[5][x]), String(aU8_Pinos_Status[0][x])) == 200) {
          aU8_ControlMsgMod[1][x] = 1;
        }
      } else if ((aU8_AcaoRede2[0][x] >0 ) && !aU8_Pinos_Status[0][x] && aU8_ControlMsgMod[1][x]){
        if (f_enviaModulo(aU8_AcaoRede2[0][x],String(aU16_Acao2[2][x]), String(aU16_Acao1[5][x]), String(aU8_Pinos_Status[0][x])) == 200) {
          aU8_ControlMsgMod[1][x] = 0;
        }
      }
      if ((aU8_AcaoRede3[0][x] >0 ) && aU8_Pinos_Status[0][x] && !aU8_ControlMsgMod[2][x]) {
        if (f_enviaModulo(aU8_AcaoRede3[0][x],String(aU16_Acao3[2][x]), String(aU16_Acao1[5][x]), String(aU8_Pinos_Status[0][x])) == 200) {
          aU8_ControlMsgMod[2][x] = 1;
        }
      } else if ((aU8_AcaoRede3[0][x] >0 ) && !aU8_Pinos_Status[0][x] && aU8_ControlMsgMod[2][x]){
        if (f_enviaModulo(aU8_AcaoRede3[0][x],String(aU16_Acao3[2][x]), String(aU16_Acao1[5][x]), String(aU8_Pinos_Status[0][x])) == 200) {
          aU8_ControlMsgMod[2][x] = 0;
        }
      }
    }
    check_acoes_mod_lasttime = agora;
    f_checkHandShake();
  }
}

//========================================
void f_checkHandShake() {
/* -----------------------------------------------------------
Controle de alerta de handshake para inter modulos
aU16_ControlHS[0][vU8_totPinos] = Controle tempo
aU16_ControlHS[1][vU8_totPinos] = Status handshake
aU16_ControlHS[2][vU8_totPinos] = Controle de Resposta HS
/* -----------------------------------------------------------
*/
  for (uint8_t y=0; y<vU8_totPinos; y++) {
    if (aU16_ControlHS[0][y] < 1) {
      aU16_ControlHS[1][y] = 1;
    } else {
      aU16_ControlHS[0][y]--;
    }
    if (aU16_InterMod[1][y] > 0) {
      if (aU16_ControlHS[0][y] < 2 && aU16_InterMod[1][y] > 0) { 
        //Serial.print("SEND HS Modulo:");
        //Serial.print(aS_InterMod[0][y]);
        //Serial.print(" IP:");
        //Serial.print(f_retornaIpModulo(aU16_InterMod[0][y]));
        //Serial.print(" Pino:");
        //Serial.print(aU16_InterMod[0][y]);
        //Serial.print(" da Origem Pino ID:");
        //Serial.print(f_retornaIndicePino(aU16_InterMod[0][f_retornaIndiceHS(vS_nomeDispositivo)]));
        //Serial.print(" Status:");
        //Serial.println(aU16_ControlHS[1][y]);        
        if (f_enviaModulo(aU16_InterMod[0][y],"255", String(aU16_InterMod[0][f_retornaIndiceHS(vS_nomeDispositivo)]), "0") == 200) {
          aU16_ControlHS[0][y] = vI_cicloHandshake;
          aU16_ControlHS[1][y] = 0;
          aU16_ControlHS[0][f_retornaModulo(vS_nomeDispositivo)] = vI_cicloHandshake;
          aU16_ControlHS[1][f_retornaModulo(vS_nomeDispositivo)] = 0;
        }
      }
    }
    aU8_Pinos_Status[0][f_retornaIndicePino(aU16_InterMod[0][y])] = aU16_ControlHS[1][y];
  }
}

//========================================
bool f_checkAcaoCadastrada() {
  uint64_t ctrlacao = 0;
  for (int x=0; x<vU8_totPinos; x++) {
    ctrlacao += aU8_AcaoRede1[0][x];
    ctrlacao += aU8_AcaoRede2[0][x];
    ctrlacao += aU8_AcaoRede3[0][x];
  }
  if (ctrlacao > 0) {
    return true;
  } else {
    return false;
  }
}

//========================================
int f_enviaModulo(uint8_t idmodulo, String acao, String pino, String valor){
  vI_httpResponseCode = 0;
  int resposta =  504;
  if (WiFi.status() != WL_CONNECTED) {
    f_configuraWIFI();
  } else {
    if (aU16_InterMod[1][f_retornaIndiceModulo(idmodulo)] > 0) {
      GET_SERVIDOR = "http://" + f_retornaIpModulo(idmodulo) + ":" + aU16_InterMod[1][f_retornaIndiceModulo(idmodulo)] + "/dados?pl=" + vS_nomeDispositivo + "&ac=" + acao + "&pn=" + pino + "&vl=" + valor; //aS_InterMod[1][idmodulo]
    } else {
      GET_SERVIDOR = "http://" + f_retornaIpModulo(idmodulo) + ":" + vU16_portaWeb + "/dados?pl=" + vS_nomeDispositivo + "&ac=" + acao + "&pn=" + pino + "&vl=" + valor; //aS_InterMod[1][idmodulo]
    }
    
    if (ULTIMOS_GET_SERVIDOR.length() > 260) {
      ULTIMOS_GET_SERVIDOR = "";
    }
    ULTIMOS_GET_SERVIDOR += GET_SERVIDOR;
    ULTIMOS_GET_SERVIDOR += "<br><br>";    
    if (!CLIENTE_WEB.connected()) {
      CLIENTE_WEB.setTimeout(vU16_modulos_MTBS);
      CLIENTE_WEB.setConnectTimeout(vU16_modulos_MTBS);
      CLIENTE_WEB.setReuse(true);
      CLIENTE_WEB.begin(GET_SERVIDOR.c_str());
    } else {
      CLIENTE_WEB.setURL(GET_SERVIDOR.c_str());
    }
    vI_httpResponseCode = CLIENTE_WEB.GET();
    String payload = CLIENTE_WEB.getString();
    vS_payload = payload;
    CLIENTE_WEB.end();
    if (vI_httpResponseCode == 200) {
      if (vS_payload == "OK_DADO_RECEBIDO") {
        resposta = 200;
        vU8_ultimoModEnviado = idmodulo;
        aU16_ControlHS[0][f_retornaIndiceModulo(idmodulo)] = vI_cicloHandshake;
        aU16_ControlHS[1][f_retornaIndiceModulo(idmodulo)] == 0;
      }
    }
    Serial.println("\nEnviado: "+GET_SERVIDOR);
    Serial.println("HTTP Response code: " + String(vI_httpResponseCode));
    Serial.println(payload);    
  }
  return resposta;
}

//========================================
bool f_checkAcoesAssistentes() {
  uint64_t agora = millis();
  bool resultado = true;
  // Inicio/Fim + Acao + sensor origem + sensor destino
  if ((agora - check_acoes_ass_lasttime) > vU16_ass_MTBS) {
    for (uint8_t x=0; x<vU8_totPinos; x++) {
      if (aU8_AcaoRede1[2][x] && aU8_Pinos_Status[0][x] && !aU8_ControlMsgAss[0][x]) {
        resultado = f_enviaAssistentes((vS_ass_Alerta+" "+f_traduzAcoesAss(aU16_Acao1[2][x])+" do sensor: "+f_pegaNomePino(aU16_Acao1[0][x])+" para o sensor: "+f_pegaNomePino(aU16_Acao1[1][x])+"."));
        aU8_ControlMsgAss[0][x] = 1;
      } else if(aU8_AcaoRede1[2][x] && !aU8_Pinos_Status[0][x] && aU8_ControlMsgAss[0][x]){
        resultado = f_enviaAssistentes((vS_ass_Normal+" "+f_traduzAcoesAss(aU16_Acao1[2][x])+" do sensor: "+f_pegaNomePino(aU16_Acao1[0][x])+" para o sensor: "+f_pegaNomePino(aU16_Acao1[1][x])+"."));
        aU8_ControlMsgAss[0][x] = 0;
      }
      if (aU8_AcaoRede2[2][x] && aU8_Pinos_Status[0][x] && !aU8_ControlMsgAss[1][x]) {
        resultado = f_enviaAssistentes(vS_ass_Alerta+" "+f_traduzAcoesAss(aU16_Acao2[2][x])+" do sensor : "+f_pegaNomePino(aU16_Acao2[0][x])+" para o sensor: "+f_pegaNomePino(aU16_Acao2[1][x])+".");
        aU8_ControlMsgAss[1][x] = 1;
      } else if(aU8_AcaoRede2[2][x] && !aU8_Pinos_Status[0][x] && aU8_ControlMsgAss[1][x]){
        resultado = f_enviaAssistentes(vS_ass_Normal+" "+f_traduzAcoesAss(aU16_Acao2[2][x])+" do sensor : "+f_pegaNomePino(aU16_Acao2[0][x])+" para o sensor: "+f_pegaNomePino(aU16_Acao2[1][x])+".");
        aU8_ControlMsgAss[1][x] = 0;
      }
      if (aU8_AcaoRede3[2][x] && aU8_Pinos_Status[0][x] && !aU8_ControlMsgAss[2][x]) {
        resultado = f_enviaAssistentes(vS_ass_Alerta+" "+f_traduzAcoesAss(aU16_Acao3[2][x])+" do sensor : "+f_pegaNomePino(aU16_Acao3[0][x])+" para o sensor: "+f_pegaNomePino(aU16_Acao3[1][x])+".");
        aU8_ControlMsgAss[2][x] = 1;
      } else if(aU8_AcaoRede3[2][x] && !aU8_Pinos_Status[0][x] && aU8_ControlMsgAss[2][x]){
        resultado = f_enviaAssistentes(vS_ass_Normal+" "+f_traduzAcoesAss(aU16_Acao3[2][x])+" do sensor : "+f_pegaNomePino(aU16_Acao3[0][x])+" para o sensor: "+f_pegaNomePino(aU16_Acao3[1][x])+".");
        aU8_ControlMsgAss[2][x] = 0;
      }     
    }
    check_acoes_ass_lasttime = agora;
  }
  return resultado;
}

//========================================
bool f_enviaAssistentes(String msg) {
  bool resultado = false;
  if (WiFi.status() != WL_CONNECTED) {
    f_configuraWIFI();
  } else {
    resultado =  CLIENT_ASS_GOOGLE.notify(msg.c_str());
  }
  return resultado;
}

//========================================
String f_pegaNomePino(uint16_t pino) {
  String resultado = "desconhecido";
  for (uint8_t x=0; x<vU8_totPinos; x++) {
    if (pino == aU8_Pinos[0][x]){
      resultado = aS8_Pinos[0][x];
      break;
    }
  }
  return resultado;
}

//========================================
String f_traduzAcoesAss(uint16_t cod) {
  String resultado = "NULO";
  switch (cod) {
    case 0:
      resultado = "NENHUMA";
      break;
    case 1:
      resultado = "LIGA";
      break;
    case 2:
      resultado = "LIGA_DELAY";
      break;
    case 3:
      resultado = "PISCA";
      break;
    case 4:
      resultado = "PULSO";
      break;
    case 5:
      resultado = "PULSO_DELAY";
      break;
    case 254:
      resultado = "STATUS_REMOTO";
      break;      
  }
  return resultado;
}

//========================================
void f_rebootaESP(uint8_t parametro) {
  ESP.restart();
}

//========================================
void f_callbackNotificaAlexa(uint8_t parametro) {
  Serial.println("Execucao de f_callbackNotificaAlexa(uint8_t parametro)");
  Serial.println(parametro);
  Serial.println("Fim de Execucao de f_callbackNotificaAlexa(uint8_t parametro)");
}

//========================================
void f_configuraAssistenteALX(bool force) {
  if (!vB_exec_Assistente) {
    f_carregaConfi("ASSISTENTE",force);
  } else if (force) {
    vB_exec_Assistente = true;
  }
  if (WiFi.status() == 3 && vB_exec_Assistente) {
    Serial.print("Iniciando configuracao assistente Alexa: ");
    if (vS_assNomeAlexa.length() > 3) {
      uint8_t cont = 1;
      CLIENT_ASS_ALEXA.setDiscoverable(true);
      CLIENT_ASS_ALEXA.addDevice("Reiniciar Módulo "+vS_nomeDispositivo, f_rebootaESP);
      while ( !CLIENT_ASS_ALEXA.begin() ) {
        Serial.print("Conectando a ALX... ");
        Serial.print(cont);
        Serial.print(" tentativa de ");
        Serial.print(vU8_tentativaConexoes);
        Serial.print(" : ");
        Serial.println(CLIENT_ASS_ALEXA.getEscapedMac());
        cont++;
        if (cont > vU8_tentativaConexoes) {
          break;
        }
        delay(5000);      
      }
      if (cont > vU8_tentativaConexoes) {
        Serial.println(" OK");
      } else {
        Serial.println(" FALHA ao iniciar assistente ALX.");
      }
    } else {
      Serial.println(" IGNORANDO ALX sem nome cadastrado.");
    }
  }
}

//========================================
void f_configuraAssistenteGH(bool force) {
  if (!vB_exec_Assistente) {
    f_carregaConfi("ASSISTENTE",force);
  } else if (force) {
    vB_exec_Assistente = true;
  }
  if (WiFi.status() == 3 && vB_exec_Assistente) {
    Serial.print("Iniciando configuracao assistente Google: ");
    if (vS_assNomeGoogle.length() > 3) {
      uint8_t cont = 1;
      while ( !CLIENT_ASS_GOOGLE.device(vS_assNomeGoogle.c_str(), vS_assLinguagem.c_str()) ) {
        Serial.print("Conectando ao GH... ");
        Serial.print(cont);
        Serial.print(" tentativa de ");
        Serial.print(vU8_tentativaConexoes);
        Serial.print(" : ");
        Serial.println(CLIENT_ASS_GOOGLE.getLastError());
        cont++;
        if (cont > vU8_tentativaConexoes) {
          break;
        }
        delay(5000);      
      }
      if (cont > vU8_tentativaConexoes) {
        Serial.print(CLIENT_ASS_GOOGLE.getIPAddress());
        Serial.println(" OK");
        f_enviaAssistentes("O módulo "+vS_nomeDispositivo+" foi iniciado.");
      } else {
        Serial.println(" FALHA ao iniciar assistente GH.");
      }
    } else {
      Serial.println(" IGNORANDO GH sem nome cadastrado.");
    }
  }
}

//========================================
bool f_publishDiscoveryMessage(String icone, String classe, String servico, String id_pin, uint8_t onoff) {
/*
  classe: switch, binary_sensor, sensor, etc.
  servico: PISCA, PULSO, LIGA, etc.
  id_pin: 4_21
*/
  bool resultado = false;
  if (WiFi.status() != WL_CONNECTED) {
    f_configuraWIFI();
  } else {
    vS_mqttDiscovery = "homeassistant/"+classe+"/"+vS_nomeDispositivo+"_"+classe+"/"+id_pin+"/config";
  
    DynamicJsonDocument doc(1024);
    doc["name"]    = vS_nomeDispositivo+" "+id_pin+" "+servico;
    doc["state_topic"]  = vS_mqttTopico+"/"+id_pin+"/"+servico+"/state";
    doc["command_topic"]  = vS_mqttTopico+"/"+id_pin+"/"+servico+"/set";
    doc["unique_id"] = vS_nomeDispositivo+"_"+vS_mqttIdUnico+"_"+classe+"_"+id_pin+"_"+servico;
    doc["device_class"] = classe;
    doc["icon"] = icone;
    doc["payload_on"]   = String(onoff);
    doc["payload_off"]  = String(!onoff);
    doc["value_template"] = "{{ value_json.state}}";
  
    JsonObject device = doc.createNestedObject("device");
    device["identifiers"] = vS_mqttIdUnico;
    device["name"] = vS_nomeDispositivo;
    device["model"] = "esp32dev";
    device["sw_version"] = "SMCR 2.0";
    device["manufacturer"] = "espressif";
  
    char buffer[1024];
    size_t n = serializeJson(doc, buffer);
  
    resultado = CLIENT_MQTT.publish(vS_mqttDiscovery.c_str(), buffer, true);
    //Serial.println("");
    //Serial.print("f_publishDiscoveryMessage status: ");
    //Serial.println(resultado);
    //Serial.print("Topico: ");
    //Serial.println(vS_mqttDiscovery);
    //Serial.print("             ->");
    //Serial.println(buffer);
  }
  return resultado;
}

//========================================
String f_traduzAcoesMqTT(uint16_t cod) {
  String resultado = "";
  switch (cod) {
    case 0:
      resultado = "NENHUMA";
      break;
    case 1:
      resultado = "LIGA";
      break;
    case 2:
      resultado = "LIGA_DELAY";
      break;
    case 3:
      resultado = "PISCA";
      break;
    case 4:
      resultado = "PULSO";
      break;
    case 5:
      resultado = "PULSO_DELAY";
      break;
    case 254:
      resultado = "STATUS_REMOTO";
      break;
  }
  return resultado;
}

//========================================
void f_enviaMqTTDiscovery() {
  uint64_t agora = millis();
  if ((agora - discovery_mqtt_lasttime) > vU32_mqtt_disc_MTBS) {  
    if (f_comunicaMQTT()) {
      for (uint8_t x=0; x<vU8_totPinos; x++) {
        if (aU8_AcaoRede1[3][x]) {
          f_publishDiscoveryMessage(aS8_Acao1[1][x],aS8_Acao1[0][x],f_traduzAcoesMqTT(aU16_Acao1[2][x]),String(aU16_Acao1[0][x])+"_"+String(aU16_Acao1[1][x]),aU16_Acao1[5][x]);
        } 
        if (aU8_AcaoRede2[3][x]) {
          f_publishDiscoveryMessage(aS8_Acao2[1][x],aS8_Acao2[0][x],f_traduzAcoesMqTT(aU16_Acao2[2][x]),String(aU16_Acao2[0][x])+"_"+String(aU16_Acao2[1][x]),aU16_Acao2[5][x]);
        } 
        if (aU8_AcaoRede3[3][x]) {
          f_publishDiscoveryMessage(aS8_Acao3[1][x],aS8_Acao3[0][x],f_traduzAcoesMqTT(aU16_Acao3[2][x]),String(aU16_Acao3[0][x])+"_"+String(aU16_Acao3[1][x]),aU16_Acao3[5][x]);
        } 
      }
    } else {
      f_reconnectMQTT();
    }
    discovery_mqtt_lasttime = agora;
  }
}

//========================================
bool f_checkAcoesMqTT() {
  uint64_t agora = millis();
  bool resultado = true;
  if ((agora - check_acoes_mqtt_lasttime) > vU16_mqtt_MTBS) {
    if (f_comunicaMQTT()) {
      for (uint8_t x=0; x<vU8_totPinos; x++) {
        if (aU8_AcaoRede1[3][x]) {
          f_enviaMqTT(String(aU16_Acao1[0][x])+"_"+String(aU16_Acao1[1][x])+"/"+f_traduzAcoesMqTT(aU16_Acao1[2][x])+"/state",String(aU8_Pinos_Status[0][x]));
        }
        if (aU8_AcaoRede2[3][x]) {
          f_enviaMqTT(String(aU16_Acao2[0][x])+"_"+String(aU16_Acao2[1][x])+"/"+f_traduzAcoesMqTT(aU16_Acao2[2][x])+"/state",String(aU8_Pinos_Status[0][x]));
        }
        if (aU8_AcaoRede3[3][x]) {
          f_enviaMqTT(String(aU16_Acao3[0][x])+"_"+String(aU16_Acao3[1][x])+"/"+f_traduzAcoesMqTT(aU16_Acao3[2][x])+"/state",String(aU8_Pinos_Status[0][x]));
          aU8_ControlMsgMqTT[2][x] = 1;
        }
      }
    } else {
      f_reconnectMQTT();
    }
    check_acoes_mqtt_lasttime = agora;
  }
  return resultado;
}

//========================================
bool f_enviaMqTT(String tpc, String msg) {
  if (WiFi.status() != WL_CONNECTED) {
    f_configuraWIFI();
  } else {
    String topenvia = vS_mqttTopico+"/"+tpc;
    return CLIENT_MQTT.publish(topenvia.c_str(), msg.c_str());
  }
}

//========================================
bool f_comunicaMQTT() {
  uint64_t agora = millis();
  bool resultado = true;
  if (agora - mqtt_lasttime >= vU16_mqtt_MTBS) {
    if (!CLIENT_MQTT.connected()) {
      resultado = false;
    } else {
      CLIENT_MQTT.loop();
    }
    mqtt_lasttime = agora;
  }  
  return resultado;
}

//========================================
void f_reconnectMQTT() {
  if (WiFi.status() == 3) {
    Serial.print("Conectando ao MQTT, status... ");
    if (CLIENT_MQTT.connect(vS_nomeDispositivo.c_str(),vS_mqttUser.c_str(),vS_mqttSenha.c_str())) {
      Serial.print(CLIENT_MQTT.connected());
      Serial.println(" OK");
      f_enviaMqTTDiscovery();  
    } else {
      Serial.print( CLIENT_MQTT.state());
      Serial.println(" FALHA - Reconfigurando MqTT");
      f_configuraMQTT(false);
    }
  } else {
    Serial.print("Ignorando reconexao com MqTT por falha no wifi, status: ");
    Serial.println(WiFi.status());
  }
}

//========================================
void f_configuraMQTT(bool force) {
  if (!vB_exec_MqTT) {
    f_carregaConfi("MQTT",force);
  } else if (force) {
    vB_exec_MqTT = true;
  }
  if (WiFi.status() == 3 && vB_exec_MqTT) {
    Serial.print("Iniciando configuracao MQTT: ");
    CLIENT_MQTT.setServer(vS_mqttServer.c_str(),vU16_mqttPorta);
    CLIENT_MQTT.setKeepAlive(30);
    CLIENT_MQTT.setBufferSize(1024);
    Serial.println(" OK");
    Serial.print("Conectando ao MQTT, status... ");
    if (CLIENT_MQTT.connect(vS_nomeDispositivo.c_str(),vS_mqttUser.c_str(),vS_mqttSenha.c_str())) {
      Serial.print(CLIENT_MQTT.connected());
      Serial.println(" OK");
      //f_enviaMqTTDiscovery();
    } else {
      Serial.print(CLIENT_MQTT.connected());
      Serial.println(" FALHA");
    }    
  }
}

//========================================
bool f_configuraTELEGRAM(bool force) {
  bool resultado = false;
  if (!vB_exec_Telegram) {
    f_carregaConfi("TELEGRAM",force);
  } else if (force) {
    vB_exec_Telegram = true;
  }
  if (WiFi.status() == 3 && vB_exec_Telegram) {
    Serial.print("Iniciando configuracao de hora e telegram: ");
    configTime(0, 0, "pool.ntp.br"); // Ajusta hora via NTP
    bot.updateToken(vS_api_Telegram);
    CLIENT_TELEGRAM.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Adiciona certificado root para api.telegram.org
    CLIENT_TELEGRAM.connected();
    Serial.println(" OK");
  }
  return resultado;
}

//========================================
String f_traduzAcoesTelegram(uint16_t cod) {
  String resultado = "NULO";
  switch (cod) {
    case 0:
      resultado = "NENHUMA";
      break;
    case 1:
      resultado = "LIGA";
      break;
    case 2:
      resultado = "LIGA_DELAY";
      break;
    case 3:
      resultado = "PISCA";
      break;
    case 4:
      resultado = "PULSO";
      break;
    case 5:
      resultado = "PULSO_DELAY";
      break;
    case 254:
      resultado = "STATUS_REMOTO";
      break;      
  }
  return resultado;
}

//========================================
uint16_t f_carregaConfi(String ref, bool force) {
  uint16_t resultado = 1;
  CONFIG_FLASH.begin("confiGeral", true);
  if (ref == "REDE" || ref == "TUDO") {
    vS_nomeWifi = CONFIG_FLASH.getString("nome_wifi", "wifi"); //SSID da sua rede wifi (rede que essa placa ESP vai conectar)
    vS_senhaWifi = CONFIG_FLASH.getString("senha_wifi", "12345678"); //Senha da sua rede wifi (rede que essa placa ESP vai conectar)
    vU8_tentativaConexoes = CONFIG_FLASH.getUChar("tenta_conect", 4); //Tentativas de conexoes diversas antes de seguir com o boot(para nao ficar parado durante o boot esperando conetar em outros recursos)
    vU16_portaWeb = CONFIG_FLASH.getUShort("porta_srvweb", 8080);                                    //Porta do servidor web desta placa ESP
    vS_nomeDispositivo = CONFIG_FLASH.getString("nome_disp", "esp32modularx");                       //Hostname desta placa ESP na rede    
    vS_nomeAP_Wifi = CONFIG_FLASH.getString("nome_wifi_ap", vS_nomeDispositivo+" Ponto de Acesso");  //Nome do wifi (SSID) que sera gerado se esta placa ESP entrar em modo AP
    vS_senhaAP_Wifi = CONFIG_FLASH.getString("senha_wifi_ap", "senha12345678");                      //Senha do wifi que sera gerado se esta placa ESP entrar em modo AP
    vB_modoAP = CONFIG_FLASH.getBool("modo_wifi_ap", true); //Se true esta placa ESP entra em modo AP caso nao consiga conectar no wifi definido em vS_nomeWifi
    vS_ntpServer1 = CONFIG_FLASH.getString("ntp_srv1", "pool.ntp.br");
    vS_ntpServer2 = CONFIG_FLASH.getString("ntp_srv2", "pool.ntp.org");
    vS_timeZone = CONFIG_FLASH.getString("ntp_timez", "<-03>3");
  }
  if (ref == "TELEGRAM" || ref == "TUDO") {
    if (force) {
      vB_exec_Telegram = true;
    } else {
      vB_exec_Telegram = CONFIG_FLASH.getBool("exe_teleg", false); //Se true esta placa ESP envia mensagens via telegram
    }
    vS_api_Telegram = CONFIG_FLASH.getString("api_teleg", ":"); //API do telegram
    vS_chat_Telegram = CONFIG_FLASH.getString("chat_teleg", "-"); //ID do chat para enviar notificacoes
    vS_user_Telegram = CONFIG_FLASH.getString("boot_teleg", "@"); //Username do bot no telegram
    vU16_bot_MTBS = CONFIG_FLASH.getULong64("time_teleg", 65535); //Tempo em milisegundos para verificacao de mensagens telegram
  }
  if (ref == "MQTT" || ref == "TUDO") {
    if (force) {
      vB_exec_MqTT = true;
    } else {
      vB_exec_MqTT = CONFIG_FLASH.getBool("exe_mqtt", false); //Se true esta placa ESP envia mensagens via mqtt
    }
    vS_mqttTopico = CONFIG_FLASH.getString("top_mqtt", "pubsub"); //Topico MqTT
    vS_mqttServer = CONFIG_FLASH.getString("srv_mqtt", "10."); //Servidor MqTT
    vS_mqttUser = CONFIG_FLASH.getString("usr_mqtt", "usr"); //Usuario MqTT
    vS_mqttSenha = CONFIG_FLASH.getString("pss_mqtt", "pwd"); //Senha MqTT
    vU16_mqttPorta = CONFIG_FLASH.getUShort("porta_mqtt", 0); //Porta para comunicacao com mqtt
    vU16_mqtt_MTBS = CONFIG_FLASH.getULong64("time_mqtt", 65535); //Tempo em milisegundos para comunicacao com mqtt
    vU32_mqtt_disc_MTBS = CONFIG_FLASH.getULong64("disc_mqtt", 65535); //Tempo em milisegundos para discovery com mqtt
  }
  if (ref == "ASSISTENTE" || ref == "TUDO") {
    if (force) {
      vB_exec_Assistente = true;
    } else {
      vB_exec_Assistente = CONFIG_FLASH.getBool("exe_ass", false);
    }
    vS_assNomeGoogle = CONFIG_FLASH.getString("ass_google", "dh");
    vS_assNomeAlexa = CONFIG_FLASH.getString("ass_alexa", "alx");
    vS_assLinguagem = CONFIG_FLASH.getString("ass_ling", "ling");
    vU16_ass_MTBS = CONFIG_FLASH.getULong64("ass_time", 65535);
    vS_ass_Alerta = CONFIG_FLASH.getString("ass_alerta", "frase alerta");
    vS_ass_Normal = CONFIG_FLASH.getString("ass_normal", "frase normal");
  }
  if (ref == "MODULOS" || ref == "TUDO") {
    vB_exec_Modulos = CONFIG_FLASH.getBool("exe_mod", false);
    vU16_modulos_MTBS = CONFIG_FLASH.getULong64("time_mod", 65535);
    //vU16_portaWebModulos = CONFIG_FLASH.getULong64("porta_mod", 65535);
    vI_cicloHandshake = CONFIG_FLASH.getULong64("ciclo_mod", 10);
  }
  if (ref == "ARRAY" || ref == "TUDO") {
    resultado = CONFIG_FLASH.getUChar("qnt_pinos", 52);
  }
  if (ref == "ASYNC" || ref == "TUDO") {
    resultado = CONFIG_FLASH.getUShort("porta_srvweb", 8080)+1;
  }  
  CONFIG_FLASH.end();
  return resultado;
}

//========================================
bool f_checkAcoesTelegram() {
  uint64_t agora = millis();
  bool resultado = true;
  if ((agora - check_acoes_telegram_lasttime) > vU16_bot_MTBS) {
    for (uint8_t x=0; x<vU8_totPinos; x++) {
      if (aU8_AcaoRede1[1][x] && aU8_Pinos_Status[0][x] && !aU8_ControlMsgTelegram[0][x]) {
        resultado = f_enviaTelegram(vS_nomeDispositivo+"\n"+aS8_Pinos[0][x]+" - Alerta AÇÃO: "+f_traduzAcoesTelegram(aU16_Acao1[2][x])+"\n Origem: "+String(aU16_Acao1[0][x])+" Destino: "+aU16_Acao1[1][x]);
        aU8_ControlMsgTelegram[0][x] = 1;
      } else if(aU8_AcaoRede1[1][x] && !aU8_Pinos_Status[0][x] && aU8_ControlMsgTelegram[0][x]){
        resultado = f_enviaTelegram(vS_nomeDispositivo+"\n"+aS8_Pinos[0][x]+" - Normalização AÇÃO: "+f_traduzAcoesTelegram(aU16_Acao1[2][x])+"\n Origem: "+String(aU16_Acao1[0][x])+" Destino: "+aU16_Acao1[1][x]);
        aU8_ControlMsgTelegram[0][x] = 0;
      }
      if (aU8_AcaoRede2[1][x] && aU8_Pinos_Status[0][x] && !aU8_ControlMsgTelegram[1][x]) {
        resultado = f_enviaTelegram(vS_nomeDispositivo+"\n"+aS8_Pinos[0][x]+" - Alerta AÇÃO 2: "+f_traduzAcoesTelegram(aU16_Acao2[2][x])+"\n Origem: "+String(aU16_Acao2[0][x])+" Destino: "+aU16_Acao2[1][x]);
        aU8_ControlMsgTelegram[1][x] = 1;
      } else if(aU8_AcaoRede2[1][x] && !aU8_Pinos_Status[0][x] && aU8_ControlMsgTelegram[1][x]){
        resultado = f_enviaTelegram(vS_nomeDispositivo+"\n"+aS8_Pinos[0][x]+" - Normalização AÇÃO 2: "+f_traduzAcoesTelegram(aU16_Acao2[2][x])+"\n Origem: "+String(aU16_Acao2[0][x])+" Destino: "+aU16_Acao2[1][x]);
        aU8_ControlMsgTelegram[1][x] = 0;
      }
      if (aU8_AcaoRede3[1][x] && aU8_Pinos_Status[0][x] && !aU8_ControlMsgTelegram[2][x]) {
        resultado = f_enviaTelegram(vS_nomeDispositivo+"\n"+aS8_Pinos[0][x]+" - Alerta AÇÃO 3: "+f_traduzAcoesTelegram(aU16_Acao3[2][x])+"\n Origem: "+String(aU16_Acao3[0][x])+" Destino: "+aU16_Acao3[1][x]);
        aU8_ControlMsgTelegram[2][x] = 1;
      } else if(aU8_AcaoRede3[1][x] && !aU8_Pinos_Status[0][x] && aU8_ControlMsgTelegram[2][x]){
        resultado = f_enviaTelegram(vS_nomeDispositivo+"\n"+aS8_Pinos[0][x]+" - Normalização AÇÃO 3: "+f_traduzAcoesTelegram(aU16_Acao3[2][x])+"\n Origem: "+String(aU16_Acao3[0][x])+" Destino: "+aU16_Acao3[1][x]);
        aU8_ControlMsgTelegram[2][x] = 0;
      }     
    }
    check_acoes_telegram_lasttime = agora;
  }
  return resultado;
}

//========================================
bool f_enviaTelegram(String msg) {
  bool resultado = false;
  if (WiFi.status() != WL_CONNECTED) {
    f_configuraWIFI();
  } else {
    bot.sendChatAction(vS_chat_Telegram, "typing");
    String vS_msgTelegram = msg;
    vS_msgTelegram += "\n";
    resultado = bot.sendMessage(vS_chat_Telegram, vS_msgTelegram);
  }
  return resultado;
}

//========================================
void f_handleNewMessagesTelegram(int numNewMessages) {
  Serial.println("f_handleNewMessagesTelegram: ");
  Serial.println(String(numNewMessages));
  String vS_msgTelegram = "";
  for (int i = 0; i < numNewMessages; i++)
  {
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = vS_nomeDispositivo;
    
    Serial.println("Recebido via Telegram: "+text);

    if (text == "/start") {
      bot.sendChatAction(vS_chat_Telegram, "typing");      
      vS_msgTelegram = "Conexão com a placa, " + vS_nomeDispositivo + ".\n";
      vS_msgTelegram += "Envie /"+vS_nomeDispositivo+" para lista de comandos da placa \n";

    }

    if (text.substring(1,text.length()) == (vS_nomeDispositivo+vS_user_Telegram)) {
      bot.sendChatAction(vS_chat_Telegram, "typing");
      vS_msgTelegram = "Conexão com a placa, " + vS_nomeDispositivo + ".\n";
      vS_msgTelegram += "Envie /"+vS_nomeDispositivo+" para lista de comandos da placa \n";
    }

    //if (text.substring(1,text.length()) == ("Energia_Gerador"+vS_user_Telegram)) {
    //  bot.sendChatAction(vS_chat_Telegram, "typing");
    //  vS_msgTelegram = "Info 1:\n";
    //  vS_msgTelegram += " V\n";
    //  //bot.sendMessage(vS_chat_Telegram, vS_msgTelegram);
    //}

    bot.sendMessage(vS_chat_Telegram, vS_msgTelegram);
  }
}

//========================================
void f_recebeTelegram() {
  uint64_t agora = millis();
  if ((agora - telegram_lasttime) > vU16_bot_MTBS) {
    if (WiFi.status() != WL_CONNECTED) {
      f_configuraWIFI();
    } else {    
      //if (CLIENT_TELEGRAM.connected()) {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        while (numNewMessages)
        {
          Serial.println("got response");
          f_handleNewMessagesTelegram(numNewMessages);
          numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
      //} else {
      //    f_configuraTELEGRAM();  
      //}
      telegram_lasttime = agora;
    }
  }
}

//========================================
void f_salvaFlash() {
  CONFIG_FLASH.begin("confiGeral", false);
  CONFIG_FLASH.clear();

  CONFIG_FLASH.putString("nome_wifi", vS_nomeWifi);
  CONFIG_FLASH.putString("senha_wifi", vS_senhaWifi);
  CONFIG_FLASH.putUChar("tenta_conect", vU8_tentativaConexoes);
  CONFIG_FLASH.putUShort("porta_srvweb", vU16_portaWeb);
  CONFIG_FLASH.putString("nome_disp", vS_nomeDispositivo);
  CONFIG_FLASH.putString("nome_wifi_ap", vS_nomeDispositivo+" Ponto de Acesso");
  CONFIG_FLASH.putString("senha_wifi_ap", vS_senhaAP_Wifi);
  CONFIG_FLASH.putBool("modo_wifi_ap", vB_modoAP);
  CONFIG_FLASH.putString("ntp_srv1", vS_ntpServer1);
  CONFIG_FLASH.putString("ntp_srv2", vS_ntpServer2);
  CONFIG_FLASH.putString("ntp_timez", vS_timeZone);
  CONFIG_FLASH.putString("cor_sts_1", vS_corStatus1);
  CONFIG_FLASH.putString("cor_sts_0", vS_corStatus0);
  CONFIG_FLASH.putBool("exe_teleg", vB_exec_Telegram);
  CONFIG_FLASH.putString("api_teleg", vS_api_Telegram);
  CONFIG_FLASH.putString("chat_teleg", vS_chat_Telegram);
  CONFIG_FLASH.putString("boot_teleg", vS_user_Telegram);
  CONFIG_FLASH.putULong64("time_teleg", vU16_bot_MTBS);
  CONFIG_FLASH.putBool("exe_mqtt", vB_exec_MqTT);
  CONFIG_FLASH.putString("top_mqtt", vS_mqttTopico);
  CONFIG_FLASH.putString("srv_mqtt", vS_mqttServer);
  CONFIG_FLASH.putString("usr_mqtt", vS_mqttUser);
  CONFIG_FLASH.putString("pss_mqtt", vS_mqttSenha);
  CONFIG_FLASH.putULong64("time_mqtt", vU16_mqtt_MTBS);
  CONFIG_FLASH.putULong64("disc_mqtt", vU32_mqtt_disc_MTBS);
  CONFIG_FLASH.putUShort("porta_mqtt", vU16_mqttPorta);
  CONFIG_FLASH.putBool("exe_ass", vB_exec_Assistente);
  CONFIG_FLASH.putULong64("ass_time", vU16_ass_MTBS);
  CONFIG_FLASH.putString("ass_google", vS_assNomeGoogle);
  CONFIG_FLASH.putString("ass_alexa", vS_assNomeAlexa);
  CONFIG_FLASH.putString("ass_ling", vS_assLinguagem);
  CONFIG_FLASH.putString("ass_alerta", vS_ass_Alerta);
  CONFIG_FLASH.putString("ass_normal", vS_ass_Normal);
  CONFIG_FLASH.putBool("exe_mod", vB_exec_Modulos);
  CONFIG_FLASH.putULong64("time_mod", vU16_modulos_MTBS);
 // CONFIG_FLASH.putULong64("porta_mod", vU16_portaWebModulos);
  CONFIG_FLASH.putULong64("ciclo_mod", vI_cicloHandshake);
  CONFIG_FLASH.putUChar("qnt_pinos", vU8_totPinos);

  Serial.print("Numero de elementos aU8_Pinos: ");
  Serial.println(sizeof(aU8_Pinos) / sizeof(uint8_t));
  Serial.print("Tamanho aU8_Pinos em bytes: ");
  Serial.println( sizeof(aU8_Pinos) );
  CONFIG_FLASH.putBytes( "paU8_Pinos", aU8_Pinos, sizeof(aU8_Pinos) );
  Serial.print("Tamanho paU8_Pinos em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU8_Pinos") );

  Serial.print("Numero de elementos aS8_Pinos: ");
  Serial.println(sizeof(aS8_Pinos) / sizeof(uint8_t));
  Serial.print("Tamanho aS8_Pinos em bytes: ");
  Serial.println( sizeof(aS8_Pinos) );
  CONFIG_FLASH.putBytes( "paS8_Pinos", aS8_Pinos, sizeof(aS8_Pinos) );
  Serial.print("Tamanho paS8_Pinos em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paS8_Pinos") );

  Serial.print("Numero de elementos aU16_Acao1: ");
  Serial.println(sizeof(aU16_Acao1) / sizeof(uint8_t)); //uint16_t
  Serial.print("Tamanho aU16_Acao1 em bytes: ");
  Serial.println( sizeof(aU16_Acao1) );
  CONFIG_FLASH.putBytes( "paU16_Acao1", aU16_Acao1, sizeof(aU16_Acao1) );
  Serial.print("Tamanho paU16_Acao1 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU16_Acao1") );

  Serial.print("Numero de elementos aU8_AcaoRede1: ");
  Serial.println(sizeof(aU8_AcaoRede1) / sizeof(uint8_t)); //uint16_t
  Serial.print("Tamanho aU8_AcaoRede1 em bytes: ");
  Serial.println( sizeof(aU8_AcaoRede1) );
  CONFIG_FLASH.putBytes( "paU8_AcaoRede1", aU8_AcaoRede1, sizeof(aU8_AcaoRede1) );
  Serial.print("Tamanho paU8_AcaoRede1 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU8_AcaoRede1") );

  Serial.print("Numero de elementos aS8_Acao1: ");
  Serial.println(sizeof(aS8_Acao1) / sizeof(uint8_t));
  Serial.print("Tamanho aS8_Acao1 em bytes: ");
  Serial.println( sizeof(aS8_Acao1) );
  CONFIG_FLASH.putBytes( "paS8_Acao1", aS8_Acao1, sizeof(aS8_Acao1) );
  Serial.print("Tamanho paS8_Acao1 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paS8_Acao1") );  

  Serial.print("Numero de elementos aU16_Acao2: ");
  Serial.println(sizeof(aU16_Acao2) / sizeof(uint8_t)); //uint16_t
  Serial.print("Tamanho aU16_Acao2 em bytes: ");
  Serial.println( sizeof(aU16_Acao2) );
  CONFIG_FLASH.putBytes( "paU16_Acao2", aU16_Acao2, sizeof(aU16_Acao2) );
  Serial.print("Tamanho paU16_Acao2 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU16_Acao2") );

  Serial.print("Numero de elementos aU8_AcaoRede2: ");
  Serial.println(sizeof(aU8_AcaoRede2) / sizeof(uint8_t)); //uint16_t
  Serial.print("Tamanho aU8_AcaoRede2 em bytes: ");
  Serial.println( sizeof(aU8_AcaoRede2) );
  CONFIG_FLASH.putBytes( "paU8_AcaoRede2", aU8_AcaoRede2, sizeof(aU8_AcaoRede2) );
  Serial.print("Tamanho paU8_AcaoRede2 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU8_AcaoRede2") );

  Serial.print("Numero de elementos aS8_Acao2: ");
  Serial.println(sizeof(aS8_Acao2) / sizeof(uint8_t));
  Serial.print("Tamanho aS8_Acao2 em bytes: ");
  Serial.println( sizeof(aS8_Acao2) );
  CONFIG_FLASH.putBytes( "paS8_Acao2", aS8_Acao2, sizeof(aS8_Acao2) );
  Serial.print("Tamanho paS8_Acao2 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paS8_Acao2") );

  Serial.print("Numero de elementos aU16_Acao3: ");
  Serial.println(sizeof(aU16_Acao3) / sizeof(uint8_t)); //uint16_t
  Serial.print("Tamanho aU16_Acao3 em bytes: ");
  Serial.println( sizeof(aU16_Acao3) );
  CONFIG_FLASH.putBytes( "paU16_Acao3", aU16_Acao3, sizeof(aU16_Acao3) );
  Serial.print("Tamanho paU16_Acao3 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU16_Acao3") );

  Serial.print("Numero de elementos aU8_AcaoRede3: ");
  Serial.println(sizeof(aU8_AcaoRede3) / sizeof(uint8_t)); //uint16_t
  Serial.print("Tamanho aU8_AcaoRede3 em bytes: ");
  Serial.println( sizeof(aU8_AcaoRede3) );
  CONFIG_FLASH.putBytes( "paU8_AcaoRede3", aU8_AcaoRede3, sizeof(aU8_AcaoRede3) );
  Serial.print("Tamanho paU8_AcaoRede3 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU8_AcaoRede3") );

  Serial.print("Numero de elementos aS8_Acao3: ");
  Serial.println(sizeof(aS8_Acao3) / sizeof(uint8_t));
  Serial.print("Tamanho aS8_Acao3 em bytes: ");
  Serial.println( sizeof(aS8_Acao3) );
  CONFIG_FLASH.putBytes( "paS8_Acao3", aS8_Acao3, sizeof(aS8_Acao3) );
  Serial.print("Tamanho paS8_Acao3 em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paS8_Acao3") );

  Serial.print("Numero de elementos aS_InterMod: ");
  Serial.println(sizeof(aS_InterMod) / sizeof(uint8_t));
  Serial.print("Tamanho aS_InterMod em bytes: ");
  Serial.println( sizeof(aS_InterMod) );
  CONFIG_FLASH.putBytes( "paS_InterMod", aS_InterMod, sizeof(aS_InterMod) );
  Serial.print("Tamanho paS_InterMod em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paS_InterMod"));

  Serial.print("Numero de elementos aU16_InterMod: ");
  Serial.println(sizeof(aU16_InterMod) / sizeof(uint8_t));
  Serial.print("Tamanho aU16_InterMod em bytes: ");
  Serial.println( sizeof(aU16_InterMod) );
  CONFIG_FLASH.putBytes( "paU16_InterMod", aU16_InterMod, sizeof(aU16_InterMod) );
  Serial.print("Tamanho paU16_InterMod em bytes: ");
  Serial.println( CONFIG_FLASH.getBytesLength("paU16_InterMod"));

  CONFIG_FLASH.end();
}

//========================================
void f_iniciaAcoes(bool force) {
/*
vI16_aU16_Acao = 10;
aU16_Acao[10][23]
aU16_Acao[Propriedade][Pino]
aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Daley / 3=Pisca / 4=Pulso / 5=Pulso Delay
aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU8_Pinos[4][x] = Envia ao Receptor 0=Nao / 1=Sim
aU16_Acao[6][x] = Envia ao Telegram 0=Nao / 1=Sim
aU16_Acao[7][x] = Envia ao MqTT 0=Nao / 1=Sim
aU16_Acao[8][x] = Notifica Assitente 0=Nao / 1=Sim
aU16_Acao[9][x] = Acionamento Alto=1 / Baixo=0
*/
  Serial.print("Iniciando configuracao das Acoes... ");
  bool addass = false;
  CONFIG_FLASH.begin("confiGeral", true);
  uint16_t aU16BufferX[vI8_aU16_Acao][vU8_totPinos] = {};
  uint8_t aU8BufferY[vI8_aU16_AcaoRede][vU8_totPinos] = {};
  String aSBufferZ[vI8_aS8_Acao][vU8_totPinos] = {};

  // Acoes 1
  CONFIG_FLASH.getBytes("paU16_Acao1", aU16BufferX, CONFIG_FLASH.getBytesLength("paU16_Acao1"));
  CONFIG_FLASH.getBytes("paU8_AcaoRede1", aU8BufferY, CONFIG_FLASH.getBytesLength("paU8_AcaoRede1"));
  CONFIG_FLASH.getBytes("paS8_Acao1", aSBufferZ, CONFIG_FLASH.getBytesLength("paS8_Acao1"));

  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU16_Acao1[x][y] = aU16BufferX[x][y];
    }
  }
  for (uint8_t x=0; x<vI8_aU16_AcaoRede; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU8_AcaoRede1[x][y] = aU8BufferY[x][y];
      if(aU8_AcaoRede1[2][y]) {
        addass = true;
        CLIENT_ASS_ALEXA.addDevice(f_traduzAcoesAss(aU16_Acao1[2][x])+" "+aS8_Pinos[0][y], f_callbackNotificaAlexa);
      }
    }
  }
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aS8_Acao1[x][y] = aSBufferZ[x][y];
    }
  }

  // Acoes 2
  CONFIG_FLASH.getBytes("paU16_Acao2", aU16BufferX, CONFIG_FLASH.getBytesLength("paU16_Acao2"));
  CONFIG_FLASH.getBytes("paU8_AcaoRede2", aU8BufferY, CONFIG_FLASH.getBytesLength("paU8_AcaoRede2"));
  CONFIG_FLASH.getBytes("paS8_Acao2", aSBufferZ, CONFIG_FLASH.getBytesLength("paS8_Acao2"));

  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU16_Acao2[x][y] = aU16BufferX[x][y];
    }
  }
  for (uint8_t x=0; x<vI8_aU16_AcaoRede; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU8_AcaoRede2[x][y] = aU8BufferY[x][y];
      if(aU8_AcaoRede2[2][y]) {
        addass = true;
        CLIENT_ASS_ALEXA.addDevice(f_traduzAcoesAss(aU16_Acao2[2][x])+" "+aS8_Pinos[0][y], f_callbackNotificaAlexa);
      }
    }
  }
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aS8_Acao2[x][y] = aSBufferZ[x][y];
    }
  }

  // Acoes 3
  CONFIG_FLASH.getBytes("paU16_Acao3", aU16BufferX, CONFIG_FLASH.getBytesLength("paU16_Acao3"));
  CONFIG_FLASH.getBytes("paU8_AcaoRede3", aU8BufferY, CONFIG_FLASH.getBytesLength("paU8_AcaoRede3"));
  CONFIG_FLASH.getBytes("paS8_Acao3", aSBufferZ, CONFIG_FLASH.getBytesLength("paS8_Acao3"));

  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU16_Acao3[x][y] = aU16BufferX[x][y];
    }
  }
  for (uint8_t x=0; x<vI8_aU16_AcaoRede; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU8_AcaoRede3[x][y] = aU8BufferY[x][y];
      if(aU8_AcaoRede3[2][y]) {
        addass = true;
        CLIENT_ASS_ALEXA.addDevice(f_traduzAcoesAss(aU16_Acao3[2][x])+" "+aS8_Pinos[0][y], f_callbackNotificaAlexa);
      }
    }
  }
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aS8_Acao3[x][y] = aSBufferZ[x][y];
    }
  }
  CONFIG_FLASH.end();
  Serial.println(" OK");
  f_grupoAcoes();
}

//========================================
void f_grupoAcoes() {

  //for (uint8_t x=1; x<vI8_ControlAcoesGroups; x++){
  //  for (uint8_t y=0; y<vU8_totPinos; y++){
  //    aU16_ControlAcoesGroups[x][y] == 0;
  //  }
  //}

  int xyz = 1;
  //Acoes 1
  Serial.print("Formando grupo acoes1: ");
  for (uint8_t x=0; x<vU8_totPinos; x++){
    if (aU16_Acao1[0][x] > 1) {
      for (uint8_t y=0; y<vU8_totPinos; y++){
        if (aU16_ControlAcoesGroups[0][x] == aU16_Acao1[1][y]) {
          aU16_ControlAcoesGroups[xyz][x] = aU16_Acao1[0][y];
          xyz++;
        }
      }
    }
  }
  Serial.println(xyz-1);
  //Acoes 2
  Serial.print("Formando grupo acoes2: ");
  for (uint8_t x=0; x<vU8_totPinos; x++){
    if (aU16_Acao2[0][x] > 1) {
      for (uint8_t y=0; y<vU8_totPinos; y++){
        if (aU16_ControlAcoesGroups[0][x] == aU16_Acao2[1][y]) {
          aU16_ControlAcoesGroups[xyz][x] = aU16_Acao2[0][y];
          xyz++;
        }
      }
    }
  }
  Serial.println(xyz-1);
  //Acoes 3
  Serial.print("Formando grupo acoes3: ");
  for (uint8_t x=0; x<vU8_totPinos; x++){
    if (aU16_Acao3[0][x] > 1) {
      for (uint8_t y=0; y<vU8_totPinos; y++){
        if (aU16_ControlAcoesGroups[0][x] == aU16_Acao3[1][y]) {
          aU16_ControlAcoesGroups[xyz][x] = aU16_Acao3[0][y];
          xyz++;
        }
      }
    }
  }
  Serial.println(xyz-1);
}

//========================================
void f_pisca(uint8_t pino) {
  digitalWrite(pino,!digitalRead(pino));
}

//========================================
void f_gravaPino(uint8_t tipo, uint8_t pino, uint8_t valor) {
  if (tipo == 1 || tipo == 254) {
    digitalWrite(pino,valor);
  } else {
    analogWrite(pino, valor);
  }
}

//========================================
uint8_t f_lePino(uint8_t tipo, uint8_t invert, uint8_t pino) {
  uint8_t resultado = 0;
  if (tipo) {
    resultado = invert^digitalRead(pino);
  } else {
    resultado = analogRead(pino);
  }
  return resultado;
}

//========================================
void f_iniciaPinos(bool force) {
/*
aU8_Pinos[0][x] = Fisico Mapeamento dos pinos fisicos
aU8_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO
aU8_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0
*/
  Serial.print("Iniciando configuracao dos pinos... ");
  CONFIG_FLASH.begin("confiGeral", true);
  uint8_t aU8Buffer[vI8_aU8_Pinos][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paU8_Pinos", aU8Buffer, CONFIG_FLASH.getBytesLength("paU8_Pinos"));

  vS_corStatus1 = CONFIG_FLASH.getString("cor_sts_1", "Tomato");
  vS_corStatus0 = CONFIG_FLASH.getString("cor_sts_0", "LightGreen");

  String aSBuffer[vI8_aS8_Pinos][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paS8_Pinos", aSBuffer, CONFIG_FLASH.getBytesLength("paS8_Pinos"));
  CONFIG_FLASH.end();

  for (uint8_t x=0; x<vI8_aU8_Pinos; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aU8_Pinos[x][y] = aU8Buffer[x][y];
    }
  }
  for (uint8_t x=0; x<vU8_totPinos; x++){
    aU16_ControlAcoesGroups[0][x] = aU8_Pinos[0][x];
    if (aU8_Pinos[1][x] == 1) {
      pinMode(aU8_Pinos[0][x],aU8_Pinos[2][x]);
    }
  }
  for (uint8_t x=0; x<vI8_aS8_Pinos; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      aS8_Pinos[x][y] = aSBuffer[x][y];
    }
  }
  Serial.println("OK");
}

//========================================
bool f_configuraWEB() {
  bool resultado = false;
  if (WiFi.status() == 3) {
    Serial.print("Iniciando configuracao do servidor web na porta ");
    Serial.print(vU16_portaWeb);
    SERVIDOR_WEB.begin(vU16_portaWeb);
    SERVIDOR_WEB.on("/", f_handle_Index);
    SERVIDOR_WEB.on("/wifi", f_handle_ConfiguraWifi);
    SERVIDOR_WEB.on("/configurag", f_handle_ConfiguraGeral);
    SERVIDOR_WEB.on("/limpaflash", f_limpaFLASH);
    SERVIDOR_WEB.on("/firmware", f_handle_OTA);
    SERVIDOR_WEB.on("/reboota", f_Reboota);
    SERVIDOR_WEB.on("/pinos", f_handle_ConfiguraPortas);
    SERVIDOR_WEB.on("/acoes1pg1", f_handle_ConfiguraAcoes1pg1);
    SERVIDOR_WEB.on("/acoes1pg2", f_handle_ConfiguraAcoes1pg2);
    SERVIDOR_WEB.on("/acoes2pg1", f_handle_ConfiguraAcoes2pg1);
    SERVIDOR_WEB.on("/acoes2pg2", f_handle_ConfiguraAcoes2pg2);
    SERVIDOR_WEB.on("/acoes3pg1", f_handle_ConfiguraAcoes3pg1);
    SERVIDOR_WEB.on("/acoes3pg2", f_handle_ConfiguraAcoes3pg2);
    SERVIDOR_WEB.on("/salvaflash", f_handle_SalvaFlash);
    SERVIDOR_WEB.on("/recarrega", f_handle_RecarregarFuncoes);
    SERVIDOR_WEB.on("/lsprefpin", f_listaPreferencesMEM);
    SERVIDOR_WEB.on("/lsprefflash", f_listaPreferencesFLASH);
    SERVIDOR_WEB.on("/dados", f_recebeDados);
    SERVIDOR_WEB.on("/intermod", f_handle_InterModulos);
    SERVIDOR_WEB.on("/expimp", f_ExportImport);
    SERVIDOR_WEB.on("/imp", f_Import);

    SERVIDOR_WEB.on("/importar", HTTP_POST, []() {
         SERVIDOR_WEB.sendHeader("Connection", "close");
         SERVIDOR_WEB.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      }
      , []() {  
         HTTPUpload& upload = SERVIDOR_WEB.upload();
         if (upload.status == UPLOAD_FILE_START) {
           jsonFile = SPIFFS.open("/temp.json", FILE_WRITE);
           if (!jsonFile) {
             Serial.println("Erro ao abrir o arquivo para escrita");
             return;
           }
           jsonFile.close();
         } else if (upload.status == UPLOAD_FILE_WRITE) {
            jsonFile = SPIFFS.open("/temp.json", FILE_APPEND);
            if (!jsonFile) {
              Serial.println("Erro ao abrir o arquivo para escrita");
              return;
            }
            if (jsonFile.write(upload.buf, upload.currentSize) != upload.currentSize) {
              Serial.println("Erro ao escrever no arquivo");
              return;
            }
            jsonFile.close();
         } else if (upload.status == UPLOAD_FILE_END) {
           f_importarDoBackup();
         }
      });

    SERVIDOR_WEB.on("/update", HTTP_POST, []() {
                                                  SERVIDOR_WEB.sendHeader("Connection", "close");
                                                  SERVIDOR_WEB.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
                                                  ESP.restart();
                                               }
                                        , []() {
                                                  HTTPUpload& upload = SERVIDOR_WEB.upload();
                                                  if (upload.status == UPLOAD_FILE_START) {
                                                    Serial.printf("Update: %s\n", upload.filename.c_str());
                                                    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
                                                      Update.printError(Serial);
                                                    }
                                                  } else if (upload.status == UPLOAD_FILE_WRITE) {
                                                    /* flashing firmware to ESP*/
                                                    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                                                      Update.printError(Serial);
                                                    }
                                                  } else if (upload.status == UPLOAD_FILE_END) {
                                                    if (Update.end(true)) { //true to set the size to the current progress
                                                      Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                                                    } else {
                                                      Update.printError(Serial);
                                                    }
                                                  }
                                               });
    SERVIDOR_WEB.onNotFound(f_handle_NotFound);                                               
    Serial.println(" OK");
    resultado = true;

    SERVIDOR_WEB_ASYNC.on("/exportar", HTTP_GET, [](AsyncWebServerRequest *request) {
      String dadosBackup = f_exportarParaBackup();

      String arquivo = vS_nomeDispositivo;
      arquivo.replace(" ", "_");  
      arquivo = "backup_" + arquivo + "_" + String(timeinfo.tm_year + 1900) + "_" + String(timeinfo.tm_mday) + "_" + aS_traduzMes[0][timeinfo.tm_mon] + "_" + String(timeinfo.tm_hour) + String(timeinfo.tm_min) + String(timeinfo.tm_sec) + ".json";

      AsyncWebServerResponse *response = request->beginResponse(200, "application/octet-stream", dadosBackup);
      response->addHeader("Content-Disposition", "attachment; filename=" + arquivo);
      request->send(response);
    });    
    SERVIDOR_WEB_ASYNC.begin();
  } else {
    Serial.println("O servidor web nao sera configurado por erro na conexao do wifi.");
  }
  return resultado;
}

//========================================
String listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  String resultado = "";
  Serial.printf("Listing directory: %s\r\n", dirname);
  resultado += "<br>Listing directory: ";
  resultado += dirname;
  File root = fs.open(dirname);
  if(!root){
    Serial.println("- failed to open directory");
    resultado += "- failed to open directory<br>";
    return resultado;
  }
  if(!root.isDirectory()){
    Serial.println(" - not a directory");
    resultado += " - not a directory<br>";
    return resultado;
  }
  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      resultado += "<br> DIR: ";
      resultado += file.name();
      Serial.println(file.name());
      if(levels){
          resultado += listDir(fs, file.path(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      resultado += "<br> FILE: ";
      resultado += file.name();
      Serial.print(file.name());

      Serial.print("\tSIZE: ");
      resultado += " SIZE:";
      resultado += file.size();
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
  Serial.println("");
  return resultado;
}

//========================================
String f_idPlaca(){
  uint16_t vI_chipID = 0;
	for(int i=0; i<17; i=i+8) {
	  vI_chipID |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}
  vS_mqttIdUnico = String(vI_chipID);
	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: "); 
  Serial.println(vI_chipID);
  String msg = "ESP32 Chip model = ";
  msg += ESP.getChipModel();
  msg += " Rev ";
  msg += ESP.getChipRevision();
  msg += "<br>This chip has cores ";
  msg += ESP.getChipCores();
  msg += "<br>Chip ID: ";
  msg += vI_chipID;
  return msg;
}

//========================================
void f_modoAP(String wifi, String senha, uint16_t portaap) {
  WiFi.disconnect();
  Serial.println("Entrando em modo AP... ");
  delay(1000);
  WiFi.softAP(wifi.c_str(), senha.c_str());
  SERVIDOR_WEB.begin(portaap);
  SERVIDOR_WEB.on("/wifiinicio", f_handle_ConfiguraWifiInicio);
  SERVIDOR_WEB.onNotFound(f_handle_NotFound);
  Serial.println("Servidor HTTP iniciado.");
  Serial.print("Conecte seu wifi na rede ["+wifi+"] e acesse http://");
  Serial.print(WiFi.softAPIP());
  Serial.print(":");
  Serial.print(portaap);
  Serial.println("/wifiinicio pelo navegador para configurar o SSID e SENHA na placa "+vS_nomeDispositivo);
  while (1) {
    SERVIDOR_WEB.handleClient();
    if (vB_finalizaModoAP) {
      Serial.println("Saindo do modo AP da placa "+vS_nomeDispositivo);
      delay(10000);
      ESP.restart();
    }
    delay(2);
  }
  Serial.println(" OK");
}

//========================================
void f_cria_MDNS(String nome, IPAddress ip, uint16_t porta) {
  Serial.print("Configurando mDNS: ");
  if (!MDNS.begin(nome.c_str())) {
    Serial.println("ERRO");
  } else {
    MDNS.addService("_http", "_tcp", porta);
    Serial.println("OK");
  }
}

//========================================
void f_config_NTP() {
  Serial.print("Configurando NTP: ");
  sntp_set_time_sync_notification_cb( timeavailable );
  sntp_servermode_dhcp(1);
  configTime(3600, 3600, vS_ntpServer1.c_str(), vS_ntpServer2.c_str());
  configTzTime(vS_timeZone.c_str(), vS_ntpServer1.c_str(), vS_ntpServer2.c_str());
  Serial.println("OK");
}

//========================================
void timeavailable(struct timeval *t) {
  // Callback function (get's called when time adjusts via NTP)
  Serial.println("Obtive ajuste de tempo do NTP!!");
}

//========================================
bool f_atualizaHora() {
  bool resultado = false;  
  uint64_t agora = millis();
  if ((agora - hora_lasttime) > 1000) {  
    resultado = getLocalTime(&timeinfo);
    if(!resultado){
      Serial.println("Hora ainda nao ajustada.");
    }
    hora_lasttime = agora;
  }  
  return resultado;  
}

//========================================
uint8_t  f_configuraWIFI() {
  f_carregaConfi("REDE",false);
  if (WiFi.status() != WL_CONNECTED) {
    if (vS_nomeDispositivo.length() > 1) {
      WiFi.setHostname(vS_nomeDispositivo.c_str());
    }
    WiFi.setAutoReconnect(true);
    WiFi.setAutoConnect(true);
    WiFi.begin(vS_nomeWifi.c_str(), vS_senhaWifi.c_str());
    int cont = 1;
    while (WiFi.status() != WL_CONNECTED) {
      delay(5000);
      Serial.print("Conectando ao WiFi, status ");
      Serial.print(WiFi.status());
      Serial.print(" ");
      Serial.print(" tentativa ");
      Serial.print(cont);
      Serial.print(" de ");
      Serial.println(vU8_tentativaConexoes);
      cont++;
      if (cont > vU8_tentativaConexoes) {
        break;
      }
    }
    Serial.print("Endereço IP do WIFI: ");
    Serial.print(WiFi.localIP().toString());
    Serial.print(" Hostname: ");
    Serial.print(vS_nomeDispositivo+" ");
    if ( WiFi.status() == 3) {
      Serial.println(" OK");
      if (vB_emExecucao) {
        f_configuraWEB();
      }
    } else {
      Serial.print(" ERRO - Informacoes usadas no WIFI: ");
      String passwdw = "";
      for (uint8_t x=0; x<=vS_senhaWifi.length(); x++){
        passwdw += "*";
      }
      Serial.println("Hostname:"+vS_nomeDispositivo+" SSID:"+vS_nomeWifi+" Senha:"+passwdw);
    }
  } else {
    Serial.println("O Wifi ja esta conectado !");
  }
  if (WiFi.status() == 3) {
    f_cria_MDNS(vS_nomeDispositivo, WiFi.localIP(), vU16_portaWeb);
    f_config_NTP();
  } else if (vB_modoAP && WiFi.status() != 3 && !vB_emExecucao) {
    f_modoAP(vS_nomeAP_Wifi, vS_senhaAP_Wifi, vU16_portaWeb);
  }  
  return  WiFi.status();
}
