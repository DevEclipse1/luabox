#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Draw a single pixel on the sprite buffer.
 * @param L_ Lua state; expects arguments: 
 *        1: x (X coordinate), 
 *        2: y (Y coordinate), 
 *        3: color (16-bit RGB565).
 * @return int Pushes no values to Lua stack.
 * @note The sprite uses 16-bit RGB565 color format.
 */

int DisplayPixel(lua_State* L_)
{
    int x = luaL_checkinteger(L_, 1);
    int y = luaL_checkinteger(L_, 2);
    int c = luaL_checkinteger(L_, 3);

    sprite.drawPixel(x, y, c);
    
    return 0;
}
