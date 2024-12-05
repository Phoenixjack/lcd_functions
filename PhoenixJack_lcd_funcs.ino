#include <PhoenixJack_button_resistor_network.h>

ACTION_id lastaction = ACTION_END_OF_LIST;
BUTTON_id lastbutton = ID_END_OF_LIST;
unsigned long button_timeout = 0;
#include "PhoenixJack_lcd_funcs.h"

void setup() {
  Serial.begin(9600);
  button_array.setup_values();
  disp.init();
}

void loop() {
  if (button_array.check()) {
    button_timeout = millis() + 1000;
    if (button_array.pressed) {
      lastbutton = button_array.currentid;
    } else {
      lastaction = button_array.currentaction;
    }
  }
  if (millis() > button_timeout && !button_array.pressed) {
    lastbutton = ID_END_OF_LIST;
    lastaction = ACTION_END_OF_LIST;
  }
  draw.update(draw::DRAW_STANDARD);
}