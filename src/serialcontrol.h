#pragma once
#include <Arduino.h>
#include "loader.h"
#include <SD.h>

void serial_control_task(void* parameter) {
    String buffer = "";

    while (true) {
        while (Serial.available() > 0) {
            char c = Serial.read();
            buffer += c;
        }

        if (buffer.endsWith("<<<END>>>")) {
            buffer.replace("<<<END>>>", "");

            SD.mkdir("/temp");

            SD.remove("/temp/tempcode.lua");
            File file = SD.open("/temp/tempcode.lua", FILE_WRITE);
            if (file) {
                file.print(buffer);
                file.close();

                vTaskDelay(100 / portTICK_PERIOD_MS);

                char* path_copy = strdup("/temp/tempcode.lua");
                loader_start_game_threaded(path_copy);

                buffer = "";
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void serialcontrol_init() {
    xTaskCreatePinnedToCore(
        serial_control_task,
        "SerialControlTask",
        8192,
        NULL,
        1,
        NULL,
        1
    );
}
