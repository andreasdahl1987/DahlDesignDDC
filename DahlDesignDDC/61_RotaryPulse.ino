void rotary2Pulse(int row, int column, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];

    if ((Pin1 == 1 || Pin2 == 1) && (globalClock - switchTimer[Row][Column]) > (pulseEncCD + pulseEncDuration) && (globalClock - switchTimer[Row][Column + 1]) > (pulseEncCD + pulseEncDuration))
    {
        if (Pin1 == 1)
        {
            switchTimer[Row][Column] = globalClock;
        }
        else
        {
            switchTimer[Row][Column + 1] = globalClock;
        }
    }

    if ((globalClock - switchTimer[Row][Column]) < pulseEncCD)
    {
        toggleTimer[Row][Column] = globalClock;
    }
    if ((globalClock - switchTimer[Row][Column + 1]) < pulseEncCD)
    {
        toggleTimer[Row][Column + 1] = globalClock;
    }


    if ((globalClock - toggleTimer[Row][Column]) < pulseEncDuration)
    {
        Joystick.setButton(Number + reverse, 1);
    }
    else
    {
        Joystick.setButton(Number + reverse, 0);
    }

    if ((globalClock - toggleTimer[Row][Column + 1]) < pulseEncDuration)
    {
        Joystick.setButton(Number + 1 - reverse, 1);
    }
    else
    {
        Joystick.setButton(Number + 1 - reverse, 0);
    }
}
