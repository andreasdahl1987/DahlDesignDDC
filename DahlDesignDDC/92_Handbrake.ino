void handbrakeL(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
        if (pushState[Row][Column] == 0)
        {
            Joystick.setBrake(0);
        }
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

    if (latchState[Row][Column] == 1)
    {
        Joystick.setBrake(1000);
    };

    //Push handbrake
    long push = 0;
    push = push | latchState[Row][Column];
    push = push << 9;
    buttonField = buttonField | push;
}

void handbrakeM(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
        if (pushState[Row][Column] == 0)
        {
            Joystick.setBrake(0);
        }
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }
    if (pushState[Row][Column] == 1)
    {
        Joystick.setBrake(1000);
    }

    //Push handbrake
    long push = 0;
    push = push | pushState[Row][Column];
    push = push << 9;
    buttonField = buttonField | push;
}
