#include "Arduino.h"
#include "ArduinoJson.h"

class Parser
{

public:
    Parser();
    ~Parser();
    void setMessage(String *value) { m_message = value; };
    bool isValid() { return (m_message->indexOf('{') != -1) && (m_message->indexOf('}') != -1); }

private:
    String *m_message;
    /* data */
};
