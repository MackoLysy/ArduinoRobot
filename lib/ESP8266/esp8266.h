#pragma once
#include "Arduino.h"
#include "SoftwareSerial.h"

class Esp8266
{

public:
    Esp8266();
    ~Esp8266();
    void init();
    void handleMessage();
    void writeData(String data);
    void clearMessage() { m_message = ""; }
    bool isReady()
    {

        return m_ready;
    }

    String *getMessage() { return &m_message; }

private:
    enum class Status
    {
        EMPTY,
        RESET,
        SETCWMODE,
        HANDLEWIFICONNECTED,
        GETIP,
        SETUDPSERVER,
        READYTOREAD
    };
    void writeCmd(String value);
    bool isOk();
    void parseMessage();
    void handleReset();
    void handleCWMode();
    void handleWifiConnected();
    void handleGetIp();
    void hanldeCPDInfo();
    void handleSetServerIp();
    void getIp();
    bool m_ready;
    Status m_status;
    String m_message;
    String m_ip;
    String m_server;
    SoftwareSerial *m_serial;
};
