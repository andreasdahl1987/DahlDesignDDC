/*
 * Chose your board. Default is to 32U4-based boards. 
 */

//----------------------------
//-----------BOARD------------
//----------------------------

#define BOARDTYPE 2

// 0 -> Atmel 32U4 based boards. (Leonardo, Pro Micro, Feather, Teensy 2.0, etc) SAM3X based boards. (Due)

// 1 -> SAMD21 or SAMD51 based boards. (Arduino Zero and many more)

// 2 -> RP2040 based boards. (Raspberry Pi Pico, Pico W, Pro Micro RP2040, and many more)


//------------------------------
//---------DAHL DESIGN----------
//------------------------------


#define USING_CB1 1


//------------------------------
//---------I2C DEVICES----------
//------------------------------
#define SDA0PIN 0
#define SCL0PIN 1
#define SDA1PIN 2
#define SCL1PIN 3


#define USING_PCA9555 1
#define PCA9555_I2C_NUMBER 0
uint8_t PCA9555interruptPins [] = {8, 16};




bool wire1Init = false;
bool wire0Init = false;




//------------------------------
//---------LIBRARIES------------
//------------------------------

#if (BOARDTYPE == 0)
  #include <DDC32U4.h>
#elif (BOARDTYPE == 1)
  #include <DDCSAMD.h>
#elif (BOARDTYPE == 2)
  #include <DDCPI.h>
#endif

#if (USING_CB1 == 1 || USING_PCA9555 == 1)
  #include <Wire.h>
#endif
