/*
Este sketch contém o código utilizado no Arduino Controlador (escravo), 
unidade responsável pelo monitoramento e controle individual das luminárias,
e envio dos dados para um Concentrador.
*/


#include <Arduino.h>

#define PINO_LED 13

void setup() {
  pinMode(PINO_LED, OUTPUT);
}

void loop() {
  digitalWrite(PINO_LED, HIGH);
  delay(1000);
  digitalWrite(PINO_LED, LOW);
  delay(1000);
}
