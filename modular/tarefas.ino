//========================================
void TaskLeituraPinos(void *pvParameters) {
/*
aU8_Pinos[7][23]
aU8_Pinos[Propriedade][Pino]
aU8_Pinos[0][x] = Fisico Mapeamento dos pinos fisicos
aU8_Pinos[1][x] = Tipo 1=DIGITAL / 0=ANALOGICO
aU8_Pinos[2][x] = Modo INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0
aU8_Pinos[3][x] = Invertido(XOR) 1=SIM / 0=NAO
aU8_Pinos[4][x] = Status 0=LOW / 1=HIGH
aU8_Pinos[5][x] = Retencao 0=NAO / 1=SIM
aU8_Pinos[6][x] = Tempo Retencao 0 a 254
*/
  uint8_t aU8_IgnoraPino[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t idx=0;
  for (;;){
    if (aU8_Pinos[1][idx] != 254) {
      if (aU8_Pinos[0][idx] > 0) {
        if ( aU8_IgnoraPino[0][idx] < 1) {
          aU8_Pinos[4][idx] = f_lePino(aU8_Pinos[1][idx],aU8_Pinos[3][idx],aU8_Pinos[0][idx]);
        }
        if ( aU8_Pinos[5][idx] && aU8_Pinos[4][idx] ) {
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
    vTaskDelay(9/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoesPinos(void *pvParameters) {
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
aU16_Acao[9][x] = Acionamento Alto=1 / Baixo=0
*/

  uint8_t aU8_Acao2DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao2LigaDelay[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao2LigaDelayTempo[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao3UP[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao3DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao3TempoUP[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
  uint16_t aU16_Acao3TempoDOWN[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao4DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao4Pulso[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao4PulsoTempo[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao5UP[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao5DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao5PulsoDelayTempoUP[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
  uint16_t aU16_Acao5PulsoDelayTempoDOWN[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t idz=0;
  for (;;){
    switch (aU16_Acao1[2][idz]) {
      case 1: //LIGA
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if (aU8_Pinos[4][idz]) {
            f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU16_Acao1[9][idz]);
          } else {
            f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[9][idz]);
            //aU8_ControlMsgTelegram[0][idz] = 0;
          }
        }
        break;
      case 2: //LIGA DELAY
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao2LigaDelay[0][idz]) {
                aU8_Acao2LigaDelay[0][idz] = 1;
                aU16_Acao2LigaDelayTempo[0][idz] = aU16_Acao1[3][idz];
              } else {
                if ( aU16_Acao2LigaDelayTempo[0][idz] > 0) {
                  aU16_Acao2LigaDelayTempo[0][idz]--;
                } else {
                  f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU16_Acao1[9][idz]);
                }
              }
          } else {
            if (aU8_Acao2LigaDelay[0][idz] || aU8_Acao2DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[9][idz]);
              aU8_Acao2LigaDelay[0][idz] = 0;
              aU8_Acao2DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[0][idz] = 0;
            }
          }
        }
        break;
      case 3: //PISCA
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao3UP[0][idz]) {
                aU8_Acao3UP[0][idz] = 1;
                aU8_Acao3DOWN[0][idz] = 0;
                aU16_Acao3TempoUP[0][idz] = aU16_Acao1[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU16_Acao1[9][idz]);
              } else {
                if ( aU16_Acao3TempoUP[0][idz] > 0) {
                  aU16_Acao3TempoUP[0][idz]--;
                } else {
                  if (!aU8_Acao3DOWN[0][idz]) {
                    aU8_Acao3DOWN[0][idz] = 1;
                    aU16_Acao3TempoDOWN[0][idz] = aU16_Acao1[4][idz];
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[9][idz]);
                  } else {
                    if ( aU16_Acao3TempoDOWN[0][idz] > 0) {
                      aU16_Acao3TempoDOWN[0][idz]--;
                    } else {
                      aU8_Acao3UP[0][idz] = 0;
                    }
                  }
                }
              }
          } else {
            if (aU8_Acao3UP[0][idz] || aU8_Acao3DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[9][idz]);
              aU8_Acao3UP[0][idz] = 0;
              aU8_Acao3DOWN[0][idz] = 0;   
              //aU8_ControlMsgTelegram[0][idz] = 0;
            }
          }
        }
        break;
      case 4: //PULSO
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao4Pulso[0][idz]) {
                aU8_Acao4Pulso[0][idz] = 1;
                aU16_Acao4PulsoTempo[0][idz] = aU16_Acao1[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU16_Acao1[9][idz]);
              } else {
                if ( aU16_Acao4PulsoTempo[0][idz] > 0) {
                  aU16_Acao4PulsoTempo[0][idz]--;
                } else {
                  f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[9][idz]);
                }
              }
          } else {
            if (aU8_Acao4Pulso[0][idz] || aU8_Acao4DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[9][idz]);
              aU8_Acao4Pulso[0][idz] = 0;
              aU8_Acao4DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[0][idz] = 0;
            }
          }
        }
        break;
      case 5: //PULSO DELAY ON
        if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao5UP[0][idz]) {
                aU8_Acao5UP[0][idz] = 1;
                aU16_Acao5PulsoDelayTempoUP[0][idz] = aU16_Acao1[3][idz];
              } else {
                if ( aU16_Acao5PulsoDelayTempoUP[0][idz] > 0) {
                  aU16_Acao5PulsoDelayTempoUP[0][idz]--;
                } else {
                  if (aU8_Acao5UP[0][idz] && !aU8_Acao5DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],aU16_Acao1[9][idz]);
                    aU16_Acao5PulsoDelayTempoDOWN[0][idz] = aU16_Acao1[4][idz];
                    aU8_Acao5DOWN[0][idz] = 1;
                  } else {
                    if (aU16_Acao5PulsoDelayTempoDOWN[0][idz] > 0) {
                      aU16_Acao5PulsoDelayTempoDOWN[0][idz]--;
                    } else {
                      f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[9][idz]);
                    }
                  }
                }
              }
          } else {
            if (aU8_Acao5UP[0][idz] ) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao1[1][idz],!aU16_Acao1[1][idz]);
              aU8_Acao5UP[0][idz] = 0;
              aU8_Acao5DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[0][idz] = 0;
            }
          }
        }
        break;
    }
    idz++;
    if (idz >= vU8_totPinos){
      idz=0;
    }
    vTaskDelay(8/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoesPg2Pinos(void *pvParameters) {
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
aU16_Acao[9][x] = Acionamento Alto=1 / Baixo=0
*/

  uint8_t aU8_Acao2DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao2LigaDelay[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao2LigaDelayTempo[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao3UP[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao3DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao3TempoUP[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
  uint16_t aU16_Acao3TempoDOWN[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao4DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao4Pulso[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao4PulsoTempo[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao5UP[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao5DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao5PulsoDelayTempoUP[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
  uint16_t aU16_Acao5PulsoDelayTempoDOWN[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t idz=0;
  for (;;){
        switch (aU16_Acao2[2][idz]) {
      case 1: //LIGA
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if (aU8_Pinos[4][idz]) {
            f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU16_Acao2[9][idz]);
          } else {
            f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[9][idz]);
            //aU8_ControlMsgTelegram[1][idz] = 0;
          }
        }
        break;
      case 2: //LIGA DELAY
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao2LigaDelay[0][idz]) {
                aU8_Acao2LigaDelay[0][idz] = 1;
                aU16_Acao2LigaDelayTempo[0][idz] = aU16_Acao2[3][idz];
              } else {
                if ( aU16_Acao2LigaDelayTempo[0][idz] > 0) {
                  aU16_Acao2LigaDelayTempo[0][idz]--;
                } else {
                  f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU16_Acao2[9][idz]);
                }
              }
          } else {
            if (aU8_Acao2LigaDelay[0][idz] || aU8_Acao2DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[9][idz]);
              aU8_Acao2LigaDelay[0][idz] = 0;
              aU8_Acao2DOWN[0][idz] = 0; 
              //aU8_ControlMsgTelegram[1][idz] = 0;                           
            }
          }
        }
        break;
      case 3: //PISCA
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao3UP[0][idz]) {
                aU8_Acao3UP[0][idz] = 1;
                aU8_Acao3DOWN[0][idz] = 0;
                aU16_Acao3TempoUP[0][idz] = aU16_Acao2[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU16_Acao2[9][idz]);
              } else {
                if ( aU16_Acao3TempoUP[0][idz] > 0) {
                  aU16_Acao3TempoUP[0][idz]--;
                } else {
                  if (!aU8_Acao3DOWN[0][idz]) {
                    aU8_Acao3DOWN[0][idz] = 1;
                    aU16_Acao3TempoDOWN[0][idz] = aU16_Acao2[4][idz];
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[9][idz]);
                  } else {
                    if ( aU16_Acao3TempoDOWN[0][idz] > 0) {
                      aU16_Acao3TempoDOWN[0][idz]--;
                    } else {
                      aU8_Acao3UP[0][idz] = 0;
                    }
                  }
                }
              }
          } else {
            if (aU8_Acao3UP[0][idz] || aU8_Acao3DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[9][idz]);
              aU8_Acao3UP[0][idz] = 0;
              aU8_Acao3DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[1][idz] = 0;                            
            }
          }
        }
        break;
      case 4: //PULSO
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao4Pulso[0][idz]) {
                aU8_Acao4Pulso[0][idz] = 1;
                aU16_Acao4PulsoTempo[0][idz] = aU16_Acao2[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU16_Acao2[9][idz]);
              } else {
                if ( aU16_Acao4PulsoTempo[0][idz] > 0) {
                  aU16_Acao4PulsoTempo[0][idz]--;
                } else {
                  f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[9][idz]);
                }
              }
          } else {
            if (aU8_Acao4Pulso[0][idz] || aU8_Acao4DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[9][idz]);
              aU8_Acao4Pulso[0][idz] = 0;
              aU8_Acao4DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[1][idz] = 0;                            
            }
          }
        }
        break;
      case 5: //PULSO DELAY ON
        if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao5UP[0][idz]) {
                aU8_Acao5UP[0][idz] = 1;
                aU16_Acao5PulsoDelayTempoUP[0][idz] = aU16_Acao2[3][idz];
              } else {
                if ( aU16_Acao5PulsoDelayTempoUP[0][idz] > 0) {
                  aU16_Acao5PulsoDelayTempoUP[0][idz]--;
                } else {
                  if (aU8_Acao5UP[0][idz] && !aU8_Acao5DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],aU16_Acao2[9][idz]);
                    aU16_Acao5PulsoDelayTempoDOWN[0][idz] = aU16_Acao2[4][idz];
                    aU8_Acao5DOWN[0][idz] = 1;
                  } else {
                    if (aU16_Acao5PulsoDelayTempoDOWN[0][idz] > 0) {
                      aU16_Acao5PulsoDelayTempoDOWN[0][idz]--;
                    } else {
                      f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[9][idz]);
                    }
                  }
                }
              }
          } else {
            if (aU8_Acao5UP[0][idz] ) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao2[1][idz],!aU16_Acao2[1][idz]);
              aU8_Acao5UP[0][idz] = 0;
              aU8_Acao5DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[1][idz] = 0;
            }
          }
        }
        break;        
    }
    idz++;
    if (idz >= vU8_totPinos){
      idz=0;
    }
    vTaskDelay(8/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoesPg3Pinos(void *pvParameters) {
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
aU16_Acao[9][x] = Acionamento Alto=1 / Baixo=0
*/

  uint8_t aU8_Acao2DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao2LigaDelay[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao2LigaDelayTempo[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao3UP[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao3DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao3TempoUP[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
  uint16_t aU16_Acao3TempoDOWN[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao4DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao4Pulso[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao4PulsoTempo[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t aU8_Acao5UP[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint8_t aU8_Acao5DOWN[1][vU8_totPinos]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  uint16_t aU16_Acao5PulsoDelayTempoUP[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
  uint16_t aU16_Acao5PulsoDelayTempoDOWN[1][vU8_totPinos]= {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  uint8_t idz=0;
  for (;;){
        switch (aU16_Acao3[2][idz]) {
      case 1: //LIGA
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if (aU8_Pinos[4][idz]) {
            f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU16_Acao3[9][idz]);
          } else {
            f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[9][idz]);
            //aU8_ControlMsgTelegram[2][idz] = 0;
          }
        }
        break;
      case 2: //LIGA DELAY
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao2LigaDelay[0][idz]) {
                aU8_Acao2LigaDelay[0][idz] = 1;
                aU16_Acao2LigaDelayTempo[0][idz] = aU16_Acao3[3][idz];
              } else {
                if ( aU16_Acao2LigaDelayTempo[0][idz] > 0) {
                  aU16_Acao2LigaDelayTempo[0][idz]--;
                } else {
                  f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU16_Acao3[9][idz]);
                }
              }
          } else {
            if (aU8_Acao2LigaDelay[0][idz] || aU8_Acao2DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[9][idz]);
              aU8_Acao2LigaDelay[0][idz] = 0;
              aU8_Acao2DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[2][idz] = 0;                            
            }
          }
        }
        break;
      case 3: //PISCA
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao3UP[0][idz]) {
                aU8_Acao3UP[0][idz] = 1;
                aU8_Acao3DOWN[0][idz] = 0;
                aU16_Acao3TempoUP[0][idz] = aU16_Acao3[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU16_Acao3[9][idz]);
              } else {
                if ( aU16_Acao3TempoUP[0][idz] > 0) {
                  aU16_Acao3TempoUP[0][idz]--;
                } else {
                  if (!aU8_Acao3DOWN[0][idz]) {
                    aU8_Acao3DOWN[0][idz] = 1;
                    aU16_Acao3TempoDOWN[0][idz] = aU16_Acao3[4][idz];
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[9][idz]);
                  } else {
                    if ( aU16_Acao3TempoDOWN[0][idz] > 0) {
                      aU16_Acao3TempoDOWN[0][idz]--;
                    } else {
                      aU8_Acao3UP[0][idz] = 0;
                    }
                  }
                }
              }
          } else {
            if (aU8_Acao3UP[0][idz] || aU8_Acao3DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[9][idz]);
              aU8_Acao3UP[0][idz] = 0;
              aU8_Acao3DOWN[0][idz] = 0; 
              //aU8_ControlMsgTelegram[2][idz] = 0;                           
            }
          }
        }
        break;
      case 4: //PULSO
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao4Pulso[0][idz]) {
                aU8_Acao4Pulso[0][idz] = 1;
                aU16_Acao4PulsoTempo[0][idz] = aU16_Acao3[3][idz];
                f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU16_Acao3[9][idz]);
              } else {
                if ( aU16_Acao4PulsoTempo[0][idz] > 0) {
                  aU16_Acao4PulsoTempo[0][idz]--;
                } else {
                  f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[9][idz]);
                }
              }
          } else {
            if (aU8_Acao4Pulso[0][idz] || aU8_Acao4DOWN[0][idz]) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[9][idz]);
              aU8_Acao4Pulso[0][idz] = 0;
              aU8_Acao4DOWN[0][idz] = 0; 
              //aU8_ControlMsgTelegram[2][idz] = 0;                           
            }
          }
        }
        break;
      case 5: //PULSO DELAY ON
        if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
          if ( aU8_Pinos[4][idz] ) {
              if (!aU8_Acao5UP[0][idz]) {
                aU8_Acao5UP[0][idz] = 1;
                aU16_Acao5PulsoDelayTempoUP[0][idz] = aU16_Acao3[3][idz];
              } else {
                if ( aU16_Acao5PulsoDelayTempoUP[0][idz] > 0) {
                  aU16_Acao5PulsoDelayTempoUP[0][idz]--;
                } else {
                  if (aU8_Acao5UP[0][idz] && !aU8_Acao5DOWN[0][idz]) {
                    f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],aU16_Acao3[9][idz]);
                    aU16_Acao5PulsoDelayTempoDOWN[0][idz] = aU16_Acao3[4][idz];
                    aU8_Acao5DOWN[0][idz] = 1;
                  } else {
                    if (aU16_Acao5PulsoDelayTempoDOWN[0][idz] > 0) {
                      aU16_Acao5PulsoDelayTempoDOWN[0][idz]--;
                    } else {
                      f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[9][idz]);
                    }
                  }
                }
              }
          } else {
            if (aU8_Acao5UP[0][idz] ) {
              f_gravaPino(aU8_Pinos[1][idz],aU16_Acao3[1][idz],!aU16_Acao3[1][idz]);
              aU8_Acao5UP[0][idz] = 0;
              aU8_Acao5DOWN[0][idz] = 0;
              //aU8_ControlMsgTelegram[2][idz] = 0;
            }
          }
        }
        break;        
    }
    idz++;
    if (idz >= vU8_totPinos){
      idz=0;
    }
    vTaskDelay(8/portTICK_PERIOD_MS);
  }
}