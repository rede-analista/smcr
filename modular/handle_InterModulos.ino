//========================================
void f_handle_InterModulos() {
  String html;

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+" Cadastro Inter Módulos</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigInterModulos'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Cadastro de Módulos</h1>";
  html += "<div id='mensagens'><p>Insira novas informações de configuração dos módulos. Em seguida, clique em \"Aplicar\".("+String(vU8_totPinos)+" módulos total)</p></div>";
  html += "<br><a href=\"/wifi\">Config Rede</a>";
  html += "<br><a href=\"/configurag\">Config Geral</a>";
  html += "<br><a href=\"/\">Página Inicial</a><br>";
  html += "<br><div style='border-style:inset; width:1145px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/intermod' method='POST' style='margin:5px'>";
  html += "<label for='id_enviarec'>Habilita Inter Módulos: ";
  html += "<input type='checkbox' name='ENVIAREC' id='id_enviarec' value='1' "+String((vB_exec_Modulos ? "checked" : ""))+"></label>";
  html += "<br>";
  html += "<label for='id_mtbsrec'>Tempo Kandshake: ";
  html += "<input type='text' name='MTBSREC' id='id_mtbsrec' maxlength='6' size='6' value='"+String(vU16_modulos_HandShake)+"'> 1000 a 65535 </label>";
  html += "<br>";
  html += "<label for='id_ciclomod'>Ciclos Handshake: ";
  html += "<input type='text' name='CICLOMOD' id='id_ciclomod' maxlength='6' size='6' value='"+String(vI_cicloHandshake)+"'> 3 a 255 </label>";
  html += "<br>";
  html += "<label for='id_mtbsacoes'>Tempo de Verificação das Ações: ";
  html += "<input type='text' name='MTBSACOES' id='id_mtbsacoes' maxlength='6' size='6' value='"+String(vU16_modulos_MTBS_Acoes)+"'> 1000 a 65035 </label>";
  html += "<br><br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  short linha = vU8_totPinos/vU8_colunasTabelas;
  uint8_t colINICIO = 0;
  uint8_t colFIM = vU8_colunasTabelas;
  uint8_t x;
  html += "<table border='1'>";
  while (linha >= 0) {

    for (uint8_t xM = 0; xM<vI8_aS_InterMod;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aS_InterModMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        html += "<td><input type='text' name='"+aS_InterModMenu[0][xM]+String(x)+"' maxlength='14' size='14' value='"+aS_InterMod[xM][x]+"'></td>";
      }
      html += "</tr>";
    }

    for (uint8_t xM = 0; xM<vI8_aU16_InterMod;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aU16_InterModMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        html += "<td><input type='text' name='"+aU16_InterModMenu[0][xM]+String(x)+"' maxlength='14' size='14' value='"+String(aU16_InterMod[xM][x])+"'></td>";
      }
      html += "</tr>";
    }

    for (uint8_t xM = 0; xM<vI8_aB_InterMod;xM++) {
      html += "<tr>";
      html += "<td style='background-color: LightGrey'><center>"+aSB_InterModMenu[0][xM]+"</center></td>";
      for (x=colINICIO; x<colFIM; x++){
        html += "<td><center><input type='checkbox' name='"+aSB_InterModMenu[0][xM]+String(x)+"' value='1' "+String((aB_InterMod[xM][x] ? "checked" : ""))+"></center></td>";
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
  Serial.println("Aguardando informacoes... f_handle_InterModulos()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes: ");
    for (x=0; x<vU8_totPinos; x++){
      for (uint8_t xM = 0; xM<vI8_aS_InterMod;xM++) {
        aS_InterMod[xM][x] = SERVIDOR_WEB.arg((aS_InterModMenu[0][xM]+String(x)));
      }
    }
    for (x=0; x<vU8_totPinos; x++){
      for (uint8_t xM = 0; xM<vI8_aU16_InterMod;xM++) {
        aU16_InterMod[xM][x] = SERVIDOR_WEB.arg((aU16_InterModMenu[0][xM]+String(x))).toInt();
      }
    }
    for (x=0; x<vU8_totPinos; x++){
      for (uint8_t xM = 0; xM<vI8_aB_InterMod;xM++) {
        aB_InterMod[xM][x] = SERVIDOR_WEB.arg((aSB_InterModMenu[0][xM]+String(x))).toInt();
      }
    }
    vB_exec_Modulos = SERVIDOR_WEB.arg("ENVIAREC").toInt();
    vU16_modulos_HandShake = SERVIDOR_WEB.arg("MTBSREC").toInt();
    vI_cicloHandshake = SERVIDOR_WEB.arg("CICLOMOD").toInt();
    vU16_modulos_MTBS_Acoes = SERVIDOR_WEB.arg("MTBSACOES").toInt();
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES ATUALIZADAS", "As informações dos MÓDULOS foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<br><a href=\"/wifi\">Config Rede</a>";
  html += "<br><a href=\"/configurag\">Config Geral</a>";
  html += "<br><a href=\"/\">Página Inicial</a><br>";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);

}