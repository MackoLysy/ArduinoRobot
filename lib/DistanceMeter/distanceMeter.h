#pragma once
#include "Arduino.h"
#include "Servo.h"

class DistanceMeter
{
public:
    DistanceMeter(/* args */);
    ~DistanceMeter();
    void init();
    int getDistance(int angle);

private:
    Servo m_servo;
};
