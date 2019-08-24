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

#include "../../../inc/MarlinConfig.h"

#if HAS_FILAMENT_SENSOR

#include "../../gcode.h"
#include "../../../feature/runout.h"

static void print_ro_state(const bool value, PGM_P const label = nullptr) {
  if(label) serialprintPGM(label);
  SERIAL_ECHOPGM(": ");
  serialprintPGM(value ? PSTR(MSG_ENDSTOP_OK) : PSTR(MSG_FILAMENT_OPEN));
  SERIAL_EOL();
}

/**
 * M412: Enable / Disable filament runout detection
 */
void GcodeSuite::M412() {
  if (parser.seen("RS"
    #ifdef FILAMENT_RUNOUT_DISTANCE_MM
      "D"
    #endif
    #if ENABLED(HOST_ACTION_COMMANDS)
      "H"
    #endif
  )) {
    #if ENABLED(HOST_ACTION_COMMANDS)
      if (parser.seen('H')) runout.host_handling = parser.value_bool();
    #endif
    const bool seenR = parser.seen('R'), seenS = parser.seen('S');
    if (seenR || seenS) runout.reset();
    if (seenS) runout.enabled = parser.value_bool();
    #ifdef FILAMENT_RUNOUT_DISTANCE_MM
      if (parser.seen('D')) runout.set_runout_distance(parser.value_linear_units());
    #endif
  }
  else {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Filament runout ");
    serialprintln_onoff(runout.enabled);
    #ifdef FILAMENT_RUNOUT_DISTANCE_MM
      SERIAL_ECHOLNPAIR("Filament runout distance (mm): ", runout.runout_distance());
    #endif
    #if NUM_RUNOUT_SENSORS == 1
      print_ro_state(READ(FIL_RUNOUT_PIN) != FIL_RUNOUT_INVERTING, PSTR(MSG_FILAMENT_RUNOUT_SENSOR));
    #else
      for (uint8_t i = 1; i <= NUM_RUNOUT_SENSORS; i++) {
        pin_t pin;
        switch (i) {
          default: continue;
          case 1: pin = FIL_RUNOUT_PIN; break;
          case 2: pin = FIL_RUNOUT2_PIN; break;
          #if NUM_RUNOUT_SENSORS > 2
            case 3: pin = FIL_RUNOUT3_PIN; break;
            #if NUM_RUNOUT_SENSORS > 3
              case 4: pin = FIL_RUNOUT4_PIN; break;
              #if NUM_RUNOUT_SENSORS > 4
                case 5: pin = FIL_RUNOUT5_PIN; break;
                #if NUM_RUNOUT_SENSORS > 5
                  case 6: pin = FIL_RUNOUT6_PIN; break;
                #endif
              #endif
            #endif
          #endif
        }
        SERIAL_ECHOPGM(MSG_FILAMENT_RUNOUT_SENSOR);
        if (i > 1) { SERIAL_CHAR(' '); SERIAL_CHAR('0' + i); }
        print_ro_state(extDigitalRead(pin) != FIL_RUNOUT_INVERTING, nullptr;
      }
    #endif
  }
}

#endif // HAS_FILAMENT_SENSOR
