#pragma once

#include "lua_include.h"
#include "global.h"
#include "../backlight.h"

/**
 * @brief Set the display backlight brightness.
 * @param L_ Lua state; expects first argument as integer (0–255) for brightness level.
 * @return int Pushes no values to Lua stack.
 */

int api_DisplayBacklight(lua_State* L_)
{
    backlight_set(luaL_checkinteger(L_, 1));
    return 0;
}
