//========================================
void f_handle_Index() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<meta http-equiv='refresh' content='32'>";  
  html += "<title>"+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body>";
  html += "<center><h1>PÁGINA INICIAL [" + vS_nomeDispositivo + "]</h1>Seu ip é: ";
  html += SERVIDOR_WEB.client().remoteIP().toString();
  html += "<br><a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/acoes'> Configurar Acoes</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/pinos'> Configurar Pinos</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/configurag'> Configurações Gerais</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/lsprefpin'> Parâmetros</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/reboota'> Reiniciar Este Módulo</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/firmware'> Atualizar Firmware</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/recarrega'> Recarregar Funções</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/limpaflash'> Limpar Flash</a></center>";
  html += "<h3>SENSORES</h3>";
  html += "<table border='1'>";
  uint8_t linha = vU8_totPinos/5;
  uint8_t colINICIO = 0;
  uint8_t colFIM = 6;
  CONFIG_FLASH.begin("ConfiPinos", true);
  while (linha > 0) {
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Nome</center></td>";
                    for (uint8_t z=colINICIO; z<colFIM; z++){
                      html += "        <td><center>"+String(aS8_Pinos[0][z])+"</center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "        <td style='background-color: LightGrey'><center>Pino</center></td>";
                    for (uint8_t a=colINICIO; a<colFIM; a++){
                      html += "        <td><center>"+String(aU8_Pinos[0][a])+"</center></td>";
                    }
    html += "    </tr>";
    html += "    </tr>";
    html += "        <td style='background-color: LightGrey'><center>Status</center></td>";
                    for (uint8_t b=colINICIO; b<colFIM; b++){
                      html += "        <td><center>"+String(aU8_Pinos[4][b])+"</center></td>";
                    }
    html += "    </tr>";
    html += "    <tr>";
    html += "    <tr>";
    html += "        <th colspan='7' style='background-color: LightGrey'> |</th>";
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
  CONFIG_FLASH.end();
  html += "</table>";
  html += "<br><br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}