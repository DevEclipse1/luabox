#include "global.h"
#include "display.h"
#include "sdcard.h"
#include "buttons.h"
#include "api.h"
#include "main_menu.h"
#include "serialcontrol.h"
#include "backlight.h"
#include "gif.h"

void setup(void) {
  Serial.begin(115200);

  buttons_init();
  display_init();
  sprite_init();
  backlight_setup();
  backlight_set(255);

  if (!sdcard_init())
  {
    tft.print("Failed to init SD");
  }
  
  serialcontrol_init();
  main_menu_set_items(main_menu_construct_items(sdcard_read_games()));
}

void loop() {
  main_menu_loop();
}
