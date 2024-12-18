#include "include.h"
#include "globals.h"

//========================================
// Ajustado para incluir timeout e verificação de tamanho
void fV_enviarArquivo(const char* ipDestino, const char* nomeArquivo) {
    if (!LittleFS.exists(nomeArquivo)) {
        Serial.printf("Erro: O arquivo %s não existe no sistema de arquivos.\n", nomeArquivo);
        return;
    }

    String url = String("http://") + ipDestino + "/copia_arq";
    Serial.printf("URL para enviar arquivo: %s\n", url.c_str());

    File arquivo = LittleFS.open(nomeArquivo, "r");
    if (!arquivo) {
        Serial.printf("Falha ao abrir o arquivo %s para leitura.\n", nomeArquivo);
        return;
    }

    if (CLIENTE_WEB_ASYNC != nullptr) {
        delete CLIENTE_WEB_ASYNC;
        CLIENTE_WEB_ASYNC = nullptr;
    }
    CLIENTE_WEB_ASYNC = new asyncHTTPrequest;

    CLIENTE_WEB_ASYNC->setTimeout(10000); // Timeout de 10 segundos

    CLIENTE_WEB_ASYNC->onReadyStateChange([](void* optParm, asyncHTTPrequest* request, int readyState) {
        if (readyState == 4) {
            int httpCode = request->responseHTTPcode();
            if (httpCode == 200) {
               fV_imprimeSerial(3,"Arquivo enviado com sucesso!");
            } else {
                Serial.printf("Falha ao enviar arquivo. Código HTTP: %d\n", httpCode);
            }
        }
    });

    if (CLIENTE_WEB_ASYNC->open("POST", url.c_str())) {
        CLIENTE_WEB_ASYNC->setReqHeader("Content-Type", "application/octet-stream");
        CLIENTE_WEB_ASYNC->setReqHeader("File-Name", nomeArquivo);

        size_t tamanho = arquivo.size();
        if (tamanho > 0) {
            char* conteudo = new char[tamanho];
            arquivo.readBytes(conteudo, tamanho);

            CLIENTE_WEB_ASYNC->send(reinterpret_cast<const uint8_t*>(conteudo), tamanho);
            delete[] conteudo;

            Serial.printf("Enviando arquivo %s (%d bytes) para %s\n", nomeArquivo, tamanho, ipDestino);
        } else {
           fV_imprimeSerial(3,"Erro: Arquivo vazio, não foi enviado.");
        }
    } else {
       fV_imprimeSerial(3,"Falha ao iniciar o envio do arquivo.");
    }

    arquivo.close();
}

//========================================
void fV_recebeDados(AsyncWebServerRequest *request) {
/*
 Argumento 0 = Nome do Dispositivo
 Argumento 1 = Acao
 Argumento 2 = Numero do Pino
 Argumento 3 = Status do Pino
*/
  if (vB_exec_Modulos) {
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
        fV_imprimeSerial(3,"Recebido dados da placa " + request->arg((size_t)0));
        switch (request->arg(1).toInt()) {
          //case 0: // Parametro acao = 0(Nenhuma)
          //  aI16_InterMod_CTRL_HandShake[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
          //  aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = request->arg(3).toInt();
          //  validacao = "OK_DADO_RECEBIDO";
          //  break;
          case 65534: // Parametro acao = 65534(status)
            aI16_InterMod_CTRL_HandShake[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
            aI16_InterMod_CTRL_HandShake[1][fU8_retornaIndiceHS(request->arg((size_t)0))] = request->arg(3).toInt();
            aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = request->arg(3).toInt();
            vB_envia_Historico = true;
            validacao = "OK_DADO_RECEBIDO";
            break;
          case 65535: // Parametro acao = 65535(sincronismo)
            aI16_InterMod_CTRL_HandShake[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
            aI16_InterMod_CTRL_HandShake[1][fU8_retornaIndiceHS(request->arg((size_t)0))] = request->arg((size_t)0).toInt();
            aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = aI16_InterMod_CTRL_HandShake[1][fU8_retornaIndiceHS(request->arg((size_t)0))];
            validacao = "OK_DADO_RECEBIDO";
            break;
          default:
            aI16_InterMod_CTRL_HandShake[0][fU8_retornaIndiceHS(request->arg((size_t)0))] = vI_cicloHandshake;
            aI16_InterMod_CTRL_HandShake[1][fU8_retornaIndiceHS(request->arg((size_t)0))] = 0;
            aU16_Pinos_Status[0][fU16_retornaIndicePino(request->arg(2).toInt())] = request->arg(3).toInt();
            validacao = "OK_DADO_RECEBIDO";
            break;
        }
        fV_imprimeSerial(3,"Acao/Indice/Status " + request->arg(1) + " " + request->arg(2) + " " + request->arg(3));
        request->send(200, "text/plain", validacao);
      } else {
        fV_imprimeSerial(1,"Rejeitado dados da placa " + request->arg((size_t)0));
        fV_imprimeSerial(1,"Acao/Indice/Status " + request->arg(1) + " " + request->arg(2) + " " + request->arg(3));
        request->send(401, "text/plain", "ERRO - PLACA NAO CADASTRADA\n");
      }
    } else {
      fV_imprimeSerial(1,"Erro dados da placa " + request->arg((size_t)0));
      fV_imprimeSerial(1,"Acao/Indice/Status " + request->arg(1) + " " + request->arg(2) + " " + request->arg(3));
      request->send(400, "text/plain", "ERRO - PARAMETROS INVALIDOS\n");
    }
  } else {
    fV_imprimeSerial(3,"Intermodulos desabilitado " + request->arg((size_t)0));
    fV_imprimeSerial(3,"Acao/Indice/Status " + request->arg(1) + " " + request->arg(2) + " " + request->arg(3));
    request->send(503, "text/plain", "ERRO - INTERMODULOS REMOTO DESABILITADO\n");
  }
}

