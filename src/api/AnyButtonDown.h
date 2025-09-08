#pragma once

#include "lua_include.h"
#include "global.h"
#include "buttons.h"

/**
 * @brief Check if any button is currently pressed.
 * @param L_ Lua state.
 * @return int Pushes 1 boolean to Lua stack: true if any button (UP, DOWN, LEFT, RIGHT, SET, GET) is pressed, false otherwise.
 */

int AnyButtonDown(lua_State* L_)
{
    lua_pushboolean(L_, buttons_read(UP) || buttons_read(DOWN) || buttons_read(LEFT) || buttons_read(RIGHT) || buttons_read(SET) || buttons_read(GET));

    return 1;
}
