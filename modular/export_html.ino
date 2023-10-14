//========================================
void f_ExportImport() {
  String html;
  String valores;
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />";
  html += "<title>"+vS_nomeDispositivo+" Exporta/Import</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Exporta e Importa Parâmetros do Sistema</h1>";
  html += "<div id='mensagens'></div>";
  html += "<a href=\"/\">Página Inicial</a><br><br>\n";
  html += "<h1>EXECUTANDO NA MEMÓRIA</h1>";
  html += "<form action='/expimp' method='POST' style='margin:5px'>";
  html += "<h3>PINOS</h3>";
  valores = "";
  for (uint8_t x=0; x<vI8_aU8_Pinos; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aU8_Pinos[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaPinos' rows='"+String(vI8_aU8_Pinos)+"' cols='100'>"+valores+"</textarea>";
  html += "<h3>NOMES</h3>";
  valores = "";
  for (uint8_t x=0; x<vI8_aS8_Pinos; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aS8_Pinos[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    html += "<input type='text' name='Nomes' size='100' value='"+valores+"'><br>";
  }


  html += "<h3>AÇÕES</h3>";
  html += "<h5>AçõesPg 1</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aU16_Acao1[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoes1' rows='"+String(vI8_aU16_Acao)+"' cols='100'>"+valores+"</textarea>";
  html += "<h5>Ações NetConfigPg 1</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aU16_AcaoRede; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aU16_AcaoRede1[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoesRede1' rows='"+String(vI8_aU16_AcaoRede)+"' cols='100'>"+valores+"</textarea>";
  html += "<h5>Ações MqTTConfigPg 1</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aS8_Acao1[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoesString1' rows='"+String(vI8_aS8_Acao)+"' cols='100'>"+valores+"</textarea>";


  html += "<h5>AçõesPg 2</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aU16_Acao2[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoes2' rows='"+String(vI8_aU16_Acao)+"' cols='100'>"+valores+"</textarea>";
  html += "<h5>Ações NetConfigPg 2</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aU16_AcaoRede; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aU16_AcaoRede2[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoesRede2' rows='"+String(vI8_aU16_AcaoRede)+"' cols='100'>"+valores+"</textarea>";
  html += "<h5>Ações MqTTConfigPg 2</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aS8_Acao2[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoesString2' rows='"+String(vI8_aS8_Acao)+"' cols='100'>"+valores+"</textarea>";


  html += "<h5>AçõesPg 3</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aU16_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aU16_Acao3[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoes3' rows='"+String(vI8_aU16_Acao)+"' cols='100'>"+valores+"</textarea>";
  html += "<h5>Ações NetConfigPg 3</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aU16_AcaoRede; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aU16_AcaoRede3[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoesRede3' rows='"+String(vI8_aU16_AcaoRede)+"' cols='100'>"+valores+"</textarea>";
  html += "<h5>Ações MqTTConfigPg 3</h5>";
  valores = "";
  for (uint8_t x=0; x<vI8_aS8_Acao; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aS8_Acao3[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaAcoesString3' rows='"+String(vI8_aS8_Acao)+"' cols='100'>"+valores+"</textarea><br>";


  html += "<h3>REDE</h3>";
  html += "Nome - IP dos Módulos <br>";
  valores = "";
  for (uint8_t x=0; x<vI8_aS_InterMod; x++){
    for (uint8_t y=0; y<vU8_totPinos; y++) {
      valores += aS_InterMod[x][y];
      if (y < vU8_totPinos-1) {
        valores += ",";
      }
    }
    valores += "\n";
  }
  html += "<textarea name='areaInterMod' rows='"+String(vI8_aS_InterMod)+"' cols='100'>"+valores+"</textarea>";

  html += "<br><br>";
  html += "<input type='submit' name='SUBMIT_SALVAR' value='Aplicar (sem salvar)' id='id_salvar'>";
  html += "</form>";
  html += "</div>";
  html += "</div>";

  Serial.println("Aguardando informacoes... f_ExportImport()");
  if (SERVIDOR_WEB.arg("SUBMIT_SALVAR").length() > 0) {
    Serial.print("Atualizando Informacoes massupdate: ");
    int z;
    String xval;
    String val_linha;
    uint8_t xPinos = 0;    
    // Massupdade Pinos
    valores = SERVIDOR_WEB.arg("areaPinos");
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aU8_Pinos[xPinos][z] = xval.toInt();
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        aU8_Pinos[xPinos][z] = xval.toInt();
        xPinos++;
        val_linha = "";
      } else {
        val_linha += valores[x];
      }
    }

    for (int xx=0; xx<vU8_totPinos; xx++){
      if (aU8_Pinos[1][xx] == 1) {
        pinMode(aU8_Pinos[0][xx],aU8_Pinos[2][xx]);
      }
    }

    // Massupdade Nomes Pinos
    xval = "";
    valores = "";
    valores = SERVIDOR_WEB.arg("Nomes");
    z = 0;
    for (uint16_t y=0; y<=valores.length(); y++) {
      if (valores[y] == 44) {
        aS8_Pinos[0][z] = xval;
        xval = "";
        z++;
      } else {
        xval += valores[y];
      }
    }
    xval = xval.substring(0,xval.length()-1);
    aS8_Pinos[0][z] = xval;


    // Massupdade Acoes1
    valores = SERVIDOR_WEB.arg("areaAcoes1");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aU16_Acao1[xPinos][z] = xval.toInt();
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        aU16_Acao1[xPinos][z] = xval.toInt();
        xPinos++;
        val_linha = "";
      } else {
        val_linha += valores[x];
      }
    }
    //aU16_Acao1[xPinos][z] = xval.toInt();
    valores = SERVIDOR_WEB.arg("areaAcoesRede1");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aU16_AcaoRede1[xPinos][z] = xval.toInt();
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        aU16_AcaoRede1[xPinos][z] = xval.toInt();
        xPinos++;
        val_linha = "";
      } else {
        val_linha += valores[x];
      }
    }
    //aU16_AcaoRede1[xPinos][z] = xval.toInt();
    valores = SERVIDOR_WEB.arg("areaAcoesString1");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aS8_Acao1[xPinos][z] = xval;
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        xval = xval.substring(0,xval.length()-1);
        aS8_Acao1[xPinos][z] = xval;
        xPinos++;
        val_linha = "";
        x++;
      } else {
        val_linha += valores[x];
      }
    }
    //xval = xval.substring(0,xval.length()-1);
    //aS8_Acao1[xPinos][z] = xval;

    // Massupdade Acoes2
    valores = SERVIDOR_WEB.arg("areaAcoes2");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aU16_Acao2[xPinos][z] = xval.toInt();
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        aU16_Acao2[xPinos][z] = xval.toInt();
        xPinos++;
        val_linha = "";
      } else {
        val_linha += valores[x];
      }
    }
    //aU16_Acao2[xPinos][z] = xval.toInt();
    valores = SERVIDOR_WEB.arg("areaAcoesRede2");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aU16_AcaoRede2[xPinos][z] = xval.toInt();
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        aU16_AcaoRede2[xPinos][z] = xval.toInt();
        xPinos++;
        val_linha = "";
      } else {
        val_linha += valores[x];
      }
    }
    //aU16_AcaoRede2[xPinos][z] = xval.toInt();
    valores = SERVIDOR_WEB.arg("areaAcoesString2");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aS8_Acao2[xPinos][z] = xval;
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        xval = xval.substring(0,xval.length()-1);
        aS8_Acao2[xPinos][z] = xval;
        xPinos++;
        val_linha = "";
        x++;
      } else {
        val_linha += valores[x];
      }
    }
    //xval = xval.substring(0,xval.length()-1);
    //aS8_Acao2[xPinos][z] = xval;

    // Massupdade Acoes3
    valores = SERVIDOR_WEB.arg("areaAcoes3");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aU16_Acao3[xPinos][z] = xval.toInt();
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        aU16_Acao3[xPinos][z] = xval.toInt();
        xPinos++;
        val_linha = "";
      } else {
        val_linha += valores[x];
      }
    }
    //aU16_Acao3[xPinos][z] = xval.toInt();
    valores = SERVIDOR_WEB.arg("areaAcoesRede3");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aU16_AcaoRede3[xPinos][z] = xval.toInt();
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        aU16_AcaoRede3[xPinos][z] = xval.toInt();
        xPinos++;
        val_linha = "";
      } else {
        val_linha += valores[x];
      }
    }
    //aU16_AcaoRede3[xPinos][z] = xval.toInt();
    valores = SERVIDOR_WEB.arg("areaAcoesString3");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aS8_Acao3[xPinos][z] = xval;
            xval = "";
            z++;
          } else {
            xval += val_linha[y];
          }
        }
        xval = xval.substring(0,xval.length()-1);
        aS8_Acao3[xPinos][z] = xval;
        xPinos++;
        val_linha = "";
        x++;
      } else {
        val_linha += valores[x];
      }
    }
    //xval = xval.substring(0,xval.length()-1);
    //aS8_Acao3[xPinos][z] = xval;

    // Massupdade InterModulos
    valores = SERVIDOR_WEB.arg("areaInterMod");
    xPinos = 0;
    val_linha = "";
    for (uint16_t x=0; x<= valores.length(); x++) {
      if (valores[x] == 13) {
        z = 0;
        xval = "";
        for (uint16_t y=0; y<=val_linha.length(); y++) {
          if (val_linha[y] == 44) {
            aS_InterMod[xPinos][z] = xval;
            xval = "";
            z++;
          } else {
            if (val_linha[y] != 13) {
              xval += val_linha[y];
            }
          }
        }
        xval = xval.substring(0,xval.length()-1);
        aS_InterMod[xPinos][z] = xval;
        xPinos++;
        val_linha = "";
        x++;
      } else {
        val_linha += valores[x];
      }
    }
    //xval = xval.substring(0,xval.length()-1);
    //aS_InterMod[xPinos][z] = xval;

    Serial.println("OK");
    Serial.println("Informacoes novas em uso.");
    html += f_MensagemHTML("INFORMAÇÕES ATUALIZADAS", "As informações foram atualizadas. NÃO Deslige a placa ["+vS_nomeDispositivo+"] antes de salvar as novas configurações.", sucesso);
  }
  html += "<br><br><a href=\"/\">Página Inicial</a>\n";
  html += "</body>";
  html += "</html>";
  SERVIDOR_WEB.send(200, "text/html", html);
}