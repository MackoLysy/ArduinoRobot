/*************************************** 
Waveshare AlphaBot mjpg-AlphaBot-PID

Command Line:
-----------------------------------------------------------------------------------------------------
{"Car":"Forward"}
{"Car":"Backward"}
{"Car":"Left"}
{"Car":"Right"}

Expended Command
{"Car":"Forward","Time":"1000"}   ------   Car run forward 1000ms
{"Car":"SetSpeed","Value":[250,200]} ------  Set speed as 250 on left motor and 200 on right motor
-----------------------------------------------------------------------------------------------------
{"LCD":"Display","Line1":"Waveshare","Line2":"Waveshare"}

CN: www.waveshare.net/wiki/AlphaBot
EN: www.waveshare.com/wiki/AlphaBot
****************************************/
#include "Arduino.h"
#include "motorContoller.h"

MotorController Motor;
void setup()
{
  // Motor.init();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);
}
