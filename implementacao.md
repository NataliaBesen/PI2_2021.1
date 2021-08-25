# Implementação

A etapa da implementação é o momento de materializar o que foi descrito anteriormente, nas etapas de concepção e design. A seguir, serão descritos os processos de fabricação da maquete, codificação, teste e validação de cada tarefa do sistema e integração do todo para obtenção dos resultados desejados. 

## Fabricação da maquete

Na etapa da concepção foi apresentada a planta baixa da casa em questão, baseando-se nela a maquete foi confeccionada. Para a construção da estrutura da casa foram utilizadas caixas de papelão e como base para a maquete uma placa de isopor. Além disso foram empregues outros materiais a fim de aprimorar a estética da casa, como EVAs e papel adesivo.

Alguns componentes estarão localizados nos cômodos da sala e cozinha, como o cooler e o sensor de gás, portanto para ser possível a visualização destes a casa possui um telhado removível. O arduino e matriz de contatos serão localizados na região da garagem e os fios de conexão levarão os componentes aos seus locais definidos.

(falar sobre mecanismo do portão)

(foto)


* [Monitor Serial](./Testes/monitor_serial.md)

## Tarefas realizadas pelo sistema

Para criação das tarefas é necessário integrar os componentes, que já foram testados individulamente na etapa anterior. Como diversas tarefas serão executadas repetidamente, há alguns cuidados a serem tomados para um funcionamento adequado do sistema, como por exemplo não utilizar funções que bloqueiem completamente o sistema que é o caso da função delay().  Além disso, certas tarefas não precisam ou não podem ser executadas a todo momento, sem um tempo de espera, por esses motivos algumas tarefas serão temporizadas.

Para exemplificar, a técnica de multitarefas que será utilizada, o código abaixo demostra como temporizar duas tarefas simples de piscar LED:



