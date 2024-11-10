#include "include.h"
#include "globals.h"

//========================================
void fV_salvarModulos(AsyncWebServerRequest *request) {
    fV_imprimeSerial("Salvando Modulos...", false);    

    String params = "";
    uint16_t moduloID = 65535;
    int paramsCount = request->params();
    
    if (request->hasParam("modulo", true)) {
        moduloID = request->getParam("modulo", true)->value().toInt();
    }

    // Tratamento dos campos de nome e IP
    for (int i = 0; i < vI8_aS_InterMod; i++) {
        String fieldName = "aS_InterMod" + String(i); // Nome esperado dos campos aS_InterMod
        if (request->hasParam(fieldName, true)) {
            AsyncWebParameter* param = request->getParam(fieldName, true);
            aS_InterMod[i][moduloID] = fS_limpaEspacoFimLinha(param->value());
        }
    }

    // Tratamento dos campos de id e porta
    for (int i = 0; i < vI8_aU16_InterMod; i++) {
        String fieldName = "aU16_InterModMenu" + String(i); // Nome esperado dos campos aU16_InterModMenu
        if (request->hasParam(fieldName, true)) {
            AsyncWebParameter* param = request->getParam(fieldName, true);
            aU16_InterMod[i][moduloID] = param->value().toInt();
        }
    }

    // Tratamento dos campos checkbox
    for (int i = 0; i < vI8_aB_InterMod; i++) {
        String checkboxName = "aSB_InterModMenu" + String(i); // Nome esperado do checkbox
        bool checkboxFound = false;

        for (int j = 0; j < paramsCount; j++) {
            AsyncWebParameter* param = request->getParam(j);
            String paramName = param->name();
            String paramValue = param->value();

            if (paramName == checkboxName) {
                if (paramValue == "on") {
                    aB_InterMod[i][moduloID] = 1;  // Checkbox marcado
                }
                checkboxFound = true;
            }
        }

        if (!checkboxFound) {
            aB_InterMod[i][moduloID] = 0;  // Checkbox desmarcado
        }
    }

    // Responde com uma página HTML
    String html = fS_cabecaHTML("Cadastro de Módulos", "Informações do módulo alteradas.","/modulos","/blob/main/manual/modulos.md");
    html += "<br>Informação do Módulo: " + String(moduloID);
    html += "<br> Nome: " + aS_InterMod[0][moduloID];
    html += "<br> IP: " + aS_InterMod[1][moduloID] + "<br>";
    html += fS_rodapeHTML("/modulos","/blob/main/manual/modulos.md");
    fV_imprimeSerial(" OK");
    request->send(200, "text/html", html );
}

//========================================
void fV_salvarInterModulos(AsyncWebServerRequest *request) {
    int erro = 0;

    // Verifica se o checkbox foi marcado e define o valor corretamente
    if (request->hasParam("HABINTMOD", true)) {
        vB_exec_Modulos = request->getParam("HABINTMOD", true)->value().toInt();
    } else {
        vB_exec_Modulos = 0; // Valor padrão se o checkbox não estiver marcado
    }
    aS_Preference[0][35] = String(vB_exec_Modulos);
    // Verifica e trata o total de modulos
    if (request->hasParam("TOTMODUlOS", true)) {
        int totmod = request->getParam("TOTMODUlOS", true)->value().toInt();
        vU8_totModulos = totmod;
    } else {
        erro++;
        fV_imprimeSerial("Erro: Total de modulos nao informado.");
    }
    aS_Preference[0][47] = String(vU8_totModulos);
    // Verifica e trata o tempo de handshake
    if (request->hasParam("TEMPOHANDSHK", true)) {
        int porta = request->getParam("TEMPOHANDSHK", true)->value().toInt();
        vU16_modulos_HandShake = porta;
    } else {
        erro++;
        fV_imprimeSerial("Erro: Tempo de handshake nao informado.");
    }
    aS_Preference[0][36] = String(vU16_modulos_HandShake);
    // Verifica e trata o ciclos de handshake
    if (request->hasParam("CICLOHANDSHK", true)) {
        int porta = request->getParam("CICLOHANDSHK", true)->value().toInt();
        vI_cicloHandshake = porta;
    } else {
        erro++;
        fV_imprimeSerial("Erro: Ciclos de handshake nao informado.");
    }
    aS_Preference[0][38] = String(vI_cicloHandshake);
    // Verifica e trata o tempo de envio
    if (request->hasParam("TEMPOENVIO", true)) {
        int porta = request->getParam("TEMPOENVIO", true)->value().toInt();
        vU16_modulos_MTBS_Acoes = porta;
    } else {
        erro++;
        fV_imprimeSerial("Erro: Tempo de envio nao informado.");
    }
    aS_Preference[0][37] = String(vU16_modulos_MTBS_Acoes);
    // Responde com uma página HTML
    String html = "";
    if (erro == 0) {
        html += fS_cabecaHTML("Configuração de Módulos", "Informações de inter módulos alteradas.","/modulos");
        html += "<br>Informações aplicadas. Não esqueça de salvar antes de reiniciar o módulo.<br>";
    } else {
        html += fS_cabecaHTML("Configuração de Módulos", "Informações de inter módulos alteradas.","/modulos");
        html += "<br>Houveram "+ String (erro) +" erro(s) ao aplicar alterações.<br>";
    }    
    html += fS_rodapeHTML("/configurag");
    request->send(200, "text/html", html );
}

