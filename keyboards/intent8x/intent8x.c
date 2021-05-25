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
#ifndef RGB_BACKLIGHT_INTENT8X
#error RGB_BACKLIGHT_INTENT8X not defined, recheck config.h
#endif

#include "intent8x.h"
#include "i2c_master.h"
#include "drivers/issi/is31fl3733.h"

#define USB_HUB_ADDRESS 0x2D // This is the 7bit address
uint8_t usb_hub_write_buffer[8] = { 0 };
uint8_t usb_hub_config_reg_access_cmd[3] = { 0x99, 0x37, 0x00 };
uint8_t usb_hub_attach[3] = { 0xAA, 0x55, 0x00 };
uint8_t usb_hub_read_buffer[2] = { 0xFF, 0xFF };

void keyboard_pre_init_kb(void) {
    i2c_init();
    i2c_start(USB_HUB_ADDRESS << 0);

    usb_hub_write_buffer[0] = 0x00; // Config Register Access - Direction Address
    usb_hub_write_buffer[1] = 0x00; // Config Register Access - Direction Address
    usb_hub_write_buffer[2] = 0x05; // Number of bytes to write
    usb_hub_write_buffer[3] = 0x00; // Config Register Access - Register Write
    usb_hub_write_buffer[4] = 0x01; // Number of Configuration Register bytes to write
    usb_hub_write_buffer[5] = 0x3C; // Upper byte of Configuration Register address - VBUS_PASS_THRU
    usb_hub_write_buffer[6] = 0x40; // Lower byte of Configuration Register address - VBUS_PASS_THRU
    usb_hub_write_buffer[7] = 0x04; // Data - [0] USB_PASS_THRU [2] HUB_CONN_PASS_THRU [1] [7:3] Reserved
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    usb_hub_write_buffer[5] = 0x3C; // Upper byte of Configuration Register address - SUSP_SEL
    usb_hub_write_buffer[6] = 0x52; // Lower byte of Configuration Register address - SUSP_SEL
    usb_hub_write_buffer[7] = 0x01; // Data - [0] SUSPEND_SEL [7:1] Reserved
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    usb_hub_write_buffer[5] = 0x30; // Upper byte of Configuration Register address - MAXPS
    usb_hub_write_buffer[6] = 0x0C; // Lower byte of Configuration Register address - MAXPS
    usb_hub_write_buffer[7] = 0x32; // Data - [7:0] MAX_PWR_SP
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    usb_hub_write_buffer[5] = 0x30; // Upper byte of Configuration Register address - HUB_CFG2
    usb_hub_write_buffer[6] = 0x07; // Lower byte of Configuration Register address - HUB_CFG2
    usb_hub_write_buffer[7] = 0x2A; // Data - [2:0] Reserved [3] COMPOUND [7:4] Other Stuff
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    usb_hub_write_buffer[5] = 0x30; // Upper byte of Configuration Register address - NRD
    usb_hub_write_buffer[6] = 0x09; // Lower byte of Configuration Register address - NRD
    usb_hub_write_buffer[7] = 0x0C; // Data - [7:0] NR_DEVICE
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    usb_hub_write_buffer[5] = 0x09; // Upper byte of Configuration Register address - PIO_39_32_DIR
    usb_hub_write_buffer[6] = 0x33; // Lower byte of Configuration Register address - PIO_39_32_DIR
    usb_hub_write_buffer[7] = 0x01; // Data - [7:0] PIO DIR 39..32 (1 = Output)
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    usb_hub_write_buffer[5] = 0x09; // Upper byte of Configuration Register address - PIO_39_32_OUT
    usb_hub_write_buffer[6] = 0x37; // Lower byte of Configuration Register address - PIO_39_32_OUT
    usb_hub_write_buffer[7] = 0x01; // Data - [7:0] PIO OUT 39..32
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    usb_hub_write_buffer[2] = 0x04; // Number of bytes to write
    usb_hub_write_buffer[3] = 0x01; // Config Register Access - Register Read
    usb_hub_write_buffer[5] = 0x08; // Upper byte of Configuration Register address - PIO_16_23_IN
    usb_hub_write_buffer[6] = 0x39; // Lower byte of Configuration Register address - PIO_16_23_IN
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 7, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);
    usb_hub_write_buffer[1] = 0x04; // Config Register Access - Data Address
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 2, usb_hub_read_buffer, 2);

    usb_hub_write_buffer[1] = 0x00; // Config Register Access - Direction Address
    usb_hub_write_buffer[2] = 0x05; // Number of bytes to write
    usb_hub_write_buffer[3] = 0x00; // Config Register Access - Register Write
    usb_hub_write_buffer[5] = 0x31; // Upper byte of Configuration Register address - CONNECT_CFG
    usb_hub_write_buffer[6] = 0x8E; // Lower byte of Configuration Register address - CONNECT_CFG
    if (usb_hub_read_buffer[1] & (1 << 0)) {
        // USB0 is Upstream
        usb_hub_write_buffer[7] = 0x82; // Data - [0] FLEXCONNECT [1] EN_FLEX_MODE [7:2] Other
    } else {
        // USB1 is Upstream
        usb_hub_write_buffer[7] = 0x83; // Data - [0] FLEXCONNECT [1] EN_FLEX_MODE [7:2] Other
    }
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_write_buffer, 8, 0, 0);
    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_config_reg_access_cmd, 3, 0, 0);

    i2cMasterTransmit(&I2CD1, USB_HUB_ADDRESS, usb_hub_attach, 3, 0, 0);
}
