/*
DDCANJOMOUSE2040.h

Copyright (c) 2015, Arduino LLC
Original code (pre-library): Copyright (c) 2011, Peter Barrett

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef JOYMOUSERP2040_h
#define JOYMOUSERP2040_h

#include <Arduino.h>
#include "Adafruit_TinyUSB.h"

//================================================================================
//================================================================================
//  Mouse

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)
#define MOUSE_UP 3
#define MOUSE_DOWN 4

class JoyMouseRP2040_
{
private:
	Adafruit_USBD_HID usb_hid;
protected:
	uint8_t _buttons;
	void buttons(uint8_t b);
	int limit_xy(int const xy);
public:
	JoyMouseRP2040_();
	void begin(void);
	void end(void);
	void click(uint8_t b = MOUSE_LEFT);
	void move(int x, int y, signed char wheel = 0);
	void press(uint8_t b = MOUSE_LEFT);   // press LEFT by default
	void release(uint8_t b = MOUSE_LEFT); // release LEFT by default
	bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
};

#endif
