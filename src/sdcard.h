#pragma once

#include <SD.h>
#include "pins.h"
#include <vector>

bool sdcard_init()
{
    for (int i = 0; i < 10; i++) {
        if (SD.begin(SD_CS)) return true;
        delay(10);
    }
    return false;
}

std::vector<String> sdcard_read_games()
{
    std::vector<String> returns;

    if (!SD.exists("/games")) return returns;

    File dir = SD.open("/games");
    if (!dir) return returns;

    File entry;
    while (entry = dir.openNextFile()) {
        if (!entry.isDirectory()) {
            returns.push_back(entry.path());
        }
        entry.close();
    }

    dir.close();

    return returns;
}

File* open_file(const char* path)
{
    File* f = new File(SD.open(path));
    if (!f->available()) {
        delete f;
        return nullptr;
    }
    return f;
}