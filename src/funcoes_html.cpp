#include "include.h"
#include "globals.h"

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
    html += "Escolha sua opção para ["+vS_nomeDispositivo+"]<br>";
    html += "<br><button id='openWebSerial'>Serial Web</button><script>document.getElementById('openWebSerial').addEventListener('click', function() { window.location.href = '/serial'; });</script><br>";
    html += "<br><button id='openRestart'>Reiniciar o Módulo</button><script>document.getElementById('openRestart').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_restart&redirecionar=true'; });</script><br>";
    html += "<br><button id='openPausarExecs'>Pausar/Retornar Execuções</button><script>document.getElementById('openPausarExecs').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_mudaExec'; });</script>";
    if (vB_pausaEXECs) {
        html += " (Rotinas: Desabilitadas)<br>";
        html += "<br><button id='openRestartTasks'>Reiniciar Tasks</button><script>document.getElementById('openRestartTasks').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_restartTasks&redirecionar=true'; });</script><br>";
    } else {
        html += " (Rotinas: Habilitadas)<br>";
        html += "<br><button id='openRestartTasks' disabled>Reiniciar Tasks</button><script>document.getElementById('openRestartTasks').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_restartTasks&redirecionar=true'; });</script><br>";
    }
    html += "<br><button id='openFormataFlash'>Formatar Flash</button><script>document.getElementById('openFormataFlash').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_formataFLASH&redirecionar=true'; });</script><br>";
    html += "<br><button id='openCarregarModulos'>Recarregar Inter Módulos</button><script>document.getElementById('openCarregarModulos').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_configuraModulos(true)'; });</script><br>";
    html += "<br><button id='openRecargaPinos'>Recarregar Configuração dos Pinos</button><script>document.getElementById('openRecargaPinos').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_iniciaPinos(true)'; });</script><br>";
    html += "<br><button id='openRecargaAcoes'>Recarregar Configuração das Ações</button><script>document.getElementById('openRecargaAcoes').addEventListener('click', function() { window.location.href = '/pergunta?funcao=fV_iniciaAcoes(true)'; });</script><br>";
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
        fV_imprimeSerial("Erro no parametro CORSTAT1");
    }
    aS_Preference[0][13] = vS_corStatus1;
    if (request->hasParam("CORSTAT0", true)) {
        vS_corStatus0 = fS_limpaEspacoFimLinha(request->getParam("CORSTAT0", true)->value());
    } else {
        erro++;
        fV_imprimeSerial("Erro no parametro CORSTAT0");
    }
    aS_Preference[0][14] = vS_corStatus0;
    if (request->hasParam("TREFRESH", true)) {
        vU8_tempoRefresh = request->getParam("TREFRESH", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial("Erro no parametro TREFRESH");
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
        fV_imprimeSerial("Erro no parametro CLOCKESP");
    }
    aS_Preference[0][42] = String(vU16_clockESP32);
    if (request->hasParam("TEMPOWDOG", true)) {
        vU32_tempoWatchDog = request->getParam("TEMPOWDOG", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial("Erro no parametro TEMPOWDOG");
    }
    aS_Preference[0][44] = String(vU32_tempoWatchDog);
    if (request->hasParam("TOTPIN", true)) {
        vU8_totPinos = request->getParam("TOTPIN", true)->value().toInt();
    } else {
        erro++;
        fV_imprimeSerial("Erro no parametro TOTPIN");
    }
    aS_Preference[0][39] = String(vU8_totPinos);
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
    html += "Insira novas informações e em seguida, clique em Aplicar para enviar os dados para o [" + vS_nomeDispositivo + "]<br><br>";
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
    html += "<td><input type='text' name='TEMPOWDOG' maxlength='12' size='12' id='id_tempowdog' value='" + String(vU32_tempoWatchDog) + "' required></td>";
    html += "</tr>";

    // Linha para quantidade de pinos
    html += "<tr>";
    html += "<td><label for='id_totpin'>Informe a Quantidade Total de Pinos: </label></td>";
    html += "<td><input type='text' style='background-color: Red' name='TOTPIN' maxlength='6' size='6' id='id_totpin' value='" + String(vU8_totPinos) + "' required></td>";
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
    fV_imprimeSerial("executar");
}

//========================================
void executarFuncaoNao() {
    // Coloque aqui o código que será executado quando a resposta for "Não"
    fV_imprimeSerial("não executar");
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
    fV_imprimeSerial("Execucao da acao: " + funcao, false);

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
            fV_imprimeSerial(" SIM");
            it->second();  // Chama a função
            pagina += "<p>Função '" + funcao + "' executada com sucesso!</p>";
        } else {
            //auto it2 = mapaFuncoesComParam.find(funcao);
            auto it2 = mapaFuncoesComParam.find(nomeFuncao);
            if (it2 != mapaFuncoesComParam.end()) {
                fV_imprimeSerial(" SIM");
                if (funcao.startsWith("f_handle_")) {
                    it2->second(request);  // Chama a função COM parametro 'request'
                    pagina += "<p>Função " + nomeFuncao + " executada com sucesso!</p>";
                } else {
                    it2->second(request);  // Chama a função SEM parametro 'request'
                    pagina += "<p>Função " + nomeFuncao + "("+parametros+") executada com sucesso!</p>";
                }
            } else {
                fV_imprimeSerial(" NAO");
                pagina += "<p>Função " + nomeFuncao + "("+parametros+") desconhecida.</p>";
            }
        }
    }

    pagina += fS_rodapeHTML("/");

    // Envia a resposta HTML para o cliente
    request->send(200, "text/html", pagina);
}

