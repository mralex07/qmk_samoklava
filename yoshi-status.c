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

/* Graphical Yoshi animation status display.
   Yoshi is 32x32 pixels and frames are oriented for
   vertical rendering (OLED_ROTATION_270).
*/

#include "filterpaper.h"

#define YOSHI_FRAME_DURATION 130 // Number of ms between frames
#define YOSHI_SIZE 128 // Yoshi is 32 x 32px


static void render_yoshi_ready(void) {
	static char const ready[][YOSHI_SIZE] PROGMEM = { {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x70, 0xc8, 0x48, 0x28, 0x3c,
		0x42, 0x81, 0x81, 0x9a, 0x41, 0x99, 0x42, 0x3c, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x10, 0x08, 0x08, 0x0b, 0x8c, 0x1c, 0x6f, 0xb0, 0x60, 0x00,
		0x00, 0x00, 0x10, 0xb8, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x40, 0x41, 0x21, 0x1e, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x80, 0x7e, 0x11, 0x11, 0x13, 0x12, 0x72, 0xc2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xc0, 0x38, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x3a, 0x66, 0x46, 0x8a, 0x89, 0x91,
		0x90, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x90, 0x50, 0x78, 0x84,
		0x02, 0x02, 0x34, 0x82, 0x32, 0x84, 0x78, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x89, 0xf8, 0xdf, 0x60, 0xc0, 0x00, 0x00,
		0x01, 0x21, 0x71, 0x80, 0x01, 0x00, 0x00, 0x02, 0x80, 0x82, 0x43, 0x3c, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x3c, 0xc4, 0x3c, 0x42, 0x82, 0x81, 0xa1, 0x44, 0x3c, 0x04, 0x01, 0x00, 0x00, 0x80,
		0x60, 0x3e, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x38, 0x27, 0x21, 0x21, 0x21, 0x21, 0x27, 0xfc, 0x84, 0x84, 0x84, 0x8e, 0x92, 0x91,
		0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0xa0, 0xf0, 0x08, 0x04,
		0x04, 0x08, 0x84, 0x04, 0x08, 0xf0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x12, 0x71, 0xbf, 0xc1, 0x80, 0x00, 0x01, 0x01,
		0x41, 0xe1, 0x00, 0x01, 0x01, 0x00, 0x04, 0x00, 0x05, 0x86, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xf0, 0x10, 0x18, 0x28, 0x54, 0x52, 0x52, 0xea, 0x3f, 0x02, 0x01, 0x58, 0x30, 0xe0,
		0xc0, 0xbc, 0x03, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xe3, 0x9c, 0x84, 0x84, 0x84, 0x84, 0x9d, 0xf2, 0x94, 0x8c, 0x9c, 0x9a, 0x97,
		0xe5, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x90, 0x50, 0x78, 0x84,
		0x02, 0x02, 0x34, 0x82, 0x32, 0x84, 0x78, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x86, 0x89, 0xf8, 0xdf, 0x60, 0xc0, 0x00, 0x00,
		0x01, 0x21, 0x71, 0x80, 0x01, 0x00, 0x00, 0x02, 0x80, 0x82, 0x43, 0x3c, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x3c, 0xc4, 0x06, 0x0a, 0x15, 0x14, 0x14, 0x7a, 0x8f, 0x00, 0x01, 0x16, 0x8c, 0xf8,
		0x70, 0xee, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xe0, 0x9d, 0x86, 0x86, 0x84, 0x84, 0x9c, 0xfc, 0x25, 0x25, 0x23, 0x22, 0x25,
		0x25, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x70, 0xc8, 0x48, 0x28, 0x3c, 0x42,
		0x81, 0x81, 0x9a, 0x41, 0x99, 0x42, 0x3c, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x43, 0x44, 0xfc, 0x6f, 0xb0, 0x60, 0x00, 0x00,
		0x00, 0x10, 0xb8, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x40, 0x41, 0x21, 0x1e, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x1e, 0x62, 0x83, 0x05, 0x0a, 0x0a, 0x0a, 0x0f, 0x11, 0x11, 0x20, 0x21, 0x20, 0xe0,
		0x31, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xe0, 0x9c, 0x85, 0x85, 0x86, 0x86, 0x9e, 0xf6, 0x06, 0x06, 0x05, 0x05, 0x04,
		0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	} };
	static char const *anim[] = {
		ready[0], ready[1], ready[2], ready[3],
		ready[4], ready[3], ready[2], ready[1]
	};

	static uint8_t current_frame = 0;
	current_frame = (current_frame + 1 > sizeof(anim)/sizeof(anim[0]) - 1) ? 0 : current_frame + 1;
	oled_write_raw_P(anim[current_frame], YOSHI_SIZE);
}


