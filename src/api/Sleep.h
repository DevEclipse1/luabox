#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Pause execution for a specified time.
 * @param L_ Lua state; expects first argument as integer duration in milliseconds.
 * @return int Pushes no values to Lua stack.
 */

int api_Sleep(lua_State* L_)
{
    int t = luaL_checkinteger(L_, 1);
    vTaskDelay(pdMS_TO_TICKS(t));

    return 0;
}