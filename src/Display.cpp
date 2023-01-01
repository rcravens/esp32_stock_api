#include "Display.h"

namespace rlc
{
    Display::Display(TFT_eSPI *tft) : _header_sprite(tft),
                                      _graph_sprite(tft),
                                      _footer_sprite(tft),
                                      _tft(tft)
    {
        _screen_width = 320;
        _screen_height = 170;
        _header_height = 23;
        _footer_height = 20;
        _chart_padding = 10;
        _legend_x = 30;
        _legend_y = 40;
        _chart_h = _screen_height - _header_height - _footer_height - 2 * _chart_padding - _legend_x;
        _chart_w = _screen_width - 2 * _chart_padding - _legend_y;

        _header_sprite.createSprite(_screen_width, _header_height);

        _graph_sprite.createSprite(_screen_width, _screen_height - _header_height - _footer_height);

        _footer_sprite.createSprite(_screen_width, _footer_height);
    }

    Display::Display(int width, int height, int header_height, int footer_height, TFT_eSPI *tft) : _header_sprite(tft),
                                                                                                   _graph_sprite(tft),
                                                                                                   _footer_sprite(tft),
                                                                                                   _screen_width(width),
                                                                                                   _screen_height(height),
                                                                                                   _header_height(header_height),
                                                                                                   _footer_height(footer_height),
                                                                                                   _tft(tft)
    {
        _chart_padding = 10;
        _legend_x = 30;
        _legend_y = 40;
        _chart_h = _screen_height - _header_height - _footer_height - 2 * _chart_padding - _legend_x;
        _chart_w = _screen_width - 2 * _chart_padding - _legend_y;

        _header_sprite.createSprite(_screen_width, _header_height);

        _graph_sprite.createSprite(_screen_width, _screen_height - _header_height - _footer_height);

        _footer_sprite.createSprite(_screen_width, _footer_height);
    }

    void Display::init()
    {
        _tft->init();
        _tft->setRotation(1);
    }

    void Display::render_splash()
    {
        _tft->fillScreen(TFT_BLACK);

        _tft->setTextDatum(7);
        _tft->setTextColor(TFT_ORANGE, TFT_BLACK);
        _tft->drawString("STOCK TICKER 2", _screen_width / 2, _screen_height / 2, 4);

        _tft->setTextDatum(1);
        _tft->setTextColor(TFT_ORANGE, TFT_BLACK);
        _tft->drawString("by Bob Cravens", _screen_width / 2, _screen_height / 2, 2);
    }

    void Display::render(StockData &data)
    {
        render_header(data);

        render_footer(data);

        render_graph(data);
    }

    void Display::render_header(StockData &data)
    {
        _header_sprite.fillSprite(TFT_BLACK);
        _header_sprite.setTextColor(TFT_ORANGE, TFT_BLACK);

        _header_sprite.setTextDatum(0);
        _header_sprite.drawString(data.symbol, 0, 0, 4);

        _header_sprite.setTextDatum(2);
        _header_sprite.drawString(data.last_refresh_str, _screen_width, 7, 2);

        _header_sprite.pushSprite(0, 0);
    }

    void Display::render_footer(StockData &data)
    {
        char buffer[80];

        _footer_sprite.fillSprite(TFT_BLACK);
        _footer_sprite.setTextColor(TFT_ORANGE, TFT_BLACK);

        _footer_sprite.setTextDatum(6);
        sprintf(buffer, "open: %0.1f", data.open);
        _footer_sprite.drawString(buffer, 0, _footer_height, 2);

        _footer_sprite.setTextDatum(7);
        sprintf(buffer, "close: %0.1f", data.close);
        _footer_sprite.drawString(buffer, _screen_width / 2, _footer_height, 2);

        _footer_sprite.setTextDatum(8);
        sprintf(buffer, "volume: %0.1f", data.volume);
        _footer_sprite.drawString(buffer, _screen_width, _footer_height, 2);

        _footer_sprite.pushSprite(0, _screen_height - _footer_height);
    }

