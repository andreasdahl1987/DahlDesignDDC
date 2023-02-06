//-------------------------
// ------- DEFINES & Vars
//-------------------------
#include <DDCPILED.h>

#define PROTOCOLVERSION "SIMHUB_1.0"

#if(STRIP1_RGBLEDCOUNT > 0)
Adafruit_NeoPixel pixels1(STRIP1_RGBLEDCOUNT, STRIP1_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

#if(STRIP2_RGBLEDCOUNT > 0)
Adafruit_NeoPixel pixels2(STRIP2_RGBLEDCOUNT, STRIP2_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

#if(STRIP3_RGBLEDCOUNT > 0)
Adafruit_NeoPixel pixels3(STRIP3_RGBLEDCOUNT, STRIP3_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

#if(STRIP4_RGBLEDCOUNT > 0)
Adafruit_NeoPixel pixels4(STRIP4_RGBLEDCOUNT, STRIP4_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

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
	#if(STRIP1_RGBLEDCOUNT > 0)
    pixels1.begin(); 
	#endif
	#if(STRIP2_RGBLEDCOUNT > 0)
    pixels2.begin(); 
	#endif
	#if(STRIP3_RGBLEDCOUNT > 0)
    pixels13.begin(); 
	#endif
	#if(STRIP4_RGBLEDCOUNT > 0)
    pixels14.begin(); 
	#endif
}


void readStrip() {
	uint8_t r, g, b;

	LEDPre();

	#if(STRIP1_RGBLEDCOUNT > 0)
	for (uint16_t i = 0; i < STRIP1_RGBLEDCOUNT; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
	}
	#endif

	#if(STRIP2_RGBLEDCOUNT > 0)
	for (uint16_t i = 0; i < STRIP2_RGBLEDCOUNT; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
	}
	#endif

	#if(STRIP3_RGBLEDCOUNT > 0)
	for (uint16_t i = 0; i < STRIP3_RGBLEDCOUNT; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

    pixels3.setPixelColor(i, pixels3.Color(r, g, b));
	}
	#endif

	#if(STRIP4_RGBLEDCOUNT > 0)
	for (uint16_t i = 0; i < STRIP4_RGBLEDCOUNT; i++) {
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

    pixels4.setPixelColor(i, pixels4.Color(r, g, b));
	}
	#endif

	LEDPost();
}


void readLeds() {

	readStrip();

// 3 bytes end of message, it must be (0xFF)(0xFE)(0xFD) to be taken into account, it's a super simple way to be sure we reached the correct end.
	bool valid = true;
	for (int i = 0; i < 3; i++) {
		valid = valid && (WaitAndReadOneByte() == 0xFF - i);
	}
	if (valid) {
		#if(STRIP1_RGBLEDCOUNT>0)
		pixels1.show();
		#endif

		#if(STRIP2_RGBLEDCOUNT>0)
		pixels2.show();
		#endif

		#if(STRIP3_RGBLEDCOUNT>0)
		pixels3.show();
		#endif

		#if(STRIP4_RGBLEDCOUNT>0)
		pixels4.show();
		#endif
	}
}

/// <summary>
/// Sends leds count to the serial port.
/// </summary>
void getLedsCount() {
	Serial.println(STRIP1_RGBLEDCOUNT+STRIP2_RGBLEDCOUNT+STRIP3_RGBLEDCOUNT+STRIP4_RGBLEDCOUNT);
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