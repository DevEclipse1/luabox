#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Push the current sprite buffer to the display.
 * @param L_ Lua state.
 * @return int Pushes no values to Lua stack.
 * @note The sprite uses 16-bit RGB565 color format.
 */

int DisplayDraw(lua_State* L_)
{
    sprite.pushSprite(0, 0);
    
    return 0;
}