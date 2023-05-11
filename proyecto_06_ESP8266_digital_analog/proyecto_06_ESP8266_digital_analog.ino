#include <ESP8266WiFi.h>

String apiKey = "";

const char *ssid = "";

const char *pass = "";

const char *server = "api.thingspeak.com";

WiFiClient client;

int entradaDigital = 5;
int estado;

int entradaAnalogica = A0;
int iLectura_ADC;
int grados;

void setup()
{
  Serial.begin(9600);
  pinMode(entradaDigital, INPUT);

  Serial.println("Conectando a: " + String(ssid));

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
  iLectura_ADC = analogRead(entradaAnalogica);

  grados = map(iLectura_ADC, 0, 1023, 0, 270);

  Serial.println("Grados: " + String(grados) + "°");
  Serial.println();

  if (digitalRead(entradaDigital))
  {
    estado = 1;
  }
  else
  {
    estado = 0;
  }
  Serial.println("Estado: " + String(estado));
  Serial.println();

  if (client.connect(server, 80))
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(estado);
    postStr += "&field2=";
    postStr += String(grados);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY:" + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println("Grados: " + String(grados) + "°");
    Serial.println("Enviado a ThingSpeak");
    Serial.println();

    Serial.println("Estado: " + String(estado));
    Serial.println("Enviado a ThingSpeak");
    Serial.println();
  }
  client.stop();
  delay(1000);
}
