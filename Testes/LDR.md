# Testando sensor de luminosidade

### Montagem do circuito


### Código

~~~C
#define LDR  A2  //Pino digital onde está o LDR             
                      
 
void setup()
{
 Serial.begin(9600); //Inicializa o monitor serial     
}
 
void loop()
{
  //Lê o valor no pino analógico e armazena na variável
  int valorLuz = analogRead(LDR);
  //Exibe no monitor serial a menasagem     
  Serial.println("Luminosidade:");
  //Exibe o valor lido no monitor serial   
  Serial.println(valorLuz);
  //Intervalo de 1s
  delay(1000);                   
}
~~~
