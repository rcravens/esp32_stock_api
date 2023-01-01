#ifndef Display_h
#define Display_h

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "StockData.h"
#include "ChartHelper.h"

namespace rlc
{
    class Display
    {
    public:
        Display(TFT_eSPI *tft);
        Display(int screen_width, int screen_height, int header_height, int footer_height, TFT_eSPI *tft);
        void init();
        void render_splash();
        void render(StockData &data);

    private:
        TFT_eSPI *_tft;
        TFT_eSprite _header_sprite;
        TFT_eSprite _footer_sprite;
        TFT_eSprite _graph_sprite;

        int _screen_width;
        int _screen_height;
        int _header_height;
        int _footer_height;
        int _chart_padding;
        int _legend_x;
        int _legend_y;
        int _chart_w;
        int _chart_h;

        void render_header(StockData &data);
        void render_footer(StockData &data);
        void render_graph(StockData &data);
        void render_vertical_axis(int num_tics, ChartHelper &chart_helper);
        void render_horizontal_axis(int num_tics, ChartHelper &chart_helper);
        void render_points(StockData &data, ChartHelper &chart_helper);
        void draw_string(const char *str, float x1, float y1);
        void draw_line(float x1, float y1, float x2, float y2, int color);
    };
}

#endif
