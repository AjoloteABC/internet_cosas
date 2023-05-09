// Incluir la biblioteca para utilizar el puerto I2C o en su defecto el puerto SPI
#include <Wire.h>

String cadenaRecibida;

String LecturaI2C(int iEsclavo, int iBytes)
{
  char byteSolicitado;
  String cadenaBytes = "";

  // No. del nodo esclavo y no. de bytes a recibir
  Wire.requestFrom(iEsclavo, iBytes);

  // Mientras el buffer del nodo esclavo paar leer
  while (Wire.available())
  {
    byteSolicitado = Wire.read();
    cadenaBytes += byteSolicitado; 
  }
  return cadenaBytes;
}

void setup() 
{
  // Inicializamos el módulo Wire (la conexión a I2C)
  // Sin definir parámetro en el método estamos configurando un nodo maestro, 
  // de lo contrario debemos definir el número del nodo esclavo
  Wire.begin();

  // Mostramos los datos solicitados de los nodos a través del puerto Serie
  Serial.begin(9600);
}

void loop() 
{
  for (int i = 9; i <= 17; i++)
  {
    cadenaRecibida = LecturaI2C(i, 1);
    Serial.print("Lectura Esclavo " + String(i) + ": " + cadenaRecibida + "\n");

    // Necesario para no saturar el buffer (la memoria interna del nodo maestro)
    delay(500);
  }
  Serial.print("\n");
}
