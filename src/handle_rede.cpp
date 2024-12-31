#include "include.h"
#include "globals.h"

//========================================
void fV_salvarRede(AsyncWebServerRequest *request) {
    int erro = 0;
    uint16_t TEMP_portaWebAsync = fU16_carregaConfigGeral(3,4080);
    // Verifica se o checkbox foi marcado e define o valor corretamente
    if (request->hasParam("MODAP", true)) {
        aS_Preference[9] = request->getParam("MODAP", true)->value();
    } else {
        aS_Preference[9] = "0"; // Valor padrão se o checkbox não estiver marcado
    }
    aS_Preference[9] = String(fB_carregaConfigGeral(9, true));
    // Verifica e trata o SSID
    if (request->hasParam("SSID", true)) {
        aS_Preference[0] = fS_limpaEspacoFimLinha(request->getParam("SSID", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: SSID não informado.");
    }
    aS_Preference[0] = aS_Preference[0];
    // Verifica e trata a senha do Wifi
    if (request->hasParam("PASS", true)) {
        aS_Preference[1] = fS_limpaEspacoFimLinha(request->getParam("PASS", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: Senha Wifi não informada.");
    }
    aS_Preference[1] = aS_Preference[1];
    // Verifica e trata o hostname
    if (request->hasParam("HSTNAME", true)) {
        aS_Preference[4] = fS_limpaEspacoFimLinha(request->getParam("HSTNAME", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: Hostname não informado.");
    }
    aS_Preference[4] = aS_Preference[4];
    aS_Preference[7] = aS_Preference[4]+" Ponto de Acesso";
    // Verifica e trata a porta web
    if (request->hasParam("PORTAWEB", true)) {
        int porta = request->getParam("PORTAWEB", true)->value().toInt();
        TEMP_portaWebAsync = porta;
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: Porta Web não informada.");
    }
    aS_Preference[3] = String(TEMP_portaWebAsync);
    // Verifica e trata o número de tentativas de conexão
    if (request->hasParam("TENTCON", true)) {
        int tentativas = request->getParam("TENTCON", true)->value().toInt();
        aS_Preference[2] = String(tentativas);
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: Número de tentativas de conexão não informado.");
    }
    aS_Preference[2] = String(fU8_carregaConfigGeral(2,4));
    // Verifica e trata o usuário web
    if (request->hasParam("USRWEB", true)) {
        aS_Preference[5] = fS_limpaEspacoFimLinha(request->getParam("USRWEB", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: Nome de usuário web não informado.");
    }
    aS_Preference[5] = aS_Preference[5];
    // Verifica e trata a senha web
    if (request->hasParam("PWDWEB", true)) {
        aS_Preference[6] = fS_limpaEspacoFimLinha(request->getParam("PWDWEB", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: Senha web não informada.");
    }
    aS_Preference[6] = aS_Preference[6];
    // Verifica e trata a ntp 1
    if (request->hasParam("NTP1", true)) {
        aS_Preference[10] = fS_limpaEspacoFimLinha(request->getParam("NTP1", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: servidor ntp 1 não informado.");
    }
    aS_Preference[10] = aS_Preference[10];
    // Verifica e trata a ntp 2
    if (request->hasParam("NTP2", true)) {
        aS_Preference[11] = fS_limpaEspacoFimLinha(request->getParam("NTP2", true)->value());
    } else {
        erro++;
        fV_imprimeSerial(1,"Erro: servidor ntp 2 não informado.");
    }
    aS_Preference[11] = aS_Preference[11];
    // Responde com uma página HTML
    String html = "";
    if (erro == 0) {
        html += fS_cabecaHTML("Configuração de Rede", "Informações de rede alteradas.","/configurag");
        html += "<br>Informações aplicadas. Não esqueça de salvar antes de reiniciar o módulo.<br>";
    } else {
        html += fS_cabecaHTML("Configuração de Rede", "Informações de rede alteradas.","/configurag");
        html += "<br>Houveram "+ String (erro) +" erro(s) ao aplicar alterações.<br>";
    }    
    html += fS_rodapeHTML("/configurag");
    if (aS_Preference[3] != String(TEMP_portaWebAsync)) {
        aS_Preference[3] = String(TEMP_portaWebAsync);
        fB_configuraServidorWEB(TEMP_portaWebAsync);
    }
    request->send(200, "text/html", html );
}

//========================================
void f_handle_ConfiguraWifi(AsyncWebServerRequest *request) {
    String html = fS_cabecaHTML("Cadastro de Rede", "Configuração de Rede", "/configurag", "/blob/main/manual/rede.md");
    html += "Insira novas informações e em seguida, clique em Aplicar para enviar os dados para o [" + aS_Preference[4] + "]<br><br>";
    html += "<form action='/salvar_rede' method='POST' style='margin:5px'>";
    html += "<table border='1' cellpadding='5' cellspacing='0'>";

    // Linha para o Modo AP
    html += "<tr>";
    html += "<td><label for='id_modap'>Habilita Modo AP: </label></td>";
    html += "<td><input type='checkbox' name='MODAP' id='id_modap' value='1' " + String((fB_carregaConfigGeral(9, true) ? "checked" : "")) + "></td>";
    html += "</tr>";
    
    // Linha para o SSID
    html += "<tr>";
    html += "<td><label for='id_ssid'>Informe o SSID: </label></td>";
    html += "<td><input type='text' name='SSID' id='id_ssid' value='" + aS_Preference[0] + "' required></td>";
    html += "</tr>";
    
    // Linha para a Senha
    html += "<tr>";
    html += "<td><label for='id_password'>Informe a Senha: </label></td>";
    html += "<td><input type='password' name='PASS' id='id_password' value='" + aS_Preference[1] + "' required></td>";
    html += "</tr>";
    
    // Linha para o Hostname
    html += "<tr>";
    html += "<td><label for='id_hstname'>Informe o Hostname (mDNS): </label></td>";
    html += "<td><input type='text' name='HSTNAME' id='id_hstname' value='" + aS_Preference[4] + "' required></td>";
    html += "</tr>";
    
    // Linha para a Porta do Servidor Web
    html += "<tr>";
    html += "<td><label for='id_portaweb'>Informe a Porta do Servidor Web: </label></td>";
    html += "<td><input type='text' name='PORTAWEB' maxlength='6' size='6' id='id_portaweb' value='" + String(fU16_carregaConfigGeral(3,4080)) + "' required></td>";
    html += "</tr>";
    
    // Linha para o Número de Tentativas de Conexão
    html += "<tr>";
    html += "<td><label for='id_tentcon'>Número de Tentativas de Conexão do Wifi: </label></td>";
    html += "<td><input type='text' name='TENTCON' maxlength='6' size='6' id='id_tentcon' value='" + String(fU8_carregaConfigGeral(2,4)) + "' required></td>";
    html += "</tr>";

    // Linha para o Usuario de acesso web
    html += "<tr>";
    html += "<td><label for='id_usrweb'>Informe Nome de Usuário WEB: </label></td>";
    html += "<td><input type='text' name='USRWEB' id='id_usrweb' value='" + aS_Preference[5] + "' required></td>";
    html += "</tr>";

    // Linha para a Senha do usuario de acesso web
    html += "<tr>";
    html += "<td><label for='id_passweb'>Informe a Senha WEB: </label></td>";
    html += "<td><input type='password' name='PWDWEB' id='id_passweb' value='" + aS_Preference[6] + "' required></td>";
    html += "</tr>";

    // Linha para a servidor NTP 1
    html += "<tr>";
    html += "<td><label for='id_ntp1'>Servidor 1 NTP: </label></td>";
    html += "<td><input type='text' name='NTP1' id='id_ntp1' value='" + aS_Preference[10] + "' required></td>";
    html += "</tr>";

    // Linha para a servidor NTP 2
    html += "<tr>";
    html += "<td><label for='id_ntp2'>Servidor 2 NTP: </label></td>";
    html += "<td><input type='text' name='NTP2' id='id_ntp2' value='" + aS_Preference[11] + "' required></td>";
    html += "</tr>";

    html += "</table>";    
    
    html += "<br><input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
    html += "</form>";
    html += fS_rodapeHTML("/configurag", "/blob/main/manual/rede.md");

    request->send(200, "text/html", html);
}
