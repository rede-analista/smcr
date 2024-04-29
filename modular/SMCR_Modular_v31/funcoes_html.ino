//void f_analogConf() {
//  String html;
//  html += "<!DOCTYPE html>";
//  html += "<html lang='pt-br'>";
//  html += "<head>";
//  html += "<meta charset='UTF-8'>";
//  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
//  html += "<title>"+vS_nomeDispositivo+"</title>";
//  html += "</head>";
//  html += "<body id='body'>";
//  html += "<div id='telaConfigGeral'> ";
//  html += "<div id='bloqueiaTela'></div>";
//  html += "<h1>Configuração de Parâmetros para Leitura Analógica</h1>";
//  html += "<div id='mensagens'><p>Insira novas informações. Em seguida, clique em Aplicar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div><br>";
//  html += "<div style='border-style:inset; width:700px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
//  html += "<form action='/analog' method='POST' style='margin:5px'>";
//  html += "<label for='id_bitsproc'>Bits do Processador: ";
//  html += "<input type='text' name='BITSPROC' id='id_bitsproc' value='"+String(vU8_bitsProc)+"' required> 9, 10, 11 ou 12</label>";
//  html += "<br><br>";
//  html += "<label for='id_ciclos'>Ciclos por amostra:";
//  html += "<input type='text' name='CICLOS' id='id_ciclos' value='"+String(vU8_ciclosAmostra)+"' required> 1 a 255</label>";
//  html += "<br>";
//  html += "<br>";  
//  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
//  html += "</form>";
//  html += "</div>";
//  html += "</div>";
//  Serial.println("Aguardando informacoes... f_handle_ConfiguraGeral()");
//  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
//    Serial.print("Atualizando Informacoes Gerais: ");
//    //vU8_totPinos = SERVIDOR_WEB.arg("TOTPIN").toInt();
//    vU8_bitsProc = SERVIDOR_WEB.arg("BITSPROC").toInt();
//    vU8_ciclosAmostra = SERVIDOR_WEB.arg("CICLOS").toInt();
//    analogSetWidth(vU8_bitsProc);
//    //analogSetCycles(vU8_ciclosAmostra);
//    Serial.println("OK");
//    Serial.println("Informacoes novas em uso.");
//    html += f_MensagemHTML("INFORMAÇÕES LEITURA ANALÍOGICA APLICADAS", "As informações de LEITURA ANALÓGICA foram aplicadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
//  }
//  html += "<br><a href=\"/wifi\">Config Rede</a>";
//  html += "<br><a href=\"/intermod\">Config Inter Módulos</a>";
//  html += "<br><a href=\"/configurag\">Config Geral</a>";
//  html += "<br><a href=\"/\">Página Inicial</a><br>";
//  html += "</body>";
//  html += "</html>";
//  SERVIDOR_WEB.send(200, "text/html", html);
//}