static void render_yoshi_fly(void) {
	static char const fly[][YOSHI_SIZE] PROGMEM = { {
		0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x90, 0x3c, 0x02, 0x45, 0x85, 0x8a, 0x61, 0x29, 0x16,
		0x0c, 0x08, 0x48, 0x08, 0x50, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x06, 0x09, 0x38, 0x5f, 0xfc, 0xc2, 0x01, 0x01, 0xc2, 0x5c, 0x50, 0xa0, 0xa0,
		0xe0, 0x20, 0x20, 0x10, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xc0, 0xb0, 0x68, 0xf4, 0x1f, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
		0x07, 0x98, 0x60, 0x10, 0x0c, 0x04, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x0c, 0x13, 0x12, 0x21, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0xf0, 0x90,
		0xcc, 0xa7, 0xa5, 0x56, 0x2e, 0x1a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x90, 0x3c, 0x02, 0x45, 0x85,
		0x8a, 0x61, 0x29, 0x16, 0x0c, 0x08, 0x48, 0x08, 0x50, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x89, 0xb8, 0xdf, 0xe0, 0xe0, 0x40, 0x00, 0x00,
		0x10, 0x10, 0xa0, 0xa0, 0x60, 0xa0, 0xa0, 0x10, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc4, 0xa8, 0x78, 0x98, 0x68, 0x1d, 0x0d, 0x00,
		0x00, 0x00, 0x00, 0x01, 0x07, 0x9c, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x70, 0xc8, 0x88, 0x1c, 0x13, 0x32, 0x21, 0xe0, 0xc0, 0xc0, 0x40, 0x40,
		0x60, 0x60, 0x90, 0x10, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x90, 0x3c, 0x02, 0x45, 0x85,
		0x8a, 0x61, 0x29, 0x16, 0x0c, 0x08, 0x48, 0x08, 0x50, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x38, 0x5f, 0xe0, 0xe0, 0x40, 0x00, 0x00,
		0x10, 0x10, 0xa0, 0xa0, 0x60, 0x20, 0x20, 0x10, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xf0, 0x48, 0x44, 0x62, 0xc2, 0xe6, 0x38, 0x0c, 0x02, 0x01, 0x00, 0xb0, 0xa8, 0x44,
		0x00, 0x00, 0x00, 0x01, 0x06, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x1f, 0x20, 0x20, 0x24, 0x1d, 0x0b, 0x16, 0x14, 0x24, 0x22, 0x41, 0x40, 0x40, 0x40,
		0x20, 0x20, 0x10, 0x10, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	} };
	static char const *anim[] = {
		fly[0], fly[1], fly[2], fly[1],
	};

	static uint8_t current_frame = 0;
	current_frame = (current_frame + 1 > sizeof(anim)/sizeof(anim[0]) - 1) ? 0 : current_frame + 1;
	oled_write_raw_P(anim[current_frame], YOSHI_SIZE);
}


