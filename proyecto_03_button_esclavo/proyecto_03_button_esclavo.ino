#include <Wire.h>

int pinDigital = 11;

void solicitarEvento()
{
  char estadoLogico;

  if (digitalRead(pinDigital))
  {
    estadoLogico = '1';
  }
  else 
  {
    estadoLogico = '0';
  }
  Serial.println(estadoLogico);
  Wire.println(estadoLogico);
}

void setup() 
{
  Wire.begin(11);
  Serial.begin(9600);
  
  Wire.onRequest(solicitarEvento);

  pinMode(pinDigital, INPUT);
}

void loop() 
{
  delay(500);
}
