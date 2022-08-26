void PEC11(int row, int col, bool reverse) {

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }


    Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
    Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
}