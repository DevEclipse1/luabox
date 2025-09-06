#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Yield execution from the current Lua coroutine.
 * @param L_ Lua state.
 * @return int Yields the coroutine; pushes no values to Lua stack.
 */

int api_Yield(lua_State* L_)
{
    return lua_yield(L, 0);
}