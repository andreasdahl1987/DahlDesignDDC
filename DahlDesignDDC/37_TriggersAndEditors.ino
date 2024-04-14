 //----------------------------------------------------------------
 //-------------------------TRIGGERS-------------------------------
 //----------------------------------------------------------------
 
 bool buttonFieldBit (int fieldPlacement)
 {
    return (buttonField >> (fieldPlacement-1))  & 0x1;
 }

  bool rotaryFieldBit (int fieldPlacement)
 {
    return (rotaryField >> (fieldPlacement-1))  & 0x1;
 }

 bool biteSettingMode (int biteSettingMode)
 {
   return (biteSettingMode == (biteButtonBit1 | (biteButtonBit2 << 1)));
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

 bool rotaryPosition(int analogChannel, int switchPosition)
 {
    return analogLastCounter[analogChannel-1] + 1 == switchPosition;
 }

 bool analogTravel(int analogChannel, int threshold)
 {
    return average[analogChannel-1] >= threshold*10;
 }

bool encoderStack(int row, int col, int layer)
{
  return toggleTimer[row-1][col-1] == layer;
}

 //----------------------------------------------------------------
 //-------------------------EDITORS----------------------------------
 //----------------------------------------------------------------

void setButtonNumber(int row, int column, int number)
{
    buttonNumber[row-1][column-1] = number;
}

void setAnalogButtonNumber(int analogChannel, int layer, int number)
{
    if (layer == 1)
    {
      analogButtonNumber[analogChannel-1] = number;
    }
    else if (layer == 2)
    {
      analogButtonNumberIncMode[analogChannel-1] = number;
    }
}

void setSwitchMode(int row, int column, int mode)
{
    switchMode[row-1][column-1] = mode;
}

void setAnalogSwitchMode(int analogChannel, int modeBit, int modeValue)
{
    if (modeBit == 1)
    {
        analogSwitchMode1[analogChannel-1] = modeValue;
    }
    else if (modeBit == 2)
    {
        analogSwitchMode2[analogChannel-1] = modeValue;
    }
}
 
