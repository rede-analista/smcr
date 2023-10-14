//========================================
void f_handle_Index() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<meta http-equiv='refresh' content='32'>";  
  html += "<title>Módulo: "+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body>";
  html += "<center><h1>PÁGINA INICIAL [" + vS_nomeDispositivo + "]</h1>Seu ip é: ";
  html += SERVIDOR_WEB.client().remoteIP().toString();
  html += "<br><a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/acoes'> Configurar Acoes</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/pinos'> Configurar Pinos</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/configurag'> Configurações Gerais</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/lsprefpin'> Parâmetros</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/reboota'> Reiniciar Módulo</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/firmware'> Atualizar Firmware</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/recarrega'> Recarregar Funções</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/limpaflash'> Limpar Flash</a></center>";
  html += "<h2>SENSORES</h2>";
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
                      if (aU8_Pinos[4][b] && aU8_Pinos[0][b] > 0) {
                        html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aU8_Pinos[4][b])+"</center></td>";
                      } else if (!aU8_Pinos[4][b] && aU8_Pinos[0][b] > 0) {
                        html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aU8_Pinos[4][b])+"</center></td>";
                      } else {
                        html += "        <td><center>"+String(aU8_Pinos[4][b])+"</center></td>";
                      }
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
  html += "</table><br>";
  html += "<h2>COMUNICAÇÃO ENTRE MÓDULOS</h2>";
  html += "Ciclo Handshake: ";
  html += String(vI_controleCicloHandshake);
  html += " de ";
  html += String(vI_cicloHandshake);
  html += "<p <span>Alerta Handshake: </span>";
  if (vB_AlertaHandshake > 0) {
    html += "<span style='background-color:"+vS_corStatus1+"'>"+String(vB_AlertaHandshake)+"</span></p>";
  } else {
    html += "<span style='background-color:"+vS_corStatus0+"'>"+String(vB_AlertaHandshake)+"</span></p>";
  }
  html += "<p>Último recebido: ";
  html += vS_uri;
  html += "<br>";
  html += "<p>Último envio: (Módulo ID:";
  html += vU8_ultimoModEnviado;
  html += ") - ";
  html += GET_SERVIDOR;
  if (vI_httpResponseCode == 200) {
    html += "<div id='idpayload' style='background-color: lightgreen'>";
  } else if (vI_httpResponseCode == 404) {
    html += "<div id='idpayload' style='background-color: lightred'>";
  } else {
    html += "<div id='idpayload' style='background-color: lightyellow'>";
  }
  html += "Resposta: ";
  html += vI_httpResponseCode;
  html += "<br>";
  html += vS_payload;
  html += "</div>";
  html += "<br><br>Últimos envios:<br>";
  html += ULTIMOS_GET_SERVIDOR;
  html += "<br><br>Últimos recebidos:<br>";
  html += ULTIMOS_GET_RECEBIDOS;
  html += "<br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}