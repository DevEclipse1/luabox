#pragma once

#include "lua_include.h"
#include "global.h"
#include "../gif.h"

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

int GifPlayAsync(lua_State* L)
{
    Gif* gif = *(Gif**)luaL_checkudata(L, 1, "LuaGif");
    gif->PlayAsync();
    return 0;
}

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
