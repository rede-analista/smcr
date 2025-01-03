#include "include.h"
#include "globals.h"

//========================================
void fV_salvarAcoes(AsyncWebServerRequest *request) {
    fV_imprimeSerial(1,"Salvando acoes...", false);

    String html = fS_cabecaHTML("Cadastro de Ações", "Cadastro de Ações", "/acoes", "/blob/main/manual/acoes.md");
    uint16_t acaoID = 65535;
    uint16_t coluna = 65535;
    if (request->hasParam("acao", true)) {
        acaoID = request->getParam("acao", true)->value().toInt();
    }
    if (request->hasParam("coluna", true)) {
        coluna = request->getParam("coluna", true)->value().toInt();
    }

    // Verifica se o acaoID é válido
    if (acaoID == 65535 || coluna == 65535) {
        html += "Parametro ID da ação inválido. ID: " + String(acaoID);
        html += fS_rodapeHTML("/acoes", "/blob/main/manual/acoes.md");
        fV_imprimeSerial(1," ERRO: Parametro ID da acao invalido");
        request->send(400, "text/html", html);
        return;
    }
    // Salvar aU16_Acao
    for (uint8_t i = 0; i < aU32_Variaveis[17]; i++) {
        String fieldName = "aU16_Acao" + String(i);
        if (request->hasParam(fieldName, true)) {
            AsyncWebParameter* param = request->getParam(fieldName, true);
            switch (acaoID) {
                case 1: aU16_Acao1[i][coluna] = param->value().toInt(); break;
                case 2: aU16_Acao2[i][coluna] = param->value().toInt(); break;
                case 3: aU16_Acao3[i][coluna] = param->value().toInt(); break;
                case 4: aU16_Acao4[i][coluna] = param->value().toInt(); break;
            }
        }
    }

    // Salvar aU8_AcaoRede
    for (uint8_t i = 0; i < aU32_Variaveis[18]; i++) {
        String fieldName = "aU8_AcaoRede" + String(i);
        bool checkboxFound = false;
        if (request->hasParam(fieldName, true)) {
            AsyncWebParameter* param = request->getParam(fieldName, true);
            switch (acaoID) {
                case 1:
                    if (fieldName == "aU8_AcaoRede0") {
                        aU8_AcaoRede1[i][coluna] = param->value().toInt();
                    } else {
                        aU8_AcaoRede1[i][coluna] = (param->value() == "on") ? 1 : 0;
                    }
                    break;
                case 2:
                    if (fieldName == "aU8_AcaoRede0") {
                        aU8_AcaoRede2[i][coluna] = param->value().toInt();
                    } else {
                        aU8_AcaoRede2[i][coluna] = (param->value() == "on") ? 1 : 0;
                    }
                    break;
                case 3:
                    if (fieldName == "aU8_AcaoRede0") {
                        aU8_AcaoRede3[i][coluna] = param->value().toInt();
                    } else {
                        aU8_AcaoRede3[i][coluna] = (param->value() == "on") ? 1 : 0;
                    }
                    break;
                case 4:
                    if (fieldName == "aU8_AcaoRede0") {
                        aU8_AcaoRede4[i][coluna] = param->value().toInt();
                    } else {
                        aU8_AcaoRede4[i][coluna] = (param->value() == "on") ? 1 : 0;
                    }
                    break;
            }
        } else {
            switch (acaoID) {
                case 1:
                    aU8_AcaoRede1[i][coluna] = 0;
                    break;
                case 2:
                    aU8_AcaoRede2[i][coluna] = 0;
                    break;
                case 3:
                    aU8_AcaoRede3[i][coluna] = 0;
                    break;
                case 4:
                    aU8_AcaoRede4[i][coluna] = 0;
                    break;
            }            
        }
    }

    // Salvar aS8_Acao
    for (uint8_t i = 0; i < aU32_Variaveis[9]; i++) {
        String fieldName = "aS8_Acao" + String(i);
        if (request->hasParam(fieldName, true)) {
            AsyncWebParameter* param = request->getParam(fieldName, true);
            switch (acaoID) {
                case 1: aS8_Acao1[i][coluna] = fS_limpaEspacoFimLinha(param->value()); break;
                case 2: aS8_Acao2[i][coluna] = fS_limpaEspacoFimLinha(param->value()); break;
                case 3: aS8_Acao3[i][coluna] = fS_limpaEspacoFimLinha(param->value()); break;
                case 4: aS8_Acao4[i][coluna] = fS_limpaEspacoFimLinha(param->value()); break;
            }
        }
    }

    // Envia uma resposta de sucesso
    switch (acaoID) {
        case 1:            
            html += "Açao " + String(acaoID) +" "+fS_traduzAcoes(aU16_Acao1[2][coluna])+" foi salva.<br>";
            html += "Pino origem: " + String(aU16_Acao1[0][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao1[0][coluna])] +"<br>";
            html += "Pino destino: " + String(aU16_Acao1[1][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao1[1][coluna])] +"<br>";
            break;
        case 2:            
            html += "Açao " + String(acaoID) +" "+fS_traduzAcoes(aU16_Acao2[2][coluna])+" foi salva.<br>";
            html += "Pino origem: " + String(aU16_Acao2[0][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao2[0][coluna])] +"<br>";
            html += "Pino destino: " + String(aU16_Acao2[1][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao2[1][coluna])] +"<br>";
            break;
        case 3:            
            html += "Açao " + String(acaoID) +" "+fS_traduzAcoes(aU16_Acao3[2][coluna])+" foi salva.<br>";
            html += "Pino origem: " + String(aU16_Acao3[0][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao3[0][coluna])] +"<br>";
            html += "Pino destino: " + String(aU16_Acao3[1][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao3[1][coluna])] +"<br>";
            break;
        case 4:            
            html += "Açao " + String(acaoID) +" "+fS_traduzAcoes(aU16_Acao4[2][coluna])+" foi salva.<br>";
            html += "Pino origem: " + String(aU16_Acao4[0][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao4[0][coluna])] +"<br>";
            html += "Pino destino: " + String(aU16_Acao4[1][coluna])+" - ";
            html += "Nome: " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao4[1][coluna])] +"<br>";
            break;                                                
    }

    html += fS_rodapeHTML("/acoes", "/blob/main/manual/acoes.md");
    fV_imprimeSerial(1," OK");
    request->send(200, "text/html", html);
}

