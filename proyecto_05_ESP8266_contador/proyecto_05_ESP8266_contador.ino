#include <ESP8266WiFi.h>

// apiKey de ThingSpeak
String apiKey = "";

// Los métodos de WiFi solo aceptan cadenas de carateres pero no Strings

// nombre de la red WiFi
const char *ssid = "";

// contraseña de la red WiFi
const char *pass = "";

// dominio o dirección IP del servidor
const char *server = "api.thingspeak.com";

// Creación de un objeto tipo WiFiClient
WiFiClient client;

void setup()
{
  Serial.begin(9600);

  Serial.println("Conectando a: " + String(ssid));

  // Conexión a la red WiFi con
  // nombre de la red y contraseña
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi conectado!");
}

void loop()
{
  for (int iContador = 0; iContador <= 10; iContador++)
  {
    // Mostramos iContador por puerto Serie
    Serial.println("Numero: " + String(iContador));
    Serial.println();

    // Si existe conexión con el servidor
    if (client.connect(server, 80))
    {
      /*
        creamos una cadena que será un post, es decir,
        vamos a realizar una operación tipo post http,
        es una manera de transmitir datos a un servidor mediante una cadena

        apiKey&field1=iContador/r/n/r/n
      */
      String postStr = apiKey;
      postStr += "&field1=";
      postStr += String(iContador);
      postStr += "\r\n\r\n";

      // Los métodos envían la información que acabamos de construir
      // a través de nuestro objeto cliente de tipo WiFiClient

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY:" + apiKey + "\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr); // Aquí se encuentra nuestra información

      // Mostramos el envío exitoso de iContador a ThingSpeak
      Serial.println("Numero: " + String(iContador));
      Serial.println("Enviado a ThingSpeak");
      Serial.println();
    }
    // Cerramos la conexión
    client.stop();
    // Agregamos delay para evitar ser reconocido como ataque DDoS
    delay(1000);
  }
}
