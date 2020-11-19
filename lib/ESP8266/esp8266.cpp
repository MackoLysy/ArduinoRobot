#include "../../include/config.h"
#include "esp8266.h"

Esp8266::Esp8266()
{
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    m_serial = new SoftwareSerial(rxPin, txPin);
    m_serial->begin(9600);
    m_message = "";
    m_server = "";
    m_ip = "";
    m_ready = false;
    m_status = Status::EMPTY;
}

Esp8266::~Esp8266()
{
    delete m_serial;
}

void Esp8266::init()
{
    m_status = Status::RESET;
    writeCmd("AT+RST");
}

void Esp8266::writeCmd(String value)
{
    value += "\r\n";
    m_serial->write(value.c_str());
}
void Esp8266::writeData(String data)
{
    String query = "AT+CIPSEND=";
    query += (data.length() + 2);
    query += ",\"";
    query += m_server;
    query += "\",";
    query += PORT;
    writeCmd(query);
    delay(200);
    writeCmd(data);
    clearMessage();
}
bool Esp8266::isOk()
{
    return m_message.indexOf("OK") != -1;
}

void Esp8266::handleMessage()
{
    while (m_serial->available() > 0)
    {
        char value = m_serial->read();
        m_message += value;
        if (value == '\n')
        {
            parseMessage();
            if (!m_ready)
            {
                Serial.print(m_message.c_str());
                m_message = "";
            }
        }
    }
}

void Esp8266::parseMessage()
{
    switch (m_status)
    {
    case Status::RESET:
        handleReset();
        break;
    case Status::SETCWMODE:
        handleCWMode();
        break;
    case Status::HANDLEWIFICONNECTED:
        handleWifiConnected();
        break;
    case Status::GETIP:
        handleGetIp();
        break;
    case Status::SETUDPSERVER:
        hanldeCPDInfo();
        break;
    case Status::READYTOREAD:
        handleSetServerIp();
        break;
    default:
        break;
    }
}

void Esp8266::handleReset()
{
    if (m_message.indexOf("ready") != -1)
    {
        m_status = Status::SETCWMODE;
        writeCmd("AT+CWMODE=1");
    }
}

void Esp8266::handleCWMode()
{
    if (isOk())
    {
        String msg = "AT+CWJAP=\"";
        msg += WIFINANE;
        msg += "\",\"";
        msg += WIFIPASSWORD;
        msg += "\"";
        m_status = Status::HANDLEWIFICONNECTED;
        writeCmd(msg);
    }
}

void Esp8266::handleWifiConnected()
{
    if (isOk())
    {
        m_status = Status::GETIP;
        writeCmd("AT+CIFSR");
    }
}

void Esp8266::handleGetIp()
{
    if (m_message.indexOf("CIFSR:STAIP") != -1)
    {
        getIp();
    }
    if (isOk())
    {
        String msg = "AT+CIPSTART=\"UDP\",\"";
        msg += m_ip;
        msg += "\",";
        msg += PORT;
        msg += ",";
        msg += PORT;
        msg += ",2";
        m_status = Status::SETUDPSERVER;
        writeCmd(msg);
    }
}

void Esp8266::getIp()
{
    m_ip = "";
    bool push = false;
    for (size_t i = 0; i < m_message.length(); i++)
    {
        if (push)
        {
            if (m_message.charAt(i) == '"')
            {
                return;
            }
            m_ip += m_message.charAt(i);
        }
        if (m_message.charAt(i) == '"')
        {
            push = true;
        }
    }
}

void Esp8266::hanldeCPDInfo()
{
    if (isOk())
    {
        m_status = Status::READYTOREAD;
        writeCmd("AT+CIPDINFO=1");
    }
}

void Esp8266::handleSetServerIp()
{
    if (m_message.indexOf("+IPD") != -1 && !m_ready)
    {
        m_server = "";
        int index = m_message.indexOf(',', 5) + 1;
        if (index == -1)
        {
            return;
        }
        unsigned int i;
        for (i = index; i < m_message.length(); i++)
        {
            if (m_message.charAt(i) == ',')
            {
                break;
            }
            m_server += m_message.charAt(i);
        }
        writeCmd("AT+CIPDINFO=0");
        delay(100);
        m_ready = true;
        m_message = "";
    }
}