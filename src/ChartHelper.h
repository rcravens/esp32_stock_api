#ifndef ChartHelper_h
#define ChartHelper_h

#include <Arduino.h>

#include "StockData.h"

namespace rlc
{
    class ChartHelper
    {
    public:
        float min_x;
        float max_x;
        float min_y;
        float max_y;
        float scale_x;
        float scale_y;
        float chart_w;
        float chart_h;

        ChartHelper(StockData &data, int chart_w, int chart_h);
        float convert_x_val_to_pixels(float x_val);
        float convert_y_val_to_pixels(float y_val);

    private:
        void analyze(StockData &data);
    };
}

#endif