//========================================
void f_handle_SerialOutput(AsyncWebServerRequest *request) {
    // Gera o HTML da página
    String html = fS_cabecaHTML("Monitor Serial", "Saída Serial", "/serial", "/blob/main/manual/serial.md");

    html += "<h1>Monitor Serial</h1>";
    html += "<button onclick='clearOutput()'>Limpar Saída</button>"; // Botão para limpar
    html += "<button onclick='downloadOutput()'>Salvar Saída</button>"; // Botão para salvar
    html += "<div id='serialOutput' style='border:1px solid #000; padding:10px; height:300px; overflow-y:scroll;'></div>";
    html += "<script>";
    html += "var gateway = `ws://${window.location.hostname}:" + String(vI_U16_portaWebAsync) + "/ws`;"; // Define o WebSocket
    html += "var websocket;";

    // Script para inicializar e receber dados do WebSocket
    html += "function initWebSocket() {";
    html += "  websocket = new WebSocket(gateway);";
    html += "  websocket.onopen = function() {";
    html += "    console.log('WebSocket conectado!');";
    html += "  };";
    html += "  websocket.onerror = function(error) {";
    html += "    console.error('WebSocket erro:', error);";
    html += "  };";
    html += "  websocket.onclose = function() {";
    html += "    console.log('WebSocket desconectado!');";
    html += "  };";
    html += "  websocket.onmessage = function(event) {";
    html += "    let output = document.getElementById('serialOutput');";
    html += "    output.innerHTML += event.data + '<br>';";  // Adiciona os dados da Serial
    html += "    output.scrollTop = output.scrollHeight;";   // Rola para o final
    html += "  };";
    html += "}";

    // Função para limpar a saída
    html += "function clearOutput() {";
    html += "  document.getElementById('serialOutput').innerHTML = '';"; // Limpa o conteúdo
    html += "}";

    // Função para baixar a saída
    html += "function downloadOutput() {";
    html += "  let output = document.getElementById('serialOutput').innerHTML;";
    html += "  output = output.replace(/<br>/g, '\\n');"; // Substitui <br> por \n
    html += "  let blob = new Blob([output], { type: 'text/plain' });";
    html += "  let link = document.createElement('a');";
    html += "  link.href = window.URL.createObjectURL(blob);";
    html += "  link.download = 'saida_serial.txt';"; // Nome do arquivo
    html += "  link.click();"; // Simula um clique para iniciar o download
    html += "};";

    html += "window.onload = function() { initWebSocket(); };";  // Inicia o WebSocket ao carregar a página
    html += "</script>";

    html += "<input type='text' id='serialInput' placeholder='Digite aqui...'>";
    html += "<button onclick='sendToSerial()'>Enviar para Serial</button>";
    html += "<script>";
    // Função para enviar dados para o WebSocket
    html += "function sendToSerial() {";
    html += "  let input = document.getElementById('serialInput').value;";
    html += "  if (input) {";
    html += "    websocket.send(input);"; // Envia os dados via WebSocket
    html += "    document.getElementById('serialInput').value = '';"; // Limpa o campo
    html += "  }";
    html += "}";
    html += "</script>";

    html += fS_rodapeHTML("/serial", "/blob/main/manual/serial.md");

    // Envia o HTML gerado para o cliente
    request->send(200, "text/html", html);
}

//========================================
void f_handle_OpcoesFuncoes(AsyncWebServerRequest *request) {
    String html = fS_cabecaHTML("Opções Gerais", "Opções Gerais","/","/blob/main/manual/execgeral.md");
    html += "Escolha sua opção para [" + aS_Variaveis[0] + "]<br>";
    html += "<br><button id='openWebSerial'>Serial Web</button><script>document.getElementById('openWebSerial').addEventListener('click', function() { window.location.href = '/serial'; });</script><br>";
    html += "<br><button id='openPausarExecs'>Pausar/Retornar Execuções</button><script>document.getElementById('openPausarExecs').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_mudaExec'; });</script>";
    if (vB_pausaEXECs) {
        html += " (Rotinas: Desabilitadas)<br>";
        html += "<br><button id='openRestartTasks'>Reiniciar Tasks</button><script>document.getElementById('openRestartTasks').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_restartTasks&redirecionar=true'; });</script><br>";
    } else {
        html += " (Rotinas: Habilitadas)<br>";
        html += "<br><button id='openRestartTasks' disabled>Reiniciar Tasks</button><script>document.getElementById('openRestartTasks').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_restartTasks&redirecionar=true'; });</script><br>";
    }
    html += "<br><button id='openRestart'>Reiniciar o Módulo</button><script>document.getElementById('openRestart').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_restart&redirecionar=true'; });</script><br>";
    html += "<br><button id='openFormataFlash'>Formatar Flash</button><script>document.getElementById('openFormataFlash').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_formataFLASH&redirecionar=true'; });</script><br>";
    //html += "<br><button id='openCarregarModulos'>Recarregar Inter Módulos</button><script>document.getElementById('openCarregarModulos').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_configuraModulos(true)'; });</script><br>";
    //html += "<br><button id='openRecargaPinos'>Recarregar Configuração dos Pinos</button><script>document.getElementById('openRecargaPinos').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_iniciaPinos(true)'; });</script><br>";
    //html += "<br><button id='openRecargaAcoes'>Recarregar Configuração das Ações</button><script>document.getElementById('openRecargaAcoes').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_iniciaAcoes(true)'; });</script><br>";
    html += "<br><button id='openRecargaGAcoes'>Recarregar Grupos das Ações</button><script>document.getElementById('openRecargaGAcoes').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_grupoAcoes(true)'; });</script><br>";
    html += "<br><button id='openRecargaWatchD'>Recarregar WhatchDog</button><script>document.getElementById('openRecargaWatchD').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_configuraWatchDog(true)&redirecionar=true'; });</script><br>";    
    html += fS_rodapeHTML("/","/blob/main/manual/execgeral.md");
  request->send(200, "text/html", html);
}

