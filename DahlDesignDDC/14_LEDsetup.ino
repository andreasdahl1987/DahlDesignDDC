//-------------------------
// ------- LED STRIP #1 Settings
//-------------------------

#define STRIP1_RGBLEDCOUNT 0 // LED count on the strip. 0 to disable
#define STRIP1_DATAPIN 2 // Pin number
#define STRIP1_TYPE NEOPIXEL // Strip type (NEOPIXEL = WS2812B compatible, PL9823 = PL9823)

//-------------------------
// ------- STRIP #2 Settings
//-------------------------
#define STRIP2_RGBLEDCOUNT 0
#define STRIP2_DATAPIN 2 
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
