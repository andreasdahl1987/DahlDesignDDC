# RGB LED

LEDs can be controlled by the firmware itself, by SimHub or by both.&#x20;

* Firmware control is ideal of features such as backlit buttons, indication of firmware controlled actions - such as setting bite point, modifier button, quick switches, magic toggle, etc. Most of these things can also be achieved with SimHub, but that would make your controller more dependent on software applications that it needs to be.&#x20;
* SimHub control is ideal for telemetry-dependent LED animations, such as rev lights, flag lights, indication of pit limiter, TC, ABS and much more.

LED setup starts in 14\_LEDsetup, where you describe your wiring the firmware.&#x20;

## 14\_LEDsetup.ino

```
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
#define LED1PIN 25  
#define LED1TYPE NEO_GRB + NEO_KHZ800
#define LED1REVERSE 0
#define LED1PRIVATE 0

//----------------------------------------------------------------------------
// ---------------------------- STRIP #2 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED2COUNT 0
#define LED2PIN 25
#define LED2TYPE NEO_GRB + NEO_KHZ800
#define LED2REVERSE 0
#define LED2PRIVATE 0

//----------------------------------------------------------------------------
// ---------------------------- STRIP #3 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED3COUNT 0
#define LED3PIN 25
#define LED3TYPE NEO_GRB + NEO_KHZ800
#define LED3REVERSE 0
#define LED3PRIVATE 0

//----------------------------------------------------------------------------
// ---------------------------- STRIP #4 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED4COUNT 0
#define LED4PIN 25
#define LED4TYPE NEO_GRB + NEO_KHZ800
#define LED4REVERSE 0
#define LED4PRIVATE 0

//----------------------------------------------------------------------------

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
    #include <DDCGENCORE.h>
#endif
```

* Four things to fill in for each LED strip:
  * COUNT -> The number of LEDs in this chain
  * PIN -> The digital pin you connect the chain to
  * TYPE -> The type of LED you're using, see the first lines for guide
  * REVERSE -> Will reverse the numbering of this LED strip. The LED that is connected to the microcontroller is by default LED number 0. In a 20 LED long chain, the last LED will then be number 19. If you reverse the chain, by typing 1 instead of 0, the last LED in the chain will now be number 0, the first will be number 19. [.](https://github.com/FastLED/FastLED/wiki/Overview#chipsets)
  * PRIVATE -> Set to 1 to make chain firmware exclusive. Hides this chain from SimHub.

Fill in for as many LED strips as you're using. When COUNT is set to 0, that strip is not active.&#x20;

## LED numbering

* In SimHub, all the chains will be put together to a long chain in terms of numbering. So with three chains of 8 + 10 + 8 LEDs, and SimHub will also do a +1 to the LED numbers to make it start with 1. So the first LED in your project will be the first LED on the first chain. That will be LED number 1. The first LED in the second chain will be number 9. And the last LED in the last chain is the full 8 + 10 + 8 = number 26.&#x20;
  * If a chain is set to PRIVATE, SimHub will simply skip it. In the example above, if chain 2 is private, there will be only 8 + 8 LEDs for SimHub to handle, with chain 3  starting on 9.&#x20;
* In the firmware, we'll refer to one chain at the time, and chains start with 0. So In the case above (3 chains of 8 + 10 + 8 LEDs), the first LED of any chain is number 0. The last LED in the second chain is number 9, you get the idea. To send info to the right chain we'll also be including the chain numbers in our code.&#x20;
* When working with holes in the mask, all LED chains are summized. So if you have 4 chains of 10, these are LEDs 0 to 39.&#x20;
