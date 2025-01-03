#include "include.h"
#include "globals.h"

//========================================
void fV_salvarPinos(AsyncWebServerRequest *request) {

    uint8_t linha,coluna = 0;
    for (uint8_t i = 0; i < 2; i++) {
        AsyncWebParameter* param = request->getParam(i);
        String paramName = param->name();
        String paramValue = param->value();
        if (i == 0){
            linha = paramValue.toInt();
        } else if (i == 1) {
            coluna = paramValue.toInt();
        }
    }
    String html = fS_cabecaHTML("Cadastro de pinos", "Informações do pino alteradas.","/pinos","/blob/main/manual/pinos.md");
    int x = 3;
    int y = 65535;
    for (int i = 0; i < vI8_aU16_Pinos; i++) {
        AsyncWebParameter* param = request->getParam(x);
        String paramName = param->name();
        String paramValue = param->value();
        x++;
        if (paramName == fS_limpaEspacoFimLinha(aS16_PinosMenu[0][0])){
            y = paramValue.toInt();
        }
    }
    if ( y == 0 || y == 65535 ) {
        html += "<br>O pino "+String(aU16_Pinos[linha][coluna])+" foi descadastrado (excluído)<br>";
        html += "<br>Descadastrando todas as ações para o pino.<br>";
        fV_imprimeSerial(1,"O pino "+String(aU16_Pinos[linha][coluna])+" foi descadastrado (excluido)");
        fV_imprimeSerial(1,"Descadastrando todas as acoes para o pino...", false);

        // Salvar aU16_Acao
        for (uint8_t i = 0; i < aU32_Variaveis[17]; i++) {
            aU16_Acao1[i][coluna] = 0;
            aU16_Acao2[i][coluna] = 0;
            aU16_Acao3[i][coluna] = 0;
            aU16_Acao4[i][coluna] = 0;
        }

        // Salvar aU8_AcaoRede
        for (uint8_t i = 0; i < aU32_Variaveis[18]; i++) {
            aU8_AcaoRede1[i][coluna] = 0;
            aU8_AcaoRede2[i][coluna] = 0;
            aU8_AcaoRede3[i][coluna] = 0;
            aU8_AcaoRede4[i][coluna] = 0;
         }

        // Salvar aS8_Acao
        for (uint8_t i = 0; i < aU32_Variaveis[9]; i++) {
            aS8_Acao1[i][coluna] = "";
            aS8_Acao2[i][coluna] = "";
            aS8_Acao3[i][coluna] = "";
            aS8_Acao4[i][coluna] = "";
        }

        x = 2;
        for (int i = 0; i < vI8_aS8_Pinos; i++) {
            AsyncWebParameter* param = request->getParam(x);
            String paramName = param->name();
            String paramValue = param->value();
            x++;
            if (paramName == "nome"){
                aS8_Pinos[i][coluna] = "";
            } else {
                fV_imprimeSerial(1,"Erro:1 no parametro "+paramName);
            }
        }

        x = 3;
        for (int i = 0; i < vI8_aU16_Pinos; i++) {
            AsyncWebParameter* param = request->getParam(x);
            String paramName = param->name();
            String paramValue = param->value();
            x++;
            if (paramName == fS_limpaEspacoFimLinha(aS16_PinosMenu[0][i])){
                aU16_Pinos[i][coluna] = 0;
            } else {
                fV_imprimeSerial(1,"Erro:2 no parametro "+paramName);
            }
        }
        fV_imprimeSerial(1," OK");
    } else {
        fV_imprimeSerial(1,"Salvando pinos...", false);   
        x = 2;
        for (int i = 0; i < vI8_aS8_Pinos; i++) {
            AsyncWebParameter* param = request->getParam(x);
            String paramName = param->name();
            String paramValue = param->value();
            x++;
            if (paramName == "nome"){
                aS8_Pinos[i][coluna] = paramValue;
            } else {
                fV_imprimeSerial(1,"Erro:1 no parametro "+paramName);
            }
        }

        x = 3;
        for (int i = 0; i < vI8_aU16_Pinos; i++) {
            AsyncWebParameter* param = request->getParam(x);
            String paramName = param->name();
            String paramValue = param->value();
            x++;
            if (paramName == fS_limpaEspacoFimLinha(aS16_PinosMenu[0][i])){
                aU16_Pinos[i][coluna] = paramValue.toInt();
                if (aU16_Pinos[0][i] > 0 ) {
                    if (aU16_Pinos[1][i] == 1 || aU16_Pinos[1][i] == 192) {
                      pinMode(aU16_Pinos[0][i],aU16_Pinos[2][i]);
                    }
                }
            } else {
                fV_imprimeSerial(1,"Erro:2 no parametro "+paramName);
            }
        }
    }
    // Responde com uma página HTML
    html += "<br>Informação do índice: " + String(linha) + "-" + String(coluna);
    html += "<br> Nome: " + aS8_Pinos[linha][coluna];
    html += "<br> Pino: " + String(aU16_Pinos[linha][coluna]) + "<br>";
    html += fS_rodapeHTML("/pinos","/blob/main/manual/pinos.md");
    fV_imprimeSerial(1," OK");
    request->send(200, "text/html", html );
}

