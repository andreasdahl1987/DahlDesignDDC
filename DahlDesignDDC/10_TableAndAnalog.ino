//-----------------------------------------
//------------TABLE VARIABLES-------------
//-----------------------------------------

uint8_t row[] = { 99 };
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = { 99,99 };
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

//---------------------------------------
//--------TABLE DESCRIPTION--------------
//---------------------------------------

uint8_t buttonNumber[rowCount][colCount] =
{
  {0, 0}
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
