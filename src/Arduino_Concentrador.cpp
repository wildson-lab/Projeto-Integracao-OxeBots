/*
Este sketch contém o código utilizado no Arduino Concentrador (mestre), 
responsável por agregar os dados fornecidos pelos Controladores (escravos).
*/

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h>

// Endereçamento de pinos
#define PINO_INTERRUPT_BOTAO 2
#define PINO_TELA_D4 4
#define PINO_TELA_D5 5
#define PINO_TELA_D6 6
#define PINO_TELA_D7 7
#define PINO_TELA_EN 8
#define PINO_TELA_RS 9

// Variáveis
int n_poste;
double tensao;
double corrente;
double temperatura;
bool status_foto;

// Instâncias de objetos
LiquidCrystal lcd(PINO_TELA_RS, PINO_TELA_EN, PINO_TELA_D4, PINO_TELA_D5, PINO_TELA_D6, PINO_TELA_D7);

// Protótipos de funções
void ISR_Botao_pressionado();
void mostra_dados();


void setup() {
  attachInterrupt(digitalPinToInterrupt(PINO_INTERRUPT_BOTAO), ISR_Botao_pressionado, FALLING);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  lcd.begin(20, 4);
  n_poste = 1;
}

void loop() {
  if (n_poste > 2){
    n_poste = 1;
  }

  if (n_poste == 1){
    if (Serial1.available() > 0){
      StaticJsonDocument<300> doc;
      DeserializationError err = deserializeJson(doc, Serial1);
      if (err == DeserializationError::Ok){
        tensao = doc["tensao"].as<double>();
        corrente = doc["corr"].as<double>();
        temperatura = doc["temp"].as<double>();
        status_foto = doc["foto"].as<bool>();
        Serial.println(tensao);
        Serial.println(corrente);
        Serial.println(temperatura);
        Serial.println(status_foto);
        mostra_dados();
      }
    }
  }

  else if (n_poste == 2){
    if (Serial2.available() > 0){
      StaticJsonDocument<300> doc;
      DeserializationError err = deserializeJson(doc, Serial2);
      if (err == DeserializationError::Ok){
        tensao = doc["tensao"].as<double>();
        corrente = doc["corr"].as<double>();
        temperatura = doc["temp"].as<double>();
        status_foto = doc["foto"].as<bool>();
        Serial.println(tensao);
        Serial.println(corrente);
        Serial.println(temperatura);
        Serial.println(status_foto);
        mostra_dados();
      }
    }
  }
}



/// @brief Mostra os dados obtidos no display LCD.
void mostra_dados(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tensao:");
  lcd.setCursor(9, 0);
  lcd.print(tensao);
  lcd.setCursor(15, 0);
  lcd.print("V");
  
  lcd.setCursor(0, 1);
  lcd.print("Corr.:");
  lcd.setCursor(9, 1);
  lcd.print(corrente);
  lcd.setCursor(15, 1);
  lcd.print("A");
  
  lcd.setCursor(0, 2);
  lcd.print("Temp.:");
  lcd.setCursor(9, 2);
  lcd.print(temperatura);
  lcd.setCursor(15, 2);
  lcd.print("C");
  
  lcd.setCursor(0, 3);
  lcd.print("Foto:");
  if (status_foto == true){
    lcd.setCursor(14, 3);
    lcd.print("ON");
  }
  else {
    lcd.setCursor(13, 3);
    lcd.print("OFF");
  }

  lcd.setCursor(19, 1);
  lcd.print("P");
  lcd.setCursor(19, 2);
  lcd.print(n_poste);
}

/// @brief Função acionada quando o botão para alternar é disparado.
void ISR_Botao_pressionado(){
  n_poste += 1;
}