#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Draws a rectangle (optionally with rounded corners) on the sprite buffer.
 * 
 * This function draws the outline of a rectangle on the `sprite` buffer using the specified coordinates and color.
 * An optional rounding radius can be provided for rounded corners.
 * 
 * @param L_ Lua state; expects arguments in order:
 *        1: x1 (X coordinate of top-left corner)
 *        2: y1 (Y coordinate of top-left corner)
 *        3: x2 (X coordinate of bottom-right corner)
 *        4: y2 (Y coordinate of bottom-right corner)
 *        5: color (16-bit RGB565 color)
 *        6: radius (optional, rounding radius; default 0)
 * 
 * @return int Returns 0; no values are pushed to the Lua stack.
 * 
 * @note Uses 16-bit RGB565 color format for the sprite buffer.
 */

int DisplayRect(lua_State* L_)
{
    int x1 = luaL_checkinteger(L_, 1);
    int y1 = luaL_checkinteger(L_, 2);
    int x2 = luaL_checkinteger(L_, 3);
    int y2 = luaL_checkinteger(L_, 4);
    int c = luaL_checkinteger(L_, 5);
    int r = 0;

    if (lua_gettop(L_) >= 6)
        r = luaL_checkinteger(L_, 6);

    if (r > 0)
        sprite.drawRoundRect(x1, y1, x2, y2, r, c);
    else
        sprite.drawRect(x1, y1, x2, y2, c);
    
    return 0;
}