    void Display::render_graph(StockData &data)
    {
        _graph_sprite.fillSprite(TFT_ORANGE);

        if (data.num_points > 0)
        {
            char buffer[256];

            ChartHelper chart_helper = ChartHelper(data, _chart_w, _chart_h);

            _graph_sprite.setTextColor(TFT_BLACK, TFT_ORANGE);

            render_vertical_axis(5, chart_helper);

            render_horizontal_axis(3, chart_helper);

            render_points(data, chart_helper);
        }
        else
        {
            _graph_sprite.setTextDatum(4);
            draw_string("No Data", _chart_w / 2, _chart_h / 2);
        }

        _graph_sprite.pushSprite(0, _header_height);
    }

    void Display::render_vertical_axis(int num_tics, ChartHelper &chart_helper)
    {
        _graph_sprite.setTextDatum(5);
        time_t x_val_1 = chart_helper.min_x;
        time_t x_val_2 = chart_helper.max_x;
        float x1 = chart_helper.convert_x_val_to_pixels(x_val_1);
        float x2 = chart_helper.convert_x_val_to_pixels(x_val_2);
        float tic_step = (chart_helper.max_y - chart_helper.min_y) / (num_tics - 1);

        char buffer[256];
        float y_val, y1;
        for (int t = 0; t < num_tics; t++)
        {
            y_val = chart_helper.min_y + t * tic_step;
            y1 = chart_helper.convert_y_val_to_pixels(y_val);
            draw_line(x1, y1, x2, y1, TFT_BLACK);

            sprintf(buffer, "%0.1f", y_val);
            draw_string(buffer, x1 - 3, y1);
        }
    }

    void Display::render_horizontal_axis(int num_tics, ChartHelper &chart_helper)
    {
        float y_val_1 = chart_helper.min_y;
        float y_val_2 = chart_helper.max_y;
        float y1 = chart_helper.convert_y_val_to_pixels(y_val_1);
        float y2 = chart_helper.convert_y_val_to_pixels(y_val_2);
        float tic_step = (chart_helper.max_x - chart_helper.min_x) / (num_tics - 1);

        char buffer[256];
        time_t x_val;
        float x1;
        for (int t = 0; t < num_tics; t++)
        {
            x_val = chart_helper.min_x + t * tic_step;
            x1 = chart_helper.convert_x_val_to_pixels(x_val);
            draw_line(x1, y1, x1, y2, TFT_BLACK);

            if (t == 0)
            {
                _graph_sprite.setTextDatum(0);
            }
            else if (t == num_tics - 1)
            {
                _graph_sprite.setTextDatum(2);
            }
            else
            {
                _graph_sprite.setTextDatum(1);
            }

            rlc::DateTime dt = rlc::DateTime::convert_to_dt((time_t)x_val);
            sprintf(buffer, "%i-%i-%i", dt.year, dt.month, dt.day);
            draw_string(buffer, x1, y1 + 8);
            sprintf(buffer, "%i:%i:%i", dt.hour, dt.minute, dt.second);
            draw_string(buffer, x1, y1 + 22);
        }
    }

    void Display::render_points(StockData &data, ChartHelper &chart_helper)
    {
        time_t x_val_1, x_val_2;
        float x1, x2, y1, y2, y_val_1, y_val_2;
        for (int i = 1; i < data.num_points; i++)
        {
            x_val_1 = data.points[i - 1].dt.epoch;
            y_val_1 = data.points[i - 1].val;

            x_val_2 = data.points[i].dt.epoch;
            y_val_2 = data.points[i].val;

            x1 = chart_helper.convert_x_val_to_pixels(x_val_1);
            y1 = chart_helper.convert_y_val_to_pixels(y_val_1);

            x2 = chart_helper.convert_x_val_to_pixels(x_val_2);
            y2 = chart_helper.convert_y_val_to_pixels(y_val_2);

            draw_line(x1, y1, x2, y2, TFT_RED);
        }
    }

    void Display::draw_string(const char *str, float x1, float y1)
    {
        _graph_sprite.drawString(str, int(x1 + _chart_padding + _legend_y), int(y1 + _chart_padding), 2);
    }

    void Display::draw_line(float x1, float y1, float x2, float y2, int color)
    {
        _graph_sprite.drawLine(x1 + _chart_padding + _legend_y, y1 + _chart_padding, x2 + _chart_padding + _legend_y, y2 + _chart_padding, color);
    }
}
