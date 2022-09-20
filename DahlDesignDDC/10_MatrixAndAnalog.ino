//------------------------------
//-------MATRIX VARIABLES-------
//------------------------------

uint8_t row[] = {};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = {};
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

//---------------------------------------
//--------MATRIX DESCRIPTION-------------
//---------------------------------------

const uint8_t buttonNumber[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

const uint8_t analogButtonNumber[10] =         //ANALOG BUTTONS 1
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint8_t analogButtonNumberIncMode[10] =  //ANALOG BUTTONS 2
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
