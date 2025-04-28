void RS16Inc(int row, int col, bool reverse)
{
  //>>
  int Row = row - 1;
  int Column = col - 1;
  int Number = buttonNumber[Row][Column];

  uint8_t pin1 = rawState[Row][Column];
  uint8_t pin2 = rawState[Row][Column+1];
  uint8_t pin3 = rawState[Row][Column+2];

  //pushState[Row][Column] : Old state
  //pushState[Row][Column+1] : New state
  //latchState[Row][Column] : CCW turn lock-in
  //latchState[Row][Column+1] : CW turn lock-in
  //toggleTimer[Row][Column] : CCW pulse timer
  //toggleTimer[Row][Column+1] : CW pulse timer

  if(pin1 + pin2 + pin3 == 1) //Resting position
  {
    pushState[Row][Column+1] = (pin1 << 0) | (pin2 << 1) | (pin3 << 2);
    pushState[Row][Column+1] = (pushState[Row][Column+1] == 4) ? 3 : pushState[Row][Column+1];
  }

  if(globalClock - toggleTimer[Row][Column] > PEC11Pulse) {latchState[Row][Column] = false;}        //Open up for CW turns
  if(globalClock - toggleTimer[Row][Column+1] > PEC11Pulse) {latchState[Row][Column+1] = false;}    //Open up for CCW turns

  if(pushState[Row][Column] != pushState[Row][Column+1]) //Initiate pulses and update position
  {
    int difference = pushState[Row][Column] - pushState[Row][Column + 1];

    if (((difference > 0 && difference < 2) || difference < -1) && !latchState[Row][Column+1] && globalClock - switchTimer[Row][Column] > E18Pulse + 10) //CCW turn
    {
        toggleTimer[Row][Column] = globalClock;
        latchState[Row][Column] = true;
        switchTimer[Row][Column] = globalClock;
    }
    else if (!latchState[Row][Column] && globalClock - switchTimer[Row][Column] > E18Pulse + 10)//CW turn
    {
      toggleTimer[Row][Column+1] = globalClock;
      latchState[Row][Column+1] = true;
      switchTimer[Row][Column] = globalClock;
    }
    pushState[Row][Column] = pushState[Row][Column+1];
  }

  Joystick.setButton(Number + 1 - reverse, globalClock-toggleTimer[Row][Column] < E18Pulse);
  Joystick.setButton(Number + reverse, globalClock-toggleTimer[Row][Column+1] < E18Pulse);
}