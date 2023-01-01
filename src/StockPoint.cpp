#include "StockPoint.h"

namespace rlc
{
    StockPoint::StockPoint()
    {
    }

    void StockPoint::set(const char *date_str, float val)
    {
        dt.set(date_str);
        val = val;
    }

    void StockPoint::set(int year, int month, int day, int hour, int minute, int second, float val)
    {
        dt.set(year, month, day, hour, minute, second);
        val = val;
    }
}