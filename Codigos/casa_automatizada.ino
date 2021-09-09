/*
   casa_automatizada.ino
        Aplicação para automatizar uma maquete, utilizando sensores, LEDs e outros componentes.
        O controle da aplicação é feito via teclado.
        
                  Arduino Mega
                -----------------
            /|\|              A0 |- <-- MQ2
             | |              A1 |- <-- DHT
             --| RST          A2 |- <-- LDR
               |                 |
   LED1  <---  | D6              |
   LED2  <---  | D7              |        -+
   LED3  <---  | D8              |- <- Rx  -  Cabo USB     
   LED4  <---  | D9              |- -> Tx  -
   LED5  <---  | D10             |        -+
   LED6  <---  | D11             |
   LED7  <---  | D12             |
  SERVO  <---  | D3          D51 |- <-- PIR
  BUZZER <---  | D4              |
  COOLER <---  | D5              |
 
*/

/*Inclusão de bibliotecas necessárias*/
#include <Servo.h> // para uso de servomotores
#include "DHT.h"   // para uso de sensores DHT

/*Declaração da conexão dos componentes nos pinos*/
#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9
#define LED5 10
#define LED6 11
#define LED7 12
#define SERVO 3
#define BUZZER 4
#define COOLER 5


#define PIR    51   //sensor de presença
#define MQ2    A0   //sensor de gás
#define DHTPIN A1   //sensor de temperatura e umidade
#define LDR    A2   //sensor de luminosidade



#define DHTTYPE DHT11 // define modelo do sensor DHT como DHT 11

DHT dht(DHTPIN, DHTTYPE); //configura um sensor DHT com o modelo e o pino utilizado
Servo s;                  //define um objeto do tipo servo

/*variáveis globais*/
bool alarme = false;        //variavel para ligar e desligar o sistema de alarme
bool sistema_PIR = false;   //variavel para ligar e desligar o sistema PIR
bool sistema_cooler = false;//variavel para ligar e desligar o sistema de refrigeração
bool sistema_LDR = false;   //variavel para ligar e desligar o sistema de iluminação do jardim
bool portao = false;        //variavel para controlar se o portão abre ou fecha
int limite_gas = 320;     //definine valor máximo de gás (nível de gás normal)
int limite_luz = 700;     //define luminosidade limite para acender a luz do jardim
float limite_temp = 23;   //define temperatura limite para acionar ventilador

/*declaração das funções*/
void ler_comandos();
void ler_PIR (unsigned long tempo_atual);
void ler_DHT (unsigned long tempo_atual);
void ler_MQ2(unsigned long tempo_atual);
void ler_LDR(unsigned long tempo_atual);
void controle_portao (bool portao);
void status_sistema ();
void menu (); 

