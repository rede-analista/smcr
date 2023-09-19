# Exemplo de Cadastro de Pinos

- Como exemplo pode cadastrar dois pinos, um como saída e outro como entrada, eles serão usados para demonstração das ações.<br>
  - Nome: Alerta Sala
    - Pino: 2 (físico)
    - Tipo: 1 (digital)
    - Modo: 3 (output)

  - Nome: Porta da Sala
    - Pino: 4 (físico)
    - Tipo: 1 (digital)
    - Modo: 5 (input_pullup)
    - 
  ![image](https://github.com/rede-analista/smcr/assets/66534023/d03310b3-59b5-4cf5-beaa-2a889c3a1f59)

- Depois de preencher as informações clique em "Aplicar(sem salvar)".<br>
  Esta ação cadastra os dois pinos porém não salva as informações da flash do ESP. Se o módulo for reiniciado antes de salvar as informações serão perdidas.<br>

- Observe na páfgina inicial que já mostra as informações dos pinos cadastrados.
  
  ![image](https://github.com/rede-analista/smcr/assets/66534023/4a6c5b21-e935-4351-a6a8-fbbf604964a9)

  Se houver mudança do status do pino 4 (cadastrado como entrada) poderá ser visto na linha Status da tabela na página inicial.<br>

  ![image](https://github.com/rede-analista/smcr/assets/66534023/dd1b8748-42df-4043-baec-efe1a665ef61)

- Se quiser salvar as informações na memória flash do ESP, na tela inicial clique em "Parâmetros", despois clique em "Salvar na Flash".<br>
  Responda "Sim" à pergunta e clique em "Salvar na Flash".<br>
  
  ![image](https://github.com/rede-analista/smcr/assets/66534023/2c82afff-a3c7-4ba4-ab7e-398530c743da)

