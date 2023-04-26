//----------------------------------------
//-----------EEPROM LIBRARY---------------
//----------------------------------------

/*
* The EEPROM IC has 512 pages to write to, each having 128 bytes (we'll call them lines) available.
* Positions incrementing by 128 to get a page for each setting
*/

//MEMORY POSITIONS

#define UTIL 0
#define BITEPOINT 128
#define LEDSLOT 256
#define BRAKESLOT 384
#define THROTTLESLOT 512

#if (USING_CAT24C512 == 1 || USING_32U4EEPROM == 1)
int oldBitePoint;
int oldLED;
int oldBrake;
int oldThrottle;
#endif
