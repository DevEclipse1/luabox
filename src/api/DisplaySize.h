#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Get the current display size.
 * @param L_ Lua state.
 * @return int Pushes a Lua table with keys:
 *         - "x": width of the display in pixels
 *         - "y": height of the display in pixels
 */

int api_DisplaySize(lua_State* L)
{
    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushinteger(L, tft.width());
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushinteger(L, tft.height());
    lua_settable(L, -3);

    return 1;
}
