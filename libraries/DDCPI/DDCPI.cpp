/*
  Joystick.cpp

  Copyright (c) 2015-2017, Matthew Heironimus

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

#include "DDCPI.h"
#include "Adafruit_TinyUSB.h"
#include <Arduino.h>

#define JOYSTICK_REPORT_ID_INDEX 7
#define JOYSTICK_AXIS_MINIMUM -32767
#define JOYSTICK_AXIS_MAXIMUM 32767
#define JOYSTICK_SIMULATOR_MINIMUM -32767
#define JOYSTICK_SIMULATOR_MAXIMUM 32767


#define JOYSTICK_INCLUDE_X_AXIS  0b00000001
#define JOYSTICK_INCLUDE_Y_AXIS  0b00000010
#define JOYSTICK_INCLUDE_Z_AXIS  0b00000100
#define JOYSTICK_INCLUDE_RX_AXIS 0b00001000
#define JOYSTICK_INCLUDE_RY_AXIS 0b00010000
#define JOYSTICK_INCLUDE_RZ_AXIS 0b00100000

#define JOYSTICK_INCLUDE_RUDDER      0b00000001
#define JOYSTICK_INCLUDE_THROTTLE    0b00000010
#define JOYSTICK_INCLUDE_ACCELERATOR 0b00000100
#define JOYSTICK_INCLUDE_BRAKE       0b00001000
#define JOYSTICK_INCLUDE_STEERING    0b00010000

#define USB_POLLING_RATE 1

#define TOTAL_LED_COUNT 128
#define LED_BUFFER_SIZE 384
uint8_t led_buffer[LED_BUFFER_SIZE];  // Store full LED data
uint8_t temp_buffer[64];              // Temporary storage for each HID report
uint32_t DDCsettings = 0;

void print_led_buffer(uint8_t start_led, uint8_t count) {
    for (int i = 0; i < count; i++) {
        int index = (start_led + i) * 3;
        Serial.printf("LED %d: R=%3d G=%3d B=%3d\n",
            start_led + i,
            led_buffer[index],
            led_buffer[index + 1],
            led_buffer[index + 2]);
    }
}


// TinyUSB HID OUT Report Callback
void tud_hid_set_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    Serial.println("WE HAVE TRIGGERED!!");
	
	// Only process output reports (not feature reports)
    if (report_type != HID_REPORT_TYPE_OUTPUT) return;
    
    // Only process LED reports (ID 0x68)
    if (report_id != 0x68) return;

    // Minimum valid size: Report ID + 3 header bytes
    if (bufsize < 4) return;  

    // Copy the buffer into a local temp if you want, or just use it directly
    memcpy(temp_buffer, buffer, bufsize); // Only necessary if you plan to reuse or modify

   // Extract header information
   uint8_t start_led   = buffer[1];  // Start index in LED array
   uint8_t led_count   = buffer[2];  // Number of LEDs affected
   uint8_t draw_flag   = buffer[3];  // 0 = store, 1 = update LEDs

   // Ensure start position + led_count doesn't exceed buffer size
   uint16_t start_pos = start_led * 3;
   uint16_t end_pos   = start_pos + (led_count * 3);

   if (end_pos <= LED_BUFFER_SIZE) {
	   // Copy LED data into the correct position in led_buffer
	   memcpy(&led_buffer[start_pos], &temp_buffer[4], led_count * 3);
   }

	if (draw_flag) {
		Serial.println("Full LED buffer state:");
		print_led_buffer(0, TOTAL_LED_COUNT);
	}
	
}

Joystick_::Joystick_(
	uint8_t hidReportId,
	uint8_t joystickType,
    uint8_t buttonCount,
	uint8_t hatSwitchCount,
	bool includeXAxis,
	bool includeYAxis,
	bool includeZAxis,
	bool includeRxAxis,
	bool includeRyAxis,
	bool includeRzAxis,
	bool includeRudder,
	bool includeThrottle,
	bool includeAccelerator,
	bool includeBrake,
	bool includeSteering)
{
    // Set the USB HID Report ID
    _hidReportId = hidReportId;

    // Save Joystick Settings
    _buttonCount = buttonCount;
	_hatSwitchCount = hatSwitchCount;
	_includeAxisFlags = 0;
	_includeAxisFlags |= (includeXAxis ? JOYSTICK_INCLUDE_X_AXIS : 0);
	_includeAxisFlags |= (includeYAxis ? JOYSTICK_INCLUDE_Y_AXIS : 0);
	_includeAxisFlags |= (includeZAxis ? JOYSTICK_INCLUDE_Z_AXIS : 0);
	_includeAxisFlags |= (includeRxAxis ? JOYSTICK_INCLUDE_RX_AXIS : 0);
	_includeAxisFlags |= (includeRyAxis ? JOYSTICK_INCLUDE_RY_AXIS : 0);
	_includeAxisFlags |= (includeRzAxis ? JOYSTICK_INCLUDE_RZ_AXIS : 0);
	_includeSimulatorFlags = 0;
	_includeSimulatorFlags |= (includeRudder ? JOYSTICK_INCLUDE_RUDDER : 0);
	_includeSimulatorFlags |= (includeThrottle ? JOYSTICK_INCLUDE_THROTTLE : 0);
	_includeSimulatorFlags |= (includeAccelerator ? JOYSTICK_INCLUDE_ACCELERATOR : 0);
	_includeSimulatorFlags |= (includeBrake ? JOYSTICK_INCLUDE_BRAKE : 0);
	_includeSimulatorFlags |= (includeSteering ? JOYSTICK_INCLUDE_STEERING : 0);
	
    // Build Joystick HID Report Description
	
	// Button Calculations
	uint8_t buttonsInLastByte = _buttonCount % 8;
	uint8_t buttonPaddingBits = 0;
	if (buttonsInLastByte > 0)
	{
		buttonPaddingBits = 8 - buttonsInLastByte;
	}
	
	// Axis Calculations
	uint8_t axisCount = (includeXAxis == true)
		+  (includeYAxis == true)
		+  (includeZAxis == true)
		+  (includeRxAxis == true)
		+  (includeRyAxis == true)
		+  (includeRzAxis == true);
		
	uint8_t simulationCount = (includeRudder == true)
		+ (includeThrottle == true)
		+ (includeAccelerator == true)
		+ (includeBrake == true)
		+ (includeSteering == true); 
		
    uint8_t tempHidReportDescriptor[150];
    int hidReportDescriptorSize = 0;

    // USAGE_PAGE (Generic Desktop)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

    // USAGE (Joystick - 0x04; Gamepad - 0x05; Multi-axis Controller - 0x08)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
    tempHidReportDescriptor[hidReportDescriptorSize++] = joystickType;

    // COLLECTION (Application)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0xa1;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

    // REPORT_ID (Default: 3)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x85;
    tempHidReportDescriptor[hidReportDescriptorSize++] = _hidReportId;
	
	if (_buttonCount > 0) {

		// USAGE_PAGE (Button)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;

		// USAGE_MINIMUM (Button 1)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x19;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

		// USAGE_MAXIMUM (Button 32)            
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x29;
		tempHidReportDescriptor[hidReportDescriptorSize++] = _buttonCount;

		// LOGICAL_MINIMUM (0)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

		// LOGICAL_MAXIMUM (1)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x25;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

		// REPORT_SIZE (1)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

		// REPORT_COUNT (# of buttons)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
		tempHidReportDescriptor[hidReportDescriptorSize++] = _buttonCount;

		// UNIT_EXPONENT (0)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x55;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

		// UNIT (None)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x65;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

		// INPUT (Data,Var,Abs)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;

		if (buttonPaddingBits > 0) {
			
			// REPORT_SIZE (1)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

			// REPORT_COUNT (# of padding bits)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
			tempHidReportDescriptor[hidReportDescriptorSize++] = buttonPaddingBits;
					
			// INPUT (Const,Var,Abs)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x03;
			
		} // Padding Bits Needed

	} // Buttons

	if ((axisCount > 0) || (_hatSwitchCount > 0)) {
	
		// USAGE_PAGE (Generic Desktop)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
		
	}

	if (_hatSwitchCount > 0) {

		// USAGE (Hat Switch)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x39;

		// LOGICAL_MINIMUM (0)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

		// LOGICAL_MAXIMUM (7)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x25;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x07;

		// PHYSICAL_MINIMUM (0)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x35;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

		// PHYSICAL_MAXIMUM (315)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x46;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x3B;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

		// UNIT (Eng Rot:Angular Pos)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x65;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x14;

		// REPORT_SIZE (4)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x04;

		// REPORT_COUNT (1)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
						
		// INPUT (Data,Var,Abs)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;
		
		if (_hatSwitchCount > 1) {
			
			// USAGE (Hat Switch)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x39;

			// LOGICAL_MINIMUM (0)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

			// LOGICAL_MAXIMUM (7)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x25;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x07;

			// PHYSICAL_MINIMUM (0)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x35;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

			// PHYSICAL_MAXIMUM (315)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x46;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x3B;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

			// UNIT (Eng Rot:Angular Pos)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x65;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x14;

			// REPORT_SIZE (4)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x04;

			// REPORT_COUNT (1)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
							
			// INPUT (Data,Var,Abs)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;
      
		
		} else {
		
			// Use Padding Bits
		
			// REPORT_SIZE (1)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

			// REPORT_COUNT (4)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x04;
					
			// INPUT (Const,Var,Abs)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x03;
			
		} // One or Two Hat Switches?

	} // Hat Switches

	if (axisCount > 0) {
	
		// USAGE (Pointer)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

		// LOGICAL_MINIMUM (-32767)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x16;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x80;

		// LOGICAL_MAXIMUM (+32767)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x26;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0xFF;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x7F;

		// REPORT_SIZE (16)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x10;

		// REPORT_COUNT (axisCount)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
		tempHidReportDescriptor[hidReportDescriptorSize++] = axisCount;
						
		// COLLECTION (Physical)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0xA1;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

		if (includeXAxis == true) {
			// USAGE (X)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x30;
		}

		if (includeYAxis == true) {
			// USAGE (Y)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x31;
		}
		
		if (includeZAxis == true) {
			// USAGE (Z)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x32;
		}
		
		if (includeRxAxis == true) {
			// USAGE (Rx)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x33;
		}
		
		if (includeRyAxis == true) {
			// USAGE (Ry)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x34;
		}
		
		if (includeRzAxis == true) {
			// USAGE (Rz)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x35;
		}
		
		// INPUT (Data,Var,Abs)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;
		
		// END_COLLECTION (Physical)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0xc0;
		
	} // X, Y, Z, Rx, Ry, and Rz Axis	
	
	if (simulationCount > 0) {
	
		// USAGE_PAGE (Simulation Controls)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;
		
		// LOGICAL_MINIMUM (-32767)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x16;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x80;

		// LOGICAL_MAXIMUM (+32767)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x26;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0xFF;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x7F;

		// REPORT_SIZE (16)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x10;

		// REPORT_COUNT (simulationCount)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
		tempHidReportDescriptor[hidReportDescriptorSize++] = simulationCount;

		// COLLECTION (Physical)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0xA1;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

		if (includeRudder == true) {
			// USAGE (Rudder)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0xBA;
		}

		if (includeThrottle == true) {
			// USAGE (Throttle)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0xBB;
		}

		if (includeAccelerator == true) {
			// USAGE (Accelerator)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0xC4;
		}

		if (includeBrake == true) {
			// USAGE (Brake)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0xC5;
		}

		if (includeSteering == true) {
			// USAGE (Steering)
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
			tempHidReportDescriptor[hidReportDescriptorSize++] = 0xC8;
		}

		// INPUT (Data,Var,Abs)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;
		
		// END_COLLECTION (Physical)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0xc0;
	
	} // Simulation Controls

	//DDC Settings report

	// Usage Page (Vendor-defined)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xFF;
	// Usage (Generic Data)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
	// Logical Minimum (0)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;
	// Logical Maximum (255)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x26;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xFF;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;
	// Report Size (8 bits)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x08;
	// Report Count (4 bytes)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x04;
	// Input (Data, Variable, Absolute)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;

	//Output report

	//Usage Page (undefined)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x06;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xff;
	//Usage (undefined)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
	//Collection (Physical)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xa1;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
	//Report ID 0x68
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x85;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x68;
	//Logical minimum
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;
	//Logical maximum
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x26;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xff;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;
	//Report size
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x08;
	//Report count
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x40;
	//Usage (undefined)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
	//OUTPUT (Data, Var, Abs)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x91;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;
	//End collection (physical)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xC0;


    // END_COLLECTION (Applicatoin)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0xc0;

	// Create a copy of the HID Report Descriptor template that is just the right size
	uint8_t *customHidReportDescriptor = new uint8_t[hidReportDescriptorSize];
	memcpy(customHidReportDescriptor, tempHidReportDescriptor, hidReportDescriptorSize);

	usb_hid.setPollInterval(USB_POLLING_RATE);
	usb_hid.setBootProtocol(HID_ITF_PROTOCOL_NONE);
	usb_hid.enableOutEndpoint(true);
	usb_hid.setReportDescriptor(customHidReportDescriptor, hidReportDescriptorSize);
	
	// Register HID Report Description
	
    // Setup Joystick State
	if (buttonCount > 0) {
		_buttonValuesArraySize = _buttonCount / 8;
		if ((_buttonCount % 8) > 0) {
			_buttonValuesArraySize++;
		}
		_buttonValues = new uint8_t[_buttonValuesArraySize];
	}
	
	// Calculate HID Report Size
	_hidReportSize = _buttonValuesArraySize;
	_hidReportSize += (_hatSwitchCount > 0);
	_hidReportSize += (axisCount * 2);
	_hidReportSize += (simulationCount * 2);
	_hidReportSize += 4; //Adding 4 bytes of extra data
	
	// Initialize Joystick State
	_xAxis = 0;
	_yAxis = 0;
	_zAxis = 0;
	_xAxisRotation = 0;
	_yAxisRotation = 0;
	_zAxisRotation = 0;
	_throttle = 0;
	_rudder = 0;
	_accelerator = 0;
	_brake = 0;
	_steering = 0;
	for (int index = 0; index < JOYSTICK_HATSWITCH_COUNT_MAXIMUM; index++)
	{
		_hatSwitchValues[index] = JOYSTICK_HATSWITCH_RELEASE;
	}
    for (int index = 0; index < _buttonValuesArraySize; index++)
    {
        _buttonValues[index] = 0;
    }
}

void Joystick_::begin(bool initAutoSendState)
{
	_autoSendState = initAutoSendState;
  usb_hid.begin();
  while( !TinyUSBDevice.mounted() ) delay(1);
	sendState();
}

void Joystick_::end()
{
}

void Joystick_::setButton(uint8_t button, uint8_t value)
{
	if (value == 0)
	{
		releaseButton(button);
	}
	else
	{
		pressButton(button);
	}
}
void Joystick_::pressButton(uint8_t button)
{
    if (button >= _buttonCount) return;

    int index = button / 8;
    int bit = button % 8;

	bitSet(_buttonValues[index], bit);
	if (_autoSendState) sendState();
}
void Joystick_::releaseButton(uint8_t button)
{
    if (button >= _buttonCount) return;

    int index = button / 8;
    int bit = button % 8;

    bitClear(_buttonValues[index], bit);
	if (_autoSendState) sendState();
}

void Joystick_::setXAxis(int16_t value)
{
	_xAxis = value;
	if (_autoSendState) sendState();
}
void Joystick_::setYAxis(int16_t value)
{
	_yAxis = value;
	if (_autoSendState) sendState();
}
void Joystick_::setZAxis(int16_t value)
{
	_zAxis = value;
	if (_autoSendState) sendState();
}

void Joystick_::setRxAxis(int16_t value)
{
	_xAxisRotation = value;
	if (_autoSendState) sendState();
}
void Joystick_::setRyAxis(int16_t value)
{
	_yAxisRotation = value;
	if (_autoSendState) sendState();
}
void Joystick_::setRzAxis(int16_t value)
{
	_zAxisRotation = value;
	if (_autoSendState) sendState();
}

void Joystick_::setRudder(int16_t value)
{
	_rudder = value;
	if (_autoSendState) sendState();
}
void Joystick_::setThrottle(int16_t value)
{
	_throttle = value;
	if (_autoSendState) sendState();
}
void Joystick_::setAccelerator(int16_t value)
{
	_accelerator = value;
	if (_autoSendState) sendState();
}
void Joystick_::setBrake(int16_t value)
{
	_brake = value;
	if (_autoSendState) sendState();
}
void Joystick_::setSteering(int16_t value)
{
	_steering = value;
	if (_autoSendState) sendState();
}

void Joystick_::setHatSwitch(int8_t hatSwitchIndex, int16_t value)
{
	if (hatSwitchIndex >= _hatSwitchCount) return;
	
	_hatSwitchValues[hatSwitchIndex] = value;
	if (_autoSendState) sendState();
}

void Joystick_::setSetting(uint8_t slot, uint8_t bits, uint16_t value)
{
    if (slot >= 32 || bits > 16 || bits == 0) {
        return; 
    }

    uint32_t mask = (1 << bits) - 1;  
    uint32_t valueBits = value & mask; 
    uint32_t shiftedMask = mask << slot;      
    uint32_t shiftedValueBits = valueBits << slot;
    DDCsettings &= ~shiftedMask; 
    DDCsettings |= shiftedValueBits;
}

int Joystick_::buildAndSet16BitValue(bool includeValue, int16_t value, int16_t valueMinimum, int16_t valueMaximum, int16_t actualMinimum, int16_t actualMaximum, uint8_t dataLocation[]) 
{
	int16_t convertedValue;
	uint8_t highByte;
	uint8_t lowByte;
	int16_t realMinimum = min(valueMinimum, valueMaximum);
	int16_t realMaximum = max(valueMinimum, valueMaximum);

	if (includeValue == false) return 0;

	if (value < realMinimum) {
		value = realMinimum;
	}
	if (value > realMaximum) {
		value = realMaximum;
	}

	if (valueMinimum > valueMaximum) {
		// Values go from a larger number to a smaller number (e.g. 1024 to 0)
		value = realMaximum - value + realMinimum;
	}

	convertedValue = map(value, realMinimum, realMaximum, actualMinimum, actualMaximum);

	highByte = (uint8_t)(convertedValue >> 8);
	lowByte = (uint8_t)(convertedValue & 0x00FF);
	
	dataLocation[0] = lowByte;
	dataLocation[1] = highByte;
	
	return 2;
}

int Joystick_::buildAndSetAxisValue(bool includeAxis, int16_t axisValue, int16_t axisMinimum, int16_t axisMaximum, uint8_t dataLocation[])
{
	return buildAndSet16BitValue(includeAxis, axisValue, axisMinimum, axisMaximum, JOYSTICK_AXIS_MINIMUM, JOYSTICK_AXIS_MAXIMUM, dataLocation);
}

int Joystick_::buildAndSetSimulationValue(bool includeValue, int16_t value, int16_t valueMinimum, int16_t valueMaximum, uint8_t dataLocation[])
{
	return buildAndSet16BitValue(includeValue, value, valueMinimum, valueMaximum, JOYSTICK_SIMULATOR_MINIMUM, JOYSTICK_SIMULATOR_MAXIMUM, dataLocation);
}

void Joystick_::sendState()
{
	uint8_t data[_hidReportSize];
	int index = 0;
	
	// Load Button State
	for (; index < _buttonValuesArraySize; index++)
	{
		data[index] = _buttonValues[index];		
	}

	// Set Hat Switch Values
	if (_hatSwitchCount > 0) {
		
		// Calculate hat-switch values
		uint8_t convertedHatSwitch[JOYSTICK_HATSWITCH_COUNT_MAXIMUM];
		for (int hatSwitchIndex = 0; hatSwitchIndex < JOYSTICK_HATSWITCH_COUNT_MAXIMUM; hatSwitchIndex++)
		{
			if (_hatSwitchValues[hatSwitchIndex] < 0)
			{
				convertedHatSwitch[hatSwitchIndex] = 8;
			}
			else
			{
				convertedHatSwitch[hatSwitchIndex] = (_hatSwitchValues[hatSwitchIndex] % 360) / 45;
			}			
		}

		// Pack hat-switch states into a single byte
		data[index++] = (convertedHatSwitch[1] << 4) | (0b00001111 & convertedHatSwitch[0]);
	
	} // Hat Switches

	// Set Axis Values
	index += buildAndSetAxisValue(_includeAxisFlags & JOYSTICK_INCLUDE_X_AXIS, _xAxis, _xAxisMinimum, _xAxisMaximum, &(data[index]));
	index += buildAndSetAxisValue(_includeAxisFlags & JOYSTICK_INCLUDE_Y_AXIS, _yAxis, _yAxisMinimum, _yAxisMaximum, &(data[index]));
	index += buildAndSetAxisValue(_includeAxisFlags & JOYSTICK_INCLUDE_Z_AXIS, _zAxis, _zAxisMinimum, _zAxisMaximum, &(data[index]));
	index += buildAndSetAxisValue(_includeAxisFlags & JOYSTICK_INCLUDE_RX_AXIS, _xAxisRotation, _rxAxisMinimum, _rxAxisMaximum, &(data[index]));
	index += buildAndSetAxisValue(_includeAxisFlags & JOYSTICK_INCLUDE_RY_AXIS, _yAxisRotation, _ryAxisMinimum, _ryAxisMaximum, &(data[index]));
	index += buildAndSetAxisValue(_includeAxisFlags & JOYSTICK_INCLUDE_RZ_AXIS, _zAxisRotation, _rzAxisMinimum, _rzAxisMaximum, &(data[index]));
	
	// Set Simulation Values
	index += buildAndSetSimulationValue(_includeSimulatorFlags & JOYSTICK_INCLUDE_RUDDER, _rudder, _rudderMinimum, _rudderMaximum, &(data[index]));
	index += buildAndSetSimulationValue(_includeSimulatorFlags & JOYSTICK_INCLUDE_THROTTLE, _throttle, _throttleMinimum, _throttleMaximum, &(data[index]));
	index += buildAndSetSimulationValue(_includeSimulatorFlags & JOYSTICK_INCLUDE_ACCELERATOR, _accelerator, _acceleratorMinimum, _acceleratorMaximum, &(data[index]));
	index += buildAndSetSimulationValue(_includeSimulatorFlags & JOYSTICK_INCLUDE_BRAKE, _brake, _brakeMinimum, _brakeMaximum, &(data[index]));
	index += buildAndSetSimulationValue(_includeSimulatorFlags & JOYSTICK_INCLUDE_STEERING, _steering, _steeringMinimum, _steeringMaximum, &(data[index]));

	//DDC setting
	uint8_t push = DDCsettings & 0xFF;
	data[index++] = push;        
	DDCsettings >>= 8;
	push = DDCsettings & 0xFF;
	data[index++] = push;        
	DDCsettings >>= 8;
	push = DDCsettings & 0xFF;
	data[index++] = push;        
	DDCsettings >>= 8;
	push = DDCsettings & 0xFF;
	data[index++] = push; 

  while(!usb_hid.ready()){};
  usb_hid.sendReport(JOYSTICK_DEFAULT_REPORT_ID, data, sizeof(data));
}



