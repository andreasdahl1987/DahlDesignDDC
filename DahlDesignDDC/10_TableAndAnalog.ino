//-----------------------------------------
//------------TABLE VARIABLES-------------
//-----------------------------------------

uint8_t row[] = { 99,99,99,99 };
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = { 99,99,99,99,99,99,99,99 };
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

//---------------------------------------
//--------TABLE DESCRIPTION-------------
//---------------------------------------

uint8_t buttonNumber[rowCount][colCount] =
{
  {0, 1, 2, 3, 4, 5, 6, 7},
  {8, 9, 10, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21, 22, 23},
  {24, 25, 26, 27, 28, 29, 30, 31}
};

//---------------------------------------
//------------DIRECT WIRING--------------
//---------------------------------------


uint8_t directPins[] = { 99 };
const uint8_t directPinsCount = sizeof(directPins) / sizeof(directPins[0]);


//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

#define analogSwitchCount 1

uint8_t analogButtonNumber[analogSwitchCount] =         //ANALOG BUTTONS 1
{ 0 };

uint8_t analogButtonNumberIncMode[analogSwitchCount] =  //ANALOG BUTTONS 2
{ 0 };
