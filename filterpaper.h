/* Copyright (C) 2021 @filterpaper
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
#include QMK_KEYBOARD_H

// Layer references
enum layers { DEF, CMK, LWR, RSE, ADJ };

// Custom dimmer indicator colors and effects
#ifdef RGB_MATRIX_ENABLE
#	define RGB_BSTEEL	60, 90, 128
#	define RGB_DGRAY	77, 77, 77
#	define RGB_DEFAULT	RGB_BSTEEL
#	define RGB_MODS		RGB_BSTEEL
#	define RGB_CAPS		RGB_PURPLE
#	define RGB_LAYER	RGB_DGRAY
#	define HSV_DEFAULT	HSV_AZURE
#	define MATRIX_NORMAL	RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#	define MATRIX_SHIFT		RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#endif

#ifdef OLED_DRIVER_ENABLE
void render_mod_status(void);
void animate_cat(void);
#	define SLIMCAT
//#	define LEFTCAT
//#	define RIGHTCAT
#ifdef LUNA
void animate_luna(void);
#endif
#endif
