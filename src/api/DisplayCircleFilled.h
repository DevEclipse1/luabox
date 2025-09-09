#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Draw a filled circle on the sprite buffer.
 * 
 * This function draws a filled circle on the `sprite` buffer
 * using the specified center coordinates, radius, and color.
 * 
 * @param L_ Lua state; expects arguments in order:
 *        1: x (X coordinate of the circle center)
 *        2: y (Y coordinate of the circle center)
 *        3: r (Radius of the circle)
 *        4: color (16-bit RGB565 color for the filled circle)
 * 
 * @return int Returns 0; no values are pushed to the Lua stack.
 * 
 * @note Uses 16-bit RGB565 color format for the sprite buffer.
 */
int DisplayCircleFilled(lua_State* L_)
{
    int x = luaL_checkinteger(L_, 1);
    int y = luaL_checkinteger(L_, 2);
    int r = luaL_checkinteger(L_, 3);
    int c = luaL_checkinteger(L_, 4);

    sprite.fillCircle(x, y, r, c);

    return 0;
}
