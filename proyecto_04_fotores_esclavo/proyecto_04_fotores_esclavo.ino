#include <Wire.h>

int iLectura_ADC;
int pinAnalogico = 0;

void solicitarEvento()
{
  iLectura_ADC = analogRead(pinAnalogico);
  
  Serial.println(iLectura_ADC);
  Wire.println(iLectura_ADC);
}

void setup() 
{
  Serial.begin(9600);
  Wire.begin(11);

  Wire.onRequest(solicitarEvento);
}

void loop() 
{  
  delay(500);
}
