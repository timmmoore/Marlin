/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
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

// PT100 with LMV324 amp on Overlord v1.1 electronics
//
// This does not match the normal thermistor behaviour so we need to set the following defines
#if THERMISTOR_HEATER_0 == 201
  #define HEATER_0_RAW_HI_TEMP 16383
  #define HEATER_0_RAW_LO_TEMP 0
#endif
#if THERMISTOR_HEATER_1 == 201
  #define HEATER_1_RAW_HI_TEMP 16383
  #define HEATER_1_RAW_LO_TEMP 0
#endif
#if THERMISTOR_HEATER_2 == 201
  #define HEATER_2_RAW_HI_TEMP 16383
  #define HEATER_2_RAW_LO_TEMP 0
#endif
#if THERMISTOR_HEATER_3 == 201
  #define HEATER_3_RAW_HI_TEMP 16383
  #define HEATER_3_RAW_LO_TEMP 0
#endif
#if THERMISTOR_HEATER_4 == 201
  #define HEATER_4_RAW_HI_TEMP 16383
  #define HEATER_4_RAW_LO_TEMP 0
#endif
#if THERMISTOR_HEATER_5 == 201
  #define HEATER_5_RAW_HI_TEMP 16383
  #define HEATER_5_RAW_LO_TEMP 0
#endif
#if THERMISTORBED == 201
  #define HEATER_BED_RAW_HI_TEMP 16383
  #define HEATER_BED_RAW_LO_TEMP 0
#endif
#if THERMISTORCHAMBER == 201
  #define HEATER_CHAMBER_RAW_HI_TEMP 16383
  #define HEATER_CHAMBER_RAW_LO_TEMP 0
#endif

const short temptable_201[][2] PROGMEM = {
  {     OV(0),       0       },
  {     OV(8),       1       },
  {    OV(23),       6       },
  {    OV(43),       15      },
  {    OV(55),       20      },
  {    OV(70),       28      },
  {    OV(90),       37      },
  {   OV(155),       63      },
  {   OV(274),       110     },
  {   OV(298),       120     },
  {   OV(321),       129     },
  {   OV(345),       139     },
  {   OV(367),       151     },
  {   OV(391),       159     },
  {   OV(414),       169     },
  {   OV(438),       179     },
  {   OV(460),       190     },
  {   OV(483),       200     },
  {   OV(505),       210     },
  {   OV(528),       220     },
  {   OV(548),       230     },
  {   OV(572),       239     },
  {  OV(1155),       499     }
};