//========================================
void fV_cadastraPino(AsyncWebServerRequest *request) {
    // Obtém o ID do pino da requisição
    String pinoID = request->getParam("pino")->value();
    int linha = pinoID.substring(0, pinoID.indexOf('-')).toInt();
    int coluna = pinoID.substring(pinoID.indexOf('-') + 1).toInt();

    // Gera o HTML para a página de configuração
    String html = fS_cabecaHTML("Cadastro do Pinos","Configuração do Índice " + String(linha) + "-" + String(coluna),"/pinos","/blob/main/manual/pinos.md");

    // Início do formulário
    html += "Insira as informações de configuração dos pinos e em seguida clique em Aplicar.<br>";
    html += "(Usado(s): "+String(fU16_pinosUsados())+" de "+String(fU16_carregaConfigGeral(39, 15))+" pino(s))<br>";
    html += "<form action='/salvar_pinos' method='post'>";
    html += "<input type='hidden' id='linha' name='linha' value='" + String(linha) + "'>";
    html += "<input type='hidden' id ='coluna' name='coluna' value='" + String(coluna) + "'>";

    // Início da tabela
    html += "<table border='1' cellpadding='5' cellspacing='0'>";
    html += "<tr><th>Campo</th><th>Valor</th></tr>";

    // Campo para o nome do pino (array aS8_Pinos)
    html += "<tr>";
    html += "<td><label for='nome'>Nome:</label></td>";
    html += "<td><input type='text' id='nome' name='nome' maxlength='45' size='45' value='" + aS8_Pinos[linha][coluna] + "'></td>";
    html += "</tr>";

    // Adiciona os campos de configuração em formato de tabela (array aU16_Pinos)
    for (int i = 0; i < vI8_aU16_Pinos; i++) {
        // Acessa a string e aplica trim()
        String idnome = fS_limpaEspacoFimLinha(aS16_PinosMenu[0][i]); // Aqui aplica trim() corretamente

        // Construção do HTML
        html += "<tr>";
        html += "<td><label for='" + idnome + "'>" + idnome + ":</label></td>";
        html += "<td><input type='text' id='" + idnome + "' name='" + idnome + "' maxlength='8' size='8' pattern='[0-9]*' value='" + String(aU16_Pinos[i][coluna]) + "' style='ime-mode:disabled;'></td>";
        html += "</tr>";
    }

    html += "</table>";
    html += "<input type='submit' value='Aplicar (sem salvar)'>";
    html += "</form>";

    html += fS_rodapeHTML("/pinos","/blob/main/manual/pinos.md");

    // Envia a resposta para o cliente
    request->send(200, "text/html", html);
}

//========================================
size_t f_handle_ConfiguraPortas(unsigned char *data, size_t len, bool final) {
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
        html += fS_cabecaHTML("Cadastro do Pinos","Cadastro de Pinos (Portas)","/","/blob/main/manual/pinos.md");
        html += "Escolha um pino para configurar os parâmetros.<br>";
        html += "(Usado(s): "+String(fU16_pinosUsados())+" de "+String(fU16_carregaConfigGeral(39, 15))+" pino(s))<br>";
        html += "<form action='/configurar_pino' method='GET' style='margin:5px'>";
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
                if (aU16_Pinos[0][x] > 0) {
                    html += "<td><button type='submit' name='pino' value='" + String(0) + "-" + String(x) + "'> Índice " + String(0) + "-" + String(x) +"<br>Pino:"+String(aU16_Pinos[0][x])+"<br>" + aS8_Pinos[0][x] + "</button></td>";
                } else {
                    html += "<td><button type='submit' name='pino' value='" + String(0) + "-" + String(x) + "'> Índice " + String(0) + "-" + String(x) +"<br>Pino:<br> livre </button></td>";
                }
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
        html += fS_rodapeHTML("/","/blob/main/manual/pinos.md");

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