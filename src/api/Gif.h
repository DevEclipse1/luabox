#pragma once

#include "lua_include.h"
#include "global.h"
#include "../gif.h"

int api_GifCreate(lua_State* L)
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

int api_GifPlayAsync(lua_State* L)
{
    Gif* gif = *(Gif**)luaL_checkudata(L, 1, "LuaGif");
    gif->PlayAsync();
    return 0;
}

int api_GifStop(lua_State* L)
{
    Gif* gif = *(Gif**)luaL_checkudata(L, 1, "LuaGif");
    gif->Stop();
    return 0;
}

int api_GifGetFrameCount(lua_State* L)
{
    Gif* gif = *(Gif**)luaL_checkudata(L, 1, "LuaGif");
    lua_pushinteger(L, gif->GetFrameCount());
    return 1;
}

void RegisterGifLua(lua_State* L)
{
    if (luaL_newmetatable(L, "LuaGif"))
    {
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, api_GifPlayAsync);
        lua_setfield(L, -2, "PlayAsync");

        lua_pushcfunction(L, api_GifStop);
        lua_setfield(L, -2, "Stop");

        lua_pushcfunction(L, api_GifGetFrameCount);
        lua_setfield(L, -2, "GetFrameCount");
    }
    lua_pop(L, 1);

    lua_register(L, "GifCreate", api_GifCreate);
}
