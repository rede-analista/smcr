# Configurações Gerais

- Nas configurações gerais devem ser cadastradas informações diversas para comportamento da interface web, watchdog, refresh, etc.<br>

- Na página inicial clique em "Configurarões Gerais" e depois em "Configuração Geral".<br>
![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/c_geral_t1.png)


- Parâmetro  Status na Página Inicial
  - Habilita/desabilita as informações de status dos pinos na página inicial.

- Parâmetro  Inter Módulos na Página Inicial
  - Habilita/desabilita as informações de comunicação de intermódulos na página inicial.

- Parâmetro  Cor Status Com Alerta
  - Informe a cor do status quando tiver um alerta. Deve usar nome de cor no padrão HTML.

- Parâmetro  Cor Status Sem Alerta
  - Informe a cor do status quando não tiver um alerta. Deve usar nome de cor no padrão HTML.

- Parâmetro  Tempo de Refresh
  - Informe o tempo de refresh em segundos. Tempo de refres da página inicial.

- Parâmetro  Executar WatchDog
  - Habilita/desabilita execução do watchdog. deve ser configurados os demais parâmetros antes de habilitar.

- Parâmetro  Clock do ESP32
  - Informe a velocidade em Megahertz do clock do ESP32. Esta informação é usada no watchdog.

- Parâmetro  Tempo para wathDog 
  - Informe o tempo de reset do watchdog em microsegundos. Esta informação é usada decisão de reboot do esp em caso de falha/travamento.

- Parâmetro  Quantidade Total de Pinos
  - Informe a quantidade total de pinos que será usado. Você pode configurar uma quantidade adequada a sua necessidade respeitando o máximo de 254 pinos. Uma quantidade maior irá consumir mais processamento do ESP32.

  NOTA 1: A quantidade de pinos irá influênciar na velocidade das rotinas que são executadas pelo módulo. Uma quantidade grande de pinos deixará o tempo das rotinas mais demorado.

  NOTA2: Esta informação deve ser alterada antes de realizar cadastro de pinos e ações. A alteração desta informação depois que o módulo já estiver configurado e em uso pode ocasionar travamentos.

  NOTA 3: Para o funcionamento correto o ideal é realizar a formatação da flash (apagar todas as configurações) antes de alterar a quantidade de pinos. Após alterar a quantidade de pinos o módulo deve ser reconfigurado.

  # Não esqueça de salvar as informações antes de reiniciar/desligar o módulo.
## Se o módulor for reiniciado antes de salvar as informações na flash as configurações realizadas serão perdidas.

- Se quiser salvar as informações na memória flash do ESP32, Vá para tela inicial clique em "Gerenciar Arquivos", despois clique em "Salvar Configurações".<br>
  Responda "Sim" à pergunta e clique em "Confirmar".<br>

![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/t_salvar_t1.png)

![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/t_salvar_t2.png)

![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/t_salvar_t3.png)