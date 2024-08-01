#if(USING_CB1 == 0)

//-----------------------------------------
//------------TABLE VARIABLES-------------
//-----------------------------------------

uint8_t row[] = { 0, 0, 0, 0, 0};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = { 0, 0, 0, 0, 0};
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
//------------OUTPUT DEVICE--------------
//---------------------------------------


uint8_t outputPins[] = { 17, 20, 18, 21, 22, 24, 19};
const uint8_t outputPinsCount = sizeof(outputPins) / sizeof(outputPins[0]);



//---------------------------------------
//--------ANALOG CHANNEL SETUP-----------
//---------------------------------------

#define analogChannelCount 1                             //Number of analog channels

uint8_t analogPins[analogChannelCount] =                 //Pin number for your analog channels
{ 99 };

uint8_t analogButtonNumber[analogChannelCount] =         //Button number for your analog channels
{ 0 };

uint8_t analogButtonNumberIncMode[analogChannelCount] =  //Button number for alternate modes
{ 0 };



#endif
