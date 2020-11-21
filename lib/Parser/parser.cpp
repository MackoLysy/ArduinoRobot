#include "parser.h"

Parser::Parser()
{
    m_message = nullptr;
}

Parser::~Parser()
{
}

bool Parser::createRawData()
{
    m_doc.clear();
    int index = m_message->indexOf(':') + 1;
    unsigned int i;
    String json = "";
    for (i = index; i < m_message->length(); i++)
    {
        json += m_message->charAt(i);
    }
    auto error = deserializeJson(m_doc, json);
    if (error)
    {
        return false;
    }
    return true;
}
void Parser::parseData()
{
    if (createRawData())
    {
        String cmd = m_doc["cmd"];
        if (cmd == "distance")
        {
            int angle = m_doc["angle"];
            int result = m_distance->getDistance(angle);
            createDistanceResponse(angle, result);
            return;
        }
        if (cmd == "forward")
        {
            int value = m_doc["ticks"];
            Serial.println(value);
            m_motor->moveFoward(value);
            createMoveResponse("forward", value);
            return;
        }
        if (cmd == "left")
        {
            int value = m_doc["ticks"];
            Serial.println(value);
            m_motor->rotateLeft(value);
            createMoveResponse("left", value);
            return;
        }
        if (cmd == "right")
        {
            int value = m_doc["ticks"];
            Serial.println(value);
            m_motor->rotateRight(value);
            createMoveResponse("right", value);
            return;
        }
        m_response = "{ cmd: \"empty\"}";
        return;
    }
    else
    {
        m_response = "{ cmd: \"error\" value: \"error in json\"}";
    }
}

void Parser::createDistanceResponse(int angle, int dinstance)
{
    m_response = "{ cmd: \"distance\", angle:";
    m_response += angle;
    m_response += ", dist:";
    m_response += dinstance;
    m_response + "}";
}

void Parser::createMoveResponse(String dir, int ticks)
{
    m_response = "{ cmd: \"move\", dir:\"";
    m_response += dir;
    m_response += "\", ticks:";
    m_response += ticks;
    m_response + "}";
}