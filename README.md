# SMCR
Programação ESP32 para sistema modular de sensores e acionamentos.
# Descrição:
O objetivo é criar uma programação para ESP32, de forma que a definição os pinos não seja estática dentro do código fonte, proporcionando a possibilidade de alterar a definição dos pinos por interface web.
# Resumo:
A programação é feita de forma que a maioria das configurações estejam disponíveis em uma interface web no ESP32, para que o usuário possa acessar pelo navegador e realizar as configurações desejadas, salvando as informações da memória flash do ESP32.<br>
Algumas das características são proporcionar comunicação com outro módulo ESP32, notificação por Telegram, comunicação com MqTT e notificação por assistentes.

**NOTA: Não sou programador e nem técnico em eletrônica, somente me interesso por programação e controladores, sendo assim, não espere uma programação "bonita" e/ou dentro das melhores práticas**

## Recursos:
- Recursos já disponíveis:
  - Recursos de Rede:
    1. Configuração inicial em modo AP.
    2. Configuração Wifi (ssid/senha).
    3. Configuração hostname.
    4. Configuração porta tcp do servidor web.
    5. Configuração tentativas de conexões.
    6. Atualização firmware por wifi.
  - Recursos Pinagem:
    1. Nomear os pinos (colocar descrição).
    2. Configuração tipo digital.
    3. Configuração modo entrada/saída.
    4. Configuração operador XOR.
    5. Configuração retenção.
  - Recursos Ações:
    1. Associar pinos e definir ações.
    2. Definir nível acionamento.
    3. Definir tempo ON/OFF conforme ação.
    4. Deninir envio dados para outro módulo ESP32.
    5. Definir envio ao telegram.
    6. Definir envio ao MqTT.
    7. Definir envio assistetes.
  - Recursos Gerais:
    1. Habilidat/desabilitar modo AP.
    2. Denifir informações de outro módulo ESP32 (receptor).
    3. Denifir informações do bot Telegram.
    4. Denifir informações do broker MqTT.
    5. Denifir informações dos assistentes.
    6. Visualizar configurações em memória e na flash.
    7. Reiniciar módulo ESP32.
    8. Limpeza de configurações da flash.
    9. Formatação da flash.

- Atividades/Recursos previstos:
  - Comando de voz por assistentes.
  - Tratar informações/configurações antes de aplicar/salvar no módulo.
  - Detalhar comentários no código fonte.
  - 

- Atividades/Recursos não previstos:
  - Não é previso comunicação usando ssl (somente para uso interno), não deve ser usado em uma rede pública ou redes desprotegidas, não usa acesso https.

# Ambiente Desenvolvimento:
- O desenvolvimento foi realizado na interface IDE do Arduíno 2.2.1. Para compilação do sketch algumas bibliotecas precisam ser instaladas. Em meu ambiente tenho bibliotecas adicionais que não são necessárias para este sketch, vou listar aqui as que precisei instalar, porém, algumas já estavam instaladas em meu ambiente. Como cada ambiente tem sua peculiaridade acredito que vai precisar de algumas pesquisas para ajustar sua IDE para compilação.
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
Na programação ainda não esstá sendo feito nenhuma tratativa com as informações que são inseridas, não há tratativas para informações com acentuação e tambem não há tratativas para informações incorretas de pinagem.
Desta forma, uma configuração incorreta pode causar travamentos, falhas ou ainda danificar o módulo ESP32, tenha cuidado e muita atenção para inserir as informações.


# Como Utilizar (resumo)
Após realizar a gravação do progrma no ESP32 e rebootar o módulo ele irá gerar uma rede wifi (modo AP) com o nome padrão default do módulo "esp32modularx Ponto de Acesso" a senha padrão é "senha12345678".<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/50d66af1-0918-4cfd-87c9-e04728b089dc)

Conecte-se na rede e pelo navegador você deve acessar o endereço "http://192.168.4.1:8080/wifiinicio". ao abrir a página informe o nome e senha da sua rede wifi, logo após salve as informações.<br>
![image](https://github.com/rede-analista/smcr/assets/66534023/bb87e3e0-50be-4dfb-96fe-4497856e6943)

Depois de salvar as informações o módulo irá reiniciar e conectar na sua rede wifi.<br>


Pelo navegador acesse o endereço "http://esp32modularx.local:8080", irá abrir a página inicial do módulo ESP32 e voce terá acesso as demais páginas de configuração.
![image](https://github.com/rede-analista/smcr/assets/66534023/13792da4-3303-49b6-9e79-091416084e11)



A informações default de hostname, porta, senha, etc. podem ser alteradas depois pela interface web. Caso queira alterar as informações no código antes de compilar/gravar elas podem ser encontradas no arquivo "funcoes.ino" nas linhas 495 a 498.
![image](https://github.com/rede-analista/smcr/assets/66534023/7ba3fe7a-30c6-4afc-a335-33dfb037514c)




