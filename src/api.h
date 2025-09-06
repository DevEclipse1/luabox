#pragma once

#include "lua_include.h"
#include "global.h"

#include "api/DisplayPixel.h"
#include "api/DisplayClear.h"
#include "api/DisplayLine.h"
#include "api/DisplayLineH.h"
#include "api/DisplayLineV.h"
#include "api/DisplayPrint.h"
#include "api/DisplaySize.h"
#include "api/DisplayBacklight.h"
#include "api/DisplayDraw.h"
#include "api/ButtonWaitRelease.h"
#include "api/Sleep.h"
#include "api/ButtonDown.h"
#include "api/AnyButtonDown.h"
#include "api/RGB.h"
#include "api/HSV.h"
#include "api/Yield.h"
#include "api/Gif.h"

void api_register_functions()
{
    // display stuff

    lua_pushcfunction(L, api_DisplayClear);
    lua_setglobal(L, "DisplayClear");

    lua_pushcfunction(L, api_DisplayPixel);
    lua_setglobal(L, "DisplayPixel");

    lua_pushcfunction(L, api_DisplayClear);
    lua_setglobal(L, "DisplayClear");

    lua_pushcfunction(L, api_DisplayLine);
    lua_setglobal(L, "DisplayLine");

    lua_pushcfunction(L, api_DisplayLineH);
    lua_setglobal(L, "DisplayLineH");

    lua_pushcfunction(L, api_DisplayLineV);
    lua_setglobal(L, "DisplayLineV");

    lua_pushcfunction(L, api_DisplayPrint);
    lua_setglobal(L, "DisplayPrint");

    lua_pushcfunction(L, api_DisplaySize);
    lua_setglobal(L, "DisplaySize");

    lua_pushcfunction(L, api_DisplayBacklight);
    lua_setglobal(L, "DisplayBacklight");

    lua_pushcfunction(L, api_DisplayDraw);
    lua_setglobal(L, "DisplayDraw");

    // common

    lua_pushcfunction(L, api_ButtonDown);
    lua_setglobal(L, "ButtonDown");

    lua_pushcfunction(L, api_AnyButtonDown);
    lua_setglobal(L, "AnyButtonDown");

    lua_pushcfunction(L, api_ButtonWaitRelease);
    lua_setglobal(L, "ButtonWaitRelease");

    lua_pushcfunction(L, api_Sleep);
    lua_setglobal(L, "Sleep");

    lua_pushcfunction(L, api_RGB);
    lua_setglobal(L, "RGB");

    lua_pushcfunction(L, api_HSV);
    lua_setglobal(L, "HSV");

    lua_pushcfunction(L, api_Yield);
    lua_setglobal(L, "Yield");

    // gif

    RegisterGifLua(L);
}

void lua_init()
{
    L = luaL_newstate();
    luaopen_math(L);
    luaopen_table(L);
    luaopen_utf8(L);
    luaopen_string(L);
    luaopen_package(L);
    luaopen_coroutine(L);
    luaopen_base(L);
    api_register_functions();
}