void wildInc(int row, int col, bool pinSwitch, bool reverse) 
{
    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int bCol = col;

    if (pinSwitch)
    {
      Column = col;
      bCol = col -1;
    }

    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        //latchLock[Row][Column] = 1; //Fetching 01
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

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown) && !latchLock[Row][Column])
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (pushState[Row][bCol] == 1 && pushState[Row][Column] == 3 && !latchLock[Row][bCol]))
        {
            switchTimer[Row][Column] = globalClock;
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (pushState[Row][bCol] == 3 && pushState[Row][Column] == 1 && !latchLock[Row][bCol]))
        {
            switchTimer[Row][bCol] = globalClock;
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
        if (pushState[Row][Column] == 1 || pushState[Row][Column] == 3)
        {
          pushState[Row][bCol] = pushState[Row][Column];
        }
    }

    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
}
