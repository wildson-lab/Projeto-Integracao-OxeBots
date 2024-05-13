/*
Este sketch contém o código utilizado no Arduino Controlador (escravo), 
unidade responsável pelo monitoramento e controle individual das luminárias,
e envio dos dados para um Concentrador.
*/


#include <Arduino.h>

#define PINO_LED 13
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

void setup() {
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_INTERRUPT_FOTO, INPUT);
  pinMode(PINO_INTERRUPT_SENSORES, INPUT);
  attachInterrupt(digitalPinToInterrupt(PINO_INTERRUPT_SENSORES), ISR_Sensores, CHANGE);
}

void loop(){

}
