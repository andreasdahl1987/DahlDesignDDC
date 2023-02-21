//----------------------------------------------------------------------------
//-----------------------------LED COLOR AND TYPES----------------------------
//----------------------------------------------------------------------------
//   NEO_KHZ800  800 KHz bitstream (WS2812 LEDs and similar)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ---------------------------- STRIP #1 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED1COUNT 0
#define LED1PIN 2  
#define LED1TYPE NEO_GRB + NEO_KHZ800
#define LED1REVERSE 0
#define LED1PRIVATE 0

//----------------------------------------------------------------------------
// ---------------------------- STRIP #2 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED2COUNT 0
#define LED2PIN 2
#define LED2TYPE NEO_GRB + NEO_KHZ800
#define LED2REVERSE 0
#define LED2PRIVATE 0

//----------------------------------------------------------------------------
// ---------------------------- STRIP #3 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED3COUNT 0
#define LED3PIN 2
#define LED3TYPE NEO_GRB + NEO_KHZ800
#define LED3REVERSE 0
#define LED3PRIVATE 0

//----------------------------------------------------------------------------
// ---------------------------- STRIP #4 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED4COUNT 0
#define LED4PIN 2
#define LED4TYPE NEO_GRB + NEO_KHZ800
#define LED4REVERSE 0
#define LED4PRIVATE 0

//----------------------------------------------------------------------------

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
    #include <DDCGENCORE.h>
#endif
