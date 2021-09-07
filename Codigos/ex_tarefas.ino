/*
   ex_tarefas.ino

        Aplicação exemplo com várias tarefas:
          - Piscar o LED 1 a cada 1 segundo.
          - Piscar o LED 2 a cada 300 milisegundos.
          
                  Arduino Mega
                -----------------
            /|\|                 |
             | |                 |
             --| RST             |
               |                 |        -+
  LED_2  <---  | D11             |- <- Rx  -  Cabo USB
  LED_1  <---  | D12             |- -> Tx  -
               |                 |        -+
               |                 |

*/

#define LED_1 12
#define LED_2 11


/* Função SETUP é executa apenas uma vez
   ela é responsável pela configuração dos
   pinos do Arduino */
void setup() {

  /* Configuração dos pinos como saída */
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

}

/* Variáveis globais para temporiazar a tarefa_1*/
const unsigned long periodo_tarefa_1 = 1000;
unsigned long tempo_tarefa_1 = millis();
int estado_LED1 = LOW;

/* Tarefa 1: pisca o LED a cada 1 segundo */
void tarefa_1(unsigned long tempo_atual) {

  /* Hora de piscar o led caso tenha passado 1000 ms */
  if (tempo_atual - tempo_tarefa_1 > periodo_tarefa_1) {

    tempo_tarefa_1 = tempo_atual;

    digitalWrite(LED_1, !digitalRead(LED_1));
  }
}

const unsigned long periodo_tarefa_2 = 300;
unsigned long tempo_tarefa_2 = millis();
/* Tarefa 1: pisca o LED a cada 300ms*/
void tarefa_2(unsigned long tempo_atual) {

  /* Hora de piscar o led caso tenha passado 1000 ms */
  if (tempo_atual - tempo_tarefa_2 > periodo_tarefa_2) {

    tempo_tarefa_2 = tempo_atual;

    digitalWrite(LED_2, !digitalRead(LED_2));
  }

}
/* Função loop() é responsável por escalonar as tarefas.
   Essa função é executada repetidamente */
void loop() {

  unsigned long meu_tempo_atual = millis();

  tarefa_1(meu_tempo_atual);

  tarefa_2(meu_tempo_atual);

}
