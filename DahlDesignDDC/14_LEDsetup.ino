
//---------------------------
// ------- General Setup ----
//---------------------------

bool continousUpdate = true;

//----------------------------
// ------- STRIP #1 Setup ----
//----------------------------

#define LED1COUNT 36 // LED count on the strip. 0 to disable
#define LED1PIN A3 // Pin number

//----------------------------
// ------- STRIP #2 Setup ----
//----------------------------
#define LED2COUNT 0
#define LED2PIN 2
#define LED2INTERNAL 0

//----------------------------
// ------- STRIP #3 Setup ----
//----------------------------
#define LED3COUNT 0
#define LED3PIN 2
#define LED3INTERNAL 0

//----------------------------
// ------- STRIP #4 Setup ----
//----------------------------
#define LED4COUNT 0
#define LED4PIN 2
#define LED4INTERNAL 0

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
    #include <DDCGENCORE.h>
#endif
