
## Informações do Inter Módulos



  - Parâmetro HABILITA INTER MÒDULOS
    - Habilita o envio de informações para um outro módulo pela rede wifi.<br>
    NOTA 1: Para habilitar esta opção os parâmetros referente aos módulos precisam ser informados.

  - Parâmetro PORTA DO RECEPTOR
    - Informe a porta TCP(porta web) do módulo que irá receber as informações.

  - Parâmetro TEMPO ENVIO RECEPTOR
    - Informe o tem em milisegundos que a função de enviar informações à outro módulo será executada.

  - Parâmetro NOME
    - Informe o nome do módulo remoto, esta informação é usada apenas para validação quando receber dados de outro ESP. Se o nome do módulo que enviou a informação não for igual a um desses campos os dados serão descartados.<br>
    NOTA 2: Observer que em cada nome/ip de um módulo há um número de "ID", esse ID será usado na configuração das ações no campo "Envia Receptor" lá no cadastro de ações deve ser informado o ID correspondente ao módulo que irá receber a informação.<br>
    
    exemplo:<br>![image](https://github.com/rede-analista/smcr/assets/66534023/1d3faffa-bafb-4e6f-833f-fe74bfebf5af)

    No exemplo acima este módulo irá aceitar informações de outros módulos que tenha o hostname "Medidor", "Aquario" ou "Gerador".
