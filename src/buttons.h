#pragma once

#include "pins.h"
#include <Arduino.h>

void buttons_init()
{
    pinMode(UP, INPUT_PULLUP);
    pinMode(DOWN, INPUT_PULLUP);
    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(GET, INPUT_PULLUP);
    pinMode(SET, INPUT_PULLUP);
    pinMode(SELECT, INPUT_PULLUP);
}

bool buttons_read(int P)
{
    return digitalRead(P) == LOW;
}