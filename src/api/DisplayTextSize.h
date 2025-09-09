#pragma once

#include "lua_include.h"
#include "global.h"

/**
 * @brief Calculate the pixel width and height of a text string on the sprite buffer.
 * 
 * This function calculates the width and height of a given text string when drawn on the `sprite` buffer,
 * taking into account the current font and an optional text size multiplier. It also accounts for multiple
 * lines if the string contains `\n` characters.
 * 
 * @param L_ Lua state; expects arguments in order:
 *        1: text string
 *        2: text size (optional, default 1)
 * 
 * @return int Returns a Lua table with the following fields:
 *         - "x": pixel width of the text
 *         - "y": pixel height of the text, including multiple lines
 * 
 * @note Uses the current font of the sprite buffer.
 */

int DisplayTextSize(lua_State* L_)
{
    int arg_count = lua_gettop(L_);

    const char* t = luaL_checkstring(L_, 1);
    int size = 1;

    if (arg_count >= 2)
        size = luaL_checkinteger(L_, 2);

    int sx = tft.textWidth(t);

    int lines = 1;
    for (const char* p = t; *p; p++)
        if (*p == '\n')
            lines++;

    int sy = lines * tft.fontHeight() * size;

    lua_newtable(L_);
    lua_pushinteger(L_, sx);
    lua_setfield(L_, -2, "x");

    lua_pushinteger(L_, sy);
    lua_setfield(L_, -2, "y");

    return 1;
}
