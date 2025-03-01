//----------------------------
//----FUNKY ENCODER-----------
//----------------------------

void funkyRotary(int Arow, int Acol, int Bcol, bool reverse) 
{
    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = Bcol - 1;

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
}

void funkyBite(int Arow, int Acol, int Bcol, bool reverse) 
{

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = Bcol - 1;

    //Reading switch mode
    toggleTimer[Row][bCol] = switchMode[Row][bCol] << 1 | switchMode[Row][Column];

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3)) //CLOCKWIZE TURN
        {
            switchTimer[Row][Column] = globalClock;

            if (pushState[biteButtonRow - 1][biteButtonCol - 1] && !biteButtonBit1 && !biteButtonBit2) //Engage in bite mode
            {
                biteButtonBit1 = true;
            }
            else if (!(!biteButtonBit1 && !biteButtonBit2)) //If we're in bite mode
            {
                if (biteButtonBit1 && !biteButtonBit2)
                {
                    bitePoint = bitePoint - 100;
                    if (bitePoint < 0)
                    {
                        bitePoint = 1000;
                    }
                }
                else if (!biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint - 10;
                    if (bitePoint < 0)
                    {
                        bitePoint = 1000;
                    }
                }
                else if (biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint - 1;
                    if (bitePoint < 0)
                    {
                        bitePoint = 1000;
                    }
                }
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1)) //COUNTER CLOCKWIZE TURN
        {
            switchTimer[Row][bCol] = globalClock;

            if (pushState[biteButtonRow - 1][biteButtonCol - 1] && !biteButtonBit1 && !biteButtonBit2) //Engage in bite mode
            {
                biteButtonBit1 = true;
            }
            else if (!(!biteButtonBit1 && !biteButtonBit2)) //If we're in bite mode
            {
                if (biteButtonBit1 && !biteButtonBit2)
                {
                    bitePoint = bitePoint + 100;
                    if (bitePoint > 1000)
                    {
                        bitePoint = 1000;
                    }
                    else if (bitePoint == 1000)
                    {
                        bitePoint = 0;
                    }
                }
                else if (!biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint + 10;
                    if (bitePoint > 1000)
                    {
                        bitePoint = 1000;
                    }
                    else if (bitePoint == 1000)
                    {
                        bitePoint = 0;
                    }
                }
                else if (biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint + 1;
                    if (bitePoint > 1000)
                    {
                        bitePoint = 1000;
                    }
                    else if (bitePoint == 1000)
                    {
                        bitePoint = 0;
                    }
                }
            }
        }
    }
    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    if (!biteButtonBit1 && !biteButtonBit2)
    {
        Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
        Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }
}

void funkyRotaryMod(int Arow, int Acol, int Bcol, bool reverse) 
{
    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
    {
      Number += 2;
    }

    int bCol = Bcol - 1;

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
}

