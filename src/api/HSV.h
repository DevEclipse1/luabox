#pragma once

#include "lua_include.h"
#include "global.h"
#include <cmath>

/**
 * @brief Convert HSV color to 16-bit RGB565.
 * @param L_ Lua state; expects arguments: 
 *        1: h (hue, 0–360), 
 *        2: s (saturation, 0–1), 
 *        3: v (value/brightness, 0–1).
 * @return int Pushes 1 integer to Lua stack: 16-bit RGB565 color.
 * @note The returned color is in 16-bit RGB565 format.
 */

int api_HSV(lua_State* L_)
{
    double h = luaL_checknumber(L_, 1);
    double s = luaL_checknumber(L_, 2);
    double v = luaL_checknumber(L_, 3);

    if (s < 0) s = 0; else if (s > 1) s = 1;
    if (v < 0) v = 0; else if (v > 1) v = 1;
    while (h < 0) h += 360;
    while (h >= 360) h -= 360;

    double c = v * s;
    double x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    double m = v - c;

    double r1, g1, b1;
    if (h < 60)       { r1 = c; g1 = x; b1 = 0; }
    else if (h < 120) { r1 = x; g1 = c; b1 = 0; }
    else if (h < 180) { r1 = 0; g1 = c; b1 = x; }
    else if (h < 240) { r1 = 0; g1 = x; b1 = c; }
    else if (h < 300) { r1 = x; g1 = 0; b1 = c; }
    else              { r1 = c; g1 = 0; b1 = x; }

    int r = (int)((r1 + m) * 31);
    int g = (int)((g1 + m) * 63);
    int b = (int)((b1 + m) * 31);

    uint16_t color = (r << 11) | (g << 5) | b;
    lua_pushinteger(L_, color);

    return 1;
}