//========================================
void f_handle_ConfiguraPortas() {
  String html;

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigPortas'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Insira as informações das Portas</h1>";
  html += "<div id='mensagens'><p>Insira novas informações de configuração das portas. Em seguida, clique em Salvar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div>";
  html += "<br> Tipo - 0=Analogico / 1=Digital / 254=Remoto";
  html += "<br> XoR - 0=Valor igual a leitura do pino / 1=Valor inverso a leitura do pino";
  html += "<br> Status - LOW=0 / HIGH=1";
  html += "<br> Modo - INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0<br>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "<br><div style='border-style:inset; width:1300px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/pinos' method='POST' style='margin:5px'>";
  html += "<table border='1'>";
  uint8_t linha = vU8_totPinos/5;
  uint8_t colINICIO = 0;
  uint8_t colFIM = 6;
  uint8_t x;
  while (linha > 0) {
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Nome</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' name='NOME"+String(x)+"' value='"+String(aS8_Pinos[0][x])+"'></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Pino</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' name='PINO"+String(x)+"' value='"+String(aU8_Pinos[0][x])+"' required></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Status</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><center>"+String(aU8_Pinos[4][x])+"</center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Tipo</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' name='TIPO"+String(x)+"' value='"+String(aU8_Pinos[1][x])+"' required></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Modo</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' name='MODO"+String(x)+"' value='"+String(aU8_Pinos[2][x])+"' required></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";                  
    html += "       <td style='background-color: LightGrey'><center>XoR</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' name='XOR"+String(x)+"' value='"+String(aU8_Pinos[3][x])+"' required></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Retenção</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' name='RETEM"+String(x)+"' value='"+String(aU8_Pinos[5][x])+"' required></td>";
                    }
    html += "    </tr>";
    html += "    <tr>"; 
    html += "       <td style='background-color: LightGrey'><center>Tempo Retenção</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' name='TPRET"+String(x)+"' value='"+String(aU8_Pinos[6][x])+"' required></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td colspan='7' style='background-color: LightGrey' >| </td>";
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
  Serial.println("Aguardando informacoes... f_handle_ConfiguraPortas()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes: ");    
    for (x=0; x<vU8_totPinos; x++){
      aS8_Pinos[0][x] = SERVIDOR_WEB.arg(("NOME"+String(x)));
      aU8_Pinos[0][x] = SERVIDOR_WEB.arg(("PINO"+String(x))).toInt();
      aU8_Pinos[1][x] = SERVIDOR_WEB.arg(("TIPO"+String(x))).toInt();
      aU8_Pinos[2][x] = SERVIDOR_WEB.arg(("MODO"+String(x))).toInt();
      if (aU8_Pinos[1][x] == 1) {
        pinMode(aU8_Pinos[0][x],aU8_Pinos[2][x]);
      }
      aU8_Pinos[3][x] = SERVIDOR_WEB.arg(("XOR"+String(x))).toInt();
      //aU8_Pinos[4][x] = Status ignorar
      aU8_Pinos[5][x] = SERVIDOR_WEB.arg(("RETEM"+String(x))).toInt();
      aU8_Pinos[6][x] = SERVIDOR_WEB.arg(("TPRET"+String(x))).toInt();

    }
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES ATUALIZADAS", "As informações dos PINOS foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }

  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);

}