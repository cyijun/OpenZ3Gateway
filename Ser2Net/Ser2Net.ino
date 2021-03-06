/*
    8266 serial to TCP bridge
    need to add your server address
    based on https://github.com/dparnell/esp8266-ser2net
*/

#define USE_WDT

#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
// application config
const String strHWID = "zigbee-serial_" + String(ESP.getChipId(), HEX);
const char *HWID = strHWID.c_str();

#define BAUD_RATE 115200
#define TCP_LISTEN_PORT 1234

// serial and ethernet buffer size
#define BUFFER_SIZE 256

WiFiServer server(TCP_LISTEN_PORT);

void setup(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.hostname(strHWID);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);

    Serial.begin(BAUD_RATE);

    WiFiManager wm;
    bool res = wm.autoConnect(HWID, "espconfig");
    // wm.resetSettings();

    if (!res)
    {
        ESP.restart(); // restart when failed
    }

    // Start TCP server
    server.begin();

#ifdef USE_WDT
    wdt_enable(1000);
#endif
}

WiFiClient wClient;

void loop(void)
{
    size_t bytes_read;
    uint8_t net_buf[BUFFER_SIZE];
    uint8_t serial_buf[BUFFER_SIZE];

#ifdef USE_WDT
    wdt_reset();
#endif

    if (WiFi.status() != WL_CONNECTED)
    {
        // we've lost the connection, so we need to reconnect
        if (wClient)
        {
            wClient.stop();
        }
    }
    // Check if a client has connected
    if (!wClient.connected())
    {
        // eat any bytes in the serial buffer as there is nothing to see them
        while (Serial.available())
        {
            Serial.read();
        }

        wClient = server.available();
    }

#define min(a, b) ((a) < (b) ? (a) : (b))

    if (wClient.connected())
    {
        // check the network for any bytes to send to the serial
        int count = wClient.available();
        if (count > 0)
        {
            bytes_read = wClient.read(net_buf, min(count, BUFFER_SIZE));
            Serial.write(net_buf, bytes_read);
            Serial.flush();
        }

        // now check the serial for any bytes to send to the network
        bytes_read = 0;
        while (Serial.available() && bytes_read < BUFFER_SIZE)
        {
            serial_buf[bytes_read] = Serial.read();
            bytes_read++;
        }

        if (bytes_read > 0)
        {
            wClient.write((const uint8_t *)serial_buf, bytes_read);
            wClient.flush();
        }
    }
    else
    {
        wClient.stop();
    }
}
