#include <Wire.h>

String cadenaRecibida;

String LecturaI2C(int iEsclavo, int iBytes)
{
  char byteSolicitado;
  String cadenaBytes = "";

  Wire.requestFrom(iEsclavo, iBytes);

  while (Wire.available())
  {
    byteSolicitado = Wire.read();
    cadenaBytes += byteSolicitado; 
  }
  return cadenaBytes;
}

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
}

void loop() 
{
  for (int i = 9; i <= 17; i++)
  {
    cadenaRecibida = LecturaI2C(i, 4);
    Serial.print("Lectura Esclavo " + String(i) + ": " + cadenaRecibida + "\n");

    delay(500);
  }
  Serial.print("\n");
}
