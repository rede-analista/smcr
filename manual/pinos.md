# Configurações dos pinos

- Você deve configurar os pinos do módulo como entrara ou saída, para isto, na página inicial clique na opção "Configurar Pinos".<br>
![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/c_pinos_t0.png)


- Será aberta a página com as informações de todos os pinos. Nesta página pode chegar a 254 posições para configurações dos pinos, o cadastro de um pino pode ser realizada em qualquer posição.<br>
![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/c_pinos_t1.png)


O total de pinos pode ser ajustado no cadastro geral. Em testes realizados o valor máximo atingido com boa performance foi de 48 pinos.<br>


NOTA 1: Para não limitar a configuração dos pinos não há uma validação de quais pinos podem ser usados, consulte a informações de pinout do ESP32 para identificar pinos reservados e que não devem ser usados nas configurações nesta página.<br>

NOTA 2: Após configurar e clicar no botão "Aplicar (sem salvar)" as configurações já estarão sendo usadas pelo módulo mas **não estarão salvas na flash**. Isto pode ser usado para testar uma configuração sem alterar a configuração que está salva na flash.<br>

NOTA 3: Se o módulo for reiniciado antes de salvar as informações na flash todas as configurações serão perdidas.<br>

- Parâmetro NOME
  - É uma nomenclatura para facilitar na identificação dos pinos, um nome curto de 14 caracteres, este nome será usado na caso de notificações dos assistentes.

- Parâmetro PINO
  - É a informação do pino físico do ESP32, aqui será feito a associação do pino físico na placa ESP.<br>
    Esta informação será usada na configuração de Ações(eventos).<br>
    Pode ser um número que corresponde ao pino físico do ESP, por exemplo, este número pode ser 2,4,5,12,13,14,15,16,17,18,19,21,22,23,25,26,27,32,33,34,35,36,39 ou pode ser um número que não corresponda ao pino físico do ESP, por exemplo, ...251,253,65534<br>
    NOTA 4: Número de pinos que não são reconhecidos pelo ESP são chamados de pinos virtuais.<br>
    NOTA 5: O Pino 65535 é reservado para controle de status de comunicação entre módulos. [Veja CICLOS HANDSHAKE](intermod.md)

- Parâmetro TIPO
  - É o tipo do pino, esta informação pode ser 0=Sem Uso / 1=Digital / 192=Analógico / 65534=Remoto<br>
  
    - Se o valor 65534 for configurado significa que é um pino virtual(ver conceito). O módulo não irá realizar a atualização de status do pino, esta configuração pode ser usada quando for habilitado o recurso de "Inter Módulos".<br>

    - O recurso de Inter Módulos ativa a comunicação entre dois ou mais módulos ESP32 onde um módulo transmissor iŕa atualizar o status de um pino(físico ou virtual) no módulo receptor.<br>
    
    - O cadastro de um pino como tipo 65534 deve ser usado quando o módulo vai receber o status deste pino de forma remota, o status será recebido de outro módulo ESP para este módulo que terá o pino cadastrado como tipo 65534. Quando for cadastrar um pino como 65534 pode ser usado qualquer númeração de pino entre 1 e 65534 pois um pino do tipo 254 será considerado um pino virtual(não físico) e servirá apenas para disparar ações no módulo que recebe os dados de status de outros módulos. Este recurso pode ser usado para não inutilizar um pino físico em uma ação que não teŕa leitura de sensor localmente.

**Pino virtual (clique na seta abaixo para mais detalhes)**
<details>
<summary>- O conceito de pino virtual foi introduzido com a intenção de aumentar a quantidade de configurações possíveis e tambem evitar "gastar" o uso de um pino físico em configurações que o pino físico não seŕa útil.</summary>

- Considere um ambiente em que tem vários módulos com várias funções, neste tipo de ambiente facilmente voce pode se impedido de usar pinos iguais entre módulos devido a conflito de identificação de pinos, ou ainda ter poucos pinos disponíveis para realizar suas configurações.<br>

