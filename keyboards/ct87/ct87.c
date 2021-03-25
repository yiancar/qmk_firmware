/* Copyright 2021 Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// #ifndef RGB_BACKLIGHT_CT87
// #error RGB_BACKLIGHT_CT87 not defined, recheck config.h
// #endif

#include <stdio.h>
#include <string.h>
#include "ct87.h"
// #include "drivers/issi/is31fl3733.h"
#include "i2c_master.h"

char keypress_buf[34];
uint8_t eeprom_write_buffer[6] = { [0] = 0x00, [1] = 0x00 };

static union {
  uint32_t i;
  uint8_t b[4];
} eeprom_total_count;

void keyboard_post_init_kb(void) {
  i2cMasterTransmit(&I2CD1, (0xAC >> 1), eeprom_write_buffer, 2, eeprom_total_count.b, 4);
  // eeprom_total_count.i = 0x0;
  oled_write("Clack Track 87\n--------------", false);
}

#ifdef OLED_DRIVER_ENABLE
__attribute__ ((weak)) void oled_task_user(void) {
  sprintf(keypress_buf, "Clacks: %lu\nWPM: %u", eeprom_total_count.i, get_current_wpm());

  memcpy(eeprom_write_buffer + 2, eeprom_total_count.b , 4);
  i2cMasterTransmit(&I2CD1, (0xAC >> 1), eeprom_write_buffer, 6, 0, 0);
  // oled_write("Total Clacks: ", false);
  oled_set_cursor(0, 2);
  oled_write(keypress_buf, false);
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed){
    eeprom_total_count.i++;
  }
  return process_record_user(keycode, record);
}

/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 63 Blue channel
 * Middle LED is blue and red. LED driver 2 RGB 63 Red and Green channel
 * Bottom LED is red only LED driver 2 RGB 48 Blue channel.
 */
// uint8_t CAPS = 0;
// uint8_t FN1 = 0;
// uint8_t FN2 = 0;

// bool led_update_kb(led_t led_state) {
//     bool res = led_update_user(led_state);
//     if(res) {
//         if (led_state.caps_lock) {
//             CAPS = 255;
//         } else {
//             CAPS = 0;
//         }
//     }
//     IS31FL3733_set_color( 63+64-1, FN1, FN1, CAPS );
//     IS31FL3733_set_color( 48+64-1, 0, 0, FN2 );
//     return res;
// }

// __attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
//     if (state & (1UL << 1)) {
//         FN1 = 255;
//     } else {
//         FN1 = 0;
//     }
//     if (state & (1UL << 2)) {
//         FN2 = 255;
//     } else {
//         FN2 = 0;
//     }
//   return state;
// }
