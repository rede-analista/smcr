#include "include.h"
#include "globals.h"

//========================================
void fV_mapaFuncoes() {
    // Mapeia função sem parâmetros
    mapaFuncoesSemParam["fV_salvarFlash"] = fV_salvarFlash;
    mapaFuncoesSemParam["fV_restart"] = fV_restart;
    mapaFuncoesSemParam["fV_mudaExec"] = fV_mudaExec;
    mapaFuncoesSemParam["fV_restartTasks"] = fV_restartTasks;
    mapaFuncoesSemParam["fV_formataFLASH"] = fV_formataFLASH;

    // Mapeia função com AsyncWebServerRequest*
    mapaFuncoesComParam["f_handle_OTA"] = f_handle_OTA;
    mapaFuncoesComParam["fV_iniciaPinos"] = fV_iniciaPinos;
    mapaFuncoesComParam["fV_iniciaAcoes"] = fV_iniciaAcoes;
    mapaFuncoesComParam["fV_configuraModulos"] = fV_configuraModulos;
    mapaFuncoesComParam["fV_grupoAcoes"] = fV_grupoAcoes;
    mapaFuncoesComParam["fV_configuraWatchDog"] = fV_configuraWatchDog;

}

//========================================
void fV_recebeDados(AsyncWebServerRequest *request) {
/*
 Argumento 0 = Nome do Dispositivo
 Argumento 1 = Acao
 Argumento 2 = Numero do Pino
 Argumento 3 = Status do Pino
*/
  vS_uri = request->url();
  if (request->args() == 4) {
    if (ULTIMOS_GET_RECEBIDOS.length() > 260) {
      ULTIMOS_GET_RECEBIDOS = "";
    }
    vS_payrec = vS_uri + "?" + request->argName(0) + "=" + request->arg((size_t)0) + "&" + request->argName(1) + "=" + request->arg(1) + "&" + request->argName(2) + "=" + request->arg(2) + "&" + request->argName(3) + "=" + request->arg(3);
    ULTIMOS_GET_RECEBIDOS += fS_DataHora();
    ULTIMOS_GET_RECEBIDOS += " -> ";
    ULTIMOS_GET_RECEBIDOS += vS_payrec;
    ULTIMOS_GET_RECEBIDOS += "<br><br>";
    String validacao = "_SEM_DADOS_";
    vU16_ulimoModRecebido = fI_retornaModulo(request->arg((size_t)0));
    if ( vU16_ulimoModRecebido < vU8_totModulos) {
      Serial.println("Recebido dados da placa " + request->arg((size_t)0));
      switch (request->arg(1).toInt()) {
        case 0: // Parametro acao = 0(Nenhuma)
          aI16_ControlHS[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
          aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = request->arg(3).toInt();
          validacao = "OK_DADO_RECEBIDO";
          break;
        case 65534: // Parametro acao = 65534(status)
          aI16_ControlHS[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
          aI16_ControlHS[1][fU8_retornaIndiceHS(request->arg((size_t)0))] = request->arg(3).toInt();
          aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = request->arg(3).toInt();
          vB_envia_Historico = true;
          validacao = "OK_DADO_RECEBIDO";
          break;
        case 65535: // Parametro acao = 65535(sincronismo)
          aI16_ControlHS[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
          aI16_ControlHS[1][fU8_retornaIndiceHS(request->arg((size_t)0))] = request->arg((size_t)0).toInt();
          aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = aI16_ControlHS[1][fU8_retornaIndiceHS(request->arg((size_t)0))];
          validacao = "OK_DADO_RECEBIDO";
          break;
        default:
          aI16_ControlHS[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
          aI16_ControlHS[1][fU8_retornaIndiceHS(request->arg((size_t)0))] = 0;
          aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = request->arg(3).toInt();
          validacao = "OK_DADO_RECEBIDO";
          break;
      }
      Serial.println("Acao/Indice/Status " + request->arg(1) + " " + request->arg(2) + " " + request->arg(3));
      request->send(200, "text/plain", validacao);
    } else {
      Serial.println("Rejeitado dados da placa " + request->arg((size_t)0));
      Serial.println("Acao/Indice/Status " + request->arg(1) + " " + request->arg(2) + " " + request->arg(3));
      request->send(401, "text/plain", "ERRO - PLACA NAO CADASTRADA\n");
    }
  } else {
    Serial.println("Erro dados da placa " + request->arg((size_t)0));
    Serial.println("Acao/Indice/Status " + request->arg(1) + " " + request->arg(2) + " " + request->arg(3));
    request->send(400, "text/plain", "ERRO - PARAMETROS INVALIDOS\n");
  }
}

//========================================
uint8_t fU8_retornaIndiceHS(String modulo) {
  uint8_t resultado = 0;
  for (uint8_t x=0; x<vU8_totModulos; x++) {
    if (aS_InterMod[0][x] == modulo) {
      resultado = x;
    }
  }
  return resultado;
}

//========================================
int fI_retornaModulo(String modulo) {
  int resultado = vU8_totModulos+1;
  if (modulo.length() > 0) {
    for (int x=0; x<vU8_totModulos; x++) {
      if (modulo == aS_InterMod[0][x]) {
        resultado = x;
        break;
      }
    }
  }
  return resultado;
}

//========================================
void fV_checkHandShake() {
  uint64_t agora = millis();
  if (!vB_pausaEXECs && vB_exec_Modulos) {
    if ((agora - check_mod_lasttime) > vU16_modulos_HandShake) {
      for (uint8_t y=0; y<vU8_totPinos; y++) {
        if (aI16_ControlHS[0][y] < 1) {
          aI16_ControlHS[1][y] = 1;
          //vB_envia_Historico = true;
        } else {
          aI16_ControlHS[0][y]--;
        }
        if ( aB_InterMod[0][y] && aU16_InterMod[0][y] > 0 ) {
          aI16_ControlHS[2][y] = fI_enviaModulo(aU16_InterMod[0][y],"65535", String(aU16_InterMod[0][fU8_retornaIndiceHS(vS_nomeDispositivo)]), "0");
          if (aI16_ControlHS[2][y] == 200) {
            aI16_ControlHS[0][y] = vI_cicloHandshake;
            aI16_ControlHS[1][y] = 0;
            aI16_ControlHS[3][fI_retornaModulo(vS_nomeDispositivo)] = 0;
          }
        }
        if ( fU16_retornaIndicePino(aU16_InterMod[0][y]) > 0 && fU16_retornaIndicePino(aU16_InterMod[0][y]) < 65535 ) {
          aU16_Pinos_Status[0][fU16_retornaIndicePino(aU16_InterMod[0][y])] = aI16_ControlHS[1][y];
        }
      }
      check_mod_lasttime = agora;
    }
  }
}

//========================================
String fS_retornaIpModulo(uint16_t modulo) {
  String resultado = "";
  if (modulo > 0) {
    for (int x=0; x<vU8_totModulos; x++) {
      if (modulo == aU16_InterMod[0][x]) {
        resultado = aS_InterMod[1][x]; //f_formataIp(aS_InterMod[1][x]);
        break;
      }
    }
  }
  return resultado;
}

//========================================
uint16_t fU16_retornaIndiceModulo(uint16_t modulo) {
  int resultado = 0;
  if (modulo > 0) {
    for (int x=0; x<vU8_totModulos; x++) {
      if (modulo == aU16_InterMod[0][x]) {
        resultado = x;
        break;
      }
    }
  }
  return resultado;
}

//========================================
int fI_enviaModulo(uint16_t idmodulo, String acao, String pino, String valor) {
  vI_httpResponseCode = 0;
  int resposta = 504;
 if (aI16_ControlHS[3][fU16_retornaIndiceModulo(idmodulo)] < vU8_tentativaConexoes) {
    if (WiFi.status() != WL_CONNECTED) {
        fU8_configuraWifi();
    } else {
      if (CLIENTE_WEB_ASYNC != nullptr) {
        delete CLIENTE_WEB_ASYNC;
        CLIENTE_WEB_ASYNC = nullptr;
      }
      if (!request_in_progress) {
        request_in_progress = true;
        String GET_SERVIDOR;
        if (aU16_InterMod[1][fU16_retornaIndiceModulo(idmodulo)] > 0) {
            GET_SERVIDOR = "http://" + fS_retornaIpModulo(idmodulo) + ":" + aU16_InterMod[1][fU16_retornaIndiceModulo(idmodulo)] +
                           "/dados?pl=" + vS_nomeDispositivo + "&ac=" + acao + "&pn=" + pino + "&vl=" + valor;
        } else {
          GET_SERVIDOR = "http://" + fS_retornaIpModulo(idmodulo) + ":" + vI_U16_portaWebAsync +
                        "/dados?pl=" + vS_nomeDispositivo + "&ac=" + acao + "&pn=" + pino + "&vl=" + valor;
        }
        if (!CLIENTE_WEB_ASYNC) {
          CLIENTE_WEB_ASYNC = new asyncHTTPrequest;
        }
        // Configura a requisição
        if (ULTIMOS_GET_SERVIDOR.length() > 260) {
          ULTIMOS_GET_SERVIDOR = "";
        }
          ULTIMOS_GET_SERVIDOR += fS_DataHora();
          ULTIMOS_GET_SERVIDOR += " -> ";
          ULTIMOS_GET_SERVIDOR += GET_SERVIDOR;
          ULTIMOS_GET_SERVIDOR += "<br><br>";
         CLIENTE_WEB_ASYNC->open("GET", GET_SERVIDOR.c_str());
        // Captura de variáveis para a lambda
         uint16_t moduloIdx = fU16_retornaIndiceModulo(idmodulo);
        // Define o callback para quando a resposta for recebida
        CLIENTE_WEB_ASYNC->onReadyStateChange([=](void* optParm, asyncHTTPrequest* req, int readyState) {
            if (readyState == 4) {  // Use o valor inteiro diretamente
              int statusCode = req->responseHTTPcode();
              String payload = req->responseText();
              // Armazena o código da resposta e o payload
              vI_httpResponseCode = statusCode;
              vS_payload = payload;
              if (statusCode == 200 && payload == "OK_DADO_RECEBIDO") {
                // Atualiza o controle do handshake
                aI16_ControlHS[0][moduloIdx] = vI_cicloHandshake;
                aI16_ControlHS[1][moduloIdx] = 0;
                aI16_ControlHS[2][moduloIdx] = statusCode;
                aI16_ControlHS[3][moduloIdx] = 0;
                vU8_ultimoModEnviado = idmodulo;
              } else {
                  aI16_ControlHS[2][moduloIdx] = statusCode;
                  aI16_ControlHS[3][moduloIdx] = (aI16_ControlHS[3][moduloIdx] < 32766) 
                                                  ? aI16_ControlHS[3][moduloIdx] + 1 
                                                  : 1;
              }
              fV_imprimeSerial("HTTP Response code: " + String(statusCode));
              fV_imprimeSerial("Payload: " + payload);
            }
        }, nullptr);  // Passar nullptr como argumento para a lambda
        CLIENTE_WEB_ASYNC->send();  // Envia a requisição assíncrona
        fV_imprimeSerial("Enviado: " + GET_SERVIDOR);
        request_in_progress = false;
      } else {
        fV_imprimeSerial("Aguardando envio de informacoes");
      }
    }
  } 
  return resposta;
}

//========================================
void fV_enviaAcoesModulos() {
  uint64_t agora = millis();
  if (!vB_pausaEXECs && vB_exec_Modulos) {
    if ((agora - envia_acoes_mod_lasttime) > (vU16_modulos_MTBS_Acoes+500)) {
      for (uint8_t x=0; x<vU8_totPinos; x++) {
        if (aU16_ControlMsgModHist[0][x] > 0) {
          if ( fI_enviaModulo(aU16_ControlMsgModHist[0][x], String(aU16_ControlMsgModHist[1][x]), String(aU16_ControlMsgModHist[2][x]), String(aU16_ControlMsgModHist[3][x])) == 200) {
            aU16_ControlMsgModHist[0][x] = 0;
            aU16_ControlMsgModHist[1][x] = 0;
            aU16_ControlMsgModHist[2][x] = 0;
            aU16_ControlMsgModHist[3][x] = 0;
          }
        }
      }
      envia_acoes_mod_lasttime = agora;
    }
  }
}

//========================================
void fV_restartTasks() {
  fV_imprimeSerial("As tarefas serao reiniciadas.");
  aB_restartRotinas[0] = 1; // Reinicia task Pinos
  aB_restartRotinas[1] = 1; // Reinicia task tarefas 1
  aB_restartRotinas[2] = 1; // Reinicia task tarefas 2
  aB_restartRotinas[3] = 1; // Reinicia task tarefas 3
  aB_restartRotinas[4] = 1; // Reinicia task tarefas 4
}

//========================================
void fV_mudaExec() {
  vB_pausaEXECs = !vB_pausaEXECs;
  if (vB_pausaEXECs) {
    fV_imprimeSerial("A execucao das rotinas foi pausada.");
  } else {
    fV_imprimeSerial("A execucao das rotinas foi retomada.");
  }
}

//========================================
void fV_Preference(String op, bool force) {
  fV_imprimeSerial("Iniciando configuracao de parametros...", false);
  if (op == "L") {
    fV_carregaFILESYS_AS2D("/aS_Preference.txt",aS_Preference,vI8_aS_Preference_ROW,vI8_aS_Preference_COL);
  } else if (op == "E") {
    fV_salvaFILESYS_AS2D("/aS_Preference.txt",aS_Preference,vI8_aS_Preference_ROW,vI8_aS_Preference_COL);
  }
  fV_imprimeSerial(" OK");
}

//========================================
bool fB_verificaPrimeiraExec(bool force) {
  bool resultado = false; // Inicialmente, assume que nem todos os arquivos existem
  int arquivosExistentes = 0; // Contador para arquivos existentes
  int totalArquivos = 13;
  fV_imprimeSerial("Verificando arquivos de configuracao...");
  String aS_checkFiles[totalArquivos] = {
      "aU8_diasDaSemana", "aU8_meses", "aS16_PinosMenu", "aS8_AcoesMenu", 
      "aS8_AcoesStringMenu", "aS8_AcoesRedeMenu", "aS_InterModMenu",
      "aU16_InterModMenu", "aSB_InterModMenu", "aS16_InterModHA", "aS8_ControlMsgModHist",
      "nulo","aS_Preference" };

  // Percorre cada arquivo do array
  for (uint8_t i = 0; i < totalArquivos; i++) {
      String fileName = "/" + aS_checkFiles[i] + ".txt"; // Adiciona extensão .txt ao nome do arquivo
      bool fileExists = FILESYS.exists(fileName); // Verifica se o arquivo existe
      // Se o arquivo não existir ou se "force" for verdadeiro, recria o arquivo
      fV_imprimeSerial("Verificando arquivo: "+ String(i) + " - " + fileName);
      if (!fileExists || force) {
          fV_imprimeSerial("Recriando arquivo: " + fileName);
          File file = FILESYS.open(fileName, FILE_WRITE);
         if (file) {
              String defaultValues;
             // Define os valores padrão para cada arquivo baseado no nome
              if (aS_checkFiles[i] == "aU8_diasDaSemana") {
                  defaultValues = "Domingo,Segunda,Terça,Quarta,Quinta,Sexta,Sábado";
              } else if (aS_checkFiles[i] == "aU8_meses") {
                  defaultValues = "Janeiro,Fevereiro,Março,Abril,Maio,Junho,Julho,Agosto,Setembro,Outubro,Novembro,Dezembro";
              } else if (aS_checkFiles[i] == "aS16_PinosMenu") {
                  defaultValues = "Pino,Tipo,pinMode(),XoR,Nível Acionamento,Tempo Retenção";
              } else if (aS_checkFiles[i] == "aS8_AcoesMenu") {
                  defaultValues = "Pino Origem,Pino Destino,Ação,Tempo ON,Tempo OFF,Pino Destino Remoto (máscara)";
              } else if (aS_checkFiles[i] == "aS8_AcoesStringMenu") {
                  defaultValues = "Classe MqTT,Ícone_MqTT";
              } else if (aS_checkFiles[i] == "aS8_AcoesRedeMenu") {
                  defaultValues = "Envia Para Módulo,Envia Telegram,Notifica Assistentes,Envia MqTT";
              } else if (aS_checkFiles[i] == "aS_InterModMenu") {
                  defaultValues = "Nome,IP";
              } else if (aS_checkFiles[i] == "aU16_InterModMenu") {
                  defaultValues = "ID-Pino HandShake,Porta do Receptor";
              } else if (aS_checkFiles[i] == "aSB_InterModMenu") {
                  defaultValues = "Enviar Handshake";
              } else if (aS_checkFiles[i] == "aS16_InterModHA") {
                  defaultValues = "Ciclo,Status,CTRL Resposta,Envio Pausado";
              } else if (aS_checkFiles[i] == "aS8_ControlMsgModHist") {
                  defaultValues = "Módulo,Ação,Pino,Valor";
              } else if (aS_checkFiles[i] == "nulo") {
                  defaultValues = "";
              } else if (aS_checkFiles[i] == "aS_Preference") {
                  defaultValues = String("wifi,") + //0
                                  String("12345678,") + //1
                                  String("4,") + //2
                                  String("8080,") + //3
                                  String("esp32modularx,") + //4
                                  String("admin,") + //5
                                  String("admin,") + //6
                                  String("esp32modularx Ponto de Acesso,") + //7
                                  String("senha12345678,") + //8
                                  String("true,") + //9
                                  String("pool.ntp.br,") + //10
                                  String("pool.ntp.org,") + //1
                                  String("<-03>3,") + //12
                                  String("Tomato,") + //13
                                  String("LightGreen,") + //14
                                  String("false,") + //15
                                  String(":,") + //16
                                  String("-,") + //17
                                  String("@,") + //18
                                  String("65535,") + //19
                                  String("false,") + //20
                                  String("pubsub,") + //21
                                  String("10.10.10.10,") + //22
                                  String("usr,") + //23
                                  String("123,") + //24
                                  String("65535,") + //25
                                  String("65535,") + //26
                                  String("1833,") + //27
                                  String("false,") + //28
                                  String("65535,") + //29
                                  String("caixas,") + //30
                                  String("caixas,") + //31
                                  String("pt_br,") + //32
                                  String("Alerta para,") + //33
                                  String("Normalização para,") + //34
                                  String("false,") + //35
                                  String("65535,") + //36
                                  String("65535,") + //37
                                  String("10,") + //38
                                  String("15,") + //39
                                  String("7,") + //40
                                  String("120,") + //41
                                  String("80,") + //42
                                  String("false,") + //43
                                  String("300000000") + //44
                                  String("12") + //45
                                  String("8") + //46
                                  String("5") + //47
                                  String("false") + //48
                                  String("0") + //49
                                  String("0") + //50 sem uso
                                  String("0") + //51 sem uso
                                  String("0") + //52 sem uso
                                  String("0") + //53 sem uso
                                  String("0") + //54 sem uso
                                  String("0") + //55 sem uso
                                  String("0") + //56 sem uso
                                  String("0") + //57 sem uso
                                  String("0") + //58 sem uso
                                  String("0"); //59 sem uso
              }
             // Escreve os valores padrões no arquivo
              file.println(defaultValues);
              file.close();
              fV_imprimeSerial("Arquivo recriado: " + fileName);
          } else {
              fV_imprimeSerial("Erro ao criar arquivo: " + fileName);
          }
      } else {
          // Se o arquivo existe, incrementa o contador
          arquivosExistentes++;
      }
  }

  // Se todos os 11 arquivos existem, define resultado como true
  if (arquivosExistentes == totalArquivos) {
      resultado = true;
  }
  fV_imprimeSerial("Verificação de arquivos finalizada.");
  return resultado;
}

//========================================
bool fV_regModHist(uint16_t idmodulo, uint16_t acao, uint16_t pino, uint16_t valor) {
  aU16_ControlMsgModHist[0][vU8_crtl_ModHist] = idmodulo;
  aU16_ControlMsgModHist[1][vU8_crtl_ModHist] = acao;
  aU16_ControlMsgModHist[2][vU8_crtl_ModHist] = pino;
  aU16_ControlMsgModHist[3][vU8_crtl_ModHist] = valor;
  vU8_crtl_ModHist++;
  if (vU8_crtl_ModHist >= vU8_totPinos) {
    vU8_crtl_ModHist = 0;
  }
  return true;
}

//========================================
void fV_checkAcoesModulos() {
  uint64_t agora = millis();
  if (!vB_pausaEXECs && vB_exec_Modulos) {
    if ((agora - check_acoes_mod_lasttime) > vU16_modulos_MTBS_Acoes) {
      for (uint8_t x=0; x<vU8_totPinos; x++) {
        if ((aU8_AcaoRede1[0][x] > 0 ) && (aU16_Pinos_Status[0][x] >= aU16_Pinos[4][x]) && (aU16_ControlMsgMod[0][x] < 1)) {
          if (fV_regModHist(aU8_AcaoRede1[0][x],aU16_Acao1[2][x], aU16_Acao1[5][x], aU16_Pinos_Status[0][x])) {
            aU16_ControlMsgMod[0][x] = 1;
          }
        } else if ((aU8_AcaoRede1[0][x] >0 ) && (aU16_Pinos_Status[0][x] < aU16_Pinos[4][x]) && (aU16_ControlMsgMod[0][x] > 0)) {
          if (fV_regModHist(aU8_AcaoRede1[0][x],aU16_Acao1[2][x], aU16_Acao1[5][x], aU16_Pinos_Status[0][x])) {
            aU16_ControlMsgMod[0][x] = 0;
          }
        } else if (vB_envia_Historico && (aU8_AcaoRede1[0][x] >0)){
          fV_regModHist(aU8_AcaoRede1[0][x],aU16_Acao1[2][x], aU16_Acao1[5][x], aU16_Pinos_Status[0][x]);
        }


        if ((aU8_AcaoRede2[0][x] >0 ) && (aU16_Pinos_Status[0][x] >= aU16_Pinos[4][x]) && (aU16_ControlMsgMod[1][x] < 1)) {
          if (fV_regModHist(aU8_AcaoRede2[0][x],aU16_Acao2[2][x], aU16_Acao2[5][x], aU16_Pinos_Status[0][x])) {
            aU16_ControlMsgMod[1][x] = 1;
          }
        } else if ((aU8_AcaoRede2[0][x] >0 ) && (aU16_Pinos_Status[0][x] < aU16_Pinos[4][x]) && (aU16_ControlMsgMod[1][x] > 0)){
          if (fV_regModHist(aU8_AcaoRede2[0][x],aU16_Acao2[2][x], aU16_Acao2[5][x], aU16_Pinos_Status[0][x])) {
            aU16_ControlMsgMod[1][x] = 0;
          }
        } else if (vB_envia_Historico && (aU8_AcaoRede2[0][x] >0)){
          fV_regModHist(aU8_AcaoRede2[0][x],aU16_Acao2[2][x], aU16_Acao2[5][x], aU16_Pinos_Status[0][x]);
        }


        if ((aU8_AcaoRede3[0][x] >0 ) && (aU16_Pinos_Status[0][x] >= aU16_Pinos[4][x])&& (aU16_ControlMsgMod[2][x] < 1)) {
          if (fV_regModHist(aU8_AcaoRede3[0][x], aU16_Acao3[2][x], aU16_Acao3[5][x], aU16_Pinos_Status[0][x])) {
            aU16_ControlMsgMod[2][x] = 1;
          }
        } else if ((aU8_AcaoRede3[0][x] >0 ) && (aU16_Pinos_Status[0][x] < aU16_Pinos[4][x]) && (aU16_ControlMsgMod[2][x] > 0)){
          if (fV_regModHist(aU8_AcaoRede3[0][x], aU16_Acao3[2][x], aU16_Acao3[5][x], aU16_Pinos_Status[0][x])) {
            aU16_ControlMsgMod[2][x] = 0;
          }
        } else if (vB_envia_Historico && (aU8_AcaoRede3[0][x] >0)){
          fV_regModHist(aU8_AcaoRede3[0][x],aU16_Acao3[2][x], aU16_Acao3[5][x], aU16_Pinos_Status[0][x]);
        }
      }
      vB_envia_Historico = false;
      check_acoes_mod_lasttime = agora;
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
template<typename T>
struct VariableSetter {
    static void set(T& variable, const String& value);
};

// Especializações para cada tipo
template<>
struct VariableSetter<String> {
    static void set(String& variable, const String& value) {
        variable = value;
    }
};

template<>
struct VariableSetter<uint8_t> {
    static void set(uint8_t& variable, const String& value) {
        variable = static_cast<uint8_t>(value.toInt());
    }
};

template<>
struct VariableSetter<uint16_t> {
    static void set(uint16_t& variable, const String& value) {
        variable = static_cast<uint16_t>(value.toInt());
    }
};

template<>
struct VariableSetter<uint32_t> {
    static void set(uint32_t& variable, const String& value) {
        variable = static_cast<uint32_t>(value.toInt());
    }
};

template<>
struct VariableSetter<uint64_t> {
    static void set(uint64_t& variable, const String& value) {
        variable = static_cast<uint64_t>(value.toInt());
    }
};

template<>
struct VariableSetter<int16_t> {
    static void set(int16_t& variable, const String& value) {
        variable = static_cast<int16_t>(value.toInt());
    }
};

template<>
struct VariableSetter<bool> {
    static void set(bool& variable, const String& value) {
        variable = (value == "true");
    }
};

template<typename T>
void registerVariable(const String& name, T& variable) {
    VarType type;

    // Determinar o tipo
    if (std::is_same<T, String>::value) {
        type = VarType::STRING;
    } else if (std::is_same<T, uint8_t>::value) {
        type = VarType::UINT8;
    } else if (std::is_same<T, uint16_t>::value) {
        type = VarType::UINT16;
    } else if (std::is_same<T, uint32_t>::value) {
        type = VarType::UINT32;
    } else if (std::is_same<T, uint64_t>::value) {
        type = VarType::UINT64;
    } else if (std::is_same<T, int16_t>::value) {
        type = VarType::INT16;
    } else if (std::is_same<T, bool>::value) {
        type = VarType::BOOL;
    }

    variables[name] = Variable{
        .setter = [&variable](String value) {
            VariableSetter<T>::set(variable, value); // Usar a especialização para setar
        },
        .type = type
    };
}

//========================================
VarType getVariableType(const String& varName) {
    auto it = variables.find(varName);
    if (it != variables.end()) {
        return it->second.type;
    }
    return VarType::UNKNOWN; // Nome da variável inválido
}

//========================================
bool setVariable(const String& varName, const String& value) {
    auto it = variables.find(varName);
    if (it != variables.end()) {
        it->second.setter(value);
        variables.erase(varName);  // Remove a variável do mapa após a alteração
        return true;
    }
    return false; // Nome da variável inválido
}

//========================================
void fV_handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        String message = String((char*)data).substring(0, len); // Converte os dados para string

        if (message.startsWith("SET_VAR ")) {
            int spaceIndex = message.indexOf(' ', 8);
            if (spaceIndex > 0) {
                String varName = message.substring(8, spaceIndex);  
                String value = message.substring(spaceIndex + 1);

                //registerVariable(varName, VB_mostra_Status);

                if (setVariable(varName, value)) {
                    fV_imprimeSerial("Variavel alterada e removida: " + varName + " = " + value);
                } else {
                    fV_imprimeSerial("Nome da variavel invalido: " + varName);
                }
            }
        } else if (message.startsWith("GET_TYPE ")) {
            int spaceIndex = message.indexOf(' ', 9);
            if (spaceIndex > 0) {
                String varName = message.substring(9, spaceIndex);
                VarType type = getVariableType(varName);
                
                switch (type) {
                    case VarType::STRING: fV_imprimeSerial(varName + " e do tipo STRING"); break;
                    case VarType::UINT8: fV_imprimeSerial(varName + " e do tipo UINT8"); break;
                    case VarType::UINT16: fV_imprimeSerial(varName + " e do tipo UINT16"); break;
                    case VarType::UINT32: fV_imprimeSerial(varName + " e do tipo UINT32"); break;
                    case VarType::UINT64: fV_imprimeSerial(varName + " e do tipo UINT64"); break;
                    case VarType::INT16: fV_imprimeSerial(varName + " e do tipo INT16"); break;
                    case VarType::BOOL: fV_imprimeSerial(varName + " e do tipo BOOL"); break;
                    default: fV_imprimeSerial(varName + " tem tipo desconhecido"); break;
                }
            }
        } else {
            fV_imprimeSerial(message); // Se não for um comando "SET", apenas imprime na Serial
        }
    }
}

//========================================
void fV_onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
      fV_sendSerialData("Conectado WebSocket Serial!");
  } else if (type == WS_EVT_DISCONNECT) {

  } else if (type == WS_EVT_DATA) {
      fV_handleWebSocketMessage(arg, data, len);
  }
}

//========================================
void fV_sendSerialData(String message) {
  if (vB_emExecucaoWS) {
    if (message.length() > 0) {
        ws->textAll(message);
    }
  }
}

//========================================
void fV_gravaPino(uint16_t tipo, uint16_t pino, uint16_t valor) {
  if (tipo == 1) {
    digitalWrite(pino,valor);
  } else if (tipo == 192) {
    analogWrite(pino, valor);
  }
}

//========================================
bool fB_retornaStatusGrupoAcao(String pinos, uint8_t status) {
  bool resultado = false;
  String xpin = "";
  int xstat = 0;
  for (int x=0; x<=pinos.length();x++) {
    if (pinos[x] == 44) {
      xstat += aU16_Pinos_Status[0][fU16_retornaIndicePino(xpin.toInt())];
      xpin = "";
    } else {
      xpin += pinos[x];
    }
  }
  xstat += aU16_Pinos_Status[0][fU16_retornaIndicePino(xpin.toInt())];
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
String fS_retornaGrupoAcao(uint16_t pino) {
  String resultado = "";
  int cont = 0;
  for (uint16_t x=1; x<vI8_ControlAcoesGroups; x++){ 
    if (aU16_ControlAcoesGroups[x][fU16_retornaIndicePino(pino)] >0 ) {
      resultado += String(aU16_ControlAcoesGroups[x][fU16_retornaIndicePino(pino)]);
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
uint16_t fU16_lePino(uint16_t tipo, uint16_t invert, uint16_t pino) {
  uint16_t resultado = aU16_Pinos_Status[0][fU16_retornaIndicePino(pino)];
  if (tipo == 1) {
    resultado = invert ^ digitalRead(pino);
  } else if (tipo == 192) {
    resultado = analogRead(pino);
  }
  return resultado;
}

//========================================
String fS_traduzAcoes(uint16_t cod) {
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
    case 65534:
      resultado = "STATUS_REMOTO";
      break;      
  }
  return resultado;
}

//========================================
uint16_t fU16_retornaIndicePino(uint16_t pino) {
  uint16_t resultado = 65535;
  for (uint8_t x=0; x<vU8_totPinos; x++) {
    if (aU16_Pinos[0][x] == pino) {
      resultado = x;
    }
  }
  return resultado;
}

//========================================
bool fB_atualizaHora() {
  bool resultado = false;  
  if (!vB_pausaEXECs) {
    static uint64_t hora_lasttime = 0;  // Variável local estática para manter o último tempo
    uint64_t agora = millis();
    if ((agora - hora_lasttime) > 120000) {  // Se já se passou mais de 1 minuto
        resultado = getLocalTime(&timeinfo);  // Atualiza a hora
        if (!resultado) {
            fV_imprimeSerial("Hora ainda nao ajustada.");
        }
        hora_lasttime = agora;  // Atualiza o último tempo da execução
    }
  }
  return resultado;  
}

//========================================
void fV_grupoAcoes(bool force) {
  // Zerar array de grupo de acoes
  fV_imprimeSerial("Iniciando formacoes de grupos de acoes...");
  if (force) {
    for (uint8_t i = 0; i < vI8_ControlAcoesGroups; i++) {
      for (uint8_t j = 0; j < vU8_totPinos; j++) {
        aU16_ControlAcoesGroups[i][j] = 0;
      }
    }
    for (uint8_t x = 0; x < vU8_totPinos; x++) {
      if (aU16_Pinos[0][x] > 0) {
        aU16_ControlAcoesGroups[0][x] = aU16_Pinos[0][x];
      }
    }
  }

  // Inicia em 1 pq 0 significa pino nao cadastrado
  int xyz = 1;

  fV_imprimeSerial("Formando grupo acoes1: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < vU8_totPinos; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < vU8_totPinos; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao1[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao1[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(xyz-1);

  fV_imprimeSerial("Formando grupo acoes2: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < vU8_totPinos; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < vU8_totPinos; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao2[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao2[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(xyz-1);

  fV_imprimeSerial("Formando grupo acoes3: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < vU8_totPinos; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < vU8_totPinos; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao3[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao3[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(xyz-1);

  fV_imprimeSerial("Formando grupo acoes4: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < vU8_totPinos; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < vU8_totPinos; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao4[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao4[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(xyz-1);  
  fV_imprimeSerial("Formacao de grupos de acoes finalizado.");
}

//========================================
void fV_restart() {
    fV_imprimeSerial("Reiniciando o modulo ",false);
    fV_imprimeSerial(vS_nomeDispositivo);
    delay(20000);
    esp_restart();
}

//========================================
void fV_formataFLASH () {
    fV_imprimeSerial("Particao NVS sendo formatada, todas as informacoes serão perdidas...",false);
    fV_apagaTodosArquivosSPIFFS();
    nvs_flash_erase(); //apague a partição NVS
    nvs_flash_init(); //inicializa a partição NVS
    fV_imprimeSerial(" OK");
}

//========================================
uint64_t fU64_stringToULong64(const String& str) {
    return strtoull(str.c_str(), nullptr, 10);
}

//========================================
void fV_configuraWatchDog(const bool force) {
    if (vB_exec_WatchDog || force) {
        fV_imprimeSerial("Configurando watchdog e iniciando...",false);
        vU16_clockESP32 = fU16_carregaConfigGeral(0,42,80); // clock do ESP32 para whatchdog
        vU32_tempoWatchDog = fU32_carregaConfigGeral(0,44,300000000); // Tempo para whatchdog
        vHW_timer = timerBegin(0, vU16_clockESP32, true);  // TimerID 0, div 80 (clock do esp), contador progressivo
        timerAttachInterrupt(vHW_timer, &fV_resetModule, true);
        timerAlarmWrite(vHW_timer, vU32_tempoWatchDog, true);  // Timer, tempo (us), repeticao
        timerAlarmEnable(vHW_timer);  // Habilita a interrupcao
        vB_emExecucaoWDog = true;
    } else {
        fV_imprimeSerial("Configurando watchdog...",false);
        vB_exec_WatchDog = fB_carregaConfigGeral(0,43,false);        
        vU16_clockESP32 = fU16_carregaConfigGeral(0,42,80); // clock do ESP32 para whatchdog
        vU32_tempoWatchDog = fU32_carregaConfigGeral(0,44,300000000); // Tempo para whatchdog
    }
    fV_imprimeSerial(" OK");    
}

//========================================
void fV_resetarWatchdog() {
  if (vB_exec_WatchDog && vB_emExecucaoWDog) {
    static unsigned long ultimoResetWatchdog = 0;  // Mantém o valor entre as chamadas da função
    if (millis() - ultimoResetWatchdog >= 5000) {
        timerWrite(vHW_timer, 0);  // Reinicia o contador do temporizador do watchdog
        ultimoResetWatchdog = millis();  // Atualiza o tempo do último reset
    }
  }
}

//========================================
void IRAM_ATTR fV_resetModule(){
    ets_printf("Vai Reiniciar por (WatchDog) \n"); //imprime no log
    esp_restart(); //reinicia o chip
}

//========================================
void fV_iniciaAcoes(bool force) {
    fV_imprimeSerial("Iniciando configuracao das Acoes...");

    bool addass = false;

    fV_carregaFILESYS_AS2D("/aS8_AcoesMenu.txt",aS8_AcoesMenu,1,vU8_totPinos);
    fV_carregaFILESYS_AS2D("/aS8_AcoesRedeMenu.txt",aS8_AcoesRedeMenu,1,vU8_totPinos);
    fV_carregaFILESYS_AS2D("/aS8_AcoesStringMenu.txt",aS8_AcoesStringMenu,1,vU8_totPinos);

    // Acoes 1  
    fV_carregaFlash_AUint("/aU16_Acao1.txt", aU16_Acao1, vI8_aU16_Acao, vU8_totPinos);
    fV_carregaFlash_AUint("/aU8_AcaoRede1.txt", aU8_AcaoRede1, vI8_aU8_AcaoRede, vU8_totPinos);
    fV_carregaFILESYS_AS2D("/aS8_Acao1.txt",aS8_Acao1,vI8_aS8_Acao,vU8_totPinos);
  
    // Acoes 2
    fV_carregaFlash_AUint("/aU16_Acao2.txt", aU16_Acao2, vI8_aU16_Acao, vU8_totPinos);
    fV_carregaFlash_AUint("/aU8_AcaoRede2.txt", aU8_AcaoRede2, vI8_aU8_AcaoRede, vU8_totPinos);
    fV_carregaFILESYS_AS2D("/aS8_Acao2.txt",aS8_Acao2,vI8_aS8_Acao,vU8_totPinos);

    // Acoes 3
    fV_carregaFlash_AUint("/aU16_Acao3.txt", aU16_Acao3, vI8_aU16_Acao, vU8_totPinos);
    fV_carregaFlash_AUint("/aU8_AcaoRede3.txt", aU8_AcaoRede3, vI8_aU8_AcaoRede, vU8_totPinos);
    fV_carregaFILESYS_AS2D("/aS8_Acao3.txt",aS8_Acao3,vI8_aS8_Acao,vU8_totPinos);

    // Acoes 4
    fV_carregaFlash_AUint("/aU16_Acao4.txt", aU16_Acao4, vI8_aU16_Acao, vU8_totPinos);
    fV_carregaFlash_AUint("/aU8_AcaoRede4.txt", aU8_AcaoRede4, vI8_aU8_AcaoRede, vU8_totPinos);
    fV_carregaFILESYS_AS2D("/aS8_Acao4.txt",aS8_Acao4,vI8_aS8_Acao,vU8_totPinos);

    fV_imprimeSerial("Configuracao das acoes finalizada");
    fV_grupoAcoes(false);
}

//========================================
void fV_configuraModulos(bool force) {
  fV_imprimeSerial("Iniciando configuracao dos modulos...", false);
  if (!force) {
    vB_exec_Modulos = fB_carregaConfigGeral(0,35, false);
    vU16_modulos_HandShake = fU16_carregaConfigGeral(0,36, 65535);
    vU16_modulos_MTBS_Acoes = fU16_carregaConfigGeral(0,37, 65535);
    vU8_totModulos = fU8_carregaConfigGeral(0,47,5);
    vI_cicloHandshake = fI32_carregaConfigGeral(0,38, 65535);

    fV_carregaFlash_AUint("/aU16_InterMod.txt", aU16_InterMod, vI8_aU16_InterModHA, vU8_totModulos);
    fV_carregaFlash_AUint("/aB_InterMod.txt", aB_InterMod, vI8_aB_InterMod, vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS_InterMod.txt",aS_InterMod,vI8_aS_InterMod,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS_InterModMenu.txt",aS_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aU16_InterModMenu.txt",aU16_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS16_InterModHA.txt",aS16_InterModHA,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aSB_InterModMenu.txt",aSB_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS8_ControlMsgModHist.txt",aS8_ControlMsgModHist,1,vU8_totModulos);

    fV_carregaFlash_AUint("/aI16_ControlHS.txt", aI16_ControlHS, vI8_aU16_InterModHA, vU8_totModulos);
    for (uint8_t y=0; y<vU8_totModulos; y++) {
      aI16_ControlHS[0][y] = vI_cicloHandshake;
      aI16_ControlHS[3][y] = 0;
    }
  } else if (force) {

    fV_carregaFlash_AUint("/aU16_InterMod.txt", aU16_InterMod, vI8_aU16_InterModHA, vU8_totModulos);
    fV_carregaFlash_AUint("/aB_InterMod.txt", aB_InterMod, vI8_aB_InterMod, vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS_InterMod.txt",aS_InterMod,vI8_aS_InterMod,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS_InterModMenu.txt",aS_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aU16_InterModMenu.txt",aU16_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS16_InterModHA.txt",aS16_InterModHA,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aSB_InterModMenu.txt",aSB_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS8_ControlMsgModHist.txt",aS8_ControlMsgModHist,1,vU8_totModulos);

    fV_carregaFlash_AUint("/aI16_ControlHS.txt", aI16_ControlHS, vI8_aU16_InterModHA, vU8_totModulos);
    for (uint8_t y=0; y<vU8_totModulos; y++) {
      aI16_ControlHS[0][y] = vI_cicloHandshake;
      aI16_ControlHS[3][y] = 0;
    }
    vB_exec_Modulos = true;
    vU8_crtl_ModHist = 0;
  }
  fV_carregaFlash_AUint("/nulo.txt", aU16_ControlMsgModHist, vI8_aU8_ControlMsgHist, vU8_totModulos,"aU16_ControlMsgModHist");
  fV_carregaFlash_AUint("/nulo.txt", aU16_ControlMsgMod, vI8_aU8_ControlMsg, vU8_totModulos,"aU16_ControlMsgMod");  
  fV_imprimeSerial(" OK");  
}

//========================================
void fV_salvarFlash() {
  fV_imprimeSerial("Salvando informacoes em Preferences e Filesys...");
  
  // Preferencias
  fV_Preference("E",false);
  //fV_salvaFILESYS_AS2D("/aS_Preference.txt", aS_Preference, vI8_aS_Preference_ROW, vI8_aS_Preference_COL);
  
  // Pinos
  fV_salvaFlash_AUint("/aU16_Pinos.txt", aU16_Pinos, vI8_aU16_Pinos, vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_Pinos.txt", aS8_Pinos, vI8_aS8_Pinos, vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_AcoesMenu.txt",aS8_AcoesMenu,1,vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_AcoesRedeMenu.txt",aS8_AcoesRedeMenu,1,vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_AcoesStringMenu.txt",aS8_AcoesStringMenu,1,vU8_totPinos);
  
  // Acoes 1  
  fV_salvaFlash_AUint("/aU16_Acao1.txt", aU16_Acao1, vI8_aU16_Acao, vU8_totPinos);
  fV_salvaFlash_AUint("/aU8_AcaoRede1.txt", aU8_AcaoRede1, vI8_aU8_AcaoRede, vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_Acao1.txt",aS8_Acao1,vI8_aS8_Acao,vU8_totPinos);
  // Acoes 2
  fV_salvaFlash_AUint("/aU16_Acao2.txt", aU16_Acao2, vI8_aU16_Acao, vU8_totPinos);
  fV_salvaFlash_AUint("/aU8_AcaoRede2.txt", aU8_AcaoRede2, vI8_aU8_AcaoRede, vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_Acao2.txt",aS8_Acao2,vI8_aS8_Acao,vU8_totPinos);
  // Acoes 3
  fV_salvaFlash_AUint("/aU16_Acao3.txt", aU16_Acao3, vI8_aU16_Acao, vU8_totPinos);
  fV_salvaFlash_AUint("/aU8_AcaoRede3.txt", aU8_AcaoRede3, vI8_aU8_AcaoRede, vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_Acao3.txt",aS8_Acao3,vI8_aS8_Acao,vU8_totPinos);
  // Acoes 4
  fV_salvaFlash_AUint("/aU16_Acao4.txt", aU16_Acao4, vI8_aU16_Acao, vU8_totPinos);
  fV_salvaFlash_AUint("/aU8_AcaoRede4.txt", aU8_AcaoRede4, vI8_aU8_AcaoRede, vU8_totPinos);
  fV_salvaFILESYS_AS2D("/aS8_Acao4.txt",aS8_Acao4,vI8_aS8_Acao,vU8_totPinos);
  
  // Inter Modulos
  fV_salvaFlash_AUint("/aI16_ControlHS.txt", aI16_ControlHS, vI8_aS_InterMod, vU8_totModulos);
  fV_salvaFlash_AUint("/aU16_InterMod.txt", aU16_InterMod, vI8_aU16_InterMod, vU8_totModulos);
  fV_salvaFlash_AUint("/aB_InterMod.txt", aB_InterMod, vI8_aB_InterMod, vU8_totModulos);
  fV_salvaFILESYS_AS2D("/aS_InterMod.txt",aS_InterMod,vI8_aS_InterMod,vU8_totModulos);
  fV_salvaFILESYS_AS2D("/aU16_InterModMenu.txt",aU16_InterModMenu,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aS_InterModMenu.txt",aS_InterModMenu,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aS16_InterModHA.txt",aS16_InterModHA,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aSB_InterModMenu.txt",aSB_InterModMenu,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aS8_ControlMsgModHist.txt",aS8_ControlMsgModHist,1,vU8_totModulos);
  //fV_salvaFILESYS_AS1D("/aU8_diasDaSemana.txt",aU8_diasDaSemana,vU8_diasDaSemana);
  //fV_salvaFILESYS_AS1D("/aU8_meses.txt",aU8_meses,vU8_meses);
  
  fV_imprimeSerial("As informacoes forma salvas");
}

//========================================
String fS_calculaBytes(const size_t bytes) {
  if (bytes < 1024) return String(bytes) + " B";
  else if (bytes < (1024 * 1024)) return String(bytes / 1024.0) + " KB";
  else if (bytes < (1024 * 1024 * 1024)) return String(bytes / 1024.0 / 1024.0) + " MB";
  else return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
}

//========================================
String processor(const String& var) {
  String tmp;
  
  if (var == "FREEFILESYS") {
    tmp = "-2";
    return tmp;
    //return fS_calculaBytes((FILESYS.totalBytes() - FILESYS.usedBytes()));
  }

  if (var == "USEDFILESYS") {
    tmp = "-1";
    return tmp;
    //return fS_calculaBytes(FILESYS.usedBytes());
  }

  if (var == "TOTALFILESYS") {
    tmp = "-3";
    return tmp;
   // return fS_calculaBytes(FILESYS.totalBytes());
  }
  return String();
}

//========================================
bool fB_configuraServidorWEB(const uint16_t& porta, bool force) {
    bool resultado = false;

    if (WiFi.status() == WL_CONNECTED) {
        fV_imprimeSerial("Iniciando configuracao do servidor web na porta ", false);
        if (!force) {
          vI_U16_portaWebAsync = fU16_carregaConfigGeral(0,3,8080);
          fV_imprimeSerial(vI_U16_portaWebAsync, false);
          fV_imprimeSerial("...", false);
          vU8_tempoRefresh = fU8_carregaConfigGeral(0,41,60);
          VB_mostra_Status = fU8_carregaConfigGeral(0,48,60);
          VB_mostra_Interm = fU8_carregaConfigGeral(0,49,60);
        } else {
          vI_U16_portaWebAsync = porta;
          fV_imprimeSerial(vI_U16_portaWebAsync, false);
          fV_imprimeSerial("...", false);
          vB_emExecucaoWS = false;
          delete SERVIDOR_WEB_ASYNC;          
        }

        // Liberar a memória se o servidor já estiver criado
        if (SERVIDOR_WEB_ASYNC != nullptr) {
          vB_emExecucaoWS = false;
          delete SERVIDOR_WEB_ASYNC;
        }
        // Criar nova instância do servidor na porta configurada
        SERVIDOR_WEB_ASYNC = new AsyncWebServer(vI_U16_portaWebAsync);

        // ---- Conjunto basico pagina inicial ---- //
        // Pagina inicial do acesso web ao esp32
        SERVIDOR_WEB_ASYNC->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
          //if(!request->authenticate(vS_userWeb.c_str(), vS_passWeb.c_str()) && vB_pedeAutentica) {
          //  return request->requestAuthentication(); // Solicita autenticação
          //} else {
            f_handle_Index(request);
          //}
          //request->send(200, "text/plain", "Acesso SMCR!<br>Necessário autenticar");
        });
        // Faz logout do acesso web ao esp32
        SERVIDOR_WEB_ASYNC->on("/logout", HTTP_GET, [](AsyncWebServerRequest * request) {
          request->requestAuthentication();
          request->send(401);
        });
        // ---- Fim do conjunto basico pagina inicial ---- //

        // ---- Conjunto de cadastro de rede ---- //
        // Configuracao de rede wifi, hostname, etc.
        SERVIDOR_WEB_ASYNC->on("/conf_rede", HTTP_GET, [](AsyncWebServerRequest *request) {
          f_handle_ConfiguraWifi(request);
          //request->send(200, "text/html", "Configuração de Rede");
        });
        // Salvar informacoes do cadastro de rede
        SERVIDOR_WEB_ASYNC->on("/salvar_rede", HTTP_POST, [](AsyncWebServerRequest *request) {
            fV_salvarRede(request);
        });
        // ---- Fim do conjunto de cadastro de rede ---- //

        // ---- Conjunto de cadastro de pinos ---- //
        // Lista as portas (pinos) para escolha do pino para cadastro
        SERVIDOR_WEB_ASYNC->on("/pinos", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->sendChunked("text/html", f_handle_ConfiguraPortas);
        });
        // Formulario para cadastro de pinos (portas)
        SERVIDOR_WEB_ASYNC->on("/configurar_pino", HTTP_GET, [](AsyncWebServerRequest *request) {
            fV_cadastraPino(request);
        });
        // Salvar informacoes do cadastro de pinos
        SERVIDOR_WEB_ASYNC->on("/salvar_pinos", HTTP_POST, [](AsyncWebServerRequest *request) {
            fV_salvarPinos(request);
        });
        // ---- Fim do conjunto de cadastro de pinos ---- //

        // ---- Conjunto de cadastro de acoes ---- //
        // Lista as acoes para escolha da acao para cadastro
        SERVIDOR_WEB_ASYNC->on("/acoes", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->sendChunked("text/html", f_handle_ConfiguraAcoes);
        });
        // Formulario para cadastro de pinos (portas)
        SERVIDOR_WEB_ASYNC->on("/configurar_acoes", HTTP_GET, [](AsyncWebServerRequest *request) {
            fV_cadastraAcoes(request);
        });
        // Salvar informacoes do cadastro de pinos
        SERVIDOR_WEB_ASYNC->on("/salvar_acoes", HTTP_POST, [](AsyncWebServerRequest *request) {
            fV_salvarAcoes(request);
        });
        // ---- Fim do conjunto de cadastro de acoes ---- //

        // ---- Conjunto de configuracao geral ---- //
        // Configuracao de rede wifi, hostname, etc.
        SERVIDOR_WEB_ASYNC->on("/conf_geral", HTTP_GET, [](AsyncWebServerRequest *request) {
          f_handle_CadastroGeral(request);
        });
        // Salvar informacoes do cadastro de rede
        SERVIDOR_WEB_ASYNC->on("/salvar_conf_geral", HTTP_POST, [](AsyncWebServerRequest *request) {
            f_handle_salvarCadastroGeral(request);
        });
        // ---- Fim do conjunto de configuracao geral ---- //

        // ---- Conjunto de cadastro de modulos ---- //
        // Lista os modulos para escolha do modulos para cadastro
        SERVIDOR_WEB_ASYNC->on("/modulos", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->sendChunked("text/html", f_handle_ConfiguraModulos);
        });
        // Formulario para cadastro de modulos
        SERVIDOR_WEB_ASYNC->on("/configurar_modulo", HTTP_GET, [](AsyncWebServerRequest *request) {
            fV_cadastraModulo(request);
        });
        // Salvar informacoes do cadastro do modulos
        SERVIDOR_WEB_ASYNC->on("/salvar_intermodulos", HTTP_POST, [](AsyncWebServerRequest *request) {
            fV_salvarInterModulos(request);
        });        
        // Salvar informacoes do cadastro de um modulo
        SERVIDOR_WEB_ASYNC->on("/salvar_modulos", HTTP_POST, [](AsyncWebServerRequest *request) {
            fV_salvarModulos(request);
        });
        // ---- Fim do conjunto de cadastro de modulos ---- //

        // ---- Conjunto para confirmacoes de execucao pela web ---- //
        // Usado para dialogo na interface web
        SERVIDOR_WEB_ASYNC->on("/pergunta", HTTP_GET, [](AsyncWebServerRequest *request) {
            String funcao = "";
            bool redirecionar = false;
            String pagina = "";

            // Verifica se o parâmetro 'funcao' foi fornecido
            if (request->hasParam("funcao")) {
                funcao = request->getParam("funcao")->value();
            } else {
                funcao = "nenhuma função especificada"; // Mensagem de fallback
            }

            // Verifica se o parâmetro 'redirecionar' foi fornecido
            if (request->hasParam("redirecionar")) {
                String redirParam = request->getParam("redirecionar")->value();
                redirecionar = (redirParam == "true");  // Converte para booleano
            }
            if (!redirecionar) {
                pagina += fS_cabecaHTML("Pergunta", "Deseja executar esta ação?", "/");
                pagina += "<br><br><label id='texto'>Executar a ação: " + funcao + "</label><br>";
                pagina += "<form action='/resposta' method='post'>";
                pagina += "<input type='hidden' name='funcao' value='" + funcao + "'>";
                pagina += "<br><label for='confirmacao'>Digite 'Sim' para confirmar a ação:</label>";
                pagina += "<input type='text' id='confirmacao' name='confirmacao'>";
                pagina += "<input type='submit' value='Confirmar'>";
                pagina += "</form>";
                pagina += fS_rodapeHTML("/");
            } else {
                pagina += "<!DOCTYPE html>";
                pagina += "<html lang='pt-br'>";
                pagina += "<head>";
                pagina += "<meta charset='UTF-8'>";
                pagina += "<meta http-equiv='refresh' content='15000; URL=/'>";
                pagina += "<script>setTimeout(function(){ window.location = '/'; }, 15000);</script>";                
                pagina += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
                pagina += "<title>"+vS_nomeDispositivo+" - Pergunta</title>";
                pagina += "</head>";
                pagina += "<body id='body'>";
                pagina += "<h1>Deseja executar esta ação?</h1>";
                pagina += "<br><a href='https://github.com/rede-analista/smcr/' target='_blank'>Ajuda</a>";
                pagina += "<br><a href=\"/\">Página Inicial</a>";
                pagina += "<p>Você será redirecionado para página inicial em 15 segundos.</p>";                
                pagina += "<form action='/resposta' method='post'>";
                pagina += "<input type='hidden' name='funcao' value='" + funcao + "'>";
                pagina += "<br><label for='confirmacao'>Digite 'Sim' para confirmar a ação:</label>";
                pagina += "<input type='text' id='confirmacao' name='confirmacao'>";
                pagina += "<input type='submit' value='Confirmar'>";
                pagina += "</form>";
                pagina += fS_rodapeHTML("/");                
            }

            request->send(200, "text/html", pagina);
        });
        // Usado para executar funcao conforme resposta do dialogo na interface web
        SERVIDOR_WEB_ASYNC->on("/resposta", HTTP_POST, [](AsyncWebServerRequest *request){
            fV_resposta(request);
        });
        // ---- Fim do conjunto para confirmacoes de execucao pela web ---- //

        // ---- Conjunto para gerenciamento de arquivos ---- //
        // Pagina de gerenciamento de arquivos
        SERVIDOR_WEB_ASYNC->on("/files", HTTP_GET, [](AsyncWebServerRequest *request) {
          request->send_P(200, "text/html", index_html, processor);
        });
        // Faz upload de arquivos para LittleFS (FILESYS)
        SERVIDOR_WEB_ASYNC->on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {
            request->send(200, "text/plain", "Upload successful");
        }, handleFileUpload);
        // Lista arquivos do LittleFS (FILESYS)
        SERVIDOR_WEB_ASYNC->on("/fS_listaArquivosFilesys", HTTP_GET, [](AsyncWebServerRequest *request) {
          request->send(200, "text/plain", fS_listaArquivosFilesys(true));
        });    
        // Manipula arquivos do LittleFS (FILESYS), download, delete e lista
        SERVIDOR_WEB_ASYNC->on("/file", HTTP_GET, [](AsyncWebServerRequest *request) {
          if (request->hasParam("name") && request->hasParam("action")) {
              String fileName = request->getParam("name")->value();
              String fileAction = request->getParam("action")->value();
              // Garantir que o nome do arquivo comece com "/"
              if (!fileName.startsWith("/")) {
                  fileName = "/" + fileName;
              }
              if (!FILESYS.exists(fileName)) {
                  request->send(400, "text/plain", "ERROR: arquivo nao existe");
              } else {
                  if (fileAction == "download") {
                      request->send(FILESYS, fileName, "application/octet-stream");
                  } else if (fileAction == "delete") {
                      FILESYS.remove(fileName);
                      String html = fS_cabecaHTML("Gerência de Arquivos","Apagar Arquivos","/files");
                      html += "Arquivo apagado: ";
                      html += fileName;
                      html += "<br>";
                      html += fS_rodapeHTML("/files");
                      request->send(200, "text/html", html);
                  } else {
                      request->send(400, "text/plain", "ERROR: parametro de acao invalido fornecido");
                  }
              }
          } else {
              request->send(400, "text/plain", "ERROR: nome e parametros de acao necessarios");
          }

        });
        // ---- Fim do conjunto para gerenciamento de arquivos ---- //

        // ---- Abre pagina de monitoramento da Serial ---- //
        SERVIDOR_WEB_ASYNC->on("/serial", HTTP_GET, [](AsyncWebServerRequest *request) {
          f_handle_SerialOutput(request);
        });

        // Abre opcoes para configuracoes gerais do programa
        SERVIDOR_WEB_ASYNC->on("/configurag", HTTP_GET, [](AsyncWebServerRequest *request) {
          f_handle_OpcoesGerais(request);
        });

        // Abre opcoes para executar funcoes do programa
        SERVIDOR_WEB_ASYNC->on("/execfuncoes", HTTP_GET, [](AsyncWebServerRequest *request) {
          f_handle_OpcoesFuncoes(request);
        });

        // Recebe dados do intermodulos
        SERVIDOR_WEB_ASYNC->on("/dados", HTTP_GET, [](AsyncWebServerRequest *request) {
          fV_recebeDados(request);
        });

        // Menssagem quando a pagina solicitada nao e encontrada
        SERVIDOR_WEB_ASYNC->onNotFound([](AsyncWebServerRequest *request) {
          f_handle_NotFound(request);
          //request->send(200, "text/html", "Pagina nao encontrada");
        });

        // Iniciar o servidor
        if (SERVIDOR_WEB_ASYNC != nullptr) {
            ws = new AsyncWebSocket("/ws");
            ws->onEvent(fV_onEvent);
            SERVIDOR_WEB_ASYNC->addHandler(ws);
            SERVIDOR_WEB_ASYNC->begin();
            resultado = true;
            vB_emExecucaoWS = true;
            fV_imprimeSerial(" OK", true);
        } else {
            fV_imprimeSerial(" ERRO", true);
        }   
    } else {
        fV_imprimeSerial("Erro na conexao WiFi. Servidor web nao configurado.", true);
    }
  return resultado;
}

//========================================
bool fV_apagaTodosArquivosSPIFFS() {
    // Inicializa o SPIFFS se ainda não foi inicializado
    if (!SPIFFS.begin(true)) {  // true = format if mount failed
        fV_imprimeSerial("Erro ao inicializar o SPIFFS.");
        return false;
    }

    // Abre o diretório raiz do SPIFFS
    File root = SPIFFS.open("/");
    if (!root || !root.isDirectory()) {
        fV_imprimeSerial("Erro ao abrir o diretório raiz do SPIFFS.");
        SPIFFS.end();  // Fecha SPIFFS antes de retornar
        return false;
    }

    // Itera sobre todos os arquivos no diretório
    File file = root.openNextFile();
    while (file) {
        // Captura o nome do arquivo
        String filename = file.name();
        
        // Adiciona '/' ao início do nome do arquivo, se necessário
        if (filename.length() > 0 && filename[0] != '/') {
            filename = "/" + filename;
        }

        fV_imprimeSerial("Tentando apagar arquivo: ",false);
        fV_imprimeSerial(filename);

        // Tenta remover o arquivo
        if (!SPIFFS.remove(filename)) {
            fV_imprimeSerial("Erro ao apagar arquivo: ",false);
            fV_imprimeSerial(filename);
            SPIFFS.end();  // Fecha SPIFFS antes de retornar
            return false;
        } else {
            fV_imprimeSerial("Arquivo apagado com sucesso: ",false);
            fV_imprimeSerial(filename);
        }

        // Move para o próximo arquivo
        file = root.openNextFile();
    }

    // Fecha SPIFFS após todas as operações
    SPIFFS.end();
    fV_imprimeSerial("Todos os arquivos foram apagados com sucesso.");
    return true;
}

//========================================
void fV_iniciaPinos(bool force) {
    fV_imprimeSerial("Iniciando configuracao dos pinos...");
    if (!force) {
      vS_corStatus1 = fS_carregaConfigGeral(0,13,"Tomato");
      vS_corStatus0 = fS_carregaConfigGeral(0,14,"LightGreen");
      vU8_totPinos = fU8_carregaConfigGeral(0,39,5);
      vU8_bitsProc = fU8_carregaConfigGeral(0,45,12);
      vU8_ciclosAmostra = fU8_carregaConfigGeral(0,46,8);
      vU8_colunasTabelas = fU8_carregaConfigGeral(0,40,7);
    }
    analogSetWidth(vU8_bitsProc);

    if (vU8_colunasTabelas > vU8_totPinos) {
      vU8_colunasTabelas = vU8_totPinos;
    }
    vU8_PinosCadastrados = 0;
    fV_carregaFlash_AUint("/aU16_Pinos.txt", aU16_Pinos, vI8_aU16_Pinos, vU8_totPinos);
    for (uint8_t x=0; x<vI8_aU16_Pinos; x++){
      for (uint8_t y=0; y<vU8_totPinos; y++) {
        if (x == 0 && aU16_Pinos[x][y] > 0){
          vU8_PinosCadastrados++;
        }
      }
    }

    fV_carregaFlash_AUint("/nulo.txt", aU16_Pinos_Status, 1, vU8_totPinos,"aU16_Pinos_Status");

    if (aU16_ControlAcoesGroups != nullptr ){
      for (int i = 0; i < vI8_ControlAcoesGroups; i++) {
        delete[] aU16_ControlAcoesGroups[i]; // Libera cada linha
      }
      delete[] aU16_ControlAcoesGroups; // Libera o array de ponteiros
      aU16_ControlAcoesGroups = nullptr; // Define o ponteiro para nullptr
    }
    vI8_ControlAcoesGroups = (vU8_totPinos * 4) + 1;
    fV_carregaFlash_AUint("/nulo.txt", aU16_ControlAcoesGroups, vI8_ControlAcoesGroups, vU8_totPinos,"aU16_ControlAcoesGroups");
    for (uint8_t x=0; x<vU8_totPinos; x++){
      if (aU16_Pinos[0][x] > 0 ) {
        aU16_ControlAcoesGroups[0][x] = aU16_Pinos[0][x];
        if (aU16_Pinos[1][x] == 1 || aU16_Pinos[1][x] == 192) {
          pinMode(aU16_Pinos[0][x],aU16_Pinos[2][x]);
        }
      }
    }

    fV_carregaFILESYS_AS2D("/aS16_PinosMenu.txt",aS16_PinosMenu,1,vI8_aU16_Pinos);
    fV_carregaFILESYS_AS2D("/aS8_Pinos.txt", aS8_Pinos, vI8_aS8_Pinos, vU8_totPinos);

    fV_imprimeSerial("Configuracao dos pinos finalizada");
}

//========================================
void f_cria_MDNS(String nome, IPAddress ip, uint16_t porta) {
  fV_imprimeSerial("Configurando mDNS: ",false);
  if (!MDNS.begin(nome.c_str())) {
    fV_imprimeSerial("ERRO",true);
  } else {
    MDNS.addService("_http", "_tcp", porta);
    fV_imprimeSerial("OK",true);
  }
}

//========================================
void fV_configNTP() {
  fV_imprimeSerial("Configurando NTP: ",false);
  sntp_set_time_sync_notification_cb( fV_callbackNTP );
  sntp_servermode_dhcp(1);
  configTime(3600, 3600, vS_ntpServer1.c_str(), vS_ntpServer2.c_str());
  configTzTime(vS_timeZone.c_str(), vS_ntpServer1.c_str(), vS_ntpServer2.c_str());
  fV_imprimeSerial("OK",true);
}

//========================================
void fV_callbackNTP(struct timeval *t) {
  // Callback function (get's called when time adjusts via NTP)
  fV_imprimeSerial("Executado ajuste de tempo do NTP!!",true);
  fV_imprimeSerial(fS_DataHora(),true);
}

//========================================
void fV_modoAP(String wifi, String senha, uint16_t portaap) {
  WiFi.disconnect();
  fV_imprimeSerial("Entrando em modo AP... ", true);
  delay(1000);
  WiFi.softAP(wifi.c_str(), senha.c_str());

  // Criação do servidor web na porta especificada
  if (SERVIDOR_WEB_ASYNC != nullptr) {
    delete SERVIDOR_WEB_ASYNC;
  }
  SERVIDOR_WEB_ASYNC = new AsyncWebServer(portaap);

  // Cadastro inicial do WIFI necesita os dois metodos GET e POST
  SERVIDOR_WEB_ASYNC->on("/wifiinicio", HTTP_GET, [](AsyncWebServerRequest *request) {
    f_handle_ConfiguraWifiInicio(request);
    request->send(200, "text/html", "Configuracao Inicial do Wifi");
  });
  SERVIDOR_WEB_ASYNC->on("/wifiinicio", HTTP_POST, [](AsyncWebServerRequest *request) {
    f_handle_SalvarWifiInicio(request);
  });

  SERVIDOR_WEB_ASYNC->onNotFound([](AsyncWebServerRequest *request) {
    f_handle_NotFound(request);
  });

  // Inicia o servidor web assíncrono
  SERVIDOR_WEB_ASYNC->begin();

  fV_imprimeSerial("Servidor HTTP iniciado.", true);
  fV_imprimeSerial("Conecte seu wifi na rede [" + wifi + "] e acesse http://", false);
  fV_imprimeSerial(WiFi.softAPIP().toString(), false);
  fV_imprimeSerial(":", false);
  fV_imprimeSerial(portaap, false);
  fV_imprimeSerial("/wifiinicio pelo navegador para configurar o SSID e SENHA na placa " + vS_nomeDispositivo, true);

  // Loop de espera enquanto o modo AP está ativo
  while (1) {
    if (vB_finalizaModoAP) {
      fV_imprimeSerial("Saindo do modo AP da placa " + vS_nomeDispositivo + " e reiniciando o dispositivo", true);
      delay(10000);
      esp_restart();
    }
    delay(2); // Pequeno delay para evitar sobrecarga
  }
  fV_imprimeSerial(" OK", true);
}

//========================================
uint8_t fU8_configuraWifi() {
    fV_imprimeSerial("Iniciando verificacao/configuracao do wifi...");
    if (WiFi.status() != WL_CONNECTED) {
        vS_nomeWifi = fS_carregaConfigGeral(0,0,"wifi"); //SSID da sua rede wifi (rede que essa placa ESP vai conectar)
        vS_senhaWifi = fS_carregaConfigGeral(0,1,"12345678"); //Senha da sua rede wifi (rede que essa placa ESP vai conectar)
        vU8_tentativaConexoes = fU8_carregaConfigGeral(0,2,4); //Tentativas de conexoes diversas antes de seguir com o boot(para nao ficar parado durante o boot esperando conetar em outros recursos)
        vI_U16_portaWebAsync = fU16_carregaConfigGeral(0,3,8080); //Porta do servidor web desta placa ESP
        vS_nomeDispositivo = fS_carregaConfigGeral(0,4,"esp32modularx"); //Hostname desta placa ESP na rede    
        vS_nomeAP_Wifi = fS_carregaConfigGeral(0,7,vS_nomeDispositivo) + " Ponto de Acesso"; //Nome do wifi (SSID) que sera gerado se esta placa ESP entrar em modo AP
        vS_senhaAP_Wifi = fS_carregaConfigGeral(0,8, "senha12345678"); //Senha do wifi que sera gerado se esta placa ESP entrar em modo AP
        vB_modoAP = fB_carregaConfigGeral(0,9, true); //Se true esta placa ESP entra em modo AP caso nao consiga conectar no wifi definido em vS_nomeWifi
        vS_ntpServer1 = fS_carregaConfigGeral(0,10, "pool.ntp.br"); // Servidor NTP para sincronismo de horario
        vS_ntpServer2 = fS_carregaConfigGeral(0,11, "pool.ntp.org"); // Servidor NTP para sincronismo de horario
        vS_timeZone = fS_carregaConfigGeral(0,12, "<-03>3"); // TimeZone para sincronismo de horario
        vS_userWeb = fS_carregaConfigGeral(0,5, "admin"); // Usuario acesso HTTP
        vS_passWeb = fS_carregaConfigGeral(0,6, "admin"); // Senha acesso HTTP        

        if (vS_nomeDispositivo.length() > 1) {
          WiFi.setHostname(vS_nomeDispositivo.c_str());
        }
        WiFi.setAutoReconnect(true);
        WiFi.setAutoConnect(true);
        WiFi.begin(vS_nomeWifi.c_str(), vS_senhaWifi.c_str());
               int cont = 1;
        while (WiFi.status() != WL_CONNECTED && cont <= vU8_tentativaConexoes) {
          delay(5000);
          fV_imprimeSerial("Conectando ao WiFi, status ", false);
          fV_imprimeSerial(WiFi.status(), false);
          fV_imprimeSerial(" tentativa ", false);
          fV_imprimeSerial(cont, false);
          fV_imprimeSerial(" de ", false);
          fV_imprimeSerial(vU8_tentativaConexoes, true);
          cont++;
        }
        fV_imprimeSerial("Endereco IP do WIFI: ", false);
        fV_imprimeSerial(WiFi.localIP().toString(), false);
        fV_imprimeSerial(":", false);
        fV_imprimeSerial(vI_U16_portaWebAsync, false);
        fV_imprimeSerial(" Hostname: ", false);
        fV_imprimeSerial(vS_nomeDispositivo + " ", false);
        if (WiFi.status() == WL_CONNECTED) {
          vB_emExecucaoWifi = true;  
          fV_imprimeSerial(" OK", true);
          if (vB_emExecucaoWifi) {
            f_cria_MDNS(vS_nomeDispositivo, WiFi.localIP(), vI_U16_portaWebAsync);
            fV_configNTP();            
          }
        } else {
          fV_imprimeSerial(" ERRO - Informacoes usadas no WIFI: ", false);
          String passwdw = "";
          for (uint8_t x = 0; x < vS_senhaWifi.length(); x++) {
            passwdw += "*";
          }
          fV_imprimeSerial("Hostname:" + vS_nomeDispositivo + " SSID:" + vS_nomeWifi + " Senha:" + passwdw, true);
          if (vB_modoAP && WiFi.status() != WL_CONNECTED && !vB_emExecucaoWifi) {
          fV_modoAP(vS_nomeAP_Wifi, vS_senhaAP_Wifi, vI_U16_portaWebAsync);
          }
        }
    } else {
        fV_imprimeSerial("O Wifi já está conectado!", true);
        if (WiFi.status() == WL_CONNECTED) {
          f_cria_MDNS(vS_nomeDispositivo, WiFi.localIP(), vI_U16_portaWebAsync);
          fV_configNTP();
        } else if (vB_modoAP && WiFi.status() != WL_CONNECTED && !vB_emExecucaoWifi) {
          fV_modoAP(vS_nomeAP_Wifi, vS_senhaAP_Wifi, vI_U16_portaWebAsync);
        }
    }
    fV_imprimeSerial("Verificacao/Configuracao do wifi finalizado");
    return WiFi.status();
}

//========================================
String fS_listaArquivosFilesys(bool ishtml) {
    String returnText = "";

    // Abrir o diretório raiz para leitura
    File root = FILESYS.open("/");
    if (!root) {
        return "Erro ao abrir o diretório.";
    }

    File foundfile = root.openNextFile();
  
    // Verificar se a saída será em HTML
    if (ishtml) {
        returnText += "<table border='1' cellpadding='5' cellspacing='0'><tr><th align='left'>Nome</th><th align='left'>Tamanho</th><th>Download</th><th>Excluir</th></tr>";
    }

    // Iterar sobre os arquivos no diretório 
    while (foundfile) {
        if (ishtml) {
            returnText += "<tr align='left'><td>" + String(foundfile.name()) + "</td><td>" + fS_calculaBytes(foundfile.size()) + "</td>";
            // Botão de download
            returnText += "<td><button onclick=\"window.location.href='/file?name=" + String(foundfile.name()) + "&action=download'\">Download</button></td>";
            // Botão de exclusão
            returnText += "<td><button onclick=\"window.location.href='/file?name=" + String(foundfile.name()) + "&action=delete'\">Excluir</button></td></tr>";
        } else {
            returnText += "Arquivo: " + String(foundfile.name()) + " Tamanho: " + fS_calculaBytes(foundfile.size()) + "\n";
        }
        foundfile = root.openNextFile();  // Próximo arquivo
    }

    // Fechar arquivos e diretório
    root.close();
    foundfile.close();

    // Adicionar informações sobre o sistema de arquivos
    returnText += "<BR>" + fS_calculaBytes(FILESYS.totalBytes()) + " de tamanho total do sistema de arquivos<BR>";
    returnText += fS_calculaBytes(FILESYS.usedBytes()) + " usados, incluindo a estrutura de diretórios<BR>";
    
    return returnText;
}

//========================================
String fS_listDir(const char * dirname, uint8_t levels) {
  String resultado = "";

  fV_imprimeSerial(String("Listando diretorio: ") + dirname, true);
  resultado += "<br>Listando diretorio: ";
  resultado += dirname;

  // Abre o diretório com FILESYS
  File root = FILESYS.open(dirname);
  if (!root) {
    fV_imprimeSerial("- falha ao abrir diretorio", true);
    resultado += "- falha ao abrir diretorio<br>";
    return resultado;
  }

  if (!root.isDirectory()) {
    fV_imprimeSerial(" - nao e um diretorio", true);
    resultado += " - nao e um diretorio<br>";
    return resultado;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      fV_imprimeSerial("  DIRETORIO : ", false);
      resultado += "<br> DIRETORIO: ";
      resultado += file.name();
      fV_imprimeSerial(file.name(), true);
      if (levels) {
        resultado += fS_listDir(file.path(), levels - 1);
      }
    } else {
      fV_imprimeSerial("  ARQUIVO: ", false);
      resultado += "<br> ARQUIVO: ";
      resultado += file.name();
      fV_imprimeSerial(file.name(), false);

      fV_imprimeSerial("\tTAMANHO: ", false);
      resultado += " TAMANHO:";
      resultado += file.size();
      fV_imprimeSerial(String(file.size()), true);
    }
    file = root.openNextFile();
  }
  fV_imprimeSerial("", true);  // Linha em branco no final

  return resultado;
}

//========================================
String fS_DataHora() {
    // Obter a data e hora atual

    time_t now = time(0);
    struct tm *tmInfo = localtime(&now);
    int dia = tmInfo->tm_mday;
    int mes = tmInfo->tm_mon;
    int ano = tmInfo->tm_year + 1900; // tm_year e o ano desde 1900
    int diaDaSemana = tmInfo->tm_wday;
    int hora = tmInfo->tm_hour;
    int minuto = tmInfo->tm_min;
    int segundo = tmInfo->tm_sec;

    // Construir a string formatada
    String dataHora = String(dia) + " de " + aU8_meses[mes] + " de " + String(ano) + ", " +
                      aU8_diasDaSemana[diaDaSemana] + " " +
                      String(hora) + ":" + (minuto < 10 ? "0" : "") + (minuto) + ":" + (segundo < 10 ? "0" : "") + String(segundo);

    return dataHora;
}

//========================================
String fS_Uptime() {
  unsigned long uptimeMillis = millis();
  unsigned long seconds = uptimeMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  unsigned long days = hours / 24;
  
  seconds %= 60;
  minutes %= 60;
  hours %= 24;
  String uptimeString = String(days) + "d " +
                        String(hours) + "h " +
                        String(minutes) + "m " +
                        String(seconds) + "s";
  return uptimeString;
}

//========================================
// Função para ler uint32_t
int32_t fI32_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const int32_t padrao) {
    int32_t resultado = padrao;
    String resp = aS_Preference[linha][coluna];
    if (resp.length() > 0) {
        resultado = resp.toInt();
    } 
    return resultado;
}
// Função para ler uint32_t
uint32_t fU32_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const uint32_t& padrao) {
    uint32_t resultado = padrao;
    String resp = aS_Preference[linha][coluna];
    if (resp.length() > 0) {
        resultado = resp.toInt();
    } 
    return resultado;
}
// Função para ler uint16_t
uint16_t fU16_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const uint16_t& padrao) {
    uint16_t resultado = padrao;
    String resp = aS_Preference[linha][coluna];
    if (resp.length() > 0) {
        resultado = resp.toInt();
    } 
    return resultado;
}
// Função para ler uint8_t
uint8_t fU8_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const uint8_t& padrao) {
    uint8_t resultado = padrao;
    String resp = aS_Preference[linha][coluna];
    if (resp.length() > 0) {
        resultado = resp.toInt();
    } 
    return resultado;
}
// Função para ler String com valor padrão
String fS_carregaConfigGeral(const uint8_t linha, uint8_t coluna ,const String& padrao) {
    String resultado = padrao;
    String resp = aS_Preference[linha][coluna];
    if (resp.length() > 0) {
      resultado = resp;

    } 
    return resultado;
}
// Função para ler bool
bool fB_carregaConfigGeral(const uint8_t linha, uint8_t coluna, const bool& padrao) {
    bool resultado = padrao;
    String resp = aS_Preference[linha][coluna];
    if (resp.length() > 0) {
        if (resp == "true" || resp == "1") {
          resultado = true;
        } else {
          resultado = false;
        }
    } 
    return resultado;
}

//========================================
String fS_idPlaca() {
  uint16_t vI_chipID = 0;
  for (int i = 0; i < 17; i = i + 8) {
    vI_chipID |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  vS_mqttIdUnico = String(vI_chipID);

  // Construa a mensagem para impressão
  String msg = "ESP32 Chip model = ";
  msg += ESP.getChipModel();
  msg += " Rev ";
  msg += ESP.getChipRevision();
  msg += "<br>This chip has cores ";
  msg += ESP.getChipCores();
  msg += "<br>Chip ID: ";
  msg += vI_chipID;

  fV_imprimeSerial(msg, true);
  fV_imprimeSerial("ESP32 Chip model = " + String(ESP.getChipModel()) + " Rev " + String(ESP.getChipRevision()), true);
  fV_imprimeSerial("This chip has " + String(ESP.getChipCores()) + " cores", true);
  fV_imprimeSerial("Chip ID: " + String(vI_chipID), true);

  return msg;
}

//========================================
bool fB_montaLittleFS() {
    // Inicializa o LittleFS no setup
    if (!FILESYS.begin(true)) {  // true = format if mount failed
        fV_imprimeSerial("Erro ao inicializar o FILESYS.",true);
        return false;
    } else {
        fV_imprimeSerial("FILESYS inicializado com sucesso.",true);
        return true;
    }
}

//========================================
void fV_salvaFILESYS_AS1D(const char* fileName, String* arr, uint8_t size) {
    fV_imprimeSerial("Salvando dias da semana no arquivo: ", false);
    fV_imprimeSerial(fileName, false);

    // Abre o arquivo para escrita
    File file = FILESYS.open(fileName, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial("Erro ao abrir o arquivo para escrita.", true);
        return;
    }

    // Escreve os dados do array no arquivo
    for (uint8_t i = 0; i < size; i++) {
        file.print(arr[i]);
        if (i < size - 1) {
            file.print(","); // Adiciona separador entre os elementos
        }
    }
    file.println(); // Adiciona nova linha ao final

    file.close();
    fV_imprimeSerial(" OK", true);
}


//========================================
void fV_carregaFILESYS_AS1D(const char* fileName, String*& arr, uint8_t& size, String sol) {
    fV_imprimeSerial("Carregando arquivo ("+sol+"): ", false);
    fV_imprimeSerial(fileName, false);

    // Tenta abrir o arquivo para leitura
    File file = FILESYS.open(fileName, FILE_READ);
    if (!file) {
        fV_imprimeSerial("Arquivo nao encontrado ou erro ao abrir.", true);
        size = 0;
        arr = nullptr;  // Assegura que o ponteiro esteja nulo se o arquivo não for encontrado
        return;
    }

    // Lê a primeira linha do arquivo para obter o conteúdo
    String line = file.readStringUntil('\n');
    
    // Conta o número de itens (dias) com base nas vírgulas
    uint8_t itemCount = 1; // Pelo menos um item está presente
    for (int i = 0; i < line.length(); i++) {
        if (line.charAt(i) == ',') {
            itemCount++;
        }
    }

    // Aloca memória para o array de acordo com o número de itens
    arr = new String[itemCount];
    size = itemCount;

    // Preenche o array com os dias lidos do arquivo
    uint8_t index = 0;
    int startIndex = 0;
    while (index < itemCount) {
        int endIndex = line.indexOf(',', startIndex);
        if (endIndex == -1) {
            endIndex = line.length();
        }
        arr[index] = line.substring(startIndex, endIndex);
        startIndex = endIndex + 1;
        index++;
    }

    file.close();
    fV_imprimeSerial(" OK", true);
}

//========================================
void fV_salvaFILESYS_AS2D(const char* fileName, String** arr, size_t rows, size_t cols) {
    fV_imprimeSerial("Salvando arquivo: ", false);
    fV_imprimeSerial(fileName, false);

    // Abre o arquivo para escrita com FILESYS
    File file = FILESYS.open(fileName, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial("Erro ao abrir o arquivo para escrita.", true);
        return;
    }

    // Escreve os dados do array no arquivo
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            file.print(arr[i][j]);
            if (j < cols - 1) {
                file.print(","); // Adiciona separador entre colunas
            }
        }
        file.println(); // Nova linha após cada linha do array
    }

    file.close();
    fV_imprimeSerial(" OK", true);
}

//========================================
void fV_carregaFILESYS_AS2D(const char* fileName, String**& arr, size_t rows, size_t cols, String sol) {
    fV_imprimeSerial("Carregando arquivo: ("+sol+"): ", false);
    fV_imprimeSerial(fileName, false);

    // Aloca memória para o array e preenche com strings vazias
    arr = new String*[rows];
    for (size_t i = 0; i < rows; i++) {
        arr[i] = new String[cols];
        for (size_t j = 0; j < cols; j++) {
            arr[i][j] = "";  // Inicializa com string vazia
        }
    }

    // Abre o arquivo para leitura com FILESYS
    File file = FILESYS.open(fileName, FILE_READ);
    if (!file) {
        if (fileName != "/nulo.txt") {
            fV_imprimeSerial("Arquivo nao encontrado ou erro ao abrir.", true);
        }
        return;  // Retorna com array já preenchido com strings vazias
    }
    size_t row = 0;
    while (file.available() && row < rows) {
        String line = file.readStringUntil('\n');  // Lê uma linha do arquivo
        size_t col = 0;
        int startIndex = 0;
        while (col < cols) {
            int endIndex = line.indexOf(',', startIndex);
            if (endIndex == -1) {  // Último item da linha
                endIndex = line.length();
            }
            arr[row][col] = fS_limpaEspacoFimLinha(line.substring(startIndex, endIndex));
            startIndex = endIndex + 1;
            col++;
        }
        row++;
    }

    file.close();
    fV_imprimeSerial(" OK", true);
}

//========================================
String fS_limpaEspacoFimLinha(const String& str) {
  if (str.length() == 0) return "";
  // Pointers to the beginning and end of the string
  int start = 0;
  int end = str.length() - 1;
  // Move start pointer to the first non-whitespace character
  while (start <= end && isspace(str[start]) || str[start] == '\n' || str[start] == '\r') {
      start++;
  }
  // Move end pointer to the last non-whitespace character
  while (end >= start && (isspace(str[end]) || str[end] == '\n' || str[end] == '\r')) {
      end--;
  }
  // Create a new string with the trimmed content
  if (start > end) {
      return ""; // String is all whitespace
  }
  return str.substring(start, end + 1);
}

//========================================
void fV_salvaFlash_AUint(const char* filename, uint16_t** arr, size_t rows, size_t cols) {
    fV_imprimeSerial("Salvando arquivo: ", false);
    fV_imprimeSerial(filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial("LittleFS nao esta inicializado.");
        return;
    }

    // Verifica se os parâmetros são válidos
    if (rows == 0 || cols == 0) {
        fV_imprimeSerial("Erro: número de linhas ou colunas inválido.");
        return;
    }

    // Abre o arquivo para escrita
    File file = FILESYS.open(filename, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial("Erro ao abrir o arquivo para escrita.");
        return;
    }

    // Salva os dados do array no arquivo em formato de texto
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            file.printf("%u", arr[i][j]);  // Escreve os valores do array
            if (j < cols - 1) {
                file.print(",");  // Adiciona vírgula para separar os valores na mesma linha
            }
        }
        file.println();  // Nova linha após cada linha do array
    }

    file.close();  // Fecha o arquivo
    fV_imprimeSerial(" OK", true);
}

