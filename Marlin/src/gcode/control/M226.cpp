/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if ENABLED(DIRECT_PIN_CONTROL)

#include "../gcode.h"
#include "../../MarlinCore.h" // for pin_is_protected and idle()
<<<<<<< HEAD
#include "../../module/planner.h"
=======
#include "../../module/stepper.h"
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

void protected_pin_err();

/**
 * M226: Wait until the specified pin reaches the state required (M226 P<pin> S<state>)
 */
void GcodeSuite::M226() {
  if (parser.seen('P')) {
    const int pin_number = PARSED_PIN_INDEX('P', 0),
              pin_state = parser.intval('S', -1); // required pin state - default is inverted
    const pin_t pin = GET_PIN_MAP_PIN(pin_number);

    if (WITHIN(pin_state, -1, 1) && pin > -1) {
      if (pin_is_protected(pin))
        protected_pin_err();
      else {
        int target = LOW;
        planner.synchronize();
        pinMode(pin, INPUT);
        switch (pin_state) {
          case 1: target = HIGH; break;
          case 0: target = LOW; break;
          case -1: target = !extDigitalRead(pin); break;
        }
        while (int(extDigitalRead(pin)) != target) idle();
      }
    } // pin_state -1 0 1 && pin > -1
  } // parser.seen('P')
}

#endif // DIRECT_PIN_CONTROL
