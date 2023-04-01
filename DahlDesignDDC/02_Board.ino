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


//PORT EXPANDER PCA9555
#define USING_PCA9555 0
#define PCA9555_I2C_NUMBER 0
uint8_t PCA9555interruptPins [] = {99};

//16-BIT ADC ADS1115
#define USING_ADS1115 0
#define ADS1115_I2C_NUMBER 0
#define ADS1115_CHIPS 0

//VARIABLES
bool wire1Init = false;
bool wire0Init = false;

#if(USING_CB1 == 1)
  bool ADS1115sentReq[2] = {false, false};
  uint16_t ADS1115value[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t ADS1115channelCounter[2] = {0,0};  
#elif(ADS1115_CHIPS > 0)
  bool ADS1115sentReq[ADS1115_CHIPS];
  uint16_t ADS1115value[4*ADS1115_CHIPS];
  uint8_t ADS1115channelCounter[ADS1115_CHIPS];
#endif

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

#if (USING_CB1 == 1 || USING_PCA9555 == 1 || USING_ADS1115 == 1)
  #include <Wire.h>
#endif
