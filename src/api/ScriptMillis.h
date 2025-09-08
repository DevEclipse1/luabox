#pragma once

#include "lua_include.h"
#include "global.h"

static unsigned long script_start_time = 0;

/**
 * @brief Get the time in milliseconds since the script started running.
 * @param L_ Lua state.
 * @return int Pushes 1 integer to Lua stack: milliseconds since script start.
 */

int ScriptMillis(lua_State* L_)
{
    if (script_start_time == 0) {
        script_start_time = millis();
    }
    
    lua_pushinteger(L_, millis() - script_start_time);
    return 1;
}

void reset_script_time()
{
    script_start_time = millis();
}
