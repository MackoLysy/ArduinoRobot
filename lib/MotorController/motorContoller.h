#pragma once
#include <Arduino.h>
#include "AlphaBot.h"
#include <PID_v1.h>
class MotorController
{
private:
    /* data */
public:
    MotorController();
    ~MotorController();
    void init();
    void update();

private:
    static void leftInterruptHanlder();
    static void rightInterruptHanlder();
    const int m_maxSpeed = 16;
    void PIDinit();
    PID *m_PIDL;
    PID *m_PIDR;
    AlphaBot robot;
    static int countL;
    static int countR;
    double m_setpointL;
    double m_inputL;
    double m_outputL;
    double m_setpointR;
    double m_inputR;
    double m_outputR;
};