//========================================
void f_handle_ConfiguraGeral() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigGeral'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Configuração de Parâmetros Gerais</h1>";
  html += "<div id='mensagens'><p>Insira novas informações. Em seguida, clique em Aplicar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div><br>";
  html += "<br><a href=\"/wifi\">Config Rede</a>";
  html += "<br><a href=\"/intermod\">Config Inter Módulos</a>";
  html += "<br><a href=\"/\">Página Inicial</a><br>";
  html += "<div style='border-style:inset; width:700px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/configurag' method='POST' style='margin:5px'>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "<br>";
  html += "<br>";
  html += "<label for='id_totpin'>Total de Pinos: ";
  html += "<input type='text' style='background-color: LightGrey' name='TOTPIN' maxlength='6' size='6' id='id_totpin' value='"+String(vU8_totPinos)+"' readonly required></label>";
  html += "<br>";
  html += "<label for='id_moststat'>Mostrar Informações na Página Inicial: ";
  html += "<input type='checkbox' name='MOSTSTAT' id='id_moststat' value='1' "+String((VB_mostra_Status ? "checked" : ""))+"></label>";
  html += "<br>";
  html += "<br>";    
  html += "<label for='id_hateleg'>Habilita Telegram:";
  html += "<input type='checkbox' name='HATELEG' id='id_hateleg' value='1' "+String((vB_exec_Telegram ? "checked" : ""))+"></label>";
  html += "<br>";
  html += "<label for='id_apiteleg'>Chave API Telegram: ";
  html += "<input type='text' name='APITELEG' id='id_apiteleg' value='"+String(vS_api_Telegram)+"' required></label>";
  html += "<br>";
  html += "<label for='id_grpteleg'>ID Grupo Telegram: ";
  html += "<input type='text' name='GRPTELEG' id='id_grpteleg' value='"+String(vS_chat_Telegram)+"' required></label>";
  html += "<br>";
  html += "<label for='id_borteleg'>Nome Bot Telegram: ";
  html += "<input type='text' name='BOTTELEG' id='id_borteleg' value='"+String(vS_user_Telegram)+"' required></label>";
  html += "<br>";
  html += "<label for='id_tmpteleg'>Tempo de Verificação do Telegram: ";
  html += "<input type='text' name='TMPTELEG' maxlength='6' size='6' id='id_tmpteleg' value='"+String(vU16_bot_MTBS)+"' required></label>";
  html += "<br><br>";
  html += "<label for='id_hamqtt'>Habilita MqTT:";
  html += "<input type='checkbox' name='HAMQTT' id='id_hamqtt' value='1' "+String((vB_exec_MqTT ? "checked" : ""))+"></label>";
  html += "<br>";  
  html += "<label for='id_ipmqtt'>IP Servidor MqTT: ";
  html += "<input type='text' name='IPMQTT' id='id_ipmqtt' value='"+String(vS_mqttServer)+"' required></label>";
  html += "<br>";
  html += "<label for='id_usrmqtt'>Usuário MqTT: ";
  html += "<input type='text' name='USRMQTT' id='id_usrmqtt' value='"+String(vS_mqttUser)+"' required></label>";
  html += "<br>";
  html += "<label for='id_pwdmqtt'>Senha MqTT: ";
  html += "<input type='password' name='PWDMQTT' id='id_pwdmqtt' value='"+String(vS_mqttSenha)+"' required></label>";
  html += "<br>";
  html += "<label for='id_prtmqtt'>Porta MqTT: ";
  html += "<input type='text' name='PRTMQTT' maxlength='6' size='6' id='id_prtmqtt' value='"+String(vU16_mqttPorta)+"' required></label>";
  html += "<br>";
  html += "<label for='id_tpcmqtt'>Tópico MqTT: ";
  html += "<input type='text' name='TPCMQTT' id='id_tpcmqtt' value='"+String(vS_mqttTopico)+"' required></label>";
  html += "<br>";
  html += "<label for='id_tmpmqtt'>Tempo de Verificação do MqTT: ";
  html += "<input type='text' name='TMPMQTT' maxlength='6' size='6' id='id_tmpmqtt' value='"+String(vU16_mqtt_MTBS)+"' required></label>";
  html += "<br>";
  html += "<label for='id_tmpdiscmqtt'>Tempo de Descoberta do MqTT: ";
  html += "<input type='text' name='TMPDISCMQTT' maxlength='6' size='6' id='id_tmpdiscmqtt' value='"+String(vU32_mqtt_disc_MTBS)+"' required></label>";
  html += "<br><br>";
  html += "<label for='id_haassist'>Habilita Assistentes:";
  html += "<input type='checkbox' name='HAASSIST' id='id_haassist' value='1' "+String((vB_exec_Assistente ? "checked" : ""))+"></label>";
  html += "<br>";
  html += "<label for='id_nomeassistgoogle'>Nome Assistente Google: ";
  html += "<input type='text' name='NOMEASSGOOGLE' id='id_nomeassistgoogle' value='"+String(vS_assNomeGoogle)+"'></label> (vazio para não usar Google Home)";
  html += "<br>";
  html += "<label for='id_nomeassistalexa'>Nome Assistente Alexa: ";
  html += "<input type='text' name='NOMEASSALEXA' id='id_nomeassistalexa' value='"+String(vS_assNomeAlexa)+"'></label> (vazio para não usar Alexa)";
  html += "<br>";
  html += "<label for='id_lingassist'>Linguagem Assistentes: ";
  html += "<input type='text' name='LINGASSIST' id='id_lingassist' value='"+String(vS_assLinguagem)+"'></label>";
  html += "<br>";
  html += "<label for='id_timeassist'>Tempo Envio Assistentes: ";
  html += "<input type='text' name='TIMEASSIST' maxlength='6' size='6' id='id_timeassist' value='"+String(vU16_ass_MTBS)+"'></label>";
  html += "<br>";
  html += "<label for='id_alertaassist'>Início Frase Alerta Assistentes: ";
  html += "<input type='text' name='ALERTAASSIST' id='id_alertaassist' value='"+vS_ass_Alerta+"'></label>";
  html += "<br>";
  html += "<label for='id_normalassist'>Início Frase Normalização Assistentes: ";
  html += "<input type='text' name='NORMALASSIST' id='id_normalassist' value='"+vS_ass_Normal+"'></label>";
  html += "<br>";
  html += "<br>";
  html += "<label for='id_corsts1'>Cor Status HIGH(com alerta): ";
  html += "<input type='text' name='CORSTS1' id='id_corsts1' value='"+vS_corStatus1+"'></label>";
  html += "<br>";
  html += "<label for='id_corsts0'>Cor Status LOW(sem alerta): ";
  html += "<input type='text' name='CORSTS0' id='id_corsts0' value='"+vS_corStatus0+"'></label>";
  html += "<br>";
  html += "<br>";  
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraGeral()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes Gerais: ");
    VB_mostra_Status = SERVIDOR_WEB.arg("MOSTSTAT").toInt();
    vB_exec_Telegram = SERVIDOR_WEB.arg("HATELEG").toInt();
    vS_api_Telegram = SERVIDOR_WEB.arg("APITELEG");
    vS_chat_Telegram = SERVIDOR_WEB.arg("GRPTELEG");
    vS_user_Telegram = SERVIDOR_WEB.arg("BOTTELEG");
    vU16_bot_MTBS = SERVIDOR_WEB.arg("TMPTELEG").toInt();
    vB_exec_MqTT = SERVIDOR_WEB.arg("HAMQTT").toInt();
    vS_mqttServer = SERVIDOR_WEB.arg("IPMQTT");
    vS_mqttUser = SERVIDOR_WEB.arg("USRMQTT");
    vS_mqttSenha = SERVIDOR_WEB.arg("PWDMQTT");
    vU16_mqttPorta = SERVIDOR_WEB.arg("PRTMQTT").toInt();
    vS_mqttTopico = SERVIDOR_WEB.arg("TPCMQTT");
    vU16_mqtt_MTBS = SERVIDOR_WEB.arg("TMPMQTT").toInt();
    vU32_mqtt_disc_MTBS = SERVIDOR_WEB.arg("TMPDISCMQTT").toInt();
    vB_exec_Assistente = SERVIDOR_WEB.arg("HAASSIST").toInt();
    vS_assNomeGoogle = SERVIDOR_WEB.arg("NOMEASSGOOGLE");
    vS_assNomeAlexa = SERVIDOR_WEB.arg("NOMEASSALEXA");
    vS_assLinguagem = SERVIDOR_WEB.arg("LINGASSIST");
    vU16_ass_MTBS = SERVIDOR_WEB.arg("TIMEASSIST").toInt();
    vS_ass_Alerta = SERVIDOR_WEB.arg("ALERTAASSIST");
    vS_ass_Normal = SERVIDOR_WEB.arg("NORMALASSIST");
    vS_corStatus1 = SERVIDOR_WEB.arg("CORSTS1");
    vS_corStatus0 = SERVIDOR_WEB.arg("CORSTS0");
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES GERAIS APLICADAS", "As informações GERAIS foram aplicadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<br><a href=\"/wifi\">Config Rede</a>";
  html += "<br><a href=\"/intermod\">Config Inter Módulos</a>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_handle_RecarregarFuncoes() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telarecarrega'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>!! RECARREGAR FUNÇÕES DO SETUP !!</h1>";
  html += "<div style='border-style:inset; width:700px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/recarrega' method='POST' style='margin:5px'>";
  html += "<label for='id_recarrega'>Você confirma recarregar as funções do setup? </label>";
  html += "<br>Tudo, PINOS, ACOES, GACOES, TELEGRAM, MQTT, MODULOS ou ASSISTENTES";
  html += "<input type='text' name='RECRG' id='id_recarrega' value='Não' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Recarregar' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes...f_handle_RecarregarFuncoes()");

  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    if (SERVIDOR_WEB.arg("RECRG") == "Tudo") {
      Serial.println("Recarregando Setup... ");
        f_iniciaPinos(true);
        f_configuraTELEGRAM(true);
        f_configuraMQTT(true);
        f_configuraAssistenteGH(true);
        f_configuraModulos(true);
      html += f_MensagemHTML("SETUP RECARREGADO", "As funções do setup da placa ["+vS_nomeDispositivo+"] foram recarregadas.", sucesso);
    } else if (SERVIDOR_WEB.arg("RECRG") == "PINOS") {
      Serial.println("Recarregando Pinos... ");
      f_iniciaPinos(true);
      html += f_MensagemHTML("PINOS RECARREGADO", "A função Pinos da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);
} else if (SERVIDOR_WEB.arg("RECRG") == "ACOES") {
      Serial.println("Recarregando Grupos de Acoes... ");
      f_iniciaAcoes(true);
      html += f_MensagemHTML("AÇÕES RECARREGADO", "A função Ações da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);      
    } else if (SERVIDOR_WEB.arg("RECRG") == "GACOES") {
      Serial.println("Recarregando Grupos de Acoes... ");
      f_grupoAcoes(true);
      html += f_MensagemHTML("GRUPO DE AÇÕES RECARREGADO", "A função Grupos de Ações da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);
    } else if (SERVIDOR_WEB.arg("RECRG") == "TELEGRAM") {
      Serial.println("Recarregando Telegram... ");
      f_configuraTELEGRAM(true);
      html += f_MensagemHTML("TELEGRAM RECARREGADO", "A função Telegram da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);
    } else if (SERVIDOR_WEB.arg("RECRG") == "MQTT") {
      Serial.println("Recarregando MqTT... ");
      f_configuraMQTT(true);
      html += f_MensagemHTML("MQTT RECARREGADO", "A função MqTT da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);
    } else if (SERVIDOR_WEB.arg("RECRG") == "ASSISTENTES") {
      Serial.println("Recarregando Assistentes... ");
      f_configuraAssistenteGH(true);
      f_configuraAssistenteALX(true);
      html += f_MensagemHTML("ASSISTENTES RECARREGADO", "A função Assistentes da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);
    } else if (SERVIDOR_WEB.arg("RECRG") == "MODULOS") {
      Serial.println("Recarregando Receptor... ");
      f_configuraModulos(true);
      html += f_MensagemHTML("RECEPTOR RECARREGADO", "A função Receptor da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);
    }    
      Serial.println("OK");
  }
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_handle_SalvaFlash() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telasalvaflash'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>!! SALVAR CONFIGURAÇÕES NA FLASH !!</h1>";
  html += "<div style='border-style:inset; width:400px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/salvaflash' method='POST' style='margin:5px'>";
  html += "<label for='id_salvaflash'>Você confirma salvar as informações na flash? </label>";
  html += "<input type='text' name='SVFLSH' id='id_salvaflash' value='Não' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Salvar na Flash' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes...f_handle_SalvaFlash()");

  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    if (SERVIDOR_WEB.arg("SVFLSH") == "Sim") {
      Serial.println("Salvando informações na flash... ");
      f_salvaFlash();
      html += f_MensagemHTML("INFORMAÇÕES SALVAS", "As informações foram salvas na flash da placa ["+vS_nomeDispositivo+"].", sucesso);
      Serial.println("OK");
    }
  }
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_Reboota() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telareboota'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>!! REINICIAR MÓDULO ESP !!</h1>";
  html += "<div style='border-style:inset; width:300px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/reboota' method='POST' style='margin:5px'>";
  html += "<label for='id_reboota'>Você confirma restart do módulo? </label>";
  html += "<input type='text' name='REBT' id='id_reboota' value='Não' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Reboot' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes...f_Reboota()");

  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    if (SERVIDOR_WEB.arg("REBT") == "Sim") {
      Serial.println("Esta placa esta sendo reiniciada !");
      html += f_MensagemHTML("reboot esp", "Deslige a placa ["+vS_nomeDispositivo+"] e ligue novamente.", sucesso);
      Serial.println("ESP reiniciando...");
      ESP.restart();
    }
  }
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
String f_horaHTML() {
  String html = "";
  html += "<br>";
  html += aS_traduzDiaSemana[0][timeinfo.tm_wday];
  html += ",";
  html += String(timeinfo.tm_mday);
  html += " de ";
  html += aS_traduzMes[0][timeinfo.tm_mon];
  html += " de ";
  html += String(timeinfo.tm_year + 1900);
  html += " - ";
  html += String(timeinfo.tm_hour);
  html += ":";
  html += String(timeinfo.tm_min);
  html += ":";
  html += String(timeinfo.tm_sec);
  html += " - (dia ";
  html += String(timeinfo.tm_yday + 1);
  html += ")";
  return html;
}

//========================================
void f_handle_OTA() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telarecarrega'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>!! ATUALIZA FIRMWARE SMCR !!</h1>";  
  html += f_idPlaca();
  html += "<br>";  
  html += "<br><a href=\"/\">Pagina Inicial</a>\n";
  html += "<br><br>";
  html += "<div style='border-style:inset; width:700px; background-color: Tomato' id='divDoForm'>";  
  html += "<br><br>";
  html += "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>";
  html += "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>";
  html +=    "<input type='file' name='update'>";
  html +=         "<input type='submit' value='Update'>";
  html +=     "</form>";
  html += "</div>";
  html += "</div>";  
  html +=  "<div id='prg'>Progresso: 0%</div>";
  html +=  "<script>";
  html +=   "$('form').submit(function(e){";
  html +=   "e.preventDefault();";
  html +=   "var form = $('#upload_form')[0];";
  html +=   "var data = new FormData(form);";
  html +=   " $.ajax({";
  html +=   "url: '/update',";
  html +=   "type: 'POST',";
  html +=   "data: data,";
  html +=   "contentType: false,";
  html +=   "processData:false,";
  html +=   "xhr: function() {";
  html +=   "var xhr = new window.XMLHttpRequest();";
  html +=   "xhr.upload.addEventListener('progress', function(evt) {";
  html +=   "if (evt.lengthComputable) {";
  html +=   "var per = evt.loaded / evt.total;";
  html +=   "$('#prg').html('Progresso: ' + Math.round(per*100) + '%');";
  html +=   "}";
  html +=   "}, false);";
  html +=   "return xhr;";
  html +=   "},";
  html +=   "success:function(d, s) {";
  html +=   "console.log('Sucesso!')";
  html +=  "},";
  html +=  "error: function (a, b, c) {";
  html +=  "}";
  html +=  "});";
  html +=  "});";
  html +=  "</script>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_limpaFLASH() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaLimpaflash'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>!! LIMPA MEMÓRIA FLASH !!</h1>";
  html += "<div style='border-style:inset; width:600px; background-color: Tomato' id='divDoForm'>";
  html += "<form action='/limpaflash' method='POST' style='margin:5px'>";
  html += "<label for='id_flash'>Qual ação de limpeza quer realizar da memória flash?: </label><br>";
  html += "<br>Acoes , ExcetoWifi, Tudo, Formatar";
  html += "<input type='text' name='FLASH' id='id_flash' value='Comando?' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='!!EXECUTAR!!' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes...f_limpaFLASH()");

  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    if (SERVIDOR_WEB.arg("FLASH") == "Tudo") {
      Serial.print("As preferencias estao sendo limpas, todas as configuracoes serão perdidas... ");
      CONFIG_FLASH.begin("confiGeral", false);
      CONFIG_FLASH.clear();
      CONFIG_FLASH.end();
      Serial.println(" OK");
      html += f_MensagemHTML("MEMÓRIA FLASH FOI LIMPA", "As configurações da placa ["+vS_nomeDispositivo+"] foram apagadas.", sucesso);
    } else if (SERVIDOR_WEB.arg("FLASH") == "Formatar") {
      Serial.print("Particao NVS sendo formatada, todas as informacoes serão perdidas... ");
      nvs_flash_erase(); //apague a partição NVS
      nvs_flash_init(); //inicializa a partição NVS
      Serial.println("OK");
      html += f_MensagemHTML("MEMÓRIA FLASH FOI FORMATADA", "A placa ["+vS_nomeDispositivo+"] será reiniciada.", sucesso);
      delay(100);
      ESP.restart();
    } else if (SERVIDOR_WEB.arg("FLASH") == "Acoes") {
      Serial.print("As preferencias de Ações estao sendo limpas, as configuracoes de AÇÕES serão perdidas... ");
      CONFIG_FLASH.begin("confiGeral", false);
      CONFIG_FLASH.remove("paU16_Acao1");
      CONFIG_FLASH.remove("paU8_AcaoRede1");
      CONFIG_FLASH.remove("paS8_Acao1");
      CONFIG_FLASH.remove("paU16_Acao2");
      CONFIG_FLASH.remove("paU8_AcaoRede2");
      CONFIG_FLASH.remove("paS8_Acao2");
      CONFIG_FLASH.remove("paU16_Acao3");
      CONFIG_FLASH.remove("paU8_AcaoRede3");
      CONFIG_FLASH.remove("paS8_Acao3");
      CONFIG_FLASH.end();
      Serial.println(" OK");
      html += f_MensagemHTML("MEMÓRIA FLASH AÇÕES LIMPA", "As Ações da placa ["+vS_nomeDispositivo+"] foram apagadas.", sucesso);
    } else if (SERVIDOR_WEB.arg("FLASH") == "ExcetoWifi") {
      Serial.print("As preferencias de Ações, Pinos, etc. (Exceto Wifi) estao sendo limpas, as CONFIGURAÇÕES serão perdidas... ");
      CONFIG_FLASH.begin("confiGeral");
      CONFIG_FLASH.remove("time_mqtt");
      CONFIG_FLASH.remove("porta_mqtt");
      CONFIG_FLASH.remove("exe_ass");
      CONFIG_FLASH.remove("ass_google");
      CONFIG_FLASH.remove("ass_alexa");
      CONFIG_FLASH.remove("ass_ling");
      CONFIG_FLASH.remove("ass_time");
      CONFIG_FLASH.remove("ass_alerta");
      CONFIG_FLASH.remove("ass_normal");
      CONFIG_FLASH.remove("exe_mod");
      CONFIG_FLASH.remove("time_mod");
      CONFIG_FLASH.remove("porta_mod");
      CONFIG_FLASH.remove("paU16_Pinos");
      CONFIG_FLASH.remove("paS8_Pinos");
      CONFIG_FLASH.remove("paU16_Acao1");
      CONFIG_FLASH.remove("paS8_Acao1");
      CONFIG_FLASH.remove("paU16_Acao2");
      CONFIG_FLASH.remove("paS8_Acao2");
      CONFIG_FLASH.remove("paU16_Acao3");
      CONFIG_FLASH.remove("paS8_Acao3");
      CONFIG_FLASH.remove("paS_InterMod");
      CONFIG_FLASH.end();
      Serial.println(" OK");
      html += f_MensagemHTML("MEMÓRIA FLASH AÇÕES/PINOS/ETC LIMPA", "As Configurações da placa ["+vS_nomeDispositivo+"] foram apagadas.", sucesso);
    }
  }
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_handle_ConfiguraWifiInicio() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigWifiInicio'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Insira as informações do seu WIFI</h1>";
  html += "<div id='mensagens'><p>Insira novas informações para acesso ao seu wifi. Em seguida, clique em Salvar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div>";
  html += "<div style='border-style:inset; width:300px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/wifiinicio' method='POST' style='margin:5px'>";
  html += "<label for='id_ssid'>Informe o SSID: </label>";
  html += "<input type='text' name='SSID' id='id_ssid' value='"+vS_nomeWifi+"' required>";
  html += "<br>";
  html += "<br><label for='id_password'>Informe a Senha: </label>";
  html += "<input type='password' name='PASS' id='id_password' value='"+vS_senhaWifi+"' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Salvar' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraWifi()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.println("Atualizando informacoes Wifi...");
    vS_nomeWifi = SERVIDOR_WEB.arg("SSID");
    vS_senhaWifi = SERVIDOR_WEB.arg("PASS");
    CONFIG_FLASH.begin("confiGeral", false);
    CONFIG_FLASH.putString("nome_wifi", SERVIDOR_WEB.arg("SSID"));
    CONFIG_FLASH.putString("senha_wifi", SERVIDOR_WEB.arg("PASS"));
    CONFIG_FLASH.end();
    Serial.println(" OK");
    Serial.println("Informacoes salvas na flash.");
    html += f_MensagemHTML("INFORMAÇÕES WIFI SALVAR", "As informações do WIFI foram salvas. Reinicie a placa ["+vS_nomeDispositivo+"] para usar as novas configurações.", sucesso);
    vB_finalizaModoAP = true;
  }
  html += "<br><a href=\"/configurag\">Config Geral</a>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_handle_ConfiguraWifi() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigWifi'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Insira as informações de REDE</h1>";
  html += "<div id='mensagens'><p>Insira novas informações de REDE. Em seguida, clique em Salvar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div>";
  html += "<div style='border-style:inset; width:500px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/wifi' method='POST' style='margin:5px'>";
  html += "<label for='id_modap'>Habilita Modo AP: ";
  html += "<input type='checkbox' name='MODAP' id='id_modap' value='1' "+String((vB_modoAP ? "checked" : ""))+"></label>";
  html += "<br>";  
  html += "<label for='id_ssid'>Informe o SSID: </label>";
  html += "<input type='text' name='SSID' id='id_ssid' value='"+vS_nomeWifi+"' required>";
  html += "<br>";
  html += "<br><label for='id_password'>Informe a Senha: </label>";
  html += "<input type='password' name='PASS' id='id_password' value='"+vS_senhaWifi+"' required>";
  html += "<br>";
  html += "<br><label for='id_hstname'>Informe o Hostname*: (mDNS) </label>";
  html += "<input type='text' name='HSTNAME' id='id_hstname' value='"+vS_nomeDispositivo+"' required>";
  html += "<br>";
  html += "<br><label for='id_portaweb'>Informe a Porta do Servidor Web: </label>";
  html += "<input type='text' name='PORTAWEB' maxlength='6' size='6' id='id_portaweb' value='"+String(vU16_portaWeb)+"' required>";
  html += "<br>";
  html += "<br><label for='id_tentcon'>Número de Tentativas de Conexão: </label>";
  html += "<input type='text' name='TENTCON' maxlength='6' size='6' id='id_tentcon' value='"+String(vU8_tentativaConexoes)+"' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraWifi()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.println("Atualizando informacoes Wifi...");
    vB_modoAP = SERVIDOR_WEB.arg("MODAP").toInt();
    vS_nomeWifi = SERVIDOR_WEB.arg("SSID");
    vS_senhaWifi = SERVIDOR_WEB.arg("PASS");
    vS_nomeDispositivo = SERVIDOR_WEB.arg("HSTNAME");
    vU16_portaWeb = SERVIDOR_WEB.arg("PORTAWEB").toInt();
    vU8_tentativaConexoes = SERVIDOR_WEB.arg("TENTCON").toInt();
    Serial.println(" OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES REDE APLICADAS", "As informações da REDE foram aplicadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "*Este nome poderá ser usado para acessar o esp exemplo: hostname.local ou para descobrir o IP do esp exemplo: ping hostname.local";
  html += "<br><a href=\"/intermod\">Config Inter Módulos</a>";
  html += "<br><a href=\"/configurag\">Config Geral</a>";
  html += "<br><a href=\"/\">Página Inicial</a><br>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_handle_NotFound() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Página Não encontrada</h1>";
  html += "<div id='mensagens'></div>";
  html += "<script>";

  html += "document.getElementById('mensagens').innerHTML = '";
  html += "<p>URL: ";
  html += SERVIDOR_WEB.uri();
  html += "</p>";

  html += "<p>Método: ";
  html += (SERVIDOR_WEB.method() == HTTP_GET) ? "GET" : "POST";
  html += "</p>";

  html += "<p>Argumentos: ";
  html += SERVIDOR_WEB.args();
  html += "</p>";
  for (uint8_t i = 0; i < SERVIDOR_WEB.args(); i++) {
    html += "<p> " + SERVIDOR_WEB.argName(i) + ": " + SERVIDOR_WEB.arg(i) + "</p>";
  }
  html += "';";
  html += "</script>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(404, "text/html", html);
}

