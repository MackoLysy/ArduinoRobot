#include "motorContoller.h"

int MotorController::countL = 0;
int MotorController::countR = 0;
bool MotorController::m_isMove = false;
int MotorController::m_moveCounter = 0;

MotorController::MotorController()
{
    init();
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
    m_setpointL = 20 * m_maxSpeed / 255;
    m_setpointR = 20 * m_maxSpeed / 255;
}

void MotorController::leftInterruptHanlder()
{
    if (m_isMove)
    {
        countL++;
        m_moveCounter++;
    }
}

void MotorController::rightInterruptHanlder()
{
    if (m_isMove)
    {
        countR++;
    }
}

void MotorController::update()
{
    if (m_isMove)
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
}

void MotorController::moveFoward(int ticks)
{
    robot.Brake();
    m_moveCounter = 0;
    m_isMove = true;
    while (m_moveCounter <= ticks)
    {
        Serial.println(m_moveCounter);
        robot.Forward();
    }
    m_moveCounter = 0;
    m_isMove = false;
    robot.Brake();
}

void MotorController::rotateLeft(int ticks)
{
    robot.Brake();
    m_moveCounter = 0;
    m_isMove = true;
    while (m_moveCounter <= ticks)
    {
        Serial.println(m_moveCounter);
        robot.LeftCircle();
    }
    m_moveCounter = 0;
    m_isMove = false;
    robot.Brake();
}

void MotorController::rotateRight(int ticks)
{
    robot.Brake();
    m_moveCounter = 0;
    m_isMove = true;
    while (m_moveCounter <= ticks)
    {
        Serial.println(m_moveCounter);
        robot.RightCircle();
    }
    m_moveCounter = 0;
    m_isMove = false;
    robot.Brake();
}