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

void PEC11Bite(int row, int col, bool reverse) {

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

        //----------------------------------------------
        //----------------BITE POINT SETTING------------
        //----------------------------------------------

        if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
        {
            if (!biteButtonBit1 && !biteButtonBit2)
            {
                biteButtonBit1 = true;
            }
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
        if (biteButtonBit1 || biteButtonBit2)
        {
            latchState[Row][Column] = true;
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if (biteButtonBit1 || biteButtonBit2)
        {
            latchState[Row][Column + 1] = true;
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Changing bite point

    if (latchState[Row][Column + 1]) //CW add to bite
    {
        if (biteButtonBit1 && !biteButtonBit2)
        {
            bitePoint = bitePoint + 100;
            if (bitePoint > 1000)
            {
                bitePoint = 1000;
            }
        }
        else if (!biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint + 10;
            if (bitePoint > 1000)
            {
                bitePoint = 1000;
            }
        }
        else if (biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint + 1;
            if (bitePoint > 1000)
            {
                bitePoint = 1000;
            }
        }
        latchState[Row][Column + 1] = false;
    }
    else if (latchState[Row][Column]) //CCW reduce bite
    {
        if (biteButtonBit1 && !biteButtonBit2)
        {
            bitePoint = bitePoint - 100;
            if (bitePoint < 0)
            {
                bitePoint = 0;
            }
        }
        else if (!biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint - 10;
            if (bitePoint < 0)
            {
                bitePoint = 0;
            }
        }
        else if (biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint - 1;
            if (bitePoint < 0)
            {
                bitePoint = 0;
            }
        }
        latchState[Row][Column] = false;
    }
    Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
    Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
}

void PEC11Brightness(int row, int col, bool reverse) {

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
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          LEDBrightness = LEDBrightness + 2 - (4*Reverse);
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          LEDBrightness = LEDBrightness - 2 + (4*Reverse);
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Adjustment
    if (LEDBrightness < 0)
    {
      LEDBrightness = 0;
    }
    else if (LEDBrightness > 100)
    {
      LEDBrightness = 100;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
    }

}