//========================================
void fV_cadastraModulo(AsyncWebServerRequest *request) {
    // Obtém o ID do pino da requisição
    uint16_t moduloID = request->getParam("modulo")->value().toInt();
    // Gera o HTML para a página de configuração
    String html = fS_cabecaHTML("Cadastro de Módulos","Configuração do Módulo:" + String(moduloID),"/modulos","/blob/main/manual/modulos.md");

    // Início do formulário
    html += "Insira as informações de configuração do módulo e em seguida clique em Aplicar.<br>";
    html += "<form action='/salvar_modulos' method='POST'>";

    // Início da tabela
    html += "<table border='1' cellpadding='5' cellspacing='0'>";
    html += "<input type='hidden' id ='modulo' name='modulo' value='" + String(moduloID) + "'>";
    html += "<tr><th>Campo</th><th>Valor</th></tr>";
    // Adiciona os campos de configuração em formato de tabela
    for (int i = 0; i < vI8_aS_InterMod; i++) {
        // Campos nome e ip
        String idnome = fS_limpaEspacoFimLinha("aS_InterMod"+String(i));
        html += "<tr>";
        html += "<td><label for='" + idnome + "'>" + aS_InterModMenu[0][i] + ":</label></td>";
        html += "<td><input type='text' id='" + idnome + "' name='" + idnome + "' maxlength='45' size='45' ' value='" + String(aS_InterMod[i][moduloID]) + "' style='ime-mode:disabled;'></td>";
        html += "</tr>";
    }

    for (int i = 0; i < vI8_aU16_InterMod; i++) {
        // Campos id e porta
        String idnome = fS_limpaEspacoFimLinha("aU16_InterModMenu"+String(i));
        html += "<tr>";
        html += "<td><label for='" + idnome + "'>" + aU16_InterModMenu[0][i] + ":</label></td>";
        html += "<td><input type='text' id='" + idnome + "' name='" + idnome + "' maxlength='8' size='8' pattern='[0-9]*' value='" + String(aU16_InterMod[i][moduloID]) + "' style='ime-mode:disabled;'></td>";
        html += "</tr>";
    }

    for (int i = 0; i < vI8_aB_InterMod; i++) {
        // Campos handshake
        String idnome = fS_limpaEspacoFimLinha("aSB_InterModMenu"+String(i));
        html += "<tr>";
        html += "<td><label for='" + idnome + "'>" + aSB_InterModMenu[0][i] + ":</label></td>";
        //html += "<td><input type='hidden' id='" +idnome+ "' name='"+idnome+"' value='0'>";
        html += "<td><input type='checkbox' id='" +idnome+ "' name='"+idnome+"'" + (aB_InterMod[i][moduloID] == 1 ? " checked" : "") + "></td></tr>";
        html += "</tr>";        

    }

    html += "</table>";
    html += "<input type='submit' value='Aplicar (sem salvar)'>";
    html += "</form>";

    html += fS_rodapeHTML("/modulos","/blob/main/manual/modulos.md");

    // Envia a resposta para o cliente
    request->send(200, "text/html", html);
}

