/* Copyright 2022 Yiancar
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

#include "sgk50_s3.h"

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {  67,     68,  69,     70,     71,     72,  73,     74,     75,  76,  77,  78,  79,  80,     81 }, 
    {  66,     65,  64,     63,     62,     61,  60,     59,     58,  57,  56,  55,  54,  53,     52 }, 
    {  37,     38,  39,     40,     41,     42,  43,     44,     45,  46,  47,  48,  49,  82,     51 }, 
    {  36,     35,  34,     33,     32,     31,  30,     29,     28,  27,  26,  25,  50,  24,     23 }, 
    {  10, NO_LED,  11,     12,     13,     14,  15,     16,     17,  18,  19,  20,  21,  22, NO_LED }, 
    {   9,      8,   7, NO_LED, NO_LED, NO_LED,   6, NO_LED, NO_LED,   5,   4,   3,   2,   1,      0 }
}, {
    {224,64 }, {209,64 }, {194,64 }, {179,64 }, {164,64 }, {149,64 }, { 95,64 }, { 39,64 }, { 21,64 }, {  2,64 }, 
    {  9,51 }, { 34,51 }, { 49,51 }, { 63,51 }, { 78,51 }, { 93,51 }, {108,51 }, {123,51 }, {138,51 }, {153,51 }, {168,51 }, {189,51 }, {209,51 },
    {224,38 }, {200,38 }, {175,38 }, {161,38 }, {146,38 }, {131,38 }, {116,38 }, {101,38 }, { 86,38 }, { 71,38 }, { 56,38 }, { 41,38 }, { 26,38 }, {  6,38 },
    {  4,26 }, { 22,26 }, { 37,26 }, { 52,26 }, { 67,26 }, { 82,26 }, { 97,26 }, {112,26 }, {127,26 }, {142,26 }, {157,26 }, {172,26 }, {187,26 }, {205,26 }, {224,26 },
    {224,13 }, {202,13 }, {179,13 }, {164,13 }, {149,13 }, {134,13 }, {119,13 }, {105,13 }, { 90,13 }, { 75,13 }, { 60,13 }, { 45,13 }, { 30,13 }, { 15,13 }, {  0,13 },
    {  0,0  }, { 15,0  }, { 30,0  }, { 45,0  }, { 60,0  }, { 75,0  }, { 90,0  }, {105,0  }, {119,0  }, {134,0  }, {149,0  }, {164,0  }, {179,0  }, {194,0  }, {209,0  }, {224,0  }
}, {
    4, 4, 4, 1, 1, 1, 4, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
// clang-format on
#endif
