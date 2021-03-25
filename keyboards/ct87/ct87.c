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
#ifndef RGB_BACKLIGHT_CT87
#error RGB_BACKLIGHT_CT87 not defined, recheck config.h
#endif

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed){
    eeprom_total_count.i++;
  }
  return true;
}