//========================================
void fV_carregaFlash_AUint(const char* filename, uint16_t**& array, size_t rows, size_t cols, String sol) {
    fV_imprimeSerial("Carregando arquivo: ("+sol+"): ", false);
    fV_imprimeSerial(filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial("LittleFS nao esta inicializado.");
        return;
    }

    // Verifica se os parâmetros são válidos
    if (rows == 0 || cols == 0) {
        fV_imprimeSerial("Erro: número de linhas ou colunas inválido.");
        return;
    }

    // Abre o arquivo para leitura
    File file = FILESYS.open(filename, FILE_READ);
    if (!file) {
        if (filename != "/nulo.txt") {
            fV_imprimeSerial("Erro ao abrir o arquivo para leitura, inicializando com valores vazios.");
        }

        // Inicializa o array com valores vazios se o arquivo não existir ou não puder ser aberto
        array = new uint16_t*[rows];
        for (size_t i = 0; i < rows; i++) {
            array[i] = new uint16_t[cols];
            for (size_t j = 0; j < cols; j++) {
                array[i][j] = 0;  // Preenche com zero (ou valor padrão)
            }
        }
        return;
    }

    // Libera memória previamente alocada, se necessário
    if (array != nullptr) {
        for (size_t i = 0; i < rows; i++) {
            delete[] array[i];
        }
        delete[] array;
    }

    // Aloca memória para o array
    array = new uint16_t*[rows];
    for (size_t i = 0; i < rows; i++) {
        array[i] = new uint16_t[cols];
    }

    // Lê o conteúdo do arquivo como uma String
    String content = file.readString();
    file.close();  // Fecha o arquivo

    // Processa a String para preencher o array
    size_t i = 0, j = 0;
    int index = 0;
    String numStr;
    while (index < content.length()) {
        // Extrai o número até encontrar um caractere não numérico
        char c = content[index];
        if (c >= '0' && c <= '9') {
            numStr += c;  // Adiciona o caractere à string do número
        } else {
            if (numStr.length() > 0) {
                int value = numStr.toInt();
                if (i < rows && j < cols) {
                    array[i][j] = static_cast<uint16_t>(value);
                    j++;
                    if (j >= cols) {
                        j = 0;
                        i++;
                    }
                }
                numStr = "";  // Limpa a string para o próximo número
            }
        }
        index++;
    }

    // Adiciona o último número se houver
    if (numStr.length() > 0) {
        int value = numStr.toInt();
        if (i < rows && j < cols) {
            array[i][j] = static_cast<uint16_t>(value);
        }
    }

    // Preenche o restante do array com zeros se o arquivo não tiver todos os dados
    while (i < rows) {
        while (j < cols) {
            array[i][j] = 0;
            j++;
        }
        j = 0;
        i++;
    }
    fV_imprimeSerial(" OK", true);    
}

