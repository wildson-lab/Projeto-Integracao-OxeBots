/*
Este sketch contém o código utilizado no Arduino Controlador (escravo), 
unidade responsável pelo monitoramento e controle individual das luminárias,
e envio dos dados para um Concentrador.
*/


#include <Arduino.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h>

// Endereçamento de pinos
#define PINO_SENSOR_TENSAO A0
#define PINO_SENSOR_TEMPERATURA A1
#define PINO_SENSOR_CORRENTE A2
#define PINO_FOTOSENSOR 2
#define PINO_INTERRUPT_SENSORES 3
#define PINO_TELA_D4 4
#define PINO_TELA_D5 5
#define PINO_TELA_D6 6
#define PINO_TELA_D7 7
#define PINO_TELA_EN 8
#define PINO_TELA_RS 9
#define PINO_LED 13


// Variáveis globais
double tensao;
double corrente;
double temperatura;
bool estado_foto;


// Instâncias de bibliotecas
LiquidCrystal lcd(PINO_TELA_RS, PINO_TELA_EN, PINO_TELA_D4, PINO_TELA_D5, PINO_TELA_D6, PINO_TELA_D7);


// Protótipos de Funções

double leitura_tensao();
double leitura_corrente();
double leitura_temperatura();
void ISR_Sensores();
void mostra_dados();
void envia_dados();


void setup() {
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_FOTOSENSOR, INPUT);
  pinMode(PINO_INTERRUPT_SENSORES, INPUT);
  attachInterrupt(digitalPinToInterrupt(PINO_INTERRUPT_SENSORES), ISR_Sensores, CHANGE);
  Serial.begin(9600);
  lcd.begin(16, 4);
}


void loop(){
  tensao = leitura_tensao();
  temperatura = leitura_temperatura();
  corrente = leitura_corrente();
  estado_foto = !digitalRead(PINO_FOTOSENSOR);

  mostra_dados();
  envia_dados();
  delay(3000);
}


/// @brief Realiza leitura de tensão obtida pelo sensor
/// @return Um double, com o valor da tensão (em Volts)
double leitura_tensao(){
  double valor_bruto = analogRead(PINO_SENSOR_TENSAO);
  double valor_convertido = (valor_bruto * 5.0) / 1023.0 ;
  return valor_convertido;
}


/// @brief Realiza leitura de temperatura obtida pelo sensor
/// @return Um double, com o valor da temperatura (em graus Celsuis)
double leitura_temperatura(){
  int valor_bruto = analogRead(PINO_SENSOR_TEMPERATURA);
  double valor_convertido = 100 * (valor_bruto * 5.0) / 1023.0 ;
  return valor_convertido;
}


/// @brief Realiza leitura de corrente obtida pelo sensor
/// @return Um double, com o valor da corrente (em Amperes)
double leitura_corrente(){
  double valor_bruto = analogRead(PINO_SENSOR_CORRENTE);
  double valor_convertido = 10 * (((valor_bruto * 5.0) / 1023.0) - 2.5);
  return valor_convertido;
}


/// @brief Função executada quando a interrupção é acionada.
void ISR_Sensores(){
  digitalWrite(PINO_LED, digitalRead(PINO_INTERRUPT_SENSORES));
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
  if (estado_foto == true){
    lcd.setCursor(14, 3);
    lcd.print("ON");
  }
  else {
    lcd.setCursor(13, 3);
    lcd.print("OFF");
  }
}


/// @brief Envia os dados obtidos dos sensores por serial
void envia_dados(){
  // Serial.print(tensao);  
  // Serial.print(", ");
  // Serial.print(corrente);
  // Serial.print(", ");
  // Serial.print(temperatura);
  // Serial.print(", ");
  // Serial.println(estado_foto);
  StaticJsonDocument<200> doc;
  doc["tensao"] = tensao;
  doc["corr"] = corrente;
  doc["temp"] = temperatura;
  doc["foto"] = estado_foto;
  serializeJson(doc, Serial);
}