/*
DDCANJOMOUSE2040.cpp

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

#include "DDCANJOMOUSE2040.h"

#define USB_POLLING_RATE 2

uint8_t const _hidReportDescriptor[] = {
	TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(HID_ITF_PROTOCOL_MOUSE))
};

//================================================================================
//================================================================================
//	JoyMouseRP2040

/* This function is for limiting the input value for x and y
* axis to -127 <= x/y <= 127 since this is the allowed value
* range for a USB HID device.
*/
int JoyMouseRP2040_::limit_xy(int const xy)
{
	if     (xy < -127) return -127;
	else if(xy >  127) return 127;
	else               return xy;
}

JoyMouseRP2040_::JoyMouseRP2040_(void) : _buttons(0) {}

void JoyMouseRP2040_::begin(void)
{
	usb_hid.setPollInterval(USB_POLLING_RATE);
	usb_hid.setReportDescriptor(_hidReportDescriptor, sizeof(_hidReportDescriptor));
	usb_hid.begin();
	while( !TinyUSBDevice.mounted() ) delay(1);
}

void JoyMouseRP2040_::end(void)
{
}

void JoyMouseRP2040_::click(uint8_t b)
{
	_buttons = b;
	move(0,0,0);
	delay(10);
	_buttons = 0;
	move(0,0,0);
	delay(5);
}

void JoyMouseRP2040_::move(int x, int y, signed char wheel)
{
	if ( TinyUSBDevice.suspended() )
	{
		TinyUSBDevice.remoteWakeup();
	}
	while(!usb_hid.ready())
	{
		delay(1);
	};
	usb_hid.mouseReport(HID_ITF_PROTOCOL_MOUSE, _buttons, limit_xy(x), limit_xy(y), wheel, 0);
}

void JoyMouseRP2040_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0,0,0);
	}
}

void JoyMouseRP2040_::press(uint8_t b)
{
	buttons(_buttons | b);
}

void JoyMouseRP2040_::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

bool JoyMouseRP2040_::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0)
	{
		return true;
	}
	return false;
}
