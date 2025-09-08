#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Draw a vertical line on the sprite buffer.
 * @param L_ Lua state; expects arguments: 
 *        1: x (X coordinate), 
 *        2: y (start Y), 
 *        3: h (height), 
 *        4: color (16-bit RGB565).
 * @return int Pushes no values to Lua stack.
 * @note The sprite uses 16-bit RGB565 color format.
 */

int DisplayLineV(lua_State* L_)
{
    int x = luaL_checkinteger(L_, 1);
    int y = luaL_checkinteger(L_, 2);
    int h = luaL_checkinteger(L_, 3);
    int c = luaL_checkinteger(L_, 4);

    sprite.drawFastVLine(x, y, h, c);
    
    return 0;
}