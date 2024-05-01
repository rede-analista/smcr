//========================================
void f_handle_Index() {
  String html;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  if (VB_mostra_Status) {
    html += "<meta http-equiv='refresh' content='32'>";  
  }
  html += "<title>Módulo: "+vS_nomeDispositivo+"</title>";
  html += "</head>";
  html += "<body>";
  html += "<center><h1>PÁGINA STATUS [" + vS_nomeDispositivo + "]</h1>Seu ip é: ";
  html += SERVIDOR_WEB.client().remoteIP().toString();
  html += f_horaHTML();
  html += "<br>Uptime: ";
  html += f_upTime();
  html += "<br><a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/acoes1pg1'> Configurar Ações</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/pinos'> Configurar Pinos</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/configurag'> Configurações Gerais</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/lsprefpin'> Parâmetros</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/reboota'> Reiniciar Módulo</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/firmware'> Atualizar Firmware</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/recarrega'> Recarregar Funções</a> - ";
  html += "<a href='http://" + WiFi.localIP().toString() + ":" + String(vU16_portaWeb) + "/limpaflash'> Limpar Flash</a> - ";
  html += "<a href='https://github.com/rede-analista/smcr/tree/main' target='_blank'>Ajuda</a></center>";
  if (VB_mostra_Status) {
    html += "<h2>PINOS(Portas)</h2>";
    short linha = vU8_totPinos/vU8_colunasTabelas;
    uint8_t colINICIO = 0;
    uint8_t colFIM = vU8_colunasTabelas;
    uint8_t x;
  
    html += "(Usado: "+String(vU8_PinosCadastrados)+" de "+String(vU8_totPinos)+" pinos)";
    html += "<table border='1'>";
    while (linha >= 0) {
      html += "    <tr>";
      html += "        <td style='background-color: LightGrey'><center>Nome</center></td>";
                      for (uint8_t z=colINICIO; z<colFIM; z++){
                        html += "        <td><center>"+String(aS8_Pinos[0][z])+"</center></td>";
                      }
      html += "    </tr>";
      html += "    <tr>";
      html += "        <td style='background-color: LightGrey'><center>Pino</center></td>";
                      for (uint8_t a=colINICIO; a<colFIM; a++){
                        if (aU16_Pinos[0][a] > 0) {
                          html += "<td><center>"+String(aU16_Pinos[0][a])+"</center></td>";
                        } else {
                          html += "<td><center></center></td>";
                        }
                      }
      html += "    </tr>";
      html += "    </tr>";
      html += "        <td style='background-color: LightGrey'><center>Status</center></td>";
                      for (uint8_t b=colINICIO; b<colFIM; b++){
                        if (aU16_Pinos_Status[0][b] >= aU16_Pinos[4][b] && aU16_Pinos[0][b] > 0) {
                          html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aU16_Pinos_Status[0][b])+"</center></td>";
                        } else if (aU16_Pinos_Status[0][b] < aU16_Pinos[4][b] && aU16_Pinos[0][b] > 0) {
                          html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aU16_Pinos_Status[0][b])+"</center></td>";
                        } else {
                          html += "        <td><center></center></td>"; //"+String(aU16_Pinos_Status[0][b])+"
                        }
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
  
    html += "</table><br>";
    html += "<h2>COMUNICAÇÃO ENTRE MÓDULOS</h2>";
    html += "Ciclo Handshake: ";
    html += String(vI_cicloHandshake);
    html += "<br> Alerta Handshake";
    html += "<table border='1'>";
  
    html += "<tr>";
    html += "<td style='background-color: LightGrey'><center>Módulo</center></td>";
    for (uint8_t z=0; z<vU8_totPinos; z++){
      if (aS_InterMod[0][z].length() >0 && aU16_InterMod[0][z] > 0) {
        html += "        <td><center>"+aS_InterMod[0][z]+"</center></td>";
      }
    }
    html += "</tr>";
    for (uint8_t x=0; x<vI8_aU16_InterModHA; x++) {
        html += "    <tr>";
        html += "    <td style='background-color: LightGrey'><center>"+aS16_InterModHA[0][x]+"</center></td>";
        for (uint8_t y=0; y<vU8_totPinos; y++) {
          if (aS_InterMod[0][y].length() >0) {
            if ( x == 1) {
              if (aI16_ControlHS[x][y] && aU16_InterMod[0][y] > 0) {
                html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aI16_ControlHS[x][y])+"</td>";
              } else {
                if (aU16_InterMod[0][y] > 0) {
                  html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aI16_ControlHS[x][y])+"</td>";
                } else {
                  html += "        <td ><center>-</td>";
                }
              }
            } else if (x == 3) {
              if (aI16_ControlHS[x][y] >= vU8_tentativaConexoes ) {
                html += "        <td style='background-color:"+vS_corStatus1+"'><center>"+String(aI16_ControlHS[x][y])+"</td>";
              } else {
                html += "        <td style='background-color:"+vS_corStatus0+"'><center>"+String(aI16_ControlHS[x][y])+"</td>";
              }
            } else {
                html += "        <td ><center>"+String(aI16_ControlHS[x][y])+"</td>";
            }
          }
        }
        html += "    </tr>";
  
    }
    html += "</table>";

    html += "<p>Último recebido: ";
    html += vS_uri;
    html += "<br>";
    html += "<p>Último envio: (Módulo ID:";
    html += String(vU8_ultimoModEnviado);
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
    html += "<br><hr>";
    html += "<br>Últimos envios:<br>";
    html += ULTIMOS_GET_SERVIDOR;
    html += "<br><br>Últimos recebidos:<br>";
    html += ULTIMOS_GET_RECEBIDOS;
  }
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}