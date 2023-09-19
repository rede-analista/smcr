#Configurações dos pinos

- Você pode configurar os pinos do módulo, para isto clique na opção "Configurar Pinos"na página inicial.<br>
  ![image](https://github.com/rede-analista/smcr/assets/66534023/958fc6ce-0156-463d-8f22-1f67ae2545e8)


- Será aberta a página com todas as informações de todos os pinos. Nesta página tem um total de 23 posições para configurações dos pinos, o cadastro dos pinos pode ser realizada em qualquer posição.
![image](https://github.com/rede-analista/smcr/assets/66534023/bb235d1f-7a1e-4ae1-b241-365aa2c5fed3)

NOTA 1: Para não limitar a configuração dos pinos não há uma validação de quais pinos podem ser usados, consulte a informações de pinout do ESP32 para identificar pinos reservados e que não devem ser configurações nesta página.<br>
NOTA 2: Após configurar e clicar no botão "Aplicar" as configurações já estarão sendo usadas pelo módulo mas não estarão salvas na flash. Isto pode ser usado para testar uma configuração sem perder a configuração que está salva na flash.<br>
NOTA 3: Se o módulo for reiniciado antes de salvar as informações na flash todas as configurações serão perdidas.<br>

- Parâmetro NOME
  - É uma nomenclatura para facilitar na identificação dos pinos, um nome curto, este nome será usado na caso de notificações.
  
- Parâmetro PINO
  - É a informação do pino físico do ESP32, aqui será feito a associação do pino físico na placa ESP.<br>
    Esta informação será usada na configuração de Ações(eventos).
  
- Parâmetro TIPO
  - É o tipo que o pino será configurado na função pinMode(). Se o valor 254 for configurado, o módulo não irá realizar a atualização de status do pino, esta configuração deve ser usada quando for habilitado o recurso de "Inter Módulos".<br>
    O recurso de Inter Módulos ativa a comunicação entre dois ou mais módulos ESP32 onde um módulo transmissor iŕa atualizar o status de um pino no módulo receptor.<br>
