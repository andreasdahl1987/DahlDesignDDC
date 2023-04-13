//----------------------------------------
//-----------EEPROM LIBRARY---------------
//----------------------------------------

/*
* The EEPROM IC has 512 pages to write to, each having 128 bytes (we'll call them lines) available.
*/

//PAGE NUMBERS

#define UTIL 0x00

#define BITEPOINT 0x01
#define PRESET 0x02



//LINE NUMBERS

#define UTIL_INIT 0x00

//Variables
#if (USING_CAT24C512 == 1)
int oldBitePoint;
int oldPreset;
#endif
