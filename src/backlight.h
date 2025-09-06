#pragma once

#include "global.h"

void backlight_setup()
{
    ledcSetup(0, 5000, 8);
    ledcAttachPin(TFT_BL, 0);
}

void backlight_set(int x)
{
    ledcWrite(0, x);
}