//-------------------------
// ------- LED STRIP #1 Settings
//-------------------------

// How many leds on this strip? Set to 0 to disable.
#define STRIP1_RGBLEDCOUNT 12
// Data pin
#define STRIP1_DATAPIN 27
// Strip type (NEOPIXEL = WS2812B compatible, PL9823 = PL9823)
#define STRIP1_TYPE NEOPIXEL

//-------------------------
// ------- STRIP #2 Settings
//-------------------------
#define STRIP2_RGBLEDCOUNT 8
#define STRIP2_DATAPIN 28 
#define STRIP2_TYPE NEOPIXEL

//-------------------------
// ------- STRIP #3 Settings
//-------------------------
#define STRIP3_RGBLEDCOUNT 0
#define STRIP3_DATAPIN 2
#define STRIP3_TYPE NEOPIXEL

//-------------------------
// ------- STRIP #4 Settings
//-------------------------
#define STRIP4_RGBLEDCOUNT 0
#define STRIP4_DATAPIN 2
#define STRIP4_TYPE NEOPIXEL



#if (STRIP1_RGBLEDCOUNT + STRIP2_RGBLEDCOUNT + STRIP3_RGBLEDCOUNT + STRIP4_RGBLEDCOUNT > 0)
    #include <DDCGENCORE.h>
#endif