void funkyRotaryStack(int stackButtonRow, int stackButtonColumn, int fieldPlacement, int layers, int Arow, int Acol, int Bcol, bool reverse) 
{
    int Row = Arow - 1;
    int Column = Acol - 1;
    int bCol = Bcol - 1;

    int ButtonRow = stackButtonRow - 1;
    int ButtonCol = stackButtonColumn - 1;

    //Button logics
    if (pushState[ButtonRow][ButtonCol] != rawState[ButtonRow][ButtonCol] && (globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        switchTimer[ButtonRow][ButtonCol] = globalClock;
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if ((globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if (pushState[ButtonRow][ButtonCol] == 0)
    {
        latchLock[ButtonRow][ButtonCol] = false;
    }

    if (pushState[ButtonRow][ButtonCol] == 1 && !latchLock[ButtonRow][ButtonCol])
    {
        latchLock[ButtonRow][ButtonCol] = true;
        toggleTimer[ButtonRow][ButtonCol] ++;
    }
    if (toggleTimer[ButtonRow][ButtonCol] >= layers)
    {
      toggleTimer[ButtonRow][ButtonCol] = 0;
    }
    
    //Adjust button number

    int Number = buttonNumber[Row][Column] + toggleTimer[ButtonRow][ButtonCol] * 2;

    //Encoder logic
    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));

    //Push stack placement
    long push = 0;
    push = push | toggleTimer[ButtonRow][ButtonCol];
    push = push << (fieldPlacement - 1);
    rotaryField = rotaryField | push;
}

void funkyRotaryStackPush(int pushButtonRow, int pushButtonColumn, int aButton, int bButton, int cButton, int dButton, int fieldPlacement, int layers, int rotRow, int rotAcol, int rotBcol, bool reverse) 
{
    int Row = rotRow - 1;
    int Column = rotAcol - 1;
    int bCol = rotBcol - 1;

    int PushRow = pushButtonRow - 1;
    int PushCol = pushButtonColumn - 1;
    int Acol = aButton - 1;
    int Bcol = bButton - 1;
    int Ccol = cButton - 1;
    int Dcol = dButton - 1;

    //Funky pushbutton
    if (!pushState[PushRow][Acol] && !pushState[PushRow][Bcol] && !pushState[PushRow][Ccol] && !pushState[PushRow][Dcol])
    {
        if (pushState[PushRow][PushCol] != rawState[PushRow][PushCol] && (globalClock - switchTimer[PushRow][PushCol]) > buttonCooldown)
        {
            switchTimer[PushRow][PushCol] = globalClock;
            pushState[PushRow][PushCol] = rawState[PushRow][PushCol];
        }

        if ((globalClock - switchTimer[PushRow][PushCol]) > buttonCooldown)
        {
            pushState[PushRow][PushCol] = rawState[PushRow][PushCol];
        }
    }

    if (pushState[PushRow][PushCol] == 0)
    {
        latchLock[PushRow][PushCol] = false;
    }

    if (pushState[PushRow][PushCol] == 1 && !latchLock[PushRow][PushCol])
    {
        latchLock[PushRow][PushCol] = true;
        toggleTimer[PushRow][PushCol]++;
    }
    if (toggleTimer[PushRow][PushCol] >= layers)
    {
      toggleTimer[PushRow][PushCol] = 0;
    }
    
    //Adjust button number

    int Number = buttonNumber[Row][Column] + toggleTimer[PushRow][PushCol] * 2;

    //Encoder logic
    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));

    //Push stack placement
    long push = 0;
    push = push | toggleTimer[PushRow][PushCol];
    push = push << (fieldPlacement - 1);
    rotaryField = rotaryField | push;
}

