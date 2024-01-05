//========================================
void f_handle_ConfiguraPortas() {
  String html;

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+" Cadastro de Portas</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigPortas'>";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Cadastro de Pinos (Portas)</h1>";
  html += "<div id='mensagens'><p>Insira as informações de configuração dos pinos e em seguida clique em \"Aplicar\".("+String(vU8_totPinos)+" pinos total)</p></div>";
  html += "<a href=\"/\">Página Inicial</a>";
  html += "<br><a href='https://github.com/rede-analista/smcr/blob/main/manual/excadpino.md' target='_blank'>Ajuda</a>";
  html += "<br><div style='border-style:inset; width:auto; background-color: rgb(148, 187, 242)' id='divDoForm'>"; //1145px
  html += "<form action='/pinos' method='POST' style='margin:5px'>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'><br>";
  short linha = vU8_totPinos/vU8_colunasTabelas;
  uint8_t colINICIO = 0;
  uint8_t colFIM = vU8_colunasTabelas;
  uint8_t x;
  html += "<table border='1'>";
  while (linha >= 0) {
    html += "<tr>";
    html += "<td style='background-color: LightGrey'><center>Nome</center></td>";
    for (x=colINICIO; x<colFIM; x++) {
      html += "<td><input type='text' name='NOME"+String(x)+"' maxlength='14' size='14' value='"+aS8_Pinos[0][x]+"'></td>";
    }
    html += "</tr>";

    for (uint8_t xM = 0; xM<vI8_aU8_Pinos;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS8_PinosMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        //if (xM == 4) {
          //html += "<td><center>"+String(aU8_Pinos[xM][x])+"</center></td>";
        //} else {
          html += "<td><input type='text' name='"+aS8_PinosMenu[0][xM]+String(x)+"' maxlength='14' size='14' value='"+aU8_Pinos[xM][x]+"'></td>";
        //}
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
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  Serial.println("Aguardando informacoes... f_handle_ConfiguraPortas()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes: ");
    vU8_PinosCadastrados = 0;
    for (x=0; x<vU8_totPinos; x++){
      aS8_Pinos[0][x] = SERVIDOR_WEB.arg(("NOME"+String(x)));
      for (uint8_t xM = 0; xM<vI8_aU8_Pinos;xM++) {
        aU8_Pinos[xM][x] = SERVIDOR_WEB.arg((aS8_PinosMenu[0][xM]+String(x))).toInt();
        if (aU8_Pinos[1][x] == 1) {
          pinMode(aU8_Pinos[0][x],aU8_Pinos[2][x]);
        }
        if (xM == 0 && aU8_Pinos[xM][x] > 0){
          vU8_PinosCadastrados++;
        }
      }
    }
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES ATUALIZADAS", "As informações dos PINOS foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<a href='https://github.com/rede-analista/smcr/blob/main/manual/excadpino.md' target='_blank'>Ajuda</a>";
  html += "<br><a href='/'>Página Inicial</a>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}