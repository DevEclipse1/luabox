#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Get the current system time in milliseconds.
 * @param L_ Lua state.
 * @return int Pushes 1 integer to Lua stack: current system time in milliseconds.
 */

int Millis(lua_State* L_)
{
    lua_pushinteger(L_, millis());
    return 1;
}