//========================================
void fV_cadastraAcoes(AsyncWebServerRequest *request) {
    // Verifica qual parâmetro está presente e obtém o valor
    String acaoID = "";
    int acaoIDValue = 0;
    int indice = 0;
    int coluna = 0;
 
    // Identifica o parâmetro da ação e define o ID da ação
    if (request->hasParam("acao1")) {
        acaoID = request->getParam("acao1")->value();
        acaoIDValue = 1;  // ID da ação 1
    } else if (request->hasParam("acao2")) {
        acaoID = request->getParam("acao2")->value();
        acaoIDValue = 2;  // ID da ação 2
    } else if (request->hasParam("acao3")) {
        acaoID = request->getParam("acao3")->value();
        acaoIDValue = 3;  // ID da ação 3
    } else if (request->hasParam("acao4")) {
        acaoID = request->getParam("acao4")->value();
        acaoIDValue = 4;  // ID da ação 4
    } else {
        // Se nenhum parâmetro conhecido foi encontrado
        String html = fS_cabecaHTML("Cadastro de Ações", "Cadastro de Ações", "/acoes", "/blob/main/manual/acoes.md");
        html += "Parâmetros não encontrados: acaoID:" + acaoID + " - Índice:"+String(indice)+" para o Pino:" + String(coluna);
        html += fS_rodapeHTML("/acoes", "/blob/main/manual/acoes.md");
        request->send(400, "text/html", html);
        return;
    }

    // Obtém o índice e a coluna da requisição
    int delimiterIndex = acaoID.indexOf('-');
    if (delimiterIndex != -1) {
        indice = acaoID.substring(0, delimiterIndex).toInt();
        coluna = acaoID.substring(delimiterIndex + 1).toInt();
    }

    // Gera o HTML para a página de configuração da ação
    String html = fS_cabecaHTML("Cadastro de Ações", "Cadastro de Ações", "/acoes", "/blob/main/manual/acoes.md");
    html += "Configuração da Ação " + String(acaoIDValue) + " - Índice:"+String(indice)+" para o Pino:" + String(coluna);
    html += "<br><form action='/salvar_acoes' method='POST'>";
    html += "<input type='hidden' id ='acao' name='acao' value='" + String(acaoIDValue) + "'>";
    html += "<input type='hidden' id ='coluna' name='coluna' value='" + String(coluna) + "'>";
    // Gera a tabela HTML
    html += "<table border='1'>";
    html += "<tr><th>Campo</th><th>Valor</th></tr>";

    switch (acaoIDValue) {
        case 1:
            // Campos de configuração para ações 1
            for (int i = 0; i < aU32_Variaveis[17]; i++) {
                String idnome = "aU16_Acao"+String(i);
                if (aU16_Pinos[0][coluna] > 0 && i == 0) {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' style='background-color: LightGrey' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Pinos[0][coluna]) + "' readonly></td></tr>";
                } else {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Acao1[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de rede 1
            for (int i = 0; i < aU32_Variaveis[18]; i++) {
                String idnome = "aU8_AcaoRede"+String(i);
                html += "<tr><td>" + aS8_AcoesRedeMenu[0][i] + ":</td>";
                if (i >= 1 && i <= aU32_Variaveis[18]) {
                    html += "<td><input type='checkbox' id='" +idnome+ "' name='"+idnome+"'" + (aU8_AcaoRede1[i][coluna] == 1 ? " checked" : "") + "></td></tr>";
                } else {
                    html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU8_AcaoRede1[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de texto 1
            for (int i = 0; i < aU32_Variaveis[9]; i++) {
                String idnome = "aS8_Acao"+String(i);
                html += "<tr><td>" + aS8_AcoesStringMenu[0][i] + ":</td>";
                html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aS8_Acao1[i][coluna]) + "'></td></tr>";
            }
            break;
        case 2:
            // Campos de configuração para ações 2
            for (int i = 0; i < aU32_Variaveis[17]; i++) {
                String idnome = "aU16_Acao"+String(i);
                if (aU16_Pinos[0][coluna] > 0 && i == 0) {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' style='background-color: LightGrey' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Pinos[0][coluna]) + "' readonly></td></tr>";
                } else {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Acao2[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de rede 2
            for (int i = 0; i < aU32_Variaveis[18]; i++) {
                String idnome = "aU8_AcaoRede"+String(i);
                html += "<tr><td>" + aS8_AcoesRedeMenu[0][i] + ":</td>";
                if (i >= 1 && i <= aU32_Variaveis[18]) {
                    html += "<td><input type='checkbox' id='" +idnome+ "' name='"+idnome+"'" + (aU8_AcaoRede2[i][coluna] == 1 ? " checked" : "") + "></td></tr>";
                } else {
                    html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU8_AcaoRede2[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de texto 2
            for (int i = 0; i < aU32_Variaveis[9]; i++) {
                String idnome = "aS8_Acao"+String(i);
                html += "<tr><td>" + aS8_AcoesStringMenu[0][i] + ":</td>";
                html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aS8_Acao2[i][coluna]) + "'></td></tr>";
            }
            break;
        case 3:
            // Campos de configuração para ações 3
            for (int i = 0; i < aU32_Variaveis[17]; i++) {
                String idnome = "aU16_Acao"+String(i);
                if (aU16_Pinos[0][coluna] > 0 && i == 0) {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' style='background-color: LightGrey' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Pinos[0][coluna]) + "' readonly></td></tr>";
                } else {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Acao3[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de rede 3
            for (int i = 0; i < aU32_Variaveis[18]; i++) {
                String idnome = "aU8_AcaoRede"+String(i);
                html += "<tr><td>" + aS8_AcoesRedeMenu[0][i] + ":</td>";
                if (i >= 1 && i <= aU32_Variaveis[18]) {
                    html += "<td><input type='checkbox' id='" +idnome+ "' name='"+idnome+"'" + (aU8_AcaoRede3[i][coluna] == 1 ? " checked" : "") + "></td></tr>";
                } else {
                    html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU8_AcaoRede3[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de texto 3
            for (int i = 0; i < aU32_Variaveis[9]; i++) {
                String idnome = "aS8_Acao"+String(i);
                html += "<tr><td>" + aS8_AcoesStringMenu[0][i] + ":</td>";
                html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aS8_Acao3[i][coluna]) + "'></td></tr>";
            }
            break;
        case 4:
            // Campos de configuração para ações 4
            for (int i = 0; i < aU32_Variaveis[17]; i++) {
                String idnome = "aU16_Acao"+String(i);
                if (aU16_Pinos[0][coluna] > 0 && i == 0) {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' style='background-color: LightGrey' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Pinos[0][coluna]) + "' readonly></td></tr>";
                } else {
                    html += "<tr><td>" + aS8_AcoesMenu[0][i] + ":</td><td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU16_Acao4[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de rede 4
            for (int i = 0; i < aU32_Variaveis[18]; i++) {
                String idnome = "aU8_AcaoRede"+String(i);
                html += "<tr><td>" + aS8_AcoesRedeMenu[0][i] + ":</td>";
                if (i >= 1 && i <= aU32_Variaveis[18]) {
                    html += "<td><input type='checkbox' id='" +idnome+ "' name='"+idnome+"'" + (aU8_AcaoRede4[i][coluna] == 1 ? " checked" : "") + "></td></tr>";
                } else {
                    html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aU8_AcaoRede4[i][coluna]) + "'></td></tr>";
                }
            }

            // Campos de configuração para ações de texto 4
            for (int i = 0; i < aU32_Variaveis[9]; i++) {
                String idnome = "aS8_Acao"+String(i);
                html += "<tr><td>" + aS8_AcoesStringMenu[0][i] + ":</td>";
                html += "<td><input type='text' id='" +idnome+ "' name='"+idnome+"' value='" + String(aS8_Acao4[i][coluna]) + "'></td></tr>";
            }
            break;
        default:
            html += "<tr><td colspan='2'>Ação não identificada.</td></tr>";
            break;
    }

    html += "</table>";
    html += "<br><input type='submit' value='Aplicar (sem salvar)'>";
    html += "</form>";
    html += fS_rodapeHTML("/acoes", "/blob/main/manual/acoes.md");

    request->send(200, "text/html", html);
}

//========================================
size_t f_handle_ConfiguraAcoes(unsigned char *data, size_t len, bool final) {
    static size_t bufferSize = 1024; // Tamanho inicial do buffer
    static uint8_t x, y = 0;
    String html;
    size_t written = 0;

    if (final && aU32_Variaveis[12] == 0) {
        //written = 0;
        return 0;
    }
    if (aU32_Variaveis[12] == 0) {
        //linha = std::ceil(static_cast<float>(fU16_carregaConfigGeral(39, 15)) / fU8_carregaConfigGeral(40,7));
        aI32_Variaveis[0] = fU16_carregaConfigGeral(39, 15)/fU8_carregaConfigGeral(40,7);
        aU32_Variaveis[10] = 0;
        aU32_Variaveis[11] = fU8_carregaConfigGeral(40,7);
        html += fS_cabecaHTML("Cadastro de Ações","Cadastro de Ações","/","/blob/main/manual/acoes.md");
        html += "Escolha uma ação para configurar os parâmetros.<br>";        
        html += "<form action='/configurar_acoes' method='GET' style='margin:5px'>";
        html += "<table border='1'>";

        written = html.length();
        if (written > len) {
           fV_imprimeSerial(3,"Buffer insuficiente no aU32_Variaveis[12] 0");
            return 0;
        }
        memcpy(data, html.c_str(), written);
        aU32_Variaveis[12]++;
        return written;
    }
    if (aU32_Variaveis[12] == 1 && aI32_Variaveis[0] >= 0 && (aI32_Variaveis[0] <= std::ceil(static_cast<float>(fU16_carregaConfigGeral(39, 15)) / fU8_carregaConfigGeral(40,7)))) {
        html = "";
        if (aI32_Variaveis[0] >= 0) {
            html += "<tr>";
            for (x = aU32_Variaveis[10]; x < aU32_Variaveis[11]; x++) {
                html += "<td><center>";
                if (aS8_Pinos[0][x] == 0) {
                    html += "<label for='id_ac_pino'>Índice " + String(0) + "-" + String(x) +"<br>Pino: (sem cadastro)</label>";
                } else {
                    html += "<label for='id_ac_pino'>Índice " + String(0) + "-" + String(x) +"<br>Origem é Pino:"+String(aU16_Pinos[0][x])+"<br>" + aS8_Pinos[0][x] + "</label>";
                }
                if (aU16_Pinos[0][x] > 0) {
                    if (aU16_Acao1[1][x] == 0 ) {
                        html += "<br><button type='submit' name='acao1' value='" + String(0) + "-" + String(x) + "'> 1ªAção(livre)";
                    } else {
                        html += "<br><button type='submit' name='acao1' value='" + String(0) + "-" + String(x) + "'> 1ªAção é " + fS_traduzAcoes(aU16_Acao1[2][x]) + "<br>Destino: " + String(aU16_Acao1[1][x]) + " - " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao1[1][x])];
                    }
                    if (aU16_Acao2[1][x] == 0 ) {
                        html += "<br><button type='submit' name='acao2' value='" + String(0) + "-" + String(x) + "'> 2ªAção(livre)";
                    } else {
                        html += "<br><button type='submit' name='acao2' value='" + String(0) + "-" + String(x) + "'> 2ªAção é " + fS_traduzAcoes(aU16_Acao2[2][x]) + "<br>Destino: " + String(aU16_Acao2[1][x]) + " - " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao2[1][x])];
                    }
                    if (aU16_Acao3[1][x] == 0 ) {
                        html += "<br><button type='submit' name='acao3' value='" + String(0) + "-" + String(x) + "'> 3ªAção(livre)";
                    } else {
                        html += "<br><button type='submit' name='acao3' value='" + String(0) + "-" + String(x) + "'> 3ªAção é " + fS_traduzAcoes(aU16_Acao3[2][x]) + "<br>Destino: " + String(aU16_Acao3[1][x]) + " - " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao3[1][x])];
                    }
                    if (aU16_Acao4[1][x] == 0 ) {
                        html += "<br><button type='submit' name='acao4' value='" + String(0) + "-" + String(x) + "'> 4ªAção(livre)";
                    } else {
                        html += "<br><button type='submit' name='acao4' value='" + String(0) + "-" + String(x) + "'> 4ªAção é " + fS_traduzAcoes(aU16_Acao4[2][x]) + "<br>Destino: " + String(aU16_Acao4[1][x]) + " - " + aS8_Pinos[0][fU16_retornaIndicePino(aU16_Acao4[1][x])];
                    }                    
                }
                html += "</center></td>";
            }
            html += "</tr>";
            html += "<tr>";
            html += "<td colspan='" + String(fU8_carregaConfigGeral(40,7) + 1) + "'>&nbsp</td>";
            html += "</tr>";

            aI32_Variaveis[0]--;
            if (aI32_Variaveis[0] > 0) {
                aU32_Variaveis[10] = aU32_Variaveis[11];
                aU32_Variaveis[11] = aU32_Variaveis[11] + fU8_carregaConfigGeral(40,7);
            } else if (aI32_Variaveis[0] == 0 ) {
                if (aU32_Variaveis[11] > fU16_carregaConfigGeral(39, 15)) {
                    aU32_Variaveis[10] = aU32_Variaveis[11];
                    aU32_Variaveis[11] = aU32_Variaveis[11]+1;
                } else {
                    aU32_Variaveis[10] = aU32_Variaveis[11];
                    aU32_Variaveis[11] = fU16_carregaConfigGeral(39, 15);
                }
            } 
        }

        written = html.length();
        if (written > len) {
           fV_imprimeSerial(3,"Buffer insuficiente no aU32_Variaveis[12] 1");
            return 0;
        }
        memcpy(data, html.c_str(), written);
        if (aI32_Variaveis[0] < 0) {
            aU32_Variaveis[12]++;
        }
        return written;
    }

    if (aU32_Variaveis[12] == 2) {
        html = "</table>";
        html += "</form>";
        html += fS_rodapeHTML("/","/blob/main/manual/acoes.md");

        written = html.length();
        if (written > len) {
           fV_imprimeSerial(3,"Buffer insuficiente no aU32_Variaveis[12] 2");
            return 0;
        }
        memcpy(data, html.c_str(), written);
        aU32_Variaveis[12] = 0;
        return written;
    }

    return 0;
}