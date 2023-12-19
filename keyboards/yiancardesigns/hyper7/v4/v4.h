/* Copyright 2023 Yiancar-Designs, Bit-Shifter
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
#pragma once

#include "quantum.h"

#define XXX KC_NO

// modifier masks used for determining modifier actuation within macros
#define MODS_SHIFT_MASK   (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))

// Clear mods, perform action, restore mods
#define CLEAN_MODS(action) {       \
        uint8_t mods = get_mods(); \
        clear_mods();              \
        action;                    \
        set_mods(mods);            \
    }

enum custom_keycodes {
    // daughter board R1
    H_HELP = QK_USER,
    H_MACRO,
    H_TERMINAL,
    H_QUOTE,
    H_OVERSTRIKE,
    H_CLEAR_INPUT,
    H_CLEAR_SCREEN,
    H_HOLD_OUTPUT,
    H_STOP_OUTPUT,
    H_ABORT,
    H_BREAK,
    H_RESUME,
    H_CALL,

    // daughter board R2
    H_LOCAL,
    H_NETWORK,
    H_SYSTEM,
    H_REFRESH,
    H_BUFFER,
    H_SQUARE,
    H_CIRCLE,
    H_TRIANGLE,
    H_DIAMOND,
    H_REPEAT,
    H_TRANSMIT,
    H_STATUS,
    H_SUSPEND,

    // daughter board r3
    H_CLOSE,
    H_OPEN,
    H_COMPLETE,

    // main board r1
    H_WRITE,
    H_DOUBLE_QUOTE__PLUS_MINUS,
    H_COLON__TILDE,
    H_L_BRACE__L_CHEVRON,
    H_R_BRACE__R_CHEVRON,

    // main board r2
    H_MARK,
    H_LEFT_PAREN__LEFT_BRACKET,
    H_RIGHT_PAREN__RIGHT_BRACKET,

    // main board r3
    H_SELECT,
    H_DEBUG,
    H_SEMI_COLON__BACK_TICK,
    H_TICK__QUOTE,
    H_LINE,
    H_PAGE,

    // main board r4
    H_TTY,
    H_LOCK, // lock machine? a little close to other used keys on a single keypress?

    // main board r5
    H_EOF,
    H_7BIT,
    H_CIRCLE_SM
};
