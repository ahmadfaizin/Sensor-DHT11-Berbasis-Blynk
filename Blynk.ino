// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "8jUTCcAJhJBmVVje-u-YI0wTvNMW5Uja";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Pesma SDM IPTEK";
char pass[] = "xxxxxxx";

#define DHTPINKU 0
#define DHTTYPE DHT11

DHT dht(DHTPINKU, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)) {
    Serial.println("Gagal dalam membaca Sensor DHT-11");
    return;
  }
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  
}
