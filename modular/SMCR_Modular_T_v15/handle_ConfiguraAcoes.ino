//========================================
void f_handle_ConfiguraAcoes() {
  String html;

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigAcoes'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Insira as informações das Ações</h1>";
  html += "<div id='mensagens'><p>Insira novas informações de configuração das Ações. Em seguida, clique em Aplicar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div>";
  html += "<br> Origem - Pino de Origem (sensor/entrada)";
  html += "<br> Destino - Pino de Destino (atuador/saída)";
  html += "<br> Ação - NENHUMA=0 / LIGA=1 / LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5";
  html += "<br> Nível Acionamento - BAIXO=0 / ALTO=1";
  html += "<br> Ação On - Tempo ligado ou delay para ações de acionamento";
  html += "<br> Ação Off - Tempo desligado ou delay para ações de desligamento";
  html += "<br> Envia Receptor - NÃO=0 / SIM=1";
  html += "<br> Envia Telegram - NÃO=0 / SIM=1";
  html += "<br> Envia MqTT - NÃO=0 / SIM=1";
  html += "<br> Classe MqTT - switch / binary_sensor / sensor / Consultar Tabela";
  html += "<br> Notifica Assistente - NÃO=0 / SIM=1<br>";
  html += "<br><a href=\"/\">Página Inicial</a>";
  html += "<br><a href=\"/acoes2\">Açṍes Pg2</a>";
  html += "<br><a href=\"/acoes3\">Açṍes Pg3</a><br>";
  html += "<br><div style='border-style:inset; width:1300px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/acoes' method='POST' style='margin:5px'>";
  html += "<table border='1'>";
  uint8_t linha = vU8_totPinos/5;
  uint8_t colINICIO = 0;
  uint8_t colFIM = 6;
  uint8_t x;  
  while (linha > 0) {
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Pino Origem</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' style='background-color: LightGrey' name='PINORI"+String(x)+"' value='"+String(aU8_Pinos[0][x])+"' readonly required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Pino Destino</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='PINDES"+String(x)+"' value='"+String(aU16_Acao1[1][x])+"' required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Ação</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='ACAO"+String(x)+"' value='"+String(aU16_Acao1[2][x])+"' required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Nível Acion.</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='NIVAC"+String(x)+"' value='"+String(aU16_Acao1[9][x])+"' required></center></td>";
                    }
    html += "    </tr>";    
    html += "    <tr>";                  
    html += "        <td style='background-color: LightGrey'><center>Tempo ON</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='TON"+String(x)+"' value='"+String(aU16_Acao1[3][x])+"' required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Tempo OFF</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='TOFF"+String(x)+"' value='"+String(aU16_Acao1[4][x])+"' required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Envia Receptor</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='EVREC"+String(x)+"' value='"+String(aU16_Acao1[5][x])+"' required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Envia Telegram</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='EVTEL"+String(x)+"' value='"+String(aU16_Acao1[6][x])+"' required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Envia MqTT</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='EVMQT"+String(x)+"' value='"+String(aU16_Acao1[7][x])+"'></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Classe MqTT </center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='CLSMQT"+String(x)+"' value='"+aS8_Acao1[0][x]+"'></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Icone MqTT </center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='ICOMQT"+String(x)+"' value='"+aS8_Acao1[1][x]+"'></center></td>";
                    }
    html += "    </tr>";    
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Not. Assist.</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "        <td><center><input type='text' name='NOTASS"+String(x)+"' value='"+String(aU16_Acao1[8][x])+"' required></center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td colspan='7' style='background-color: LightGrey'>|</td>";
    html += "    </tr>";
    linha--;
    if (linha > 1) {
      colINICIO = colFIM;
      colFIM = colFIM+6;
    } else {
      colINICIO = colFIM;
      colFIM = vU8_totPinos;
    }
  }
  html += "</table>";
  html += "<br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraAcoes()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes Acoes: ");
    for (x=0; x<vU8_totPinos; x++){
      aU16_Acao1[0][x] = SERVIDOR_WEB.arg(("PINORI"+String(x))).toInt();
      aU16_Acao1[1][x] = SERVIDOR_WEB.arg(("PINDES"+String(x))).toInt();
      aU16_Acao1[2][x] = SERVIDOR_WEB.arg(("ACAO"+String(x))).toInt();
      aU16_Acao1[3][x] = SERVIDOR_WEB.arg(("TON"+String(x))).toInt();
      aU16_Acao1[4][x] = SERVIDOR_WEB.arg(("TOFF"+String(x))).toInt();
      aU16_Acao1[5][x] = SERVIDOR_WEB.arg(("EVREC"+String(x))).toInt();
      aU16_Acao1[6][x] = SERVIDOR_WEB.arg(("EVTEL"+String(x))).toInt();
      aU16_Acao1[7][x] = SERVIDOR_WEB.arg(("EVMQT"+String(x))).toInt();
      aU16_Acao1[8][x] = SERVIDOR_WEB.arg(("NOTASS"+String(x))).toInt();
      aU16_Acao1[9][x] = SERVIDOR_WEB.arg(("NIVAC"+String(x))).toInt();
      aS8_Acao1[0][x] = SERVIDOR_WEB.arg(("CLSMQT"+String(x)));
      aS8_Acao1[1][x] = SERVIDOR_WEB.arg(("ICOMQT"+String(x)));
    }
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES AÇÕES ATUALIZADAS", "As informações das AÇÕES foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<br><a href=\"/\">Página Inicial</a>";
  html += "<br><a href=\"/acoes2\">Açṍes Pg2</a>";
  html += "<br><a href=\"/acoes3\">Açṍes Pg3</a><br>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);

}