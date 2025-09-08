#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Convert 8-bit RGB values to 16-bit RGB565 color.
 * @param L_ Lua state; expects arguments: 
 *        1: r (red, 0–255), 
 *        2: g (green, 0–255), 
 *        3: b (blue, 0–255).
 * @return int Pushes 1 integer to Lua stack: 16-bit RGB565 color.
 * @note The returned color is in 16-bit RGB565 format.
 */

int RGB(lua_State* L_)
{
    int r = luaL_checkinteger(L_, 1);
    int g = luaL_checkinteger(L_, 2);
    int b = luaL_checkinteger(L_, 3);

    if (r < 0) r = 0; else if (r > 255) r = 255;
    if (g < 0) g = 0; else if (g > 255) g = 255;
    if (b < 0) b = 0; else if (b > 255) b = 255;

    uint16_t color = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);

    lua_pushinteger(L_, color);
    return 1;
}
