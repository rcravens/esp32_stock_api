#ifndef DateTime_h
#define DateTime_h

#include <Arduino.h>
#include <TimeLib.h>

namespace rlc
{
    class DateTime
    {
    public:
        static time_t convert_to_epoch(DateTime &dt);
        static time_t convert_to_epoch(int year, int month, int day, int hour, int minute, int second);
        static DateTime convert_to_dt(time_t epoch);

        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        time_t epoch;

        DateTime();
        DateTime(const char *str);
        DateTime(int year, int month, int day, int hour, int minute, int second);
        void set(const char *str);
        void set(int year, int month, int day, int hour, int minute, int second);
        const char *to_data_time_string();
        const char *to_date_string();
        const char *to_time_string();
    };
}

#endif