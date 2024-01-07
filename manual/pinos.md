# Configurações dos pinos

- Você pode configurar os pinos do módulo, para isto clique na opção "Configurar Pinos"na página inicial.<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/958fc6ce-0156-463d-8f22-1f67ae2545e8)
[Exemplo Cadastro](excadpino.md)


- Será aberta a página com todas as informações de todos os pinos. Nesta página pode chegar a 52 posições para configurações dos pinos, o cadastro dos pinos pode ser realizada em qualquer posição.
![image](https://github.com/rede-analista/smcr/assets/66534023/99edd9c2-e18b-49e1-9c46-449e37b71a05)

O total de pinos pode ser ajustado na variável "vU8_totPinos" no código antes da compilação que fica no arquivo SMCR_Modular_v15.ino.

NOTA 1: Para não limitar a configuração dos pinos não há uma validação de quais pinos podem ser usados, consulte a informações de pinout do ESP32 para identificar pinos reservados e que não devem ser usados nas configurações nesta página.<br>

NOTA 2: Após configurar e clicar no botão "Aplicar" as configurações já estarão sendo usadas pelo módulo mas não estarão salvas na flash. Isto pode ser usado para testar uma configuração sem alterar a configuração que está salva na flash.<br>

NOTA 3: Se o módulo for reiniciado antes de salvar as informações na flash todas as configurações serão perdidas.<br>

- Parâmetro NOME
  - É uma nomenclatura para facilitar na identificação dos pinos, um nome curto, este nome será usado na caso de notificações.
  
- Parâmetro PINO
  - É a informação do pino físico do ESP32, aqui será feito a associação do pino físico na placa ESP.<br>
    Esta informação será usada na configuração de Ações(eventos).
    Deve ser um número que corresponde ao pino físico do ESP, por exemplo, este número pode ser 2,4,5,12,13,14,15,16,17,18,19,21,22,23,25,26,27,32,33,34,35,36,39...251,253,254<br>
    NOTA 4: O Pino 255 é reservado para controle de status de comunicação entre módulos. [Veja CICLOS HANDSHAKE](intermod.md)

- Parâmetro STATUS
  - Informa o status UP ou DOWN da última leitura do pino.Esta informação será LOW=0 / HIGH=1 para pinos digitais<br>
  
- Parâmetro TIPO
  - É o tipo que o pino será configurado na função pinMode(), esta informação pode ser 0=Sem Uso / 1=Digital / 192=Digital / 254=Remoto<br>
    Se o valor 254 for configurado, o módulo não irá realizar a atualização de status do pino, esta configuração deve ser usada quando for habilitado o recurso de "Inter Módulos".<br>
    O recurso de Inter Módulos ativa a comunicação entre dois ou mais módulos ESP32 onde um módulo transmissor iŕa atualizar o status de um pino no módulo receptor.<br>
    O cadastro de um pino como tipo 254 deve ser usado quando o módulo vai receber o status deste pino de forma remota, o status será enviado de outro módulo ESP para este módulo que terá o pino cadastrado como tipo 254. Quando for cadastrar um pino como 254 pode ser usado qualquer númeração de pino entre 1 e 255 pois um pino do tipo 254 será considerado um pino virtual(não físico) e servirá apenas para disparar ações no módulo que recebe os dados de status de outros módulos. este recurso pode ser usado para não inutilizar um pino físico em uma ação que não teŕa leitura de sensor localmente. 
    

- Parâmetro MODO
  - É o modo que o pino será configurado na função pinMode(), esta informação pode ser INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12<br>
    Se o pino for do tipo 254 este valor não será considerado, pode ser 0(zero).

- Parâmetro XOR
  - Indica se deve ser aplicado a operação XoR quando realizar a leitura do status do pino, esta informação pode ser 0=Valor igual a leitura do pino / 1=Valor inverso a leitura do pino<br>

- Parâmetro RETENÇÃO
  - Informa se após a leitura de status de um pino a task irá ignorar a leitura do pino nos próximos X ciclos mantendo a última leitura do pino, esta informação pode ser 0=Não / 1=Sim<br>

Parâmetro TEMPO RETENÇÃO
  - Informa quantos clicos a task deixará de ler o status de um pino se a opção RETENÇÃO estiver ativada.<br>
    O tempo de retenção não é contado em milisegundos mas sim em tempo de clico do processador, para mais detalhe do tempo de retenção veja "NOTA 5"<br>
    Esta informação pode ser de 1 a 255 ciclos.

[Exemplo Cadastro](excadpino.md)

# Tarefa de leitura do status dos pinos

- A leitura de status dos pinos é executada pela task "TaskLeituraPinos" o código desta task está no arquivo "tarefas.ino".<br>
  Essa task é iniciada no final da função "setup()" do módulo ESP, basicamente ela realiza a leitura do status dos pinos e atualiza o array "aU8_Pinos[4][x]" com o status atual de cada pino.<br>

  NOTA 5: Se um pino for cadastrado como TIPO = 254 a task não irá realizar a leitura deste pino e portanto seu status não será atualizado por esta função.

  NOTA 6: Essa task é executada continuamente aplicando apenas uma pausa pela função "vTaskDelay(9/portTICK_PERIOD_MS)" isto que dizer que o período de leitura de cada pino é feita no tempo de 9 dividido por portTICK_PERIOD_MS, isto está ligado diretamente a frequência do processador.<br>
          #define portTICK_PERIOD_MS ((TickType_t)1000 / configTICK_RATE_HZ)

- São usados 2 arrays com as informações dos pinos o array aU8_Pinos do tipo uint8_t e o array aS8_Pinos do tipo string.<br>

  - aU8_Pinos[7][43] = Array de 7 linhas e 43 colunas.
    - aU8_Pinos[Propriedade][Pino]
    - aU8_Pinos[0][x] Índice 0 = PINO           = Guarda número do pino físico.
    - aU8_Pinos[1][x] Índice 1 = TIPO           = Guarda o tipo do pino. 1=DIGITAL / 0=ANALOGICO
    - aU8_Pinos[2][x] Índice 2 = MODO           = Guarda o modo do pino. INPUT=1 / OUTPUT=3 / PULLUP=4 / INPUT_PULLUP=5 / PULLDOWN=8 / INPUT_PULLDOWN=9 / OPEN_DRAIN=10 / OUTPUT_OPEN_DRAIN=12 / ANALOG=0
    - aU8_Pinos[3][x] Índice 3 = XOR            = Guarda se deve aplicar operação xor no status do pino.  1=SIM / 0=NAO
    - aU8_Pinos[4][x] Índice 4 = STATUS         = Guarda o valor da última leitura do pino.  0=LOW / 1=HIGH
    - aU8_Pinos[5][x] Índice 5 = RETENÇÃO       = Guarda se deve aplicar retenção na leitura do pino. 0=NAO / 1=SIM
    - aU8_Pinos[6][x] Índice 6 = TEMPO RETENÇÃO = Guarda o tempo de retenção da leitura do pino, 0 a 254

  - aS8_Pinos[1][43] = Array de 1 linha e 43 colunas.
    - aS8_Pinos[Propriedade][Pino]
    - aS8_Pinos[0][x] = Nome/descricao do pino.
