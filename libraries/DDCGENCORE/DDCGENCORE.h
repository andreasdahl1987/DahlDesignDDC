//-----------------------------------
// ------- DEFINES AND VARIABLES-----
//-----------------------------------
#include <DDCLEDGEN.h>

#define PROTOCOLVERSION "SIMHUB_1.0"

#if(LED1COUNT > 0)
Adafruit_NeoPixel LED1(LED1COUNT, LED1PIN, LED1TYPE);
#endif

#if(LED2COUNT > 0)
Adafruit_NeoPixel LED2(LED2COUNT, LED2PIN, LED2TYPE);
#endif

#if(LED3COUNT > 0)
Adafruit_NeoPixel LED3(LED3COUNT, LED3PIN, LED3TYPE);
#endif

#if(LED4COUNT > 0)
Adafruit_NeoPixel LED4(LED4COUNT, LED4PIN, LED4TYPE);
#endif

int messageend = 0;
String command = "";


int WaitAndReadOneByte() 
{
	while (!Serial.available()) {}
	return Serial.read();
}

/// <summary>

void setupLeds()
{
	#if(LED1COUNT > 0)
    LED1.begin(); 
	stripCount++;
	#endif
	#if(LED2COUNT > 0)
    LED2.begin(); 
	stripCount++;
	#endif
	#if(LED3COUNT > 0)
    LED3.begin(); 
	stripCount++;
	#endif
	#if(LED4COUNT > 0)
    LED4.begin(); 
	stripCount++;
	#endif
}


void readStrip() 
{
	uint8_t r, g, b;

	#if(LED1COUNT > 0 && LED1PRIVATE == 0)
	for (uint16_t i = 0; i < LED1COUNT; i++) 
	{
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

		if (LED1REVERSE == 1)
		{
			#if (ECOLED == 0)
			SH_R[LED1COUNT - 1 - i] = r;
			SH_G[LED1COUNT - 1 - i] = g;
			SH_B[LED1COUNT - 1 - i] = b;
			#else
			LED1.setPixelColor(LED1COUNT - 1 - i, r, g, b);
			#endif
		}
		else 
		{
			#if (ECOLED == 0)
			SH_R[i] = r;
			SH_G[i] = g;
			SH_B[i] = b;
			#else
			LED1.setPixelColor(i, r, g, b);
			#endif
		}
	}
	#endif

	#if(LED2COUNT > 0  && LED2PRIVATE == 0)
	for (uint16_t i = 0; i < LED2COUNT; i++) 
	{
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

		if (LED2REVERSE == 1)
		{	
			#if (ECOLED == 0)
			SH_R[LED1COUNT + LED2COUNT - 1 - i] = r;
			SH_G[LED1COUNT + LED2COUNT - 1 - i] = g;
			SH_B[LED1COUNT + LED2COUNT - 1 - i] = b;
			#else
			LED2.setPixelColor(LED2COUNT - 1 - i, r, g, b);
			#endif
			
		}
		else 
		{
			#if (ECOLED == 0)
			SH_R[LED1COUNT + i] = r;
			SH_G[LED1COUNT + i] = g;
			SH_B[LED1COUNT + i] = b;
			#else
			LED2.setPixelColor(i, r, g, b);
			#endif
		}
	}
	#endif

	#if(LED3COUNT > 0  && LED3PRIVATE == 0)
	for (uint16_t i = 0; i < LED3COUNT; i++) 
	{
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

		if (LED3REVERSE == 1)
		{
			#if(ECOLED == 0)
			SH_R[LED1COUNT + LED2COUNT + LED3COUNT - 1 - i] = r;
			SH_G[LED1COUNT + LED2COUNT + LED3COUNT - 1 - i] = g;
			SH_B[LED1COUNT + LED2COUNT + LED3COUNT - 1 - i] = b;
			#else
			LED3.setPixelColor(LED3COUNT - 1 - i, r, g, b);
			#endif
		}
		else 
		{
			#if(ECOLED == 0)
			SH_R[LED1COUNT + LED2COUNT + i] = r;
			SH_G[LED1COUNT + LED2COUNT + i] = g;
			SH_B[LED1COUNT + LED2COUNT + i] = b;
			#else
			LED3.setPixelColor(i, r, g, b);
			#endif
		}
	}
	#endif

	#if(LED4COUNT > 0 && LED4PRIVATE == 0)
	for (uint16_t i = 0; i < LED4COUNT; i++) 
	{
		r = WaitAndReadOneByte();
		g = WaitAndReadOneByte();
		b = WaitAndReadOneByte();

		if (LED4REVERSE == 1)
		{
			#if(ECOLED == 0)
			SH_R[LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT - 1 - i] = r;
			SH_G[LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT - 1 - i] = g;
			SH_B[LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT - 1 - i] = b;
			#else
			LED4.setPixelColor(LED4COUNT - 1 - i, r, g, b);
			#endif
		}
		else 
		{
			#if(ECOLED == 0)
			SH_R[LED1COUNT + LED2COUNT + LED3COUNT + i] = r;
			SH_G[LED1COUNT + LED2COUNT + LED3COUNT + i] = g;
			SH_B[LED1COUNT + LED2COUNT + LED3COUNT + i] = b;
			#else
			LED4.setPixelColor(i, r, g, b);
			#endif
		}
	}
	#endif

}


void readLeds() {

	readStrip();

// 3 bytes end of message, it must be (0xFF)(0xFE)(0xFD) to be taken into account, it's a super simple way to be sure we reached the correct end.
	bool valid = true;
	for (int i = 0; i < 3; i++) {
		valid = valid && (WaitAndReadOneByte() == 0xFF - i);
	
	}
	if (valid) 
	{
		#if(ECOLED == 0)
		simhubActive = true;
		for(int i = 0; i < LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT; i++ )
		{
			SH_R_Valid[i] = SH_R[i];
			SH_G_Valid[i] = SH_G[i];
			SH_B_Valid[i] = SH_B[i];
		}
		#else
		ecoTrig = true;
		LEDTop();
		#endif
	}
}

void getLedsCount() 
{
	uint8_t ledTotal = LED1COUNT+LED2COUNT+LED3COUNT+LED4COUNT;
	#if (LED1PRIVATE == 1)
		ledTotal = ledTotal - LED1COUNT;
	#endif
		#if (LED2PRIVATE == 1)
		ledTotal = ledTotal - LED2COUNT;
	#endif
		#if (LED3PRIVATE == 1)
		ledTotal = ledTotal - LED3COUNT;
	#endif
		#if (LED4PRIVATE == 1)
		ledTotal = ledTotal - LED4COUNT;
	#endif


	Serial.println(ledTotal);
}


void getProtocolVersion() 
{
	Serial.println(PROTOCOLVERSION);
}


void processCommands() 
{

	// Read data
	if (Serial.available()) 
	{
		simhubDropTimer = globalClock;
		simhubCheckIn = true;
		
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
		/*
		#if (BOARDTYPE == 2)
			#if(USING_CB1 == 1)
			delayMicroseconds(100); //Stability between cores on CB1.
			#else
			delayMicroseconds(500); //Stability between cores on regular RP2040 board.
			#endif
		#endif
		*/

	}
}
