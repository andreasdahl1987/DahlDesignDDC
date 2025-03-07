/*
 * Chose your board. Defaults to 32U4-based boards.
 */

//------------------------------
//-----------BOARD MCU----------
//------------------------------

#define BOARDTYPE 2

// 0 -> Atmel 32U4 based boards. (Leonardo, Pro Micro, Feather, Teensy 2.0, etc) SAM3X based boards. (Due)

// 1 -> SAMD21 or SAMD51 based boards. (Arduino Zero and many more)

// 2 -> RP2040 based boards. (Dahl Design CB1, Raspberry Pi Pico, Pico W, Pro Micro RP2040, and many more)

//------------------------------
//-----------EEPROM-------------
//------------------------------

#define RESET_EEPROM 0
#define USING_RP2040EEPROM 0
#define USING_32U4EEPROM 0

//------------------------------
//-------PERFORMANCE------------
//------------------------------

#define ECOLED 0

//------------------------------
//---RP2040 ADC OVERSAMPLING----
//------------------------------

#define ENABLE_OVERSAMPLING 0

//------------------------------
//-----------MOUSE--------------
//------------------------------

#define ENABLE_MOUSE 1


//------------------------------
//-------DAHL DESIGN BOARDS-----
//------------------------------

//Enable board
#define USING_CB1 1
#define USING_CB2 0

//------------------------------
//---------CB1 SETTINGS---------
//------------------------------

//ADC setup
#define CB1_ADC1 1
#define CB1_ADC1_CHANNELS 4
#define CB1_ADC1_RATE 7
#define CB1_ADC1_GAIN 1

#define CB1_ADC2 1
#define CB1_ADC2_CHANNELS 4
#define CB1_ADC2_RATE 7
#define CB1_ADC2_GAIN 1

//Port expander setup
#define CB1_PE1 1
#define CB1_PE2 1
#define CB1_PE1_OUTPUT 0
#define CB1_PE2_OUTPUT 0

//ROW5 and ROW6
#define ROW5_ACTIVE 1
#define ROW6_ACTIVE 1

//ROW6 PWM
#define ROW6_PWMCOUNT 0

//ROW7
#define GROUND_CALIBRATION 8

//ROW8 setup
#define DISABLE_ALERT_PINS 0  //Gives access to COL2 and COL3. Disables ALERT pins for the ADCs, making them heavier to run.
#define DISABLE_ANALOG 0      //Gives access to COL4 - COL 7 by using (and disabling analog function of) ADC9 - ADC12 pins.
#define DISABLE_LED_PIN 0     //Gives access to COL8, use the dedicated 8-8 pin. The LED pin will no longer work.

//------------------------------
//---------PWM CONTROL----------
//------------------------------

#define PWMENABLED 0

#if (ROW6_PWMCOUNT > 0)
  int8_t PWMChannelPins [ROW6_PWMCOUNT];
#elif (PWMENABLED == 1)
  int8_t PWMChannelPins [] = {99};
#endif

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
#define PCA9555_OUTPUT 0

#if (PCA9555_OUTPUT== 1)
uint8_t PCA9555outputAddress [] = {0x20};

const uint8_t PCA9555outputCount = sizeof(PCA9555outputAddress) / sizeof(PCA9555outputAddress[0]);
#elif (USING_CB1 == 1 && (CB1_PE1_OUTPUT == 1 || CB1_PE2_OUTPUT == 1))
  #if (CB1_PE1_OUTPUT == 1 && CB1_PE2_OUTPUT == 1)
  uint8_t PCA9555outputAddress [] = {0x21, 0x20};
  const uint8_t PCA9555outputCount = 2;
  #elif (CB1_PE1_OUTPUT == 1)
   uint8_t PCA9555outputAddress [] = {0x21};
  const uint8_t PCA9555outputCount = 1;
  #elif (CB1_PE2_OUTPUT == 1)
  uint8_t PCA9555outputAddress [] = {0x20};
  const uint8_t PCA9555outputCount = 1;
  #endif
#endif

//16-BIT ADC ADS1115
#define USING_ADS1115 0
#define ADS1115_I2C_NUMBER 0
#define ADS1115_CHIPS 1
uint8_t ADS1115_chipAddress [] = {0x48};

#define ADS1115_ALERT 0

#if (ADS1115_ALERT == 1)
uint8_t ADS1115_alertPins [] = {99};
#endif

//EEPROM CAT24C512
#define USING_CAT24C512 0
#define CAT24C512_I2C_NUMBER 0
#define CAT24C512_ADDRESS 0x50

//VARIABLES
bool wire1Init = false;
bool wire0Init = false;


#if(USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)
  #include <ADCInput.h>
  ADCInput oversamples (A0, A1, A2, A3);
#endif

#if(USING_CB1 == 1)
  bool ADS1115sentReq[2] = {false, false};
  long ADS1115value[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t ADS1115channelCounter[2] = {0,0};  
#elif(ADS1115_CHIPS > 0 && ENABLE_OVERSAMPLING == 1)
  bool ADS1115sentReq[ADS1115_CHIPS];
  uint16_t ADS1115value[4*(ADS1115_CHIPS+1)];
  uint8_t ADS1115channelCounter[ADS1115_CHIPS];
#elif(ADS1115_CHIPS > 0)
  bool ADS1115sentReq[ADS1115_CHIPS];
  uint16_t ADS1115value[4*ADS1115_CHIPS];
  uint8_t ADS1115channelCounter[ADS1115_CHIPS];
#endif

//ADC defines
#define ADC1 50
#define ADC2 51
#define ADC3 52
#define ADC4 53
#define ADC5 54
#define ADC6 55
#define ADC7 56
#define ADC8 57
#define ADC9 58
#define ADC10 59
#define ADC11 60
#define ADC12 61
#define ADC13 62
#define ADC14 63
#define ADC15 64
#define ADC16 65
#define ADC17 66
#define ADC18 67
#define ADC19 68
#define ADC20 69
#define ADC_CORR 50

//DDC ID DEFINES
#define DDCID 1
#define CB1ID 2
#define CB2ID 3

//DDC VERSION

#define MAJORVERSION 2
#define MINORVERSION 12
#define PATCHVERSION 0

//------------------------------
//---------LIBRARIES------------
//------------------------------

#if (BOARDTYPE == 0)
  #include <DDC32U4.h>
  #if (ENABLE_MOUSE == 1)
  #include <DDCANJOMOUSE.h>
  JoyMouse_ Mouse;
  uint8_t oldMouseSegment = 0;
  bool mouseRun = false;
  bool mouseRan = false;
  #endif
#elif (BOARDTYPE == 1)
  #include <DDCSAMD.h>
#elif (BOARDTYPE == 2)
  #include <DDCPI.h>
  extern "C"
  {
  #include "pico/bootrom.h"
  }
  #if (ENABLE_MOUSE == 1)
  #include <DDCANJOMOUSE2040.h>
  JoyMouseRP2040_ Mouse;
  uint8_t oldMouseSegment = 0;
  bool mouseRun = false;
  bool mouseRan = false;
  #endif
  long bootTimer = 0;
#endif

#if (USING_CB1 == 1 || USING_PCA9555 == 1 || USING_ADS1115 == 1 || USING_CAT24C512 == 1)
  #include <Wire.h>
#endif

#if (USING_32U4EEPROM == 1 || USING_RP2040EEPROM == 1)
  #include <EEPROM.h>
#endif
