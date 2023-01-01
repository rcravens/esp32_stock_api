#ifndef StockData_h
#define StockData_h

#define MAX_NUM_STOCK_POINTS 25

#include <Arduino.h>
#include "StockPoint.h"

namespace rlc
{
    class StockData
    {
    public:
        static int MAX_POINTS;

        const char *symbol;
        const char *last_refresh_str;
        float open;
        float high;
        float low;
        float close;
        float volume;
        byte num_points;
        StockPoint points[MAX_NUM_STOCK_POINTS];

        StockData();
        StockData(const char *symbol);
        void clear_data();
        void print_data();
    };
}

#endif