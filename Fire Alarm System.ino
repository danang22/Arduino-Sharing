#include "DHT.h"
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int buzzer = D1;    // Pin Buzzer
int smokeA0 = A0;   // Smoke Sensor
int sensorPin = D6; // Flame Sensor
int sensorThres = 500;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(sensorPin, INPUT);

  Serial.begin(9600);

  
  Serial.println("Temperature!");
  dht.begin();

}

void loop() {

  
  delay(2000);
  float humidity = dht.readHumidity();
  float celcius = dht.readTemperature();
  if (isnan(humidity) || isnan(celcius)){
    Serial.println("Sensor not detected!");
    return;

  }
  float htoc = dht.computeHeatIndex(celcius, humidity, false);
  Serial.print("Humidity;: ");
  Serial.print(humidity);
  Serial.print(" %\t");

  Serial.print("Temperature : ");
  Serial.print(celcius);
  Serial.print("C / ");

  Serial.print("Heat Index: ");
  Serial.print(htoc);
  Serial.print("°");
  Serial.println("C ");

  
  int analogSensor = analogRead(smokeA0);
  Serial.print("Smoke level: ");
  Serial.println(analogSensor);
  if (analogSensor > sensorThres)
  {
    Serial.println("level Smoke High");
  }
  else
  {
    //noTone(buzzer);
    
  }
delay(1000);

Serial.println("Flame Sensor");

int sensorValue = analogRead(sensorPin);

Serial.println(sensorValue);

if (sensorValue < 100)

{

  Serial.println("Fire Detected");

  tone(buzzer,1000,200);

}
else
{

  noTone(buzzer);
}
delay(1000);

}
