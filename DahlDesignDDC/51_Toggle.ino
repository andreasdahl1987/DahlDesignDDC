//------------------------------
//------TOGGLE FUNCTIONS--------
//------------------------------

void toggle(int row, int column)
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

    Joystick.setButton(Number, pushState[Row][Column]);
}

void toggleP(int row, int column)
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

    if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
    {
        toggleTimer[Row][Column] = globalClock;
    }

    if ((globalClock - toggleTimer[Row][Column]) < togglePulse)
    {
        Joystick.setButton(Number, 1);
    }
    else
    {
        Joystick.setButton(Number, 0);
    }
}

void toggleM(int row, int column, int fieldPlacement)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
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

    //Change switch mode
    if (pushState[Row][Column] == 0)
    {
        switchModeLock[Row][Column] = false;
    }

    if (((globalClock - switchTimer[Row][Column]) < buttonCooldown) && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && FieldPlacement != 0 && !switchModeLock[Row][Column])
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

    //SWITCH MODE 1: TOGGLE
    if (!switchMode[Row][Column])
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }

    //SWITCH MODE 2: PULSE
    if (switchMode[Row][Column])
    {
        if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
        {
            toggleTimer[Row][Column] = globalClock;
        }

        if ((globalClock - toggleTimer[Row][Column]) < togglePulse)
        {
            Joystick.setButton(Number, 1);
        }
        else
        {
            Joystick.setButton(Number, 0);
        }
    }
}
