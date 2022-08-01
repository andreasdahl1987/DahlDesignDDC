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
