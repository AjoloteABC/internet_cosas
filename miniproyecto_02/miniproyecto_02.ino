
int iLecturaADC, iGrados;

int iLed01 = 2, iLed02 = 3, iLed03 = 4, iLed04 = 5;
int iLed05 = 6, iLed06 = 7, iLed07 = 8, iLed08 = 9;

void setup()
{
  Serial.begin(9600); //Inicializar puerto serie

  pinMode(iLed01, OUTPUT); pinMode(iLed02, OUTPUT); pinMode(iLed03, OUTPUT); pinMode(iLed04, OUTPUT);
  pinMode(iLed05, OUTPUT); pinMode(iLed06, OUTPUT); pinMode(iLed07, OUTPUT); pinMode(iLed08, OUTPUT);
}

// Usa como parámetro el led que debe encerderse dependiendo 
// del rango en el que se encuentre la lectura analógica (iLecturaADC)
void encender(int iPinLed)
{
  // Enciende los leds
  for (int i = iLed01; i <= iPinLed; i++) 
  {
    digitalWrite(i, HIGH);
  }
  
  // Apaga los leds
  for (int i = iLed08; i > iPinLed; i--) 
  {
    digitalWrite(i, LOW);
  }
}

void loop()
{
  iLecturaADC = analogRead(1); // Lectura de entrada analógica A1
  
  // La función map remapea el número de un rango a otro
  iGrados = map(iLecturaADC, 0, 1023, 0, 270);
  
  // El Arduino tiene una resolución de 10 bits (1024 niveles de cuantificación)
  // Por lo tanto, dividimos 1024 entre el no. de leds a ocupar
  if (iLecturaADC <= 127) 
  {
    encender(iLed01);
  }
  else if (iLecturaADC > 127 && iLecturaADC <= 255)
  {
    encender(iLed02);
  }
  else if (iLecturaADC > 255 && iLecturaADC <= 383)
  {
    encender(iLed03);
  }
  else if (iLecturaADC > 383 && iLecturaADC <= 514)
  {
    encender(iLed04);
  }
  else if (iLecturaADC > 514 && iLecturaADC <= 639)
  {
    encender(iLed05);
  }
  else if (iLecturaADC > 639 && iLecturaADC <= 767)
  {
    encender(iLed06);
  }
  else if (iLecturaADC > 767 && iLecturaADC <= 895)
  {
    encender(iLed07);
  }
  else
  {
    encender(iLed08);
  }
  Serial.print("LecturaADC: " + String(iLecturaADC) + "\n"); // Unidades adimensionales del ADC
  Serial.print("Grados    : " + String(iGrados) + "°\n\n"); // Unidades de la magnitud física detectada

  delay(500);
}
