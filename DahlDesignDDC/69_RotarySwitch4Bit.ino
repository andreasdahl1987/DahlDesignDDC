void rotarySwitch4Bit(int row, int column,bool reverse)
{
  int Row = row - 1;
  int Column = column - 1;
  int Number = buttonNumber[Row][Column];
  int IncNumber = buttonNumber[Row][Column+1];

  bool Pin1 = rawState[Row][Column];
  bool Pin2 = rawState[Row][Column + 1];
  bool Pin3 = rawState[Row][Column + 2];
  bool Pin4 = rawState[Row][Column + 3];

  bool array[4] = { Pin1, Pin2, Pin3, Pin4 };

  int pos = 0;

  for (int i = 0; i < 4; i++)
  {
      if (array[i])
      {
          pos |= (1 << i);
      }
  }

  pos = pos ^ (pos >> 2);
  pos = pos ^ (pos >> 1);

  int result = pos;

  //pushState and switchTimer +1: CCW position and timer
  //pushState and switchTimer +2: CW position and timer
  //toggletimer: old value
  //latchState and toggleTimer +1 : CCW 0-expect trigger and timer
  //latchState and toggleTimer +2 : CW 0-expect trigger and timer
  //pushState and toggleTimer + 3: Unexpected value
  //latchState +3: first boot
  //switchTimer +3: unexpected value timer 


  if(!latchState[Row][Column+3]) // First boot, setting cW and CCW values
  {
    latchState[Row][Column+3] = true;
    pushState[Row][Column] = result; //Reset result
    toggleTimer[Row][Column] = result; //Reset old value
    pushState[Row][Column+1] = result - 1; //Set next expeted CCW position
    pushState[Row][Column+2] = result + 1; //Set next expected CW position
    if (result == 11)
    {
      pushState[Row][Column+2] = 0; //CW position rolls over
    }
    else if (result == 0)
    {
      pushState[Row][Column+1] = 11; //CCW positions rolls back
    }
  }

  if(pushState[Row][Column] == result) //Reset unexpected value
  {
    switchTimer[Row][Column+3] = globalClock;
    pushState[Row][Column+3] = result;
  }

  //Detecting position change, initiating the whole thing
  if((pushState[Row][Column] != result) && !latchState[Row][Column+1] && !latchState[Row][Column+2] && globalClock - switchTimer[Row][Column] > rotarySwitchCooldown)
  {
    if(result == pushState[Row][Column+1] && (globalClock - switchTimer[Row][Column+2] > rotarySwitchCounterLock)) //
    {
      if (pushState[Row][Column+1] != 0) //If expected CCW position is not 0
      {
        toggleTimer[Row][Column] = pushState[Row][Column]; //Catch the old value
        pushState[Row][Column] = result; //Reset result
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1) //Change mode
        {
          switchMode[Row][Column] = !switchMode[Row][Column];
          latchState[Row][Column] = true; //Initiate button resets
        }
        else
        {
          switchTimer[Row][Column] = globalClock; //Pulse timer
        }
        switchTimer[Row][Column+1] = globalClock; //CW lock timer

        pushState[Row][Column+1] = result - 1; //Set next expeted CCW position
        pushState[Row][Column+2] = result + 1; //Set next expected CW position
        if (result == 11)
        {
          pushState[Row][Column+2] = 0; //CW position rolls over
        }
        else if (result == 0)
        {
          pushState[Row][Column+1] = 11; //CCW positions rolls back
        }
      }
      else //If expected CCW position is 0
      {
        latchState[Row][Column+1] = true; //Now tuning into 0-checking
        toggleTimer[Row][Column+1] = globalClock; //Starting timer to keep 0
      }
    }

    else if(result == pushState[Row][Column+2] && (globalClock - switchTimer[Row][Column+1] > rotarySwitchCounterLock)) //If expected CW position
    {
      if (pushState[Row][Column+2] != 0) //If expected CW position is not 0
      {
        toggleTimer[Row][Column] = pushState[Row][Column]; //Catch the old value
        pushState[Row][Column] = result; //Reset result
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1) //Change mode
        {
          switchMode[Row][Column] = !switchMode[Row][Column];
          latchState[Row][Column] = true; //Initiate button resets
        }
        else
        {
          switchTimer[Row][Column] = globalClock; //Pulse timer
        }
        switchTimer[Row][Column+2] = globalClock; //CCW lock timer

        pushState[Row][Column+1] = result - 1; //Set next expeted CCW position
        pushState[Row][Column+2] = result + 1; //Set next expected CW position
        if (result == 11)
        {
          pushState[Row][Column+2] = 0; //CW position rolls over
        }
        else if (result == 0)
        {
          pushState[Row][Column+1] = 11; //CCW positions rolls back
        }
      }
      else //If expected CW position is 0
      {
        latchState[Row][Column+2] = true; //Now tuning into 0-checking
        toggleTimer[Row][Column+2] = globalClock; //Starting timer to keep 0
      }
    }
    else //result is something completely unexpected
    {
      if(result != pushState[Row][Column+3]) //first loop seeing this, reset timer and remember state
      {
        switchTimer[Row][Column+3] = globalClock;
        pushState[Row][Column+3] = result;
      }
      else if(globalClock- switchTimer[Row][Column+3] > rotarySwitchUnexpected) //This unexpected value is actually sticking, we've missed something. Not triggering any pulse.
      {
        pushState[Row][Column+1] = result - 1; //Set next expeted CCW position
        pushState[Row][Column+2] = result + 1; //Set next expected CW position
        if (result == 11)
        {
          pushState[Row][Column+2] = 0; //CW position rolls over
        }
        else if (result == 0)
        {
          pushState[Row][Column+1] = 11; //CCW positions rolls back
        }
      }
    }
  }

  //CCW 0 timer
  if(latchState[Row][Column+1])
  {
    if (result == 0)
    {
      if (globalClock - toggleTimer[Row][Column+1] > rotarySwitchZeroBounce && globalClock - switchTimer[Row][Column+2] > rotarySwitchCounterLock) //We've kept 0 for 50 ms, it is actually not a bounce
      {
        toggleTimer[Row][Column] = pushState[Row][Column]; //Catch the old value
        pushState[Row][Column] = result; //Reset result
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1) //Change mode
        {
          switchMode[Row][Column] = !switchMode[Row][Column];
          latchState[Row][Column] = true; //Initiate button resets
        }
        else
        {
          switchTimer[Row][Column] = globalClock; //Pulse timer
        }
        switchTimer[Row][Column+1] = globalClock; //CW lock timer

        pushState[Row][Column+1] = 11; //Set next expeted CCW position
        pushState[Row][Column+2] = 1; //Set next expected CW position
        latchState[Row][Column+1] = false; //Turn off
      } //If timer hasnt passed 50 ms, we'll do nothing. Just wait and see if it sticks. 
    }
    else
    {
      latchState[Row][Column+1] = false; //It was just a bounce :(
    }
  }

  //CW 0 timer
  if(latchState[Row][Column+2])
  {
    if (result == 0)
    {
      if (globalClock - toggleTimer[Row][Column+2] > rotarySwitchZeroBounce && globalClock - switchTimer[Row][Column+1] > rotarySwitchCounterLock) //We've kept 0 for 50 ms, it is actually not a bounce
      {
        toggleTimer[Row][Column] = pushState[Row][Column]; //Catch the old value
        pushState[Row][Column] = result; //Reset result
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1) //Mode change
        {
          switchMode[Row][Column] = !switchMode[Row][Column];
          latchState[Row][Column] = true;
        }
        else
        {
          switchTimer[Row][Column] = globalClock; //Pulse timer
        }
        switchTimer[Row][Column+2] = globalClock; //CCW lock timer
        pushState[Row][Column+1] = 11; //Set next expeted CCW position
        pushState[Row][Column+2] = 1; //Set next expected CW position
        latchState[Row][Column+2] = false; //Turn off
      } //If timer hasnt passed 50 ms, we'll do nothing. Just wait and see if it sticks. 
    }
    else
    {
      latchState[Row][Column+2] = false; //It was just a bounce :(
    }
  }

  if(latchState[Row][Column]) //Resetting button numbers
  {
    for (int i = 0; i < 12; i++)
    {
      Joystick.releaseButton(i + Number);
    }

    Joystick.releaseButton(IncNumber);
    Joystick.releaseButton(IncNumber+1);
  }

//Switch mode 0: 12 positions

  if(!switchMode[Row][Column])
  {
    for (int i = 0; i < 12; i++)
    {
        if (i == pushState[Row][Column])
        {
          int press = i+Number;
          if(reverse) {press = 11 - press;}
          Joystick.pressButton(press);
        }
        else
        {   
          int press = i+Number;
          if(reverse) {press = 11 - press;}
          Joystick.releaseButton(press);
        }
    }
  }

//Switch mode 1: Incremental

  if(switchMode[Row][Column]) 
  {
    if(globalClock - switchTimer[Row][Column] < encoderPulse) //Encoder pulses
    {
      int difference = pushState[Row][Column] - toggleTimer[Row][Column];

      if ((difference > 0 && difference < 5) || difference < -5)
      {
        Joystick.setButton(IncNumber, 1-reverse);
        Joystick.setButton(IncNumber + 1, reverse);
      }
      else
      {
        Joystick.setButton(IncNumber, reverse);
        Joystick.setButton(IncNumber + 1, 1-reverse);
      }
    }
    else
    {
        Joystick.setButton(IncNumber, 0);
        Joystick.setButton(IncNumber + 1, 0);
    }
  }
}