void setup() {

  /*Inicializa monitor serial*/
  Serial.begin(9600);

  /*Inicializa sensor DHT*/
  dht.begin();

  /*Inicializa servomotor*/
  s.attach(SERVO); //associa pino digital ao servo
  s.write(10);     //inicia o motor na posição 10°

  /*Inicializa pinos de entrada e saída*/
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(COOLER, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(PIR, INPUT);
  pinMode(MQ2, INPUT);


  /*Buzzer se inicia desligado*/
  digitalWrite(BUZZER, HIGH);

 /*Exibe o menu de comandos*/
  menu();
}

void loop() {

  unsigned long meu_tempo_atual = millis(); //variável utilizada para temporizar as tarefas

  /*Chama as funções de cada tarefa a ser executada*/
  ler_comandos();
  ler_PIR(meu_tempo_atual);
  ler_DHT(meu_tempo_atual);
  ler_MQ2(meu_tempo_atual);
  ler_LDR(meu_tempo_atual);

}

/*função para ler comandos do usuário, passados pelo teclado*/
void ler_comandos() {
  if (Serial.available() != 0)
  {
    char tecla;    //tecla digitada pelo usuário
    tecla = Serial.read();

    //Cada tecla realiza uma ação
    switch (tecla)
    {
      case '1':
        digitalWrite(LED1, !digitalRead(LED1));
        break;
      case '2':
        digitalWrite(LED2, !digitalRead(LED2));
        break;
      case '3':
        digitalWrite(LED3, !digitalRead(LED3));
        break;
      case '4':
        digitalWrite(LED4, !digitalRead(LED4));
        break;
      case '5':
        digitalWrite(LED5, !digitalRead(LED5));
        break;
      case '6':
        digitalWrite(LED6, !digitalRead(LED6));
        break;
      case '7':
        digitalWrite(LED7, !digitalRead(LED7));
        break;
      case 'a':
        alarme = !alarme;
        break;
      case 'p':
        sistema_PIR = !sistema_PIR;
        break;
      case 't':
        sistema_cooler = !sistema_cooler;
        digitalWrite(COOLER, LOW);
        break;
      case 'c':
        digitalWrite(COOLER, !digitalRead(COOLER));
        break;
      case 'l':
        sistema_LDR = !sistema_LDR;
        break;
      case 'm':
        portao = !portao;
        controle_portao (portao);
        break;
      case 's':
        status_sistema();
        break;
      case 'i':
        menu ();
        break;
      default:
        break;
    }
  }

}

/*Variáveis globais para temporizar a tarefa*/
const unsigned long periodo_ler_PIR = 1000;
unsigned long tempo_ler_PIR = millis();

/*  Verifica se o sensor PIR está ativado e controla LED e buzzer */
void ler_PIR (unsigned long tempo_atual)
{
  /*Inicia a função de leitura do PIR se o sistema estiver ligado*/
  if (sistema_PIR == true)
  {
    /* Verifica o sensor caso tenha passado o periodo de tempo definido */
    if (tempo_atual - tempo_ler_PIR > periodo_ler_PIR)
    {
      tempo_ler_PIR = tempo_atual;

      if ((digitalRead (PIR)) == HIGH) //Se houver movimento faz:
      {
        Serial.println("Alerta! Presença detectada");
        digitalWrite(LED6, HIGH);  //liga LED
        if (alarme == true)        //Se o sistema de alarme estiver ligado:
        { //liga buzzer
          for (int x = 180; x > 0; x--)
          {
            float seno;
            int frequencia;
            //converte graus para radiando e depois obtém o valor do seno
            seno = (sin(x * 3.1416 / 180));
            //gera uma frequência a partir do valor do seno
            //variando de 1000 a 2000 Hz
            frequencia = 1000 + (int(seno * 1000));
            tone(BUZZER, frequencia);
            delay(2);
          }
          noTone(BUZZER);             //Desliga buzzer
          digitalWrite(BUZZER, HIGH);
        }

      }
      else   //Se não houver movimento :
        digitalWrite(LED6, LOW);    //Desliga LED



    }
  }
}

/*Variáveis globais para temporizar a tarefa*/
const unsigned long periodo_ler_DHT = 10000;
unsigned long tempo_ler_DHT = millis();

/*Lê temperatura e umidade exibe para o usuário e liga ventilador*/
void ler_DHT(unsigned long tempo_atual)
{
  /* Verifica o sensor caso tenha passado o periodo de tempo definido */
  if (tempo_atual - tempo_ler_DHT > periodo_ler_DHT)
  {
    tempo_ler_DHT = tempo_atual;
    // A leitura da temperatura e umidade pode levar 250ms!
    // O atraso do sensor pode chegar a 2 segundos.
    float h = dht.readHumidity();    //Lê o valor da umidade
    float t = dht.readTemperature(); //Lê o valor da temperatura

    /* testa se retorno é valido, caso contrário algo está errado.*/
    if (isnan(t) || isnan(h))
    {
      Serial.println("Falha na leitura do DHT");
    }
    else
    {
      /*Exibe temperatura e umidade no monitor serial*/
      Serial.print("Umidade: ");
      Serial.print(h);
      Serial.print("% ");
      Serial.print(" Temperatura: ");
      Serial.print(t);
      Serial.println("ºC");
    }
    /*Se o sistema de refrigeração estiver ligado:*/
    if (sistema_cooler == true)
    {
      /*verifica se a temperatura for maior que o limite definido:*/
      if ((t > limite_temp))
        digitalWrite(COOLER, HIGH); //liga ventilador
      else
        digitalWrite(COOLER, LOW);  //desliga ventilador
    }

  }
}

/*Variáveis globais para temporizar a tarefa*/
const unsigned long periodo_ler_MQ2 = 5000;
unsigned long tempo_ler_MQ2 = millis();

/*Lê o sensor de gas exibe para o usuário e liga buzzer*/
void ler_MQ2(unsigned long tempo_atual)
{
  /* Verifica o sensor caso tenha passado o periodo de tempo definido */
  if (tempo_atual - tempo_ler_MQ2 > periodo_ler_MQ2)
  {
    tempo_ler_MQ2 = tempo_atual;
    int gas = analogRead(MQ2);           //variável que recebe o valor lido no pino analógico
    Serial.print("Quantidade de gás: ");
    Serial.println(gas);                 // Exibe o valor lido no monitor serial

    /*se o valor lido for maior que a quantidade limite de gás ativa o buzzer*/
    if (gas > limite_gas)
    {
      Serial.println("Cuidado! Nível de gás elevado");
      for (int x = 0; x < 180; x++)
      {
        float seno;
        int frequencia;
        //converte graus para radiando e depois obtém o valor do seno
        seno = (sin(x * 3.1416 / 180));
        //gera uma frequência a partir do valor do seno
        //variando de 1000 a 2000 Hz
        frequencia = 1000 + (int(seno * 1000));
        tone(BUZZER, frequencia);
        delay(2);
      }
      noTone(BUZZER);
      digitalWrite(BUZZER, HIGH);
    }
  }
}


/*Variáveis globais para temporizar a tarefa*/
const unsigned long periodo_ler_LDR = 5000;
unsigned long tempo_ler_LDR = millis();

/*Lê o sensor LDR e controla LED*/
void ler_LDR(unsigned long tempo_atual)
{
  /*Inicia a função de leitura do LDR se o sistema estiver ligado*/
  if (sistema_LDR == true)
  {
    /* Verifica o sensor caso tenha passado o periodo de tempo definido */
    if (tempo_atual - tempo_ler_LDR > periodo_ler_LDR)
    {

      tempo_ler_LDR = tempo_atual;
      int luminosidade = analogRead(LDR); //variável que recebe o valor lido no pino analógico
      Serial.print("Luminosidade: ");
      Serial.println(luminosidade);       //exibe o valor lido no monitor serial

      /*Se a luminosidade for menor que o limite definido acende o LED */
      if (luminosidade < limite_luz)
        digitalWrite(LED7, HIGH);

      else
        digitalWrite(LED7, LOW);

    }
  }
}

/*Abre e fecha o portão de acordo com a variável recebida*/
void controle_portao (bool c_portao)
{
  int pos; //posição do servo

  /*Abre o portão*/
  if (c_portao == true)
  {
    /*Varia o ângulo do motor de 10 a 140*/
    for (pos = 10; pos <= 90; pos++)
    {
      s.write(pos);
    }
  }
  /*Fecha o portão*/
  else if(c_portao == false)
  {
    /*Varia o ângulo do motor de 140 a 10*/
    for (pos = 90; pos >= 10; pos--)
    {
      s.write(pos);
    }
  }

}

/*Exibe no monitor serial o status de cada função do sistema*/
void status_sistema ()
{
  if (sistema_PIR == true)
  {
    Serial.println("Sistema de detecção de presença: ligado");
    if (alarme == true)
      Serial.println("Sistema de alarme: ligado");
    else
      Serial.println("Sistema de alarme: desligado");
  }
  else
  {
    Serial.println("Sistema de detecção de presença: desligado");
    Serial.println("Sistema de alarme: desligado");
  }

  if (sistema_cooler == true)
    Serial.println("Sistema de refrigeração: ligado");
  else
    Serial.println("Sistema de refrigeração: desligado");

  if (sistema_LDR == true)
    Serial.println("Sistema de iluminação do jardim: ligado");
  else
    Serial.println("Sistema de iluminação do jardim: desligado");

}

void menu()
{
  Serial.println("Menu de comandos: ");
  Serial.println("'1' - luz do quarto 2");
  Serial.println("'2' - luz do banheiro");
  Serial.println("'3' - luz do quarto 1");
  Serial.println("'4' - luz da cozinha");
  Serial.println("'5' - luz da sala");
  Serial.println("'6' - luz da varanda");
  Serial.println("'7' - luz do jardim");
  Serial.println("'a' - sistema de alarme");
  Serial.println("'p' - sensor de presença");
  Serial.println("'t' - sistema de refrigeração");
  Serial.println("'c' - cooler");
  Serial.println("'l' - sistema de iluminação do jardim");
  Serial.println("'m' - portão");
  Serial.println("'s' - status do sistema");
  Serial.println("'i' - menu de comandos");
}
