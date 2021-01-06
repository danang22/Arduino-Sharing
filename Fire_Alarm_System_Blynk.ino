#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int pinBuzzer = D2;

char auth[] = "...."; // Token Blynk

char ssid[] = "......."; // Nama WiFi Yang Terhubung
char pass[] = "........"; // Password WiFi
int flag=0;
void notifyOnFire()
{
  int isButtonPressed = digitalRead(D1); // Sensor Api
  if (isButtonPressed==1 && flag==0)
  {
    Serial.println("Api Terdeteksi");
    Blynk.notify("Peringatan : Api Terdeteksi");
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }
}

SimpleTimer timer;

int mq2 = A0;
int data = 0;


#include "DHT.h"
#define DHTPIN D6

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
 float h = dht.readHumidity();
  float t = dht.readTemperature();

   if (isnan(h) || isnan(t)){
    Serial.println(F("Pembacaan Sensor DHT Gagal!"));
    return;
  }
   Blynk.virtualWrite(V5, t);
   Blynk.virtualWrite(V6, h);
}

void setup()
{
pinMode(pinBuzzer, OUTPUT);
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  pinMode(D1,INPUT_PULLUP);
  timer.setInterval(1000L,notifyOnFire);

  timer.setInterval(1000L, getSendData);
  
  Serial.println(F("testing DHTxx!"));

  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void getSendData(){
  data = analogRead(mq2);
  Blynk.virtualWrite(V1, data);

  if (data > 700)
  {
    Blynk.notify("Asap Terdeteksi");
  }
}
