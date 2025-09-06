#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Clear the display sprite buffer to a given color.
 * @param L_ Lua state; optional first argument as 16-bit RGB565 color (default 0x0000 = black).
 * @return int Pushes no values to Lua stack.
 */

int api_DisplayClear(lua_State* L_)
{
    int c = luaL_optinteger(L_, 1, 0x0);

    sprite.fillSprite(c);

    return 0;
}
