#include "DateTime.h"

namespace rlc
{

    DateTime::DateTime()
    {
        set(0, 0, 0, 0, 0, 0);
    }

    DateTime::DateTime(const char *date_str)
    {
        set(date_str);
    }

    DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    {
        set(year, month, day, hour, minute, second);
    }

    void DateTime::set(const char *date_str)
    {
        sscanf(date_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

        this->epoch = DateTime::convert_to_epoch(year, month, day, hour, minute, second);
    }

    void DateTime::set(int year, int month, int day, int hour, int minute, int second)
    {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->second = second;

        this->epoch = DateTime::convert_to_epoch(year, month, day, hour, minute, second);
    }

    const char *DateTime::to_data_time_string()
    {
        String tmp = String(year) + "/" + String(month) + "/" + String(day) + " " + String(hour) + ":" + String(minute) + ":" + String(second);
        return tmp.c_str();
    }

    const char *DateTime::to_date_string()
    {
        String tmp = String(year) + "/" + String(month) + "/" + String(day);
        return tmp.c_str();
    }

    const char *DateTime::to_time_string()
    {
        String tmp = String(hour) + ":" + String(minute) + ":" + String(second);
        return tmp.c_str();
    }

    // STATIC METHODS ------------------------------------
    //
    time_t DateTime::convert_to_epoch(DateTime &dt)
    {
        return DateTime::convert_to_epoch(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
    }

    time_t DateTime::convert_to_epoch(int year, int month, int day, int hour, int minute, int second)
    {
        tmElements_t t1;
        t1.Hour = hour;
        t1.Minute = minute;
        t1.Second = second;
        t1.Day = day;
        t1.Month = month;
        t1.Year = year - 1970; // epoch reference date

        return ::makeTime(t1);
    }

    DateTime DateTime::convert_to_dt(time_t epoch)
    {
        DateTime dt;
        dt.set(::year(epoch), ::month(epoch), ::day(epoch), ::hour(epoch), ::minute(epoch), ::second(epoch));
        return dt;
    }

}