#pragma once

#include <Arduino.h>
#include "global.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void sprite_init()
{
    tft.setRotation(3);
    sprite.createSprite(tft.width(), tft.height());
    sprite.setRotation(3);
}
