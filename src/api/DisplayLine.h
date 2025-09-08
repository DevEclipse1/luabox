#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Draw a line on the sprite buffer.
 * @param L_ Lua state; expects arguments: 
 *        1: x1 (start X), 
 *        2: y1 (start Y), 
 *        3: x2 (end X), 
 *        4: y2 (end Y), 
 *        5: color (16-bit RGB565).
 * @return int Pushes no values to Lua stack.
 * @note The sprite uses 16-bit RGB565 color format.
 */

int DisplayLine(lua_State* L_)
{
    int x1 = luaL_checkinteger(L_, 1);
    int y1 = luaL_checkinteger(L_, 2);
    int x2 = luaL_checkinteger(L_, 3);
    int y2 = luaL_checkinteger(L_, 4);
    int c = luaL_checkinteger(L_, 5);

    sprite.drawLine(x1, y1, x2, y2, c);

    return 0;
}