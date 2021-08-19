## Testando LEDs

Acender LEDs é o primeiro passo para entender o funcionamento do arduíno e funções básicas como pinMode e digitalWrite. Inicialmente, será exibido a montagem do circuito e o código para uma aplicação simples de pisca LED.


~~~
#define LED 2  //define o pino digital em que o LED está conectado

/*A função setup é utilizada para inicializaçãoe é executada apenas uma vez*/ 
void setup() 
{
  pinMode(LED, OUTPUT); //inicializa o pino em que o LED está como saída 

}

/*A função loop é executada repetidamente*/ 
void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);   // liga o LED
  delay(1000);                       // espera por 1s
  digitalWrite(LED_BUILTIN, LOW);    // desliga o LED
  delay(1000);                       // espera por 1s
}
~~~

