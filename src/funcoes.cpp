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
uint16_t fU16_pinosUsados() {
  uint16_t resultado = 0;
  for (int x=0;x<aU32_Variaveis[36];x++) {
    if (aU16_Pinos[0][x] > 0) {
      resultado++;
    }
  }
  return resultado;
}

//========================================
uint16_t fU16_separaPinos(String pinos) {
  uint16_t resultado = 0;

  return resultado;
}

//========================================
uint8_t fU8_retornaIndiceHS(String modulo) {
  uint8_t resultado = 0;
  for (uint8_t x=0; x<vU8_totModulos; x++) {
    if (aS_InterMod[0][x] == modulo) {
      resultado = x;
      break;
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

/*========================================
Funcao HandShake, envia sinal de handshake para testar comunicacao entrte modulos
*/
void fV_checkHandShake() {
  uint64_t agora = millis();
  if (!vB_pausaEXECs && vB_exec_Modulos) {
    if ((agora - aU64_Variaveis[2]) > vU16_modulos_HandShake) {
      for (uint8_t y=0; y<vU8_totModulos; y++) {
        if (aI16_InterMod_CTRL_HandShake[0][y] < 1) {
          aI16_InterMod_CTRL_HandShake[1][y] = 1;
          //vB_envia_Historico = true;
        } else {
          aI16_InterMod_CTRL_HandShake[0][y]--;
        }
        if ( aB_InterMod[0][y] && aU16_InterMod[0][y] > 0 ) {
          aI16_InterMod_CTRL_HandShake[2][y] = fI_enviaModulo(aU16_InterMod[0][y],"65535", String(aU16_InterMod[0][fU8_retornaIndiceHS(aS_Variaveis[0])]), "0");
          if (aI16_InterMod_CTRL_HandShake[2][y] == 200) {
            aI16_InterMod_CTRL_HandShake[0][y] = vI_cicloHandshake;
            aI16_InterMod_CTRL_HandShake[1][y] = 0;
            aI16_InterMod_CTRL_HandShake[3][fI_retornaModulo(aS_Variaveis[0])] = 0;
          }
        }
        if ( fU16_retornaIndicePino(aU16_InterMod[0][y]) > 0 && fU16_retornaIndicePino(aU16_InterMod[0][y]) < 65535 ) {
          aU16_Pinos_Status[0][fU16_retornaIndicePino(aU16_InterMod[0][y])] = aI16_InterMod_CTRL_HandShake[1][y];
        }
      }
      aU64_Variaveis[2] = agora;
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

/*========================================
Funcao enviar informacoes para outro modulo
*/
int fI_enviaModulo(uint16_t idmodulo, String acao, String pino, String valor) {
  vI_httpResponseCode = 0;
  int resposta = 504;
  uint16_t moduloIdx = fU16_retornaIndiceModulo(idmodulo);
 if (aI16_InterMod_CTRL_HandShake[3][fU16_retornaIndiceModulo(idmodulo)] < vU8_tentativaConexoes) {
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
                           "/dados?pl=" + aS_Variaveis[0] + "&ac=" + acao + "&pn=" + pino + "&vl=" + valor;
        } else {
          GET_SERVIDOR = "http://" + fS_retornaIpModulo(idmodulo) + ":" + vI_U16_portaWebAsync +
                        "/dados?pl=" + aS_Variaveis[0] + "&ac=" + acao + "&pn=" + pino + "&vl=" + valor;
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
                aI16_InterMod_CTRL_HandShake[0][moduloIdx] = vI_cicloHandshake;
                aI16_InterMod_CTRL_HandShake[1][moduloIdx] = 0;
                aI16_InterMod_CTRL_HandShake[2][moduloIdx] = statusCode;
                aI16_InterMod_CTRL_HandShake[3][moduloIdx] = 0;
                aU32_Variaveis[28] = idmodulo;
              } else {
                  aI16_InterMod_CTRL_HandShake[2][moduloIdx] = statusCode;
                  aI16_InterMod_CTRL_HandShake[3][moduloIdx] = aI16_InterMod_CTRL_HandShake[3][moduloIdx] + 1;
                  //(aI16_InterMod_CTRL_HandShake[3][moduloIdx] < vU8_tentativaConexoes)  //32766
                  //                                ? aI16_InterMod_CTRL_HandShake[3][moduloIdx] + 1 
                  //                                : 1;
              }
              fV_imprimeSerial(3,"HTTP Response code: " + String(statusCode));
              fV_imprimeSerial(3,"Payload: " + payload);
            }
        }, nullptr);  // Passar nullptr como argumento para a lambda
        CLIENTE_WEB_ASYNC->send();  // Envia a requisição assíncrona
        fV_imprimeSerial(3,"Enviado: " + GET_SERVIDOR);
        request_in_progress = false;
      } else {
        fV_imprimeSerial(1,"Aguardando para enviar informacoes");
      }
    }
  } else {
    aI16_InterMod_CTRL_HandShake[3][moduloIdx] = aI16_InterMod_CTRL_HandShake[3][moduloIdx] +1;
    if (aI16_InterMod_CTRL_HandShake[3][moduloIdx] > vI8_aS16_InterModFila_EnviaModulo) {
      aI16_InterMod_CTRL_HandShake[3][moduloIdx] = 0;
    }
  }
  return resposta;
}

/*========================================
Funcao para enviar a outro modulo a fila de status dos alertas
*/
void fV_enviaAcoesModulos() {
  uint64_t agora = millis();
  if (!vB_pausaEXECs && vB_exec_Modulos) {
    if ((agora - aU64_Variaveis[1]) > (vU16_modulos_MTBS_Acoes+500)) {
      for (uint8_t x=0; x<aU32_Variaveis[36]; x++) {
        if (aS16_InterModFila_EnviaModulo[0][x] > 0) {
          if ( fI_enviaModulo(aS16_InterModFila_EnviaModulo[0][x], String(aS16_InterModFila_EnviaModulo[1][x]), String(aS16_InterModFila_EnviaModulo[2][x]), String(aS16_InterModFila_EnviaModulo[3][x])) == 200) {
            aS16_InterModFila_EnviaModulo[0][x] = 0;
            aS16_InterModFila_EnviaModulo[1][x] = 0;
            aS16_InterModFila_EnviaModulo[2][x] = 0;
            aS16_InterModFila_EnviaModulo[3][x] = 0;
          }
        }
      }
      aU64_Variaveis[1] = agora;
    }
  }
}

//========================================
void fV_restartTasks() {
  fV_imprimeSerial(1,"As tarefas serao reiniciadas.");
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
    fV_imprimeSerial(1,"A execucao das rotinas foi pausada.");
  } else {
    fV_imprimeSerial(1,"A execucao das rotinas foi retomada.");
  }
}

//========================================
void fV_Preference(String op, bool force) {
  fV_imprimeSerial(1,"Iniciando configuracao de parametros...", false);
  if (op == "L") {
    fV_carregaFILESYS_AS2D("/aS_Preference.txt",aS_Preference,1,ARRAY_PREFERENCE_COL);
  } else if (op == "E") {
    fV_salvaFILESYS_AS2D("/aS_Preference.txt",aS_Preference,1,ARRAY_PREFERENCE_COL);
  }
  fV_imprimeSerial(1," OK");
}