//========================================
void f_handle_SalvaFlash(AsyncWebServerRequest *request) {
    fV_imprimeSerial("Salvando informações na flash... ");
        
    request->send(200, "text/html", fS_cabecaHTML("!! SALVAR CONFIGURAÇÕES NA FLASH !!", "Você confirma salvar as informações na flash?","/files")+fS_rodapeHTML("/files"));
}

//========================================
String fS_cabecaHTML(String titulo, String h1, String url, String ajuda) {
    String resposta = "<!DOCTYPE html>";
    resposta += "<html lang='pt-br'>";
    resposta += "<head>";
    resposta += "<meta charset='UTF-8'>";
    resposta += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
    resposta += "<title>"+vS_nomeDispositivo+" - "+titulo+"</title>";
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
  html += "<title>" + vS_nomeDispositivo + "</title>";
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
    html += "Escolha sua opção de configuração para ["+vS_nomeDispositivo+"]<br>";
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
    html += "<title>Módulo: "+vS_nomeDispositivo+"</title>";
    html += "</head>";
    html += "<body>";
    html += "<center><h1>PÁGINA STATUS [" + vS_nomeDispositivo + "]</h1>Seu ip é: ";
    html += request->client()->remoteIP().toString();
    html += " , ";
    html += fS_DataHora();
    html += "<br>Uptime: ";
    html += fS_Uptime();
    html += "<br>";
    if (!vB_rodando) {
        html += "<br><br><br><br><br><br><center><h1>!!! SISTEMA INICIANDO !!!</h1></center>";
    } else {
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/configurag'> Configurações Gerais</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/pinos'> Configurar Pinos</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/acoes'> Configurar Ações</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/execfuncoes'> Executar Funções</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/files'> Gerenciar Arquivos</a> - ";
        html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vI_U16_portaWebAsync) + "/logout'> Sair</a> - ";
        html += "<a href='https://github.com/rede-analista/smcr/tree/main' target='_blank'>Ajuda</a></center>";

        if (VB_mostra_Status && vB_rodando) {
            html += "<h2>PINOS(Portas)</h2>";
            vU16_linhaPagCad = vU8_totPinos/vU8_colunasTabelas;
            vU8_colINICIO = 0;
            vU8_colFIM = vU8_colunasTabelas;

            html += "(Usado(s): "+String(vU8_PinosCadastrados)+" de "+String(vU8_totPinos)+" pino(s))";
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
                    vU8_colFIM = vU8_totPinos;
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
            for (uint8_t z=0; z<vU8_totPinos; z++) {
                if (aS_InterMod[0][z].length() > 0 && aU16_InterMod[0][z] > 0) {
                    html += "        <td><center>"+aS_InterMod[0][z]+"</center></td>";
                }
            }
            html += "</tr>";
            for (uint8_t x=0; x<vI8_aU16_InterModHA; x++) {
                html += "    <tr>";
                html += "    <td style='background-color: LightGrey'><center>"+aS16_InterModHA[0][x]+"</center></td>";
                for (uint8_t y=0; y<vU8_totPinos; y++) {
                    if (aS_InterMod[0][y].length() > 0) {
                        if (x == 1) {
                            if (aI16_ControlHS[x][y] && aU16_InterMod[0][y] > 0) {
                                html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aI16_ControlHS[x][y])+"</center></td>";
                            } else {
                                if (aU16_InterMod[0][y] > 0) {
                                    html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aI16_ControlHS[x][y])+"</center></td>";
                                } else {
                                    html += "        <td ><center>-</td>";
                                }
                            }
                        } else if (x == 3) {
                            if (aI16_ControlHS[x][y] >= vU8_tentativaConexoes) {
                                html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aI16_ControlHS[x][y])+"</center></td>";
                            } else {
                                html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aI16_ControlHS[x][y])+"</center></td>";
                            }
                        } else {
                            html += "        <td ><center>"+String(aI16_ControlHS[x][y])+"</td>";
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
            if (vU8_ultimoModEnviado > 0) {
                html += String(vU8_ultimoModEnviado);
                html += ") - ";
                html += aS_InterMod[0][fU16_retornaIndiceModulo(vU8_ultimoModEnviado)];
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
              for (uint8_t y=0; y<vU8_totPinos; y++) {
                html += aU16_ControlMsgModHist[x][y];
                if (y < vU8_totPinos-1) {
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

//========================================
void f_handle_SalvarWifiInicio(AsyncWebServerRequest *request) {
    fV_imprimeSerial("Atualizando informacoes Wifi...", true);

    String html = fS_cabecaHTML("Modo AP", "Modo AP - Salvando Configuração do WIFI", "/", "/smcr");

    vS_nomeWifi = request->arg("SSID");
    vS_senhaWifi = request->arg("PASS");
    aS_Preference[0][0] = fS_limpaEspacoFimLinha(vS_nomeWifi);
    aS_Preference[0][1] = fS_limpaEspacoFimLinha(vS_senhaWifi);

    html += "<br> Informações do wifi salvas na FLASH.<br>Reinicie o módulo!<br>";
    fV_Preference("E",false);

    html += fS_rodapeHTML("/", "smcr");
    vB_finalizaModoAP = true;
    request->send(200, "text/html", html);
}

//========================================
void f_handle_ConfiguraWifiInicio(AsyncWebServerRequest *request) {
    String html = fS_cabecaHTML("Modo AP", "Modo AP - Configuração do WIFI", "/", "/smcr");
    html += "<form action='/wifiinicio' method='POST' style='margin:5px'>";
    html += "<label for='id_ssid'>Informe o SSID: </label>";
    html += "<input type='text' name='SSID' id='id_ssid' value='" + vS_nomeWifi + "' required>";
    html += "<br>";
    html += "<br><label for='id_password'>Informe a Senha: </label>";
    html += "<input type='password' name='PASS' id='id_password' value='" + vS_senhaWifi + "' required>";
    html += "<br>";
    html += "<br>";
    html += "<input type='submit' name='SUBMIT_SALVAR' value='Salvar' id='id_salvar'>";
    html += "</form>";
    html += fS_rodapeHTML("/", "smcr");
    fV_imprimeSerial("Aguardando informacoes... f_handle_ConfiguraWifi()", true);
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
  html += "<title>" + vS_nomeDispositivo + "</title>";
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

