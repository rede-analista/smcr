# Funcionamento e Configurações de Rede

No momento inicial o módulo vem com a função "Modo AP" ativada, está função proporciona uma facilidade de conectar e configurar o wifi básico para que o módulo consiga se conectar na rede wifi que ele irá funcionar.<br>

## Funcionamento no Modo AP (quando ativado)
- Ao ligar o módulo ele carrega as informações de rede que estão na flash e tenta se conectar na rede widi de trabalho, caso não consiga em 4 tentativas, ele aciona o modo AP onde o ESP vai gerar uma rede wifi própria para que voce possa se conectar nesta rede e realizar a configuração básico de wifi.<br>
Se a configuração default não foi alterada o nome da rede própria do ESP será "esp32modularx Ponto de Acesso" e a senha para se conectar nesta rede será "senha12345678".<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/50d66af1-0918-4cfd-87c9-e04728b089dc)

- Conecte-se na rede e pelo navegador você deve acessar o endereço "http://192.168.4.1:8080/wifiinicio". ao abrir a página informe o nome e senha da sua rede wifi, logo após salve as informações.<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/bb87e3e0-50be-4dfb-96fe-4497856e6943)

- Depois de salvar as informações o módulo irá reiniciar e conectar na sua rede wifi.<br>

## Configurações de Rede
- Parâmetro SSID
  - É a informação do nome da rede wifi que o módulo vai usar para se conectar durante o funcionamento normal(rede de trabalho).
- Parâmetro SENHA
  - É a informação da senha da rede wifi que o módulo vai usar para se conectar durante o funcionamento normal(rede de trabalho).
- Parâmetro HOSTNAME
  - É a informação de nome que o módulo vai usar para configuração de rede, esta nome deve ser único na sua rede para não gerar conflito. O Hostname pode ser usado para acessar o módulo sem que voce saiba qual foi o IP que o módulo recebeu da sua rede.<br>
  Voce pode acessar o módulo pelo navegador usando o seguinte formato "http://" + "hostname" + ".local" + ":" + "porta"<br>
  - Alguns exemplos:
    - http://esp32modularx.local:8080
    - http://192.168.50.10:8080
    - http://modulocampainha.local:8000
    - http://192.168.50.15:8000
      
  O módulo usa o serviço de mDNS para que o acesso por nome funcione na sua rede local.

  NOTA 1: Como sugestão voce pode identificar qual é o IP que o módulo está usando na sua rede atraves do seu roteador, esta  informação pode ser usada para acessar o módulo caso a resolução de nomes não funcione corretamente.<br>
  NOTA 2: Ao ativar o recurso de notificação por assistentes o serviço de mDNS não resolve o nome do módulo, sendo assim a informação de IP da "NOTA 1" deve ser usado para acessar o módulo.

  - Parâmetro Porta do Servidor WEB
    - É a informação de qual porta será usada para que voce consiga acessar o módulo ESP, o padrão é a porta 8080.<br>

  - Parâmetro Tentativas de Conexão
    - É a informação de quantas vezes o módulo vai tentar para se conectar a serviços remotos durante o boot, por exemplo, conextar no wifi, contctar ano MqTT, conectar em um assistente.<br>
      Após essa quantidade de tentativas o módulo continua a carragar as configurações deixando o serviço que falhou sem utilizar.<br>

    NOTA 1: Este parâmetro foi implementado para que o módulo não fique "preso" durante o boot por falta de conexão com alhuma serviço externo que impeça o funcionamento local do módulo.
 
