#pragma once
#include "Arduino.h"
#include "ArduinoJson.h"
#include "distanceMeter.h"

class Parser
{
public:
    Parser();
    ~Parser();
    void setMessage(String *value) { m_message = value; };
    bool isValid() { return (m_message->indexOf('{') != -1) && (m_message->indexOf('}') != -1); }
    void parseData();
    void setPointers(DistanceMeter *distance) { m_distance = distance; }
    String *getResponse() { return &m_response; }

private:
    void createDistanceResponse(int angle, int dinstance);
    bool createRawData();
    
    DistanceMeter *m_distance;
    String *m_message;
    String m_response;
    StaticJsonDocument<100> m_doc;
};
