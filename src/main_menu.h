#pragma once

#include <vector>
#include <Arduino.h>
#include "global.h"
#include "buttons.h"
#include "sdcard.h"
#include "loader.h"
#include "backlight.h"

struct MainMenuItem {
    String path;

    MainMenuItem(String _path)
    {
        path = _path;
    }
};

struct SettingsItem {
    String title;
    void (*callback)();

    SettingsItem(String _title)
    {
        title = _title;
    }

    void call()
    {
        if (callback) callback();
    }
};

std::vector<MainMenuItem> main_menu_items;
int main_menu_selected_index = 0;
int previous_selected_index = -1;

std::vector<MainMenuItem> main_menu_construct_items(const std::vector<String>& list)
{
    std::vector<MainMenuItem> returns;
    for (const auto& item : list)
        returns.push_back(MainMenuItem(item));
    return returns;
}

void main_menu_set_items(const std::vector<MainMenuItem>& list)
{
    main_menu_items = list;
    main_menu_selected_index = 0;
    previous_selected_index = -1;
}

void main_menu_settings()
{
    std::vector<SettingsItem> items;

    while (!buttons_read(SET))
    {

    }
}

void main_menu_loop()
{
    static bool was_game_running = true;
    bool selection_changed = false;

    if (!game_running)
    {
        backlight_set(255);

        if (buttons_read(DOWN))
        {
            main_menu_selected_index++;
            while (buttons_read(DOWN)) delay(1);
            selection_changed = true;
        }
        else if (buttons_read(UP))
        {
            main_menu_selected_index--;
            while (buttons_read(UP)) delay(1);
            selection_changed = true;
        }
        else if (buttons_read(SELECT))
        {
            while (buttons_read(SELECT)) delay(1);

            if (main_menu_selected_index >= 0 && main_menu_selected_index < main_menu_items.size())
            {
                const String& pathStr = main_menu_items[main_menu_selected_index].path;
                if (pathStr.length() > 0)
                {
                    const char* path = pathStr.c_str();
                    game_running = true;
                    stop_game = false;
                    loader_start_game_threaded(path);
                }
            }
        }
    }
    else if (buttons_read(GET) && buttons_read(SET))
    {
        while (buttons_read(GET) && buttons_read(SET)) delay(1);
        stop_game = true;
    }
    
    if (buttons_read(SET))
    {
        main_menu_settings();
    }

    main_menu_selected_index = max(0, min(int(main_menu_items.size() - 1), main_menu_selected_index));

    bool menu_needs_refresh = false;
    if (!game_running && (selection_changed || was_game_running))
    {
        menu_needs_refresh = true;
    }

    if (menu_needs_refresh)
    {
        previous_selected_index = main_menu_selected_index;

        sprite.fillSprite(TFT_BLACK);

        int barHeight = sprite.fontHeight() + 2;
        sprite.fillRect(0, 0, tft.width(), barHeight, 0x701f);

        sprite.setTextColor(0xffff);
        sprite.setTextSize(1);
        sprite.setCursor(2, 2);
        sprite.print("LuaBox");

        uint64_t totalBytes = SD.totalBytes();
        uint64_t usedBytes = SD.usedBytes();
        uint64_t freeBytes = totalBytes - usedBytes;
        float freeGB = freeBytes / 1024.0 / 1024.0 / 1024.0;

        int gameCount = main_menu_items.size();

        uint32_t freeRAM = ESP.getFreeHeap() / 1024;

        uint32_t freeFlash = ESP.getFreeSketchSpace() / 1024;

        String infoStr = String(freeGB, 1) + "GB " +
                        String(gameCount) + "G " +
                        "RAM" + String(freeRAM) + "K " +
                        "FLH" + String(freeFlash) + "K";

        sprite.setCursor(sprite.width() - sprite.textWidth(infoStr) - 2, 2);
        sprite.print(infoStr);

        const int visible_items = 20;
        int start_idx = 0;
        if (main_menu_selected_index >= visible_items)
            start_idx = main_menu_selected_index - visible_items + 1;

        int idx = 0;
        int x_offset = 5;
        int y_offset = barHeight + 2;

        for (int i = start_idx; i < main_menu_items.size() && idx < visible_items; ++i, ++idx)
        {
            const auto& item = main_menu_items[i];
            int y_pos = y_offset + idx * sprite.fontHeight() - 2;

            if (i == main_menu_selected_index)
                sprite.drawRect(0, y_pos, sprite.width(), sprite.fontHeight() - 1, 0x701f);

            sprite.setCursor(x_offset, y_pos + 1);
            sprite.setTextColor(0xffff);
            sprite.setTextSize(1);
            sprite.print(item.path.substring(item.path.lastIndexOf('/') + 1));
        }

        sprite.pushSprite(0, 0);
    }

    was_game_running = game_running;
}
