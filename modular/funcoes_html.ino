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
  html += "<br><a href=\"/wifi\">Config Wifi</a>";
  html += "<br><a href=\"/\">Página Inicial</a><br>";
  html += "<div style='border-style:inset; width:700px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/configurag' method='POST' style='margin:5px'>";
  html += "<label for='id_modap'>Habilita Modo AP: ";
  html += "<input type='text' name='MODAP' id='id_modap' value='"+String(vB_modoAP)+"' required> 0=Não / 1=Sim</label>";
  html += "<br><br>";
  html += "<label for='id_enviarec'>Habilita Inter Módulos: ";
  html += "<input type='text' name='ENVIAREC' id='id_enviarec' value='"+String(vB_exec_Receptor)+"' required> 0=Não / 1=Sim</label>";
  html += "<br>";
  html += "<label for='id_nomerec'>Nome Módulo Remoto: ";
  html += "<input type='text' name='NOMEREC' id='id_nomerec' value='"+vS_nomeReceptor+"' required></label>";
  html += "<br>";
  html += "<label for='id_iprec'>IP do Receptor: ";
  html += "<input type='text' name='IPREC' id='id_iprec' value='"+String(vS_ipReceptor)+"' required></label>";
  html += "<br>";
  html += "<label for='id_portarec'>Porta do Receptor: ";
  html += "<input type='text' name='PORTAREC' id='id_ipporta' value='"+String(vU16_portaWebReceptor)+"' required></label>";
  html += "<br>";
  html += "<label for='id_mtbsrec'>Tempo de Envio do Receptor: ";
  html += "<input type='text' name='MTBSREC' id='id_mtbsrec' value='"+String(vU16_rec_MTBS)+"' required></label>";
  html += "<br><br>";
  html += "<label for='id_hateleg'>Habilita Telegram:";
  html += "<input type='text' name='HATELEG' id='id_hateleg' value='"+String(vB_exec_Telegram)+"' required> 0=Não / 1=Sim</label>";
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
  html += "<input type='number' name='TMPTELEG' id='id_tmpteleg' value='"+String(vU16_bot_MTBS)+"' required></label>";
  html += "<br><br>";
  html += "<label for='id_hamqtt'>Habilita MqTT:";
  html += "<input type='text' name='HAMQTT' id='id_hamqtt' value='"+String(vB_exec_MqTT)+"' required> 0=Não / 1=Sim</label>";
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
  html += "<input type='text' name='PRTMQTT' id='id_prtmqtt' value='"+String(vU16_mqttPorta)+"' required></label>";
  html += "<br>";
  html += "<label for='id_tpcmqtt'>Tópico MqTT: ";
  html += "<input type='text' name='TPCMQTT' id='id_tpcmqtt' value='"+String(vS_mqttTopico)+"' required></label>";
  html += "<br>";
  html += "<label for='id_tmpmqtt'>Tempo de Verificação do MqTT: ";
  html += "<input type='number' name='TMPMQTT' id='id_tmpmqtt' value='"+String(vU16_mqtt_MTBS)+"' required></label>";
  html += "<br>";
  html += "<label for='id_tmpdiscmqtt'>Tempo de Descoberta do MqTT: ";
  html += "<input type='number' name='TMPDISCMQTT' id='id_tmpdiscmqtt' value='"+String(vU32_mqtt_disc_MTBS)+"' required></label>";
  html += "<br><br>";
  html += "<label for='id_haassist'>Habilita Assistentes:";
  html += "<input type='text' name='HAASSIST' id='id_haassist' value='"+String(vB_exec_Assistente)+"' required> 0=Não / 1=Sim</label>";
  html += "<br>";
  html += "<label for='id_nomeassistgoogle'>Nome Assistentes Google: ";
  html += "<input type='text' name='NOMEASSGOOGLE' id='id_nomeassistgoogle' value='"+String(vS_assNomeGoogle)+"' required></label>";
  html += "<br>";
  html += "<label for='id_lingassist'>Linguagem Assistentes: ";
  html += "<input type='text' name='LINGASSIST' id='id_lingassist' value='"+String(vS_assLinguagem)+"' required></label>";
  html += "<br>";
  html += "<label for='id_timeassist'>Tempo Envio Assistentes: ";
  html += "<input type='text' name='TIMEASSIST' id='id_timeassist' value='"+String(vU16_ass_MTBS)+"' required></label>";
  html += "<br>";
  html += "<label for='id_alertaassist'>Início Frase Alerta Assistentes: ";
  html += "<input type='text' name='ALERTAASSIST' id='id_alertaassist' value='"+vS_ass_Alerta+"' required></label>";
  html += "<br>";
  html += "<label for='id_normalassist'>Início Frase Normalização Assistentes: ";
  html += "<input type='text' name='NORMALASSIST' id='id_normalassist' value='"+vS_ass_Normal+"' required></label>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraGeral()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes Gerais: ");
    vB_modoAP = SERVIDOR_WEB.arg("MODAP").toInt();
    vB_exec_Receptor = SERVIDOR_WEB.arg("ENVIAREC").toInt();
    vS_nomeReceptor = SERVIDOR_WEB.arg("NOMEREC");
    vS_ipReceptor = SERVIDOR_WEB.arg("IPREC");
    vU16_portaWebReceptor = SERVIDOR_WEB.arg("PORTAREC").toInt();
    vU16_rec_MTBS = SERVIDOR_WEB.arg("MTBSREC").toInt();
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
    vS_assLinguagem = SERVIDOR_WEB.arg("LINGASSIST");
    vU16_ass_MTBS = SERVIDOR_WEB.arg("TIMEASSIST").toInt();
    vS_ass_Alerta = SERVIDOR_WEB.arg("ALERTAASSIST");
    vS_ass_Normal = SERVIDOR_WEB.arg("NORMALASSIST");
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES GERAIS APLICADAS", "As informações GERAIS foram aplicadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<br><a href=\"/wifi\">Config Wifi</a>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}

