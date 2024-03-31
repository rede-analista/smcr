
## Informações do Inter Módulos

  - Parâmetro HABILITA INTER MÒDULOS
    - Habilita o envio de informações para um outro módulo pela rede wifi.<br>
      NOTA 1: Para habilitar esta opção os parâmetros referente aos módulos precisam ser informados.

  - Parâmetro TEMPO ENVIO RECEPTOR
    - Informe o tempo em milisegundos que a função de enviar informações à outro módulo será executada.

  - Parâmetro CICLOS HANDSHAKE
    - Informe o tempo em ciclos que um módulo ficará enviando informações entre eles, este valor é decrementado toda vez que a função "f_checkAcoesModulos()" é executada, se o módulo não receber nenhama informação durante um período este valor irá chegar a zero e irá colocar o status do pino 255 em 1(alto). Este processo pode ser usado parar gerar um alerta informando que houve perda de comunicação entra os módulos.

  - Parâmetro NOME / IP / ID-Pino_HandShake / Porta do Receptor
    - Informe o nome do módulo remoto, esta informação é usada apenas para validação quando receber dados de outro ESP. Se o nome do módulo que enviou a informação não for igual a um desses campos os dados serão descartados.<br>
    NOTA 2: Observe que em cada nome/ip de um módulo há um número de "ID", esse ID será usado na configuração das ações no campo "Envia_Módulo" no cadastro de ações que deve ser informado o ID correspondente ao módulo que irá receber a informação.<br>
    
    ![image](https://github.com/rede-analista/smcr/assets/66534023/36ed98f7-db92-4eed-8a08-e9e3062f0b47)

    No exemplo acima o módulo está configurado para aceitar informações de outros módulos que tenham os hostname "Medidor", "Aquario" ou "Gerador".<br>
    Estas informações tambem serão usadas caso queira enviar informações para outros módulos.<br><br>
    NOTA 3: Um módulo pode enviar e receber informações, ou seja, pode ser um transmissor e um receptor simultâneamente, basta efetuar este cadastro de nomes e IPs e configurar as ações com os ID que foram cadastrados nesta página.


  - Parâmetro IP
    - Informe o IP do módulo remoto, a placa que irá receber as informações.<br>
      NOTA 4: Deve ser usado o IP da sua rede usado pela placa que vai recebar a informação.

      O IP deve ser informado no seguinte formato: zzzzzzzzzzzz onde z são os valores em decimais de cada octeto que compõe o IP.<br>
      Quando for informado um IP deve sempre ser ter 3 dígitos em cada octeto sem digitar o .(ponto decimal), por exemplo, para o IP 10.10.1.7 o valor informado no campo deverá ser 010010001007 (010.010.001.007)

      Outro exemplo, se quiser informar o IP 192.168.100.7 deve ser difitado 192168100007


  - Parâmetro ID-Pino_HandShake
    - Informe um número entre 1 e 254, este será o ID do módulo remoto.<br>
      Esta informação será usada nas ações para informaqr para qual módulo deve ser enviado o valor do sensor.<br>
      Este ID também podeŕa ser usado para identificar perda de comunicação com o módulo remoto, para isto basta cadastrar um pino com o mesmo valor deste campo ID.


  - Parâmetro PORTA DO RECEPTOR
    - Informe a porta TCP(porta web) do módulo que irá receber as informações.

      Normalmente a placa que irá enviar as informações é considerada transmissora.<br>
      Normalmente a placa que irá receber as informações é considerada receptora.

      Para que a placa transmissora envie requisições de handshake o número da porta deve ser informado.<br<
      Para que a placa transmissora não envie requisições de handshake o número da porta deve ser 0 (zero).
      

- Se quiser salvar as informações na memória flash do ESP, na tela inicial clique em "Parâmetros", despois clique em "Salvar na Flash".<br>
  Responda "Sim" à pergunta e clique em "Salvar na Flash".<br>
  
  ![image](https://github.com/rede-analista/smcr/assets/66534023/2c82afff-a3c7-4ba4-ab7e-398530c743da)    