![image](https://github.com/rede-analista/smcr/assets/66534023/dad9435f-d5d1-4067-8ddc-a44d8a553e3c)

<br>
<br>
<br>
<br>
  - Imagine de voce possui um módulo que tem um botão e um buzzer como se fosse uma campainha no portão.<br>
  - Imagine que também possui um segundo módulo que fica dentro de casa para receber a informação que a campainha foi acionada.<br>
<br>
<br>
<br>
<br>
<br>
<br>
- Exemplo de funcionamento SEM USAR o recurso de pino virtual.<br>

![image](https://github.com/rede-analista/smcr/assets/66534023/03f72273-b3f5-430e-bd5b-9b980666265d)


<br>
<br>  
  - Veja que o pino de origem precisa se o mesmo nas duas placas. Considerando que uma placa esp possui em média 25 pinos GPIO, poderíamos ter no máximo 12 pinos de entrada e 12 pinos de saída póis para cada saída precisamos de uma entrada.<br>
    - Pino Origem == Pino de entrada == Pino de sensor (botão, reed switch, etc.).<br>
    - Pino Destino == Pino de saída == Pino de controle (buzzer, led, relé, etc.).<br>
  - Para acionar uma saída(pino destino) é preciso ter uma entrada(pino origem).<br>
  - Quando o botão for acionado, o transmissor vai enviar a informação que o pino 4 foi acionado para o receptor. O receptor recbe a informação do pino 4 acionado e também aciona o pino 23.<br>
  - Neste caso o pino 4 do módulo receptor NÃO PODERÁ mais ser usado para outra função mesmo que não tenha nehum sensor físico associado ao pino 4.<br>
  - Se quiser configurar um módulo como central onde não teŕa nenhum sensor conectado na central poderá ter apenas 12 pinos de saídas para indicar alertas pois outros 12 pinos serão usados como entrada.<br>
<br>
<br>
<br>
<br>
<br>
<br>
- Exemplo de funcionamento USANDO o recurso de pino virtual.<br>

![image](https://github.com/rede-analista/smcr/assets/66534023/b1ed2a10-05e4-434a-8ed4-cbd0044842a9)

 
  - Veja que o pino de origem precisa se o mesmo nas duas placas, porém, voce bão está usando um número de pino físico válido. Neste caso as 25 GPIO poderão ser usadas como saídas (destinos) para informar alertas.<br>
    - Pino Origem == Pino de entrada == Pino de sensor (botão, reed switch, etc.).<br>
    - Pino Destino == Pino de saída == Pino de controle (buzzer, led, relé, etc.).<br>
  - Para acionar uma saída(pino destino) é preciso ter uma entrada(pino origem).<br>
  - Quando o botão for acionado, o transmissor vai enviar a informação que o pino 200 foi acionado para o receptor. O receptor recbe a informação do pino 200 acionado e também aciona o pino 23.<br>
  - Neste caso o pino 4 do módulo receptor PODERÁ mais ser usado para outra função.<br>
  - Se quiser configurar um módulo como central onde não teŕa nenhum sensor conectado na central poderá ter 25 pinos de saídas para indicar alertas pois os pinos de entrada serão virtuais.<br>
<br>
<br>
<br>
<br>
<br>
<br>
- Exemplo de funcionamento USANDO o recurso de pino virtual com 2 módulos transmissores.<br>

![image](https://github.com/rede-analista/smcr/assets/66534023/17c1ca37-a390-4538-9917-cc247e9d641b)


  - Veja que o pino de origem precisa se o mesmo nas duas placas, porém, voce bão está usando um número de pino físico válido. Neste caso as 25 GPIO poderão ser usadas como saídas (destinos) para informar alertas.<br>
    - Pino Origem == Pino de entrada == Pino de sensor (botão, reed switch, etc.).<br>
    - Pino Destino == Pino de saída == Pino de controle (buzzer, led, relé, etc.).<br>
  - Para acionar uma saída(pino destino) é preciso ter uma entrada(pino origem).<br>
  - Note que não precisa haver relação entre os pinos das placas transmissores e receptoras. Precisa apenas ficar atento ao conflito de pinos em ums mesma placa.
<br>
<br>
<br>
<br>
<br>
<br>
</details>
    

- Parâmetro PINMODE()
  - É o modo que o pino será configurado na função pinMode(), esta informação pode ser INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=192<br>
    - Se o pino for do tipo 65534 este valor não será considerado, pode ser 0(zero).

- Parâmetro XOR
  - Indica se deve ser aplicado a operação XoR quando realizar a leitura do status do pino, esta informação pode ser 0=Valor igual a leitura do pino / 1=Valor inverso a leitura do pino<br>

- Parâmetro NÍVEL_ACIONAMENTO
  - Informa se a ação cadastrada para este pino será executada quando o pino estiver acima ou igual ao nível cadastrado. 0 a 4095.

- Parâmetro RETENÇÃO
  - Informa se após a leitura de status de um pino a task irá ignorar a leitura do pino nos próximos X ciclos mantendo a última leitura do pino, esta informação pode ser 0=Não / 1=Sim<br>

Parâmetro TEMPO RETENÇÃO
  - Informa quantos clicos a task deixará de ler o status de um pino se a opção RETENÇÃO estiver ativada.<br>
    O tempo de retenção não é contado em milisegundos mas sim em tempo de clico do processador, para mais detalhe do tempo de retenção veja "NOTA 5"<br>
    Esta informação pode ser de 1 a 255 ciclos.

[Exemplo Cadastro](excadpino.md)



##


## Tarefa de leitura do status dos pinos

- A leitura de status dos pinos é executada pela task "TaskLeituraPinos" o código desta task está no arquivo "tarefas.ino".<br>
  Essa task é iniciada no final da função "setup()" do módulo ESP, basicamente ela realiza a leitura do status dos pinos e atualiza o array "aU16_Pinos_Status[1][x]" com o status atual de cada pino.<br>

  NOTA 6: Se um pino for cadastrado como TIPO = 65534 a task não irá realizar a leitura deste pino e portanto seu status não será atualizado por esta função.

  NOTA 7: Essa task é executada continuamente aplicando apenas uma pausa pela função "vTaskDelay(4/portTICK_PERIOD_MS);" isto que dizer que o período de leitura de cada pino é feita no tempo de 4 dividido por portTICK_PERIOD_MS, isto está ligado diretamente a frequência do processador.<br>
          #define portTICK_PERIOD_MS ((TickType_t)1000 / configTICK_RATE_HZ)

- São usados 3 arrays com as informações dos pinos o array aU8_Pinos, aS8_Pinos e aU16_Pinos_Status.<br>

  - aU8_Pinos[7][x] = Array de 7 linhas.
    - aU8_Pinos[Propriedade][Pino]
    - aU8_Pinos[0][x] Índice 0 = PINO           = Guarda número do pino físico.
    - aU8_Pinos[1][x] Índice 1 = TIPO           = Guarda o tipo do pino. 1=DIGITAL / 0=ANALOGICO
    - aU8_Pinos[2][x] Índice 2 = MODO           = Guarda o modo do pino. INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0
    - aU8_Pinos[3][x] Índice 3 = XOR            = Guarda se deve aplicar operação xor no status do pino.  1=SIM / 0=NAO
    - aU8_Pinos[4][x] Índice 4 = STATUS         = Guarda o valor da última leitura do pino.  0=LOW / 4095=HIGH
    - aU8_Pinos[5][x] Índice 5 = RETENÇÃO       = Guarda se deve aplicar retenção na leitura do pino. 0=NAO / 1=SIM
    - aU8_Pinos[6][x] Índice 6 = TEMPO RETENÇÃO = Guarda o tempo de retenção da leitura do pino, 0 a 254


  - aS8_Pinos[1][x] = Array de 1 linha.
    - aS8_Pinos[Propriedade][Pino]
    - aS8_Pinos[0][x] = Nome/descricao do pino.


  - aU16_Pinos_Status[1][x] = Array de 1 linha.
    - aU16_Pinos_Status[Propriedade][Pino]
    - aU16_Pinos_Status[0][x] = Valor do pino.