//========================================
bool fB_verificaPrimeiraExec(bool force) {
  bool resultado = false; // Inicialmente, assume que nem todos os arquivos existem
  int arquivosExistentes = 0; // Contador para arquivos existentes
  int totalArquivos = 13;
  fV_imprimeSerial(1,"Verificando arquivos de configuracao...");
  String aS_checkFiles[totalArquivos] = {
      "aU8_diasDaSemana", "aU8_meses", "aS16_PinosMenu", "aS8_AcoesMenu", 
      "aS8_AcoesStringMenu", "aS8_AcoesRedeMenu", "aS_InterModMenu",
      "aU16_InterModMenu", "aSB_InterModMenu", "nulo","aS_Preference",
      "aS16_InterModMenu_CTRL_HandShake", "aS8_ControlMsgModHist" };

  // Percorre cada arquivo do array
  for (uint8_t i = 0; i < totalArquivos; i++) {
      String fileName = "/" + aS_checkFiles[i] + ".txt"; // Adiciona extensão .txt ao nome do arquivo
      bool fileExists = FILESYS.exists(fileName); // Verifica se o arquivo existe
      // Se o arquivo não existir ou se "force" for verdadeiro, recria o arquivo
      fV_imprimeSerial(1,"Verificando arquivo: "+ String(i) + " - " + fileName);
      if (!fileExists || force) {
          fV_imprimeSerial(1,"Recriando arquivo: " + fileName);
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
              } else if (aS_checkFiles[i] == "aS16_InterModMenu_CTRL_HandShake") {
                  defaultValues = "Ciclo,Status,Código HTTP,Envio Pausado";
              } else if (aS_checkFiles[i] == "aS8_ControlMsgModHist") {
                  defaultValues = "Módulo,Ação,Pino,Valor";
              } else if (aS_checkFiles[i] == "nulo") {
                  defaultValues = "";
              } else if (aS_checkFiles[i] == "aS_Preference") {
                  defaultValues = String("wifi,") + //0
                                  String("12345678,") + //1
                                  String("4,") + //2
                                  String("4080,") + //3
                                  String("esp32modularx,") + //4
                                  String("admin,") + //5
                                  String("admin,") + //6
                                  String("esp32modularx_" + aS_Variaveis[13] + ",") + //7
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
                                  String("2147483647") + //44
                                  String("12") + //45
                                  String("8") + //46
                                  String("7") + //47
                                  String("false") + //48
                                  String("0") + //49
                                  String("5") + //50
                                  String("50") + //51
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
              fV_imprimeSerial(1,"Arquivo recriado: " + fileName);
          } else {
              fV_imprimeSerial(1,"Erro ao criar arquivo: " + fileName);
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
  fV_imprimeSerial(1,"Verificação de arquivos finalizada.");
  return resultado;
}

//========================================
bool fV_regModHist(uint16_t idmodulo, uint16_t acao, uint16_t pino, uint16_t valor) {
  aS16_InterModFila_EnviaModulo[0][vU8_crtl_ModHist] = idmodulo;
  aS16_InterModFila_EnviaModulo[1][vU8_crtl_ModHist] = acao;
  aS16_InterModFila_EnviaModulo[2][vU8_crtl_ModHist] = pino;
  aS16_InterModFila_EnviaModulo[3][vU8_crtl_ModHist] = valor;
  vU8_crtl_ModHist++;
  if (vU8_crtl_ModHist >= vI8_aS16_InterModFila_EnviaModulo) {
    vU8_crtl_ModHist = 0;
  }
  return true;
}

//========================================
void fV_checkAcoesModulos() {
  uint64_t agora = millis();
  if (!vB_pausaEXECs && vB_exec_Modulos) {
    if ((agora - aU64_Variaveis[0]) > vU16_modulos_MTBS_Acoes) {
      for (uint8_t x=0; x<aU32_Variaveis[36]; x++) {
        if ((aU8_AcaoRede1[0][x] > 0 ) && (aU16_Pinos_Status[0][x] >= aU16_Pinos[4][x]) && (aS16_InterModControleRepeticao_EnviaModulo[0][x] < 1)) {
          if (fV_regModHist(aU8_AcaoRede1[0][x],aU16_Acao1[2][x], aU16_Acao1[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[0][x] = 1;
          }
        } else if ((aU8_AcaoRede1[0][x] >0 ) && (aU16_Pinos_Status[0][x] < aU16_Pinos[4][x]) && (aS16_InterModControleRepeticao_EnviaModulo[0][x] > 0)) {
          if (fV_regModHist(aU8_AcaoRede1[0][x],aU16_Acao1[2][x], aU16_Acao1[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[0][x] = 0;
          }
        } else if (vB_envia_Historico && (aU8_AcaoRede1[0][x] >0)){
          fV_regModHist(aU8_AcaoRede1[0][x],aU16_Acao1[2][x], aU16_Acao1[5][x], aU16_Pinos_Status[0][x]);
        }


        if ((aU8_AcaoRede2[0][x] >0 ) && (aU16_Pinos_Status[0][x] >= aU16_Pinos[4][x]) && (aS16_InterModControleRepeticao_EnviaModulo[1][x] < 1)) {
          if (fV_regModHist(aU8_AcaoRede2[0][x],aU16_Acao2[2][x], aU16_Acao2[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[1][x] = 1;
          }
        } else if ((aU8_AcaoRede2[0][x] >0 ) && (aU16_Pinos_Status[0][x] < aU16_Pinos[4][x]) && (aS16_InterModControleRepeticao_EnviaModulo[1][x] > 0)){
          if (fV_regModHist(aU8_AcaoRede2[0][x],aU16_Acao2[2][x], aU16_Acao2[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[1][x] = 0;
          }
        } else if (vB_envia_Historico && (aU8_AcaoRede2[0][x] >0)){
          fV_regModHist(aU8_AcaoRede2[0][x],aU16_Acao2[2][x], aU16_Acao2[5][x], aU16_Pinos_Status[0][x]);
        }


        if ((aU8_AcaoRede3[0][x] >0 ) && (aU16_Pinos_Status[0][x] >= aU16_Pinos[4][x])&& (aS16_InterModControleRepeticao_EnviaModulo[2][x] < 1)) {
          if (fV_regModHist(aU8_AcaoRede3[0][x], aU16_Acao3[2][x], aU16_Acao3[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[2][x] = 1;
          }
        } else if ((aU8_AcaoRede3[0][x] >0 ) && (aU16_Pinos_Status[0][x] < aU16_Pinos[4][x]) && (aS16_InterModControleRepeticao_EnviaModulo[2][x] > 0)){
          if (fV_regModHist(aU8_AcaoRede3[0][x], aU16_Acao3[2][x], aU16_Acao3[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[2][x] = 0;
          }
        } else if (vB_envia_Historico && (aU8_AcaoRede3[0][x] >0)){
          fV_regModHist(aU8_AcaoRede3[0][x],aU16_Acao3[2][x], aU16_Acao3[5][x], aU16_Pinos_Status[0][x]);


        if ((aU8_AcaoRede4[0][x] >0 ) && (aU16_Pinos_Status[0][x] >= aU16_Pinos[4][x])&& (aS16_InterModControleRepeticao_EnviaModulo[3][x] < 1)) {
          if (fV_regModHist(aU8_AcaoRede4[0][x], aU16_Acao4[2][x], aU16_Acao4[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[3][x] = 1;
          }
        } else if ((aU8_AcaoRede4[0][x] >0 ) && (aU16_Pinos_Status[0][x] < aU16_Pinos[4][x]) && (aS16_InterModControleRepeticao_EnviaModulo[3][x] > 0)){
          if (fV_regModHist(aU8_AcaoRede4[0][x], aU16_Acao4[2][x], aU16_Acao4[5][x], aU16_Pinos_Status[0][x])) {
            aS16_InterModControleRepeticao_EnviaModulo[3][x] = 0;
          }
        } else if (vB_envia_Historico && (aU8_AcaoRede4[0][x] >0)){
          fV_regModHist(aU8_AcaoRede4[0][x],aU16_Acao4[2][x], aU16_Acao4[5][x], aU16_Pinos_Status[0][x]);
        }

        }
      }
      vB_envia_Historico = false;
      aU64_Variaveis[0] = agora;
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
  for (uint8_t x=0; x<aU32_Variaveis[36]; x++) {
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
            fV_imprimeSerial(1,"Hora ainda nao ajustada.");
        }
        hora_lasttime = agora;  // Atualiza o último tempo da execução
    }
  }
  return resultado;  
}

//========================================
void fV_grupoAcoes(bool force) {
  // Zerar array de grupo de acoes
  fV_imprimeSerial(1,"Iniciando formacoes de grupos de acoes...");
  if (force) {
    for (uint8_t i = 0; i < vI8_ControlAcoesGroups; i++) {
      for (uint8_t j = 0; j < aU32_Variaveis[36]; j++) {
        aU16_ControlAcoesGroups[i][j] = 0;
      }
    }
    for (uint8_t x = 0; x < aU32_Variaveis[36]; x++) {
      if (aU16_Pinos[0][x] > 0) {
        aU16_ControlAcoesGroups[0][x] = aU16_Pinos[0][x];
      }
    }
  }

  // Inicia em 1 pq 0 significa pino nao cadastrado
  int xyz = 1;

  fV_imprimeSerial(1,"Formando grupo acoes1: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < aU32_Variaveis[36]; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < aU32_Variaveis[36]; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao1[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao1[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(1,1,xyz-1);

  fV_imprimeSerial(1,"Formando grupo acoes2: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < aU32_Variaveis[36]; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < aU32_Variaveis[36]; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao2[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao2[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(1,1,xyz-1);

  fV_imprimeSerial(1,"Formando grupo acoes3: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < aU32_Variaveis[36]; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < aU32_Variaveis[36]; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao3[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao3[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(1,1,xyz-1);

  fV_imprimeSerial(1,"Formando grupo acoes4: ",false);
  // Para cada pino de destino
  for (uint8_t destIndex = 0; destIndex < aU32_Variaveis[36]; destIndex++) {
    uint16_t destPin = aU16_ControlAcoesGroups[0][destIndex];
    // Se o pino de destino estiver cadastrado
    if (destPin != 0) {
      // Para cada ação associada a esse pino de destino
      for (uint8_t actionIndex = 0; actionIndex < aU32_Variaveis[36]; actionIndex++) {
        // Verifica se há uma ação associada a esse pino de destino
        if (aU16_Acao4[1][actionIndex] == destPin) {
          // Associa o pino de origem ao pino de destino no array de grupo de ações
          aU16_ControlAcoesGroups[xyz][destIndex] = aU16_Acao4[0][actionIndex];
          xyz++;
        }
      }
    }
  }
  fV_imprimeSerial(1,1,xyz-1);  
  fV_imprimeSerial(1,"Formacao de grupos de acoes finalizado.");
}

//========================================
void fV_restart() {
    fV_imprimeSerial(1,"Reiniciando o modulo ",false);
    fV_imprimeSerial(1,aS_Variaveis[0]);
    delay(20000);
    esp_restart();
}

//========================================
void fV_formataFLASH () {
    fV_imprimeSerial(1,"Particao NVS sendo formatada, todas as informacoes serão perdidas...",false);
    fV_apagaTodosArquivosSPIFFS();
    nvs_flash_erase(); //apague a partição NVS
    nvs_flash_init(); //inicializa a partição NVS
    fV_imprimeSerial(1," OK");
}

//========================================
uint64_t fU64_stringToULong64(const String& str) {
    return strtoull(str.c_str(), nullptr, 10);
}

//========================================
void fV_configuraWatchDog(const bool force) {
    if (vB_exec_WatchDog || force) {
        fV_imprimeSerial(1,"Configurando watchdog e iniciando...",false);
        vU16_clockESP32 = fU16_carregaConfigGeral(0,42,80); // clock do ESP32 para whatchdog
        aU32_Variaveis[21] = fU32_carregaConfigGeral(0,44,2147483647); // Tempo para whatchdog
        vHW_timer = timerBegin(0, vU16_clockESP32, true);  // TimerID 0, div 80 (clock do esp), contador progressivo
        timerAttachInterrupt(vHW_timer, &fV_resetModule, true);
        timerAlarmWrite(vHW_timer, aU32_Variaveis[21], true);  // Timer, tempo (us), repeticao
        timerAlarmEnable(vHW_timer);  // Habilita a interrupcao
        vB_emExecucaoWDog = true;
    } else {
        fV_imprimeSerial(1,"Configurando watchdog...",false);
        vB_exec_WatchDog = fB_carregaConfigGeral(0,43,false);        
        vU16_clockESP32 = fU16_carregaConfigGeral(0,42,80); // clock do ESP32 para whatchdog
        aU32_Variaveis[21] = fU32_carregaConfigGeral(0,44,2147483647); // Tempo para whatchdog
    }
    fV_imprimeSerial(1," OK");    
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
    fV_imprimeSerial(1,"Iniciando configuracao das Acoes...");

    bool addass = false;

    fV_carregaFILESYS_AS2D("/aS8_AcoesMenu.txt",aS8_AcoesMenu,1,aU32_Variaveis[36]);
    fV_carregaFILESYS_AS2D("/aS8_AcoesRedeMenu.txt",aS8_AcoesRedeMenu,1,aU32_Variaveis[36]);
    fV_carregaFILESYS_AS2D("/aS8_AcoesStringMenu.txt",aS8_AcoesStringMenu,1,aU32_Variaveis[36]);

    // Acoes 1  
    fV_carregaFlash_AUint("/aU16_Acao1.txt", aU16_Acao1, vI8_aU16_Acao, aU32_Variaveis[36]);
    fV_carregaFlash_AUint("/aU8_AcaoRede1.txt", aU8_AcaoRede1, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
    fV_carregaFILESYS_AS2D("/aS8_Acao1.txt",aS8_Acao1,vI8_aS8_Acao,aU32_Variaveis[36]);
  
    // Acoes 2
    fV_carregaFlash_AUint("/aU16_Acao2.txt", aU16_Acao2, vI8_aU16_Acao, aU32_Variaveis[36]);
    fV_carregaFlash_AUint("/aU8_AcaoRede2.txt", aU8_AcaoRede2, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
    fV_carregaFILESYS_AS2D("/aS8_Acao2.txt",aS8_Acao2,vI8_aS8_Acao,aU32_Variaveis[36]);

    // Acoes 3
    fV_carregaFlash_AUint("/aU16_Acao3.txt", aU16_Acao3, vI8_aU16_Acao, aU32_Variaveis[36]);
    fV_carregaFlash_AUint("/aU8_AcaoRede3.txt", aU8_AcaoRede3, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
    fV_carregaFILESYS_AS2D("/aS8_Acao3.txt",aS8_Acao3,vI8_aS8_Acao,aU32_Variaveis[36]);

    // Acoes 4
    fV_carregaFlash_AUint("/aU16_Acao4.txt", aU16_Acao4, vI8_aU16_Acao, aU32_Variaveis[36]);
    fV_carregaFlash_AUint("/aU8_AcaoRede4.txt", aU8_AcaoRede4, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
    fV_carregaFILESYS_AS2D("/aS8_Acao4.txt",aS8_Acao4,vI8_aS8_Acao,aU32_Variaveis[36]);

    fV_imprimeSerial(1,"Configuracao das acoes finalizada");
    fV_grupoAcoes(false);
}

//========================================
void fV_configuraModulos(bool force) {
  fV_imprimeSerial(1,"Iniciando configuracao dos modulos...", false);
  if (!force) {
    vB_exec_Modulos = fB_carregaConfigGeral(0,35, false);
    vU16_modulos_HandShake = fU16_carregaConfigGeral(0,36, 65535);
    vU16_modulos_MTBS_Acoes = fU16_carregaConfigGeral(0,37, 65535);
    vU8_totModulos = fU8_carregaConfigGeral(0,47,7);
    vI_cicloHandshake = fI32_carregaConfigGeral(0,38, 65535);
    vI8_aS16_InterModFila_EnviaModulo = fU16_carregaConfigGeral(0,51, 40);

    fV_carregaFlash_AUint("/aU16_InterMod.txt", aU16_InterMod, vI8_aU16_InterMod, vU8_totModulos);
    fV_carregaFlash_AUint("/aB_InterMod.txt", aB_InterMod, vI8_aB_InterMod, vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS_InterMod.txt",aS_InterMod,vI8_aS_InterMod,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aU16_InterModMenu.txt",aU16_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aSB_InterModMenu.txt",aSB_InterModMenu,1,vU8_totModulos);
    fV_carregaFILESYS_AS2D("/aS_InterModMenu.txt",aS_InterModMenu,1,vU8_totModulos);



    fV_carregaFILESYS_AS2D("/aS16_InterModMenu_CTRL_HandShake.txt",aS16_InterModMenu_CTRL_HandShake,1,vI8_aU16_InterModHA);
    fV_carregaFILESYS_AS2D("/aS8_ControlMsgModHist.txt",aS8_ControlMsgModHist,1,vI8_aU8_ControlMsgHist);

    fV_carregaFlash_AUint("/nulo.txt", aI16_InterMod_CTRL_HandShake, vI8_aU16_InterModHA, vU8_totModulos);
    for (uint8_t y=0; y<vU8_totModulos; y++) {
      aI16_InterMod_CTRL_HandShake[0][y] = vI_cicloHandshake;
      aI16_InterMod_CTRL_HandShake[3][y] = 0;
    }
  } else if (force) {

  }
  fV_carregaFlash_AUint("/nulo.txt", aS16_InterModFila_EnviaModulo, vI8_aU8_ControlMsgHist, vI8_aS16_InterModFila_EnviaModulo,"aS16_InterModFila_EnviaModulo");
  fV_carregaFlash_AUint("/nulo.txt", aS16_InterModControleRepeticao_EnviaModulo, vI8_aU8_ControlMsg, aU32_Variaveis[36],"aS16_InterModControleRepeticao_EnviaModulo");  
  fV_imprimeSerial(1," OK");  
}

//========================================
void fV_salvarFlash() {
  fV_imprimeSerial(1,"Salvando informacoes em Preferences e Filesys...");

  // Preferencias
  fV_Preference("E",false);

  // Pinos
  fV_salvaFlash_AUint("/aU16_Pinos.txt", aU16_Pinos, vI8_aU16_Pinos, aU32_Variaveis[36]);
  fV_salvaFILESYS_AS2D("/aS8_Pinos.txt", aS8_Pinos, vI8_aS8_Pinos, aU32_Variaveis[36]);
  //fV_salvaFILESYS_AS2D("/aS8_AcoesMenu.txt",aS8_AcoesMenu,1,aU32_Variaveis[36]);
  //fV_salvaFILESYS_AS2D("/aS8_AcoesRedeMenu.txt",aS8_AcoesRedeMenu,1,aU32_Variaveis[36]);
  //fV_salvaFILESYS_AS2D("/aS8_AcoesStringMenu.txt",aS8_AcoesStringMenu,1,aU32_Variaveis[36]);

  // Acoes 1  
  fV_salvaFlash_AUint("/aU16_Acao1.txt", aU16_Acao1, vI8_aU16_Acao, aU32_Variaveis[36]);
  fV_salvaFlash_AUint("/aU8_AcaoRede1.txt", aU8_AcaoRede1, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
  fV_salvaFILESYS_AS2D("/aS8_Acao1.txt",aS8_Acao1,vI8_aS8_Acao,aU32_Variaveis[36]);
  // Acoes 2
  fV_salvaFlash_AUint("/aU16_Acao2.txt", aU16_Acao2, vI8_aU16_Acao, aU32_Variaveis[36]);
  fV_salvaFlash_AUint("/aU8_AcaoRede2.txt", aU8_AcaoRede2, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
  fV_salvaFILESYS_AS2D("/aS8_Acao2.txt",aS8_Acao2,vI8_aS8_Acao,aU32_Variaveis[36]);
  // Acoes 3
  fV_salvaFlash_AUint("/aU16_Acao3.txt", aU16_Acao3, vI8_aU16_Acao, aU32_Variaveis[36]);
  fV_salvaFlash_AUint("/aU8_AcaoRede3.txt", aU8_AcaoRede3, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
  fV_salvaFILESYS_AS2D("/aS8_Acao3.txt",aS8_Acao3,vI8_aS8_Acao,aU32_Variaveis[36]);
  // Acoes 4
  fV_salvaFlash_AUint("/aU16_Acao4.txt", aU16_Acao4, vI8_aU16_Acao, aU32_Variaveis[36]);
  fV_salvaFlash_AUint("/aU8_AcaoRede4.txt", aU8_AcaoRede4, vI8_aU8_AcaoRede, aU32_Variaveis[36]);
  fV_salvaFILESYS_AS2D("/aS8_Acao4.txt",aS8_Acao4,vI8_aS8_Acao,aU32_Variaveis[36]);

  // Inter Modulos
  //fV_salvaFlash_AUint("/aI16_InterMod_CTRL_HandShake.txt", aI16_InterMod_CTRL_HandShake, vI8_aS_InterMod, vU8_totModulos);
  fV_salvaFlash_AUint("/aU16_InterMod.txt", aU16_InterMod, vI8_aU16_InterMod, vU8_totModulos);
  fV_salvaFlash_AUint("/aB_InterMod.txt", aB_InterMod, vI8_aB_InterMod, vU8_totModulos);
  fV_salvaFILESYS_AS2D("/aS_InterMod.txt",aS_InterMod,vI8_aS_InterMod,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aU16_InterModMenu.txt",aU16_InterModMenu,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aS_InterModMenu.txt",aS_InterModMenu,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aS16_InterModMenu_CTRL_HandShake.txt",aS16_InterModMenu_CTRL_HandShake,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aSB_InterModMenu.txt",aSB_InterModMenu,1,vU8_totModulos);
  //fV_salvaFILESYS_AS2D("/aS8_ControlMsgModHist.txt",aS8_ControlMsgModHist,1,vU8_totModulos);
  //fV_salvaFILESYS_AS1D("/aU8_diasDaSemana.txt",aU8_diasDaSemana,vU8_diasDaSemana);
  //fV_salvaFILESYS_AS1D("/aU8_meses.txt",aU8_meses,MESES);

  fV_imprimeSerial(1,"As informacoes foram salvas");
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
bool fV_apagaTodosArquivosSPIFFS() {
    // Inicializa o SPIFFS se ainda não foi inicializado
    if (!SPIFFS.begin(true)) {  // true = format if mount failed
        fV_imprimeSerial(1,"Erro ao inicializar o SPIFFS.");
        return false;
    }

    // Abre o diretório raiz do SPIFFS
    File root = SPIFFS.open("/");
    if (!root || !root.isDirectory()) {
        fV_imprimeSerial(1,"Erro ao abrir o diretório raiz do SPIFFS.");
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

        fV_imprimeSerial(1,"Tentando apagar arquivo: ",false);
        fV_imprimeSerial(1,filename);

        // Tenta remover o arquivo
        if (!SPIFFS.remove(filename)) {
            fV_imprimeSerial(1,"Erro ao apagar arquivo: ",false);
            fV_imprimeSerial(1,filename);
            SPIFFS.end();  // Fecha SPIFFS antes de retornar
            return false;
        } else {
            fV_imprimeSerial(1,"Arquivo apagado com sucesso: ",false);
            fV_imprimeSerial(1,filename);
        }

        // Move para o próximo arquivo
        file = root.openNextFile();
    }

    // Fecha SPIFFS após todas as operações
    SPIFFS.end();
    fV_imprimeSerial(1,"Todos os arquivos foram apagados com sucesso.");
    return true;
}

//========================================
void fV_iniciaPreference(bool force) {
  vS_corStatus1 = fS_carregaConfigGeral(0,13,"Tomato");
  vS_corStatus0 = fS_carregaConfigGeral(0,14,"LightGreen");
  aU32_Variaveis[3] = fU8_carregaConfigGeral(0,45,12);
  aU32_Variaveis[4] = fU8_carregaConfigGeral(0,46,8);
  vU8_colunasTabelas = fU8_carregaConfigGeral(0,40,7);
  aU32_Variaveis[35] = fU8_carregaConfigGeral(0,50,5);
  aU32_Variaveis[24] = fU8_carregaConfigGeral(0,52,2);

//uint64_t aU64_Variaveis[0] = 0;

}

//========================================
void fV_iniciaPinos(bool force) {
    fV_imprimeSerial(1,"Iniciando configuracao dos pinos...");
    if (!force) {
      aU32_Variaveis[36] = fU8_carregaConfigGeral(0,39,5);
    }
    analogSetWidth(aU32_Variaveis[3]);

    if (vU8_colunasTabelas > aU32_Variaveis[36]) {
      vU8_colunasTabelas = aU32_Variaveis[36];
    }
    fV_carregaFlash_AUint("/aU16_Pinos.txt", aU16_Pinos, vI8_aU16_Pinos, aU32_Variaveis[36]);

    fV_carregaFlash_AUint("/nulo.txt", aU16_Pinos_Status, 1, aU32_Variaveis[36],"aU16_Pinos_Status");

    if (aU16_ControlAcoesGroups != nullptr ){
      for (int i = 0; i < vI8_ControlAcoesGroups; i++) {
        delete[] aU16_ControlAcoesGroups[i]; // Libera cada linha
      }
      delete[] aU16_ControlAcoesGroups; // Libera o array de ponteiros
      aU16_ControlAcoesGroups = nullptr; // Define o ponteiro para nullptr
    }
    vI8_ControlAcoesGroups = (aU32_Variaveis[36] * 4) + 1;
    fV_carregaFlash_AUint("/nulo.txt", aU16_ControlAcoesGroups, vI8_ControlAcoesGroups, aU32_Variaveis[36],"aU16_ControlAcoesGroups");
    for (uint8_t x=0; x<aU32_Variaveis[36]; x++){
      if (aU16_Pinos[0][x] > 0 ) {
        aU16_ControlAcoesGroups[0][x] = aU16_Pinos[0][x];
        if (aU16_Pinos[1][x] == 1 || aU16_Pinos[1][x] == 192) {
          pinMode(aU16_Pinos[0][x],aU16_Pinos[2][x]);
        }
      }
    }

    fV_carregaFILESYS_AS2D("/aS16_PinosMenu.txt",aS16_PinosMenu,1,vI8_aU16_Pinos);
    fV_carregaFILESYS_AS2D("/aS8_Pinos.txt", aS8_Pinos, vI8_aS8_Pinos, aU32_Variaveis[36]);

    fV_imprimeSerial(1,"Configuracao dos pinos finalizada");
}

//========================================
void f_cria_MDNS(String nome, IPAddress ip, uint16_t porta) {
  fV_imprimeSerial(1,"Configurando mDNS: ",false);
  if (!MDNS.begin(nome.c_str())) {
    fV_imprimeSerial(1,"ERRO",true);
  } else {
    MDNS.addService("_http", "_tcp", porta);
    fV_imprimeSerial(1,"OK",true);
  }
}

//========================================
void fV_configNTP() {
  fV_imprimeSerial(1,"Configurando NTP: ",false);
  sntp_set_time_sync_notification_cb( fV_callbackNTP );
  sntp_servermode_dhcp(1);
  configTime(3600, 3600, vS_ntpServer1.c_str(), vS_ntpServer2.c_str());
  configTzTime(vS_timeZone.c_str(), vS_ntpServer1.c_str(), vS_ntpServer2.c_str());
  fV_imprimeSerial(1,"OK",true);
}

//========================================
void fV_callbackNTP(struct timeval *t) {
  // Callback function (get's called when time adjusts via NTP)
  fV_imprimeSerial(1,"Executado ajuste de tempo do NTP!!",true);
  fV_imprimeSerial(1,fS_DataHora(),true);
}

//========================================
void fV_modoAP(String wifi, String senha, uint16_t portaap) {
  WiFi.disconnect();
  fV_imprimeSerial(1,"Entrando em modo AP... ", true);
  aB_Variaveis[6] = false;
  delay(1000);
  WiFi.softAP(wifi.c_str(), senha.c_str());

  // Criação do servidor web na porta especificada
  if (SERVIDOR_WEB_ASYNC != nullptr) {
    delete SERVIDOR_WEB_ASYNC;
  }
  SERVIDOR_WEB_ASYNC = new AsyncWebServer(portaap);

  // Cadastro inicial do WIFI necesita os dois metodos GET e POST
  SERVIDOR_WEB_ASYNC->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    f_handle_ConfiguraWifiInicio(request);
    request->send(200, "text/html", "Configuracao Inicial do Wifi");
  });
  SERVIDOR_WEB_ASYNC->on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
    f_handle_SalvarWifiInicio(request);
  });

  SERVIDOR_WEB_ASYNC->onNotFound([](AsyncWebServerRequest *request) {
    f_handle_NotFound(request);
  });

  // Inicia o servidor web assíncrono
  SERVIDOR_WEB_ASYNC->begin();

  fV_imprimeSerial(1,"Servidor HTTP iniciado.", true);
  fV_imprimeSerial(1,"Conecte seu wifi na rede [" + wifi + "] e acesse http://", false);
  fV_imprimeSerial(1,WiFi.softAPIP().toString(), false);
  fV_imprimeSerial(1,":", false);
  fV_imprimeSerial(1,portaap, false);
  fV_imprimeSerial(1,"/ pelo navegador para configurar o SSID e SENHA na placa " + aS_Variaveis[0], true);

  // Loop de espera enquanto o modo AP está ativo
  while (1) {
    if (aB_Variaveis[6]) {
      fV_imprimeSerial(1,"Saindo do modo AP da placa " + aS_Variaveis[0] + " e reiniciando o dispositivo", true);
      delay(10000);
      esp_restart();
    }
    delay(2); // Pequeno delay para evitar sobrecarga
  }
  fV_imprimeSerial(1," OK", true);
}

//========================================
uint8_t fU8_configuraWifi() {
    fV_imprimeSerial(1,"Iniciando verificacao/configuracao do wifi...");
    if (WiFi.status() != WL_CONNECTED) {
        aS_Variaveis[1] = fS_carregaConfigGeral(0,0,"wifi"); //SSID da sua rede wifi (rede que essa placa ESP vai conectar)
        aS_Variaveis[2] = fS_carregaConfigGeral(0,1,"12345678"); //Senha da sua rede wifi (rede que essa placa ESP vai conectar)
        vU8_tentativaConexoes = fU8_carregaConfigGeral(0,2,4); //Tentativas de conexoes diversas antes de seguir com o boot(para nao ficar parado durante o boot esperando conetar em outros recursos)
        vI_U16_portaWebAsync = fU16_carregaConfigGeral(0,3,4080); //Porta do servidor web desta placa ESP
        aS_Variaveis[0] = fS_carregaConfigGeral(0,4,"esp32modularx"); //Hostname desta placa ESP na rede    
        aS_Variaveis[3] = fS_carregaConfigGeral(0,7,aS_Variaveis[0]+"_"+aS_Variaveis[13]); //Nome do wifi (SSID) que sera gerado se esta placa ESP entrar em modo AP
        aS_Variaveis[4] = fS_carregaConfigGeral(0,8, "senha12345678"); //Senha do wifi que sera gerado se esta placa ESP entrar em modo AP
        vB_modoAP = fB_carregaConfigGeral(0,9, true); //Se true esta placa ESP entra em modo AP caso nao consiga conectar no wifi definido em aS_Variaveis[1]
        vS_ntpServer1 = fS_carregaConfigGeral(0,10, "pool.ntp.br"); // Servidor NTP para sincronismo de horario
        vS_ntpServer2 = fS_carregaConfigGeral(0,11, "pool.ntp.org"); // Servidor NTP para sincronismo de horario
        vS_timeZone = fS_carregaConfigGeral(0,12, "<-03>3"); // TimeZone para sincronismo de horario
        vS_userWeb = fS_carregaConfigGeral(0,5, "admin"); // Usuario acesso HTTP
        vS_passWeb = fS_carregaConfigGeral(0,6, "admin"); // Senha acesso HTTP        

        if (aS_Variaveis[0].length() > 1) {
          WiFi.setHostname(aS_Variaveis[0].c_str());
        }
        WiFi.setAutoReconnect(true);
        WiFi.setAutoConnect(true);
        WiFi.begin(aS_Variaveis[1].c_str(), aS_Variaveis[2].c_str());
               int cont = 1;
        while (WiFi.status() != WL_CONNECTED && cont <= vU8_tentativaConexoes) {
          delay(5000);
          fV_imprimeSerial(1,"Conectando ao WiFi, status ", false);
          fV_imprimeSerial(1,WiFi.status(), false);
          fV_imprimeSerial(1," tentativa ", false);
          fV_imprimeSerial(1,cont, false);
          fV_imprimeSerial(1," de ", false);
          fV_imprimeSerial(1,vU8_tentativaConexoes, true);
          cont++;
        }
        fV_imprimeSerial(1,"Endereco IP do WIFI: ", false);
        fV_imprimeSerial(1,WiFi.localIP().toString(), false);
        fV_imprimeSerial(1,":", false);
        fV_imprimeSerial(1,vI_U16_portaWebAsync, false);
        fV_imprimeSerial(1," Hostname: ", false);
        fV_imprimeSerial(1,aS_Variaveis[0] + " ", false);
        if (WiFi.status() == WL_CONNECTED) {
          aB_Variaveis[5] = true;  
          fV_imprimeSerial(1," OK", true);
          if (aB_Variaveis[5]) {
            f_cria_MDNS(aS_Variaveis[0], WiFi.localIP(), vI_U16_portaWebAsync);
            fV_configNTP();            
          }
        } else {
          fV_imprimeSerial(1," ERRO - Informacoes usadas no WIFI: ", false);
          String passwdw = "";
          for (uint8_t x = 0; x < aS_Variaveis[2].length(); x++) {
            passwdw += "*";
          }
          fV_imprimeSerial(1,"Hostname:" + aS_Variaveis[0] + " SSID:" + aS_Variaveis[1] + " Senha:" + passwdw, true);
          if (vB_modoAP && WiFi.status() != WL_CONNECTED && !aB_Variaveis[5]) {
          fV_modoAP(aS_Variaveis[3], aS_Variaveis[4], vI_U16_portaWebAsync);
          }
        }
    } else {
        fV_imprimeSerial(1,"O Wifi já está conectado!", true);
        if (WiFi.status() == WL_CONNECTED) {
          f_cria_MDNS(aS_Variaveis[0], WiFi.localIP(), vI_U16_portaWebAsync);
          fV_configNTP();
        } else if (vB_modoAP && WiFi.status() != WL_CONNECTED && !aB_Variaveis[5]) {
          fV_modoAP(aS_Variaveis[3], aS_Variaveis[4], vI_U16_portaWebAsync);
        }
    }
    fV_imprimeSerial(1,"Verificacao/Configuracao do wifi finalizado");
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

    // Adicionar informações sobre o sistema de arquivos
    returnText += "<BR>" + fS_calculaBytes(FILESYS.totalBytes()) + " de tamanho total do sistema de arquivos<BR>";
    returnText += fS_calculaBytes(FILESYS.usedBytes()) + " usados, incluindo a estrutura de diretórios<BR>";

    // Verificar se a saída será em HTML
    if (ishtml) {
        returnText += "<form method='POST' action='/manage-files'>"; // Formulário único para download e exclusão
        returnText += "<table border='1' cellpadding='5' cellspacing='0'><tr><th align='left'>Nome</th><th align='left'>Tamanho</th><th>Selecionar</th></tr>";
    }

    // Iterar sobre os arquivos no diretório
    while (foundfile) {
        if (ishtml) {
            returnText += "<tr align='left'><td>" + String(foundfile.name()) + "</td><td>" + fS_calculaBytes(foundfile.size()) + "</td>";
            // Checkbox para seleção do arquivo
            returnText += "<td><input type='checkbox' align='center' name='files' value='" + String(foundfile.name()) + "'></td></tr>";
        }
        foundfile = root.openNextFile();  // Próximo arquivo
    }

    // Fechar arquivos e diretório
    root.close();
    foundfile.close();

    // Adicionar botões para Download, Excluir e Enviar Arquivos
    if (ishtml) {
        returnText += "</table>"; // Fechamento da tabela
        returnText += "<br><br>!! ATENÇÃO !! - Não haverá confirmação da operação após clicar nos botões.";        
        returnText += "<br><br><button type='submit' name='action' value='download'>Download Selecionados</button>"; // Botão de download
        returnText += "<br><br><button type='submit' name='action' value='delete'>Excluir Selecionados</button>"; // Botão de exclusão
        returnText += "<br><br><button type='submit' name='action' value='copia'>Copiar Selecionados</button>"; // Botão de copia
        returnText += "<label for='ipInput'>IP e Porta Destino:</label>";
        returnText += "<input type='text' id='ipInput' name='ipInput' placeholder='Ex: 192.168.1.100:4080'>";
        returnText += "</form>"; // Fechamento do formulário
    }

    return returnText;
}

//========================================
String fS_listDir(const char * dirname, uint8_t levels) {
  String resultado = "";

  fV_imprimeSerial(1,String("Listando diretorio: ") + dirname, true);
  resultado += "<br>Listando diretorio: ";
  resultado += dirname;

  // Abre o diretório com FILESYS
  File root = FILESYS.open(dirname);
  if (!root) {
    fV_imprimeSerial(1,"- falha ao abrir diretorio", true);
    resultado += "- falha ao abrir diretorio<br>";
    return resultado;
  }

  if (!root.isDirectory()) {
    fV_imprimeSerial(1," - nao e um diretorio", true);
    resultado += " - nao e um diretorio<br>";
    return resultado;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      fV_imprimeSerial(1,"  DIRETORIO : ", false);
      resultado += "<br> DIRETORIO: ";
      resultado += file.name();
      fV_imprimeSerial(1,file.name(), true);
      if (levels) {
        resultado += fS_listDir(file.path(), levels - 1);
      }
    } else {
      fV_imprimeSerial(1,"  ARQUIVO: ", false);
      resultado += "<br> ARQUIVO: ";
      resultado += file.name();
      fV_imprimeSerial(1,file.name(), false);

      fV_imprimeSerial(1,"\tTAMANHO: ", false);
      resultado += " TAMANHO:";
      resultado += file.size();
      fV_imprimeSerial(1,String(file.size()), true);
    }
    file = root.openNextFile();
  }
  fV_imprimeSerial(1,"", true);  // Linha em branco no final

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
  aS_Variaveis[13] = String(vI_chipID);

  // Construa a mensagem para impressão
  String msg = "ESP32 Chip model = ";
  msg += ESP.getChipModel();
  msg += " Rev ";
  msg += ESP.getChipRevision();
  msg += "<br>This chip has cores ";
  msg += ESP.getChipCores();
  msg += "<br>Chip ID: ";
  msg += vI_chipID;

  fV_imprimeSerial(1,msg, true);
  fV_imprimeSerial(1,"ESP32 Chip model = " + String(ESP.getChipModel()) + " Rev " + String(ESP.getChipRevision()), true);
  fV_imprimeSerial(1,"This chip has " + String(ESP.getChipCores()) + " cores", true);
  fV_imprimeSerial(1,"Chip ID: " + String(vI_chipID), true);

  return msg;
}

//========================================
bool fB_montaLittleFS() {
    // Inicializa o LittleFS no setup
    if (!FILESYS.begin(true)) {  // true = format if mount failed
        fV_imprimeSerial(1,"Erro ao inicializar o FILESYS.",true);
        return false;
    } else {
        fV_imprimeSerial(1,"FILESYS inicializado com sucesso.",true);
        return true;
    }
}

//========================================
void fV_salvaFILESYS_AS1D(const char* fileName, String* arr, uint8_t size) {
    fV_imprimeSerial(1,"Salvando dias da semana no arquivo: ", false);
    fV_imprimeSerial(1,fileName, false);

    // Abre o arquivo para escrita
    File file = FILESYS.open(fileName, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial(1,"Erro ao abrir o arquivo para escrita.", true);
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
    fV_imprimeSerial(1," OK", true);
}

//========================================
void fV_carregaFILESYS_AS1D(const char* fileName, String*& arr, uint8_t& size, String sol) {
    fV_imprimeSerial(1,"Carregando arquivo ("+sol+"): ", false);
    fV_imprimeSerial(1,fileName, false);

    // Tenta abrir o arquivo para leitura
    File file = FILESYS.open(fileName, FILE_READ);
    if (!file) {
        fV_imprimeSerial(1,"Arquivo nao encontrado ou erro ao abrir.", true);
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
    fV_imprimeSerial(1," OK", true);
}

//========================================
void fV_salvaFILESYS_AS2D(const char* fileName, String** arr, size_t rows, size_t cols) {
    fV_imprimeSerial(1,"Salvando arquivo: ", false);
    fV_imprimeSerial(1,fileName, false);

    // Abre o arquivo para escrita com FILESYS
    File file = FILESYS.open(fileName, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial(1,"Erro ao abrir o arquivo para escrita.", true);
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
    fV_imprimeSerial(1," OK", true);
}

//========================================
void fV_carregaFILESYS_AS2D(const char* fileName, String**& arr, size_t rows, size_t cols, String sol) {
    fV_imprimeSerial(1,"Carregando arquivo: ("+sol+"): ", false);
    fV_imprimeSerial(1,fileName, false);

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
            fV_imprimeSerial(1,"Arquivo nao encontrado ou erro ao abrir.", true);
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
    fV_imprimeSerial(1," OK", true);
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
    fV_imprimeSerial(1,"Salvando arquivo: ", false);
    fV_imprimeSerial(1,filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial(1,"LittleFS nao esta inicializado.");
        return;
    }

    // Verifica se os parâmetros são válidos
    if (rows == 0 || cols == 0) {
        fV_imprimeSerial(1,"Erro: número de linhas ou colunas inválido.");
        return;
    }

    // Abre o arquivo para escrita
    File file = FILESYS.open(filename, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial(1,"Erro ao abrir o arquivo para escrita.");
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
    fV_imprimeSerial(1," OK", true);
}

//========================================
void fV_carregaFlash_AUint(const char* filename, uint16_t**& array, size_t rows, size_t cols, String sol) {
    fV_imprimeSerial(1,"Carregando arquivo: ("+sol+"): ", false);
    fV_imprimeSerial(1,filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial(1,"LittleFS nao esta inicializado.");
        return;
    }

    // Verifica se os parâmetros são válidos
    if (rows == 0 || cols == 0) {
        fV_imprimeSerial(1,"Erro: número de linhas ou colunas inválido.");
        return;
    }

    // Abre o arquivo para leitura
    File file = FILESYS.open(filename, FILE_READ);
    if (!file) {
        if (filename != "/nulo.txt") {
            fV_imprimeSerial(1,"Erro ao abrir o arquivo para leitura, inicializando com valores vazios.");
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
    fV_imprimeSerial(1," OK", true);    
}

//========================================
void fV_salvaFlash_AUint(const char* filename, uint8_t** arr, size_t rows, size_t cols) {
    fV_imprimeSerial(1,"Salvando arquivo: ", false);
    fV_imprimeSerial(1,filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial(1,"LittleFS nao esta inicializado.");
        return;
    }

    if (rows == 0 || cols == 0) {
        fV_imprimeSerial(1,"Erro: número de linhas ou colunas inválido.");
        return;
    }

    File file = FILESYS.open(filename, FILE_WRITE);
    if (!file) {
        fV_imprimeSerial(1,"Erro ao abrir o arquivo para escrita.");
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
    fV_imprimeSerial(1," OK", true);
}

//========================================
void fV_carregaFlash_AUint(const char* filename, uint8_t**& array, size_t rows, size_t cols, String sol) {
    fV_imprimeSerial(1,"Carregando arquivo: ("+sol+"): ", false);
    fV_imprimeSerial(1,filename, false);
    if (!vB_filesysIniciado) {
        fV_imprimeSerial(1,"LittleFS nao esta inicializado.");
        return;
    }

    if (rows == 0 || cols == 0) {
        fV_imprimeSerial(1,"Erro: número de linhas ou colunas inválido.");
        return;
    }

    File file = FILESYS.open(filename, FILE_READ);
    if (!file) {
        if (filename != "/nulo.txt") {
            fV_imprimeSerial(1,"Erro ao abrir o arquivo para leitura, inicializando com valores vazios.");
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
    fV_imprimeSerial(1," OK", true);
}

//========================================
void fV_imprimirArray2D_S(String** array, size_t rows, size_t cols, bool linha) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (linha) {
                fV_imprimeSerial(1,array[i][j]);  // Imprime o elemento
            } else {
                fV_imprimeSerial(1,array[i][j], false);  // Imprime o elemento

                // Somente imprime a vírgula se não for o último elemento
                if (j < cols - 1) {
                    fV_imprimeSerial(1,",", false);
                }
            }
        }
        // Imprime uma nova linha se estiver imprimindo por linha
        if (linha) {
            fV_imprimeSerial(1,"");
        }
    }
}

//========================================
void fV_imprimirArray2D_U16(uint16_t** array, size_t rows, size_t cols, bool linha) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (linha) {
                fV_imprimeSerial(1,array[i][j]);  // Imprime o elemento
            } else {
                fV_imprimeSerial(1,array[i][j], false);  // Imprime o elemento

                // Somente imprime a vírgula se não for o último elemento
                if (j < cols - 1) {
                  fV_imprimeSerial(1,",", false);
                } else {
                    fV_imprimeSerial(1,"/", false);
                }
            }
        }
        // Imprime uma nova linha se estiver imprimindo por linha
        if (linha) {
            fV_imprimeSerial(1,"");
        }
    }
    fV_imprimeSerial(1,"");
}

//========================================//
//        Funcoes para impressao          //
//========================================//
void fV_imprimeSerial(uint8_t nivelLog, const String& mensagem, bool pularLinha) {
  if (nivelLog > aU32_Variaveis[24]) return;
  if (pularLinha) {
      Serial.println(mensagem);
      fV_sendSerialData(mensagem);
  } else {
      Serial.print(mensagem);
      fV_sendSerialData(mensagem);
  }
}
void fV_imprimeSerial(uint8_t nivelLog, const char* mensagem, bool pularLinha) {
    fV_imprimeSerial(nivelLog, String(mensagem), pularLinha);
}
void fV_imprimeSerial(uint8_t nivelLog, int valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(uint8_t nivelLog, size_t valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(uint8_t nivelLog, uint8_t valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(uint8_t nivelLog, uint16_t valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor);
        fV_sendSerialData(String(valor)+"<br>");
    } else {
        Serial.print(valor);
        fV_sendSerialData(String(valor));
    }
}
void fV_imprimeSerial(uint8_t nivelLog, bool valor, bool pularLinha) {
    if (pularLinha) {
        Serial.println(valor ? "true" : "false");
        fV_sendSerialData(String(valor ? "true" : "false")+"<br>");
    } else {
        Serial.print(valor ? "true" : "false");
        fV_sendSerialData(String(valor ? "true" : "false"));
    }
}
void fV_imprimeSerial(uint8_t nivelLog, float valor, bool pularLinha, int casasDecimais) {
    if (pularLinha) {
        Serial.println(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais)+"<br>");
    } else {
        Serial.print(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais));
    }
}
void fV_imprimeSerial(uint8_t nivelLog, double valor, bool pularLinha, int casasDecimais) {
    if (pularLinha) {
        Serial.println(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais)+"<br>");
    } else {
        Serial.print(valor, casasDecimais);
        fV_sendSerialData(String(valor, casasDecimais));
    }
}

void fV_imprimeSerial(uint8_t nivelLog, String mensagem, uint16_t numero, bool pularLinha) {
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
void fV_imprimeSerial(uint8_t nivelLog, const uint16_t** array, size_t rows, size_t cols, bool pularLinha) {
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
void fV_imprimeSerial(uint8_t nivelLog, const String** array, size_t rows, size_t cols, bool pularLinha) {
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