//========================================
String f_MensagemHTML(String titulo, String corpoMensagem, tipoMensagem mensagem) {
  String html;
  html = "<br><br><div id ='mensagem' style='";
  html += "margin: 0;";
  html += "display:block;";
  html += "position: fixed;";
  html += "top: 50%;";
  html += "left: 50%;";
  html += "min-width: 300px;";
  html += "min-height:120px;";
  html += "-ms-transform: translate(-50%, -50%);";
  html += "transform: translate(-50%, -50%);";

  switch (mensagem) {
    case alerta:
      html += "border: 3px solid #ff5c5c;";
      html += "background-color:#ff8c8c;";
      break;

    case aviso:
      html += "border: 3px solid #ffa05c;";
      html += "background-color:#ffbc8c;";
      break;

    case informacao:
      html += "border: 3px solid #5cb3ff;";
      html += "background-color:#8cc9ff;";
      break;

    case sucesso:
      html += "border: 3px solid #5cffa3;";
      html += "background-color:#8cffbe;";
      break;

    default:
      html += "border: 3px solid #5cb3ff;";
      html += "background-color:#8cc9ff;";
      break;

  }
  html += ">";
  html += "<script>";
  html += "document.getElementById('mensagens').innerHTML = '"+corpoMensagem+"';";
  html += "document.getElementById('divDoForm').style.display = 'none';";
  html += "</script>";
  html += "<h3><center>"+titulo+"<center></h3><br>";
  html += " "+corpoMensagem+" ";
  html +="<br>";

  return html;
}

