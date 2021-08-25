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

* [Exemplo tarefas](./Codigos/ex_tarefas.ino)

Uma ferramente que será muito importante para o sistema é o monitor serial, pois ele torna possível transmitir ou ler informações na forma de texto. Ele será fundamental para a construção do projeto, pois por meio dele será feita a comunicação com o usuário, exibindo dados e mensagem sobre o sistema na tela do computador e recebendo via teclado todos os comandos para executar tarefas. Para exemplificar o seu funcionamento foi criada uma aplicação para acender e apagar 3 LEDs utilizando os números de 1 a 3 do teclado. Cada LED muda seu estado atual quando for enviado o número correspondente a ele para o Monitor Serial:

* [Exemplo Monitor Serial](./Codigos/ex_serial.ino)

### Leitura do sensor de presença

Essa tarefa é responsável por ler o sensor PIR e caso seja detectada presença ela é responsável por acender um LED, ligar o alarme e enviar uma mensagem para o monitor serial. O alarme pode ser desligado e ligado via teclado, assim como toda a tarefa também. Essa tarefa é temporizada e é declada da seguinte forma:

~~~C
void ler_PIR (unsigned long tempo_atual)
~~~

