
## Informações do Inter Módulos



  - Parâmetro HABILITA INTER MÒDULOS
    - Habilita o envio de informações para um outro módulo pela rede wifi.
    NOTA 1: Para habilitar esta opção os parâmetros referente aos módulos precisam ser informados.

  - Parâmetro NOME MÓDULO REMOTO
    - Informe o nome do módulo remoto, esta informação é usada apenas para validação quando receber dados de outro ESP. Se o nome do módulo que envioi a informação não for igual a este campo os dados serão descartados.<br>
    NOTA 2: Neste campo pode ser cadastrado uma lista separada por ,(vírgula), este recurso pode ser usado para que um módulo ESP possa receber informações de vários outros módulos como se fosse um concentrador(módulo central).<br>
    exemplo:<br>![image](https://github.com/rede-analista/smcr/assets/66534023/3046cd74-630f-4a8c-bc57-ef4d29d7f04a)
    No exemplo acima este módulo irá aceitar informações de outros módulos que tenha o hostname "Portao", "Medidor" ou "Gerador".

    - Parâmetro IP DO RECEPTOR
      - Informe o IP do módulo que irá receber as informações.

    - Parâmetro PORTA DO RECEPTOR
      - Informe a porta TCP(porta web) do módulo que irá receber as informações.

    - Parâmetro TEMPO ENVIO RECEPTOR
      - Informe o tem em milisegundos que a função de enviar informações à outro módulo será executada.