void DDSfunky(int Arow, int Acol, int Bcol) {

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];
    if (latchState[ddButtonRow - 1][ddButtonCol - 1])
    {
        Number = Number + 12;
    }
    int FieldPlacement = 5;

    int bCol = Bcol - 1;

    #if (USING_CAT24C512 == 1 || USING_32U4EEPROM == 1 || USING_CB1 == 1)
      if (DDS_s_init)
      {
        toggleTimer[Row][Column] = read16bitFromEEPROM(DDS_s);
      }
    #endif

    //Reading switch mode
    toggleTimer[Row][bCol] = switchMode[Row][bCol] << 1 | switchMode[Row][Column];

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3)) //CLOCKWIZE TURN
        {
            switchTimer[Row][Column] = globalClock;

            if (pushState[biteButtonRow - 1][biteButtonCol - 1] && !biteButtonBit1 && !biteButtonBit2) //Engage in bite mode
            {
                biteButtonBit1 = true;
            }
            else if (!(!biteButtonBit1 && !biteButtonBit2)) //If we're in bite mode
            {
                if (biteButtonBit1 && !biteButtonBit2)
                {
                    bitePoint = bitePoint - 100;
                    if (bitePoint < 0)
                    {
                        bitePoint = 1000;
                    }
                }
                else if (!biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint - 10;
                    if (bitePoint < 0)
                    {
                        bitePoint = 1000;
                    }
                }
                else if (biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint - 1;
                    if (bitePoint < 0)
                    {
                        bitePoint = 1000;
                    }
                }
            }
            else
            {
                if ((!toggleTimer[Row][bCol]) == 1)
                {
                    toggleTimer[Row][Column] --; //Counter for position switch
                    //Keep the counters in place
                     if (toggleTimer[Row][Column] < 0)
                    {
                        toggleTimer[Row][Column] = 11;
                    }
                    #if (USING_CAT24C512 == 1 || USING_32U4EEPROM == 1 || USING_CB1 == 1)
                      if (DDS_s_init)
                      {
                        toggleTimer[Row][Column] = read16bitFromEEPROM(DDS_s);
                        DDS_s_init = false;
                      }
                      write16bitToEEPROM(DDS_s, toggleTimer[Row][Column]);
                    #endif
                }
                switchModeLock[Row][bCol] = !switchModeLock[Row][bCol]; //For MODE 4
                if (pushState[modButtonRow - 1][modButtonCol - 1] == 1) //MODE CHANGE
                {
                    for (int i = 0; i < 24; i++) //Reset all buttons
                    {
                        Joystick.releaseButton(i + buttonNumber[Row][Column]);
                    }
                    Joystick.releaseButton(buttonNumber[Row][bCol]);
                    Joystick.releaseButton(1 + buttonNumber[Row][bCol]);
                    latchLock[ddButtonRow - 1][ddButtonCol - 1] = false; //Reset DDButton
                    latchState[ddButtonRow - 1][ddButtonCol - 1] = false;
                    toggleTimer[Row][bCol] --; //Mode counter
                    if (toggleTimer[Row][bCol] == 1) //Skipping closed DDS mode
                    {
                        toggleTimer[Row][bCol] = 0;
                    }
                }
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1)) //COUNTER CLOCKWIZE TURN
        {
            switchTimer[Row][bCol] = globalClock;

            if (pushState[biteButtonRow - 1][biteButtonCol - 1] && !biteButtonBit1 && !biteButtonBit2) //Engage in bite mode
            {
                biteButtonBit1 = true;
            }
            else if (!(!biteButtonBit1 && !biteButtonBit2)) //If we're in bite mode
            {
                if (biteButtonBit1 && !biteButtonBit2)
                {
                    bitePoint = bitePoint + 100;
                    if (bitePoint > 1000)
                    {
                        bitePoint = 1000;
                    }
                    else if (bitePoint == 1000)
                    {
                        bitePoint = 0;
                    }
                }
                else if (!biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint + 10;
                    if (bitePoint > 1000)
                    {
                        bitePoint = 1000;
                    }
                    else if (bitePoint == 1000)
                    {
                        bitePoint = 0;
                    }
                }
                else if (biteButtonBit1 && biteButtonBit2)
                {
                    bitePoint = bitePoint + 1;
                    if (bitePoint > 1000)
                    {
                        bitePoint = 1000;
                    }
                    else if (bitePoint == 1000)
                    {
                        bitePoint = 0;
                    }
                }
            }
            else
            {
                if ((!toggleTimer[Row][bCol]) == 1)
                {
                    toggleTimer[Row][Column] ++;
                    //Keep the counters in place
                    if (toggleTimer[Row][Column] > 11)
                    {
                        toggleTimer[Row][Column] = 0;
                    }
                    #if (USING_CAT24C512 == 1 || USING_32U4EEPROM == 1 || USING_CB1 == 1)
                      if (DDS_s_init)
                      {
                        toggleTimer[Row][Column] = read16bitFromEEPROM(DDS_s);
                        DDS_s_init = false;
                      }
                      write16bitToEEPROM(DDS_s, toggleTimer[Row][Column]);
                    #endif
                }
                switchModeLock[Row][Column] = !switchModeLock[Row][Column]; //For MODE 4
                if (pushState[modButtonRow - 1][modButtonCol - 1] == 1) //MODE CHANGE
                {
                    for (int i = 0; i < 24; i++) //Reset all buttons
                    {
                        Joystick.releaseButton(i + buttonNumber[Row][Column]);
                    }
                    Joystick.releaseButton(buttonNumber[Row][bCol]);
                    Joystick.releaseButton(1 + buttonNumber[Row][bCol]);
                    latchLock[ddButtonRow - 1][ddButtonCol - 1] = false; //Reset DDButton
                    latchState[ddButtonRow - 1][ddButtonCol - 1] = false;
                    toggleTimer[Row][bCol] ++; //Mode counter
                    if (toggleTimer[Row][bCol] == 1) //Skipping closed DDS mode
                    {
                        toggleTimer[Row][bCol] = 2;
                    }
                }
            }
        }
    }
    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    if (toggleTimer[Row][bCol] > 3)
    {
        toggleTimer[Row][bCol] = 0;
        latchState[hybridButtonRow - 1][hybridButtonCol - 1] = 0; //Resetting hybrid button on entering this mode
    }
    else if (toggleTimer[Row][bCol] < 0)
    {
        toggleTimer[Row][bCol] = 3;
    }
    if (toggleTimer[Row][bCol] == 0 && latchState[hybridButtonRow - 1][hybridButtonCol - 1])
    {
        toggleTimer[Row][bCol] = 1;
    }
    else if (toggleTimer[Row][bCol] == 1 && !latchState[hybridButtonRow - 1][hybridButtonCol - 1])
    {
        toggleTimer[Row][bCol] = 0;
    }


    //MODE 1: DDS open
    if (toggleTimer[Row][bCol] == 0)
    {

        if (latchState[ddButtonRow - 1][ddButtonCol - 1])
        {
            for (int i = 0; i < 12; i++) //Remove the remnants from SWITCH MODE 1
            {
                Joystick.releaseButton(i + buttonNumber[Row][Column]);
            }
        }
        for (int i = 0; i < 24; i++)
        {
            if (i == toggleTimer[Row][Column])
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
        }
    }

    //MODE 2 / MODE 3: INCREMENTAL

    if ((toggleTimer[Row][bCol] == 1 || toggleTimer[Row][bCol] == 2) && !biteButtonBit1 && !biteButtonBit2)
    {
        Number = buttonNumber[Row][bCol];
        Joystick.setButton(Number, (globalClock - switchTimer[Row][Column] < funkyPulse));
        Joystick.setButton(Number + 1, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }

    //MODE 4: TOGGLE SWITCHES

    if (toggleTimer[Row][bCol] == 3)
    {
        Number = buttonNumber[Row][bCol];
        Joystick.setButton(Number, switchModeLock[Row][bCol]);
        Joystick.setButton(Number + 1, switchModeLock[Row][Column]);;
    }

    //Pushing switch mode

    switchMode[Row][Column] = (toggleTimer[Row][bCol] & 0b00000001);
    switchMode[Row][bCol] = (toggleTimer[Row][bCol] & 0b00000010) >> 1;

    long push = 0;
    push = push | toggleTimer[Row][bCol];
    push = push << (2*(FieldPlacement - 1));
    rotaryField = rotaryField | push;
}


