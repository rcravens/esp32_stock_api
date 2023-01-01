#ifndef StockApi_h
#define StockApi_h

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "StockData.h"

namespace rlc
{

    class StockApi
    {
    public:
        StockApi(const char *api_key);
        void refresh_data(StockData &data);

    private:
        static const char *API_URL;

        const char *_api_key;
    };

}

#endif