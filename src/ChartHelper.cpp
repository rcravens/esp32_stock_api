#include "ChartHelper.h"

namespace rlc
{

    ChartHelper::ChartHelper(StockData &data, int chart_w, int chart_h)
    {
        this->chart_w = chart_w;
        this->chart_h = chart_h;
        analyze(data);
    }

    void ChartHelper::analyze(StockData &data)
    {
        if (data.num_points > 0)
        {

            min_x = data.points[0].dt.epoch;
            max_x = data.points[0].dt.epoch;
            min_y = data.points[0].val;
            max_y = data.points[0].val;
            for (int i = 0; i < data.num_points; i++)
            {
                if (data.points[i].dt.epoch < min_x)
                {
                    min_x = data.points[i].dt.epoch;
                }
                if (data.points[i].dt.epoch > max_x)
                {
                    max_x = data.points[i].dt.epoch;
                }
                if (data.points[i].val < min_y)
                {
                    min_y = data.points[i].val;
                }
                if (data.points[i].val > max_y)
                {
                    max_y = data.points[i].val;
                }
            }

            if (max_x == min_x)
            {
                max_x = max_x + 5;
                min_x = min_x - 5;
            }
            if (max_y == min_y)
            {
                max_y = max_y + 5;
                min_y = min_y - 5;
            }

            scale_x = float(chart_w) / float(max_x - min_x);
            scale_y = float(chart_h) / float(max_y - min_y);
        }
    }

    float ChartHelper::convert_x_val_to_pixels(float x_val)
    {
        return scale_x * (x_val - min_x);
    }
    float ChartHelper::convert_y_val_to_pixels(float y_val)
    {
        return chart_h - scale_y * (y_val - min_y);
    }

}