//========================================
size_t f_handle_ConfiguraModulos(unsigned char *data, size_t len, bool final) {
    static size_t bufferSize = 1024; // Tamanho inicial do buffer
    static uint8_t x, y = 0;
    String html;
    size_t written = 0;

    if (final && vU8_estado == 0) {
        //written = 0;
        return 0;
    }
    if (vU8_estado == 0) {
        //linha = std::ceil(static_cast<float>(vU8_totModulos) / vU8_colunasTabelas);
        vU16_linhaPagCad = vU8_totModulos/vU8_colunasTabelas;
        vU8_colINICIO = 0;
        vU8_colFIM = vU8_colunasTabelas;
        html += fS_cabecaHTML("Cadastro de Módulos","Cadastro de Módulos","/configurag","/blob/main/manual/intermod.md");
        html += "<form action='/salvar_intermodulos' method='POST' style='margin:5px'>";
        html += "<table border='1' cellpadding='5' cellspacing='0'>";

        // Linha para habilitar intermodulos
        html += "<tr>";
        html += "<td><label for='id_habintmod'>Habilitar Inter Módulos: </label></td>";
        html += "<td><input type='checkbox' name='HABINTMOD' id='id_habintmod' value='1' " + String((vB_exec_Modulos ? "checked" : "")) + "></td>";
        html += "</tr>";

        // Total de modulos
        html += "<tr>";
        html += "<td><label for='id_totmodulos'>Total de Módulos: </label></td>";
        html += "<td><input type='text' style='background-color: Red' name='TOTMODUlOS' maxlength='12' size='12' id='id_totmodulos' value='" + String(vU8_totModulos) + "' required></td>";
        html += "</tr>";

        // Tempo de handshake
        html += "<tr>";
        html += "<td><label for='id_tempohandshake'>Tempo de Handshake: </label></td>";
        html += "<td><input type='text' name='TEMPOHANDSHK' maxlength='12' size='12' id='id_tempohandshake' value='" + String(vU16_modulos_HandShake) + "' required></td>";
        html += "</tr>";

        // Ciclos de handshake
        html += "<tr>";
        html += "<td><label for='id_ciclohandshake'>Ciclos de handshake: </label></td>";
        html += "<td><input type='text' name='CICLOHANDSHK' maxlength='12' size='12' id='id_ciclohandshake' value='" + String(vI_cicloHandshake) + "' required></td>";
        html += "</tr>";

        // Tempo de envio
        html += "<tr>";
        html += "<td><label for='id_tempoenvio'>Tempo de Envio Alertas: </label></td>";
        html += "<td><input type='text' name='TEMPOENVIO' maxlength='12' size='12' id='id_tempoenvio' value='" + String(vU16_modulos_MTBS_Acoes) + "' required></td>";
        html += "</tr></table>";
        html += "<input type='submit' value='Aplicar (sem salvar)'>";
        html += "</form>";
        html += "<br><br>Escolha um módulo para configurar os parâmetros.";
        html += "<form action='/configurar_modulo' method='GET' style='margin:5px'>";
        html += "<table border='1' cellpadding='5' cellspacing='0'><br>";

        written = html.length();
        if (written > len) {
            Serial.println("Buffer insuficiente no vU8_estado 0");
            return 0;
        }
        memcpy(data, html.c_str(), written);
        vU8_estado++;
        return written;
    }
    if (vU8_estado == 1 && vU16_linhaPagCad >= 0 && (vU16_linhaPagCad <= std::ceil(static_cast<float>(vU8_totModulos) / vU8_colunasTabelas))) {
        html = "";
        if (vU16_linhaPagCad >= 0) {
            html += "<tr>";
            for (x = vU8_colINICIO; x < vU8_colFIM; x++) {
                if (aS_InterMod[0][x].length() == 0) {
                    html += "<td><button type='submit' name='modulo' value='" + String(x) + "'> Módulo:"+String(x)+"<br>" + aS_InterMod[0][x] + "<br>"+aS_InterMod[1][x]+"(livre)</button></td>";
                } else {
                    html += "<td><button type='submit' name='modulo' value='" + String(x) + "'> Módulo:"+String(x)+"<br>" + aS_InterMod[0][x] + "<br>"+aS_InterMod[1][x]+"</button></td>";
                }
            }
            html += "</tr>";
            html += "<tr>";
            html += "<td colspan='" + String(vU8_colunasTabelas + 1) + "'>&nbsp</td>";
            html += "</tr>";

            vU16_linhaPagCad--;
            if (vU16_linhaPagCad > 0) {
                vU8_colINICIO = vU8_colFIM;
                vU8_colFIM = vU8_colFIM + vU8_colunasTabelas;
            } else if (vU16_linhaPagCad == 0 ) {
                if (vU8_colFIM > vU8_totModulos) {
                    vU8_colINICIO = vU8_colFIM;
                    vU8_colFIM = vU8_colFIM+1;
                } else {
                    vU8_colINICIO = vU8_colFIM;
                    vU8_colFIM = vU8_totModulos;
                }
            } 
        }

        written = html.length();
        if (written > len) {
            Serial.println("Buffer insuficiente no vU8_estado 1");
            return 0;
        }
        memcpy(data, html.c_str(), written);
        if (vU16_linhaPagCad < 0) {
            vU8_estado++;
        }
        return written;
    } 

    if (vU8_estado == 2) {
        html = "</table>";
        html += "</form>";
        html += fS_rodapeHTML("/configurag","/blob/main/manual/intermod.md");

        written = html.length();
        if (written > len) {
            Serial.println("Buffer insuficiente no vU8_estado 2");
            return 0;
        }
        memcpy(data, html.c_str(), written);
        vU8_estado = 0;
        return written;
    }

    return 0;
}