#include "motorContoller.h"

int MotorController::countL = 0;
int MotorController::countR = 0;

MotorController::MotorController()
{
    init();
    // robot.Forward();
}

MotorController::~MotorController()
{
    delete m_PIDL;
    delete m_PIDR;
}

void MotorController::init()
{
    attachInterrupt(0, leftInterruptHanlder, CHANGE);
    attachInterrupt(1, rightInterruptHanlder, CHANGE);
    PIDinit();
}

void MotorController::PIDinit()
{
    m_PIDL = new PID(&m_inputL, &m_outputL, &m_setpointL, 25, 8, 0, DIRECT);
    m_PIDR = new PID(&m_inputR, &m_outputR, &m_setpointR, 25, 8, 0, DIRECT);
    m_PIDL->SetMode(AUTOMATIC);
    m_PIDR->SetMode(AUTOMATIC);
    m_inputL = 0;
    m_inputR = 0;
    m_setpointL = 100 * m_maxSpeed / 255;
    m_setpointR = 100 * m_maxSpeed / 255;
}

void MotorController::leftInterruptHanlder()
{
    countL++;
}

void MotorController::rightInterruptHanlder()
{
    countR++;
}

void MotorController::update()
{
    m_inputL = countL;
    if (m_PIDL->Compute() == true)
    {
        countL = 0;
    }
    robot.SetLSpeed(m_outputL);
    m_inputR = countR;
    if (m_PIDR->Compute() == true)
    {
        countR = 0;
    }
    robot.SetRSpeed(m_outputR);
}