#include "WiFiHelper.h"
#include <WiFi.h>

namespace rlc
{
    WiFiHelper::WiFiHelper(const char *ssid, const char *pword, bool is_debug_mode)
    {
        _is_debug_mode = is_debug_mode;
        _ssid = ssid;
        _pword = pword;
    }

    void WiFiHelper::connect()
    {
        connect(-1);
    }

    void WiFiHelper::connect(int time_out)
    {
        _print("Connecting...");
        WiFi.begin(_ssid, _pword);

        long start_wait = millis();
        bool is_timed_out = false;
        while (!is_connected() && !is_timed_out)
        {
            delay(500);
            _print(".");

            if (time_out >= 0 && (millis() - start_wait) > time_out)
            {
                is_timed_out = true;
            }
        }
        _print("\n");
        _print("Connected to WiFi network with IP Address: ");
        _print(WiFi.localIP().toString().c_str());
        _print("\n");
    }

    bool WiFiHelper::is_connected()
    {
        return WiFi.status() == WL_CONNECTED;
    }

    void WiFiHelper::_print(const char *msg)
    {
        if (_is_debug_mode)
        {
            Serial.print(msg);
        }
    }

}