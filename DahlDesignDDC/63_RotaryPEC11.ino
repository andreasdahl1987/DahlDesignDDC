void PEC11(int row, int col, bool reverse) {

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    if (!rawState[Row][Column] && !rawState[Row][Column + 1])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][Column + 1])
    {
        pushState[Row][Column] = 2;
        if ((globalClock - switchTimer[Row][Column] > PEC11Cooldown) && (globalClock - switchTimer[Row][Column + 1] > PEC11Cooldown))
        {
            latchLock[Row][Column] = 1; //Fetching 01 only if we're not cooling down
        }
    }
    else if (rawState[Row][Column] && rawState[Row][Column + 1])
    {
        pushState[Row][Column] = 3;
    }
    else if (rawState[Row][Column] && !rawState[Row][Column + 1])
    {
        pushState[Row][Column] = 4;
        if ((globalClock - switchTimer[Row][Column] > PEC11Cooldown) && (globalClock - switchTimer[Row][Column + 1] > PEC11Cooldown))
        {
            latchLock[Row][Column + 1] = 1; //Fetching 10 only if we're not cooling down
        }

    }

    if ((globalClock - switchTimer[Row][Column] > PEC11Cooldown) && (globalClock - switchTimer[Row][Column + 1] > PEC11Cooldown))
    {
        if ((latchLock[Row][Column + 1] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;
            latchLock[Row][Column + 1] = 0;
            latchLock[Row][Column] = 0;
        }

        else if ((latchLock[Row][Column + 1] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][Column + 1] = globalClock;
            latchLock[Row][Column + 1] = 0;
            latchLock[Row][Column] = 0;
        }
    }

    Joystick.setButton(Number + Reverse, (globalClock - switchTimer[Row][Column] < PEC11Pulse));
    Joystick.setButton(Number + 1 - Reverse, (globalClock - switchTimer[Row][Column + 1] < PEC11Pulse));
}