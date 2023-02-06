//-------------------------
// ------- STRIP #1 Settings
//-------------------------

#define STRIP1_RGBLEDCOUNT 50 // LED count on the strip. 0 to disable
#define STRIP1_DATAPIN 2 // Pin number

//-------------------------
// ------- STRIP #2 Settings
//-------------------------
#define STRIP2_RGBLEDCOUNT 0
#define STRIP2_DATAPIN 2 

//-------------------------
// ------- STRIP #3 Settings
//-------------------------
#define STRIP3_RGBLEDCOUNT 0
#define STRIP3_DATAPIN 2

//-------------------------
// ------- STRIP #4 Settings
//-------------------------
#define STRIP4_RGBLEDCOUNT 0
#define STRIP4_DATAPIN 2


#if (STRIP1_RGBLEDCOUNT + STRIP2_RGBLEDCOUNT + STRIP3_RGBLEDCOUNT + STRIP4_RGBLEDCOUNT > 0)
    #include <DDCGENCORE.h>
#endif
