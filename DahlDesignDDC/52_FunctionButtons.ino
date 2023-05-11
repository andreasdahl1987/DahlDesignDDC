//MODIFIER BUTTON

void modButton(int row, int column)
{
    modButtonRow = row;
    modButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    //Analog inject disable logic
    if (pushState[Row][Column] != latchLock[Row][Column])
    {
      if(globalClock - toggleTimer[Row][Column] < 400)
      {
        injectMuteCounter++; 
      }
      else
      {
        injectMuteCounter = 0;
      }
      latchLock[Row][Column] = pushState[Row][Column];
      toggleTimer[Row][Column] = globalClock;
    }
    if (injectMuteCounter >= 5)
    {
      injectMuteTimer = globalClock;
      injectMuteCounter = 0;
    }
    if (globalClock - injectMuteTimer < 20000)
    {
      injectMute = true;
    }
    else
    {
      injectMute = false;
    }

    Joystick.setButton(Number, pushState[Row][Column]);
}

//PRESET BUTTON

void presetButton(int row, int column)
{
    presetButtonRow = row;
    presetButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    Joystick.setButton(Number, pushState[Row][Column]);
}


//HYBRID and DDBUTTON.


void hybridButton(int row, int column)
{
    hybridButtonRow = row;
    hybridButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if (pushState[Row][Column] == 0)
    {
        latchLock[Row][Column] = false;
    }

    if (pushState[Row][Column] == 1 && !latchLock[Row][Column])
    {
        latchLock[Row][Column] = true;
        latchState[Row][Column] = !latchState[Row][Column];
    }
}

void DDButton(int row, int column)
{
    ddButtonRow = row;
    ddButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;

    #if (USING_CAT24C512 == 1 || USING_32U4EEPROM == 1 || USING_CB1 == 1)
    if (DDS_b_init)
    {
      latchState[Row][Column] = read16bitFromEEPROM(DDS_b);
      DDS_b_init = false;
    }
    #endif

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if (pushState[Row][Column] == 0)
    {
        latchLock[Row][Column] = false;
    }

    if (pushState[Row][Column] == 1 && !latchLock[Row][Column])
    {
        latchLock[Row][Column] = true;
        latchState[Row][Column] = !latchState[Row][Column];
        write16bitToEEPROM(DDS_b, latchState[Row][Column]);
    }
}
