# SMCR
Programação ESP32 para sistema modular de sensores e acionamentos.
# Descrição:
O objetivo é criar uma programação para ESP32, de forma que a definição os pinos não seja estática dentro do código fonte, proporcionando a possibilidade de alterar a definição dos pinos por interface web.
# Resumo:
A programação é feita de forma que a maioria das configurações estejam disponíveis em uma interface web no ESP32, para que o usuário possa acessar pelo navegador e realizar as configurações desejadas, salvando as informações da memória flash do ESP32.<br>
Algumas das características são proporcionar comunicação com outro módulo ESP32, notificação por Telegram, comunicação com MqTT e notificação por assistentes.

A interface web disponibiliza 23 posições de configurações de pinos, ou seja, voce poderá configurar até 23 pinos como entrada ou saída. Tambem pela interface poderá configurar até 3 ações para cada pino, estas ações serão executadas quando por exemplo um sensor for acionado. Na configuração de ações é possível realizar uma configuração em cascata quando por exemplo o pino 2 aciona o pino 4, o pino 4 aciona o pino 5 e assim por diante, há várias formas de realizar a configuração de ações espero que seja suficiente para atender uma boa parte das necessidades.

**NOTA: Não sou programador e nem técnico em eletrônica, somente me interesso por programação e controladores, sendo assim, não espere uma programação "bonita" e/ou dentro das melhores práticas, mas fique a vontade para trocar informações ou sugerir alguma melhoria**

## Recursos:
- Recursos já disponíveis:
  - [Recursos de Rede](manual/rede.md):
    1. Configuração inicial em modo AP.
    2. Configuração Wifi (ssid/senha).
    3. Configuração hostname.
    4. Configuração porta tcp do servidor web.
    5. Configuração tentativas de conexões.
    6. Atualização firmware por wifi.
  - [Recursos Pinagem](manual/pinos.md):
    1. Nomear os pinos (colocar descrição).
    2. Configuração tipo digital.
    3. Configuração modo entrada/saída.
    4. Configuração operador XOR.
    5. Configuração retenção.
  - [Recursos Ações](manual/acoes.md):
    1. Associar pinos e definir ações.
    2. Definir nível acionamento.
    3. Definir tempo ON/OFF conforme ação.
    4. Deninir envio dados para outro módulo ESP32.
    5. Definir envio ao telegram.
    6. Definir envio ao MqTT.
    7. Definir envio assistentes.
  - [Recursos Gerais](manual/configgeral.md):
    1. Habilidat/desabilitar modo AP.
    2. Denifir informações de Inter Módulos.
    3. Denifir informações do bot Telegram.
    4. Denifir informações do broker MqTT.
    5. Denifir informações dos assistentes.
    6. Visualizar configurações em memória e na flash.
  - [Funções de Manutenção](manual/funmanu.md):
    1. Reiniciar módulo ESP32.
    2. Limpeza de configurações ou Formatação da flash.
    3. Recarregar Funções do Setup.

- Atividades/Recursos previstos:
  - Comando de voz por assistentes.
  - Tratar informações/configurações antes de aplicar/salvar no módulo.
  - Detalhar comentários no código fonte.

- Atividades/Recursos não previstos:
  - Não é previso comunicação usando ssl (somente para uso interno), não deve ser usado em uma rede pública ou redes desprotegidas, não usa acesso https.

# Ambiente Desenvolvimento:
- O desenvolvimento foi realizado na interface IDE do Arduíno 2.2.1 com sistema operacional Debian 12.1 Bookworm. Para compilação do sketch algumas bibliotecas precisam ser instaladas. Em meu ambiente tenho bibliotecas adicionais que não são necessárias para este sketch, vou listar aqui as que precisei instalar, porém, algumas já estavam instaladas em meu ambiente. Como cada ambiente tem sua peculiaridade acredito que vai precisar de algumas pesquisas para ajustar sua IDE para compilação.
  - Bibliotecas:
    1. Arduino_JSON Library for Arduino.
    2. ESP32MQTTClient.
    3. HttpClient.
    4. Universal Telegram Bot Library.
    5. esp8266-google-home-notifier.
    6. MQTTPubSubClient.
    7. Arduino_FreeRTOS_Library.
     
  NOTA: Na pasta "build" deixarei o arquivo de fimware .bin já compilado caso queiram simplesmente realizar a gravação no ESP32 sem precisar compilar. Para gravação sem compílar pode usar qualquer ferramenta como exemplo "esptools".

# !!!! IMPORTANTE !!!!
A programação atual ainda não faz nenhuma tratativa com as informações que são inseridas/configuradas, não há tratativas para informações com acentuação e tambem não há tratativas para configurações incorretas de pinagem.<br>
Desta forma, uma configuração incorreta pode causar travamentos, falhas ou ainda danificar o módulo ESP32, tenha cuidado e muita atenção para inserir as informações.


# Como Utilizar (resumo)
Após realizar a gravação do programa no ESP32 e rebootar o módulo ele irá gerar uma rede wifi (modo AP) com o nome padrão default do módulo "esp32modularx Ponto de Acesso" a senha padrão é "senha12345678".<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/50d66af1-0918-4cfd-87c9-e04728b089dc)

Conecte-se na rede e pelo navegador você deve acessar o endereço "http://192.168.4.1:8080/wifiinicio". ao abrir a página informe o nome e senha da sua rede wifi, logo após salve as informações.<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/bb87e3e0-50be-4dfb-96fe-4497856e6943)

Depois de salvar as informações o módulo irá reiniciar e conectar na sua rede wifi.<br>


Pelo navegador acesse o endereço "http://esp32modularx.local:8080", irá abrir a página inicial do módulo ESP32 e voce terá acesso as demais páginas de configuração.
![image](https://github.com/rede-analista/smcr/assets/66534023/13792da4-3303-49b6-9e79-091416084e11)



A informações default de hostname, porta, senha, etc. podem ser alteradas depois pela interface web. Caso queira alterar as informações no código antes de compilar/gravar elas podem ser encontradas no arquivo "funcoes.ino" nas linhas 495 a 498.
![image](https://github.com/rede-analista/smcr/assets/66534023/7ba3fe7a-30c6-4afc-a335-33dfb037514c)




