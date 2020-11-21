#include "Arduino.h"
#include "motorContoller.h"
#include "esp8266.h"
#include "parser.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <distanceMeter.h>

MotorController Motor;
Esp8266 esp8266;
Parser parser;
DistanceMeter distance;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  esp8266.init();
  distance.init();
  parser.setMessage(esp8266.getMessage());
  parser.setPointers(&distance);
}

void loop()
{
  esp8266.handleMessage();
  if (esp8266.isReady())
  {
    if (parser.isValid())
    {
      Serial.println(esp8266.getMessage()->c_str());
      parser.parseData();
      esp8266.writeData(parser.getResponse()->c_str());
      esp8266.clearMessage();
    }
  }
}
