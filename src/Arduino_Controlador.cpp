/*
Este sketch contém o código utilizado no Arduino Controlador (escravo), 
unidade responsável pelo monitoramento e controle individual das luminárias,
e envio dos dados para um Concentrador.
*/


#include <Arduino.h>

#define PINO_LED 13
#define PINO_SENSOR_TENSAO A0
#define PINO_SENSOR_TEMPERATURA A1
#define PINO_SENSOR_CORRENTE A2
#define PINO_INTERRUPT_FOTO 2
#define PINO_INTERRUPT_SENSORES 3

volatile bool acionado_interrupt_foto = false;
volatile bool acionado_interrupt_sensor = false;

double tensao;
double corrente;
double temperatura;
bool estado_rele;


void ISR_Sensores(){
  digitalWrite(PINO_LED, digitalRead(PINO_INTERRUPT_SENSORES));
}


double leitura_tensao(){
  double valor_bruto = analogRead(PINO_SENSOR_TENSAO);
  double valor_convertido = (valor_bruto * 5.0) / 1023.0 ;
  return valor_convertido;
}

double leitura_temperatura(){
  int valor_bruto = analogRead(PINO_SENSOR_TEMPERATURA);
  double valor_convertido = 100 * (valor_bruto * 5.0) / 1023.0 ;
  return valor_convertido;
}

double leitura_corrente(){
  double valor_bruto = analogRead(PINO_SENSOR_CORRENTE);
  double valor_convertido = 10 * (((valor_bruto * 5.0) / 1023.0) - 2.5);
  return valor_convertido;
}


void setup() {
  Serial.begin(9600);
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_INTERRUPT_FOTO, INPUT);
  pinMode(PINO_INTERRUPT_SENSORES, INPUT);
  attachInterrupt(digitalPinToInterrupt(PINO_INTERRUPT_SENSORES), ISR_Sensores, CHANGE);
}

void loop(){
  tensao = leitura_tensao();
  temperatura = leitura_temperatura();
  corrente = leitura_corrente();

  Serial.print(tensao);  
  Serial.print(", ");
  Serial.print(corrente);
  Serial.print(", ");
  Serial.print(temperatura);
  Serial.print(", ");
  Serial.println(estado_rele);
  delay(1000);
}
