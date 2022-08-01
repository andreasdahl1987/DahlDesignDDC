//------------------------------
//------BUTTON FUNCTIONS--------
//------------------------------

void pushButton(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];

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

void pushButtonM(int8_t row, int8_t column, int8_t fieldPlacement)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];
    int8_t FieldPlacement = fieldPlacement;

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


void pushButtonL(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];

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

    Joystick.setButton(Number, latchState[Row][Column]);
}
