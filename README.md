# SMCR
Programação de um sistema modular de sensores e acionamentos para ESP32.

# Descrição:
O objetivo é criar uma programação para ESP32, de forma que a definição os pinos não seja estática dentro do código fonte, proporcionando a possibilidade de alterar a definição dos pinos por interface web e configurar ações com base no status dos pinos.

# Resumo:
A programação é feita de forma que a maioria das configurações estejam disponíveis em uma interface web no ESP32, para que o usuário possa acessar pelo navegador e realizar as configurações desejadas, salvando as informações em arquivos na flash do ESP32.<br>
Algumas das características são proporcionar comunicação com outros módulos ESP32, notificação por Telegram, comunicação com MqTT e notificação por assistentes.

A interface web pode disponibilizar até 254 posições de configurações de pinos, ou seja, voce poderá configurar até 254 pinos como entrada ou saída. Tambem pela interface poderá configurar até 4 ações para cada pino, estas ações serão executadas quando por exemplo um sensor for acionado. Na configuração de ações é possível realizar uma configuração em cascata quando por exemplo o pino 2 aciona o pino 4, o pino 4 aciona o pino 5 e assim por diante, há várias formas de realizar as configurações de ações, depende um pouco da imaginação, espero que as quantidades sejam suficientes para atender uma boa parte das necessidades.

**NOTA: Não sou programador e nem técnico em eletrônica, somente me interesso por programação, sendo assim, não espere uma programação "bonita" e/ou dentro das melhores práticas, mas fique a vontade para trocar informações ou sugerir alguma melhoria.**

[Print de Telas](manual/telas/prints.md)

## Recursos:
- Recursos já disponíveis: 

  - [Recursos de Rede](manual/rede.md):
    - Configurações relacionadas da rede, modo AP, Wifi (ssid/senha), hostname, porta servidor web, tentativas de conexões, servidor NTP, etc.

  - [Recursos Gerais](manual/configgeral.md):
    - Configurações relacionadas a status, cores, temporizadores, whatchdog, quantidade de pinos, etc.

  - [Recursos Pinagem](manual/pinos.md):
    - Configurações relacionadas aos pinos, nome, id de pino, tipo, modo, XoR, nível de acionamento, retenção, etc.

  - [Recursos Ações](manual/acoes.md):
    - Configurações relacionadas as ações, pinos origem/destino, tipo de ação, temporizadores, acionamentos, MqTT, acionamento remoto, etc.

  - [Execução de Funções](manual/funcoes.md):
    - Execução de funções, Visualização serial, reboot, pausar rotinas, tasks, formatação flash, recarregar funções, whatchdog, etc;

  - [Recursos Arquivos](manual/arquivos.md):
    - Configurações relacionadas a arquivos, listar, upload, doanload, salvar, deletar, atualizar firmware, etc.

  - [Conceitos, Definições e Códigos para Referências](manual/ref.md):

- Atividades/Recursos previstos:
  - Comando de voz por assistentes.

- Atividades/Recursos não previstos:
  - Não é previso comunicação usando ssl, não é aconselhado ser usado em uma rede pública ou redes desprotegidas, não usa acesso https.

# Ambiente Desenvolvimento:
- O desenvolvimento foi realizado no VSCode + platformio com sistema operacional Debian 12.1 Bookworm. Para compilação do sketch algumas bibliotecas precisam ser instaladas. Em meu ambiente tenho bibliotecas adicionais que não são necessárias para este sketch, vou listar aqui as que precisei instalar, porém, algumas já estavam instaladas em meu ambiente. Como cada ambiente tem sua peculiaridade acredito que vai precisar de algumas pesquisas para ajustar sua IDE para compilação.

  - Bibliotecas:

    1. Arduino_JSON Library for Arduino.
    2. ESP32MQTTClient.
    3. HttpClient.
    4. Universal Telegram Bot Library.
    5. esp8266-google-home-notifier.
    6. MQTTPubSubClient.
    7. Arduino_FreeRTOS_Library.
     
  NOTA: Na pasta ["build"](https://github.com/rede-analista/smcr/tree/main/.pio/build/upesy_wroom) deixarei o arquivo de fimware .bin já compilado caso queiram simplesmente realizar a gravação no ESP32 sem precisar compilar. Para gravação sem compílar pode usar qualquer ferramenta como exemplo "esptools".

# !!!! IMPORTANTE !!!!
A programação atual não faz nenhuma tratativa com as informações que são inseridas/configuradas, não há tratativas para informações com acentuação e tambem não há tratativas para configurações incorretas de pinagem.<br>
Desta forma, uma configuração incorreta pode causar travamentos, falhas ou ainda danificar o módulo ESP32, tenha cuidado e muita atenção para inserir as informações.


# Como Utilizar (resumo) 
[Consulte Configuração de Rede](manual/rede.md)
<br>Após realizar a gravação do programa no ESP32 e rebootar o módulo ele irá gerar uma rede wifi (modo AP) com o nome padrão default do módulo "esp32modularx Ponto de Acesso" a senha padrão é "senha12345678".<br>
![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/c_wifi_inicial_t1.png)

Conecte-se na rede e pelo navegador você deve acessar o endereço "http://192.168.4.1:8080/wifiinicio". ao abrir a página informe o nome e senha da sua rede wifi, logo após salve as informações.<br>
![image](https://github.com/rede-analista/smcr/blob/develop/manual/telas/c_wifi_inicial_t2.png)
