# Implementação

A etapa da implementação é o momento de materializar o que foi descrito anteriormente, nas etapas de concepção e design. A seguir, serão descritos os processos de fabricação da maquete, codificação, teste e validação de cada tarefa do sistema e integração do todo para obtenção dos resultados desejados. 

## Fabricação da maquete

Na etapa da concepção foi apresentada a planta baixa da casa em questão, baseando-se nela a maquete foi confeccionada. Para a construção da estrutura da casa foram utilizadas caixas de papelão e como base para a maquete uma placa de isopor. Além disso foram empregues outros materiais a fim de aprimorar a estética da casa, como EVAs e papel adesivo.

Alguns componentes estarão localizados nos cômodos da sala e cozinha, como o cooler e o sensor de gás, portanto para ser possível a visualização destes a casa possui um telhado removível. O arduino e matriz de contatos serão localizados na região da garagem e os fios de conexão levarão os componentes aos seus locais definidos.


![Maquete](./Imagens/fabricacao_maquete.png)

## Tarefas realizadas pelo sistema

Para criação das tarefas é necessário integrar os componentes, que já foram testados individulamente na etapa anterior. Como diversas tarefas serão executadas repetidamente, há alguns cuidados a serem tomados para um funcionamento adequado do sistema, como por exemplo não utilizar funções que bloqueiem completamente o sistema que é o caso da função delay().  Além disso, certas tarefas não precisam ou não podem ser executadas a todo momento, sem um tempo de espera, por esses motivos algumas tarefas serão temporizadas.

Para exemplificar, a técnica de multitarefas que será utilizada, o código abaixo demostra como temporizar duas tarefas simples de piscar LED:

* [Exemplo tarefas](./Codigos/ex_tarefas.ino)

Uma ferramente que será muito importante para o sistema é o monitor serial, pois ele torna possível transmitir ou ler informações na forma de texto. Ele será fundamental para a construção do projeto, pois por meio dele será feita a comunicação com o usuário, exibindo dados e mensagem sobre o sistema na tela do computador e recebendo via teclado todos os comandos para executar tarefas. Para exemplificar o seu funcionamento foi criada uma aplicação para acender e apagar 3 LEDs utilizando os números de 1 a 3 do teclado. Cada LED muda seu estado atual quando for enviado o número correspondente a ele para o Monitor Serial:

* [Exemplo Monitor Serial](./Codigos/ex_serial.ino)

### Leitura do sensor de presença

Essa tarefa faz a leitura do sensor PIR e caso seja detectada presença ela é responsável por acender um LED, ligar o alarme e enviar uma mensagem para o monitor serial. O alarme pode ser desligado e ligado via teclado, assim como toda a tarefa. Essa tarefa é temporizada e é declarada da seguinte forma:

~~~ C
void ler_PIR (unsigned long tempo_atual)
~~~

### Leitura do sensor de gás

Faz a leitura do sensor de gás e exibe o valor lido no monitor serial, quando esse valor atingir o limite máximo estipulado o alarme é ligado e uma mensagem é exibida no monitor serial. Essa função também é temporizada e é declarada como:

~~~ C
void ler_MQ2(unsigned long tempo_atual) 
~~~

### Leitura do sensor de temperatura e umidade

Função temporizada responsável por ler os valores de temperatura e umidade e exibi-los no monitor serial, além disso quando a temperatura atinge um limite definido o cooler é acionado. O sistema de refrigeração com cooler pode ser ligado e desligado via teclado. A declaração desse tarefa é:

~~~ C
void ler_DHT(unsigned long tempo_atual)
~~~

### Leitura do sensor de luminosidade 

A leitura temporizada do LDR é feita por essa tarefa, o valor lido pela por porta analógica é exibido no monitor serial e controla a iluminação do jardim. Quando a luminosidade for baixa, de acordo com um valor limite estipulado, um LED verde será aceso e quando a luminosidade for alta o LED apagará. Esse sistema de iluminação pode ser desligado e ligado por meio do teclado e a função para ela é:

~~~ C
void ler_LDR(unsigned long tempo_atual)
~~~ 

### Controle do portão

Essa é uma função não temporizada e ela é executada somente quando o usuário envia um comando pelo teclado. Ela é responsável por girar o motor de 10° a 90° e em seguida quando o usuário apertar novamente a tecla destinada ao portão o motor irá retornar para a posição 0°. A funçao é declarada da forma exibida a seguir e a variável booleana que ela recebe indica qual movimento o motor deve fazer, icrementar ou decrementar o ângulo.

~~~ C
void controle_portao (bool portao)
~~~

### Exibir status do sistema

Essa função é responsável por exibir no monitor serial se os sistemas dos sensores estão ligados ou desligados, ela só é executada quando o usuário evia um comando via teclado. A sua declaração é:

~~~ C
void status_sistema ()
~~~

### Ler comandos do teclado 

E por fim essa tarefa que é muito importante para o sistema, ela é encarregada de ler as teclas enviadas pelo teclado e realizar a sua respectiva ação. A função não é temporizada e ela só será inteiramente executada quando algo for enviado pelo monitor serial. As teclas são usadas para controlar os LEDs, o portão e o cooler, além disso há teclas para ligar e desligar partes do sistema e uma tecla para exibir o status do sistema. A declaração da função é:

~~~ C
void ler_comandos()
~~~

# Integração do projeto

Integrar as tarefas e funções do código é feito de forma muito simples, primeiramente são declarados todos os pinos onde estão conectados os componentes, variáveis globais e funções e em seguida na função setup() é realizada a inicialização de todo o sistema. Na função loop() são chamadas todas as tarefas temporizadas e a função ler_comandos() de acordo com o exemplo de multitarefas mostrado anteriormente. O resultado final do código do sistema pode ser visualizado no link abaixo:

* [Código completo casa automatizada](./Codigos/casa_automatizada.ino)

![Maquete integrada](./Imagens/integracao_maquete.png)


