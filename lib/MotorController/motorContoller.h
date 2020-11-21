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
    void moveFoward(int ticks);
    void rotateLeft(int ticks);
    void rotateRight(int ticks);

private:
    static void leftInterruptHanlder();
    static void rightInterruptHanlder();
    static int countL;
    static int countR;
    static bool m_isMove;
    static int m_moveCounter;
    const int m_maxSpeed = 16;
    void PIDinit();
    PID *m_PIDL;
    PID *m_PIDR;
    AlphaBot robot;
    double m_setpointL;
    double m_inputL;
    double m_outputL;
    double m_setpointR;
    double m_inputR;
    double m_outputR;
};
