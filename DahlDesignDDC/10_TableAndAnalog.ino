#if(USING_CB1 == 0)

//-----------------------------------------
//------------TABLE VARIABLES-------------
//-----------------------------------------

uint8_t row[] = { 4,30,2,11,17,7,A5};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = { 12,6,8,9,10,5,13};
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

//---------------------------------------
//--------TABLE DESCRIPTION--------------
//---------------------------------------

uint8_t buttonNumber[rowCount][colCount] =
{
  {14, 0, 10, 11, 0, 1, 2},     //ROW 1
  {26, 27, 29, 25, 28, 0, 24},  //ROW 2
  {32, 31, 6, 0, 34, 18, 0},    //ROW 3
  {16, 0, 12, 13, 3, 4, 5},     //ROW 4
  {39, 41, 65, 0, 40, 0, 38},   //ROW 5
  {20, 0, 35, 33, 0, 0, 23},    //ROW 6
  {22, 37, 36 ,67 , 0, 0, 0}    //ROW 7
};

//---------------------------------------
//------------DIRECT WIRING--------------
//---------------------------------------


uint8_t directPins[] = { 99 };
const uint8_t directPinsCount = sizeof(directPins) / sizeof(directPins[0]);


//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

#define analogSwitchCount 4

uint8_t analogButtonNumber[analogSwitchCount] =         //ANALOG BUTTONS 1
{ 69, 83, 0, 0 };

uint8_t analogButtonNumberIncMode[analogSwitchCount] =  //ANALOG BUTTONS 2
{ 81, 95, 0, 0 };



#endif
