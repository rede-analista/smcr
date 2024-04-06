# Configuração de Ações

- Ações podem ser configuradas para que o múdulo execute uma funcionalidade como acionar um led, notificar quando um sensor for acionado, comunicar com um broker mqtt, etc.<br>

- O cadastro de ações está dividido em 3 camadas, primeira ação, segunda ação e terceira ação.<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/9f65db23-6085-49b4-958d-8288a3c7ddca)
<br>

- Cada camada está subdividida em duas páginas, onde a primeira página tem metade dos pinos (do pino 1 ao pino 26) e a segunda página tem a outra metade dos pinos (do pino 27 ao pino 52).<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/2166a16d-3a01-4f8e-b3a3-015470d90a32)




<br>
<br>
<br>
<br>  
- Para configurar ações, clique na opção "Configurar Ações"na página inicial.<br>

![image](https://github.com/rede-analista/smcr/assets/66534023/958fc6ce-0156-463d-8f22-1f67ae2545e8)
.[Exemplo Cadastro](excadacao.md).


- Será aberta a página com todas as informações de ações mas para cadastrar uma ação é necessário que já tenha pelo menos um pino cadastrado. Em cada camada tem um total de 52 posições para configurações das ações, o cadastro das ações pode ser realizada considerando a informação do "Pino Origem".<br>
<br>
- Pino Origem == Pino de entrada == Pino de sensor (botão, reed switch, etc.).<br>
Pino que irá disparar uma ação.<br>
<br>
- Pino Destino == Pino de saída == Pino de controle (buzzer, led, relé, etc.).<br>
Pino que irá sofrer uma ação.<br>
<br>
<br>
  NOTA 1: Observe que para cadastro de Ações existem várias páginas, antes de alterar entre as páginas você deve aplicar as configurações.<br>

  NOTA 2: Após configurar e clicar no botão "Aplicar" as configurações já estarão sendo usadas pelo módulo mas não estarão salvas na flash. Isto pode ser usado para testar uma configuração sem alterar a configuração que está salva na flash.

  NOTA 3: Você pode navegar entra as páginas de ações mas lembre-se de aplicar as configurações antes de trocar de página para não perder as configurações que foram realizadas na página atual.<br>

  NOTA 4: <strong>Se o módulo for reiniciado antes de salvar as informações na flash todas as configurações serão perdidas</strong>.
  
![image](https://github.com/rede-analista/smcr/assets/66534023/4ddfc001-cf6a-4e3b-b00c-35ef9b8aa63c)


- Parâmetro PINO ORIGEM
  - É o pino que irá iniciar a execução da ação com base no seu status.

- Parâmetro PINO DESTINO
  - É o pino que irá sofrer uma alteração durante a execução da ação.

- Parâmetro AÇÃO
  - É a ação que será executada, esta informação pode ser NENHUMA=0 / LIGA=1 / LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5 / Status=254 / Sincronismo=255(reservada)<br>
    NOTA 5: A ação 254 é usada para atualizar o status de um pino virtual.[Veja TIPO](pinos.md)<br>
    NOTA 6: A ação 255 é reservada para controle de status de comunicação entre módulos. [Veja CICLOS HANDSHAKE](intermod.md)

- Parâmetro TEMPO ON
  - Informa o tempo em contagem de ciclos em determinadas ações.  Este valor pode ser de 0 a 65535. 
    1. Se a ação for LIGA DELAY=2 aguarda a contagem de "Tempo ON" para executar a ação depois que o pino for acionado.
    2. Se a ação for PISCA=3 será a contagem de "Tempo ON" quando a saída(Pino Destino) ficara ligada.
    3. Se a ação for PULSO=4 será o tempo que a saída(Pino Destino) ficará acionada antes de desligar.
    4. Se a ação for PULSO DELAY ON=5 será o tempo que vai aguardar antes de acionar a saída(Pino Destino).(veja Tempo OFF)

- Parâmetro TEMPO OFF
  - Informa o tempo em contagem de ciclos em determinadas ações.  Este valor pode ser de 0 a 65535. 
    1. Se a ação for PISCA=3 será a contagem de "Tempo OFF" quando a saída(Pino Destino) ficara desligada.
    2. Se a ação for PULSO DELAY ON=5 será o tempo que vai aguardar antes de desligar a saída(Pino Destino).(veja Tempo ON)

- Parâmetro PINO_DEST_REM_(MASK)
  - Informa qual pino será informado ao módulo remoto. Server como uma máscara, você pode usar em um módulo o pino 4 e em outro o pino 23. Normalmente usado com recurso de pino virtuao. ([Veja](pinos.md).

- Parâmetro ENVIA PARA MÓDULO
  - Ativa o envio de informação de status do pino a outro módulo ESP32, esta informaçẽo pode ser NÃO=0 / 1 a 254 esta numeração corresponde ao ID do módulo que será enviado o status dos pinos<br>
    NOTA 7: Antes de habilitar este item você deve ser configurar as informações do módulo receptor.[Veja Configurações Gerais](configgeral.md)

- Parâmetro ENVIA TELEGRAM
  - Ativa as notificações desta ação para enviar ao Telegram, esta informaçẽo pode ser NÃO=0 / SIM=1<br>
    NOTA 8: Antes de habilitar este item você configurar as informações do Telegram.[Veja Configurações Gerais](configgeral.md)

- Parâmetro NOT. ASSIST.
  - Ativa as notificações desta ação para notificar aos assistentes, esta informaçẽo pode ser NÃO=0 / SIM=1<br>
    NOTA 9: Antes de habilitar este item você configurar as informações dos Assistentes.[Veja Configurações Gerais](configgeral.md)<br>

- Parâmetro ENVIA MQTT
  - Ativa as notificações desta ação para envior a um mqtt, esta informaçẽo pode ser NÃO=0 / SIM=1<br>
    NOTA 10: Antes de habilitar este item você configurar as informações do MQTT.[Veja Configurações Gerais](configgeral.md)

- Parâmetro CLASSE MQTT
  - É a informação de qual classe esta ação será informada ao servidor mqtt<br>
    Deve ser usado uma clase suportado pelo MqTT, mais informações podem ser consultadas em [MQTT](https://www.home-assistant.io/integrations/mqtt/)
    
   
[Exemplo Cadastro](excadacao.md)

# Tarefa de execução de ações

- As ações são executadas pelas tasks "TaskAcoes1Pinos", "TaskAcoes2Pinos" e "TaskAcoes3Pinos" o código destas tasks está no arquivo "tarefas.ino".<br>
  Essas tasks são iniciadas no final da função "setup()" do módulo ESP, basicamente ela consulta o array onde tem o status dos pinos e executa a ação conforme foi configurado.<br>

  NOTA 11: Essa task é executada continuamente aplicando apenas uma pausa pela função "vTaskDelay(8/portTICK_PERIOD_MS)" isto que dizer que o período de verificação e execução de cada ação é feita no tempo de 8 dividido por portTICK_PERIOD_MS, isto está ligado diretamente a frequência do processador.<br>
          #define portTICK_PERIOD_MS ((TickType_t)1000 / configTICK_RATE_HZ)


- São usados 6 arrays com as informações das ações aU16_Acao1 do tipo uint16_t, aU16_Acao2 do tipo uint16_t e aU16_Acao3 do tipo uint16_t, os 3 array tem a mesma função sendo que cada um gerencia as ações de cada camada de configuração.<br>
  Outros 3 arrays são usados para dados do tipo string que são aS8_Acao1, aS8_Acao2 e aS8_Acao3.<br>

  - aU16_Acao[6][43] = Array de 6 linhas e 52 colunas. (cada array)
    - aU16_Acao[Propriedade][Pino]
    - U16_Acao[0][x] = Relacao (Pino Origem) 0=Nenhum
    - aU16_Acao[1][x] = Relacao (Pino Destino) 0=Nenhum
    - aU16_Acao[2][x] = Acao 0=Nenhuma / 1=Liga / 2=Liga Delay / 3=Pisca / 4=Pulso / 5=Pulso Delay
    - aU16_Acao[3][x] = Tempo Acao ON (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
    - aU16_Acao[4][x] = Tempo Acao OFF (LIGA DELAY=2 / PISCA=3 / PULSO=4 / PULSO DELAY ON=5)
    - aU16_Acao[5][x] = Mask Pino Destino

  - aU16_AcaoRede[Propriedade][Pino]
    - aU16_AcaoRede[0][x] = Envia ao Modulo 0=Nao / 1=Sim
    - aU16_AcaoRede[1][x] = Envia ao Telegram 0=Nao / 1=Sim
    - aU16_AcaoRede[2][x] = Envia ao MqTT 0=Nao / 1=Sim
    - aU16_AcaoRede[3][x] = Notifica Assitente 0=Nao / 1=Sim

  - aS8_Acao1[2][43] = Array de 2 linhas e 52 colunas. (cada array)
    - aS8_Acao1[Propriedade][Pino]
    - aS8_Acao1[0][x] Índice 0 = Classe da ação para o MqTT
    - aS8_Acao1[1][x] Índice 1 = Icone da ação para o MqTT
