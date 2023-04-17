/*Programa creado como trabajo integrador de la diplomatura en robótica 2023 - Universidad Nacional de la Rioja
Automatización de maduradora que queso fresco con leche de vaca. Parte del código fue generado con el sitio web 
https://examples.blynk.cc/?board=Arduino%20Uno&shield=ESP8266%20WiFi%20Shield&example=GettingStarted%2FBlynkBlink para el monitoreo y control 
del dispositivo de manera remota. Abril 2023. Versión final*. Profesor Daniel Arellano*/

// Credenciales de acceso la consola de Blynk 
#define BLYNK_TEMPLATE_ID           "TMPLe9YtPpRg"
#define BLYNK_TEMPLATE_NAME         "Trabajointegrador"
#define BLYNK_AUTH_TOKEN            "v1Aqj8mHAGZ6I_blLk2GJg82BkGmYgNM"


#define BLYNK_PRINT Serial

//Librerias
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Credenciales de acceso a red wifi hogar

char ssid[] = "Personal-WiFi-178-2.4Ghz";
char pass[] = "8m8Xd4xTnq";

//Pin y modelo del sensor de Temperatura y Humedad
#define DHTPIN 12          
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

//LCD utilizada con sus parámetros, en este caso es 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4); 

BlynkTimer timer;


//Variables para led y relé
const int ledrojo = 14;
const int ledverde = 2;
const int rele = 13;

// Función para lectura del sensor DHT22 y mostrarlo en el monitor serial de Arduino. Mensajes en pantalla LCD

void sendSensor()
  {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Falló la lectura del sensor");
    return;
  }
  
  //Condiciones que se deben cumplir para encendido de los leds y relé

  if (t>=32)
  {
    digitalWrite (ledrojo, LOW);
    digitalWrite (ledverde, HIGH);   
    digitalWrite (rele, LOW); 
  }
  if (t<32) 
  {
    digitalWrite (ledrojo, HIGH);
    digitalWrite (ledverde, LOW);   
    digitalWrite (rele, HIGH);
  }
  //Mensajes que aparecen en la pantalla LCD - Valores Temperatura y Humedad
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Trabajo final");
  lcd.setCursor(0, 1);
  lcd.print("Temp. C: ");
  lcd.setCursor(10, 1);
  lcd.print(t);
  lcd.setCursor(0, 2);
  lcd.print("Hum. %: ");
  lcd.setCursor(10, 2);
  lcd.print(h);
  lcd.setCursor(0, 3);
  lcd.print("Robotica UNLAR");
  lcd.setCursor(0, 3);
  lcd.print("Robotica UNLAR");
  
  Blynk.virtualWrite(V5, h); //Pin virtual creado para enviar datos a Blynk (particular de Blynk)
  Blynk.virtualWrite(V6, t); //Pin virtual creado para enviar datos a Blynk (particular de Blynk)

  Serial.println(h);
  Serial.println(t);
}

void setup()
{
   
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Conexión a la nube de Blynk
  dht.begin();
  pinMode(ledrojo , OUTPUT);
  pinMode(ledverde , OUTPUT);
  pinMode(rele , OUTPUT);
    
  timer.setInterval(1000L, sendSensor);
}

//ejecusión del programa de Blynk y del temporizador
void loop()
{
  Blynk.run();
  timer.run();
}