//========================================
String f_listaPrefPinos() {
  CONFIG_FLASH.begin("confiGeral", true);
  uint16_t aU8Buffer[vI8_aU16_Pinos][vU8_totPinos];
  String aSBuffer[vI8_aS8_Pinos][vU8_totPinos];
  CONFIG_FLASH.getBytes("paU16_Pinos", aU8Buffer, CONFIG_FLASH.getBytesLength("paU16_Pinos"));
  CONFIG_FLASH.getBytes("paS8_Pinos", aSBuffer, CONFIG_FLASH.getBytesLength("paS8_Pinos"));
  String html = "";
  html += "<h3>NOMES PINOS</h3>";
  for (uint8_t x=0; x<vI8_aS8_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";     
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aSBuffer[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "} (Nome)<br>";
  }
  for (uint8_t x=0; x<vI8_aU16_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";    
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8Buffer[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }      
    }
    html += "} (" + aS16_PinosMenu[0][x] + ")<br>";
  }
  CONFIG_FLASH.end();
  return html;
}

//========================================
String f_listaPrefAcoes(uint8_t acoes) {

  CONFIG_FLASH.begin("confiGeral", true);
  String html = "";
  uint16_t aU16BufferX[vI8_aU16_Acao][vU8_totPinos];
  uint8_t aU8BufferY[vI8_aU8_AcaoRede][vU8_totPinos];
//  String aSBufferZ[vI8_aS8_Acao][vU8_totPinos];

  switch (acoes) {
    case 1:
      CONFIG_FLASH.getBytes("paU16_Acao1", aU16BufferX, CONFIG_FLASH.getBytesLength("paU16_Acao1"));
      CONFIG_FLASH.getBytes("paU8_AcaoRede1", aU8BufferY, CONFIG_FLASH.getBytesLength("paU8_AcaoRede1"));
//      CONFIG_FLASH.getBytes("paS8_Acao1", aSBufferZ, CONFIG_FLASH.getBytesLength("paS8_Acao1"));
      for (uint8_t x=0; x<vI8_aU16_Acao; x++){
        html += "Índice "+String(x);
        html += " = {";
        for (uint8_t y=0; y<vU8_totPinos; y++) {
          html += aU16BufferX[x][y];
          if (y < vU8_totPinos-1) {
            html += ",";
          }
        }
        html += "} (" + aS8_AcoesMenu[0][x] + ")<br>";
      }
      html += "<h5>Ações NetConfig</h5>";
      for (uint8_t x=0; x<vI8_aU8_AcaoRede; x++){
        html += "Índice "+String(x);
        html += " = {";
        for (uint8_t y=0; y<vU8_totPinos; y++) {
          html += aU8BufferY[x][y];
          if (y < vU8_totPinos-1) {
            html += ",";
          }
        }
        html += "} (" + aS8_AcoesRedeMenu[0][x] + ")<br>";
      }
      //html += "<h5>Ações MqTTConfig</h5>";
      //for (uint8_t x=0; x<vI8_aS8_Acao; x++){
      //  html += "Índice "+String(x);
      //  html += " = {";
      //  for (uint8_t y=0; y<vU8_totPinos; y++) {
      //    html += aSBufferZ[x][y];
      //    if (y < vU8_totPinos-1) {
      //      html += ",";
      //    }
      //  }
      //  html += "} (" + aS8_AcoesStringMenu[0][x] + ")<br>";
      //}
      break;
    case 2:
      CONFIG_FLASH.getBytes("paU16_Acao2", aU16BufferX, CONFIG_FLASH.getBytesLength("paU16_Acao2"));
      CONFIG_FLASH.getBytes("paU8_AcaoRede2", aU8BufferY, CONFIG_FLASH.getBytesLength("paU8_AcaoRede2"));
//      CONFIG_FLASH.getBytes("paS8_Acao2", aSBufferZ, CONFIG_FLASH.getBytesLength("paS8_Acao2"));
      for (uint8_t x=0; x<vI8_aU16_Acao; x++){
        html += "Índice "+String(x);
        html += " = {";
        for (uint8_t y=0; y<vU8_totPinos; y++) {
          html += aU16BufferX[x][y];
          if (y < vU8_totPinos-1) {
            html += ",";
          }
        }
        html += "} (" + aS8_AcoesMenu[0][x] + ")<br>";
      }
      html += "<h5>Ações NetConfig</h5>";
      for (uint8_t x=0; x<vI8_aU8_AcaoRede; x++){
        html += "Índice "+String(x);
        html += " = {";
        for (uint8_t y=0; y<vU8_totPinos; y++) {
          html += aU8BufferY[x][y];
          if (y < vU8_totPinos-1) {
            html += ",";
          }
        }
        html += "} (" + aS8_AcoesRedeMenu[0][x] + ")<br>";
      }
      //html += "<h5>Ações MqTTConfig</h5>";
      //for (uint8_t x=0; x<vI8_aS8_Acao; x++){
      //  html += "Índice "+String(x);
      //  html += " = {";
      //  for (uint8_t y=0; y<vU8_totPinos; y++) {
      //    html += aSBufferZ[x][y];
      //    if (y < vU8_totPinos-1) {
      //      html += ",";
      //    }
      //  }
      //  html += "} (" + aS8_AcoesStringMenu[0][x] + ")<br>";
      //}    
      break;
    case 3:
      CONFIG_FLASH.getBytes("paU16_Acao3", aU16BufferX, CONFIG_FLASH.getBytesLength("paU16_Acao3"));
      CONFIG_FLASH.getBytes("paU8_AcaoRede3", aU8BufferY, CONFIG_FLASH.getBytesLength("paU8_AcaoRede3"));
//      CONFIG_FLASH.getBytes("paS8_Acao3", aSBufferZ, CONFIG_FLASH.getBytesLength("paS8_Acao3"));
      html += "<h5>AçõesPg 1</h5>";
      for (uint8_t x=0; x<vI8_aU16_Acao; x++){
        html += "Índice "+String(x);
        html += " = {";
        for (uint8_t y=0; y<vU8_totPinos; y++) {
          html += aU16BufferX[x][y];
          if (y < vU8_totPinos-1) {
            html += ",";
          }
        }
        html += "} (" + aS8_AcoesMenu[0][x] + ")<br>";
      }
      html += "<h5>Ações NetConfig</h5>";
      for (uint8_t x=0; x<vI8_aU8_AcaoRede; x++){
        html += "Índice "+String(x);
        html += " = {";
        for (uint8_t y=0; y<vU8_totPinos; y++) {
          html += aU8BufferY[x][y];
          if (y < vU8_totPinos-1) {
            html += ",";
          }
        }
        html += "} (" + aS8_AcoesRedeMenu[0][x] + ")<br>";
      }
      //html += "<h5>Ações MqTTConfig</h5>";
      //for (uint8_t x=0; x<vI8_aS8_Acao; x++){
      //  html += "Índice "+String(x);
      //  html += " = {";
      //  for (uint8_t y=0; y<vU8_totPinos; y++) {
      //    html += aSBufferZ[x][y];
      //    if (y < vU8_totPinos-1) {
      //      html += ",";
      //    }
      //  }
      //  html += "} (" + aS8_AcoesStringMenu[0][x] + ")<br>";
      //}    
      break;
  }

  CONFIG_FLASH.end();
  return html;
}

