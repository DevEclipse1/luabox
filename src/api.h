#pragma once

#include "lua_include.h"
#include "global.h"

#include "api/DisplayPixel.h"
#include "api/DisplayClear.h"
#include "api/DisplayLine.h"
#include "api/DisplayLineH.h"
#include "api/DisplayLineV.h"
#include "api/DisplayPrint.h"
#include "api/DisplayCircle.h"
#include "api/DisplayCircleFilled.h"
#include "api/DisplayGetPixel.h"
#include "api/DisplayRect.h"
#include "api/DisplayRectFilled.h"
#include "api/DisplayTextSize.h"
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
#include "api/Millis.h"
#include "api/ScriptMillis.h"

void api_register_functions()
{
    // display stuff

    lua_pushcfunction(L, DisplayClear);
    lua_setglobal(L, "DisplayClear");

    lua_pushcfunction(L, DisplayPixel);
    lua_setglobal(L, "DisplayPixel");

    lua_pushcfunction(L, DisplayClear);
    lua_setglobal(L, "DisplayClear");

    lua_pushcfunction(L, DisplayLine);
    lua_setglobal(L, "DisplayLine");

    lua_pushcfunction(L, DisplayLineH);
    lua_setglobal(L, "DisplayLineH");

    lua_pushcfunction(L, DisplayLineV);
    lua_setglobal(L, "DisplayLineV");

    lua_pushcfunction(L, DisplayPrint);
    lua_setglobal(L, "DisplayPrint");

    lua_pushcfunction(L, DisplaySize);
    lua_setglobal(L, "DisplaySize");

    lua_pushcfunction(L, DisplayBacklight);
    lua_setglobal(L, "DisplayBacklight");

    lua_pushcfunction(L, DisplayDraw);
    lua_setglobal(L, "DisplayDraw");

    lua_pushcfunction(L, DisplayCircle);
    lua_setglobal(L, "DisplayCircle");

    lua_pushcfunction(L, DisplayCircleFilled);
    lua_setglobal(L, "DisplayCircleFilled");

    lua_pushcfunction(L, DisplayGetPixel);
    lua_setglobal(L, "DisplayGetPixel");

    lua_pushcfunction(L, DisplayRect);
    lua_setglobal(L, "DisplayRect");

    lua_pushcfunction(L, DisplayRectFilled);
    lua_setglobal(L, "DisplayRectFilled");

    lua_pushcfunction(L, DisplayTextSize);
    lua_setglobal(L, "DisplayTextSize");

    // common

    lua_pushcfunction(L, ButtonDown);
    lua_setglobal(L, "ButtonDown");

    lua_pushcfunction(L, AnyButtonDown);
    lua_setglobal(L, "AnyButtonDown");

    lua_pushcfunction(L, ButtonWaitRelease);
    lua_setglobal(L, "ButtonWaitRelease");

    lua_pushcfunction(L, Sleep);
    lua_setglobal(L, "Sleep");

    lua_pushcfunction(L, RGB);
    lua_setglobal(L, "RGB");

    lua_pushcfunction(L, HSV);
    lua_setglobal(L, "HSV");

    lua_pushcfunction(L, Yield);
    lua_setglobal(L, "Yield");

    lua_pushcfunction(L, Millis);
    lua_setglobal(L, "Millis");

    lua_pushcfunction(L, ScriptMillis);
    lua_setglobal(L, "ScriptMillis");

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