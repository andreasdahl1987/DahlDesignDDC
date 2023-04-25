//----------------------------------------
//-----------EEPROM LIBRARY---------------
//----------------------------------------

/*
* The EEPROM IC has 512 pages to write to, each having 128 bytes (we'll call them lines) available.
*/

//PAGE NUMBERS

#define UTIL 0
#define BITEPOINT 126

//Variables
#if (USING_CAT24C512 == 1)
int oldBitePoint;
#endif
