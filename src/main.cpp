#include <Arduino.h>
#include <TFT_eSPI.h>

#include "secrets.h"

#include "WiFiHelper.h"
#include "StockData.h"
#include "StockApi.h"
#include "Display.h"


const int num_stocks = 4;
const unsigned long display_update_interval = 5000;
const unsigned long api_request_interval_in_milliseconds = 120000;

unsigned long last_api_request = 0;
unsigned long last_display_update = 0;
int current_stock = 0;

const char *symbols[] = {"ALB", "SQM", "LAC", "PLL"};

rlc::StockData data[num_stocks];

rlc::StockApi api(API_KEY);

rlc::WiFiHelper wifi_helper(WIFI_SSID, WIFI_PWORD, true);

TFT_eSPI tft = TFT_eSPI();
rlc::Display display(&tft);

void setup()
{
    Serial.begin(9600);

    display.init();

    display.render_splash();

    long start = millis(); // track how long the splash screen is displayed

    wifi_helper.connect();

    for (byte i = 0; i < num_stocks; i++)
    {
        data[i].symbol = symbols[i];
    }

    while ((millis() - start) < 2000)
    {
        delay(250); // stay here until the splash screen is done
    }
}

void update_display()
{
    if (last_display_update == 0 || (millis() - last_display_update) > display_update_interval)
    {
        display.render(data[current_stock]);

        current_stock++;
        if (current_stock >= num_stocks)
        {
            current_stock = 0;
        }

        last_display_update = millis();
    }
}

void update_stock_data()
{
    if (last_api_request == 0 || (millis() - last_api_request) > api_request_interval_in_milliseconds)
    {
        if (wifi_helper.is_connected())
        {
            for (byte i = 0; i < num_stocks; i++)
            {
                api.refresh_data(data[i]);

                data[i].print_data();
            }

            last_api_request = millis();
        }
        else
        {
            Serial.println("Lost WiFi connection....try rebooting.");
        }
    }
}

void loop()
{
    update_stock_data();

    if (last_api_request > 0) // we should have data....
    {
        update_display();
    }
}
