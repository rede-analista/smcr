# Funcionamento e Configurações de Rede

No momento inicial(primeiro boot) após a gravação do firmware, o módulo vem com a função "Modo AP" ativada, esta função proporciona uma facilidade de conectar e configurar o ssid e senha para que o módulo consiga se conectar na rede wifi que o módulo vai usar.<br>



## Funcionamento no Modo AP (quando ativado)
- Ao ligar o módulo ele carrega as informações de rede que estão na flash e tenta se conectar na rede wifi que foi configurada, caso não consiga em 4 tentativas, ele aciona o modo AP onde o ESP vai gerar uma rede wifi própria para que voce possa se conectar no módulo e realizar a configuração básica do wifi.<br>
Se a configuração default não foi alterada o nome da rede própria do ESP será "esp32modularx Ponto de Acesso" e a senha para se conectar nesta rede será "senha12345678".<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/50d66af1-0918-4cfd-87c9-e04728b089dc)

- Conecte-se na rede wifi.<br>
  - Abra o browser e digite o endereço "http://192.168.4.1:8080/wifiinicio".<br>
  - Ao abrir a página informe o nome e senha da sua rede wifi, logo após salve as informações.<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/bb87e3e0-50be-4dfb-96fe-4497856e6943)

- Depois de salvar as informações o módulo irá reiniciar e conectar na sua rede wifi.<br>

  NOTA 1:
  - Após configurar o wifi o módulo irá conectar na rede wifi que você acabou de informar, a partir deste ponto voce deve acessar o módulo pelo IP que foi atribuído à placa esp pelo seu roteador.<br>
  - A programação configura o recurso de mDNS, voce pode tentar descobrir o IP da placa esp com o comando "ping esp32modularx.local".<br>
  - É recomendado realizar o recurso de reserva de IP do seu roteador para que a placa esp sempre recebe o mesmo endereço IP. Isso é importante pois caso voce configure comunicação entre módulos e o IP de uma das placas for alterado, a comunicação entre módulos pode não funcionar.



## Configurações de Rede
- Parâmetro SSID
  - É a informação do nome da rede wifi que o módulo vai usar para se conectar durante o funcionamento normal(rede de trabalho/nome do seu wifi).
    
- Parâmetro SENHA
  - É a informação da senha da rede wifi que o módulo vai usar para se conectar durante o funcionamento normal(rede de trabalho/nome do seu wifi).
    
- Parâmetro HOSTNAME
  - É a informação de nome que o módulo vai usar para configuração de rede, este nome deve ser único na sua rede para não gerar conflito. O Hostname pode ser usado para acessar o módulo sem que voce saiba qual foi o IP que o módulo recebeu da sua rede wifi.<br>
  Voce pode acessar o módulo pelo navegador usando o seguinte formato "http://" + "hostname" + ".local" + ":" + "porta"<br>
  - Alguns exemplos:
    - http://esp32modularx.local:8080
    - http://192.168.50.10:8080
    - http://modulocampainha.local:8000
    - http://192.168.50.15:8000
      
  O módulo usa o serviço de mDNS para que o acesso por nome funcione na sua rede local.

  NOTA 2: Como sugestão voce pode identificar qual é o IP que o módulo está usando na sua rede atraves do seu roteador ou apenas executando o comando "ping esp32modularx.local", a informação de IP pode ser usada para acessar o módulo caso a resolução de nomes não funcione corretamente.<br><br>
  NOTA 3: Ao ativar o recurso de notificação por assistentes o serviço de mDNS não resolve o nome do módulo, sendo assim a informação de IP da "NOTA 1" deve ser usado para acessar o módulo.

- Parâmetro Porta do Servidor WEB
  - É a informação de qual porta tcp será usada para que voce consiga acessar o módulo ESP, o padrão é a porta 8080.<br>

- Parâmetro Tentativas de Conexão
  - É a informação de quantas tentativas o módulo vai executar para se conectar a serviços remotos durante o boot, por exemplo, conectar no wifi, conectar no MqTT, conectar em um assistente, etc. <br>
  - Após essa quantidade de tentativas o módulo continua a carregar as configurações deixando o serviço que falhou sem ser utilizado.<br>

    NOTA 4: Este parâmetro foi implementado para que o módulo não fique "preso" durante o boot por falta de conexão com algum serviço externo que o impeça de iniciar o funcionamento local do módulo.



## Se o módulor for reiniciado antes de salvar as informações na flash as configurações realizadas serão perdidas.

- Se quiser salvar as informações na memória flash do ESP, Vá para tela inicial clique em "Parâmetros", despois clique em "Salvar na Flash".<br>
  Responda "Sim" à pergunta e clique em "Salvar na Flash".<br>
  
  ![image](https://github.com/rede-analista/smcr/assets/66534023/2c82afff-a3c7-4ba4-ab7e-398530c743da)    


 
## Atualização de Firmware
- Você pode atualizar o firmware do módulo pela rede wifi de trabalho, para isto clique na opção "Atualizar Firmware"na página inicial.<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/958fc6ce-0156-463d-8f22-1f67ae2545e8)

- Escolha o arquivo .bin e clique em "Updade", após a atualização o módulo será reiniciado.<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/990fdb88-7666-4325-be8a-5b31144ade46)

  NOTA 5: Nesta página você terá algumas informações relacionadas ao chip do ESP32.<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/508aa92c-443a-4b90-a031-908f5ac2fe66)

  
