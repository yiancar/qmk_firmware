/*
Copyright 2012-2020 Jun Wako, Jack Humbert, Yiancar-Designs

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "matrix.h"
#include "wait.h"
#include "i2c_master.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static i2c_status_t left_i2c_status = I2C_STATUS_ERROR;
static i2c_status_t right_i2c_status = I2C_STATUS_ERROR;

static void unselect_rows(void) {
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        gpio_set_pin_input_high(row_pins[x]);
    }
    // Port expanders initialize at high outputs. There is no need to unselect them.
}

static void select_row(uint8_t row) {
    gpio_set_pin_output(row_pins[row]);
    gpio_write_pin_low(row_pins[row]);
    if (left_i2c_status == I2C_STATUS_SUCCESS) {
        uint8_t send_data = 0xFF & ~((uint8_t) 1 << row);
        left_i2c_status = i2c_write_register((LEFT_ADDRESS << 1), 0x02, &send_data, 1, 10);
    }
    if (right_i2c_status == I2C_STATUS_SUCCESS) {
        uint8_t send_data = 0xFF & ~((uint8_t) 1 << row);
        right_i2c_status = i2c_write_register((RIGHT_ADDRESS << 1), 0x02, &send_data, 1, 10);
    }
}

static void unselect_row(uint8_t row) {
    gpio_set_pin_input_high(row_pins[row]);
    // Port expander will be rewritten on the next loop so no need to clear the register.
    // if (left_i2c_status == I2C_STATUS_SUCCESS) {
    //     uint8_t send_data = 0xFF | ((uint8_t)1 << row);
    //     left_i2c_status = i2c_write_register((LEFT_ADDRESS << 1), 0x02, &send_data, 1, 20);
    // }
}

static void init_pins(void) {
    unselect_rows();

    for (uint8_t x = 0; x < 4; x++) {
        // Only first 4 columns have a GPIO pin.
        gpio_set_pin_input_high(col_pins[x]);
    }
}

static void init_i2c_left_pins(void) {
    uint8_t send_data = 0x00;
    // Set rows to outputs, default is high
    left_i2c_status = i2c_write_register((LEFT_ADDRESS << 1), 0x06, &send_data, 1, 10);
    if (left_i2c_status != I2C_STATUS_SUCCESS) {
        return;
    }
    send_data = 0xFF;
    // Set cols to enable pullup, input is default, pull up is default
    left_i2c_status = i2c_write_register((LEFT_ADDRESS << 1), 0x47, &send_data, 1, 10);
}

static void init_i2c_right_pins(void) {
    uint8_t send_data = 0x00;
    // Set rows to outputs, default is high
    right_i2c_status = i2c_write_register((RIGHT_ADDRESS << 1), 0x06, &send_data, 1, 10);
    if (right_i2c_status != I2C_STATUS_SUCCESS) {
        return;
    }
    send_data = 0xFF;
    // Set cols to enable pullup, input is default, pull up is default
    right_i2c_status = i2c_write_register((RIGHT_ADDRESS << 1), 0x47, &send_data, 1, 10);
}

void matrix_init_custom(void) {
    // TODO: initialize hardware here
    // Initialize I2C
    i2c_init();

    // initialize key pins
    init_pins();
    wait_ms(100);
    init_i2c_left_pins();
    wait_ms(100);
    init_i2c_right_pins();
    wait_ms(100);
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Try reconnecting to left
    if (left_i2c_status != I2C_STATUS_SUCCESS) {
        init_i2c_left_pins();
    }
    // Try reconnecting to left
    if (right_i2c_status != I2C_STATUS_SUCCESS) {
        init_i2c_right_pins();
    }

    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    matrix_io_delay();

    uint8_t left_col_buffer = 0xFF;
    if (left_i2c_status == I2C_STATUS_SUCCESS) {
        left_i2c_status = i2c_read_register((LEFT_ADDRESS << 1), 0x01, &left_col_buffer, 1, 10);
    }

    uint8_t right_col_buffer = 0xFF;
    if (right_i2c_status == I2C_STATUS_SUCCESS) {
        right_i2c_status = i2c_read_register((RIGHT_ADDRESS << 1), 0x01, &right_col_buffer, 1, 10);
    }

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        uint8_t pin_state;
        // Select the col pin to read (active low)
        if (col_index > 9 ) {
            pin_state = right_col_buffer & (1 << (col_index - 6 - 4));
        } else if (col_index > 3 ) {
            pin_state = left_col_buffer & (1 << (col_index - 4));
        } else {
            // This is safe as the only values for the loop are 0 to 3.
            pin_state = gpio_read_pin(col_pins[col_index]);
        }

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_has_changed |= read_cols_on_row(current_matrix, current_row);
    }

    return matrix_has_changed;
}
