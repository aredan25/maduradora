/*Programa creado como trabajo integrador de la diplomatura en robótica 2023 - Universidad Nacional de la Rioja
Automatización de maduradora que queso fresco con leche de vaca. Parte del código fue generado con el sitio web 
https://examples.blynk.cc/?board=Arduino%20Uno&shield=ESP8266%20WiFi%20Shield&example=GettingStarted%2FBlynkBlink para el monitoreo y control 
del dispositivo de manera remota. Abril 2023*. Profesor Daniel Arellano*/

// Credenciales de acceso al sitio de Blynk 
#define BLYNK_TEMPLATE_ID           "TMPLe9YtPpRg"
#define BLYNK_TEMPLATE_NAME         "Trabajointegrador"
#define BLYNK_AUTH_TOKEN            "v1Aqj8mHAGZ6I_blLk2GJg82BkGmYgNM"

#define BLYNK_PRINT Serial

// Librerias 
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Credenciales de acceso a la Red Wifi Hogar
char ssid[] = "Personal-WiFi-178-2.4Ghz";
char pass[] = "8m8Xd4xTnq";

// Declaración del pin y modelo de sensor de teperatura y humedad que se usa
#define DHTPIN 2         
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  //La lectura del sensor DHT22 se puede observar en el monitor serial de Arduino
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Error de lectura del sensor");
    return;

    Serial.println("h");
    Serial.println("t");

  }
  // Uso de pines virtuales en Blynk para las variables de temperatura y humedad. Estos se usan para enviar los datos a la consola de Blynk y a la aplicación.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}


void setup()
{
  
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Conexión a la nube de Blynk
  dht.begin();
}

void loop()
{
  // Funcionaes que se encargar del arranque y comunicación con la consola de Blynk
  Blynk.run(); 
  timer.run();
}