static void render_yoshi_hide(void) {
	static char const hide[][YOSHI_SIZE] PROGMEM = { {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x40, 0x40, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x1c, 0xf2, 0x12, 0x0a, 0x0f, 0x10,
		0x20, 0x20, 0x26, 0x10, 0x26, 0x10, 0x0f, 0x48, 0x08, 0x50, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xc0, 0x40, 0x60, 0xa0, 0x50, 0x48, 0x48, 0xa9, 0xff, 0x1b, 0x2c, 0x58, 0xc0, 0x80,
		0x00, 0xc4, 0x2e, 0x30, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x03, 0xec, 0x9c, 0x84, 0x85, 0x85, 0x85, 0x9f, 0xf8, 0xd0, 0xd0, 0xb1, 0xa8, 0x9f,
		0xf7, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x70, 0xc8, 0x48, 0x28, 0x3c, 0x42,
		0x81, 0x81, 0x9a, 0x41, 0x99, 0x42, 0x3c, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x80, 0x80, 0xc0, 0x40, 0xa0, 0x90, 0x93, 0x54, 0xfc, 0x6f, 0xb0, 0x60, 0x00, 0x00,
		0x00, 0x10, 0xb8, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x40, 0x41, 0x21, 0x1e, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x07, 0xf8, 0x9c, 0x85, 0x86, 0x86, 0x86, 0x9f, 0xf1, 0xa0, 0xa0, 0xe2, 0xd1, 0xbf,
		0xee, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xc0, 0x30, 0xc8, 0x24, 0xec, 0xb0, 0xb8, 0xe6, 0xf1, 0x49, 0x36, 0x0a, 0x12, 0x0c,
		0x0a, 0x12, 0xfc, 0x48, 0x28, 0x30, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x07, 0xf8, 0x9c, 0x85, 0x84, 0x84, 0x84, 0x9f, 0xfc, 0x94, 0xd2, 0xaa, 0xb9, 0xa5,
		0xc1, 0x41, 0x80, 0x80, 0x80, 0x81, 0x40, 0x41, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	} };
	static char const *anim[] = {
		hide[0], hide[0], hide[1], hide[2],
		hide[2], hide[2], hide[2], hide[2],
		hide[2], hide[1], hide[0], hide[0]
	};

	static uint8_t current_frame = 0;
	current_frame = (current_frame + 1 > sizeof(anim)/sizeof(anim[0]) - 1) ? 0 : current_frame + 1;
	oled_write_raw_P(anim[current_frame], YOSHI_SIZE);
}


static void render_yoshi_idle(void) {
	static char const idle[][YOSHI_SIZE] PROGMEM = { {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0xa0, 0xf0, 0x08, 0x04,
		0x04, 0x68, 0x04, 0x64, 0x08, 0xf0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x12, 0x71, 0xbf, 0xc1, 0x80, 0x00, 0x01, 0x02,
		0x42, 0xe2, 0x01, 0x02, 0x01, 0x00, 0x04, 0x00, 0x05, 0x86, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xf0, 0x10, 0x18, 0xe8, 0x34, 0x12, 0x0a, 0x0e, 0x07, 0xa6, 0xd1, 0x00, 0x00, 0x00,
		0x80, 0xfe, 0x77, 0x26, 0x0a, 0xf2, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xe3, 0x9c, 0x85, 0x86, 0x84, 0x84, 0x9c, 0xf4, 0x92, 0x89, 0x98, 0x98, 0x96,
		0xe3, 0x03, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0xa0, 0xf0, 0x08, 0x04,
		0x04, 0x68, 0x04, 0x64, 0x08, 0xf0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x12, 0x71, 0xbf, 0xc1, 0x80, 0x00, 0x01, 0x02,
		0x42, 0xe2, 0x01, 0x02, 0x01, 0x00, 0x04, 0x00, 0x05, 0x86, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xf0, 0x10, 0x18, 0xe8, 0x34, 0x12, 0x0a, 0x0e, 0x07, 0xa6, 0xd1, 0x00, 0x00, 0x00,
		0x80, 0xfe, 0x73, 0xda, 0xe6, 0x9e, 0x8e, 0x83, 0x79, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xe3, 0x9c, 0x85, 0x86, 0x84, 0x84, 0x9c, 0xf4, 0x92, 0x89, 0x98, 0x98, 0x96,
		0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0xa0, 0xf0, 0x08, 0x04,
		0x04, 0x68, 0x04, 0x64, 0x08, 0xf0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x12, 0x71, 0xbf, 0xc1, 0x80, 0x00, 0x01, 0x02,
		0x42, 0xe2, 0x01, 0x02, 0x01, 0x00, 0x04, 0x00, 0x05, 0x86, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xf0, 0x10, 0x18, 0xe8, 0x34, 0x12, 0x0a, 0x0e, 0x07, 0xa6, 0xd1, 0x00, 0x00, 0x00,
		0x80, 0xfe, 0x73, 0xda, 0xe6, 0x9e, 0x8a, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xe3, 0x9c, 0x85, 0x86, 0x84, 0x84, 0x9c, 0xf4, 0x92, 0x89, 0x98, 0x98, 0x96,
		0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	} };
	static char const *anim[] = {
		idle[0], idle[0], idle[1], idle[2],
		idle[1], idle[2], idle[1], idle[2],
		idle[1], idle[0]
	};

	static uint8_t current_frame = 0;
	current_frame = (current_frame + 1 > sizeof(anim)/sizeof(anim[0]) - 1) ? 0 : current_frame + 1;
	oled_write_raw_P(anim[current_frame], YOSHI_SIZE);
}


