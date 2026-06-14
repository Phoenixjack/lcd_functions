# lcd_functions

A small Arduino 16x2 LCD helper sketch/library for displaying basic system status and button input state.

This project wraps common `LiquidCrystal` display setup and update behavior into a lightweight helper for small embedded projects. It was built around a 16x2 character LCD and a companion resistor-ladder button input helper.

## Project Status

Prototype / utility code.

This repo is intended as a reusable personal helper for small Arduino-style projects, not a polished display framework.

## Target Hardware

This code is intended for:

* Arduino-compatible boards
* HD44780-compatible 16x2 character LCD
* parallel LCD wiring using the Arduino `LiquidCrystal` library
* companion button input from `button_resistor_network`

The current LCD size is defined as:

```cpp
#define LCDRows 2
#define LCDColumns 16
```

The current LCD pin mapping is:

```cpp
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
```

## Dependencies

Required:

- Arduino framework
- `LiquidCrystal`
- [`button_resistor_network`](https://github.com/Phoenixjack/button_resistor_network)
- `icons.h`

The demo sketch currently includes:

```cpp
#include <button_resistor_network.h>
#include "lcd_functions.h"

## What It Does

The helper code provides:

* LCD initialization
* custom character/icon registration
* basic display-ready boot message
* timed refresh throttling
* display state tracking
* simple draw modes
* button/action status display
* support for small UI feedback on a 16x2 LCD

## Display Behavior

On startup, the display is initialized and shows:

```text
Display ready
<custom icons>
```

During standard operation, the display shows:

```text
online        XY
<millis>
```

Where the upper-right characters show button and action status.

## Button / Action Display

The helper displays button state and action state at LCD columns 14 and 15 on the first row.

Button indicators include:

| Input                 | Display    |
| --------------------- | ---------- |
| Up                    | up icon    |
| Down                  | down icon  |
| Left                  | left icon  |
| Right                 | right icon |
| Select                | `o`        |
| No button / end state | blank      |
| No press              | `_`        |

Action indicators include:

| Action      | Display     |
| ----------- | ----------- |
| Long press  | `L`         |
| Short press | `S`         |
| Canceled    | cancel icon |
| Released    | `R`         |
| No press    | `N`         |
| End state   | blank       |

## Draw Modes

The current `draw` helper defines several display modes:

```cpp
enum DRAW_MODE {
  DRAW_BOOTSCREEN,
  DRAW_STANDARD,
  DRAW_DIAGNOSTICS,
  DRAW_END_OF_LIST
};
```

At the moment, `DRAW_STANDARD` is the main implemented mode.

## Repository Contents

| File                | Purpose                          |
| ------------------- | -------------------------------- |
| `lcd_functions.ino` | Demo sketch / test harness       |
| `lcd_functions.h`   | LCD helper logic                 |
| `icons.h`           | Custom LCD character byte arrays |

## Suggested Arduino IDE Layout

The Arduino IDE expects the sketch folder and main `.ino` file to share the same name.

Recommended layout:

```text
lcd_functions/
├── lcd_functions.ino
├── lcd_functions.h
├── icons.h
├── README.md
└── LICENSE
```

## Known Limitations

* Prototype utility code
* Hard-coded LCD size: 16 columns x 2 rows
* Hard-coded LCD pin mapping
* Depends on external button resistor network definitions
* Custom icons must be supplied by `icons.h`
* Not a general-purpose menu framework
* Not formally tested across multiple LCD modules or Arduino boards
* No warranty or support commitment

## Possible Future Improvements

Possible future improvements:

* make LCD pins configurable
* make row/column count configurable
* add a proper example folder
* add wiring diagram
* remove dependency on global state
* split into `.h` and `.cpp`
* make button/action display optional
* add menu rendering helpers
* add clearer diagnostics mode
* document custom icon byte arrays


And maybe add a small **Related Repositories** section near the bottom:

```md
## Related Repositories

- [`button_resistor_network`](https://github.com/Phoenixjack/button_resistor_network) - companion helper for resistor-ladder button input

## License

This project is released under the MIT License.

You are free to use, modify, and adapt it for your own projects. No warranty is provided, and no ongoing support or maintenance is implied.
