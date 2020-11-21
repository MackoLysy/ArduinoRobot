#pragma once
#include "Arduino.h"
#include "ArduinoJson.h"
#include "distanceMeter.h"
#include "motorContoller.h"

class Parser
{
public:
    Parser();
    ~Parser();
    void setMessage(String *value) { m_message = value; };
    bool isValid() { return (m_message->indexOf('{') != -1) && (m_message->indexOf('}') != -1); }
    void parseData();
    void setPointers(DistanceMeter *distance, MotorController *motor)
    {
        m_distance = distance;
        m_motor = motor;
    }
    String *getResponse() { return &m_response; }

private:
    void createDistanceResponse(int angle, int dinstance);
    void createMoveResponse(String dir, int ticks);
    bool createRawData();

    DistanceMeter *m_distance;
    MotorController *m_motor;
    String *m_message;
    String m_response;
    StaticJsonDocument<100> m_doc;
};
