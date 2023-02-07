//-------------------------
// ------- STRIP #1 Setup
//-------------------------

#define LED1COUNT 50 // LED count on the strip. 0 to disable
#define LED1PIN 9 // Pin number
#define LED1INTERNAL 1 // This LED strip has firmware LED calls -> 1. Else 0. 

//-------------------------
// ------- STRIP #2 Setup
//-------------------------
#define LED2COUNT 0
#define LED2PIN 2 

//-------------------------
// ------- STRIP #3 Setup
//-------------------------
#define LED3COUNT 0
#define LED3PIN 2

//-------------------------
// ------- STRIP #4 Setup
//-------------------------
#define LED4COUNT 0
#define LED4PIN 2


#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
    #include <DDCGENCORE.h>
#endif
