/* Copyright 2018 Yiancar
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
#include "v2.h"
#include "../../zeal60/zeal60_api.h"
#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "timer.h"
#include "tmk_core/common/eeprom.h"
#include "rgb_matrix.h"

bool eeprom_is_valid(void)
{
    return (eeprom_read_word((uint16_t *)11) == EEPROM_MAGIC &&
            eeprom_read_byte((uint8_t *)12) == EEPROM_VERSION);
}

void eeprom_set_valid(bool valid)
{
    eeprom_update_word((uint16_t *)11, valid ? EEPROM_MAGIC : 0xFFFF);
    eeprom_update_byte((uint8_t *)12, valid ? EEPROM_VERSION : 0xFF);
}

void eeprom_reset(void)
{
    // Set the Raw HID protocol specific EEPROM state as invalid.
    eeprom_set_valid(false);
    // Set the TMK/QMK EEPROM state as invalid.
    eeconfig_disable();
}

//RGB Matrix Configuration

#ifdef HS60_ANSI

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_1,    A_1,    C_1}, //MX1
    {0, E_1,    D_1,    F_1}, //MX2
    {0, H_1,    G_1,    I_1}, //MX3
    {0, K_1,    J_1,    L_1}, //MX4
    {0, B_2,    A_2,    C_2}, //MX6
    {0, E_2,    D_2,    F_2}, //MX7
    {0, H_2,    G_2,    I_2}, //MX8
    {0, K_2,    J_2,    L_2}, //MX14
    {0, B_3,    A_3,    C_3}, //MX11
    {0, E_3,    D_3,    F_3}, //MX12
    {0, H_3,    G_3,    I_3}, //MX13
    {0, K_3,    J_3,    L_3}, //MX19
    {0, B_4,    A_4,    C_4}, //MX16
    {0, E_4,    D_4,    F_4}, //MX17
    {0, H_4,    G_4,    I_4}, //MX18
    {0, K_4,    J_4,    L_4}, //MX23
    {0, B_5,    A_5,    C_5}, //MX20
    {0, E_5,    D_5,    F_5}, //MX21
    {0, H_5,    G_5,    I_5}, //MX22
    {0, K_5,    J_5,    L_5}, //MX27
    {0, B_6,    A_6,    C_6}, //MX24
    {0, E_6,    D_6,    F_6}, //MX25
    {0, H_6,    G_6,    I_6}, //MX26
    {0, K_6,    J_6,    L_6}, //MX31
    {0, B_7,    A_7,    C_7}, //MX28
    {0, E_7,    D_7,    F_7}, //MX29
    {0, H_7,    G_7,    I_7}, //MX30
    {0, K_7,    J_7,    L_7}, //MX36
    {0, B_8,    A_8,    C_8}, //MX33
    {0, E_8,    D_8,    F_8}, //MX34
    {0, H_8,    G_8,    I_8}, //MX35
    {0, K_8,    J_8,    L_8}, //MX40
    {0, B_9,    A_9,    C_9}, //MX37
    {0, E_9,    D_9,    F_9}, //MX38
    {0, H_9,    G_9,    I_9}, //MX39
    {0, K_9,    J_9,    L_9}, //MX44
    {0, B_10,   A_10,   C_10}, //MX41
    {0, E_10,   D_10,   F_10}, //MX42
    {0, H_10,   G_10,   I_10}, //MX43
    {0, K_10,   J_10,   L_10}, //MX48
    {0, B_11,   A_11,   C_11}, //MX45
    {0, E_11,   D_11,   F_11}, //MX46
    {0, H_11,   G_11,   I_11}, //MX47
    {0, K_11,   J_11,   L_11}, //MX53
    {0, B_12,   A_12,   C_12}, //MX50
    {0, E_12,   D_12,   F_12}, //MX51
    {0, H_12,   G_12,   I_12}, //MX52

    {0, B_13,   A_13,   C_13}, //MX55
    {0, E_13,   D_13,   F_13}, //MX56

    {0, K_13,   J_13,   L_13}, //MX61
    {0, B_14,   A_14,   C_14}, //MX59
    {0, E_14,   D_14,   F_14}, //MX57
    {0, H_14,   G_14,   I_14}, //MX60
    {0, K_14,   J_14,   L_14}, //MX62
    {0, B_15,   A_15,   C_15}, //MX5
    {0, E_15,   D_15,   F_15}, //MX10
    {0, H_15,   G_15,   I_15}, //MX15
    {0, K_15,   J_15,   L_15}, //MX32

    {0, E_16,   D_16,   F_16}, //MX49
    {0, H_16,   G_16,   I_16}, //MX54
    {0, K_16,   J_16,   L_16}, //MX58
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
//
//  MX1,  MX6, MX11, MX16, MX20, MX24, MX28, MX33, MX37, MX41, MX45, MX50, MX55, MX59,
//  MX2,  MX7, MX12, MX17, MX21, MX25, MX29, MX34, MX38, MX42, MX46, MX51, MX56,  ---,
//  MX3,  MX8, MX13, MX18, MX22, MX26, MX30, MX35, MX39, MX43, MX47, MX52, MX57, MX60,
//  MX4,  ---, MX14, MX19, MX23, MX27, MX31, MX36, MX40, MX44, MX48, MX53,  ---, MX61,
//  MX5, MX10, MX15,  ---,  ---,  ---, MX32,  ---,  ---,  ---, MX49, MX54, MX58, MX62
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{0|(0<<4)},    {  0,  0}, 1}, //MX1
    {{1|(0<<4)},    {  0, 16}, 1}, //MX2
    {{2|(0<<4)},    {  0, 32}, 1}, //MX3
    {{3|(0<<4)},    {  0, 48}, 1}, //MX4
    {{0|(1<<4)},    { 17,  0}, 0}, //MX6
    {{1|(1<<4)},    { 17, 16}, 0}, //MX7
    {{2|(1<<4)},    { 17, 32}, 0}, //MX8
    {{3|(2<<4)},    { 34, 48}, 0}, //MX14
    {{0|(2<<4)},    { 34,  0}, 0}, //MX11
    {{1|(2<<4)},    { 34, 16}, 0}, //MX12
    {{2|(2<<4)},    { 34, 32}, 0}, //MX13
    {{3|(3<<4)},    { 51, 48}, 0}, //MX19
    {{0|(3<<4)},    { 51,  0}, 0}, //MX16
    {{1|(3<<4)},    { 51, 16}, 0}, //MX17
    {{2|(3<<4)},    { 51, 32}, 0}, //MX18
    {{3|(4<<4)},    { 68, 48}, 0}, //MX23
    {{0|(4<<4)},    { 68,  0}, 0}, //MX20
    {{1|(4<<4)},    { 68, 16}, 0}, //MX21
    {{2|(4<<4)},    { 68, 32}, 0}, //MX22
    {{3|(5<<4)},    { 85, 48}, 0}, //MX27
    {{0|(5<<4)},    { 85,  0}, 0}, //MX24
    {{1|(5<<4)},    { 85, 16}, 0}, //MX25
    {{2|(5<<4)},    { 85, 32}, 0}, //MX26
    {{3|(6<<4)},    {102, 48}, 0}, //MX31
    {{0|(6<<4)},    {102,  0}, 0}, //MX28
    {{1|(6<<4)},    {102, 16}, 0}, //MX29
    {{2|(6<<4)},    {102, 32}, 0}, //MX30
    {{3|(7<<4)},    {119, 48}, 0}, //MX36
    {{0|(7<<4)},    {119,  0}, 0}, //MX33
    {{1|(7<<4)},    {119, 16}, 0}, //MX34
    {{2|(7<<4)},    {119, 32}, 0}, //MX35
    {{3|(8<<4)},    {136, 48}, 0}, //MX40
    {{0|(8<<4)},    {136,  0}, 0}, //MX37
    {{1|(8<<4)},    {136, 16}, 0}, //MX38
    {{2|(8<<4)},    {136, 32}, 0}, //MX39
    {{3|(9<<4)},    {153, 48}, 0}, //MX44
    {{0|(9<<4)},    {153,  0}, 0}, //MX41
    {{1|(9<<4)},    {153, 16}, 0}, //MX42
    {{2|(9<<4)},    {153, 32}, 0}, //MX43
    {{3|(10<<4)},   {170, 48}, 0}, //MX48
    {{0|(10<<4)},   {170,  0}, 0}, //MX45
    {{1|(10<<4)},   {170, 16}, 0}, //MX46
    {{2|(10<<4)},   {170, 32}, 0}, //MX47
    {{3|(11<<4)},   {187, 48}, 0}, //MX53
    {{0|(11<<4)},   {187,  0}, 0}, //MX50
    {{1|(11<<4)},   {187, 16}, 0}, //MX51
    {{2|(11<<4)},   {187, 32}, 0}, //MX52

    {{0|(12<<4)},   {204,  0}, 0}, //MX55
    {{1|(12<<4)},   {204, 16}, 0}, //MX56

    {{3|(13<<4)},   {221, 48}, 1}, //MX61
    {{0|(13<<4)},   {221,  0}, 1}, //MX59
    {{2|(12<<4)},   {221, 16}, 0}, //MX57
    {{2|(13<<4)},   {221, 32}, 1}, //MX60
    {{4|(13<<4)},   {221, 64}, 1}, //MX62
    {{4|(0<<4)},    {  0, 64}, 1}, //MX5
    {{4|(1<<4)},    { 17, 64}, 1}, //MX10
    {{4|(2<<4)},    { 34, 64}, 1}, //MX15
    {{4|(5<<4)},    {102, 64}, 0}, //MX32

    {{4|(10<<4)},   {170, 64}, 1}, //MX49
    {{4|(11<<4)},   {187, 64}, 1}, //MX54
    {{4|(12<<4)},   {204, 64}, 1}  //MX58
};

#elif defined(HS60_HHKB)

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_1,    A_1,    C_1}, //MX1
    {0, E_1,    D_1,    F_1}, //MX2
    {0, H_1,    G_1,    I_1}, //MX3
    {0, K_1,    J_1,    L_1}, //MX4
    {0, B_2,    A_2,    C_2}, //MX6
    {0, E_2,    D_2,    F_2}, //MX7
    {0, H_2,    G_2,    I_2}, //MX8
    {0, K_2,    J_2,    L_2}, //MX14
    {0, B_3,    A_3,    C_3}, //MX11
    {0, E_3,    D_3,    F_3}, //MX12
    {0, H_3,    G_3,    I_3}, //MX13
    {0, K_3,    J_3,    L_3}, //MX19
    {0, B_4,    A_4,    C_4}, //MX16
    {0, E_4,    D_4,    F_4}, //MX17
    {0, H_4,    G_4,    I_4}, //MX18
    {0, K_4,    J_4,    L_4}, //MX23
    {0, B_5,    A_5,    C_5}, //MX20
    {0, E_5,    D_5,    F_5}, //MX21
    {0, H_5,    G_5,    I_5}, //MX22
    {0, K_5,    J_5,    L_5}, //MX27
    {0, B_6,    A_6,    C_6}, //MX24
    {0, E_6,    D_6,    F_6}, //MX25
    {0, H_6,    G_6,    I_6}, //MX26
    {0, K_6,    J_6,    L_6}, //MX31
    {0, B_7,    A_7,    C_7}, //MX28
    {0, E_7,    D_7,    F_7}, //MX29
    {0, H_7,    G_7,    I_7}, //MX30
    {0, K_7,    J_7,    L_7}, //MX36
    {0, B_8,    A_8,    C_8}, //MX33
    {0, E_8,    D_8,    F_8}, //MX34
    {0, H_8,    G_8,    I_8}, //MX35
    {0, K_8,    J_8,    L_8}, //MX40
    {0, B_9,    A_9,    C_9}, //MX37
    {0, E_9,    D_9,    F_9}, //MX38
    {0, H_9,    G_9,    I_9}, //MX39
    {0, K_9,    J_9,    L_9}, //MX44
    {0, B_10,   A_10,   C_10}, //MX41
    {0, E_10,   D_10,   F_10}, //MX42
    {0, H_10,   G_10,   I_10}, //MX43
    {0, K_10,   J_10,   L_10}, //MX48
    {0, B_11,   A_11,   C_11}, //MX45
    {0, E_11,   D_11,   F_11}, //MX46
    {0, H_11,   G_11,   I_11}, //MX47
    {0, K_11,   J_11,   L_11}, //MX53
    {0, B_12,   A_12,   C_12}, //MX50
    {0, E_12,   D_12,   F_12}, //MX51
    {0, H_12,   G_12,   I_12}, //MX52
    {0, K_12,   J_12,   L_12}, //MX64
    {0, B_13,   A_13,   C_13}, //MX55
    {0, E_13,   D_13,   F_13}, //MX56
    {0, H_13,   G_13,   I_13}, //MX63
    {0, K_13,   J_13,   L_13}, //MX61
    {0, B_14,   A_14,   C_14}, //MX59
    {0, E_14,   D_14,   F_14}, //MX57
    {0, H_14,   G_14,   I_14}, //MX60
    {0, K_14,   J_14,   L_14}, //MX62
    {0, B_15,   A_15,   C_15}, //MX5
    {0, E_15,   D_15,   F_15}, //MX10
    {0, H_15,   G_15,   I_15}, //MX15
    {0, K_15,   J_15,   L_15}, //MX32


    {0, H_16,   G_16,   I_16}, //MX54
    {0, K_16,   J_16,   L_16}, //MX58
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
//
//  MX1,  MX6, MX11, MX16, MX20, MX24, MX28, MX33, MX37, MX41, MX45, MX50, MX55, MX59,
//  MX2,  MX7, MX12, MX17, MX21, MX25, MX29, MX34, MX38, MX42, MX46, MX51, MX56, MX64,
//  MX3,  MX8, MX13, MX18, MX22, MX26, MX30, MX35, MX39, MX43, MX47, MX52, MX57, MX60,
//  MX4, ----, MX14, MX19, MX23, MX27, MX31, MX36, MX40, MX44, MX48, MX53, MX63, MX61,
//  MX5, MX10, MX15, ----, ----, ----, MX32, ----,  ---, ----, ----, MX54, MX58, MX62
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{0|(0<<4)},    {  0,  0}, 1}, //MX1
    {{1|(0<<4)},    {  0, 16}, 1}, //MX2
    {{2|(0<<4)},    {  0, 32}, 1}, //MX3
    {{3|(0<<4)},    {  0, 48}, 1}, //MX4
    {{0|(1<<4)},    { 17,  0}, 0}, //MX6
    {{1|(1<<4)},    { 17, 16}, 0}, //MX7
    {{2|(1<<4)},    { 17, 32}, 0}, //MX8
    {{3|(2<<4)},    { 34, 48}, 0}, //MX14
    {{0|(2<<4)},    { 34,  0}, 0}, //MX11
    {{1|(2<<4)},    { 34, 16}, 0}, //MX12
    {{2|(2<<4)},    { 34, 32}, 0}, //MX13
    {{3|(3<<4)},    { 51, 48}, 0}, //MX19
    {{0|(3<<4)},    { 51,  0}, 0}, //MX16
    {{1|(3<<4)},    { 51, 16}, 0}, //MX17
    {{2|(3<<4)},    { 51, 32}, 0}, //MX18
    {{3|(4<<4)},    { 68, 48}, 0}, //MX23
    {{0|(4<<4)},    { 68,  0}, 0}, //MX20
    {{1|(4<<4)},    { 68, 16}, 0}, //MX21
    {{2|(4<<4)},    { 68, 32}, 0}, //MX22
    {{3|(5<<4)},    { 85, 48}, 0}, //MX27
    {{0|(5<<4)},    { 85,  0}, 0}, //MX24
    {{1|(5<<4)},    { 85, 16}, 0}, //MX25
    {{2|(5<<4)},    { 85, 32}, 0}, //MX26
    {{3|(6<<4)},    {102, 48}, 0}, //MX31
    {{0|(6<<4)},    {102,  0}, 0}, //MX28
    {{1|(6<<4)},    {102, 16}, 0}, //MX29
    {{2|(6<<4)},    {102, 32}, 0}, //MX30
    {{3|(7<<4)},    {119, 48}, 0}, //MX36
    {{0|(7<<4)},    {119,  0}, 0}, //MX33
    {{1|(7<<4)},    {119, 16}, 0}, //MX34
    {{2|(7<<4)},    {119, 32}, 0}, //MX35
    {{3|(8<<4)},    {136, 48}, 0}, //MX40
    {{0|(8<<4)},    {136,  0}, 0}, //MX37
    {{1|(8<<4)},    {136, 16}, 0}, //MX38
    {{2|(8<<4)},    {136, 32}, 0}, //MX39
    {{3|(9<<4)},    {153, 48}, 0}, //MX44
    {{0|(9<<4)},    {153,  0}, 0}, //MX41
    {{1|(9<<4)},    {153, 16}, 0}, //MX42
    {{2|(9<<4)},    {153, 32}, 0}, //MX43
    {{3|(10<<4)},   {170, 48}, 0}, //MX48
    {{0|(10<<4)},   {170,  0}, 0}, //MX45
    {{1|(10<<4)},   {170, 16}, 0}, //MX46
    {{2|(10<<4)},   {170, 32}, 0}, //MX47
    {{3|(11<<4)},   {187, 48}, 0}, //MX53
    {{0|(11<<4)},   {187,  0}, 0}, //MX50
    {{1|(11<<4)},   {187, 16}, 0}, //MX51
    {{2|(11<<4)},   {187, 32}, 0}, //MX52
    {{1|(13<<4)},   {221,  0}, 1}, //MX64
    {{0|(12<<4)},   {204,  0}, 0}, //MX55
    {{1|(12<<4)},   {204, 16}, 0}, //MX56
    {{3|(12<<4)},   {204, 48}, 0}, //MX63
    {{3|(13<<4)},   {212, 48}, 1}, //MX61
    {{0|(13<<4)},   {221,  0}, 0}, //MX59
    {{2|(12<<4)},   {221, 16}, 0}, //MX57
    {{2|(13<<4)},   {221, 32}, 1}, //MX60
    {{4|(13<<4)},   {221, 64}, 1}, //MX62
    {{4|(0<<4)},    {  0, 64}, 1}, //MX5
    {{4|(1<<4)},    { 17, 64}, 1}, //MX10
    {{4|(2<<4)},    { 34, 64}, 1}, //MX15
    {{4|(5<<4)},    {102, 64}, 0}, //MX32


    {{4|(11<<4)},   {187, 64}, 1}, //MX54
    {{4|(12<<4)},   {204, 64}, 1}  //MX58
};

#else //ISO layout

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_1,    A_1,    C_1}, //MX1
    {0, E_1,    D_1,    F_1}, //MX2
    {0, H_1,    G_1,    I_1}, //MX3
    {0, K_1,    J_1,    L_1}, //MX4
    {0, B_2,    A_2,    C_2}, //MX6
    {0, E_2,    D_2,    F_2}, //MX7
    {0, H_2,    G_2,    I_2}, //MX8
    {0, K_2,    J_2,    L_2}, //MX14
    {0, B_3,    A_3,    C_3}, //MX11
    {0, E_3,    D_3,    F_3}, //MX12
    {0, H_3,    G_3,    I_3}, //MX13
    {0, K_3,    J_3,    L_3}, //MX19
    {0, B_4,    A_4,    C_4}, //MX16
    {0, E_4,    D_4,    F_4}, //MX17
    {0, H_4,    G_4,    I_4}, //MX18
    {0, K_4,    J_4,    L_4}, //MX23
    {0, B_5,    A_5,    C_5}, //MX20
    {0, E_5,    D_5,    F_5}, //MX21
    {0, H_5,    G_5,    I_5}, //MX22
    {0, K_5,    J_5,    L_5}, //MX27
    {0, B_6,    A_6,    C_6}, //MX24
    {0, E_6,    D_6,    F_6}, //MX25
    {0, H_6,    G_6,    I_6}, //MX26
    {0, K_6,    J_6,    L_6}, //MX31
    {0, B_7,    A_7,    C_7}, //MX28
    {0, E_7,    D_7,    F_7}, //MX29
    {0, H_7,    G_7,    I_7}, //MX30
    {0, K_7,    J_7,    L_7}, //MX36
    {0, B_8,    A_8,    C_8}, //MX33
    {0, E_8,    D_8,    F_8}, //MX34
    {0, H_8,    G_8,    I_8}, //MX35
    {0, K_8,    J_8,    L_8}, //MX40
    {0, B_9,    A_9,    C_9}, //MX37
    {0, E_9,    D_9,    F_9}, //MX38
    {0, H_9,    G_9,    I_9}, //MX39
    {0, K_9,    J_9,    L_9}, //MX44
    {0, B_10,   A_10,   C_10}, //MX41
    {0, E_10,   D_10,   F_10}, //MX42
    {0, H_10,   G_10,   I_10}, //MX43
    {0, K_10,   J_10,   L_10}, //MX48
    {0, B_11,   A_11,   C_11}, //MX45
    {0, E_11,   D_11,   F_11}, //MX46
    {0, H_11,   G_11,   I_11}, //MX47
    {0, K_11,   J_11,   L_11}, //MX53
    {0, B_12,   A_12,   C_12}, //MX50
    {0, E_12,   D_12,   F_12}, //MX51
    {0, H_12,   G_12,   I_12}, //MX52
    {0, K_12,   J_12,   L_12}, //MX9
    {0, B_13,   A_13,   C_13}, //MX55
    {0, E_13,   D_13,   F_13}, //MX56

    {0, K_13,   J_13,   L_13}, //MX61
    {0, B_14,   A_14,   C_14}, //MX59
    {0, E_14,   D_14,   F_14}, //MX57
    {0, H_14,   G_14,   I_14}, //MX60
    {0, K_14,   J_14,   L_14}, //MX62
    {0, B_15,   A_15,   C_15}, //MX5
    {0, E_15,   D_15,   F_15}, //MX10
    {0, H_15,   G_15,   I_15}, //MX15
    {0, K_15,   J_15,   L_15}, //MX32

    {0, E_16,   D_16,   F_16}, //MX49
    {0, H_16,   G_16,   I_16}, //MX54
    {0, K_16,   J_16,   L_16}, //MX58
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
//
//  MX1,  MX6, MX11, MX16, MX20, MX24, MX28, MX33, MX37, MX41, MX45, MX50, MX55, MX59,
//  MX2,  MX7, MX12, MX17, MX21, MX25, MX29, MX34, MX38, MX42, MX46, MX51, MX56,  ---,
//  MX3,  MX8, MX13, MX18, MX22, MX26, MX30, MX35, MX39, MX43, MX47, MX52, MX57, MX60,
//  MX4,  ---, MX14, MX19, MX23, MX27, MX31, MX36, MX40, MX44, MX48, MX53,  ---, MX61,
//  MX5, MX10, MX15,  ---,  ---,  ---, MX32,  ---,  ---,  ---, MX49, MX54, MX58, MX62
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{0|(0<<4)},    {  0,  0}, 1}, //MX1
    {{1|(0<<4)},    {  0, 16}, 1}, //MX2
    {{2|(0<<4)},    {  0, 32}, 1}, //MX3
    {{3|(0<<4)},    {  0, 48}, 1}, //MX4
    {{0|(1<<4)},    { 17,  0}, 0}, //MX6
    {{1|(1<<4)},    { 17, 16}, 0}, //MX7
    {{2|(1<<4)},    { 17, 32}, 0}, //MX8
    {{3|(2<<4)},    { 34, 48}, 0}, //MX14
    {{0|(2<<4)},    { 34,  0}, 0}, //MX11
    {{1|(2<<4)},    { 34, 16}, 0}, //MX12
    {{2|(2<<4)},    { 34, 32}, 0}, //MX13
    {{3|(3<<4)},    { 51, 48}, 0}, //MX19
    {{0|(3<<4)},    { 51,  0}, 0}, //MX16
    {{1|(3<<4)},    { 51, 16}, 0}, //MX17
    {{2|(3<<4)},    { 51, 32}, 0}, //MX18
    {{3|(4<<4)},    { 68, 48}, 0}, //MX23
    {{0|(4<<4)},    { 68,  0}, 0}, //MX20
    {{1|(4<<4)},    { 68, 16}, 0}, //MX21
    {{2|(4<<4)},    { 68, 32}, 0}, //MX22
    {{3|(5<<4)},    { 85, 48}, 0}, //MX27
    {{0|(5<<4)},    { 85,  0}, 0}, //MX24
    {{1|(5<<4)},    { 85, 16}, 0}, //MX25
    {{2|(5<<4)},    { 85, 32}, 0}, //MX26
    {{3|(6<<4)},    {102, 48}, 0}, //MX31
    {{0|(6<<4)},    {102,  0}, 0}, //MX28
    {{1|(6<<4)},    {102, 16}, 0}, //MX29
    {{2|(6<<4)},    {102, 32}, 0}, //MX30
    {{3|(7<<4)},    {119, 48}, 0}, //MX36
    {{0|(7<<4)},    {119,  0}, 0}, //MX33
    {{1|(7<<4)},    {119, 16}, 0}, //MX34
    {{2|(7<<4)},    {119, 32}, 0}, //MX35
    {{3|(8<<4)},    {136, 48}, 0}, //MX40
    {{0|(8<<4)},    {136,  0}, 0}, //MX37
    {{1|(8<<4)},    {136, 16}, 0}, //MX38
    {{2|(8<<4)},    {136, 32}, 0}, //MX39
    {{3|(9<<4)},    {153, 48}, 0}, //MX44
    {{0|(9<<4)},    {153,  0}, 0}, //MX41
    {{1|(9<<4)},    {153, 16}, 0}, //MX42
    {{2|(9<<4)},    {153, 32}, 0}, //MX43
    {{3|(10<<4)},   {170, 48}, 0}, //MX48
    {{0|(10<<4)},   {170,  0}, 0}, //MX45
    {{1|(10<<4)},   {170, 16}, 0}, //MX46
    {{2|(10<<4)},   {170, 32}, 0}, //MX47
    {{3|(11<<4)},   {187, 48}, 0}, //MX53
    {{0|(11<<4)},   {187,  0}, 0}, //MX50
    {{1|(11<<4)},   {187, 16}, 0}, //MX51
    {{2|(11<<4)},   {187, 32}, 0}, //MX52
    {{3|(2<<4)},    { 17, 32}, 1}, //MX9
    {{0|(12<<4)},   {204,  0}, 0}, //MX55
    {{1|(12<<4)},   {204, 16}, 0}, //MX56

    {{3|(13<<4)},   {221, 48}, 1}, //MX61
    {{0|(13<<4)},   {221,  0}, 1}, //MX59
    {{2|(12<<4)},   {204, 32}, 0}, //MX57
    {{2|(13<<4)},   {221, 24}, 1}, //MX60
    {{4|(13<<4)},   {221, 64}, 1}, //MX62
    {{4|(0<<4)},    {  0, 64}, 1}, //MX5
    {{4|(1<<4)},    { 17, 64}, 1}, //MX10
    {{4|(2<<4)},    { 34, 64}, 1}, //MX15
    {{4|(5<<4)},    {102, 64}, 0}, //MX32

    {{4|(10<<4)},   {170, 64}, 1}, //MX49
    {{4|(11<<4)},   {187, 64}, 1}, //MX54
    {{4|(12<<4)},   {204, 64}, 1}  //MX58
};

#endif

#ifdef RAW_ENABLE

void rgbmatrix_set_config_rawhid(uint8_t *data) {
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case 0x09:
        {
            rgb_matrix_config.val = *value_data;
            eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
            break;
        }
        case 0x0A:
        {
            rgb_matrix_config.mode = *value_data;
            eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
            break;
        }
        case 0x0B:
        {
            rgb_matrix_config.speed = *value_data;
            eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
            break;
        }
        case 0x0C:
        {
            rgb_matrix_config.hue = value_data[0];
            rgb_matrix_config.sat = value_data[1];
            eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
            break;
        }
    }
}

void rgbmatrix_get_config_rawhid(uint8_t *data) {
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case 0x09:
        {
            *value_data = rgb_matrix_config.val;
            break;
        }
        case 0x0A:
        {
            *value_data= rgb_matrix_config.mode;
            break;
        }
        case 0x0B:
        {
            *value_data = rgb_matrix_config.speed;
            break;
        }
        case 0x0C:
        {
            value_data[0] = rgb_matrix_config.hue;
            value_data[1] = rgb_matrix_config.sat;
            break;
        }
    }
}

void raw_hid_receive( uint8_t *data, uint8_t length )
{
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch ( *command_id )
    {
        case id_get_protocol_version:
        {
            command_data[0] = PROTOCOL_VERSION >> 8;
            command_data[1] = PROTOCOL_VERSION & 0xFF;
            break;
        }
        case id_get_keyboard_value:
        {
            if ( command_data[0] == id_uptime )
            {
                uint32_t value = timer_read32();
                command_data[1] = (value >> 24 ) & 0xFF;
                command_data[2] = (value >> 16 ) & 0xFF;
                command_data[3] = (value >> 8 ) & 0xFF;
                command_data[4] = value & 0xFF;
            }
            else
            {
                *command_id = id_unhandled;
            }
            break;
        }
#ifdef DYNAMIC_KEYMAP_ENABLE
        case id_dynamic_keymap_get_keycode:
        {
            uint16_t keycode = dynamic_keymap_get_keycode( command_data[0], command_data[1], command_data[2] );
            command_data[3] = keycode >> 8;
            command_data[4] = keycode & 0xFF;
            break;
        }
        case id_dynamic_keymap_set_keycode:
        {
            dynamic_keymap_set_keycode( command_data[0], command_data[1], command_data[2], ( command_data[3] << 8 ) | command_data[4] );
            break;
        }
        case id_dynamic_keymap_reset:
        {
            dynamic_keymap_reset();
            break;
        }
        case id_dynamic_keymap_macro_get_count:
        {
            command_data[0] = dynamic_keymap_macro_get_count();
            break;
        }
        case id_dynamic_keymap_macro_get_buffer_size:
        {
            uint16_t size = dynamic_keymap_macro_get_buffer_size();
            command_data[0] = size >> 8;
            command_data[1] = size & 0xFF;
            break;
        }
        case id_dynamic_keymap_macro_get_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_macro_get_buffer( offset, size, &command_data[3] );
            break;
        }
        case id_dynamic_keymap_macro_set_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_macro_set_buffer( offset, size, &command_data[3] );
            break;
        }
        case id_dynamic_keymap_macro_reset:
        {
            dynamic_keymap_macro_reset();
            break;
        }
        case id_dynamic_keymap_get_layer_count:
        {
            command_data[0] = dynamic_keymap_get_layer_count();
            break;
        }
        case id_dynamic_keymap_get_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_get_buffer( offset, size, &command_data[3] );
            break;
        }
        case id_dynamic_keymap_set_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_set_buffer( offset, size, &command_data[3] );
            break;
        }
#endif // DYNAMIC_KEYMAP_ENABLE
        case id_backlight_config_set_value:
        {
            rgbmatrix_set_config_rawhid(command_data);
            break;
        }
        case id_backlight_config_get_value:
        {
            rgbmatrix_get_config_rawhid(command_data);
            break;
        }
        case id_backlight_config_save:
        {
            //backlight_config_save();
            break;
        }
        case id_eeprom_reset:
        {
            eeprom_reset();
            break;
        }
        case id_bootloader_jump:
        {
            // Need to send data back before the jump
            // Informs host that the command is handled
            raw_hid_send( data, length );
            // Give host time to read it
            wait_ms(100);
            bootloader_jump();
            break;
        }
        case id_backlight_protocol_version:
        {
            command_data[0] = BACKLIGHT_PROTOCOL_VERSION >> 8;
            command_data[1] = BACKLIGHT_PROTOCOL_VERSION & 0xFF;
            break;
        }
        default:
        {
            // Unhandled message.
            *command_id = id_unhandled;
            break;
        }
    }

    // Return same buffer with values changed
    raw_hid_send( data, length );

}

#endif

void bootmagic_lite(void)
{
    // The lite version of TMK's bootmagic made by Wilba.
    // 100% less potential for accidentally making the
    // keyboard do stupid things.

    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
    wait_ms(10);
    matrix_scan();

    // If the Esc and space bar are held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // Assumes Esc is at [0,0] and spacebar is at [4,6].
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    if ( ( matrix_get_row(0) & (1<<0) ) &&
        ( matrix_get_row(4) & (1<<6) ) )
    {
        // Set the TMK/QMK EEPROM state as invalid.
        eeconfig_disable();
        //eeprom_set_valid(false);
        // Jump to bootloader.
        bootloader_jump();
    }
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    if (eeprom_is_valid()) {
#if RGB_BACKLIGHT_ENABLED
        //backlight_config_load();
#endif // RGB_BACKLIGHT_ENABLED
    } else  {
#if RGB_BACKLIGHT_ENABLED
        // If the EEPROM has not been saved before, or is out of date,
        // save the default values to the EEPROM. Default values
        // come from construction of the zeal_backlight_config instance.
        //backlight_config_save();
#endif // RGB_BACKLIGHT_ENABLED
#ifdef DYNAMIC_KEYMAP_ENABLE
        // This resets the keymaps in EEPROM to what is in flash.
        dynamic_keymap_reset();
        // This resets the macros in EEPROM to nothing.
        //dynamic_keymap_macro_reset();
#endif
        // Save the magic number last, in case saving was interrupted
        eeprom_set_valid(true);
    }

    bootmagic_lite();

    matrix_init_user();
}

void matrix_scan_kb(void) {

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    //backlight_set_indicator_state(usb_led);
}

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}