# Testando o Servo 
O Servo MG995 utilizado pode girar até 180°, porém foi constatado nos testes que ao chegar no seu limite de ângulo ocorre uma trepidação que afeta seu funcionamento e pode sobrecarregar o Arduino. Portanto serão utilizados ângulos ligeiramente antes dos limites para evitar esse problema.

Para utilização de Servo Motores no Arduino, há uma biblioteca que deve ser incluída e que permite controla-los de forma simples enviando o ângulo desejado por meio de uma função.

### Montagem do circuito


### Código

~~~C
#include <Servo.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA

const int pinoServo = 9; //PINO DIGITAL UTILIZADO PELO SERVO

Servo s; //OBJETO DO TIPO SERVO
int pos; //POSIÇÃO DO SERVO

void setup () {
  delay(5000);
  s.attach(pinoServo); //ASSOCIAÇÃO DO PINO DIGITAL AO OBJETO DO TIPO SERVO
  s.write(0); //INICIA O MOTOR NA POSIÇÃO 0º
}
void loop() {
  for (pos = 10; pos <= 160; pos++) { //PARA "pos" IGUAL A 10, ENQUANTO "pos" MENOR QUE 160, INCREMENTA "pos"
    s.write(pos); //ESCREVE O VALOR DA POSIÇÃO QUE O SERVO DEVE GIRAR
    delay(50); //INTERVALO DE 15 MILISSEGUNDOS
  }
  delay(1000); //INTERVALO DE 1 SEGUNDO
  for (pos = 160; pos >= 10; pos--) { //PARA "pos" IGUAL A 160, ENQUANTO "pos" MAIOR OU IGUAL QUE 10, DECREMENTA "pos"
    s.write(pos); //ESCREVE O VALOR DA POSIÇÃO QUE O SERVO DEVE GIRAR
    delay(50); //INTERVALO DE 15 MILISSEGUNDOS
  }

}
~~~
