# Configurações Gerais

- Nas configurações gerais devem ser cadastrados informações diversas para uso de notificações e comunicação entre módulos.<br>

- Você pode configurar as ações, para isto clique na opção "Configurarões Gerais"na página inicial.<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/958fc6ce-0156-463d-8f22-1f67ae2545e8)


- Parâmetro HABILITAR MODO AP
  - Você pode desabilitar o modo AP. O modo AP é um recurso que o ESP32 gera uma rede wifi caso ele não consiga conexão no SSID de trabalho. [Veja Modo AP](rede.md)

- Parâmetro HABILITA RECEPTOR
  - Habilita o envio de informações para um outro módulo pela rede wifi.
    NOTA 1: Para habilitar esta opção os parâmetros referente ao receptor precisam ser informados.

- Parâmetro NOME MÓDULO REMOTO
  - Informe o nome do módulo remoto, esta informação é usada apenas para validação quando receber dados de outro ESP. Se o nome do módulo que envioi a informação não for igual a este campo os dados serão descartados.<br>
    NOTA 2: Neste campo pode ser cadastrado uma lista separada por ,(vírgula), este recurso pode ser usado para que um módulo ESP possa receber informações de vários outros módulos como se fosse um concentrador(módulo central).<br>

- Parâmetro IP DO RECEPTOR
  - Informe o IP do módulo que irá receber as informações.
