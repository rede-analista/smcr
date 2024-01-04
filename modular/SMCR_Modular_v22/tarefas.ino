//========================================
void TaskLeituraPinos(void *pvParameters) {
/*
aU8_Pinos[0][x] = Fisico Mapeamento dos pinos fisicos
aU8_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO / 254=REMOTO
aU8_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0
aU8_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO
aU8_Pinos_Status[0][x] = Status 0=LOW / 1=HIGH
aU8_Pinos[5][x] = Retencao 0=NAO / 1=SIM
aU8_Pinos[6][x] = Tempo Retencao 0 a 254
*/
  uint8_t aU8_IgnoraPino[1][vU8_totPinos] = {};
  uint8_t idx=0;
  for (;;){
    if (aU8_Pinos[1][idx] != 254) {
      if (aU8_Pinos[0][idx] > 0) {
        if ( aU8_IgnoraPino[0][idx] < 1) {
          aU8_Pinos_Status[0][idx] = f_lePino(aU8_Pinos[1][idx],aU8_Pinos[3][idx],aU8_Pinos[0][idx]);
        }
        if ( aU8_Pinos[5][idx] && aU8_Pinos_Status[0][idx] ) {
            if (!aU8_IgnoraPino[0][idx]) {
              aU8_IgnoraPino[0][idx] = aU8_Pinos[6][idx];
            } else {
              if ( aU8_IgnoraPino[0][idx] > 0) {
                aU8_IgnoraPino[0][idx]--;
              }
            }
        }
      }
    }
    idx++;
    if (idx >= vU8_totPinos){
      idx=0;
    }
    vTaskDelay(4/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoes1Pinos(void *pvParameters) {
/*
aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Delay / 3=Pisca / 4=Pulso / 5=Pulso Delay
aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[5][x] = Acionamento Alto=1 / Baixo=0
*/

  uint8_t aU8_AcaoTP1[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP2DOWN[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP2LigaDelay[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP2LigaDelayTempo[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP3UP[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP3DOWN[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP3TempoUP[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP3TempoDOWN[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP4DOWN[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP4Pulso[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP4PulsoTempo[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP5UP[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP5DOWN[2][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP5PulsoDelayTempoUP[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP5PulsoDelayTempoDOWN[1][vU8_totPinos] = {};

  uint8_t idz=0;
  for (;;){
    switch (aU16_Acao1[2][idz]) {
      case 1: //LIGA
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if (aU8_Pinos_Status[0][idz]) {
            if (!aU8_AcaoTP1[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao1[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao1[1][idz]),aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              }
              aU8_AcaoTP1[0][idz] = 1;
            }
          } else {
            if (aU8_AcaoTP1[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao1[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao1[1][idz]),!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);

              }
              aU8_AcaoTP1[0][idz] = 0;
            }
          }
        }
        break;
      case 2: //LIGA DELAY
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP2LigaDelay[0][idz]) {
                aU8_AcaoTP2LigaDelay[0][idz] = 1;
                aU16_AcaoTP2LigaDelayTempo[0][idz] = aU16_Acao1[3][idz];
              } else {
                if ( aU16_AcaoTP2LigaDelayTempo[0][idz] > 0) {
                  aU16_AcaoTP2LigaDelayTempo[0][idz]--;
                } else {
                  if (!aU8_AcaoTP2DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
                    aU8_AcaoTP2DOWN[0][idz] = 1;
                  }
                }
              }
          } else {
            if (aU8_AcaoTP2LigaDelay[0][idz] || aU8_AcaoTP2DOWN[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao1[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao1[1][idz]),!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              }
              aU8_AcaoTP2LigaDelay[0][idz] = 0;
              aU8_AcaoTP2DOWN[0][idz] = 0;
            }
          }
        }
        break;
      case 3: //PISCA
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP3UP[0][idz]) {
                aU8_AcaoTP3UP[0][idz] = 1;
                aU8_AcaoTP3DOWN[0][idz] = 0;
                aU16_AcaoTP3TempoUP[0][idz] = aU16_Acao1[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              } else {
                if ( aU16_AcaoTP3TempoUP[0][idz] > 0) {
                  aU16_AcaoTP3TempoUP[0][idz]--;
                } else {
                  if (!aU8_AcaoTP3DOWN[0][idz]) {
                    aU8_AcaoTP3DOWN[0][idz] = 1;
                    aU16_AcaoTP3TempoDOWN[0][idz] = aU16_Acao1[4][idz];
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
                  } else {
                    if ( aU16_AcaoTP3TempoDOWN[0][idz] > 0) {
                      aU16_AcaoTP3TempoDOWN[0][idz]--;
                    } else {
                      aU8_AcaoTP3UP[0][idz] = 0;
                    }
                  }
                }
              }
          } else {
            if (aU8_AcaoTP3UP[0][idz] || aU8_AcaoTP3DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              aU8_AcaoTP3UP[0][idz] = 0;
              aU8_AcaoTP3DOWN[0][idz] = 0;   
            }
          }
        }
        break;
      case 4: //PULSO
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP4Pulso[0][idz]) {
                aU8_AcaoTP4Pulso[0][idz] = 1;
                aU16_AcaoTP4PulsoTempo[0][idz] = aU16_Acao1[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              } else {
                if (!aU8_AcaoTP4DOWN[0][idz]) {
                  if ( aU16_AcaoTP4PulsoTempo[0][idz] > 0) {
                    aU16_AcaoTP4PulsoTempo[0][idz]--;
                  } else {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
                    aU8_AcaoTP4DOWN[0][idz] = 1;
                  }
                }
              }
          } else {
            if (aU8_AcaoTP4Pulso[0][idz] || aU8_AcaoTP4DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              aU8_AcaoTP4Pulso[0][idz] = 0;
              aU8_AcaoTP4DOWN[0][idz] = 0;
            }
          }
        }
        break;
      case 5: //PULSO DELAY ON
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP5UP[0][idz]) {
                aU8_AcaoTP5UP[0][idz] = 1;
                aU16_AcaoTP5PulsoDelayTempoUP[0][idz] = aU16_Acao1[3][idz];
              } else {
                if ( aU16_AcaoTP5PulsoDelayTempoUP[0][idz] > 0) {
                  aU16_AcaoTP5PulsoDelayTempoUP[0][idz]--;
                } else {
                  if (aU8_AcaoTP5UP[0][idz] && !aU8_AcaoTP5DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
                    aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] = aU16_Acao1[4][idz];
                    aU8_AcaoTP5DOWN[0][idz] = 1;
                  } else {
                    if (aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] > 0) {
                      aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz]--;
                    } else {
                      if (!aU8_AcaoTP5DOWN[1][idz]) {
                        f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
                        aU8_AcaoTP5DOWN[1][idz] = 1;
                      }
                    }
                  }
                }
              }
          } else {
            if (aU8_AcaoTP5UP[0][idz] ) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])]);
              aU8_AcaoTP5UP[0][idz] = 0;
              aU8_AcaoTP5DOWN[0][idz] = 0;
              aU8_AcaoTP5DOWN[1][idz] = 0;
            }
          }
        }
        break;
      case 254: //Atualiza Status para pino Remoto
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if (aU8_Pinos_Status[0][idz]) {
            aU8_Pinos_Status[0][f_retornaIndicePino(aU16_Acao1[1][idz])] = aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])];
          } else {
            aU8_Pinos_Status[0][f_retornaIndicePino(aU16_Acao1[1][idz])] = !aU8_Pinos[4][f_retornaIndicePino(aU16_Acao1[1][idz])];
          }
        }
        break;
    }
    idz++;
    if (idz >= vU8_totPinos){
      idz=0;
    }
    vTaskDelay(3/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoes2Pinos(void *pvParameters) {
/*
aU16_Acao[10][23]
aU16_Acao[Propriedade][Pino]
aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Daley / 3=Pisca / 4=Pulso / 5=Pulso Delay
aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[5][x] = Envia ao Receptor 0=Nao / 1=Sim
aU16_Acao[6][x] = Envia ao Telegram 0=Nao / 1=Sim
aU16_Acao[7][x] = Envia ao MqTT 0=Nao / 1=Sim
aU16_Acao[8][x] = Notifica Assitente 0=Nao / 1=Sim
aU16_Acao[5][x] = Acionamento Alto=1 / Baixo=0
*/

  uint8_t aU8_AcaoTP1[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP2DOWN[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP2LigaDelay[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP2LigaDelayTempo[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP3UP[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP3DOWN[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP3TempoUP[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP3TempoDOWN[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP4DOWN[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP4Pulso[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP4PulsoTempo[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP5UP[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP5DOWN[2][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP5PulsoDelayTempoUP[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP5PulsoDelayTempoDOWN[1][vU8_totPinos] = {};

  uint8_t idz=0;
  for (;;){
    switch (aU16_Acao2[2][idz]) {
      case 1: //LIGA
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if (aU8_Pinos_Status[0][idz]) {
            if (!aU8_AcaoTP1[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao2[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao2[1][idz]),aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              }
              aU8_AcaoTP1[0][idz] = 1;
            }
          } else {
            if (aU8_AcaoTP1[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao2[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao2[1][idz]),!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);

              }
              aU8_AcaoTP1[0][idz] = 0;
            }
          }
        }
        break;
      case 2: //LIGA DELAY
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP2LigaDelay[0][idz]) {
                aU8_AcaoTP2LigaDelay[0][idz] = 1;
                aU16_AcaoTP2LigaDelayTempo[0][idz] = aU16_Acao2[3][idz];
              } else {
                if ( aU16_AcaoTP2LigaDelayTempo[0][idz] > 0) {
                  aU16_AcaoTP2LigaDelayTempo[0][idz]--;
                } else {
                  if (!aU8_AcaoTP2DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
                    aU8_AcaoTP2DOWN[0][idz] = 1;
                  }
                }
              }
          } else {
            if (aU8_AcaoTP2LigaDelay[0][idz] || aU8_AcaoTP2DOWN[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao2[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao2[1][idz]),!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              }
              aU8_AcaoTP2LigaDelay[0][idz] = 0;
              aU8_AcaoTP2DOWN[0][idz] = 0;
            }
          }
        }
        break;
      case 3: //PISCA
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP3UP[0][idz]) {
                aU8_AcaoTP3UP[0][idz] = 1;
                aU8_AcaoTP3DOWN[0][idz] = 0;
                aU16_AcaoTP3TempoUP[0][idz] = aU16_Acao2[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              } else {
                if ( aU16_AcaoTP3TempoUP[0][idz] > 0) {
                  aU16_AcaoTP3TempoUP[0][idz]--;
                } else {
                  if (!aU8_AcaoTP3DOWN[0][idz]) {
                    aU8_AcaoTP3DOWN[0][idz] = 1;
                    aU16_AcaoTP3TempoDOWN[0][idz] = aU16_Acao2[4][idz];
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
                  } else {
                    if ( aU16_AcaoTP3TempoDOWN[0][idz] > 0) {
                      aU16_AcaoTP3TempoDOWN[0][idz]--;
                    } else {
                      aU8_AcaoTP3UP[0][idz] = 0;
                    }
                  }
                }
              }
          } else {
            if (aU8_AcaoTP3UP[0][idz] || aU8_AcaoTP3DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              aU8_AcaoTP3UP[0][idz] = 0;
              aU8_AcaoTP3DOWN[0][idz] = 0;   
            }
          }
        }
        break;
      case 4: //PULSO
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP4Pulso[0][idz]) {
                aU8_AcaoTP4Pulso[0][idz] = 1;
                aU16_AcaoTP4PulsoTempo[0][idz] = aU16_Acao2[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              } else {
                if (!aU8_AcaoTP4DOWN[0][idz]) {
                  if ( aU16_AcaoTP4PulsoTempo[0][idz] > 0) {
                    aU16_AcaoTP4PulsoTempo[0][idz]--;
                  } else {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
                    aU8_AcaoTP4DOWN[0][idz] = 1;
                  }
                }
              }
          } else {
            if (aU8_AcaoTP4Pulso[0][idz] || aU8_AcaoTP4DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              aU8_AcaoTP4Pulso[0][idz] = 0;
              aU8_AcaoTP4DOWN[0][idz] = 0;
            }
          }
        }
        break;
      case 5: //PULSO DELAY ON
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP5UP[0][idz]) {
                aU8_AcaoTP5UP[0][idz] = 1;
                aU16_AcaoTP5PulsoDelayTempoUP[0][idz] = aU16_Acao2[3][idz];
              } else {
                if ( aU16_AcaoTP5PulsoDelayTempoUP[0][idz] > 0) {
                  aU16_AcaoTP5PulsoDelayTempoUP[0][idz]--;
                } else {
                  if (aU8_AcaoTP5UP[0][idz] && !aU8_AcaoTP5DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
                    aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] = aU16_Acao2[4][idz];
                    aU8_AcaoTP5DOWN[0][idz] = 1;
                  } else {
                    if (aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] > 0) {
                      aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz]--;
                    } else {
                      if (!aU8_AcaoTP5DOWN[1][idz]) {
                        f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
                        aU8_AcaoTP5DOWN[1][idz] = 1;
                      }
                    }
                  }
                }
              }
          } else {
            if (aU8_AcaoTP5UP[0][idz] ) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])]);
              aU8_AcaoTP5UP[0][idz] = 0;
              aU8_AcaoTP5DOWN[0][idz] = 0;
              aU8_AcaoTP5DOWN[1][idz] = 0;
            }
          }
        }
        break;
      case 254: //Atualiza Status para pino Remoto
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if (aU8_Pinos_Status[0][idz]) {
            aU8_Pinos_Status[0][f_retornaIndicePino(aU16_Acao2[1][idz])] = aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])];
          } else {
            aU8_Pinos_Status[0][f_retornaIndicePino(aU16_Acao2[1][idz])] = !aU8_Pinos[4][f_retornaIndicePino(aU16_Acao2[1][idz])];
          }
        }
        break;        
    }
    idz++;
    if (idz >= vU8_totPinos){
      idz=0;
    }
    vTaskDelay(3/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoes3Pinos(void *pvParameters) {
/*
aU16_Acao[10][23]
aU16_Acao[Propriedade][Pino]
aU16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Daley / 3=Pisca / 4=Pulso / 5=Pulso Delay
aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
aU16_Acao[5][x] = Envia ao Receptor 0=Nao / 1=Sim
aU16_Acao[6][x] = Envia ao Telegram 0=Nao / 1=Sim
aU16_Acao[7][x] = Envia ao MqTT 0=Nao / 1=Sim
aU16_Acao[8][x] = Notifica Assitente 0=Nao / 1=Sim
aU16_Acao[5][x] = Acionamento Alto=1 / Baixo=0
*/

  uint8_t aU8_AcaoTP1[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP2DOWN[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP2LigaDelay[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP2LigaDelayTempo[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP3UP[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP3DOWN[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP3TempoUP[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP3TempoDOWN[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP4DOWN[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP4Pulso[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP4PulsoTempo[1][vU8_totPinos] = {};

  uint8_t aU8_AcaoTP5UP[1][vU8_totPinos] = {};
  uint8_t aU8_AcaoTP5DOWN[2][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP5PulsoDelayTempoUP[1][vU8_totPinos] = {};
  uint16_t aU16_AcaoTP5PulsoDelayTempoDOWN[1][vU8_totPinos] = {};

  uint8_t idz=0;
  for (;;){
    switch (aU16_Acao3[2][idz]) {
      case 1: //LIGA
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if (aU8_Pinos_Status[0][idz]) {
            if (!aU8_AcaoTP1[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao3[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao3[1][idz]),aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              }
              aU8_AcaoTP1[0][idz] = 1;
            }
          } else {
            if (aU8_AcaoTP1[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao3[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao3[1][idz]),!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);

              }
              aU8_AcaoTP1[0][idz] = 0;
            }
          }
        }
        break;
      case 2: //LIGA DELAY
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP2LigaDelay[0][idz]) {
                aU8_AcaoTP2LigaDelay[0][idz] = 1;
                aU16_AcaoTP2LigaDelayTempo[0][idz] = aU16_Acao3[3][idz];
              } else {
                if ( aU16_AcaoTP2LigaDelayTempo[0][idz] > 0) {
                  aU16_AcaoTP2LigaDelayTempo[0][idz]--;
                } else {
                  if (!aU8_AcaoTP2DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
                    aU8_AcaoTP2DOWN[0][idz] = 1;
                  }
                }
              }
          } else {
            if (aU8_AcaoTP2LigaDelay[0][idz] || aU8_AcaoTP2DOWN[0][idz]) {
              if (f_retornaGrupoAcao(aU16_Acao3[1][idz]).length() < 1) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              } else if (f_retornaStatusGrupoAcao(f_retornaGrupoAcao(aU16_Acao3[1][idz]),!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])])) {
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              }
              aU8_AcaoTP2LigaDelay[0][idz] = 0;
              aU8_AcaoTP2DOWN[0][idz] = 0;
            }
          }
        }
        break;
      case 3: //PISCA
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP3UP[0][idz]) {
                aU8_AcaoTP3UP[0][idz] = 1;
                aU8_AcaoTP3DOWN[0][idz] = 0;
                aU16_AcaoTP3TempoUP[0][idz] = aU16_Acao3[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              } else {
                if ( aU16_AcaoTP3TempoUP[0][idz] > 0) {
                  aU16_AcaoTP3TempoUP[0][idz]--;
                } else {
                  if (!aU8_AcaoTP3DOWN[0][idz]) {
                    aU8_AcaoTP3DOWN[0][idz] = 1;
                    aU16_AcaoTP3TempoDOWN[0][idz] = aU16_Acao3[4][idz];
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
                  } else {
                    if ( aU16_AcaoTP3TempoDOWN[0][idz] > 0) {
                      aU16_AcaoTP3TempoDOWN[0][idz]--;
                    } else {
                      aU8_AcaoTP3UP[0][idz] = 0;
                    }
                  }
                }
              }
          } else {
            if (aU8_AcaoTP3UP[0][idz] || aU8_AcaoTP3DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              aU8_AcaoTP3UP[0][idz] = 0;
              aU8_AcaoTP3DOWN[0][idz] = 0;   
            }
          }
        }
        break;
      case 4: //PULSO
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP4Pulso[0][idz]) {
                aU8_AcaoTP4Pulso[0][idz] = 1;
                aU16_AcaoTP4PulsoTempo[0][idz] = aU16_Acao3[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              } else {
                if (!aU8_AcaoTP4DOWN[0][idz]) {
                  if ( aU16_AcaoTP4PulsoTempo[0][idz] > 0) {
                    aU16_AcaoTP4PulsoTempo[0][idz]--;
                  } else {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
                    aU8_AcaoTP4DOWN[0][idz] = 1;
                  }
                }
              }
          } else {
            if (aU8_AcaoTP4Pulso[0][idz] || aU8_AcaoTP4DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              aU8_AcaoTP4Pulso[0][idz] = 0;
              aU8_AcaoTP4DOWN[0][idz] = 0;
            }
          }
        }
        break;
      case 5: //PULSO DELAY ON
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos_Status[0][idz] ) {
              if (!aU8_AcaoTP5UP[0][idz]) {
                aU8_AcaoTP5UP[0][idz] = 1;
                aU16_AcaoTP5PulsoDelayTempoUP[0][idz] = aU16_Acao3[3][idz];
              } else {
                if ( aU16_AcaoTP5PulsoDelayTempoUP[0][idz] > 0) {
                  aU16_AcaoTP5PulsoDelayTempoUP[0][idz]--;
                } else {
                  if (aU8_AcaoTP5UP[0][idz] && !aU8_AcaoTP5DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
                    aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] = aU16_Acao3[4][idz];
                    aU8_AcaoTP5DOWN[0][idz] = 1;
                  } else {
                    if (aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] > 0) {
                      aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz]--;
                    } else {
                      if (!aU8_AcaoTP5DOWN[1][idz]) {
                        f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
                        aU8_AcaoTP5DOWN[1][idz] = 1;
                      }
                    }
                  }
                }
              }
          } else {
            if (aU8_AcaoTP5UP[0][idz] ) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])]);
              aU8_AcaoTP5UP[0][idz] = 0;
              aU8_AcaoTP5DOWN[0][idz] = 0;
              aU8_AcaoTP5DOWN[1][idz] = 0;
            }
          }
        }
        break;
      case 254: //Atualiza Status para pino Remoto
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if (aU8_Pinos_Status[0][idz]) {
            aU8_Pinos_Status[0][f_retornaIndicePino(aU16_Acao3[1][idz])] = aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])];
          } else {
            aU8_Pinos_Status[0][f_retornaIndicePino(aU16_Acao3[1][idz])] = !aU8_Pinos[4][f_retornaIndicePino(aU16_Acao3[1][idz])];
          }
        }
        break;        
    }
    idz++;
    if (idz >= vU8_totPinos){
      idz=0;
    }
    vTaskDelay(3/portTICK_PERIOD_MS);
  }
}