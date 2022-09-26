void quickSwitch(int8_t row, int8_t column)
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

    //Change switch mode
    if (pushState[Row][Column] == 0)
    {
        switchModeLock[Row][Column] = false;
    }

    if (pushState[Row][Column] == 1 && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && !switchModeLock[Row][Column])
    {
        switchModeLock[Row][Column] = true;
        switchMode[Row][Column] = !switchMode[Row][Column];
        latchLock[Row][Column] = false;
        latchState[Row][Column] = false;
        quickSwitchState = false;
    }

    //Push switch mode
    long pesh = 0;
    pesh = pesh | switchMode[Row][Column];
    pesh = pesh << 7;
    buttonField = buttonField | pesh;

    //SWITCH MODE 2: MOMENTARY BUTTON
    if (switchMode[Row][Column])
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }

    //SWITCH MODE 1: Quick switch
    else if (!switchMode[Row][Column])
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

        quickSwitchState = latchState[Row][Column];
    }

    //Push switch active
    long push = 0;
    push = push | quickSwitchState;
    push = push << 8;
    buttonField = buttonField | push;
}

void quickSwitch12(int8_t row, int8_t column, int8_t fieldPlacement)
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

    if (pushState[Row][Column] == 1 && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && !switchModeLock[Row][Column])
    {
        switchModeLock[Row][Column] = true;
        switchMode[Row][Column] = !switchMode[Row][Column];
        latchLock[Row][Column] = false;
        latchState[Row][Column] = false;
        quickSwitch12State = false;
    }

    //Push switch mode
    long pesh = 0;
    pesh = pesh | switchMode[Row][Column];
    pesh = pesh << (FieldPlacement-1);
    buttonField = buttonField | pesh;

    //SWITCH MODE 2: MOMENTARY BUTTON
    if (switchMode[Row][Column])
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }

    //SWITCH MODE 1: Quick switch
    else if (!switchMode[Row][Column])
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

        quickSwitch12State = latchState[Row][Column];
    }

    //Push switch active
    long push = 0;
    push = push | quickSwitch12State;
    push = push << (FieldPlacement);
    buttonField = buttonField | push;
}

void quickSwitch34(int8_t row, int8_t column, int8_t fieldPlacement)
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

    if (pushState[Row][Column] == 1 && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && !switchModeLock[Row][Column])
    {
        switchModeLock[Row][Column] = true;
        switchMode[Row][Column] = !switchMode[Row][Column];
        latchLock[Row][Column] = false;
        latchState[Row][Column] = false;
        quickSwitch34State = false;
    }

    //Push switch mode
    long pesh = 0;
    pesh = pesh | switchMode[Row][Column];
    pesh = pesh << (FieldPlacement - 1);
    buttonField = buttonField | pesh;

    //SWITCH MODE 2: MOMENTARY BUTTON
    if (switchMode[Row][Column])
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }

    //SWITCH MODE 1: Quick switch
    else if (!switchMode[Row][Column])
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

        quickSwitch34State = latchState[Row][Column];
    }

    //Push switch active
    long push = 0;
    push = push | quickSwitch34State;
    push = push << (FieldPlacement);
    buttonField = buttonField | push;
}
