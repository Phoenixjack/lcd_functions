#include "Arduino.h"
#include <stdint.h>
#include <LiquidCrystal.h>  // https://github.com/arduino-libraries/LiquidCrystal
#define LCDRows 2           // LCD definition
#define LCDColumns 16       // LCD definition

enum icons {  // reference for our icon registers
  ICON_CANCEL,
  ICON_UP,
  ICON_DOWN,
  ICON_LEFT,
  ICON_RIGHT,
  ICON_FINGER,
  ICON_XMT,
  ICON_RCV
};
#include "icons.h"
//const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

struct disp {
  friend struct draw;
  bool ready = false;                   // global flag for tracking if LCD is started
  bool enabled = false;                 // global flag for tracking if LCD is enabled
  unsigned long refreshinterval = 500;  // minimum number of ms before performing a screen update
  unsigned long nextupdate = millis();  // for marking time we last updated the LCD; used to avoid excessive refresh
  unsigned long timeout = 30000;        // timeout before blanking screen in ms
  unsigned long timeout_time;           // will hold the millis() when the screen will timeout if no user input is received
  bool init() {
    lcd.begin(LCDColumns, LCDRows);
    lcd.createChar(ICON_CANCEL, cancelicon);
    lcd.createChar(ICON_UP, upicon);
    lcd.createChar(ICON_DOWN, downicon);
    lcd.createChar(ICON_FINGER, fingericon);
    lcd.createChar(ICON_XMT, xmticon);
    lcd.createChar(ICON_RCV, rcvicon);
    lcd.createChar(ICON_LEFT, lefticon);
    lcd.createChar(ICON_RIGHT, righticon);
    ready = true;
    enabled = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Display ready");
    lcd.setCursor(0, 1);
    for (uint8_t i = 0; i < 8; i++) {
      lcd.write(i);
    }
    nextupdate = millis() + 5000;
    //delay(1000);
    return ready;
  };
  bool can_update() {
    if (millis() > nextupdate) {
      nextupdate = millis() + refreshinterval;
      enabled = true;
      return true;
    } else {
      return false;
    }
  };
} disp;

struct draw {
  enum DRAW_MODE {
    DRAW_BOOTSCREEN,
    DRAW_STANDARD,
    DRAW_DIAGNOSTICS,
    DRAW_END_OF_LIST
  };
  bool auto_cycle = false;
  unsigned long mode_next_change = 0;
  DRAW_MODE curr_mode = DRAW_BOOTSCREEN;
  DRAW_MODE last_mode = DRAW_BOOTSCREEN;
  void advance_mode() {
    uint8_t next_mode = curr_mode + 1;
    if (next_mode >= DRAW_END_OF_LIST) { next_mode = DRAW_STANDARD; }
    curr_mode = (DRAW_MODE)next_mode;
    mode_next_change = millis() + 20000;
  };
  void update(DRAW_MODE mode = DRAW_STANDARD) {
    if (curr_mode != mode) { curr_mode = mode; }
    if (curr_mode != last_mode) { lcd.clear(); }
    if (disp.can_update()) {
      switch (curr_mode) {
        case DRAW_BOOTSCREEN:
          //
          break;
        case DRAW_STANDARD:
          lcd.setCursor(0, 0);
          lcd.print("online");
          lcd.setCursor(0, 1);
          lcd.print(millis());
          button();
          break;
        case DRAW_DIAGNOSTICS:
          //
          break;
        default:
          //
          break;
      }
    }
    last_mode = curr_mode;
    if (auto_cycle && millis() > mode_next_change) { advance_mode(); }
  };
  void button();
} draw;

void draw::button() {
  lcd.setCursor(14, 0);
  switch (lastbutton) {
    case ID_UP:
      lcd.write(ICON_UP);
      break;
    case ID_DOWN:
      lcd.write(ICON_DOWN);
      break;
    case ID_LEFT:
      lcd.write(ICON_LEFT);
      break;
    case ID_RIGHT:
      lcd.write(ICON_RIGHT);
      break;
    case ID_SELECT:
      lcd.write('o');
      break;
    case ID_END_OF_LIST:
      lcd.write(' ');
      break;
    case ID_NO_PRESS:
      lcd.write('_');
      break;
    default:
      break;
  }
  lcd.setCursor(15, 0);
  switch (lastaction) {
    case ACTION_LONGPRESS:
      lcd.write('L');
      break;
    case ACTION_SHORTPRESS:
      lcd.write('S');
      break;
    case ACTION_CANCELED:
      lcd.write(ICON_CANCEL);
      break;
    case ACTION_RELEASED:
      lcd.write('R');
      break;
    case ACTION_NOPRESS:
      lcd.write('N');
      break;
    case ACTION_END_OF_LIST:
      lcd.write(' ');
      break;
    default:
      break;
  }
};