//========================================
void fV_salvaFlash_AUint(const char* filename, uint8_t** arr, size_t rows, size_t cols) {
    fV_imprimeSerial("Salvando arquivo: ", false);
    fV_imprimeSerial(filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial("LittleFS nao esta inicializado.");
        return;
    }

    if (rows == 0 || cols == 0) {
        fV_imprimeSerial("Erro: número de linhas ou colunas inválido.");
        return;
    }

    File file = FILESYS.open(filename, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial("Erro ao abrir o arquivo para escrita.");
        return;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            file.printf("%u", arr[i][j]);
            if (j < cols - 1) {
                file.print(",");
            }
        }
        file.println();
    }

    file.close();
    fV_imprimeSerial(" OK", true);
}

//========================================
void fV_carregaFlash_AUint(const char* filename, uint8_t**& array, size_t rows, size_t cols, String sol) {
    fV_imprimeSerial("Carregando arquivo: ("+sol+"): ", false);
    fV_imprimeSerial(filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial("LittleFS nao esta inicializado.");
        return;
    }

    if (rows == 0 || cols == 0) {
        fV_imprimeSerial("Erro: número de linhas ou colunas inválido.");
        return;
    }

    File file = FILESYS.open(filename, FILE_READ);
    if (!file) {
        if (filename != "/nulo.txt") {
            fV_imprimeSerial("Erro ao abrir o arquivo para leitura, inicializando com valores vazios.");
        }
        array = new uint8_t*[rows];
        for (size_t i = 0; i < rows; i++) {
            array[i] = new uint8_t[cols];
            for (size_t j = 0; j < cols; j++) {
                array[i][j] = 0;
            }
        }
        return;
    }

    if (array != nullptr) {
        for (size_t i = 0; i < rows; i++) {
            delete[] array[i];
        }
        delete[] array;
    }

    array = new uint8_t*[rows];
    for (size_t i = 0; i < rows; i++) {
        array[i] = new uint8_t[cols];
    }

    String content = file.readString();
    file.close();

    size_t i = 0, j = 0;
    int index = 0;
    String numStr;
    while (index < content.length()) {
        char c = content[index];
        if (c >= '0' && c <= '9') {
            numStr += c;
        } else {
            if (numStr.length() > 0) {
                int value = numStr.toInt();
                if (i < rows && j < cols) {
                    array[i][j] = static_cast<uint8_t>(value);
                    j++;
                    if (j >= cols) {
                        j = 0;
                        i++;
                    }
                }
                numStr = "";
            }
        }
        index++;
    }

    if (numStr.length() > 0) {
        int value = numStr.toInt();
        if (i < rows && j < cols) {
            array[i][j] = static_cast<uint8_t>(value);
        }
    }

    while (i < rows) {
        while (j < cols) {
            array[i][j] = 0;
            j++;
        }
        j = 0;
        i++;
    }
    fV_imprimeSerial(" OK", true);
}

