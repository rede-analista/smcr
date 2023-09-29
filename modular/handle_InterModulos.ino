//========================================
void f_handle_InterModulos() {
  String html;

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body id='body'>";
  html += "<div id='telaConfigInterModulos'> ";
  html += "<div id='bloqueiaTela'></div>";
  html += "<h1>Insira as informações dos Módulos</h1>";
  html += "<div id='mensagens'><p>Insira novas informações de configuração dos módulos. Em seguida, clique em Salvar para enviar os dados para o ["+vS_nomeDispositivo+"]: </p></div>";
  html += "<br> ID - Referência de cadastro do Módulo";
  html += "<br> Nome - Nome do Módulo";
  html += "<br> Ip - Endereço IP do Módulo<br>";
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "<br><div style='border-style:inset; width:1300px; background-color: rgb(148, 187, 242)' id='divDoForm'>";
  html += "<form action='/intermod' method='POST' style='margin:5px'>";
  html += "<table border='1'>";
  html += "<label for='id_enviarec'>Habilita Inter Módulos: ";
  html += "<input type='text' name='ENVIAREC' id='id_enviarec' value='"+String(vB_exec_Modulos)+"' required> 0=Não / 1=Sim</label>";
  html += "<br>";
  html += "<label for='id_portarec'>Porta do Receptor: ";
  html += "<input type='text' name='PORTAREC' id='id_ipporta' value='"+String(vU16_portaWebModulos)+"' required></label>";
  html += "<br>";
  html += "<label for='id_mtbsrec'>Tempo de Envio do Receptor: ";
  html += "<input type='text' name='MTBSREC' id='id_mtbsrec' value='"+String(vU16_modulos_MTBS)+"' required></label>";
  html += "<br>";
  html += "<label for='id_ciclomod'>Ciclos Handshake: ";
  html += "<input type='text' name='CICLOMOD' id='id_ciclomod' value='"+String(vI_cicloHandshake)+"' required></label>";
  html += "<br><br>";
  uint8_t linha = vU8_totPinos/5;
  uint8_t colINICIO = 0;
  uint8_t colFIM = 6;
  uint8_t x;
  while (linha > 0) {
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>ID</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      html += "<td><input type='text' style='background-color: LightGrey' name='ID"+String(x)+"' value='"+String(x)+"' readonly required></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Nome</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      if (x == 0 && colINICIO == 0) {
                        html += "<td><input type='text' style='background-color: LightGrey' name='NOME"+String(x)+"' value='' readonly ></td>";
                      } else {
                        html += "<td><input type='text' name='NOME"+String(x)+"' value='"+aS_InterMod[0][x]+"'></td>";
                      }
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "       <td style='background-color: LightGrey'><center>Ip</center></td>";
                    for (x=colINICIO; x<colFIM; x++){
                      if (x == 0 && colINICIO == 0) {
                        html += "<td><input type='text' style='background-color: LightGrey' name='IP"+String(x)+"' value='' readonly></td>";
                      } else {
                        html += "<td><input type='text' name='IP"+String(x)+"' value='"+aS_InterMod[1][x]+"'></td>";
                      }
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
  Serial.println("Aguardando informacoes... f_handle_InterModulos()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes: ");    
    for (x=0; x<vU8_totPinos; x++){
      aS_InterMod[0][x] = SERVIDOR_WEB.arg(("NOME"+String(x)));
      aS_InterMod[1][x] = SERVIDOR_WEB.arg(("IP"+String(x)));
    }
    vB_exec_Modulos = SERVIDOR_WEB.arg("ENVIAREC").toInt();
    vU16_portaWebModulos = SERVIDOR_WEB.arg("PORTAREC").toInt();
    vU16_modulos_MTBS = SERVIDOR_WEB.arg("MTBSREC").toInt();
    vI_cicloHandshake = SERVIDOR_WEB.arg("CICLOMOD").toInt();
    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES ATUALIZADAS", "As informações dos MÓDULOS foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }

  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);

}