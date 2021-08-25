# Testando o Servo 
O Servo MG995 utilizado pode girar 180°, porém foi constatado nos testes que ao chegar no seu limite de ângulo ocorre uma trepidação que afeta seu funcionamento e pode sobrecarregar o Arduino. Portanto serão utilizados ângulos ligeiramente antes dos limites para evitar esse problema.

Para utilização de Servo Motores no Arduino, há uma biblioteca que deve ser incluída e que permite controlá-los de forma simples, enviando o ângulo desejado por meio de uma função.

### Montagem do circuito
 
 ![Servo](../Imagens/servo.PNG)

### Código

~~~C
#include <Servo.h> //Inclusão da bibliotéca necessária

#define SERVO 9 //Pino digital utilizado pelo servo

Servo s; //Objeto do tipo servo
int pos; //Posição do servo

void setup () {
  delay(5000);
  s.attach(SERVO); //Associação do pino digital ao objeto do tipo servo
  s.write(0); //Inicia o motor na posição 0°
}
void loop() {
 /*Incrementa a variável "pos" de 10 a 160*/
  for (pos = 10; pos <= 160; pos++) { 
    s.write(pos); //Escreve o valor da posição que o servo deve girar
    delay(50); //Intervalo de 15ms
  }
  delay(1000); //Intervalo de 1s
  /*Decrementa a variável "pos" de 160 a 10*/
  for (pos = 160; pos >= 10; pos--) { 
    s.write(pos); //Escreve o valor da posição que o servo deve girar
    delay(50); //Intervalo de 15ms
  }

}
~~~
