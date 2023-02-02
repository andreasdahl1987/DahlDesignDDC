//-------------------------
// ------- DEFINES & Vars
//-------------------------
#include <DDCPILED.h>

#define PROTOCOLVERSION "SIMHUB_1.0"


Adafruit_NeoPixel pixels(STRIP1_RGBLEDCOUNT, STRIP1_DATAPIN, NEO_GRB + NEO_KHZ800);

int messageend = 0;
String command = "";

/// <summary>
/// Wait for data to be available and reads one byte.
/// </summary>
/// <returns></returns>
int WaitAndReadOneByte() {
	while (!Serial.available()) {}
	return Serial.read();
}

/// <summary>

void setupLeds(){
    pixels.begin(); 
}


void readStrip() {
	uint8_t r, g, b;
	for (uint16_t i = 0; i < STRIP1_RGBLEDCOUNT; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

    pixels.setPixelColor(i, pixels.Color(r, g, b));
	}
}


void readLeds() {

	readStrip();

// 3 bytes end of message, it must be (0xFF)(0xFE)(0xFD) to be taken into account, it's a super simple way to be sure we reached the correct end.
	bool valid = true;
	for (int i = 0; i < 3; i++) {
		valid = valid && (WaitAndReadOneByte() == 0xFF - i);
	}
	if (valid) {
		pixels.show();
	}
}

/// <summary>
/// Sends leds count to the serial port.
/// </summary>
void getLedsCount() {
	Serial.println(STRIP1_RGBLEDCOUNT);
}

/// <summary>
/// Sends the protocol version.
/// </summary>
void getProtocolVersion() {
	Serial.println(PROTOCOLVERSION);
}


/// <summary>
/// Read commands from serial port.
/// </summary>
void processCommands() {

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

			command = "";
			messageend = 0;
		}
	}
}