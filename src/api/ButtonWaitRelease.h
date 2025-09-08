#pragma once

#include "lua_include.h"
#include "global.h"
#include "buttons.h"

/**
 * @brief Halt until the specified button is released.
 * @param L_ Lua state; expects first argument as string: "UP", "DOWN", "LEFT", "RIGHT", "SELECT", "GET", or "SET".
 * @return int Pushes no values to Lua stack.
 */

int ButtonWaitRelease(lua_State* L_)
{
    const char* b = luaL_checkstring(L_, 1);
    
    int p = -1;
    if (strcmp(b, "UP") == 0)
    {
        p = UP;
    } 
    else if (strcmp(b, "DOWN") == 0)
    {
        p = DOWN;
    } 
    else if (strcmp(b, "LEFT") == 0)
    {
        p = LEFT;
    } 
    else if (strcmp(b, "RIGHT") == 0)
    {
        p = RIGHT;
    }
    else if (strcmp(b, "SELECT") == 0)
    {
        p = SELECT;
    }
    else if (strcmp(b, "GET") == 0)
    {
        p = GET;
    }
    else if (strcmp(b, "SET") == 0)
    {
        p = SET;
    }

    while (buttons_read(p)) 
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return 0;
}
