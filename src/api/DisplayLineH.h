#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Draw a horizontal line on the sprite buffer.
 * @param L_ Lua state; expects arguments: 
 *        1: x (start X), 
 *        2: y (Y coordinate), 
 *        3: w (width), 
 *        4: color (16-bit RGB565).
 * @return int Pushes no values to Lua stack.
 * @note The sprite uses 16-bit RGB565 color format.
 */

int DisplayLineH(lua_State* L_)
{
    int x = luaL_checkinteger(L_, 1);
    int y = luaL_checkinteger(L_, 2);
    int w = luaL_checkinteger(L_, 3);
    int c = luaL_checkinteger(L_, 4);

    sprite.drawFastHLine(x, y, w, c);
    
    return 0;
}