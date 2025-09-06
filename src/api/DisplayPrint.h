#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Print a text string on the sprite buffer.
 * @param L_ Lua state; expects arguments: 
 *        1: text string, 
 *        2: x (X coordinate), 
 *        3: y (Y coordinate), 
 *        4: color (16-bit RGB565) for the text.
 * @return int Pushes no values to Lua stack.
 * @note The sprite uses 16-bit RGB565 color format.
 */

int api_DisplayPrint(lua_State* L_)
{
    const char* t = luaL_checkstring(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    int c = luaL_checkinteger(L, 4);

    sprite.setTextColor(c);
    sprite.setCursor(x, y);
    sprite.print(t);
    
    return 0;
}