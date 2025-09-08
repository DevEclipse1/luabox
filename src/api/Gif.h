#pragma once

#include "lua_include.h"
#include "global.h"
#include "../gif.h"

/**
 * @brief Create a new GIF object.
 * @param L Lua state; expects arguments: 
 *        1: path (const char*) – path to the GIF file, 
 *        2: x (int) – X position on screen, 
 *        3: y (int) – Y position on screen.
 * @return int Pushes 1 userdata to Lua stack: a LuaGif object.
 * @note Allocates memory for a new Gif instance and wraps it as Lua userdata.
*/

int GifCreate(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);

    Gif** udata = (Gif**)lua_newuserdata(L, sizeof(Gif*));
    *udata = new Gif(path, x, y);

    luaL_getmetatable(L, "LuaGif");
    lua_setmetatable(L, -2);

    return 1;
}

/**
 * @brief Play the GIF asynchronously.
 * @param L Lua state; expects argument:
 *        1: LuaGif userdata created by GifCreate.
 * @return int Returns 0; starts GIF playback in async mode.
 * @note Call this on a LuaGif object to start animation without blocking the main thread.
*/

int GifPlayAsync(lua_State* L)
{
    Gif* gif = *(Gif**)luaL_checkudata(L, 1, "LuaGif");
    gif->PlayAsync();
    return 0;
}

/**
 * @brief Stop the GIF playback.
 * @param L Lua state; expects argument:
 *        1: LuaGif userdata created by GifCreate.
 * @return int Returns 0; stops the GIF playback.
 * @note Call this on a LuaGif object to immediately halt animation.
*/

int GifStop(lua_State* L)
{
    Gif* gif = *(Gif**)luaL_checkudata(L, 1, "LuaGif");
    gif->Stop();
    return 0;
}

void RegisterGifLua(lua_State* L)
{
    if (luaL_newmetatable(L, "LuaGif"))
    {
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, GifPlayAsync);
        lua_setfield(L, -2, "PlayAsync");

        lua_pushcfunction(L, GifStop);
        lua_setfield(L, -2, "Stop");
    }
    lua_pop(L, 1);

    lua_register(L, "GifCreate", GifCreate);
}
