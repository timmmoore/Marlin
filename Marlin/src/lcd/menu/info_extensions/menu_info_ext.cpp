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

#if HAS_LCD_MENU && ENABLED(LCD_INFO_MENU) && defined(HAS_MENU_INFO_EXTENSIONS)

#include "../menu.h"
#undef LANGUAGE_INCL_
#define LANGUAGE_INCL_(M) STRINGIFY_(language_##M.h)
#include INCLUDE_LANGUAGE
#include "language_en.h"

/*
 * If input voltage is measured then display in Board info menu page
 * Assumes a resistor divider network to lower voltage to something ADC can handle
 *  E.g. 12V: Divider upper 180K, Divider lower 91K
 *  E.g. 24V: Divider upper 240K, Divider lower 47K
 * Calculate translation from ADC reading to voltage
 */
#if HAS_VOLTAGE_AVAILABLE
  #include "../../../module/temperature.h"

  #define DIVIDER_UPPER           239.16f // total resistance of divider network
  #define DIVIDER_LOWER           48.84f  // lower resistance of divider network
  #define ADC_VREF                5.0f    // Whatever the ADC AREF is, default is 5.0V
  #define ADC_RESOLUTION          1024
  #define DIVIDER_RATIO           (((ADC_VREF * (DIVIDER_UPPER + DIVIDER_LOWER)) / (DIVIDER_LOWER * ADC_RESOLUTION)) * 100.0f)
  #define VOLTAGE_ALWAYS_AVAILABLE        // If input voltage is always available
#endif

/*
 * A chargable battery supporting power loss, i.e. powers board when power loss occurs
 * If a pin is available to see if battery is charged will show battery status in menu info
 */
//#define BATTERY_STATUS_AVAILABLE
#if ENABLED(BATTERY_STATUS_AVAILABLE)
  //#define BATTERY_STATUS_PIN    -1
  #define BATTERY_STATUS_CHARGED  LOW
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
      #if ENABLED(VOLTAGE_WARNING)
        STATIC_ITEM(MSG_INPUT_VOLTAGE_CHECK_OFF, false, true);
      #else
        STATIC_ITEM(MSG_INPUT_VOLTAGE_CHECK_ON, false, true);
      #endif
    #endif
    END_SCREEN();
  }

  //
  // List of menu info submenus
  //
  static const char menu1str[] PROGMEM = MSG_INFO_POWER_MENU;

  MenuInfoExtensions ExtMenuInfoPower = {
    { menu1str, menu_info_power },
    { nullptr, nullptr }
  };
};
#endif // HAS_LCD_MENU && LCD_INFO_MENU
