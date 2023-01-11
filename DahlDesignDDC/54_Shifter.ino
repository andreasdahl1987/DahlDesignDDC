void pushPull(int rightPullRow, int rightPullCol, int rightPushRow, int rightPushCol, int leftPullRow, int leftPullCol, int leftPushRow, int leftPushCol, int fieldPlacement)
{
    int8_t RightPullRow = rightPullRow - 1;
    int8_t RightPullCol = rightPullCol - 1;
    int8_t RightPushRow = rightPushRow - 1;
    int8_t RightPushCol = rightPushCol - 1;
    int8_t LeftPullRow = leftPullRow - 1;
    int8_t LeftPullCol = leftPullCol - 1;
    int8_t LeftPushRow = leftPushRow - 1;
    int8_t LeftPushCol = leftPushCol - 1;

    int8_t FieldPlacement = fieldPlacement;

    int8_t Number = buttonNumber[RightPullRow][RightPullCol];

    //Debounce for all switches

    //Right pull
    if (pushState[RightPullRow][RightPullCol] != rawState[RightPullRow][RightPullCol] && (globalClock - switchTimer[RightPullRow][RightPullCol]) > buttonCooldown)
    {
        switchTimer[RightPullRow][RightPullCol] = globalClock;
        pushState[RightPullRow][RightPullCol] = rawState[RightPullRow][RightPullCol];
    }

    if ((globalClock - switchTimer[RightPullRow][RightPullCol]) > buttonCooldown)
    {
        pushState[RightPullRow][RightPullCol] = rawState[RightPullRow][RightPullCol];
    }

    //Right push

    if (pushState[RightPushRow][RightPushCol] != rawState[RightPushRow][RightPushCol] && (globalClock - switchTimer[RightPushRow][RightPushCol]) > buttonCooldown)
    {
        switchTimer[RightPushRow][RightPushCol] = globalClock;
        pushState[RightPushRow][RightPushCol] = rawState[RightPushRow][RightPushCol];
    }

    if ((globalClock - switchTimer[RightPushRow][RightPushCol]) > buttonCooldown)
    {
        pushState[RightPushRow][RightPushCol] = rawState[RightPushRow][RightPushCol];
    }

    //Left pull
    if (pushState[LeftPullRow][LeftPullCol] != rawState[LeftPullRow][LeftPullCol] && (globalClock - switchTimer[LeftPullRow][LeftPullCol]) > buttonCooldown)
    {
        switchTimer[LeftPullRow][LeftPullCol] = globalClock;
        pushState[LeftPullRow][LeftPullCol] = rawState[LeftPullRow][LeftPullCol];
    }

    if ((globalClock - switchTimer[LeftPullRow][LeftPullCol]) > buttonCooldown)
    {
        pushState[LeftPullRow][LeftPullCol] = rawState[LeftPullRow][LeftPullCol];
    }

    //Left push

    if (pushState[LeftPushRow][LeftPushCol] != rawState[LeftPushRow][LeftPushCol] && (globalClock - switchTimer[LeftPushRow][LeftPushCol]) > buttonCooldown)
    {
        switchTimer[LeftPushRow][LeftPushCol] = globalClock;
        pushState[LeftPushRow][LeftPushCol] = rawState[LeftPushRow][LeftPushCol];
    }

    if ((globalClock - switchTimer[LeftPushRow][LeftPushCol]) > buttonCooldown)
    {
        pushState[LeftPushRow][LeftPushCol] = rawState[LeftPushRow][LeftPushCol];
    }


    //Change switch mode
    if (pushState[RightPullRow][RightPullCol] == 0)
    {
        switchModeLock[RightPullRow][RightPullCol] = false;
    }

    if (pushState[RightPullRow][RightPullCol] == 1 && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && !switchModeLock[RightPullRow][RightPullCol])
    {
        switchModeLock[RightPullRow][RightPullCol] = true;
        switchMode[RightPullRow][RightPullCol] = !switchMode[RightPullRow][RightPullCol];
        latchLock[RightPullRow][RightPullCol] = false;
        latchState[RightPullRow][RightPullCol] = false;
    }

    //Push switch mode
    long push = 0;
    push = push | switchMode[RightPullRow][RightPullCol];
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;

    //SWITCH MODE 1: Complex
    if (!switchMode[RightPullRow][RightPullCol])
    {
        Joystick.setButton(Number, pushState[RightPullRow][RightPullCol]);
        Joystick.setButton(Number + 1, pushState[LeftPullRow][LeftPullCol]);

        if (pushState[RightPullRow][RightPullCol] == 0)
        {
            Joystick.setButton(Number, pushState[LeftPushRow][LeftPushCol]);
        }

        if (pushState[LeftPullRow][LeftPullCol] == 0)
        {
            Joystick.setButton(Number + 1, pushState[RightPushRow][RightPushCol]);
        }

        Joystick.setButton(Number + 2, 0);
        Joystick.setButton(Number + 3, 0);

    }
    //SWITCH MODE 2: Individual
    else if (switchMode[RightPullRow][RightPullCol])
    {
        Joystick.setButton(Number, pushState[RightPullRow][RightPullCol]);
        Joystick.setButton(Number + 2, pushState[RightPushRow][RightPushCol]);
        Joystick.setButton(Number + 1, pushState[LeftPullRow][LeftPullCol]);
        Joystick.setButton(Number + 3, pushState[LeftPushRow][LeftPushCol]);
    }

    //Handbrake

    if (handbrake)
    {
        Joystick.setBrake(1000);
    }
    else
    {
        Joystick.setBrake(0);
    }

    if (pushState[RightPullRow][RightPullCol] == 0 || pushState[LeftPullRow][LeftPullCol] == 0)
    {
        handbrakeLock = false;
    }

    if (!handbrakeLock && pushState[RightPullRow][RightPullCol] == 1 && pushState[LeftPullRow][LeftPullCol] == 1)
    {
        handbrakeTimer = globalClock;
        handbrakeLock = true;
    }

    else if (handbrakeLock && globalClock - handbrakeTimer > 1000)
    {
        handbrake = true;
        handbrakeLock = false;
    }

    if (pushState[RightPushRow][RightPushCol] == 0 && pushState[LeftPushRow][LeftPushCol] == 0)
    {
        handbrakeRelease = false;
    }

    if (!handbrakeRelease && pushState[RightPushRow][RightPushCol] == 1 && pushState[LeftPushRow][LeftPushCol] == 1)
    {
        handbrakeTimer = globalClock;
        handbrakeRelease = true;
    }

    else if (handbrakeRelease && globalClock - handbrakeTimer > 1000)
    {
        handbrake = false;
        handbrakeRelease = false;
    }

    //Push handbrake
    long pesh = 0;
    pesh = pesh | handbrake;
    pesh = pesh << 9;
    buttonField = buttonField | pesh;
}

void upshift(int8_t row, int8_t column, int cooldown)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > cooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > cooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    Joystick.setButton(Number, pushState[Row][Column]);
}

