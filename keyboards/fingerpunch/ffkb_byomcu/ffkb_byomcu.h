/* Copyright 2021 Sadek Baroudi <sadekbaroudi@gmail.com>
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// With the shift register, define the columns in the order of A-H as defined in the schematic
#define LAYOUT_ffkb( \
    K01, K02, K03, K04, K05, K06,           K07, K08, K09, K0A, K0B, K0C, \
    K11, K12, K13, K14, K15, K16,           K17, K18, K19, K1A, K1B, K1C, \
    K21, K22, K23, K24, K25, K26,           K27, K28, K29, K2A, K2B, K2C, \
              K32,      K34, K35, K36, K37, K38, K39,      K3B, \
                                    K3A \
) \
{ \
    { K01,   K03,  K05, K04, K06, K07, K08, K02   }, \
    { K11,   K13,  K15, K14, K16, K17, K18, K12   }, \
    { K21,   K23,  K25, K24, K26, K27, K28, K22   }, \
    { KC_NO, K19,  K0A, K2A, K1B, K2B, K0C, KC_NO }, \
    { KC_NO, K29,  K1A, K09, K0B, K2C, K1C, K3A   }, \
    { K3B,   K39,  K35, K34, K36, K37, K38, K32   } \
}

// This one works for matrix_74hc595_spi.c
/*
    { K01,   K03,  K05, K04, K06, K07, K08, K02   }, \
    { K11,   K13,  K15, K14, K16, K17, K18, K12   }, \
    { K21,   K23,  K25, K24, K26, K27, K28, K22   }, \
    { KC_NO, K19,  K0A, K2A, K1B, K2B, K0C, KC_NO }, \
    { KC_NO, K29,  K1A, K09, K0B, K2C, K1C, K3A   }, \
    { K3B,   K39,  K35, K34, K36, K37, K38, K32   } \
*/

// This one worked on matrix_fingerpunch.c
/*
    { K02,   K01,   K03,  K05, K04, K06, K07, K08 }, \
    { K12,   K11,   K13,  K15, K14, K16, K17, K18 }, \
    { K22,   K21,   K23,  K25, K24, K26, K27, K28 }, \
    { KC_NO, KC_NO, K19,  K0A, K2A, K1B, K2B, K0C }, \
    { K3A,   KC_NO, K29,  K1A, K09, K0B, K2C, K1C }, \
    { K32,   K3B,   K39,  K35, K34, K36, K37, K38 } \
*/

// Stock ffkb v2 map
/*
    { K01,   K02,   K03,  K04, K05, K06, K07, K08 }, \
    { K11,   K12,   K13,  K14, K15, K16, K17, K18 }, \
    { K21,   K22,   K23,  K24, K25, K26, K27, K28 }, \
    { KC_NO, KC_NO, K19,  K2A, K0A, K1B, K2B, K0C }, \
    { KC_NO, K3A,   K29,  K09, K1A, K0B, K2C, K1C }, \
    { K3B,   K32,   K39,  K34, K35, K36, K37, K38 } \
*/

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
extern uint16_t          dpi_array[];

enum keyboard_keycodes {
#ifdef VIAL_ENABLE
    DPI_UP = USER00,
#else
    DPI_UP = SAFE_RANGE,
#endif
    DPI_DN,
    DPI_FINE,
    NEW_SAFE_RANGE

};