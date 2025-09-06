#pragma once

#include "api.h"
#include "global.h"
#include "buttons.h"
#include "lua_include.h"
#include "display.h"
#include "sdcard.h"

volatile bool stop_game = false;
volatile bool game_running = false;

void loader_stop_hook(lua_State* L_, lua_Debug* ar)
{
    if (stop_game)
    {
        game_running = false;
        luaL_error(L_, "STOP");
    }
}

void lua_task(void* pvParameters)
{
    sprite.fillSprite(TFT_BLACK);
    sprite.setCursor(0, 0);

    const char* path = (const char*)pvParameters;

    lua_init();
    lua_sethook(L, loader_stop_hook, LUA_MASKCOUNT, 10);

    int w = TFT_WIDTH;
    int h = TFT_HEIGHT;
    const char* error_msg = NULL;

    File f = SD.open(path, FILE_READ);
    if (!f) {
        display_draw_error("Failed to open file");
        display_draw_error(path);
    } else {
        size_t size = f.size();
        char* buffer = (char*)malloc(size + 1);
        if (!buffer) {
            display_draw_error("Out of memory");
        } else {
            f.readBytes(buffer, size);
            buffer[size] = '\0';

            int status = luaL_loadstring(L, buffer);
            if (status == LUA_OK) {
                status = lua_pcall(L, 0, LUA_MULTRET, 0);
            }

            if (status != LUA_OK) {
                const char* err = lua_tostring(L, -1);
                if (err && strcmp(err, "STOP") != 0) {
                    error_msg = err;
                }
                lua_pop(L, 1);
            }

            free(buffer);
        }
        f.close();
    }

    if (error_msg) {
        sprite.fillSprite(TFT_BLACK);
        sprite.setCursor(0, 0);
        Serial.println(error_msg);
        display_draw_error(error_msg);

        vTaskDelay(100 / portTICK_PERIOD_MS);

        while (buttons_read(SELECT)) {
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }

    lua_sethook(L, NULL, 0, 0);
    if (L) {
        lua_close(L);
        L = NULL;
    }
    game_running = false;

    vTaskDelete(NULL);
}

void loader_start_game_threaded(const char* path)
{
    stop_game = false;
    game_running = true;
    BaseType_t result = xTaskCreatePinnedToCore(
        lua_task,
        "LuaTask",
        65536,
        (void*)path,
        2,
        NULL,
        0
    );
}
