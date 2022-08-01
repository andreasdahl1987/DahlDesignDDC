//----------------------------
//----FUNKY DIRECTION PUSH----
//----------------------------

void funkyButton(int row, int column, int pCol, int Col1, int Col2, int Col3)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    int pcol = pCol - 1;
    int col1 = Col1 - 1;
    int col2 = Col2 - 1;
    int col3 = Col3 - 1;

    if (!pushState[Row][pcol] && !pushState[Row][col1] && !pushState[Row][col2] && !pushState[Row][col3])
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

void funkyButtonM(int row, int column, int fieldPlacement, int pCol, int Col1, int Col2, int Col3)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = fieldPlacement;

    int pcol = pCol - 1;
    int col1 = Col1 - 1;
    int col2 = Col2 - 1;
    int col3 = Col3 - 1;

    if (!pushState[Row][pcol] && !pushState[Row][col1] && !pushState[Row][col2] && !pushState[Row][col3])
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

void funkyButtonL(int row, int column, int pCol, int Col1, int Col2, int Col3)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    int pcol = pCol - 1;
    int col1 = Col1 - 1;
    int col2 = Col2 - 1;
    int col3 = Col3 - 1;

    if (!pushState[Row][pcol] && !pushState[Row][col1] && !pushState[Row][col2] && !pushState[Row][col3])
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

void funkyButtonHybrid(int row, int column, int pCol, int Col1, int Col2, int Col3)
{
    hybridButtonRow = row;
    hybridButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int pcol = pCol - 1;
    int col1 = Col1 - 1;
    int col2 = Col2 - 1;
    int col3 = Col3 - 1;

    if (!pushState[Row][pcol] && !pushState[Row][col1] && !pushState[Row][col2] && !pushState[Row][col3])
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

void funkyButtonDDButton(int row, int column, int pCol, int Col1, int Col2, int Col3)
{
    ddButtonRow = row;
    ddButtonCol = column;

    int Row = row - 1;
    int Column = column - 1;
    int pcol = pCol - 1;
    int col1 = Col1 - 1;
    int col2 = Col2 - 1;
    int col3 = Col3 - 1;

    if (!pushState[Row][pcol] && !pushState[Row][col1] && !pushState[Row][col2] && !pushState[Row][col3])
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