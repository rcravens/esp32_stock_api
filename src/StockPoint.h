#ifndef StockPoint_h
#define StockPoint_h

#include <Arduino.h>
#include "DateTime.h"

namespace rlc
{
    class StockPoint
    {
    public:
        rlc::DateTime dt;
        float val;

        StockPoint();
        void set(const char *date_str, float val);
        void set(int year, int month, int day, int hour, int minute, int second, float val);
    };
}

#endif