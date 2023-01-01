#include "StockData.h"

namespace rlc
{

    int StockData::MAX_POINTS = MAX_NUM_STOCK_POINTS;

    StockData::StockData()
    {
        num_points = 0;
        last_refresh_str = NULL;
    }

    StockData::StockData(const char *symbol)
    {
        symbol = symbol;
    }

    void StockData::clear_data()
    {
        last_refresh_str = NULL;
        num_points = 0;
    }

    void StockData::print_data()
    {
        Serial.println("----------------------------------------------------------------------");
        Serial.printf("Symbol: %s\n", symbol);
        if (num_points > 0)
        {
            Serial.printf("last refreshed on %s\n", last_refresh_str);
            for (int pt = 0; pt < num_points; pt++)
            {
                Serial.printf("     %f - %s\n", points[pt].val, points[pt].dt.to_data_time_string());
            }
        }
        else
        {
            Serial.println("No points");
        }
    }
}
