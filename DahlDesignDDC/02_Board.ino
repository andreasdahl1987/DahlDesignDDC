/*
 * Chose your board. Default is to 32U4-based boards. 
 */

//------------------------
//---------BOARD----------
//------------------------

#define BOARDTYPE 0

// 0 -> Atmel 32U4 based boards. (Leonardo, Pro Micro, Feather, Teensy 2.0, etc) SAM3X based boards. (Due)

// 1 -> SAMD21 or SAMD51 based boards. (Arduino Zero and many more)

// 2 -> RP2040 based boards. (Raspberry Pi Pico, Pico W, Pro Micro RP2040, and many more)



#if (BOARDTYPE == 0)
  #include <DDC32U4.h>
#elif (BOARDTYPE == 1)
  #include <DDCSAMD.h>
#elif (BOARDTYPE == 2)
  #include <DDCPI.h>
#endif
