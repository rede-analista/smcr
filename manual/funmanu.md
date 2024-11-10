# Reiniciar Módulo

- Esta opção reboot o módulo ESP32.
  NOTA 1: As configurações que não estiverem salvas na memória flash do ESP serão perdidas.<br>
  Na página inicial clique em "Reiniciar Módulo", responda a pergunta com "Sim" em clique em Reboot<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/687ce7b6-f46c-4728-b288-20348d1df124)


# Limpeza da Flash

- Esta opção apaga configurações que já estão salvas na memória flash do módulo ESP32.
  
  Na página inicial clique em "Limpar Flash", responda a pergunta com a opção que lhe atenda em clique em "!!EXECUTAR!!"<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/1e2164c8-8969-4179-b022-38e492a1e3c3)


  - Você pode escolher qual conteúdo será apagado da memória flash.
    1. "Acoes" = Apagar configurações das ações.
    2. "ExcetoWifi" = Apagar todas as configurações esceto informações do wifi.
    3. "Tudo" = Apagar todas as informações inclusive do wifi.
    4. "Formatar" = Além de apagar todas as informações(inclusive wifi) tambem formata a memória flash(NVR).


# Recarregar Funções

 - Esta opção executa as funções que são executadas somente durante o setup() do ESP32.
   Pode ser usada para aplicar as configurações gerais e testar o funcionamento antes de salvar na flash.
   ![image](https://github.com/rede-analista/smcr/assets/66534023/55d07ec3-88a2-40aa-abf5-41ddfbb9f115)
<br>
NOTA 2: Ao configurar mais de uma ação para um mesmo pino destino a função GACOES deve ser executada.<br>

