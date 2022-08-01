//------------------------------
//-------MATRIX VARIABLES-------
//------------------------------

uint8_t row[] = {4,5,6,7,8};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = {10,11,14,15,16};
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


bool switchMode[rowCount][colCount] = //BOOT PRESET
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

int8_t analogSwitchMode1[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //BOOT PRESET
int8_t analogSwitchMode2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//---------------------------------------
//--------------PRESETS------------------
//---------------------------------------


const bool preset1[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const bool preset2[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const bool preset3[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const bool preset4[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const bool preset5[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const bool preset6[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const bool preset7[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const bool preset8[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

const int8_t analogMode1Preset1[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset1[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const int8_t analogMode1Preset2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const int8_t analogMode1Preset3[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset3[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const int8_t analogMode1Preset4[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset4[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const int8_t analogMode1Preset5[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset5[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const int8_t analogMode1Preset6[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset6[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const int8_t analogMode1Preset7[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset7[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const int8_t analogMode1Preset8[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int8_t analogMode2Preset8[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