//========================================
void f_handle_RecerregarFuncoes() {
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
  html += "<div style='border-style:inset; width:600px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/recarrega' method='POST' style='margin:5px'>";
  html += "<label for='id_recarrega'>Você confirma recarregar as funções do setup? </label>";
  html += "<br>Tudo, TELEGRAM, MQTT, RECEPTOR ou ASSISTENTES";
  html += "<input type='text' name='RECRG' id='id_recarrega' value='Não' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Recarregar' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes...f_handle_RecerregarFuncoes()");

  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    if (SERVIDOR_WEB.arg("RECRG") == "Tudo") {
      Serial.println("Recarregando Setup... ");
        f_configuraTELEGRAM(true);
        f_configuraMQTT(true);
        f_configuraAssistente(true);
        f_configuraReceptor(true);
      html += f_MensagemHTML("SETUP RECARREGADO", "As funções do setup da placa ["+vS_nomeDispositivo+"] foram recarregadas.", sucesso);
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
      f_configuraAssistente(true);
      html += f_MensagemHTML("ASSISTENTES RECARREGADO", "A função Assistentes da placa ["+vS_nomeDispositivo+"] foi recarregada.", sucesso);
    } else if (SERVIDOR_WEB.arg("RECRG") == "RECEPTOR") {
      Serial.println("Recarregando Receptor... ");
      f_configuraReceptor(true);
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
void f_handle_OTA() {
  String html;
  html += "<br>";
  html += f_idPlaca();
  html += "<br><br>";
  html += "<br><a href=\"/\">Pagina Inicial</a>\n";
  html += "<br><br>";
  html += "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>";
  html += "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>";
  html +=    "<input type='file' name='update'>";
  html +=         "<input type='submit' value='Update'>";
  html +=     "</form>";
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
      CONFIG_FLASH.remove("paS8_Acao1");
      CONFIG_FLASH.remove("paU16_Acao2");
      CONFIG_FLASH.remove("paS8_Acao2");
      CONFIG_FLASH.remove("paU16_Acao3");
      CONFIG_FLASH.remove("paS8_Acao3");
      CONFIG_FLASH.end();
      Serial.println(" OK");
      html += f_MensagemHTML("MEMÓRIA FLASH AÇÕES LIMPA", "As Ações da placa ["+vS_nomeDispositivo+"] foram apagadas.", sucesso);
    } else if (SERVIDOR_WEB.arg("FLASH") == "ExcetoWifi") {
      Serial.print("As preferencias de Ações, Pinos, etc. (Exceto Wifi) estao sendo limpas, as CONFIGURAÇÕES serão perdidas... ");
      CONFIG_FLASH.begin("confiGeral");
      CONFIG_FLASH.remove("exe_teleg");
      CONFIG_FLASH.remove("api_teleg");
      CONFIG_FLASH.remove("chat_teleg");
      CONFIG_FLASH.remove("boot_teleg");
      CONFIG_FLASH.remove("time_teleg");
      CONFIG_FLASH.remove("exe_mqtt");
      CONFIG_FLASH.remove("top_mqtt");
      CONFIG_FLASH.remove("srv_mqtt");
      CONFIG_FLASH.remove("usr_mqtt");
      CONFIG_FLASH.remove("pss_mqtt");
      CONFIG_FLASH.remove("time_mqtt");
      CONFIG_FLASH.remove("porta_mqtt");
      CONFIG_FLASH.remove("exe_ass");
      CONFIG_FLASH.remove("ass_google");
      CONFIG_FLASH.remove("ass_alexa");
      CONFIG_FLASH.remove("ass_ling");
      CONFIG_FLASH.remove("ass_time");
      CONFIG_FLASH.remove("ass_alerta");
      CONFIG_FLASH.remove("ass_normal");
      CONFIG_FLASH.remove("paU8_Pinos");
      CONFIG_FLASH.remove("paS8_Pinos");
      CONFIG_FLASH.remove("paU16_Acao1");
      CONFIG_FLASH.remove("paS8_Acao1");
      CONFIG_FLASH.remove("paU16_Acao2");
      CONFIG_FLASH.remove("paS8_Acao2");
      CONFIG_FLASH.remove("paU16_Acao3");
      CONFIG_FLASH.remove("paS8_Acao3");
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
  html += "<h1>Insira as informações do seu WIFI</h1>";
  html += "<div id='mensagens'><p>Insira novas informações para acesso ao seu wifi. Em seguida, clique em Salvar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div>";
  html += "<div style='border-style:inset; width:300px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/wifi' method='POST' style='margin:5px'>";
  html += "<label for='id_ssid'>Informe o SSID: </label>";
  html += "<input type='text' name='SSID' id='id_ssid' value='"+vS_nomeWifi+"' required>";
  html += "<br>";
  html += "<br><label for='id_password'>Informe a Senha: </label>";
  html += "<input type='password' name='PASS' id='id_password' value='"+vS_senhaWifi+"' required>";
  html += "<br>";
  html += "<br><label for='id_hstname'>Informe o Hostname: </label>";
  html += "<input type='text' name='HSTNAME' id='id_hstname' value='"+vS_nomeDispositivo+"' required>";
  html += "<br>";
  html += "<br><label for='id_portaweb'>Informe a Porta do Servidor Web: </label>";
  html += "<input type='number' name='PORTAWEB' id='id_portaweb' value='"+String(vU16_portaWeb)+"' required>";
  html += "<br>";
  html += "<br><label for='id_tentcon'>Número de Tentativas de Conexão: </label>";
  html += "<input type='number' name='TENTCON' id='id_tentcon' value='"+String(vU8_tentativaConexoes)+"' required>";
  html += "<br>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraWifi()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.println("Atualizando informacoes Wifi...");
    vS_nomeWifi = SERVIDOR_WEB.arg("SSID");
    vS_senhaWifi = SERVIDOR_WEB.arg("PASS");
    vS_nomeDispositivo = SERVIDOR_WEB.arg("HSTNAME");
    vU16_portaWeb = SERVIDOR_WEB.arg("PORTAWEB").toInt();
    vU8_tentativaConexoes = SERVIDOR_WEB.arg("TENTCON").toInt();
    Serial.println(" OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES WIFI APLICADAS", "As informações do WIFI foram aplicadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<br><a href=\"/configurag\">Config Geral</a>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
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
  SERVIDOR_WEB.send(200, "text/html", html);
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
void f_listaPreferences() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Informações de Parâmetros do Sistema e Flash</h1>";
  html += "<div id='mensagens'></div>";
  html += "<a href=\"/\">Página Inicial</a><br><br>\n";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/salvaflash'> Salvar na Flash </a>";
  html += "<h1SALVAS NA MEMÓRIA</h1>";
  html += "<h3>PINOS</h3>";
  for (uint8_t x=0; x<vI8_aU8_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8_Pinos[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }
  html += "<h3>NOMES</h3>";
  for (uint8_t x=0; x<vI8_aS8_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aS8_Pinos[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }  
  html += "<h3>AÇÕES</h3>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Acao1[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }
  html += "<h3>CLASSE AÇÕES</h3>";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aS8_Acao1[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }
  html += "<h3>AÇÕES PG 2</h3>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Acao2[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }
  html += "<h3>CLASSE AÇÕES PG 2</h3>";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aS8_Acao2[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }  
  html += "<h3>AÇÕES PG 3</h3>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16_Acao3[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }
  html += "<h3>CLASSE AÇÕES PG 3</h3>";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aS8_Acao2[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }  
  html += "<h3>REDE</h3>";
  html += "<br>Hostname: ";
  html += vS_nomeDispositivo;
  html += "<br>Porta WEB: ";
  html += vU16_portaWeb;
  html += "<br>SSID Conectado: ";
  html += WiFi.SSID();
  html += "<br>Modo AP: ";
  html += vB_modoAP;
  html += "<br>Envia Receptor habilitado: ";
  html += vB_exec_Receptor;
  html += "<br>Nome do Receptor: ";
  html += vS_nomeReceptor;
  html += "<br>IP do Receptor: ";
  html += vS_ipReceptor;
  html += "<br>Porta do Receptor: ";
  html += vU16_portaWebReceptor;
  html += "<br>Tempo Envio ao Receptor: ";
  html += vB_exec_Receptor;
  html += "<h3>TELEGRAM</h3>";
  html += "<br>Habilita Telegram: ";
  html += vB_exec_Telegram;
  html += "<br>API Telegram: ";
  html += vS_api_Telegram;
  html += "<br>ID Chat Telegram: ";
  html += vS_chat_Telegram;
  html += "<br>Nome bot Telegram: ";
  html += vS_user_Telegram;
  html += "<br>Tempo Verificação Telegram: ";
  html += vU16_bot_MTBS;
  html += "<h5>STATUS TELEGRAM</h5>";
  for (uint8_t x=0; x<vI8_aU8_ControlMsgTelegram; x++){
    html += "Índice "+String(x);
    html += " = {";
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8_ControlMsgTelegram[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }
    }
    html += "}<br>";
  }
  html += "<h3>MQTT</h3>";
  html += "<br>Habilita MqTT: ";
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
  html += "<br>Habilita Assistentes: ";
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


  html += "<h1>SALVAS NA FLASH</h1>";
  CONFIG_FLASH.begin("confiGeral", true);
  uint8_t aU8Buffer[7][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paU8_Pinos", aU8Buffer, CONFIG_FLASH.getBytesLength("paU8_Pinos"));
  String aSBuffer[1][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paS8_Pinos", aSBuffer, CONFIG_FLASH.getBytesLength("paS8_Pinos"));
  
  uint16_t aU16Buffer1[10][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paU16_Acao1", aU16Buffer1, CONFIG_FLASH.getBytesLength("paU16_Acao1"));
  String aSBuffer1[2][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paS8_Acao1", aSBuffer1, CONFIG_FLASH.getBytesLength("paS8_Acao1"));
  
  uint16_t aU16Buffer2[10][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paU16_Acao2", aU16Buffer2, CONFIG_FLASH.getBytesLength("paU16_Acao2"));
  String aSBuffer2[2][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paS8_Acao2", aSBuffer2, CONFIG_FLASH.getBytesLength("paS8_Acao2"));

  uint16_t aU16Buffer3[10][vU8_totPinos] = {};  
  CONFIG_FLASH.getBytes("paU16_Acao3", aU16Buffer3, CONFIG_FLASH.getBytesLength("paU16_Acao3"));
  String aSBuffer3[2][vU8_totPinos] = {};
  CONFIG_FLASH.getBytes("paS8_Acao3", aSBuffer3, CONFIG_FLASH.getBytesLength("paS8_Acao3"));

  html += "<h3>PINOS</h3>";  
  for (uint8_t x=0; x<vI8_aU8_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";    
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU8Buffer[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }      
    }
    html += "}<br>";
  }
  html += "<h3>NOMES</h3>";
  for (uint8_t x=0; x<vI8_aS8_Pinos; x++){
    html += "Índice "+String(x);
    html += " = {";     
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aSBuffer[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "}<br>";
  }
  html += "<h3>AÇÕES</h3>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";        
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16Buffer1[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "}<br>";
  }
  html += "<h3>CLASSE/ICONE AÇÕES</h3>";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";        
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aSBuffer1[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "}<br>";
  }
  html += "<h3>AÇÕES PG 2</h3>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";        
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16Buffer2[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "}<br>";
  }
  html += "<h3>CLASSE/ICONE AÇÕES PG 2</h3>";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";        
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aSBuffer2[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "}<br>";
  }
  html += "<h3>AÇÕES PG 3</h3>";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";        
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aU16Buffer3[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "}<br>";
  }
  html += "<h3>CLASSE/ICONE AÇÕES PG 3</h3>";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    html += "Índice "+String(x);
    html += " = {";        
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      html += aSBuffer3[x][y];
      if (y < vU8_totPinos-1) {
        html += ",";
      }       
    }
    html += "}<br>";
  }
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
  html += "<br>Envia Receptor habilitado: "+String(CONFIG_FLASH.getBool("exe_rec", false));
  html += "<br>Nome do receptor: "+CONFIG_FLASH.getString("nome_rec", "");
  html += "<br>IP do Receptor: "+CONFIG_FLASH.getString("ip_rec", "");
  html += "<br>Porta do Receptor: "+String(CONFIG_FLASH.getULong64("porta_rec", 65535));
  html += "<br>Tempo Enviao Receptor: "+String(CONFIG_FLASH.getULong64("time_rec", 65535));
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
  html += "<br><br><a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/salvaflash'> Salvar na Flash </a>";
  html += "<br><br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}