void biteButton(int row, int column)
{
    Joystick.setRyAxisRange(0, 1000);

    biteButtonRow = row;
    biteButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    
    biteRefresh = false;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
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

void biteButtonLatch(int row, int column)
{
    Joystick.setRyAxisRange(0, 1000);

    biteButtonRow = row;
    biteButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    biteRefresh = false;

    if (latchState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        latchState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        latchState[Row][Column] = rawState[Row][Column];
    }

    //Scrolling through bite point setting
    if (!latchState[Row][Column])
    {
        latchLock[Row][Column] = true;
    }

    if (latchState[Row][Column] && latchLock[Row][Column])
    {
        latchLock[Row][Column] = false;
        pushState[Row][Column] = !pushState[Row][Column];
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

void biteAdjustButton(int row, int column, int increment)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
        if(rawState[Row][Column] == 1)
        {
          latchState[Row][Column] = true;          
        }
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if(latchState[Row][Column] && pushState[biteButtonRow-1][biteButtonCol-1] == 1)
    {
      bitePoint += increment;
      latchState[Row][Column] = false;
      if (bitePoint > 1000)
      {
        bitePoint = 1000;  
      }
      else if (bitePoint < 0)
      {
        bitePoint = 0;
      }
    }
    else
    {
      latchState[Row][Column] = false;
    }

    if (pushState[biteButtonRow-1][biteButtonCol-1] == 0)
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }
    else
    {
        Joystick.setButton(Number, 0);
    }
}

void biteAdjustButtonSolo(int row, int column, int increment)
{
    int Row = row - 1;
    int Column = column - 1;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
        if(rawState[Row][Column] == 1)
        {
          latchState[Row][Column] = true;          
        }
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if(latchState[Row][Column])
    {
      bitePoint += increment;
      latchState[Row][Column] = false;
      if (bitePoint > 1000)
      {
        bitePoint = 1000;  
      }
      else if (bitePoint < 0)
      {
        bitePoint = 0;
      }
    }
    else
    {
      latchState[Row][Column] = false;
    }
}

void launchButton(int row, int column, int analogChannelAffected)
{
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

    if (!analogLatchLock[analogChannelAffected - 1] && pushState[Row][Column] == 1)
    {
        launchButtonLatch = true;
    }
    else if (analogLatchLock[analogChannelAffected - 1])
    {
        launchButtonLatch = false;
    }
    if (!launchButtonLatch)
    {
        Joystick.setButton(Number, pushState[Row][Column]);
        Joystick.setButton(Number+1, 0);
    }
    else
    {
        Joystick.setButton(Number+1, pushState[Row][Column]);
        Joystick.setButton(Number, 0);
    }

}

void bitePotLockButton(int8_t row, int8_t column, int fieldPlacement)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int FieldPlacement = fieldPlacement;

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
        bitePotLock = !bitePotLock;
    }

    //Push lock
    long push = 0;
    push = push | bitePotLock;
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;
}

void bitePotLockToggle(int row, int column, int fieldPlacement)
{
    int Row = row - 1;
    int Column = column - 1;
    int FieldPlacement = fieldPlacement;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    bitePotLock = pushState[Row][Column];

    //Push lock
    long push = 0;
    push = push | bitePotLock;
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;
}

void neutralButton(int row, int column)
{
    neutralButtonRow = row;
    neutralButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = 15;
    int ActivePlacement = 5;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
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

    //SWITCH MODE 2: MOMENTARY BUTTON
    if (switchMode[Row][Column])
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }

    //SWITCH MODE 1: LATCHING NEUTRAL BuTTON
    else if (!switchMode[Row][Column])
    {
        if (pushState[Row][Column] == 0)
        {
            latchLock[Row][Column] = false;
        }

        if (pushState[Row][Column] == 1 && !latchLock[Row][Column] && !(pushState[modButtonRow - 1][modButtonCol - 1] == 1))
        {
            latchLock[Row][Column] = true;
            latchState[Row][Column] = !latchState[Row][Column];
        }

        //Push neutral active
        long push = 0;
        push = push | latchState[Row][Column];
        push = push << (ActivePlacement - 1);
        buttonField = buttonField | push;
    }
}
