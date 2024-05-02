/*
Este sketch contém o código utilizado no Arduino Concentrador (mestre), 
responsável por agregar os dados fornecidos pelos Controladores (escravos).
*/

#include <Arduino.h>

#define PINO_LED 13

void setup() {
  pinMode(PINO_LED, OUTPUT);
}

void loop() {
  digitalWrite(PINO_LED, HIGH);
  delay(250);
  digitalWrite(PINO_LED, LOW);
  delay(250);
}