//========================================
void fV_imprimirArray2D_S(String** array, size_t rows, size_t cols, bool linha) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (linha) {
                fV_imprimeSerial(array[i][j]);  // Imprime o elemento
            } else {
                fV_imprimeSerial(array[i][j], false);  // Imprime o elemento

                // Somente imprime a vírgula se não for o último elemento
                if (j < cols - 1) {
                    fV_imprimeSerial(",", false);
                }
            }
        }
        // Imprime uma nova linha se estiver imprimindo por linha
        if (linha) {
            fV_imprimeSerial("");
        }
    }
}

//========================================
void fV_imprimirArray2D_U16(uint16_t** array, size_t rows, size_t cols, bool linha) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (linha) {
                fV_imprimeSerial(array[i][j]);  // Imprime o elemento
            } else {
                fV_imprimeSerial(array[i][j], false);  // Imprime o elemento

                // Somente imprime a vírgula se não for o último elemento
                if (j < cols - 1) {
                    fV_imprimeSerial(",", false);
                }
            }
        }
        // Imprime uma nova linha se estiver imprimindo por linha
        if (linha) {
            fV_imprimeSerial("");
        }
    }
}

//========================================//
//        Funcoes para impressao          //
//========================================//
void fV_imprimeSerial(const String& mensagem, bool pularLinha) {
    if (pularLinha) {
        Serial.println(mensagem);
        fV_sendSerialData(mensagem);
    } else {
        Serial.print(mensagem);
        fV_sendSerialData(mensagem);
    }
}
void fV_imprimeSerial(const char* mensagem, bool pularLinha) {
    fV_imprimeSerial(String(mensagem), pularLinha);
}
void fV_imprimeSerial(int valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(size_t valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(uint8_t valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(uint16_t valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(bool valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor ? "true" : "false");
        fV_sendSerialData(String(valor ? "true" : "false")+"<br>");
    } else {
        Serial.print(valor ? "true" : "false");
        fV_sendSerialData(String(valor ? "true" : "false"));
    }
}
void fV_imprimeSerial(float valor, bool pularLinha, int casasDecimais) {
    if (pularLinha) {
        Serial.println(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais)+"<br>");
    } else {
        Serial.print(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais));
    }
}
void fV_imprimeSerial(double valor, bool pularLinha, int casasDecimais) {
    if (pularLinha) {
        Serial.println(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais)+"<br>");
    } else {
        Serial.print(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais));
    }
}
void fV_imprimeSerial(String mensagem, uint16_t numero, bool pularLinha) {
    if (pularLinha) {
        Serial.print(mensagem);
        Serial.println(numero);
        fV_sendSerialData(mensagem+String(numero)+"<br>");
    } else {
        Serial.print(mensagem);
        Serial.print(numero);
        fV_sendSerialData(mensagem+String(numero));
    }
}
void fV_imprimeSerial(const uint16_t** array, size_t rows, size_t cols, bool pularLinha) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            Serial.print(array[i][j]);
            fV_sendSerialData(String(array[i][j]));
            if (j < cols - 1) {
                Serial.print(", ");
                fV_sendSerialData(", ");
            }
        }
        if (pularLinha) {
            Serial.println();
            fV_sendSerialData("<br>");
        }
    }
}
void fV_imprimeSerial(const String** array, size_t rows, size_t cols, bool pularLinha) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            Serial.print(array[i][j]);
            fV_sendSerialData(array[i][j]);
            if (j < cols - 1) {
                Serial.print(", ");
                fV_sendSerialData(", ");
            }
        }
        if (pularLinha) {
            Serial.println();
            fV_sendSerialData("<br>");
        }
    }
}
//========================================//
//      Fim Funcoes para impressao        //
//========================================//