//========================================
void f_handle_salvarCadastroGeral(AsyncWebServerRequest *request) {
    int erro = 0;
    if (request->hasParam("MOSTSTAT", true)) {
        VB_mostra_Status = request->getParam("MOSTSTAT", true)->value().toInt();
    } else {
        VB_mostra_Status = 0; // Checkbox desmarcada, valor padrao
    }
    aS_Preference[0][48] = String(VB_mostra_Status);
    if (request->hasParam("MOSTINTERM", true)) {
        VB_mostra_Interm = request->getParam("MOSTINTERM", true)->value().toInt();
    } else {
        VB_mostra_Interm = 0; // Checkbox desmarcada, valor padrao
    }
    aS_Preference[0][49] = String(VB_mostra_Interm);    
    if (request->hasParam("CORSTAT1", true)) {
        vS_corStatus1 = fS_limpaEspacoFimLinha(request->getParam("CORSTAT1", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro no parametro CORSTAT1");
    }
    aS_Preference[0][13] = vS_corStatus1;
    if (request->hasParam("CORSTAT0", true)) {
        vS_corStatus0 = fS_limpaEspacoFimLinha(request->getParam("CORSTAT0", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro no parametro CORSTAT0");
    }
    aS_Preference[0][14] = vS_corStatus0;
    if (request->hasParam("TREFRESH", true)) {
        vU8_tempoRefresh = request->getParam("TREFRESH", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro no parametro TREFRESH");
    }
    aS_Preference[0][41] = String(vU8_tempoRefresh);
    if (request->hasParam("EXECWDOG", true)) {
        vB_exec_WatchDog = request->getParam("EXECWDOG", true)->value().toInt();
    } else {
        vB_exec_WatchDog = 0;
    }
    aS_Preference[0][43] = String(vB_exec_WatchDog);
    if (request->hasParam("CLOCKESP", true)) {
        vU16_clockESP32 = request->getParam("CLOCKESP", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro no parametro CLOCKESP");
    }
    aS_Preference[0][42] = String(vU16_clockESP32);
    if (request->hasParam("TEMPOWDOG", true)) {
        aU32_Variaveis[21] = request->getParam("TEMPOWDOG", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro no parametro TEMPOWDOG");
    }
    aS_Preference[0][44] = String(aU32_Variaveis[21]);
    if (request->hasParam("TOTPIN", true)) {
        aU32_Variaveis[36] = request->getParam("TOTPIN", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro no parametro TOTPIN");
    }
    aS_Preference[0][39] = String(aU32_Variaveis[36]);
    if (request->hasParam("TOTTASK", true)) {
        aU32_Variaveis[35] = request->getParam("TOTTASK", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro no parametro TOTTASK");
    }
    aS_Preference[0][50] = String(aU32_Variaveis[35]);
    // Responde com uma página HTML
    String html = "";
    if (erro == 0) {
        html += fS_cabecaHTML("Configuração Gerais", "Informações Gerais alteradas.","/configurag");
        html += "<br>Informações aplicadas. Não esqueça de salvar antes de reiniciar o módulo.<br>";
    } else {
        html += fS_cabecaHTML("Configuração Gerais", "Informações Gerais alteradas.","/configurag");
        html += "<br>Houveram " + String(erro) + " erro(s) ao aplicar alterações.<br>";
    }
    html += fS_rodapeHTML("/configurag");
    request->send(200, "text/html", html);
}

//========================================
void f_handle_CadastroGeral(AsyncWebServerRequest *request) {
    String html = fS_cabecaHTML("Cadastro Geral", "Configuração de Geral", "/configurag", "/blob/main/manual/configgeral.md");
    html += "Insira novas informações e em seguida, clique em Aplicar para enviar os dados para o [" + aS_Variaveis[0] + "]<br><br>";
    html += "<form action='/salvar_conf_geral' method='POST' style='margin:5px'>";
    html += "<table border='1' cellpadding='5' cellspacing='0'>";

    // Linha para Mostra informacoes na pagina inicial
    html += "<tr>";
    html += "<td><label for='id_moststat'>Mostrar Informações de Status na Página Inicial: </label></td>";
    html += "<td><input type='checkbox' name='MOSTSTAT' id='id_moststat' value='1' " + String((VB_mostra_Status ? "checked" : "")) + "></td>";
    html += "</tr>";
    
    // Linha para Mostra informacoes intermodulos na pagina inicial
    html += "<tr>";
    html += "<td><label for='id_mostinterm'>Mostrar Informações de Inter Módulos na Página Inicial: </label></td>";
    html += "<td><input type='checkbox' name='MOSTINTERM' id='id_mostinterm' value='1' " + String((VB_mostra_Interm ? "checked" : "")) + "></td>";
    html += "</tr>";

    // Linha para cor da celula com alerta
    html += "<tr>";
    html += "<td><label for='id_corsts1'>Cor Status Com Alerta: </label></td>";
    html += "<td><input type='text' name='CORSTAT1' id='id_corsts1' value='" + vS_corStatus1 + "' required></td>";
    html += "</tr>";
    
    // Linha para cor da celula sem alerta
    html += "<tr>";
    html += "<td><label for='id_corsts0'>Cor Status Sem Alerta: </label></td>";
    html += "<td><input type='text' name='CORSTAT0' id='id_corsts0' value='" + vS_corStatus0 + "' required></td>";
    html += "</tr>";

    // Linha para tempo de refresh 
    html += "<tr>";
    html += "<td><label for='id_trefresh'>Informe o Tempo de Refresh da Página Inicial (s): </label></td>";
    html += "<td><input type='text' name='TREFRESH' maxlength='6' size='6' id='id_trefresh' value='" + String(vU8_tempoRefresh) + "' required></td>";
    html += "</tr>";

    // Linha para executa watchdog
    html += "<tr>";
    html += "<td><label for='id_execwdog'>Executar WatchDog: </label></td>";
    html += "<td><input type='checkbox' name='EXECWDOG' id='id_execwdog' value='1' " + String((vB_exec_WatchDog ? "checked" : "")) + "></td>";
    html += "</tr>";    

    // Linha para clocck do esp32
    html += "<tr>";
    html += "<td><label for='id_clockesp'>Clock do ESP32 para wathDog (MHZ): </label></td>";
    html += "<td><input type='text' name='CLOCKESP' maxlength='6' size='6' id='id_clockesp' value='" + String(vU16_clockESP32) + "' required></td>";
    html += "</tr>";

    // tempo para watchdoh
    html += "<tr>";
    html += "<td><label for='id_tempowdog'>Tempo para wathDog (µs): </label></td>";
    html += "<td><input type='text' name='TEMPOWDOG' maxlength='12' size='12' id='id_tempowdog' value='" + String(aU32_Variaveis[21]) + "' required></td>";
    html += "</tr>";

    // Linha para quantidade de pinos
    html += "<tr>";
    html += "<td><label for='id_totpin'>Informe a Quantidade Total de Pinos: </label></td>";
    html += "<td><input type='text' style='background-color: Red' name='TOTPIN' maxlength='6' size='6' id='id_totpin' value='" + String(aU32_Variaveis[36]) + "' required></td>";
    html += "</tr>";

    // Linha para quantidade de tasks
    html += "<tr>";
    html += "<td><label for='id_tottask'>Total de Tasks em execução (de 0 a 5):<br> 0=Desligado / 5=Todas </label></td>";
    html += "<td><input type='text' style='background-color: Red' name='TOTTASK' maxlength='6' size='6' id='id_tottask' value='" + String(aU32_Variaveis[35]) + "' required ></td>";
    html += "</tr>";

    html += "</table>";    

    html += "<br><input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
    html += "</form>";
    html += fS_rodapeHTML("/configurag", "/blob/main/manual/configgeral.md");

    request->send(200, "text/html", html);
}

//========================================
void executarFuncaoSim() {
    // Coloque aqui o código que será executado quando a resposta for "Sim"
    fV_imprimeSerial(1,"executar");
}

//========================================
void executarFuncaoNao() {
    // Coloque aqui o código que será executado quando a resposta for "Não"
    fV_imprimeSerial(1,"não executar");
}

//========================================
void fV_resposta(AsyncWebServerRequest *request) {
    String confirmacao = "";
    String funcao = "";

    // Verifica se os parâmetros foram enviados via POST
    if (request->hasParam("confirmacao", true)) {
        confirmacao = request->getParam("confirmacao", true)->value();
    }
    if (request->hasParam("funcao", true)) {
        funcao = request->getParam("funcao", true)->value();
    }

    confirmacao.trim();  // Remove espaços extras

    String pagina = fS_cabecaHTML("Resposta", "", "/");
    fV_imprimeSerial(1,"Execucao de: " + funcao, false);

    // Separar nome da função e parâmetros
    int pos = funcao.indexOf('(');
    String nomeFuncao = funcao;
    String parametros = "";

    if (pos != -1) {
        nomeFuncao = funcao.substring(0, pos);
        parametros = funcao.substring(pos + 1, funcao.length() - 1); // Remove os parenteses
    }

    // Remove espaços
    nomeFuncao.trim();
    parametros.trim();

    if (confirmacao.equals("Sim")) {
        // Verifica se a função existe no mapa e a executa
        auto it = mapaFuncoesSemParam.find(funcao);
        if (it != mapaFuncoesSemParam.end()) {
            fV_imprimeSerial(1," SIM");
            it->second();  // Chama a função
            pagina += "<p>Função '" + funcao + "' executada com sucesso!</p>";
        } else {
            //auto it2 = mapaFuncoesComParam.find(funcao);
            auto it2 = mapaFuncoesComParam.find(nomeFuncao);
            if (it2 != mapaFuncoesComParam.end()) {
                fV_imprimeSerial(1," SIM");
                if (funcao.startsWith("f_handle_")) {
                    it2->second(request);  // Chama a função COM parametro 'request'
                    pagina += "<p>Função " + nomeFuncao + " executada com sucesso!</p>";
                } else {
                    it2->second(request);  // Chama a função SEM parametro 'request'
                    pagina += "<p>Função " + nomeFuncao + "("+parametros+") executada com sucesso!</p>";
                }
            } else {
                fV_imprimeSerial(1," NAO");
                pagina += "<p>Função " + nomeFuncao + "("+parametros+") desconhecida.</p>";
            }
        }
    } 


    pagina += fS_rodapeHTML("/");
    request->send(200, "text/html", pagina);
}

//========================================
void f_handle_SalvaFlash(AsyncWebServerRequest *request) {
    fV_imprimeSerial(1,"Salvando informações na flash... ");
        
    request->send(200, "text/html", fS_cabecaHTML("!! SALVAR CONFIGURAÇÕES NA FLASH !!", "Você confirma salvar as informações na flash?","/files")+fS_rodapeHTML("/files"));
}

//========================================
String fS_cabecaHTML(String titulo, String h1, String url, String ajuda) {
    String resposta = "<!DOCTYPE html>";
    resposta += "<html lang='pt-br'>";
    resposta += "<head>";
    resposta += "<meta charset='UTF-8'>";
    resposta += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
    resposta += "<title>"+aS_Variaveis[0]+" - "+titulo+"</title>";
    resposta += "</head>";
    resposta += "<body id='body'>";
    resposta += "<h1>"+h1+"</h1>";
    resposta += "<br><a href='https://github.com/rede-analista/smcr"+ajuda+"' target='_blank'>Ajuda</a>";
    resposta += "<br><a href=\"/\">Página Inicial</a>";
    resposta += "<br><a href=\""+url+"\">Voltar</a><br><br>";
    return resposta;
}

//========================================
String fS_rodapeHTML(String url, String ajuda) {
    String resposta;
    resposta += "<br><a href=\""+url+"\">Voltar</a>";
    resposta += "<br><a href=\"/\">Página Inicial</a>";
    resposta += "<br><a href='https://github.com/rede-analista/smcr"+ajuda+"' target='_blank'>Ajuda</a>";
    resposta += "</body>";
    resposta += "</html>";

    return resposta;
}

//========================================
void f_handle_OTA(AsyncWebServerRequest *request) {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>" + aS_Variaveis[0] + "</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telarecarrega'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>!! ATUALIZA FIRMWARE SMCR !!</h1>";  
  html += fS_idPlaca();
  html += "<br>";  
  html += "<br><a href=\"/\">Pagina Inicial</a>\n";
  html += "<br><br>";
  html += "<div style='border-style:inset; width:700px; background-color: Tomato' id='divDoForm'>";  
  html += "<br><br>";
  html += "<center><a href='/update'>Atualizar Firmware</a></center><br><br>";
  html += "</body></html>";

  if (SERVIDOR_UPDATE != nullptr) {
    delete SERVIDOR_UPDATE;
  }
  // Criar nova instância do servidor de update
  SERVIDOR_UPDATE = new ESPAsyncHTTPUpdateServer;
  SERVIDOR_UPDATE->setup(SERVIDOR_WEB_ASYNC);

  request->send(200, "text/html", html);
}

//========================================
void f_handle_OpcoesGerais(AsyncWebServerRequest *request) {
    String html = fS_cabecaHTML("Cadastro Geral", "Configuração de Parâmetros Gerais","/","/blob/main/manual/configgeral.md");
    html += "Escolha sua opção de configuração para ["+aS_Variaveis[0]+"]<br>";
    html += "<br><button id='openConfGeral'>Confirugação Geral</button><script>document.getElementById('openConfGeral').addEventListener('click', function() { window.location.href = '/conf_geral'; });</script><br>";
    html += "<br><button id='openConfRede'>Confirugação de Rede</button><script>document.getElementById('openConfRede').addEventListener('click', function() { window.location.href = '/conf_rede'; });</script><br>";
    html += "<br><button id='openConfInterMod'>Confirugação de Inter Módulos</button><script>document.getElementById('openConfInterMod').addEventListener('click', function() { window.location.href = '/modulos'; });</script><br>";
    html += "<br><button id='openConfMqtt'>Confirugação de MQTT</button><script>document.getElementById('openConfMqtt').addEventListener('click', function() { window.location.href = '/conf_mqtt'; });</script><br>";
    html += "<br><button id='openConfTelegram'>Confirugação de Telegram</button><script>document.getElementById('openConfTelegram').addEventListener('click', function() { window.location.href = '/conf_telegram'; });</script><br>";
    html += "<br><button id='openConfAssistente'>Confirugação de Assistentes</button><script>document.getElementById('openConfAssistente').addEventListener('click', function() { window.location.href = '/conf_assistente'; });</script><br>";
    html += fS_rodapeHTML("/","/blob/main/manual/configgeral.md");
  request->send(200, "text/html", html);
}

//========================================
void f_handle_SalvarWifiInicio(AsyncWebServerRequest *request) {
    fV_imprimeSerial(1,"Atualizando informacoes Wifi...", true);

    String html = fS_cabecaHTML("Modo AP", "Modo AP - Salvando Configuração do WIFI", "/", "/smcr");

    aS_Variaveis[1] = request->arg("SSID");
    aS_Variaveis[2] = request->arg("PASS");
    aS_Preference[0][0] = fS_limpaEspacoFimLinha(aS_Variaveis[1]);
    aS_Preference[0][1] = fS_limpaEspacoFimLinha(aS_Variaveis[2]);

    html += "<br> Informações do wifi salvas na FLASH.<br>Reinicie o módulo!<br>";
    fV_Preference("E",false);

    html += fS_rodapeHTML("/", "smcr");
    aB_Variaveis[6] = true;
    request->send(200, "text/html", html);
}

//========================================
void f_handle_ConfiguraWifiInicio(AsyncWebServerRequest *request) {
    String html = fS_cabecaHTML("Modo AP", "Modo AP - Configuração do WIFI", "/", "/smcr");
    html += "<form action='/' method='POST' style='margin:5px'>";
    html += "<label for='id_ssid'>Informe o SSID: </label>";
    html += "<input type='text' name='SSID' id='id_ssid' value='" + aS_Variaveis[1] + "' required>";
    html += "<br>";
    html += "<br><label for='id_password'>Informe a Senha: </label>";
    html += "<input type='password' name='PASS' id='id_password' value='" + aS_Variaveis[2] + "' required>";
    html += "<br>";
    html += "<br>";
    html += "<input type='submit' name='SUBMIT_SALVAR' value='Salvar' id='id_salvar'>";
    html += "</form>";
    html += fS_rodapeHTML("/", "smcr");
    fV_imprimeSerial(1,"Aguardando informacoes... f_handle_ConfiguraWifi()", true);
    request->send(200, "text/html", html);
}

//========================================
void f_handle_NotFound(AsyncWebServerRequest *request) {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>" + aS_Variaveis[0] + "</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Página Não encontrada</h1>";
  html += "<div id='mensagens'></div>";
  html += "<script>";

  html += "document.getElementById('mensagens').innerHTML = '";
  html += "<p>URL: ";
  html += request->url();
  html += "</p>";

  html += "<p>Método: ";
  html += (request->method() == HTTP_GET) ? "GET" : "POST";
  html += "</p>";

  html += "<p>Argumentos: ";
  html += request->args();
  html += "</p>";

  // Adiciona parâmetros da requisição GET
  if (request->method() == HTTP_GET) {
    for (uint8_t i = 0; i < request->args(); i++) {
      html += "<p> " + request->argName(i) + ": " + request->arg(i) + "</p>";
    }
  }

  // Adiciona parâmetros da requisição POST
  else if (request->method() == HTTP_POST) {
    // Cria um buffer para armazenar os dados da requisição POST
    String postData = "";
    for (uint8_t i = 0; i < request->args(); i++) {
      postData += request->argName(i) + ": " + request->arg(i) + "<br>";
    }

    if (postData.length() == 0) {
      // Se não houver parâmetros, tenta obter o corpo da requisição POST
      postData = request->getParam(0)->value();
    }

    html += "<p>Dados POST: " + postData + "</p>";
  }

  html += "';";
  html += "</script>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";

  request->send(404, "text/html", html);
}

/*========================================
Funcao para montagem da pagina
*/
void f_handle_Index(AsyncWebServerRequest *request) {
    String html;
    html += "<!DOCTYPE html>";
    html += "<html lang='pt-br'>";
    html += "<head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
    if (VB_mostra_Status) {
        html += "<meta http-equiv='refresh' content='"+String(vU8_tempoRefresh)+"'>";
    }
    html += "<title>Módulo: "+aS_Variaveis[0]+"</title>";
    html += "</head>";
    html += "<body>";
    html += "<center><h1>PÁGINA STATUS [" + aS_Variaveis[0] + "]</h1>Seu ip é: ";
    html += request->client()->remoteIP().toString();
    html += " , ";
    html += fS_DataHora();
    html += "<br>Uptime: ";
    html += fS_Uptime();
    html += "<br>";
    if (!aB_Variaveis[13]) {
        html += "<br><br><br><br><br><br><center><h1>!!! SISTEMA INICIANDO !!!</h1></center>";
    } else {
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/configurag'> Geral</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/pinos'> Pinos</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/acoes'> Ações</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/execfuncoes'> Funções</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/files'> Arquivos</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/logout'> Sair</a> - ";
        html += "<a href='https://github.com/rede-analista/smcr/tree/main' target='_blank'>Ajuda</a></center>";

        if (VB_mostra_Status && aB_Variaveis[13]) {
            html += "<h2>PINOS(Portas)</h2>";
            vU16_linhaPagCad = aU32_Variaveis[36]/vU8_colunasTabelas;
            vU8_colINICIO = 0;
            vU8_colFIM = vU8_colunasTabelas;

            html += "(Usado(s): "+String(fU16_pinosUsados())+" de "+String(aU32_Variaveis[36])+" pino(s))";
            html += "<br>(Refresh a cada "+String(vU8_tempoRefresh)+"/s)";
            html += "<table border='1'>";
            while (vU16_linhaPagCad >= 0) {
                html += "    <tr>";
                html += "        <td style='background-color: LightGrey'><center>Nome</center></td>";
                for (uint8_t z=vU8_colINICIO; z<vU8_colFIM; z++) {
                    html += "        <td><center>"+String(aS8_Pinos[0][z])+"</center></td>";
                }
                html += "    </tr>";
                html += "    <tr>";
                html += "        <td style='background-color: LightGrey'><center>Pino</center></td>";
                for (uint8_t a=vU8_colINICIO; a<vU8_colFIM; a++) {
                    if (aU16_Pinos[0][a] > 0) {
                        html += "<td><center>"+String(aU16_Pinos[0][a])+"</center></td>";
                    } else {
                        html += "<td><center></center></td>";
                    }
                }
                html += "    </tr>";
                html += "        <td style='background-color: LightGrey'><center>Status</center></td>";
                for (uint8_t b=vU8_colINICIO; b<vU8_colFIM; b++) {
                    if (aU16_Pinos_Status[0][b] >= aU16_Pinos[4][b] && aU16_Pinos[0][b] > 0) {
                        html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aU16_Pinos_Status[0][b])+"</center></td>";
                    } else if (aU16_Pinos_Status[0][b] < aU16_Pinos[4][b] && aU16_Pinos[0][b] > 0) {
                        html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aU16_Pinos_Status[0][b])+"</center></td>";
                    } else {
                        html += "        <td><center></center></td>";
                    }
                }
                html += "<tr>";
                html += "<td colspan='"+String(vU8_colunasTabelas+1)+"' style='background-color: LightGrey'>&nbsp</td>";
                html += "</tr>";
                vU16_linhaPagCad--;
                if (vU16_linhaPagCad > 0) {
                    vU8_colINICIO = vU8_colFIM;
                    vU8_colFIM = vU8_colFIM+vU8_colunasTabelas;
                } else {
                    vU8_colINICIO = vU8_colFIM;
                    vU8_colFIM = aU32_Variaveis[36];
                }
            }
            html += "</table><br>";
        } // if (VB_mostra_Status) {            
        
        if (vB_exec_Modulos && VB_mostra_Interm) {
            html += "<h2>COMUNICAÇÃO ENTRE MÓDULOS</h2>";
            html += "Ciclo Handshake: ";
            html += String(vI_cicloHandshake);
            html += "<br> Alerta Handshake";
            html += "<table border='1'>";
            html += "<tr>";
            html += "<td style='background-color: LightGrey'><center>Módulo</center></td>";
            for (uint8_t z=0; z<vU8_totModulos; z++) {
                if (aS_InterMod[0][z].length() > 0 && aU16_InterMod[0][z] > 0) {
                    html += "        <td><center>"+aS_InterMod[0][z]+"</center></td>";
                }
            }
            html += "</tr>";
            for (uint8_t x=0; x<vI8_aU16_InterModHA; x++) {
                html += "    <tr>";
                html += "    <td style='background-color: LightGrey'><center>"+aS16_InterModMenu_CTRL_HandShake[0][x]+"</center></td>";
                for (uint8_t y=0; y<vU8_totModulos; y++) {
                    if (aS_InterMod[0][y].length() > 0) {
                        if (x == 1) {
                            if (aI16_InterMod_CTRL_HandShake[x][y] && aU16_InterMod[0][y] > 0) {
                                html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aI16_InterMod_CTRL_HandShake[x][y])+"</center></td>";
                            } else {
                                if (aU16_InterMod[0][y] > 0) {
                                    html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aI16_InterMod_CTRL_HandShake[x][y])+"</center></td>";
                                } else {
                                    html += "        <td ><center>-</td>";
                                }
                            }
                        } else if (x == 3) {
                            if (aI16_InterMod_CTRL_HandShake[x][y] >= vU8_tentativaConexoes) {
                                html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aI16_InterMod_CTRL_HandShake[x][y])+"</center></td>";
                            } else {
                                html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aI16_InterMod_CTRL_HandShake[x][y])+"</center></td>";
                            }
                        } else {
                            html += "        <td ><center>"+String(aI16_InterMod_CTRL_HandShake[x][y])+"</td>";
                        }
                    }
                }
                html += "</tr>";
            }
            html += "</table><br>";
            html += "<p>Último recebido: (Módulo:";
            if (vU16_ulimoModRecebido > 0) {
                html += String(aU16_InterMod[0][vU16_ulimoModRecebido]);
                html += ") - ";
                html += aS_InterMod[0][vU16_ulimoModRecebido];
            } else {
                html += ")";
            }
            html += "<br>";
            html += vS_payrec;
            html += "<br>";
            html += "<p>Último enviado: (Módulo:";
            if (aU32_Variaveis[28] > 0) {
                html += String(aU32_Variaveis[28]);
                html += ") - ";
                html += aS_InterMod[0][fU16_retornaIndiceModulo(aU32_Variaveis[28])];
            } else {
                html += ")";
            }
            html += GET_SERVIDOR;
            if (vI_httpResponseCode == 200) {
              html += "<div id='idpayload' style='background-color: lightgreen'>";
            } else if (vI_httpResponseCode == 404) {
              html += "<div id='idpayload' style='background-color: lightred'>";
            } else {
              html += "<div id='idpayload' style='background-color: lightyellow'>";
            }
            html += "Resposta: ";
            html += String(vI_httpResponseCode);
            html += "<br>";
            html += vS_payload;
            html += "</div>";
            html += "<br><hr>";
            html += "<h5>Histórico</h5>";
            html += "<br>Últimos envios:<br>";
            html += ULTIMOS_GET_SERVIDOR;
            html += "<br><br>Últimos recebidos:<br>";
            html += ULTIMOS_GET_RECEBIDOS;
            html += "<h5>Fila Enviar Módulos</h5>";
            
            
            for (uint8_t x=0; x<vI8_aU8_ControlMsgHist; x++){
              html += "Índice "+String(x);
              html += " = {";
              for (uint8_t y=0; y<vI8_aS16_InterModFila_EnviaModulo; y++) {
                html += aS16_InterModFila_EnviaModulo[x][y];
                if (y < vI8_aS16_InterModFila_EnviaModulo-1) {
                  html += ",";
                }
              }
              html += "} (" + aS8_ControlMsgModHist[0][x] + ")<br>";
            }
            
        }
        
    }
    html += "</body>";
    html += "</html>";
    request->send(200, "text/html", html);
}

/*========================================
Funcao para configurar o servidor web assincrono e as entradas(rotas) para chamadas de funcoes
*/
bool fB_configuraServidorWEB(const uint16_t& porta, bool force) {
    bool resultado = false;

    if (WiFi.status() == WL_CONNECTED) {
        fV_imprimeSerial(1,"Iniciando configuracao do servidor web na porta ", false);
        if (!force) {
          vI_U16_portaWebAsync = fU16_carregaConfigGeral(0,3,8080);
          fV_imprimeSerial(1,vI_U16_portaWebAsync, false);
          fV_imprimeSerial(1,"...", false);
          vU8_tempoRefresh = fU8_carregaConfigGeral(0,41,60);
          VB_mostra_Status = fU8_carregaConfigGeral(0,48,60);
          VB_mostra_Interm = fU8_carregaConfigGeral(0,49,60);
        } else {
          vI_U16_portaWebAsync = porta;
          fV_imprimeSerial(1,vI_U16_portaWebAsync, false);
          fV_imprimeSerial(1,"...", false);
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
                pagina += "<title>"+aS_Variaveis[0]+" - Pergunta</title>";
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

    SERVIDOR_WEB_ASYNC->on("/manage-files", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (!request->hasParam("files", true)) {
            request->send(400, "text/plain", "Nenhum arquivo selecionado.");
            return;
        }

        String action = request->getParam("action", true)->value(); // Ação (download, delete ou copia)
        String ipDestino = request->getParam("ipInput", true)->value(); // Obter o IP de destino
        String response = "";
        response += fS_cabecaHTML("Arquivos", "Operação com arquivos", "/files");

        // Obter a lista de arquivos selecionados
        int params = request->params();
        String firstFileName = ""; // Nome do primeiro arquivo para download
        int fileCount = 0;         // Contador de arquivos válidos para download

        for (int i = 0; i < params; i++) {
            AsyncWebParameter* param = request->getParam(i);
            if (param->isPost() && param->name() == "files") {
                String fileName = param->value();
                fileCount++;

                // Garantir que o nome do arquivo comece com "/"
                if (!fileName.startsWith("/")) {
                    fileName = "/" + fileName;
                }

                if (action == "delete") {
                    // Exclusão de arquivos
                    if (FILESYS.exists(fileName)) {
                        FILESYS.remove(fileName);
                        response += "Arquivo excluído: " + fileName + "<br>";
                    } else {
                        response += "Erro: Arquivo não encontrado para exclusão: " + fileName + "<br>";
                    }
                } else if (action == "download") {
                    // Armazena o primeiro arquivo selecionado
                    if (fileCount == 1) {
                        firstFileName = fileName;
                    }
                } else if (action == "copia") {
                    // Copiar arquivos
                    if (FILESYS.exists(fileName)) {
                        // O nome do arquivo copiado será o mesmo da origem
                        String copiedFileName = fileName; // Usando o mesmo nome da origem
                        File originalFile = FILESYS.open(fileName, "r");
                        File copiedFile = FILESYS.open(copiedFileName, FILE_WRITE);

                        if (originalFile && copiedFile) {
                            // Copiar o conteúdo do arquivo
                            while (originalFile.available()) {
                                copiedFile.write(originalFile.read());
                            }
                            originalFile.close();
                            copiedFile.close();
                            //response += "Arquivo copiado com sucesso: " + fileName + " para " + copiedFileName + "<br>";

                            // Enviar o arquivo copiado para outro ESP32, se necessário
                            if (ipDestino.length() > 0) {
                                fV_enviarArquivo(ipDestino.c_str(), copiedFileName.c_str()); // Envia o arquivo copiado
                                response += "Arquivo copiado para o destino: " + copiedFileName + "<br>";
                            }
                        } else {
                            response += "Erro ao copiar o arquivo: " + fileName + "<br>";
                        }
                    } else {
                        response += "Erro: Arquivo não encontrado para cópia: " + fileName + "<br>";
                    }
                }
            }
        }

        // Realizar o download se apenas um arquivo foi selecionado
        if (action == "download") {
            if (fileCount == 1 && FILESYS.exists(firstFileName)) {
                request->send(FILESYS, firstFileName, "application/octet-stream");
                return; // Encerra o fluxo após o download
            } else if (fileCount > 1) {
            
                // Criar um arquivo TAR temporário
                String tarFileName = "download_" + String(millis()) + ".tar.gz";
                fs::FS &fs = SPIFFS;
                File tarFile = fs.open("/tmp/" + tarFileName, FILE_WRITE);
                if (!tarFile) {
                    response += "Erro ao criar o arquivo TAR.GZ: " + tarFileName + "<br>";
                    return;
                }

            } else {
                response += "Erro: Nenhum arquivo válido encontrado para download.<br>";
            }
        }

        response += fS_rodapeHTML("/files");
        request->send(200, "text/html", response);
    });

    SERVIDOR_WEB_ASYNC->on("/copia_arq", HTTP_POST, [](AsyncWebServerRequest *request) {}, 
    NULL, 
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        static File arquivo;

        if (index == 0) {
            const String nomeArquivo = "/" + request->getHeader("File-Name")->value();

            arquivo = LittleFS.open(nomeArquivo, "w");
            if (!arquivo) {
                Serial.printf("Erro ao abrir o arquivo %s para escrita.\n", nomeArquivo.c_str());
                request->send(500, "text/plain", "Erro ao salvar o arquivo");
                return;
            }

            Serial.printf("Iniciando recepção do arquivo: %s\n", nomeArquivo.c_str());
        }

        if (arquivo) {
            size_t bytesEscritos = arquivo.write(data, len);
            if (bytesEscritos != len) {
                Serial.printf("Erro ao escrever dados no arquivo. Esperado: %d, Escrito: %d\n", len, bytesEscritos);
            } else {
                Serial.printf("Escrito: %d bytes no arquivo.\n", len);
            }
        }

        if (index + len == total) {
            Serial.printf("Finalizada recepção do arquivo: %d bytes recebidos.\n", total);
            arquivo.close();
            request->send(200, "text/plain", "Arquivo recebido com sucesso");
        }
    });



// Configuração da rota para receber e salvar arquivos
//ERVIDOR_WEB_ASYNC->on("/copia_arq", HTTP_POST, [](AsyncWebServerRequest *request) {
//   // Você pode enviar uma resposta inicial, se necessário, mas os dados já serão manipulados na parte de onData
//, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
//   // Salvando o arquivo recebido
//   String nomeArquivo = "/recebido.txt"; // Nome fixo ou dinâmico, pode ser alterado conforme necessário
//   // No início da transmissão, abre o arquivo para escrita
//  fV_imprimeSerial(3,"Recebendo arquivos: ");
//   File arquivo = LittleFS.open(nomeArquivo, index == 0 ? "w" : "a");
//   if (!arquivo) {
//      fV_imprimeSerial(3,"Falha ao abrir arquivo para escrita.");
//       return;
//   }
//
//   // Escreve o conteúdo recebido no arquivo
//   arquivo.write(data, len);
//   arquivo.close();
//
//   // Se todo o arquivo foi recebido, envia uma resposta de sucesso
//   if (index + len == total) {
//       request->send(200, "text/plain", "Arquivo recebido com sucesso.");
//       Serial.printf("Arquivo %s recebido e salvo\n", nomeArquivo.c_str());
//   }
//);

//// Rota para receber os arquivos
//SERVIDOR_WEB_ASYNC->on("/enviar_arquivos", HTTP_POST, [](AsyncWebServerRequest *request) {
//    // Extrair os arquivos do corpo da solicitação
//    String body = "";
//    if (request->hasParam("arquivos", true)) {
//        body = request->getParam("arquivos", true)->value();
//        // Aqui você pode processar o envio dos arquivos
//        // Você pode usar o corpo para extrair os arquivos e salvá-los
//       fV_imprimeSerial(3,"Arquivos recebidos: " + body);
//    }
//    request->send(200, "application/json", "{\"status\": \"sucesso\"}");
//});

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
            fV_imprimeSerial(1," OK", true);
        } else {
            fV_imprimeSerial(1," ERRO", true);
        }   
    } else {
        fV_imprimeSerial(1,"Erro na conexao WiFi. Servidor web nao configurado.", true);
    }
  return resultado;
}