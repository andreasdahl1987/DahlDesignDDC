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

void neutralButton(int row, int column)
{
    neutralButtonRow = row;
    neutralButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = 15;
    int ActivePlacement = 16;

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

void biteButton(int row, int column)
{
    Joystick.setRyAxisRange(0, 1000);

    biteButtonRow = row;
    biteButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = 6;

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
        }
    }
    //Push bite setting level
    long push = 0;
    push = push | biteButtonBit1;
    push = push | (biteButtonBit2 << 1);
    push = push << (2*(FieldPlacement - 1));
    rotaryField = rotaryField | push;

    Joystick.setRyAxis(bitePoint);
    Joystick.setButton(Number, pushState[Row][Column]);
}