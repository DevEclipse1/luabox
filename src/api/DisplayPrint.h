#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Print a text string on the sprite buffer with optional scaling.
 * 
 * This function prints a text string on the `sprite` buffer using the specified color and coordinates.
 * An optional text size can be provided to scale the text.
 * 
 * @param L_ Lua state; expects arguments in order:
 *        1: text string
 *        2: x (X coordinate)
 *        3: y (Y coordinate)
 *        4: color (16-bit RGB565 for the text)
 *        5: text size (optional, default 1)
 * 
 * @return int Returns 0; no values are pushed to the Lua stack.
 * 
 * @note Uses 16-bit RGB565 color format for the sprite buffer.
 */

int DisplayPrint(lua_State* L_)
{
    const char* t = luaL_checkstring(L_, 1);
    int x = luaL_checkinteger(L_, 2);
    int y = luaL_checkinteger(L_, 3);
    int c = luaL_checkinteger(L_, 4);
    int size = 1;

    if (lua_gettop(L_) >= 5)
        size = luaL_checkinteger(L_, 5);

    sprite.setTextColor(c);
    sprite.setTextSize(size);
    sprite.setCursor(x, y);
    sprite.print(t);
    
    return 0;
}
