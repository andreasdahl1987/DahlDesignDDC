#if (USING_CB1 == 1)

//---------------------------------------
//--------TABLE DESCRIPTION--------------
//---------------------------------------

const uint8_t rowCount = 8;
const uint8_t colCount = 8;

uint8_t buttonNumber[rowCount][colCount] =
{
  
  { 0, 1, 2, 3, 4, 5, 6, 7 },             //ROW 1, COLUMN 1-8

  { 8, 9, 10, 11, 12, 13, 14, 15 },       //ROW 2, COLUMN 1-8

  { 16, 17, 18, 19, 24, 25, 22, 23 },     //ROW 3, COLUMN 1-8

  { 24, 25, 26, 27, 28, 29, 30, 31 },     //ROW 4, COLUMN 1-8

  { 32, 33, 34, 35, 36, 37, 38, 39 },     //ROW 5, COLUMN 1-8

  { 40, 41, 42, 43, 44, 45, 46, 47 },     //ROW 6, COLUMN 1-8

  { 48, 49, 50, 51, 52, 53, 54, 55 },     //ROW 7, COLUMN 1-8

  { 56, 57, 58, 59, 60, 61, 62, 63 }      //ROW 8, COLUMN 1-8  
  
};


//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

#define analogSwitchCount 12

uint8_t analogButtonNumber[analogSwitchCount] =         //ANALOG BUTTONS 1
{ 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

uint8_t analogButtonNumberIncMode[analogSwitchCount] =  //ANALOG BUTTONS 2
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


//PINS FOR PULLUP
int row5Pins [8] = {19,17,20,18,21,22,24,23};
int row6Pins [8] = {12,13,10,11,9,3,1,2};

//ADC
bool sentReq1 = false;
bool sentReq2 = false;
int channelCount1 = 0;
int channelCount2 = 0;

#endif
