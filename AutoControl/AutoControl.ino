#include <M5StickC.h>
#include "DHT.h"
#include "Ambient.h"

#define DHT_PIN 33
#define RELAY_PIN 26
#define BUTTON_PIN 37

#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

WiFiClient client;
Ambient ambient;
char *wifiStatus = "Wifi : OK";
char *amientStatus = "";

const char *ssid = "";     // input SSID here
const char *password = ""; // input Password here

const unsigned int channelId = 0; // input Ambient channel ID here
const char *writeKey = "";        // input Ambient writeKey here

void connectWifi()
{
  if (strlen(ssid) > 0 && strlen(password))
  {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
      M5.Lcd.setCursor(0, 0, 1);
      M5.Lcd.println("WiFi connecting");
    }

    M5.Lcd.println("WiFi connected!");
    delay(500);

    Serial.print("WiFi connected\r\nIP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("ambient connecting...");
    ambient.begin(channelId, writeKey, &client);
    Serial.println("ambient connected!");

    M5.Lcd.println("Ambient connected!");
    delay(5000);
  }
  else
  {
    wifiStatus = "Wifi :NG";
    Serial.println("Skip WiFi connect");
    Serial.println("Input SSID & Password");
  }
}

void setup()
{
  Serial.begin(115200);

  // Set up M5StickC
  M5.begin();
  M5.Axp.ScreenBreath(7);
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  connectWifi();
  dht.begin();
}

void loop()
{
  M5.Lcd.setCursor(0, 0, 1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println(wifiStatus);

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  int power = 0;
  if (t < 30)
  {
    power = 1;
    digitalWrite(RELAY_PIN, HIGH);
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
  }

  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
    M5.Lcd.println("Error");
  }
  else
  {
    M5.Lcd.printf("temp :%4.1f'C\r\n", t);
    M5.Lcd.printf("humid:%4.1f%%\r\n", h);
    M5.Lcd.printf("power:%s\r\n", power == 1 ? "on" : "off");
  }

  if (channelId > 10000 && strlen(writeKey) > 0)
  {
    ambient.set(1, t);
    ambient.set(2, h);
    ambient.set(3, power);
    ambient.send();
  }

  delay(30000);
}
