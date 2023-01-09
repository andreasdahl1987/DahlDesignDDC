//--------------------------
//-------PRESET SWITCH------
//--------------------------

void preset2Bit(int row, int column, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int Reverse = reverse;

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];

    bool array[2] = { Pin1, Pin2 };

    int pos = 0;

    for (int i = 0; i < 2; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > (encoder2Wait + encoder2Pulse + encoderCooldown))
        {
            switchTimer[Row][Column] = globalClock;
            latchLock[Row][Column] = true;
        }
        else if ((globalClock - switchTimer[Row][Column] > encoder2Wait) && latchLock[Row][Column])
        {
            //----------------------------------------------
            //----------------PRESET CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.

            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            int8_t difference = pushState[Row][Column + 1];

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                if ((difference > 0 && difference < 2) || difference < -2)
                {
                    switchPreset = switchPreset + 1 - (2 * Reverse);
                }
                else if ((difference < 0 && difference > -2) || difference > 2)
                {
                    switchPreset = switchPreset - 1 + (2 * Reverse);
                }
                if (switchPreset < 0)
                {
                    switchPreset = 11;
                }
                if (switchPreset > 11)
                {
                    switchPreset = 0;
                }

                presets(switchPreset);
            }

            //Give new value to pushState
            pushState[Row][Column] = result;
            //Make sure we dont do this again
            latchLock[Row][Column] = false;
        }
    }

    int8_t difference = pushState[Row][Column + 1];

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
        if (difference != 0)
        {
            if (globalClock - switchTimer[Row][Column + 1] < encoder2Pulse + encoder2Wait)
            {
                if ((difference > 0 && difference < 2) || difference < -2)
                {
                    Joystick.setButton(Number + Reverse, 1);
                    Joystick.setButton(Number + 1 - Reverse, 0);
                }
                else if ((difference < 0 && difference > -2) || difference > 2)
                {
                    Joystick.setButton(Number + Reverse, 0);
                    Joystick.setButton(Number + 1 - Reverse, 1);
                }
                else
                {
                    pushState[Row][Column + 1] = 0;
                }
            }
            else
            {
                pushState[Row][Column + 1] = 0;
                pushState[Row][Column] = result;
                Joystick.setButton(Number, 0);
                Joystick.setButton(Number + 1, 0);
            }
        }
    }

    //Push preset

    long push = 0;
    push = push | (switchPreset << 10);
    buttonField = buttonField | push;
}

void presetNext(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;

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
        switchPreset++;
        if (switchPreset > 11)
        {
          switchPreset = 0;
        }
        presets(switchPreset);
    }
}

void presetPrevious(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;

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
        switchPreset--;
        if (switchPreset < 0)
        {
          switchPreset = 11;
        }
        presets(switchPreset);
    }
}