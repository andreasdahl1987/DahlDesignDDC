//-------------------------
// ------- DEFINES & Vars
//-------------------------
#include "src/FastLED/FastLED.h"

#if defined(ENABLE_UPLOAD_PROTECTION) && ENABLE_UPLOAD_PROTECTION == 1 
#include <avr/wdt.h>
#endif

#define PROTOCOLVERSION "SIMHUB_1.0"

#if(STRIP1_RGBLEDCOUNT > 0)
CRGB led_strip1[STRIP1_RGBLEDCOUNT];
#endif

#if(STRIP2_RGBLEDCOUNT > 0)
CRGB led_strip2[STRIP2_RGBLEDCOUNT];
#endif

#if(STRIP3_RGBLEDCOUNT > 0)
CRGB led_strip3[STRIP3_RGBLEDCOUNT];
#endif

#if(STRIP4_RGBLEDCOUNT > 0)
CRGB led_strip4[STRIP4_RGBLEDCOUNT];
#endif

int messageend = 0;
String command = "";
bool uploadUnlocked = 0;

/// <summary>
/// Wait for data to be available and reads one byte.
/// </summary>
/// <returns></returns>
int WaitAndReadOneByte() {
	while (!Serial.available()) {}
	return Serial.read();
}

/// <summary>
/// Read rgb strip data
/// </summary>
/// <param name="stripData">Pointer to the strip RGB data.</param>
/// <param name="ledcount">How many leds does the strip has.</param>
/// <param name="rightToLeft">Should the strip be fed from right to left.</param>
void readStrip(CRGB* stripData, int ledcount, bool rightToLeft) {
	byte r, g, b;
	for (int i = 0; i < ledcount; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();
		if (rightToLeft) {
			stripData[ledcount - 1 - i].setRGB(r, g, b);
		}
		else {
			stripData[i].setRGB(r, g, b);
		}
	}
}

/// <summary>
/// Pretects the pro micro from anwanted upload, it can be unlocked by a physical reset, or the "unloc" command.
/// </summary>
void protectUpload() {
#if defined(ENABLE_UPLOAD_PROTECTION) && ENABLE_UPLOAD_PROTECTION == 1 
	if (ENABLE_UPLOAD_PROTECTION && !uploadUnlocked) {
		if (millis() > UPLOAD_AVAILABLE_DELAY) {
			wdt_disable();
			wdt_reset();
		}
	}
#endif
}

/// <summary>
/// Unlock upload protection.
/// </summary>
void unlockUpload() {
	uploadUnlocked = true;
	Serial.println("Upload unlocked");
}

/// <summary>
/// Sends leds count to the serial port.
/// </summary>
void getLedsCount() {
	Serial.println(STRIP1_RGBLEDCOUNT + STRIP2_RGBLEDCOUNT + STRIP3_RGBLEDCOUNT + STRIP4_RGBLEDCOUNT);
}

/// <summary>
/// Sends the protocol version.
/// </summary>
void getProtocolVersion() {
	Serial.println(PROTOCOLVERSION);
}

/// <summary>
/// Read leds data from serial port.
/// </summary>
void readLeds() {

#if(STRIP1_RGBLEDCOUNT > 0)
	readStrip(led_strip1, STRIP1_RGBLEDCOUNT, STRIP1_RIGHTTOLEFT);
#endif

#if(STRIP2_RGBLEDCOUNT > 0)
	readStrip(led_strip2, STRIP2_RGBLEDCOUNT, STRIP2_RIGHTTOLEFT);
#endif

#if(STRIP3_RGBLEDCOUNT > 0)
	readStrip(led_strip3, STRIP3_RGBLEDCOUNT, STRIP3_RIGHTTOLEFT);
#endif

#if(STRIP4_RGBLEDCOUNT > 0)
	readStrip(led_strip4, STRIP4_RGBLEDCOUNT, STRIP4_RIGHTTOLEFT);
#endif

	// 3 bytes end of message, it must be (0xFF)(0xFE)(0xFD) to be taken into account, it's a super simple way to be sure we reached the correct end.
	bool valid = true;
	for (int i = 0; i < 3; i++) {
		valid = valid && (WaitAndReadOneByte() == 0xFF - i);
	}

	if (valid) {
		FastLED.show();
	}
}

/// <summary>
/// Setup for the leds.w
/// </summary>
void setupLeds() {
#if(STRIP1_RGBLEDCOUNT > 0)
	FastLED.addLeds<STRIP1_TYPE, STRIP1_DATAPIN>(led_strip1, STRIP1_RGBLEDCOUNT);
#endif

#if(STRIP2_RGBLEDCOUNT > 0)
	FastLED.addLeds<STRIP2_TYPE, STRIP2_DATAPIN>(led_strip2, STRIP2_RGBLEDCOUNT);
#endif

#if(STRIP3_RGBLEDCOUNT > 0)
	FastLED.addLeds<STRIP3_TYPE, STRIP3_DATAPIN>(led_strip3, STRIP3_RGBLEDCOUNT);
#endif

#if(STRIP4_RGBLEDCOUNT > 0)
	FastLED.addLeds<STRIP4_TYPE, STRIP4_DATAPIN>(led_strip4, STRIP4_RGBLEDCOUNT);
#endif

	FastLED.show();
}

/// <summary>
/// Read commands from serial port.
/// </summary>
void processCommands() {
	// Protects unwanted upload.
	protectUpload();

	// Read data
	if (Serial.available()) {
		char c = (char)Serial.read();

		if (messageend < 6) {
			if (c == (char)0xFF) {
				messageend++;
			}
			else {
				messageend = 0;
			}
		}

		if (messageend >= 3 && c != (char)(0xff)) {
			command += c;

			while (command.length() < 5) {
				c = WaitAndReadOneByte();
				command += c;
			}

			// Get protocol version
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)proto
			if (command == "proto") {
				getProtocolVersion();
			}

			// Get leds count
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)ledsc
			if (command == "ledsc") {
				getLedsCount();
			}

			// Send leds data (in binary) terminated by (0xFF)(0xFE)(0xFD)
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)sleds(RL1)(GL1)(BL1)(RL2)(GL2)(BL2) .... (0xFF)(0xFE)(0xFD)
			else if (command == "sleds") {
				readLeds();
			}

			// Unlock upload
			// (0xFF)(0xFF)(0xFF)(0xFF)(0xFF)(0xFF)unloc
			else if (command == "unloc") {
				unlockUpload();
			}

			command = "";
			messageend = 0;
		}
	}
}