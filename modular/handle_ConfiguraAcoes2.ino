//========================================
void f_handle_ConfiguraAcoes2() {
  String html;

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+" Casdastro de Ações Pg2</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigAcoes'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Insira as informações das Ações</h1>";
  html += "<div id='mensagens'><p>Insira as informações de configuração das Ações Pg 2. e em seguida clique em \"Aplicar\".</p></div>";
  html += "<br><a href=\"/\">Página Inicial</a>";
  html += "<br><a href=\"/acoes\">Açṍes Pg1</a>";
  html += "<br><a href=\"/acoes3\">Açṍes Pg3</a>";
  html += "<br><a href='https://github.com/rede-analista/smcr/blob/main/manual/excadacao.md' target='_blank'>Ajuda</a>";
  html += "<br><div style='border-style:inset; width:1300px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/acoes2' method='POST' style='margin:5px'>";
  html += "<table border='1'>";
  uint8_t linha = vU8_totPinos/5;
  uint8_t colINICIO = 0;
  uint8_t colFIM = 6;
  uint8_t x;  
  while (linha > 0) { 
    for (uint8_t xM = 0; xM<vI8_aU16_Acao;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS8_AcoesMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        if (xM == 0) {
          html += "<td><center><input type='text' style='background-color: LightGrey' name='"+aS8_AcoesMenu[0][xM]+String(x)+"' value='"+String(aU8_Pinos[xM][x])+"' readonly required></center></td>"; 
        } else {
          html += "<td><center><input type='text' name='"+aS8_AcoesMenu[0][xM]+String(x)+"' value='"+String(aU16_Acao2[xM][x])+"'></center></td>";
        }
      }
      html += "    </tr>";
    }
    for (uint8_t xM = 0; xM<vI8_aU16_AcaoRede;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS8_AcoesRedeMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        html += "<td><center><input type='text' name='"+aS8_AcoesRedeMenu[0][xM]+String(x)+"' value='"+String(aU16_AcaoRede2[xM][x])+"'></center></td>";
      }
      html += "    </tr>";
    }
    for (uint8_t xM = 0; xM<vI8_aS8_Acao;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS8_AcoesStringMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        html += "<td><center><input type='text' name='"+aS8_AcoesStringMenu[0][xM]+String(x)+"' value='"+String(aS8_Acao2[xM][x])+"'></center></td>";
      }
      html += "    </tr>";
    }    
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
      for (uint8_t xM = 0; xM<vI8_aU16_Acao;xM++) {
        aU16_Acao2[xM][x] = SERVIDOR_WEB.arg((aS8_AcoesMenu[0][xM]+String(x))).toInt();
      }
      for (uint8_t xM = 0; xM<vI8_aU16_AcaoRede;xM++) {
          aU16_AcaoRede2[xM][x] = SERVIDOR_WEB.arg((aS8_AcoesRedeMenu[0][xM]+String(x))).toInt();
      }
      for (uint8_t xM = 0; xM<vI8_aS8_Acao;xM++) {
          aS8_Acao2[xM][x] = SERVIDOR_WEB.arg((aS8_AcoesStringMenu[0][xM]+String(x)));
      }
    }
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES ATUALIZADAS", "As informações das AÇÕES PG 2 foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<a href='https://github.com/rede-analista/smcr/blob/main/manual/excadacao.md' target='_blank'>Ajuda</a>";
  html += "<br><a href=\"/\">Página Inicial</a>";
  html += "<br><a href=\"/acoes\">Açṍes Pg1</a>";
  html += "<br><a href=\"/acoes3\">Açṍes Pg3</a><br>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);

}