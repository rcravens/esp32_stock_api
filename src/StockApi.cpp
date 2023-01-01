#include "StockApi.h"

namespace rlc
{

    const char *StockApi::API_URL = "https://www.alphavantage.co/query/?function=TIME_SERIES_INTRADAY&interval=60min";

    StockApi::StockApi(const char *api_key)
    {
        this->_api_key = api_key;
    }

    void StockApi::refresh_data(StockData &data)
    {
        char url[256];
        sprintf(url, "%s&apikey=%s&symbol=%s", StockApi::API_URL, _api_key, data.symbol);
        //Serial.printf("url = %s\n", url);

        HTTPClient http;

        http.useHTTP10(true);
        http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
        http.begin(url);
        http.GET();

        DynamicJsonDocument doc(32768);
        deserializeJson(doc, http.getStream());

        const char *last_refreshed_str = doc["Meta Data"]["3. Last Refreshed"];
        //Serial.printf("last_refreshed_str = %s\n", last_refreshed_str);

        if (last_refreshed_str)
        {
            // Clear previous data for this stock
            //
            data.clear_data();

            data.last_refresh_str = last_refreshed_str;

            JsonObject obj = doc["Time Series (60min)"].as<JsonObject>();
            if (obj)
            {
                int pt_index = 0;
                for (JsonPair p : obj)
                {
                    if (pt_index >= StockData::MAX_POINTS)
                    {
                        break;
                    }
                    const char *date_str = p.key().c_str();

                    int year, month, day, hour, minute, second;
                    sscanf(date_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
                    data.points[pt_index].dt.set(year, month, day, hour, minute, second);

                    data.points[pt_index].val = p.value()["4. close"];

                    if (pt_index == 0)
                    {
                        data.open = p.value()["1. open"];
                        data.high = p.value()["2. high"];
                        data.low = p.value()["3. low"];
                        data.close = p.value()["4. close"];
                        data.volume = p.value()["5. volume"];
                    }

                    pt_index++;
                }
                data.num_points = pt_index;
                //Serial.println("num_points=" + String(pt_index));
            }
        }

        http.end();
    }

}
