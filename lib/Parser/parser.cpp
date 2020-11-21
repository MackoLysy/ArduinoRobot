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
            Serial.println(result);
            createDistanceResponse(angle, result);
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