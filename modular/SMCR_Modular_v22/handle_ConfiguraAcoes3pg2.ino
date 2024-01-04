//========================================
void f_handle_ConfiguraAcoes3pg2() {
  String html;

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+" Casdastro de Ações Pg6</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigAcoes'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Cadastro de Ações</h1>";
  uint8_t tmpcolINICIO = vU8_totPinos/2;
  uint8_t colINICIO = round(vU8_totPinos/2);
  if (tmpcolINICIO == colINICIO) {
    colINICIO++;
  }
  html += "<div id='mensagens'><p>Insira as informações de configuração das 1ª Ação(pinos "+String(colINICIO)+" a "+String(vU8_totPinos)+"). e em seguida clique em \"Aplicar\".</p></div>";
  html += "<a href='/'>Página Inicial</a>";
  html += "<br><a href='/acoes1pg1'>[ 1ª Ação Pg1</a> - <a href='/acoes1pg2'>1ª Ação Pg2 ]</a> / <a href='/acoes2pg1'>[ 2ª Ação Pg1</a> - <a href='/acoes2pg2'>2ª Ação Pg2 ]</a> / <a href='/acoes3pg1'>[ 3ª Ação Pg1</a> - <a href='/acoes3pg2'>3ª Ação Pg2 ]</a>";
  html += "<br><a href='https://github.com/rede-analista/smcr/blob/main/manual/excadacao.md' target='_blank'>Ajuda</a>";
  html += "<br><div style='border-style:inset; width:auto; background-color: rgb(148, 187, 242)' id='divDoForm'>"; //1145px
  html += "<form action='/acoes3pg2' method='POST' style='margin:5px'>";
    html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar Pg6(sem salvar)' id='id_salvar'><br>";
  short linha = vU8_totPinos/vU8_colunasTabelas;
  linha = linha/2;
  tmpcolINICIO = colINICIO;
  uint8_t colFIM = colINICIO+vU8_colunasTabelas;
  uint8_t x;
  html += "<table border='1'>";
  while (linha >= 0) {

    html += "<tr>";
    html += "<td style='background-color: LightGrey'><center>Nome</center></td>";
    for (x=colINICIO; x<colFIM; x++) {
      html += "<td style='background-color: LightGrey'><center>"+aS8_Pinos[0][x]+"</center></td>";
    }
    html += "</tr>";

    for (uint8_t xM = 0; xM<vI8_aU16_Acao;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS8_AcoesMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        if (xM == 0) {
          html += "<td><center><input type='text' style='background-color: LightGrey' name='"+aS8_AcoesMenu[0][xM]+String(x)+"' maxlength='14' size='14' value='"+String(aU8_Pinos[xM][x])+"' readonly required></center></td>";
        } else {
          html += "<td><center><input type='text' name='"+aS8_AcoesMenu[0][xM]+String(x)+"' maxlength='14' size='14' value='"+String(aU16_Acao3[xM][x])+"'></center></td>";
        }
      }
      html += "</tr>";
    }

    for (uint8_t xM = 0; xM<vI8_aU16_AcaoRede;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS8_AcoesRedeMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        html += "<td><center><input type='text' name='"+aS8_AcoesRedeMenu[0][xM]+String(x)+"' maxlength='14' size='14' value='"+String(aU16_AcaoRede3[xM][x])+"'></center></td>";
      }
      html += "</tr>";
    }

    for (uint8_t xM = 0; xM<vI8_aS8_Acao;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS8_AcoesStringMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        html += "<td><center><input type='text' name='"+aS8_AcoesStringMenu[0][xM]+String(x)+"' maxlength='14' size='14' value='"+aS8_Acao3[xM][x]+"'></center></td>";
      }
      html += "</tr>";
    }    

    html += "<tr>";
    html += "<td colspan='"+String(vU8_colunasTabelas+1)+"' style='background-color: LightGrey'>&nbsp</td>";
    html += "</tr>";
    linha--;
    if (linha > 0) {
      colINICIO = colFIM;
      colFIM = colFIM+vU8_colunasTabelas;
    } else {
      colINICIO = colFIM;
      colFIM = vU8_totPinos;
    }
  }
  html += "</table>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar Pg6(sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraAcoes3pg2");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes Acoes: ");
    bool addass = false;
    for (x=tmpcolINICIO; x<vU8_totPinos; x++){
      for (uint8_t xM = 0; xM<vI8_aU16_Acao;xM++) {
        aU16_Acao3[xM][x] = SERVIDOR_WEB.arg((aS8_AcoesMenu[0][xM]+String(x))).toInt();
      }
      for (uint8_t xM = 0; xM<vI8_aU16_AcaoRede;xM++) {
          aU16_AcaoRede3[xM][x] = SERVIDOR_WEB.arg((aS8_AcoesRedeMenu[0][xM]+String(x))).toInt();
          if(aU16_AcaoRede3[2][x]) {
            addass = true;
            CLIENT_ASS_ALEXA.addDevice(f_traduzAcoesAss(aU16_Acao3[2][x])+" "+aS8_Pinos[0][x], f_callbackNotificaAlexa);
          }
      }
      for (uint8_t xM = 0; xM<vI8_aS8_Acao;xM++) {
          aS8_Acao3[xM][x] = SERVIDOR_WEB.arg((aS8_AcoesStringMenu[0][xM]+String(x)));
      }
    }
    if(addass) {
      f_configuraAssistenteALX(false);
    }
    f_grupoAcoes();
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES AÇÕES ATUALIZADAS", "As informações das AÇÕES foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<a href='https://github.com/rede-analista/smcr/blob/main/manual/excadacao.md' target='_blank'>Ajuda</a>";
  html += "<br><a href='/acoes1pg1'>[ 1ª Ação Pg1</a> - <a href='/acoes1pg2'>1ª Ação Pg2 ]</a> / <a href='/acoes2pg1'>[ 2ª Ação Pg1</a> - <a href='/acoes2pg2'>2ª Ação Pg2 ]</a> / <a href='/acoes3pg1'>[ 3ª Ação Pg1</a> - <a href='/acoes3pg2'>3ª Ação Pg2 ]</a>";
  html += "<br><a href='/'>Página Inicial</a>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);

}