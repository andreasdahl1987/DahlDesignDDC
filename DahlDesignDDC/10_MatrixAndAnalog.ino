//------------------------------
//-------MATRIX VARIABLES-------
//------------------------------

uint8_t row[] = {0};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = {0};
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

bool nonMatrixIncluded = false;

uint8_t nonMatrix[] = {0};
const uint8_t nonMatrixCount = sizeof(nonMatrix) / sizeof(nonMatrix[0]);

//---------------------------------------
//--------MATRIX DESCRIPTION-------------
//---------------------------------------

const uint8_t buttonNumber[rowCount][colCount] =
{
  {0}
};

//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

#define analogSwitchCount 1

const uint8_t analogButtonNumber[analogSwitchCount] =         //ANALOG BUTTONS 1
{0};

const uint8_t analogButtonNumberIncMode[analogSwitchCount] =  //ANALOG BUTTONS 2
{0};
