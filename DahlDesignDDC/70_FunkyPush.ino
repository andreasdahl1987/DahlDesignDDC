//----------------------------
//----FUNKY CENTER PUSH-------
//----------------------------


void funkyPush(int row, int column, int aCol, int bCol, int cCol, int dCol)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    int Acol = aCol - 1;
    int Bcol = bCol - 1;
    int Ccol = cCol - 1;
    int Dcol = dCol - 1;

    if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
    {
        if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            switchTimer[Row][Column] = globalClock;
            pushState[Row][Column] = rawState[Row][Column];
        }

        if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            pushState[Row][Column] = rawState[Row][Column];
        }
    }

    Joystick.setButton(Number, pushState[Row][Column]);
}

void funkyPushBite(int row, int column,int aCol, int bCol, int cCol, int dCol)
{
    Joystick.setRyAxisRange(0, 1000);

    biteButtonRow = row;
    biteButtonCol = column;
    
    biteRefresh = false;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    int Acol = aCol - 1;
    int Bcol = bCol - 1;
    int Ccol = cCol - 1;
    int Dcol = dCol - 1;

    if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
    {
        if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            switchTimer[Row][Column] = globalClock;
            pushState[Row][Column] = rawState[Row][Column];
        }

        if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            pushState[Row][Column] = rawState[Row][Column];
        }
    }

    //Scrolling through bite point setting
    if (!pushState[Row][Column])
    {
        latchLock[Row][Column] = true;
    }

    if (pushState[Row][Column] && latchLock[Row][Column])
    {
        latchLock[Row][Column] = false;
        if (biteButtonBit1 && !biteButtonBit2)
        {
            biteButtonBit2 = true;
            biteButtonBit1 = false;
        }
        else if (!biteButtonBit1 && biteButtonBit2)
        {
            biteButtonBit1 = true;
        }
        else if (biteButtonBit1 && biteButtonBit2)
        {
            biteButtonBit2 = false;
            biteButtonBit1 = false;
            biteRefresh = true;
        }
    }
    
    //Push bite button state
    long pesh = 0;
    pesh = pesh | pushState[Row][Column] << 14;
    rotaryField = rotaryField | pesh;

    //Push bite setting level
    long push = 0;
    push = push | biteButtonBit1;
    push = push | (biteButtonBit2 << 1);
    push = push << 10;
    rotaryField = rotaryField | push;

    Joystick.setRyAxis(bitePoint);
    Joystick.setButton(Number, pushState[Row][Column]);
}

void funkyPushModButton(int row, int column,int aCol, int bCol, int cCol, int dCol)
{
    modButtonRow = row;
    modButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    int Acol = aCol - 1;
    int Bcol = bCol - 1;
    int Ccol = cCol - 1;
    int Dcol = dCol - 1;

    if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
    {
        if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            switchTimer[Row][Column] = globalClock;
            pushState[Row][Column] = rawState[Row][Column];
        }

        if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            pushState[Row][Column] = rawState[Row][Column];
        }
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


void funkyPushM(int row, int column, int fieldPlacement, int aCol, int bCol, int cCol, int dCol)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = fieldPlacement;

    int Acol = aCol - 1;
    int Bcol = bCol - 1;
    int Ccol = cCol - 1;
    int Dcol = dCol - 1;

    if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
    {
        if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            switchTimer[Row][Column] = globalClock;
            pushState[Row][Column] = rawState[Row][Column];
        }

        if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            pushState[Row][Column] = rawState[Row][Column];
        }
    }

    //Change switch mode
    if (pushState[Row][Column] == 0)
    {
        switchModeLock[Row][Column] = false;
    }

    if (pushState[Row][Column] == 1 && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && FieldPlacement != 0 && !switchModeLock[Row][Column])
    {
        switchModeLock[Row][Column] = true;
        switchMode[Row][Column] = !switchMode[Row][Column];
        latchLock[Row][Column] = false;
        latchState[Row][Column] = false;
    }

    //Push switch mode
    long push = 0;
    push = push | switchMode[Row][Column];
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;

    //SWITCH MODE 1: MOMENTARY BUTTON
    if (!switchMode[Row][Column])
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }

    //SWITCH MODE 2: LATCHING BUTTON
    else if (switchMode[Row][Column])
    {
        if (pushState[Row][Column] == 0)
        {
            latchLock[Row][Column] = false;
        }

        if (pushState[Row][Column] == 1 && !latchLock[Row][Column])
        {
            latchLock[Row][Column] = true;
            latchState[Row][Column] = !latchState[Row][Column];
        }

        Joystick.setButton(Number, latchState[Row][Column]);
    }
}

void funkyPushL(int row, int column, int aCol, int bCol, int cCol, int dCol)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    int Acol = aCol - 1;
    int Bcol = bCol - 1;
    int Ccol = cCol - 1;
    int Dcol = dCol - 1;

    if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
    {
        if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            switchTimer[Row][Column] = globalClock;
            pushState[Row][Column] = rawState[Row][Column];
        }

        if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            pushState[Row][Column] = rawState[Row][Column];
        }
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

    Joystick.setButton(Number, latchState[Row][Column]);
}

void funkyPushHybrid(int row, int column, int aCol, int bCol, int cCol, int dCol)
{
    hybridButtonRow = row;
    hybridButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Acol = aCol - 1;
    int Bcol = bCol - 1;
    int Ccol = cCol - 1;
    int Dcol = dCol - 1;

    if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
    {
        if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            switchTimer[Row][Column] = globalClock;
            pushState[Row][Column] = rawState[Row][Column];
        }

        if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            pushState[Row][Column] = rawState[Row][Column];
        }
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

void funkyPushDDButton(int row, int column, int aCol, int bCol, int cCol, int dCol)
{
    ddButtonRow = row;
    ddButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Acol = aCol - 1;
    int Bcol = bCol - 1;
    int Ccol = cCol - 1;
    int Dcol = dCol - 1;

    if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
    {
        if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            switchTimer[Row][Column] = globalClock;
            pushState[Row][Column] = rawState[Row][Column];
        }

        if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
        {
            pushState[Row][Column] = rawState[Row][Column];
        }
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
