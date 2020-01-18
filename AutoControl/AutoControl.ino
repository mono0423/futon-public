#include <M5StickC.h>
#include "DHT.h"
#include "Ambient.h"

#define DHT_PIN 33
#define RELAY_PIN 26
#define BUTTON_PIN 37

#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

#define LED_LENGTH 1

void setup()
{
  Serial.begin(9600);

  // Set up M5StickC
  M5.begin();
  M5.Axp.ScreenBreath(7);
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  dht.begin();
}

// 布団の最大温度
int maxTemp = 33;

void loop()
{
  M5.Lcd.setCursor(0, 0, 1);
  M5.Lcd.fillScreen(BLACK);

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  int power = 0;
  if (t < maxTemp) {
    power = 1;
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    M5.Lcd.setCursor(0, 0, 1);
    M5.Lcd.printf("temp :%4.1f'C\r\n", t);
    M5.Lcd.printf("humid:%4.1f%%\r\n", h);
    M5.Lcd.printf("power:%s\r\n", power == 1 ? "on" : "off");
    M5.Lcd.printf("MAX  :%d'C\r\n", maxTemp);
  }

  delay(10000);
}
