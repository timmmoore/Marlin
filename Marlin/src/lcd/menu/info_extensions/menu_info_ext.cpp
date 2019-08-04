/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//
// Info Menu
//

#include "../../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU && ENABLED(LCD_INFO_MENU) && ENABLED(HAS_MENU_INFO_EXTENSIONS)

#include "../menu.h"
#undef LANGUAGE_INCL_
#define LANGUAGE_INCL_(M) STRINGIFY_(language_##M.h)
#include INCLUDE_LANGUAGE
#include "language_en.h"

#if HAS_VOLTAGE_AVAILABLE
  #include "../../../module/temperature.h"
#endif
namespace ExtMenuInfo {
  //
  // About Printer > Power Info
  //
  void menu_info_power() {
    if (ui.use_click()) return ui.goto_previous_screen();
    START_SCREEN();
    STATIC_ITEM(MSG_INFO_PSU ": " PSU_NAME, true);
    #if ENABLED(POWER_LOSS_RECOVERY)
      #if PIN_EXISTS(POWER_LOSS)
        STATIC_ITEM(MSG_INFO_POWER_LOSS " Pin: " STRINGIFY(POWER_LOSS_PIN), true);
      #else
        STATIC_ITEM(MSG_INFO_POWER_LOSS ": " STRINGIFY(POWER_LOSS_MIN_Z_CHANGE) "mm", true);
      #endif
    #endif
    #if ENABLED(BATTERY_STATUS_AVAILABLE) && PIN_EXISTS(BATTERY_STATUS)
      if (READ(BATTERY_STATUS_PIN) != BATTERY_STATUS_CHARGED)
        STATIC_ITEM(MSG_BATTERY_CHARGING, true);
      else
        STATIC_ITEM(MSG_BATTERY_CHARGED, true);
    #endif
    #if HAS_VOLTAGE_AVAILABLE
      #if HAS_POWER_SWITCH && DISABLED(VOLTAGE_ALWAYS_AVAILABLE)
        if (!powersupply_on)
          STATIC_ITEM(MSG_INFO_POWER_VOLT "OFF", true);
        else
      #endif
        {
          char buffer[8];
          uint16_t volt = (uint16_t)(((float)thermalManager.voltage_level * DIVIDER_RATIO) + 0.5f);
          sprintf_P(buffer, PSTR("%3d.%02dV"), volt / 100, volt % 100);
          STATIC_ITEM(MSG_INFO_POWER_VOLT, false, false, buffer);
        }
    #endif
    END_SCREEN();
  }

  //
  // About Printer > Test Info
  //
  void menu_info_test() {
    if (ui.use_click()) return ui.goto_previous_screen();
    START_SCREEN();
    STATIC_ITEM("Test Info", true);
    END_SCREEN();
  }

  //
  // List of menu info submenus
  //
  static const char menu1str[] PROGMEM = MSG_INFO_POWER_MENU;
  static const char menu2str[] PROGMEM = "Test";

  MenuInfoExtensions ExtMenuInfoSubMenuInfoList = {
    { menu1str, menu_info_power },
    { menu2str, menu_info_test },
    { nullptr, nullptr }
  };
};
#endif // HAS_LCD_MENU && LCD_INFO_MENU
