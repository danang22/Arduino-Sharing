#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <SimpleTimer.h>
#define BLYNK_PRINT Serial


const int smoke = A0;
const int Pinbuzzer = D2;

//int data;
int dataAsap;
int data = 500;

char auth[] = "";


char ssid[] = "";
char pass[] = "";

SimpleTimer timer;

void setup(){
  pinMode(smoke, INPUT);
  pinMode(Pinbuzzer, OUTPUT);
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
}

void loop(){
  
  timer.run();
  Blynk.run();
  int analogSensor = analogRead(smoke);
  Serial.print("Nilai sensor: ");
  Serial.println(analogSensor);
  delay(3000);
  if (analogSensor > data){
    tone(Pinbuzzer, 2000, 1000);
  }
  else{
    noTone(Pinbuzzer);
  }
}

void getSendData()
{
  data = analogRead(smoke);
  Blynk.virtualWrite(V2, data);

  if (data > 500)
  {
    Blynk.notify("Asap Terdeteksi");
  }
}