static void render_yoshi_run(void) {
	static char const run[][YOSHI_SIZE] PROGMEM = { {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x90, 0xd8, 0x74,
		0x12, 0x0a, 0x0f, 0x10, 0x20, 0x20, 0x26, 0x10, 0x26, 0x10, 0x0f, 0x48, 0x08, 0x50, 0x20, 0xc0,
		0x00, 0x00, 0xf0, 0x10, 0x18, 0x28, 0x54, 0x52, 0x52, 0x7a, 0x8f, 0x8a, 0x05, 0x0f, 0x07, 0x04,
		0x88, 0xf0, 0x10, 0x20, 0x20, 0x24, 0x2e, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x08, 0x07,
		0x64, 0x44, 0x88, 0x8b, 0x94, 0x98, 0xe8, 0x10, 0x10, 0x10, 0x10, 0xf0, 0x99, 0xcd, 0xa5, 0xa7,
		0x55, 0x2c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xe0, 0x20,
		0xb0, 0xe8, 0x24, 0x14, 0x1e, 0x21, 0x40, 0x40, 0x4d, 0x20, 0x4c, 0x21, 0x1e, 0x90, 0x10, 0xa0,
		0x10, 0x10, 0x70, 0xc0, 0x78, 0x88, 0x0c, 0x14, 0x2a, 0x29, 0x29, 0x3d, 0x47, 0x45, 0x82, 0x87,
		0x87, 0x88, 0xd0, 0xe0, 0x60, 0x40, 0x40, 0xc8, 0x5c, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x20,
		0x08, 0x09, 0x07, 0x00, 0x00, 0x01, 0xe2, 0xa4, 0xb4, 0x98, 0x98, 0x98, 0x98, 0xe8, 0x08, 0x04,
		0x04, 0x1f, 0x31, 0x20, 0x20, 0x30, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	} };

	static uint8_t current_frame = 0;
	current_frame = (current_frame + 1 > 2 - 1) ? 0 : current_frame + 1;
	oled_write_raw_P(run[current_frame], YOSHI_SIZE);
}

static void render_yoshi_status(void) {
#ifdef WPM_ENABLE
	static uint8_t prev_wpm = 0;
	static uint32_t tap_timer = 0; // WPM triggered
	if (get_current_wpm() > prev_wpm) { tap_timer = timer_read32(); }
	prev_wpm = get_current_wpm();
#else
	extern uint32_t tap_timer; // process_record_user() triggered
#endif
	// Elapsed time between key presses
	uint32_t keystroke = timer_elapsed32(tap_timer);
	static uint16_t anim_timer = 0;

	void animation_phase(void) {
		oled_set_cursor(0,6);
		if (get_mods() & MOD_MASK_SHIFT) { render_yoshi_fly(); }
		else if (get_mods() & MOD_MASK_CAG) { render_yoshi_hide(); }
		else if (get_highest_layer(layer_state) > DEF) { render_yoshi_idle(); }
		else if (keystroke < YOSHI_FRAME_DURATION*3) { render_yoshi_run(); }
		else { render_yoshi_ready(); }
	}

	if (keystroke > OLED_TIMEOUT*2) { oled_off(); }
	else if (timer_elapsed(anim_timer) > YOSHI_FRAME_DURATION) {
		anim_timer = timer_read();
		animation_phase();
	}
}


// Init and rendering calls
oled_rotation_t oled_init_user(oled_rotation_t const rotation) {
	return OLED_ROTATION_270;
}

void oled_task_user(void) {
	if (is_keyboard_master()) render_yoshi_status();
}