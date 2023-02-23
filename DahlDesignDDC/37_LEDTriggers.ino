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


 
