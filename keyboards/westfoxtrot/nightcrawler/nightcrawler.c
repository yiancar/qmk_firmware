/* Copyright 2021 Yiancar-Designs
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
 #include "nightcrawler.h"

 #define MEDIA_KEY_DELAY 10

void led_init_ports(void) {
    // Set our LED pins as open drain outputs
    palSetLineMode(LED_NUM_LOCK_PIN, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(LED_CAPS_LOCK_PIN, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(LED_SCROLL_LOCK_PIN, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A15, PAL_MODE_OUTPUT_OPENDRAIN);
}

__attribute__((weak)) layer_state_t layer_state_set_kb(layer_state_t state) {
  writePin(A15, !layer_state_cmp(state, 1));
  return layer_state_set_user(state);
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    uint16_t mapped_code = 0;
    if (clockwise) {
        if (IS_LAYER_ON(0)) {
            mapped_code = KC_VOLU;
        } else {
            mapped_code = KC_MEDIA_NEXT_TRACK;
        }
    } else {
        if (IS_LAYER_ON(0)) {
            mapped_code = KC_VOLD;
        } else {
            mapped_code = KC_MEDIA_PREV_TRACK;
        }
    }
    uint16_t held_keycode_timer = timer_read();
    register_code(mapped_code);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
    unregister_code(mapped_code);
    return true;
}
