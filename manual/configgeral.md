# Configurações Gerais

- Nas configurações gerais devem ser cadastrados informações diversas para uso de notificações e comunicação entre módulos.<br>

- Você pode configurar as ações, para isto clique na opção "Configurarões Gerais"na página inicial.<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/958fc6ce-0156-463d-8f22-1f67ae2545e8)


## Informações do Modo AP

- Parâmetro HABILITAR MODO AP
  - Você pode desabilitar o modo AP. O modo AP é um recurso que o ESP32 gera uma rede wifi caso ele não consiga conexão no SSID de trabalho. [Veja Modo AP](rede.md)

## Informações do Inter Módulos
- Parâmetro HABILITAR INTER MÓDULOS
  - Você pode habilitar a comunicação entre módulos. A comunicação entre módulos é um recurso que o ESP32 envia informações de status do pino para outro módulo usando a rede wifi. Com esta atualização remota de status do pino voce pode acionar um equipamento mesmo que o sensor esteja em outro módulo esp distante. [Veja Inter Módulos](intermod.md)
   
## Informações do Telegram

- Parâmetro HABILITA TELEGRAM
  - Habilita o envio de notificações para um grupo no Telegram.<br>
    NOTA 1: Para habilitar esta opção os parâmetros referente ao Telegram precisam ser informados.

- Parâmetro CHAVE API TELEGRAM
  - Informe a chave da API do bot do Telegram.<br>
    NOTA 2: Para cada módulo deve ser gerado uma chave, caso utilize a mesma chave pode gerar conflito onde um módulo recebe informações do Telegram e outro módulo com a mesma chave não receba as informações corretamente.

- Parâmetro ID GRUPO TELEGRAM
  - Informe o ID do grupo deo Telegram que será enviado as notificações.

- Parâmetro NOME BOT TELEGRAM
  - Informe o nome do bot do Telegram.

- Parâmetro TEMPO TELEGRAM
  - Informe o tem em milisegundos que a função de enviar notificações ao Telegram será executada.


## Informações do MQTT

- Parâmetro HABILITA MQTT
  - Habilita o envio de informações para um broker mqtt.<br>
    NOTA 3: Para habilitar esta opção os parâmetros referente ao mqtt precisam ser informados.

- Parâmetro IP MQTT
  - Informe o IP do mqtt que irá receber as informações.

- Parâmetro USUÁRIO MQTT
  - Informe o usuário que irá autenticar no mqtt.

- Parâmetro SENHA MQTT
  - Informe a senha que irá autenticar no mqtt.

- Parâmetro PORTA MQTT
  - Informe a porta tcp que usada para conectar no mqtt.

- Parâmetro TÓPICO MQTT
  - Informe tópico que irá compor o subscribe para envio ao mqtt.

- Parâmetro TEMPO VERIFICAÇÃO MQTT
  - Informe o tem em milisegundos que a função de enviar notificações ao mqtt será executada.

- Parâmetro TEMPO DISCOVERY MQTT
  - Informe o tem em milisegundos que a função de enviar discovery ao mqtt será executada.

## Informações dos Assistentes

- Parâmetro HABILITA ASSISTENTES
  - Habilita o envio de notificações para assistentes e o comando de voz por assistentes.>br>
    NOTA 4: Para habilitar esta opção os parâmetros referente aos assistentes precisam ser informados.

- Parâmetro NOME GOOGLE
  - Informe nome que o dispositivo Google Home está cadastrado no seu aplicativo.

- Parâmetro NOME ALEXA
  - Informe nome que o dispositivo Alexa está cadastrado no seu aplicativo.

- Parâmetro LINGUAGEM ASSISTENTES
  - Informe a linguagem que será usada para enviar notificações aos assistentes.

- Parâmetro TEMPO ASSISTENTES
  - Informe o tem em milisegundos que a função de enviar notificações aos assistentes será executada.

- Parâmetro INÍCIO FRASE ALERTA
  - Informe o texto que irá compor o início da frase de notificação dos assistenes quando tiver um alerta.

- Parâmetro INÍCIO FRASE NORMALIZAÇÃO
  - Informe o texto que irá compor o início da frase de notificação dos assistenes quando um alerta for normalizado.


- Depois de preencher as informações clique em "Aplicar(sem salvar)".<br>
  Isto cadastra as informações porém não salva as informações da flash do ESP. Se o módulo for reiniciado antes de salvar as informações serão perdidas.<br>

  NOTA 5: Algumas informações só serão usadas após recarregar as funções do setup() do ESP32, [Veja Recarregar Funçõẽs](funmanu.md)<br>
  **Lembre-se que "Recarregar" as funções não salva as informações na flash, se o módulo for reiniciado antes de salvar na flash as informações serão perdidas**




## Visualizar Parâmetros

- Para visualizar os parâmetros que estão em execução da memória do ESP e também para visualizar as informações que estão salvas na memória flash, na página inicial clique em Parâmetros. Na tela uqe irá abri voce vera as informações. Lembre-se que a maioria das informações são tradas por arrays e é neste formato que são mostrados os dados.
![image](https://github.com/rede-analista/smcr/assets/66534023/7bfcf06d-6510-4b78-8568-2e758a947b30)



- Se quiser salvar as informações na memória flash do ESP clique em "Salvar na Flash".<br>
  Responda "Sim" à pergunta e clique em "Salvar na Flash".<br>
  
  ![image](https://github.com/rede-analista/smcr/assets/66534023/2c82afff-a3c7-4ba4-ab7e-398530c743da)



  
## Configuração em Massa

- Alguns cadastros possuem uma quantidade maior de informações, por exemplo, cadastro dos pinos ou cadastro de ações, etc. Para facilitar a configuraçõa de uma nova placa ESP ou uma substituição, foi criado esta opção para que alguns desses cadastros possam ser realizada de forma massiva. Copiando as informações desses campos pode se feito tambem um backup parcial das configurações do módulo.<br>
  

![image](https://github.com/rede-analista/smcr/assets/66534023/c90bd2b8-e8c1-40d8-b1b0-e2051d1da8cb)

  
