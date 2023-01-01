#ifndef WiFiHelper_h
#define WiFiHelper_h

#include <Arduino.h>

namespace rlc
{
    class WiFiHelper
    {
    public:
        WiFiHelper(const char *ssid, const char *pword, bool is_debug_mode = false);
        void connect();
        void connect(int time_out);
        bool is_connected();

    private:
        bool _is_debug_mode;
        const char *_ssid;
        const char *_pword;

        void _print(const char *msg);
    };
}

#endif