//========================================
String f_listaPrefModulos() {
/*
Usado para cadastro dos modulos (Inter Modulos)
aS_InterMod[Propriedade][Modulo]
aS_InterMod[0][x] = Nome Modulo
aS_InterMod[1][x] = IP Modulo
--------------------------------------------------------------------
aU16_InterMod[0][x] = Pino HandShake
*/
  CONFIG_FLASH.begin("confiGeral", true);
  String html = "";
  String aSBuffer4[vI8_aS_InterMod][vU8_totPinos];
  CONFIG_FLASH.getBytes("paS_InterMod", aSBuffer4, CONFIG_FLASH.getBytesLength("paS_InterMod"));
  html += "<br>Nome - IP dos Módulos<br>";
  for (uint8_t x=0; x<vI8_aS_InterMod; x++){
    html += "Índice "+String(x);
    html += " = {";        
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aSBuffer4[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "} "+aS_InterModMenu[0][x]+"<br>";
  }
  uint16_t aU8Buffer4[vI8_aU16_InterMod][vU8_totPinos];
  CONFIG_FLASH.getBytes("paU16_InterMod", aU8Buffer4, CONFIG_FLASH.getBytesLength("paU16_InterMod"));
  html += "ID-Pino - Porta<br>";
  for (uint8_t x=0; x<vI8_aU16_InterMod; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8Buffer4[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} "+aU16_InterModMenu[0][x]+"<br>";
  }
  bool aBBuffer4[vI8_aB_InterMod][vU8_totPinos];
  CONFIG_FLASH.getBytes("paB_InterMod", aBBuffer4, CONFIG_FLASH.getBytesLength("paB_InterMod"));
  html += "Envia HandShake<br>";
  for (uint8_t x=0; x<vI8_aB_InterMod; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aBBuffer4[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} "+aSB_InterModMenu[0][x]+"<br>";
  }

  CONFIG_FLASH.end();
  return html;
}

//========================================
void f_listaPreferencesMEM() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Informações de Parâmetros do Sistema Executando em Memória</h1>";
  html += "<div id='mensagens'></div>";
  html += "<a href=\"/\">Página Inicial</a><br>";
  html += "<a href='/lsprefflash'>Listar Flash</a><br>";
  html += "<a href=\"/expimp\">Configuração em Massa</a><br>";
  html += "<a href=\"/salvaflash\">Salvar na Flash</a><br>";
  html += "<h1>EXECUTANDO NA MEMÓRIA</h1>";
  html += "<h3>NOMES PINOS</h3>";
  for (uint8_t x=0; x<vI8_aS8_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aS8_Pinos[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (Nome)<br>";
  }
  html += "<h3>PINOS</h3>";
  for (uint8_t x=0; x<vI8_aU16_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Pinos[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (" + aS16_PinosMenu[0][x] + ")<br>";
  }
  html += "<br>";
  for (uint8_t x=0; x<1; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Pinos_Status[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (Status)<br>";
  }    
  html += "<h3>AÇÕES</h3>";
  html += "<h5>1ª Ações Pg1/2</h5>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Acao1[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (" + aS8_AcoesMenu[0][x] + ")<br>";
  }
  html += "<h5>Ações NetConfig</h5>";
  for (uint8_t x=0; x<vI8_aU8_AcaoRede; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8_AcaoRede1[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (" + aS8_AcoesRedeMenu[0][x] + ")<br>";
  }
  //html += "<h5>Ações MqTTConfig</h5>";
  //for (uint8_t x=0; x<vI8_aS8_Acao; x++){
  //  html += "Índice "+String(x);
  //  html += " = {";
  //  for (uint8_t y=0; y<vU8_totPinos; y++) {
  //    html += aS8_Acao1[x][y];
  //    if (y < vU8_totPinos-1) {
  //      html += ",";
  //    }
  //  }
  //  html += "} (" + aS8_AcoesStringMenu[0][x] + ")<br>";
  //}
  html += "<h5>2ª Ações Pg1/2</h5>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Acao2[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (" + aS8_AcoesMenu[0][x] + ")<br>";
  }
  html += "<h5>Ações NetConfig</h5>";
  for (uint8_t x=0; x<vI8_aU8_AcaoRede; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8_AcaoRede2[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (" + aS8_AcoesRedeMenu[0][x] + ")<br>";
  }
  //html += "<h5>Ações MqTTConfig</h5>";
  //for (uint8_t x=0; x<vI8_aS8_Acao; x++){
  //  html += "Índice "+String(x);
  //  html += " = {";
  //  for (uint8_t y=0; y<vU8_totPinos; y++) {
  //    html += aS8_Acao2[x][y];
  //    if (y < vU8_totPinos-1) {
  //      html += ",";
  //    }
  //  }
  //  html += "} (" + aS8_AcoesStringMenu[0][x] + ")<br>";
  //}  
  html += "<h5>3ª Ações Pg1/2</h5>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Acao3[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (" + aS8_AcoesMenu[0][x] + ")<br>";
  }
  html += "<h5>Ações NetConfig</h5>";
  for (uint8_t x=0; x<vI8_aU8_AcaoRede; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8_AcaoRede3[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} (" + aS8_AcoesRedeMenu[0][x] + ")<br>";
  }
  //html += "<h5>Ações MqTTConfig</h5>";
  //for (uint8_t x=0; x<vI8_aS8_Acao; x++){
  //  html += "Índice "+String(x);
  //  html += " = {";
  //  for (uint8_t y=0; y<vU8_totPinos; y++) {
  //    html += aS8_Acao3[x][y];
  //    if (y < vU8_totPinos-1) {
  //      html += ",";
  //    }
  //  }
  //  html += "} (" + aS8_AcoesStringMenu[0][x] + ")<br>";
  //}

  html += "<h3>GRUPO DE AÇÕES</h3>";
  String grupo = "";
  for (uint8_t x=0; x<vU8_totPinos; x++){
    if (f_retornaGrupoAcao(aU16_ControlAcoesGroups[0][x]).length() > 0) {
      grupo += "Índice "+String(x);
      grupo += " = ";
      grupo += aU16_ControlAcoesGroups[0][x];
      grupo += "{";
      grupo += f_retornaGrupoAcao(aU16_ControlAcoesGroups[0][x]);
      grupo += "}<br>";
    }
  }
  if (grupo.length() > 0) {
    html += grupo;
  } else {
    html += "Sem grupo de ações";
  }
  html += "<h3>ANALÓGICO</h3>";
  html += "Bits do Processador: ";
  html += vU8_bitsProc;
  html += "<br>Ciclos por amostra: ";
  html += vU8_ciclosAmostra;
  html += "<h3>REDE</h3>";
  html += "Hostname: ";
  html += vS_nomeDispositivo;
  html += "<br>Porta WEB: ";
  html += vU16_portaWeb;
  html += "<br>SSID Conectado: ";
  html += WiFi.SSID();
  html += "<br>Modo AP: ";
  html += vB_modoAP;
  html += "<br>Inter Módulos habilitado: ";
  html += vB_exec_Modulos;
  html += "<br>Nome - IP dos Módulos <br>";
  for (uint8_t x=0; x<vI8_aS_InterMod; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aS_InterMod[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "} "+aS_InterModMenu[0][x]+"<br>";
  }
  html += "<br>ID-Pino - Porta <br>";
  for (uint8_t x=0; x<vI8_aU16_InterMod; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_InterMod[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      } 
    }
    html += "} "+aU16_InterModMenu[0][x]+"<br>";
  }
  html += "<br>Envia HandShake <br>";
  for (uint8_t x=0; x<vI8_aB_InterMod; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aB_InterMod[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      } 
    }
    html += "} "+aSB_InterModMenu[0][x]+"<br>";
  }
  html += "<br>Tempo HandShake: ";
  html += vU16_modulos_HandShake;
  html += "<br>Ciclo Handshake: ";
  html += String(vI_cicloHandshake);
  html += "<br>Tempo de Verificação das Ações: ";
  html += vU16_modulos_MTBS_Acoes;
  html += "<h3>TELEGRAM</h3>";
  html += "Habilita Telegram: ";
  html += vB_exec_Telegram;
  html += "<br>API Telegram: ";
  html += vS_api_Telegram;
  html += "<br>ID Chat Telegram: ";
  html += vS_chat_Telegram;
  html += "<br>Nome bot Telegram: ";
  html += vS_user_Telegram;
  html += "<br>Tempo Verificação Telegram: ";
  html += vU16_bot_MTBS;
  html += "<h3>MQTT</h3>";
  html += "Habilita MqTT: ";
  html += vB_exec_MqTT;
  html += "<br>Servidor MqTT: ";
  html += vS_mqttServer;
  html += "<br>Usuário MqTT: ";
  html += vS_mqttUser;
  html += "<br>Senha MqTT: ";
  for (uint8_t x=vS_mqttSenha.length() ; x>0 ; x--) {
    html += "*";
  }
  html += "<br>Porta MqTT: ";
  html += vU16_mqttPorta;
  html += "<br>Tópico MqTT: ";
  html += vS_mqttTopico;
  html += "<br>Tempo Verificação MqTT: ";
  html += vU16_mqtt_MTBS;
  html += "<br>Tempo Descoberta MqTT: ";
  html += vU32_mqtt_disc_MTBS;
  html += "<h3>ASSISTENTES</h3>";
  html += "Habilita Assistentes: ";
  html += vB_exec_Assistente;
  html += "<br>Nome Assistente Google: ";
  html += vS_assNomeGoogle;
  html += "<br>Nome Assistente Alexa: ";
  html += vS_assNomeAlexa;
  html += "<br>Linguagem dos Assistentes: ";
  html += vS_assLinguagem;
  html += "<br>Tempo Envio Assistentes: ";
  html += vU16_ass_MTBS;
  html += "<br>Início Frase Alerta Assistentes: ";
  html += vS_ass_Alerta;
  html += "<br>Início Frase Normalização Assistentes: ";
  html += vS_ass_Normal;
  html += "<br><hr>";

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

  html += "<br><a href='/salvaflash'>Salvar na Flash</a><br>";
  html += "<a href='/expimp'>Configuração em Massa</a><br>";
  html += "<a href='/lsprefflash'>Listar Flash</a><br>";
  html += "<a href='/'>Página Inicial</a><br>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_listaPreferencesFLASH() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Informações de Parâmetros do Sistema Salvas na Flash</h1>";
  html += "<div id='mensagens'></div>";
  html += "<a href=\"/\">Página Inicial</a><br>";
  html += "<a href='/lsprefpin'>Listar Memória</a><br>";
  html += "<a href=\"/expimp\">Configuração em Massa</a><br>";
  html += "<a href=\"/salvaflash\">Salvar na Flash</a><br>";  
  html += "<h1>SALVAS NA FLASH</h1>";

  html += "<h3>PINOS</h3>"; 
  html += f_listaPrefPinos();

  html += "<h3>AÇÕES</h3>";
  
  html += "<h5>1ª Ações Pg1/2</h5>";
  html += f_listaPrefAcoes(1);
  
  html += "<h5>2ª Ações Pg1/2</h5>";
  html += f_listaPrefAcoes(2);

  html += "<h5>3ª Ações Pg1/2</h5>";
  html += f_listaPrefAcoes(3);

  CONFIG_FLASH.begin("confiGeral", true);
  //html += "<h3>ANALÓGICO</h3>";
  //html += "Bits do Processador: "+String(CONFIG_FLASH.getUChar("bits_proc", 0));
  //html += "<br>Ciclos por amostra: "+String(CONFIG_FLASH.getUChar("cicl_samp", 0));
  html += "<h3>REDE</h3>";
  html += "SSID: "+CONFIG_FLASH.getString("nome_wifi", "");
  String vS_t = CONFIG_FLASH.getString("senha_wifi", "");
  html += "<br>SENHA: ";
  for (uint8_t x=vS_t.length() ; x>0 ; x--) {
    html += "*";
  }
  html += "<br>HOSTNAME: "+CONFIG_FLASH.getString("nome_disp", "");
  html += "<br>PORTA WEB: "+String(CONFIG_FLASH.getUShort("porta_srvweb", 0));
  html += "<br>TENTATIVAS CONEXÕES: "+String(CONFIG_FLASH.getUChar("tenta_conect", 0));
  html += "<br>SSID Modo AP: "+CONFIG_FLASH.getString("nome_wifi_ap", "");
  html += "<br>Senha Wifi Modo AP: "+CONFIG_FLASH.getString("senha_wifi_ap", "");
  html += "<br>Modo AP habilitado: "+String(CONFIG_FLASH.getBool("modo_wifi_ap", false));
  html += "<br>Inter Módulos habilitado: "+String(CONFIG_FLASH.getBool("exe_mod", false));
  //html += "<br>Porta dos Módulos: "+String(CONFIG_FLASH.getULong64("porta_mod", 65535));
  html += "<br>Tempo Kandshake: "+String(CONFIG_FLASH.getULong64("time_mod", 65535));
  html += "<br>Ciclo Handshake: "+String(CONFIG_FLASH.getULong64("ciclo_mod", 65535));
  html += "<br>Tempo de Verificação das Ações: "+String(CONFIG_FLASH.getULong64("time_mod_ac", 65535));
  
  html += f_listaPrefModulos();

  html += "<h3>TELEGRAM</h3>";
  html += "Habilita Telegram: "+String(CONFIG_FLASH.getBool("exe_teleg", false));
  html += "<br>API Telegram: "+CONFIG_FLASH.getString("api_teleg", ":");
  html += "<br>ID Chat Telegram: "+CONFIG_FLASH.getString("chat_teleg", "-");
  html += "<br>Nome Bot Telegram: "+CONFIG_FLASH.getString("boot_teleg", "@");
  html += "<br>Tempo Verificação Telegram: "+String(CONFIG_FLASH.getULong64("time_teleg", 0));
  html += "<h3>MQTT</h3>";
  html += "Habilita MqTT: "+String(CONFIG_FLASH.getBool("exe_mqtt", false));
  html += "<br>Topico MqTT: "+CONFIG_FLASH.getString("top_mqtt", "");
  html += "<br>Servidor MqTT: "+CONFIG_FLASH.getString("srv_mqtt", "");
  html += "<br>Usuário MqTT: "+CONFIG_FLASH.getString("usr_mqtt", "");
  vS_t = CONFIG_FLASH.getString("pss_mqtt", "");
  html += "<br>Senha MqTT: ";
  for (uint8_t x=vS_t.length() ; x>0 ; x--) {
    html += "*";
  }
  html += "<br>Porta MqTT: "+String(CONFIG_FLASH.getUShort("porta_mqtt", 0));
  html += "<br>Tempo MqTT: "+String(CONFIG_FLASH.getULong64("time_mqtt", 65534));
  html += "<br>Descoberta MqTT: "+String(CONFIG_FLASH.getULong64("disc_mqtt", 65534));
  html += "<h3>ASSISTENTES</h3>";
  html += "Habilita Assistentes: "+String(CONFIG_FLASH.getBool("exe_ass", false));
  html += "<br>Nome Assistente Google: "+CONFIG_FLASH.getString("ass_google", "");
  html += "<br>Nome Assistente Alexa: "+CONFIG_FLASH.getString("ass_alexa", "");
  html += "<br>Linguagem dos Assistentes: "+CONFIG_FLASH.getString("ass_ling", "");
  html += "<br>Tempo Envio para Assistentes: "+String(CONFIG_FLASH.getULong64("ass_time", 65535));
  html += "<br>Tempo Início Frase Alerta Assistentes: "+CONFIG_FLASH.getString("ass_alerta", "");
  html += "<br>Tempo Início Frase Normalização Assistentes: "+CONFIG_FLASH.getString("ass_normal", "");

  CONFIG_FLASH.end();

  html += "<br><a href='/salvaflash'>Salvar na Flash</a><br>";
  html += "<a href='/expimp'>Configuração em Massa</a><br>";
  html += "<a href='/lsprefpin'>Listar Memória</a><br>";
  html += "<a href='/'>Página Inicial</a><br>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}