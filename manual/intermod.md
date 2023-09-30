
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
    NOTA 2: Observer que em cada nome/ip de um módulo há um número de "ID", esse ID será usado na configuração das ações no campo "Envia_Módulo", lá no cadastro de ações deve ser informado o ID correspondente ao módulo que irá receber a informação.<br>
    
    ![image](https://github.com/rede-analista/smcr/assets/66534023/36ed98f7-db92-4eed-8a08-e9e3062f0b47)

    No exemplo acima o módulo está copnfigurado para aceitar informações de outros módulos que tenha o hostname "Medidor", "Aquario" ou "Gerador".<br>

- Se quiser salvar as informações na memória flash do ESP, na tela inicial clique em "Parâmetros", despois clique em "Salvar na Flash".<br>
  Responda "Sim" à pergunta e clique em "Salvar na Flash".<br>
  
  ![image](https://github.com/rede-analista/smcr/assets/66534023/2c82afff-a3c7-4ba4-ab7e-398530c743da)    
