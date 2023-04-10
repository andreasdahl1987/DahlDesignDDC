#if(USING_CB1 == 0)

//-----------------------------------------
//------------TABLE VARIABLES-------------
//-----------------------------------------

uint8_t row[] = { 0, 0, 0, 0, 0};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = { 0, 0, 0, 0, 0 };
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

//---------------------------------------
//--------TABLE DESCRIPTION--------------
//---------------------------------------

uint8_t buttonNumber[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},    //ROW1
  {0, 0, 0, 0, 0},    //ROW2
  {0, 0, 0, 0, 0},    //ROW3
  {0, 0, 0, 0, 0},    //ROW4
  {0, 0, 0, 0, 0}     //ROW5
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



#endif
