#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Get the color of a pixel from the sprite buffer.
 * 
 * This function reads the color of a specific pixel from the `sprite` buffer.
 * The color is returned as a 16-bit RGB565 value.
 * 
 * @param L_ Lua state; expects arguments in order:
 *        1: x (X coordinate of the pixel)
 *        2: y (Y coordinate of the pixel)
 * 
 * @return int Returns 1 value on the Lua stack:
 *         - 16-bit RGB565 color of the pixel at the specified coordinates.
 * 
 */

int DisplayGetPixel(lua_State* L_)
{
    int x = luaL_checkinteger(L_, 1);
    int y = luaL_checkinteger(L_, 2);
    
    lua_pushinteger(L_, sprite.readPixel(x, y));
    
    return 1;
}
