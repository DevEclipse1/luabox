#pragma once
#include "global.h"
#include "smallest_pixel.h"

bool display_init()
{
    tft.init();
    tft.initDMA();
    
    tft.setRotation(3);
    sprite.setRotation(3);

    sprite.setFreeFont(&smallest_pixel_75pt7b);
    sprite.fillSprite(TFT_BLACK);
    sprite.setCursor(0, 0);
    sprite.setTextColor(TFT_RED);
    sprite.setTextSize(1);

    return true;
}

void display_draw_error(const char* err)
{
    sprite.fillSprite(TFT_BLACK);

    sprite.setTextColor(TFT_RED);
    sprite.setTextSize(1);
    sprite.println(err);

    sprite.pushSprite(0, 0);
}