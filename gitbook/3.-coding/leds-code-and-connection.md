# LEDs code and connection

You don't need to do anything here if you're not planning to use LEDs with DDC.&#x20;

## 14\_LEDsetup.ino

```
//-------------------------
// ------- LED STRIP #1 Settings
//-------------------------

#define STRIP1_RGBLEDCOUNT 0
#define STRIP1_DATAPIN 2
#define STRIP1_RIGHTTOLEFT 0
#define STRIP1_TYPE NEOPIXEL

//-------------------------
// ------- STRIP #2 Settings
//-------------------------
#define STRIP2_RGBLEDCOUNT 0
#define STRIP2_DATAPIN 2 
#define STRIP2_RIGHTTOLEFT 0
#define STRIP2_TYPE NEOPIXEL

//-------------------------
// ------- STRIP #3 Settings
//-------------------------
#define STRIP3_RGBLEDCOUNT 0
#define STRIP3_DATAPIN 2
#define STRIP3_RIGHTTOLEFT 0
#define STRIP3_TYPE NEOPIXEL

//-------------------------
// ------- STRIP #4 Settings
//-------------------------

#define STRIP4_RGBLEDCOUNT 0
#define STRIP4_DATAPIN 2
#define STRIP4_RIGHTTOLEFT 0
#define STRIP4_TYPE NEOPIXEL

// Main simhub leds core code
#include "ledscore.h"
```

* Four things to fill in for each LED strip:
  * RGBLEDCOUNT -> The number of LEDs in this chain
  * DATAPIN -> The pin you connect the chain to
  * RIGHTTOLEFT -> The direction you want this chain to be read, can be reversed (left to right). 0 is right to left, 1 is left to right.
  * TYPE -> The LED category. "NEOPIXEL" for WS2812, read more [here.](https://github.com/FastLED/FastLED/wiki/Overview#chipsets)

Fill in for as many LED strips as you're using. When RGBLEDCOUNT is set to 0, that strip is not active.&#x20;

Next you'll need to make a [custom board core. ](../4.-advanced-features/naming-the-controller.md)

When you've [uploaded](upload.md) the code, you can connect to SimHub:

* Go to devices and add a new device.

<figure><img src="../.gitbook/assets/image (15).png" alt=""><figcaption></figcaption></figure>

* Select "Create oem leds test device"

<figure><img src="../.gitbook/assets/image (14).png" alt=""><figcaption></figcaption></figure>

* Go to OEM configuration and type in the numbers you used in your board core.&#x20;

<figure><img src="../.gitbook/assets/image (12).png" alt=""><figcaption></figcaption></figure>

* Reboot your controller for SimHub to find it, press "Edit profile" to get to the RGB editor. You're all set!

<figure><img src="../.gitbook/assets/image (4).png" alt=""><figcaption></figcaption></figure>
