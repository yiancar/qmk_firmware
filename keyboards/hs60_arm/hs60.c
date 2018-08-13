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
#include "hs60.h"
#include "config.h"

// Please ignore this is for upcoming features
/*#ifdef RAW_ENABLE

void raw_hid_receive( uint8_t *data, uint8_t length )
{
	uint8_t command = data[0];
	switch ( command )
	{
		case id_protocol_version:
		{
			msg_protocol_version *msg = (msg_protocol_version*)&data[1];
			msg->version = PROTOCOL_VERSION;
			break;
		}
#if USE_KEYMAPS_IN_EEPROM
		case id_keymap_keycode_load:
		{
			msg_keymap_keycode_load *msg = (msg_keymap_keycode_load*)&data[1];
			msg->keycode = keymap_keycode_load( msg->layer, msg->row, msg->column );
			break;
		}
		case id_keymap_keycode_save:
		{
			msg_keymap_keycode_save *msg = (msg_keymap_keycode_save*)&data[1];
			keymap_keycode_save( msg->layer, msg->row, msg->column, msg->keycode);
			break;
		}
		case id_keymap_default_save:
		{
			keymap_default_save();
			break;
		}
#endif // USE_KEYMAPS_IN_EEPROM
		case id_backlight_config_set_values:
		{
			msg_backlight_config_set_values *msg = (msg_backlight_config_set_values*)&data[1];
			backlight_config_set_values(msg);
			backlight_config_save();
			break;
		}
		case id_backlight_config_set_alphas_mods:
		{
			msg_backlight_config_set_alphas_mods *msg = (msg_backlight_config_set_alphas_mods*)&data[1];
			backlight_config_set_alphas_mods( msg->alphas_mods );
			backlight_config_save();
			break;
		}
		case id_backlight_set_key_color:
		{
			msg_backlight_set_key_color *msg = (msg_backlight_set_key_color*)&data[1];
			backlight_set_key_color(msg->row, msg->column, msg->hsv);
			break;
		}
		case id_system_get_state:
		{
			msg_system_state *msg = (msg_system_state*)&data[1];
			msg->value = backlight_get_tick();
			break;
		}
		default:
		{
			// Unhandled message.
			data[0] = id_unhandled;
			break;
		}
	}

	// Return same buffer with values changed
	raw_hid_send( data, length );

}

#endif*/

void bootmagic_lite(void)
{
	// The lite version of TMK's bootmagic made by Wilba.
	// 100% less potential for accidentally making the
	// keyboard do stupid things.

	// We need multiple scans because debouncing can't be turned off.
	matrix_scan();
	wait_ms(DEBOUNCING_DELAY);
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

	bootmagic_lite();

    // Please ignore this is for upcoming features
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	/*if (eeprom_is_valid())
	{
		backlight_config_load();

		// TODO: do something to "turn on" keymaps in EEPROM?
	}
	else
	{
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the zeal_backlight_config instance.
		backlight_config_save();

		// Clear the LED colors stored in EEPROM
		for ( int row=0; row < MATRIX_ROWS; row++ )
		{
			HSV hsv;
			for ( int column=0; column < MATRIX_COLS; column++ )
			{
				hsv.h = rand() & 0xFF;
				hsv.s = rand() & 0x7F;
				hsv.v = 255;
				backlight_set_key_color( row, column, hsv );
			}
		}
        #ifdef USE_KEYMAPS_IN_EEPROM
		keymap_default_save();
		#endif
		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}*/

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