//----------------------------------------
//-----------EEPROM LIBRARY---------------
//----------------------------------------

/*
* The EEPROM IC has 512 pages to write to, each having 128 bytes (we'll call them lines) available.
* Positions incrementing by 128 to get a page for each setting
*/

//MEMORY POSITIONS

#define UTIL 0
#define DDS_b 8
#define DDS_s 10
#define SLAVERELEASED 38
#define SLAVEPRESSED 40
#define MASTERRELEASED 42
#define MASTERPRESSED 44
#define CANDY 46
#define BITEPOINT 128
#define LEDSLOT 256
#define BRAKESLOT 384
#define THROTTLESLOT 512
#define PRESETSLOT 640

uint8_t EEPROMdump;

#if (USING_CAT24C512 == 1 || USING_32U4EEPROM == 1 || USING_CB1 == 1 || USING_RP2040EEPROM == 1)
uint16_t resetEEPROM = 0;
bool DDS_b_init = true;
bool DDS_s_init = true;
int oldBitePoint;
int oldLED;
float oldBrake;
float oldThrottle;
int oldPreset;
#endif
