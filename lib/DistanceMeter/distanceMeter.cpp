#include "distanceMeter.h"
#include "../../include/config.h"
DistanceMeter::DistanceMeter(/* args */)
{
}

DistanceMeter::~DistanceMeter()
{
}

void DistanceMeter::init()
{
    m_servo.attach(SERVO);
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);
}

int DistanceMeter::getDistance(int angle)
{
    m_servo.write(angle);
    delay(200);
    digitalWrite(TRIG, LOW); // set trig pin low 2μs
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH); // set trig pin 10μs , at last 10us
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW); // set trig pin low
    float tempDistance = pulseIn(ECHO, HIGH);
    tempDistance = tempDistance / 58;
    int distance = tempDistance;
    if ((2 < distance) & (distance < 200))
    {
        return distance;
    }
    else
    {

        return -1;
    }
}
