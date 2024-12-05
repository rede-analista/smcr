#include "include.h"
#include "globals.h"

//========================================
void TaskLeituraPinos(void *pvParameters) {
    // Declaração de arrays com tipos específicos como você especificou
    uint16_t** aU8_IgnoraPino = nullptr;  

    // Alocação dinâmica de memória para cada array com 1 linha e vU8_totPinos colunas
    aU8_IgnoraPino = new uint16_t*[1];

    // Inicializa a única linha e preenche com zeros para cada array
    aU8_IgnoraPino[0] = new uint16_t[vU8_totPinos]();

    uint8_t idx=0;
    for (;;){
      if (aB_restartRotinas[0]) {
            // Reinicializa todos os arrays para zero
            for (size_t j = 0; j < vU8_totPinos; j++) {
                aU8_IgnoraPino[0][j] = 0;
            }
        idx=0;
        aB_restartRotinas[0] = 0;
      }
      if (!vB_pausaEXECs) {
        if (aU16_Pinos[1][idx] != 65535) {
          if (aU16_Pinos[0][idx] > 0) { 
            if ( aU8_IgnoraPino[0][idx] == 0) {
              aU16_Pinos_Status[0][idx] = fU16_lePino(aU16_Pinos[1][idx],aU16_Pinos[3][idx],aU16_Pinos[0][idx]);
            }
            if ( aU16_Pinos[5][idx] > 0 && aU16_Pinos_Status[0][idx] ) {
                if (aU8_IgnoraPino[0][idx] == 0) {
                  aU8_IgnoraPino[0][idx] = aU16_Pinos[5][idx];
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
      }
      vTaskDelay(20/portTICK_PERIOD_MS);
    }
}

//========================================
void TaskAcoes1Pinos(void *pvParameters) {
    // Declaração de arrays com tipos específicos como você especificou
    uint16_t** aU8_AcaoTP1 = nullptr;
    uint16_t** aU8_AcaoTP2DOWN = nullptr;
    uint16_t** aU8_AcaoTP2LigaDelay = nullptr;
    uint16_t** aU16_AcaoTP2LigaDelayTempo = nullptr;
    uint8_t** aU8_AcaoTP3UP = nullptr;
    uint8_t** aU8_AcaoTP3DOWN = nullptr;
    uint16_t** aU16_AcaoTP3TempoUP = nullptr;
    uint16_t** aU16_AcaoTP3TempoDOWN = nullptr;
    uint16_t** aU8_AcaoTP4DOWN = nullptr;
    uint16_t** aU8_AcaoTP4Pulso = nullptr;
    uint16_t** aU16_AcaoTP4PulsoTempo = nullptr;
    uint16_t** aU8_AcaoTP5UP = nullptr;
    uint16_t** aU8_AcaoTP5DOWN = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoUP = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoDOWN = nullptr;

    // Alocação dinâmica de memória para cada array com 1 linha e vU8_totPinos colunas
    aU8_AcaoTP1 = new uint16_t*[1];
    aU8_AcaoTP2DOWN = new uint16_t*[1];
    aU8_AcaoTP2LigaDelay = new uint16_t*[1];
    aU16_AcaoTP2LigaDelayTempo = new uint16_t*[1];
    aU8_AcaoTP3UP = new uint8_t*[1];
    aU8_AcaoTP3DOWN = new uint8_t*[1];
    aU16_AcaoTP3TempoUP = new uint16_t*[1];
    aU16_AcaoTP3TempoDOWN = new uint16_t*[1];
    aU8_AcaoTP4DOWN = new uint16_t*[1];
    aU8_AcaoTP4Pulso = new uint16_t*[1];
    aU16_AcaoTP4PulsoTempo = new uint16_t*[1];
    aU8_AcaoTP5UP = new uint16_t*[1];
    aU8_AcaoTP5DOWN = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoUP = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoDOWN = new uint16_t*[1];

    // Inicializa a única linha e preenche com zeros para cada array
    aU8_AcaoTP1[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2LigaDelay[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP2LigaDelayTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP3UP[0] = new uint8_t[vU8_totPinos]();
    aU8_AcaoTP3DOWN[0] = new uint8_t[vU8_totPinos]();
    aU16_AcaoTP3TempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP3TempoDOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4Pulso[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP4PulsoTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5UP[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5DOWN[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoDOWN[0] = new uint16_t[vU8_totPinos]();

    // Loop infinito da task
    uint8_t idz = 0;
    for (;;) {
        if (aB_restartRotinas[1]) {
            // Reinicializa todos os arrays para zero
            for (size_t j = 0; j < vU8_totPinos; j++) {
                aU8_AcaoTP1[0][j] = 0;
                aU8_AcaoTP2DOWN[0][j] = 0;
                aU8_AcaoTP2LigaDelay[0][j] = 0;
                aU16_AcaoTP2LigaDelayTempo[0][j] = 0;
                aU8_AcaoTP3UP[0][j] = 0;
                aU8_AcaoTP3DOWN[0][j] = 0;
                aU16_AcaoTP3TempoUP[0][j] = 0;
                aU16_AcaoTP3TempoDOWN[0][j] = 0;
                aU8_AcaoTP4DOWN[0][j] = 0;
                aU8_AcaoTP4Pulso[0][j] = 0;
                aU16_AcaoTP4PulsoTempo[0][j] = 0;
                aU8_AcaoTP5UP[0][j] = 0;
                aU8_AcaoTP5DOWN[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoUP[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoDOWN[0][j] = 0;
            }
            idz = 0;
            aB_restartRotinas[1] = 0;
        }
    if (!vB_pausaEXECs) {
      switch (aU16_Acao1[2][idz]) {
        case 1: //LIGA
          if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
            if (aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz]) {
              if (!aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao1[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao1[1][idz]),aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                }
                aU8_AcaoTP1[0][idz] = 1;
              }
            } else {
              if (aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao1[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao1[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);

                }
                aU8_AcaoTP1[0][idz] = 0;
              }
            }
          }
          break;
        case 2: //LIGA DELAY
          if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP2LigaDelay[0][idz]) {
                  aU8_AcaoTP2LigaDelay[0][idz] = 1;
                  aU16_AcaoTP2LigaDelayTempo[0][idz] = aU16_Acao1[3][idz];
                } else {
                  if ( aU16_AcaoTP2LigaDelayTempo[0][idz] > 0) {
                    aU16_AcaoTP2LigaDelayTempo[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP2DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                      aU8_AcaoTP2DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP2LigaDelay[0][idz] || aU8_AcaoTP2DOWN[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao1[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao1[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                }
                aU8_AcaoTP2LigaDelay[0][idz] = 0;
                aU8_AcaoTP2DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 3: //PISCA
          if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP3UP[0][idz]) {
                  aU8_AcaoTP3UP[0][idz] = 1;
                  aU8_AcaoTP3DOWN[0][idz] = 0;
                  aU16_AcaoTP3TempoUP[0][idz] = aU16_Acao1[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                } else {
                  if ( aU16_AcaoTP3TempoUP[0][idz] > 0) {
                    aU16_AcaoTP3TempoUP[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP3DOWN[0][idz]) {
                      aU8_AcaoTP3DOWN[0][idz] = 1;
                      aU16_AcaoTP3TempoDOWN[0][idz] = aU16_Acao1[4][idz];
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
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
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                aU8_AcaoTP3UP[0][idz] = 0;
                aU8_AcaoTP3DOWN[0][idz] = 0;   
              }
            }
          }
          break;
        case 4: //PULSO
          if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP4Pulso[0][idz]) {
                  aU8_AcaoTP4Pulso[0][idz] = 1;
                  aU16_AcaoTP4PulsoTempo[0][idz] = aU16_Acao1[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                } else {
                  if (!aU8_AcaoTP4DOWN[0][idz]) {
                    if ( aU16_AcaoTP4PulsoTempo[0][idz] > 0) {
                      aU16_AcaoTP4PulsoTempo[0][idz]--;
                    } else {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                      aU8_AcaoTP4DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP4Pulso[0][idz] || aU8_AcaoTP4DOWN[0][idz]) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                aU8_AcaoTP4Pulso[0][idz] = 0;
                aU8_AcaoTP4DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 5: //PULSO DELAY ON
          if (aU16_Acao1[0][idz] > 0 && aU16_Acao1[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP5UP[0][idz]) {
                  aU8_AcaoTP5UP[0][idz] = 1;
                  aU16_AcaoTP5PulsoDelayTempoUP[0][idz] = aU16_Acao1[3][idz];
                } else {
                  if ( aU16_AcaoTP5PulsoDelayTempoUP[0][idz] > 0) {
                    aU16_AcaoTP5PulsoDelayTempoUP[0][idz]--;
                  } else {
                    if (aU8_AcaoTP5UP[0][idz] && !aU8_AcaoTP5DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                      aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] = aU16_Acao1[4][idz];
                      aU8_AcaoTP5DOWN[0][idz] = 1;
                    } else {
                      if (aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] > 0) {
                        aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz]--;
                      } else {
                        if (!aU8_AcaoTP5DOWN[1][idz]) {
                          fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                          aU8_AcaoTP5DOWN[1][idz] = 1;
                        }
                      }
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP5UP[0][idz] ) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao1[1][idz])],aU16_Acao1[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao1[1][idz])]);
                aU8_AcaoTP5UP[0][idz] = 0;
                aU8_AcaoTP5DOWN[0][idz] = 0;
                aU8_AcaoTP5DOWN[1][idz] = 0;
              }
            }
          }
          break;
      }
      idz++;
      if (idz >= vU8_totPinos){
        idz=0;
      }
    }
    vTaskDelay(11/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoes2Pinos(void *pvParameters) {
    // Declaração de arrays com tipos específicos como você especificou
    uint16_t** aU8_AcaoTP1 = nullptr;
    uint16_t** aU8_AcaoTP2DOWN = nullptr;
    uint16_t** aU8_AcaoTP2LigaDelay = nullptr;
    uint16_t** aU16_AcaoTP2LigaDelayTempo = nullptr;
    uint8_t** aU8_AcaoTP3UP = nullptr;
    uint8_t** aU8_AcaoTP3DOWN = nullptr;
    uint16_t** aU16_AcaoTP3TempoUP = nullptr;
    uint16_t** aU16_AcaoTP3TempoDOWN = nullptr;
    uint16_t** aU8_AcaoTP4DOWN = nullptr;
    uint16_t** aU8_AcaoTP4Pulso = nullptr;
    uint16_t** aU16_AcaoTP4PulsoTempo = nullptr;
    uint16_t** aU8_AcaoTP5UP = nullptr;
    uint16_t** aU8_AcaoTP5DOWN = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoUP = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoDOWN = nullptr;

    // Alocação dinâmica de memória para cada array com 1 linha e vU8_totPinos colunas
    aU8_AcaoTP1 = new uint16_t*[1];
    aU8_AcaoTP2DOWN = new uint16_t*[1];
    aU8_AcaoTP2LigaDelay = new uint16_t*[1];
    aU16_AcaoTP2LigaDelayTempo = new uint16_t*[1];
    aU8_AcaoTP3UP = new uint8_t*[1];
    aU8_AcaoTP3DOWN = new uint8_t*[1];
    aU16_AcaoTP3TempoUP = new uint16_t*[1];
    aU16_AcaoTP3TempoDOWN = new uint16_t*[1];
    aU8_AcaoTP4DOWN = new uint16_t*[1];
    aU8_AcaoTP4Pulso = new uint16_t*[1];
    aU16_AcaoTP4PulsoTempo = new uint16_t*[1];
    aU8_AcaoTP5UP = new uint16_t*[1];
    aU8_AcaoTP5DOWN = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoUP = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoDOWN = new uint16_t*[1];

    // Inicializa a única linha e preenche com zeros para cada array
    aU8_AcaoTP1[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2LigaDelay[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP2LigaDelayTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP3UP[0] = new uint8_t[vU8_totPinos]();
    aU8_AcaoTP3DOWN[0] = new uint8_t[vU8_totPinos]();
    aU16_AcaoTP3TempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP3TempoDOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4Pulso[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP4PulsoTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5UP[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5DOWN[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoDOWN[0] = new uint16_t[vU8_totPinos]();

    // Loop infinito da task
    uint8_t idz = 0;
    for (;;) {
        if (aB_restartRotinas[1]) {
            // Reinicializa todos os arrays para zero
            for (size_t j = 0; j < vU8_totPinos; j++) {
                aU8_AcaoTP1[0][j] = 0;
                aU8_AcaoTP2DOWN[0][j] = 0;
                aU8_AcaoTP2LigaDelay[0][j] = 0;
                aU16_AcaoTP2LigaDelayTempo[0][j] = 0;
                aU8_AcaoTP3UP[0][j] = 0;
                aU8_AcaoTP3DOWN[0][j] = 0;
                aU16_AcaoTP3TempoUP[0][j] = 0;
                aU16_AcaoTP3TempoDOWN[0][j] = 0;
                aU8_AcaoTP4DOWN[0][j] = 0;
                aU8_AcaoTP4Pulso[0][j] = 0;
                aU16_AcaoTP4PulsoTempo[0][j] = 0;
                aU8_AcaoTP5UP[0][j] = 0;
                aU8_AcaoTP5DOWN[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoUP[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoDOWN[0][j] = 0;
            }
            idz = 0;
            aB_restartRotinas[1] = 0;
        }
    if (!vB_pausaEXECs) {
      switch (aU16_Acao2[2][idz]) {
        case 1: //LIGA
          if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
            if (aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz]) {
              if (!aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao2[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao2[1][idz]),aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                }
                aU8_AcaoTP1[0][idz] = 1;
              }
            } else {
              if (aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao2[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao2[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);

                }
                aU8_AcaoTP1[0][idz] = 0;
              }
            }
          }
          break;
        case 2: //LIGA DELAY
          if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP2LigaDelay[0][idz]) {
                  aU8_AcaoTP2LigaDelay[0][idz] = 1;
                  aU16_AcaoTP2LigaDelayTempo[0][idz] = aU16_Acao2[3][idz];
                } else {
                  if ( aU16_AcaoTP2LigaDelayTempo[0][idz] > 0) {
                    aU16_AcaoTP2LigaDelayTempo[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP2DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                      aU8_AcaoTP2DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP2LigaDelay[0][idz] || aU8_AcaoTP2DOWN[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao2[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao2[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                }
                aU8_AcaoTP2LigaDelay[0][idz] = 0;
                aU8_AcaoTP2DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 3: //PISCA
          if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP3UP[0][idz]) {
                  aU8_AcaoTP3UP[0][idz] = 1;
                  aU8_AcaoTP3DOWN[0][idz] = 0;
                  aU16_AcaoTP3TempoUP[0][idz] = aU16_Acao2[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                } else {
                  if ( aU16_AcaoTP3TempoUP[0][idz] > 0) {
                    aU16_AcaoTP3TempoUP[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP3DOWN[0][idz]) {
                      aU8_AcaoTP3DOWN[0][idz] = 1;
                      aU16_AcaoTP3TempoDOWN[0][idz] = aU16_Acao2[4][idz];
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
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
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                aU8_AcaoTP3UP[0][idz] = 0;
                aU8_AcaoTP3DOWN[0][idz] = 0;   
              }
            }
          }
          break;
        case 4: //PULSO
          if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP4Pulso[0][idz]) {
                  aU8_AcaoTP4Pulso[0][idz] = 1;
                  aU16_AcaoTP4PulsoTempo[0][idz] = aU16_Acao2[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                } else {
                  if (!aU8_AcaoTP4DOWN[0][idz]) {
                    if ( aU16_AcaoTP4PulsoTempo[0][idz] > 0) {
                      aU16_AcaoTP4PulsoTempo[0][idz]--;
                    } else {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                      aU8_AcaoTP4DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP4Pulso[0][idz] || aU8_AcaoTP4DOWN[0][idz]) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                aU8_AcaoTP4Pulso[0][idz] = 0;
                aU8_AcaoTP4DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 5: //PULSO DELAY ON
          if (aU16_Acao2[0][idz] > 0 && aU16_Acao2[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP5UP[0][idz]) {
                  aU8_AcaoTP5UP[0][idz] = 1;
                  aU16_AcaoTP5PulsoDelayTempoUP[0][idz] = aU16_Acao2[3][idz];
                } else {
                  if ( aU16_AcaoTP5PulsoDelayTempoUP[0][idz] > 0) {
                    aU16_AcaoTP5PulsoDelayTempoUP[0][idz]--;
                  } else {
                    if (aU8_AcaoTP5UP[0][idz] && !aU8_AcaoTP5DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                      aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] = aU16_Acao2[4][idz];
                      aU8_AcaoTP5DOWN[0][idz] = 1;
                    } else {
                      if (aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] > 0) {
                        aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz]--;
                      } else {
                        if (!aU8_AcaoTP5DOWN[1][idz]) {
                          fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                          aU8_AcaoTP5DOWN[1][idz] = 1;
                        }
                      }
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP5UP[0][idz] ) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao2[1][idz])],aU16_Acao2[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao2[1][idz])]);
                aU8_AcaoTP5UP[0][idz] = 0;
                aU8_AcaoTP5DOWN[0][idz] = 0;
                aU8_AcaoTP5DOWN[1][idz] = 0;
              }
            }
          }
          break;
      }
      idz++;
      if (idz >= vU8_totPinos){
        idz=0;
      }
    }
    vTaskDelay(11/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoes3Pinos(void *pvParameters) {
    // Declaração de arrays com tipos específicos como você especificou
    uint16_t** aU8_AcaoTP1 = nullptr;
    uint16_t** aU8_AcaoTP2DOWN = nullptr;
    uint16_t** aU8_AcaoTP2LigaDelay = nullptr;
    uint16_t** aU16_AcaoTP2LigaDelayTempo = nullptr;
    uint8_t** aU8_AcaoTP3UP = nullptr;
    uint8_t** aU8_AcaoTP3DOWN = nullptr;
    uint16_t** aU16_AcaoTP3TempoUP = nullptr;
    uint16_t** aU16_AcaoTP3TempoDOWN = nullptr;
    uint16_t** aU8_AcaoTP4DOWN = nullptr;
    uint16_t** aU8_AcaoTP4Pulso = nullptr;
    uint16_t** aU16_AcaoTP4PulsoTempo = nullptr;
    uint16_t** aU8_AcaoTP5UP = nullptr;
    uint16_t** aU8_AcaoTP5DOWN = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoUP = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoDOWN = nullptr;

    // Alocação dinâmica de memória para cada array com 1 linha e vU8_totPinos colunas
    aU8_AcaoTP1 = new uint16_t*[1];
    aU8_AcaoTP2DOWN = new uint16_t*[1];
    aU8_AcaoTP2LigaDelay = new uint16_t*[1];
    aU16_AcaoTP2LigaDelayTempo = new uint16_t*[1];
    aU8_AcaoTP3UP = new uint8_t*[1];
    aU8_AcaoTP3DOWN = new uint8_t*[1];
    aU16_AcaoTP3TempoUP = new uint16_t*[1];
    aU16_AcaoTP3TempoDOWN = new uint16_t*[1];
    aU8_AcaoTP4DOWN = new uint16_t*[1];
    aU8_AcaoTP4Pulso = new uint16_t*[1];
    aU16_AcaoTP4PulsoTempo = new uint16_t*[1];
    aU8_AcaoTP5UP = new uint16_t*[1];
    aU8_AcaoTP5DOWN = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoUP = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoDOWN = new uint16_t*[1];

    // Inicializa a única linha e preenche com zeros para cada array
    aU8_AcaoTP1[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2LigaDelay[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP2LigaDelayTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP3UP[0] = new uint8_t[vU8_totPinos]();
    aU8_AcaoTP3DOWN[0] = new uint8_t[vU8_totPinos]();
    aU16_AcaoTP3TempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP3TempoDOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4Pulso[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP4PulsoTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5UP[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5DOWN[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoDOWN[0] = new uint16_t[vU8_totPinos]();

    // Loop infinito da task
    uint8_t idz = 0;
    for (;;) {
        if (aB_restartRotinas[1]) {
            // Reinicializa todos os arrays para zero
            for (size_t j = 0; j < vU8_totPinos; j++) {
                aU8_AcaoTP1[0][j] = 0;
                aU8_AcaoTP2DOWN[0][j] = 0;
                aU8_AcaoTP2LigaDelay[0][j] = 0;
                aU16_AcaoTP2LigaDelayTempo[0][j] = 0;
                aU8_AcaoTP3UP[0][j] = 0;
                aU8_AcaoTP3DOWN[0][j] = 0;
                aU16_AcaoTP3TempoUP[0][j] = 0;
                aU16_AcaoTP3TempoDOWN[0][j] = 0;
                aU8_AcaoTP4DOWN[0][j] = 0;
                aU8_AcaoTP4Pulso[0][j] = 0;
                aU16_AcaoTP4PulsoTempo[0][j] = 0;
                aU8_AcaoTP5UP[0][j] = 0;
                aU8_AcaoTP5DOWN[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoUP[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoDOWN[0][j] = 0;
            }
            idz = 0;
            aB_restartRotinas[1] = 0;
        }
    if (!vB_pausaEXECs) {
      switch (aU16_Acao3[2][idz]) {
        case 1: //LIGA
          if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
            if (aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz]) {
              if (!aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao3[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao3[1][idz]),aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                }
                aU8_AcaoTP1[0][idz] = 1;
              }
            } else {
              if (aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao3[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao3[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);

                }
                aU8_AcaoTP1[0][idz] = 0;
              }
            }
          }
          break;
        case 2: //LIGA DELAY
          if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP2LigaDelay[0][idz]) {
                  aU8_AcaoTP2LigaDelay[0][idz] = 1;
                  aU16_AcaoTP2LigaDelayTempo[0][idz] = aU16_Acao3[3][idz];
                } else {
                  if ( aU16_AcaoTP2LigaDelayTempo[0][idz] > 0) {
                    aU16_AcaoTP2LigaDelayTempo[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP2DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                      aU8_AcaoTP2DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP2LigaDelay[0][idz] || aU8_AcaoTP2DOWN[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao3[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao3[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                }
                aU8_AcaoTP2LigaDelay[0][idz] = 0;
                aU8_AcaoTP2DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 3: //PISCA
          if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP3UP[0][idz]) {
                  aU8_AcaoTP3UP[0][idz] = 1;
                  aU8_AcaoTP3DOWN[0][idz] = 0;
                  aU16_AcaoTP3TempoUP[0][idz] = aU16_Acao3[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                } else {
                  if ( aU16_AcaoTP3TempoUP[0][idz] > 0) {
                    aU16_AcaoTP3TempoUP[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP3DOWN[0][idz]) {
                      aU8_AcaoTP3DOWN[0][idz] = 1;
                      aU16_AcaoTP3TempoDOWN[0][idz] = aU16_Acao3[4][idz];
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
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
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                aU8_AcaoTP3UP[0][idz] = 0;
                aU8_AcaoTP3DOWN[0][idz] = 0;   
              }
            }
          }
          break;
        case 4: //PULSO
          if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP4Pulso[0][idz]) {
                  aU8_AcaoTP4Pulso[0][idz] = 1;
                  aU16_AcaoTP4PulsoTempo[0][idz] = aU16_Acao3[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                } else {
                  if (!aU8_AcaoTP4DOWN[0][idz]) {
                    if ( aU16_AcaoTP4PulsoTempo[0][idz] > 0) {
                      aU16_AcaoTP4PulsoTempo[0][idz]--;
                    } else {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                      aU8_AcaoTP4DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP4Pulso[0][idz] || aU8_AcaoTP4DOWN[0][idz]) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                aU8_AcaoTP4Pulso[0][idz] = 0;
                aU8_AcaoTP4DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 5: //PULSO DELAY ON
          if (aU16_Acao3[0][idz] > 0 && aU16_Acao3[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP5UP[0][idz]) {
                  aU8_AcaoTP5UP[0][idz] = 1;
                  aU16_AcaoTP5PulsoDelayTempoUP[0][idz] = aU16_Acao3[3][idz];
                } else {
                  if ( aU16_AcaoTP5PulsoDelayTempoUP[0][idz] > 0) {
                    aU16_AcaoTP5PulsoDelayTempoUP[0][idz]--;
                  } else {
                    if (aU8_AcaoTP5UP[0][idz] && !aU8_AcaoTP5DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                      aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] = aU16_Acao3[4][idz];
                      aU8_AcaoTP5DOWN[0][idz] = 1;
                    } else {
                      if (aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] > 0) {
                        aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz]--;
                      } else {
                        if (!aU8_AcaoTP5DOWN[1][idz]) {
                          fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                          aU8_AcaoTP5DOWN[1][idz] = 1;
                        }
                      }
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP5UP[0][idz] ) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao3[1][idz])],aU16_Acao3[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao3[1][idz])]);
                aU8_AcaoTP5UP[0][idz] = 0;
                aU8_AcaoTP5DOWN[0][idz] = 0;
                aU8_AcaoTP5DOWN[1][idz] = 0;
              }
            }
          }
          break;
      }
      idz++;
      if (idz >= vU8_totPinos){
        idz=0;
      }
    }
    vTaskDelay(11/portTICK_PERIOD_MS);
  }
}

//========================================
void TaskAcoes4Pinos(void *pvParameters) {
    // Declaração de arrays com tipos específicos como você especificou
    uint16_t** aU8_AcaoTP1 = nullptr;
    uint16_t** aU8_AcaoTP2DOWN = nullptr;
    uint16_t** aU8_AcaoTP2LigaDelay = nullptr;
    uint16_t** aU16_AcaoTP2LigaDelayTempo = nullptr;
    uint8_t** aU8_AcaoTP3UP = nullptr;
    uint8_t** aU8_AcaoTP3DOWN = nullptr;
    uint16_t** aU16_AcaoTP3TempoUP = nullptr;
    uint16_t** aU16_AcaoTP3TempoDOWN = nullptr;
    uint16_t** aU8_AcaoTP4DOWN = nullptr;
    uint16_t** aU8_AcaoTP4Pulso = nullptr;
    uint16_t** aU16_AcaoTP4PulsoTempo = nullptr;
    uint16_t** aU8_AcaoTP5UP = nullptr;
    uint16_t** aU8_AcaoTP5DOWN = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoUP = nullptr;
    uint16_t** aU16_AcaoTP5PulsoDelayTempoDOWN = nullptr;

    // Alocação dinâmica de memória para cada array com 1 linha e vU8_totPinos colunas
    aU8_AcaoTP1 = new uint16_t*[1];
    aU8_AcaoTP2DOWN = new uint16_t*[1];
    aU8_AcaoTP2LigaDelay = new uint16_t*[1];
    aU16_AcaoTP2LigaDelayTempo = new uint16_t*[1];
    aU8_AcaoTP3UP = new uint8_t*[1];
    aU8_AcaoTP3DOWN = new uint8_t*[1];
    aU16_AcaoTP3TempoUP = new uint16_t*[1];
    aU16_AcaoTP3TempoDOWN = new uint16_t*[1];
    aU8_AcaoTP4DOWN = new uint16_t*[1];
    aU8_AcaoTP4Pulso = new uint16_t*[1];
    aU16_AcaoTP4PulsoTempo = new uint16_t*[1];
    aU8_AcaoTP5UP = new uint16_t*[1];
    aU8_AcaoTP5DOWN = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoUP = new uint16_t*[1];
    aU16_AcaoTP5PulsoDelayTempoDOWN = new uint16_t*[1];

    // Inicializa a única linha e preenche com zeros para cada array
    aU8_AcaoTP1[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP2LigaDelay[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP2LigaDelayTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP3UP[0] = new uint8_t[vU8_totPinos]();
    aU8_AcaoTP3DOWN[0] = new uint8_t[vU8_totPinos]();
    aU16_AcaoTP3TempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP3TempoDOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4DOWN[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP4Pulso[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP4PulsoTempo[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5UP[0] = new uint16_t[vU8_totPinos]();
    aU8_AcaoTP5DOWN[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoUP[0] = new uint16_t[vU8_totPinos]();
    aU16_AcaoTP5PulsoDelayTempoDOWN[0] = new uint16_t[vU8_totPinos]();

    // Loop infinito da task
    uint8_t idz = 0;
    for (;;) {
        if (aB_restartRotinas[1]) {
            // Reinicializa todos os arrays para zero
            for (size_t j = 0; j < vU8_totPinos; j++) {
                aU8_AcaoTP1[0][j] = 0;
                aU8_AcaoTP2DOWN[0][j] = 0;
                aU8_AcaoTP2LigaDelay[0][j] = 0;
                aU16_AcaoTP2LigaDelayTempo[0][j] = 0;
                aU8_AcaoTP3UP[0][j] = 0;
                aU8_AcaoTP3DOWN[0][j] = 0;
                aU16_AcaoTP3TempoUP[0][j] = 0;
                aU16_AcaoTP3TempoDOWN[0][j] = 0;
                aU8_AcaoTP4DOWN[0][j] = 0;
                aU8_AcaoTP4Pulso[0][j] = 0;
                aU16_AcaoTP4PulsoTempo[0][j] = 0;
                aU8_AcaoTP5UP[0][j] = 0;
                aU8_AcaoTP5DOWN[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoUP[0][j] = 0;
                aU16_AcaoTP5PulsoDelayTempoDOWN[0][j] = 0;
            }
            idz = 0;
            aB_restartRotinas[1] = 0;
        }
    if (!vB_pausaEXECs) {
      switch (aU16_Acao4[2][idz]) {
        case 1: //LIGA
          if (aU16_Acao4[0][idz] > 0 && aU16_Acao4[1][idz] > 0) {
            if (aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz]) {
              if (!aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao4[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao4[1][idz]),aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                }
                aU8_AcaoTP1[0][idz] = 1;
              }
            } else {
              if (aU8_AcaoTP1[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao4[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao4[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);

                }
                aU8_AcaoTP1[0][idz] = 0;
              }
            }
          }
          break;
        case 2: //LIGA DELAY
          if (aU16_Acao4[0][idz] > 0 && aU16_Acao4[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP2LigaDelay[0][idz]) {
                  aU8_AcaoTP2LigaDelay[0][idz] = 1;
                  aU16_AcaoTP2LigaDelayTempo[0][idz] = aU16_Acao4[3][idz];
                } else {
                  if ( aU16_AcaoTP2LigaDelayTempo[0][idz] > 0) {
                    aU16_AcaoTP2LigaDelayTempo[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP2DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                      aU8_AcaoTP2DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP2LigaDelay[0][idz] || aU8_AcaoTP2DOWN[0][idz]) {
                if (fS_retornaGrupoAcao(aU16_Acao4[1][idz]).length() < 1) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                } else if (fB_retornaStatusGrupoAcao(fS_retornaGrupoAcao(aU16_Acao4[1][idz]),!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])])) {
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                }
                aU8_AcaoTP2LigaDelay[0][idz] = 0;
                aU8_AcaoTP2DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 3: //PISCA
          if (aU16_Acao4[0][idz] > 0 && aU16_Acao4[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP3UP[0][idz]) {
                  aU8_AcaoTP3UP[0][idz] = 1;
                  aU8_AcaoTP3DOWN[0][idz] = 0;
                  aU16_AcaoTP3TempoUP[0][idz] = aU16_Acao4[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                } else {
                  if ( aU16_AcaoTP3TempoUP[0][idz] > 0) {
                    aU16_AcaoTP3TempoUP[0][idz]--;
                  } else {
                    if (!aU8_AcaoTP3DOWN[0][idz]) {
                      aU8_AcaoTP3DOWN[0][idz] = 1;
                      aU16_AcaoTP3TempoDOWN[0][idz] = aU16_Acao4[4][idz];
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
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
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                aU8_AcaoTP3UP[0][idz] = 0;
                aU8_AcaoTP3DOWN[0][idz] = 0;   
              }
            }
          }
          break;
        case 4: //PULSO
          if (aU16_Acao4[0][idz] > 0 && aU16_Acao4[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP4Pulso[0][idz]) {
                  aU8_AcaoTP4Pulso[0][idz] = 1;
                  aU16_AcaoTP4PulsoTempo[0][idz] = aU16_Acao4[3][idz];
                  fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                } else {
                  if (!aU8_AcaoTP4DOWN[0][idz]) {
                    if ( aU16_AcaoTP4PulsoTempo[0][idz] > 0) {
                      aU16_AcaoTP4PulsoTempo[0][idz]--;
                    } else {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                      aU8_AcaoTP4DOWN[0][idz] = 1;
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP4Pulso[0][idz] || aU8_AcaoTP4DOWN[0][idz]) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                aU8_AcaoTP4Pulso[0][idz] = 0;
                aU8_AcaoTP4DOWN[0][idz] = 0;
              }
            }
          }
          break;
        case 5: //PULSO DELAY ON
          if (aU16_Acao4[0][idz] > 0 && aU16_Acao4[1][idz] > 0) {
            if ( aU16_Pinos_Status[0][idz] >= aU16_Pinos[4][idz] ) {
                if (!aU8_AcaoTP5UP[0][idz]) {
                  aU8_AcaoTP5UP[0][idz] = 1;
                  aU16_AcaoTP5PulsoDelayTempoUP[0][idz] = aU16_Acao4[3][idz];
                } else {
                  if ( aU16_AcaoTP5PulsoDelayTempoUP[0][idz] > 0) {
                    aU16_AcaoTP5PulsoDelayTempoUP[0][idz]--;
                  } else {
                    if (aU8_AcaoTP5UP[0][idz] && !aU8_AcaoTP5DOWN[0][idz]) {
                      fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                      aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] = aU16_Acao4[4][idz];
                      aU8_AcaoTP5DOWN[0][idz] = 1;
                    } else {
                      if (aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz] > 0) {
                        aU16_AcaoTP5PulsoDelayTempoDOWN[0][idz]--;
                      } else {
                        if (!aU8_AcaoTP5DOWN[1][idz]) {
                          fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                          aU8_AcaoTP5DOWN[1][idz] = 1;
                        }
                      }
                    }
                  }
                }
            } else {
              if (aU8_AcaoTP5UP[0][idz] ) {
                fV_gravaPino(aU16_Pinos[1][fU16_retornaIndicePino(aU16_Acao4[1][idz])],aU16_Acao4[1][idz],!aU16_Pinos[4][fU16_retornaIndicePino(aU16_Acao4[1][idz])]);
                aU8_AcaoTP5UP[0][idz] = 0;
                aU8_AcaoTP5DOWN[0][idz] = 0;
                aU8_AcaoTP5DOWN[1][idz] = 0;
              }
            }
          }
          break;
      }
      idz++;
      if (idz >= vU8_totPinos){
        idz=0;
      }
    }
    vTaskDelay(11/portTICK_PERIOD_MS);
  }
}