void funkyBrightness(int Arow, int Acol, int Bcol, bool reverse) {

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = Bcol - 1;

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              LEDBrightness = LEDBrightness + 2 - (4*reverse);
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              LEDBrightness = LEDBrightness - 2 + (4*reverse);
            }
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    //Adjustment
    if (LEDBrightness < 0)
    {
      LEDBrightness = 0;
    }
    else if (LEDBrightness > 100)
    {
      LEDBrightness = 100;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }
}

void funkyBrake(int Arow, int Acol, int Bcol, bool reverse) {

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = Bcol - 1;

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              brakeMagicValue = brakeMagicValue + 10 - (20*reverse);
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              brakeMagicValue = brakeMagicValue - 10 + (20*reverse);
            }
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    //Adjustment
    if (brakeMagicValue < 0)
    {
      brakeMagicValue = 0;
    }
    else if (brakeMagicValue > 1000)
    {
      brakeMagicValue = 1000;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }
}

void funkyPreset(int Arow, int Acol, int Bcol, bool reverse) {

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = Bcol - 1;

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              if(switchPreset == 0 && reverse)
              {
                switchPreset = 11;
              }
              else
              {
                switchPreset = switchPreset + 1 - (2 * reverse);
              }
              if (switchPreset > 11)
              {
                  switchPreset = 0;
              }

              presets(switchPreset);
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              if(switchPreset == 0 && !reverse)
              {
                switchPreset = 11;
              }
              else
              {
                switchPreset = switchPreset - 1 + (2 * reverse);
              }
              
              if (switchPreset > 11)
              {
                  switchPreset = 0;
              }
              presets(switchPreset);
            }
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }

    long push = 0;
    push = push | (switchPreset << 10);
    buttonField = buttonField | push;

}

void funkyThrottle(int Arow, int Acol, int Bcol, bool reverse) {

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = Bcol - 1;

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              throttleHoldValue = throttleHoldValue + 10 - (20*reverse);
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              throttleHoldValue = throttleHoldValue - 10 + (20*reverse);
            }
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    //Adjustment
    if (throttleHoldValue < 0)
    {
      throttleHoldValue = 0;
    }
    else if (throttleHoldValue > 1000)
    {
      throttleHoldValue = 1000;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }
}


void funkyBiteAdjust(int Arow, int Acol, int Bcol, bool reverse, int increment) {

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = Bcol - 1;

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
    }
    else if (rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 4;
        latchLock[Row][bCol] = 1; //Fetching 10
    }

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
            if(pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
            {
              bitePoint = bitePoint + increment  - (reverse * 2 * increment);
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
            if(pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
            {
              bitePoint = bitePoint - increment  + (reverse * 2 * increment);
            }
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    //Adjustment
    if (bitePoint > 1000)
    {
      bitePoint = 1000;  
    }
    else if (bitePoint < 0)
    {
      bitePoint = 0;
    }

    if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 0)
    {
    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }
}
