int iCount, iAccepted = 11, iDenied = 12;

int arrPassword[] = {0, 0, 0, 0, 0, 1, 1, 1}, arrInPassword[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
  Serial.begin(9600);

  // El pin 2 de entrada corresponde al dígito menos significativo controlado por el Dip Switch
  // y así sucesivamente con los demás
  pinMode(2, INPUT), (3, INPUT), (4, INPUT), (5, INPUT);
  pinMode(6, INPUT), (7, INPUT), (8, INPUT), (9, INPUT);

  pinMode(iAccepted, OUTPUT), (iDenied, OUTPUT);
}

void loop()
{
  // Recorre los pines de forma ascendente
  for (int i = 2; i <= 9; i++)
  {
    // La lectura digital del pin es almacenada en un array
    // El dígito menos significado concuerda con el índice cero del array
    arrInPassword[i - 2] = digitalRead(i);
  }

  // Reinicia el contador con cada nueva comparación entre arrays
  iCount = 0;
  
  // Recorre los índices de ambos arrays 
  for (int i = 0; i <= 7; i++)
  {
    // Si ambos elementos no concuerdan...  
    if (arrInPassword[i] != arrPassword[i])
    {
      Serial.println("Contraseña incorrecta"); // se señala la incongruencia...
      digitalWrite(iAccepted, LOW);
      digitalWrite(iDenied, HIGH); // solo se muestra un led encendido...
      break; // y se rompe el ciclo al ya no ser necesario seguir comparando
    }
    else
    {
      // De lo contrario, se lleva la cuenta
      iCount += 1;
    }
  }
  
  // Sy el contador es igual a ocho, significa que ambos arrays son iguales en su totalidad...
  if (iCount == 8)
  {
    Serial.println("Contraseña correcta!"); // se señala la igualdad...
    digitalWrite(iAccepted, HIGH); // y se encienden ambos leds
    digitalWrite(iDenied, HIGH);
  }
  delay(500);
}
