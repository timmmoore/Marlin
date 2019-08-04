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
#pragma once

/**
 * English
 *
 * LCD Menu Messages
 * See also http://marlinfw.org/docs/development/lcd_language.html
 *
 */

#define en 1234
#if LCD_LANGUAGE == en
  #define NOT_EXTENDED_ISO10646_1_5X7
#endif
#undef en

#ifndef MSG_INFO_POWER_MENU
  #define MSG_INFO_POWER_MENU                 _UxGT("Power Info")
#endif

#ifndef MSG_BATTERY_CHARGED
  #define MSG_BATTERY_CHARGED                 _UxGT("Battery: Charged")
#endif
#ifndef MSG_BATTERY_CHARGING
  #define MSG_BATTERY_CHARGING                _UxGT("Battery: Charging")
#endif

#ifndef MSG_INFO_POWER_LOSS
  #define MSG_INFO_POWER_LOSS                 _UxGT("Power Loss")
#endif
