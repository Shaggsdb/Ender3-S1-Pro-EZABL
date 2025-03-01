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

#include "../../../inc/MarlinConfig.h"

#if HAS_COLOR_LEDS

#include "../../gcode.h"
#include "../../../feature/leds/leds.h"

/**
 * M150: Set Status LED Color - Use R-U-B-W for R-G-B-W
 *       and Brightness       - Use P (for NEOPIXEL only)
 *
<<<<<<< HEAD
 * Always sets all 3 or 4 components unless the K flag is specified.
 *                              If a component is left out, set to 0.
 *                              If brightness is left out, no value changed.
 *
 * With NEOPIXEL_LED:
 *  I<index>  Set the NeoPixel index to affect. Default: All
 *  K         Keep all unspecified values unchanged instead of setting to 0.
=======
 * Always sets all 3 or 4 components. If a component is left out, set to 0.
 *                                    If brightness is left out, no value changed
 *
 * With NEOPIXEL_LED:
 *  I<index>  Set the NeoPixel index to affect. Default: All
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
 *
 * With NEOPIXEL2_SEPARATE:
 *  S<index>  The NeoPixel strip to set. Default: All.
 *
 * Examples:
 *
 *   M150 R255       ; Turn LED red
 *   M150 R255 U127  ; Turn LED orange (PWM only)
 *   M150            ; Turn LED off
 *   M150 R U B      ; Turn LED white
 *   M150 W          ; Turn LED white using a white LED
 *   M150 P127       ; Set LED 50% brightness
 *   M150 P          ; Set LED full brightness
 *   M150 I1 R       ; Set NEOPIXEL index 1 to red
 *   M150 S1 I1 R    ; Set SEPARATE index 1 to red
<<<<<<< HEAD
 *   M150 K R127     ; Set LED red to 50% without changing blue or green
 */
void GcodeSuite::M150() {
  int32_t old_color = 0;

=======
 */
void GcodeSuite::M150() {
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
  #if ENABLED(NEOPIXEL_LED)
    const pixel_index_t index = parser.intval('I', -1);
    #if ENABLED(NEOPIXEL2_SEPARATE)
      int8_t brightness = neo.brightness(), unit = parser.intval('S', -1);
      switch (unit) {
        case -1: neo2.neoindex = index; // fall-thru
<<<<<<< HEAD
        case  0:  neo.neoindex = index; old_color = parser.seen('K') ? neo.pixel_color(index >= 0 ? index : 0) : 0; break;
        case  1: neo2.neoindex = index; brightness = neo2.brightness(); old_color = parser.seen('K') ? neo2.pixel_color(index >= 0 ? index : 0) : 0; break;
=======
        case  0:  neo.neoindex = index; break;
        case  1: neo2.neoindex = index; brightness = neo2.brightness(); break;
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
      }
    #else
      const uint8_t brightness = neo.brightness();
      neo.neoindex = index;
    #endif
  #endif

  const LEDColor color = LEDColor(
<<<<<<< HEAD
    parser.seen('R') ? (parser.has_value() ? parser.value_byte() : 255) : (old_color >> 16) & 0xFF,
    parser.seen('U') ? (parser.has_value() ? parser.value_byte() : 255) : (old_color >>  8) & 0xFF,
    parser.seen('B') ? (parser.has_value() ? parser.value_byte() : 255) : old_color & 0xFF
    OPTARG(HAS_WHITE_LED, parser.seen('W') ? (parser.has_value() ? parser.value_byte() : 255) : (old_color >> 24) & 0xFF)
=======
    parser.seen('R') ? (parser.has_value() ? parser.value_byte() : 255) : 0,
    parser.seen('U') ? (parser.has_value() ? parser.value_byte() : 255) : 0,
    parser.seen('B') ? (parser.has_value() ? parser.value_byte() : 255) : 0
    OPTARG(HAS_WHITE_LED, parser.seen('W') ? (parser.has_value() ? parser.value_byte() : 255) : 0)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
    OPTARG(NEOPIXEL_LED, parser.seen('P') ? (parser.has_value() ? parser.value_byte() : 255) : brightness)
  );

  #if ENABLED(NEOPIXEL2_SEPARATE)
    switch (unit) {
      case 0: leds.set_color(color); return;
      case 1: leds2.set_color(color); return;
    }
  #endif

  // If 'S' is not specified use both
  leds.set_color(color);
  TERN_(NEOPIXEL2_SEPARATE, leds2.set_color(color));
}

#endif // HAS_COLOR_LEDS
