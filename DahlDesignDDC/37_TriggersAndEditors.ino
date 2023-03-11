 //----------------------------------------------------------------
 //-------------------------EDITS----------------------------------
 //----------------------------------------------------------------
 
 bool buttonFieldBit (int fieldPlacement)
 {
    return (buttonField >> (fieldPlacement-1))  & 0x1;
 }

  bool rotaryFieldBit (int fieldPlacement)
 {
    return (rotaryField >> (fieldPlacement-1))  & 0x1;
 }

 bool buttonPressed (int row, int column)
 {
    return pushState[row-1][column-1];
 }

 bool switchPressed (int row, int column)
 {
    return rawState[row-1][column-1];
 }

 bool togglePressed (int row, int column)
 {
    return latchState[row-1][column-1];
 }

 bool presetSearch (int presetNumber)
 {
    return (presetNumber == (switchPreset + 1));
 }

 bool modButtonPressed ()
 {
    return pushState[modButtonRow-1][modButtonCol-1];
 }

 bool rotaryPosition(int switchNumber, int switchPositioin)
 {
    return analogLastCounter[switchNumber-1] + 1 == switchNumber;
 }


 //----------------------------------------------------------------
 //-------------------------EDITORS----------------------------------
 //----------------------------------------------------------------

void setButtonNumber(int row, int column, int number)
{
    buttonNumber[row-1][column-1] = number;
}

void setAnalogButtonNumber(int switchNumber, int layer, int number)
{
    if (layer == 1)
    {
      analogButtonNumber[switchNumber-1] = number;
    }
    else if (layer == 2)
    {
      analogButtonNumberIncMode[switchNumber-1] = number;
    }
}

void setSwitchMode(int row, int column, int mode)
{
    switchMode[row-1][column-1] = mode;
}

void setAnalogSwitchMode(int switchNumber, int modeBit, int modeValue)
{
    if (modeBit == 1)
    {
        analogSwitchMode1[switchNumber-1] = modeValue;
    }
    else if (modeBit == 2)
    {
        analogSwitchMode2[switchNumber-1] = modeValue;
    }
}
 
