void throttleHoldSW1(int8_t buttonRow, int8_t buttonCol, int8_t rotaryRow, int8_t rotaryColA, int rotaryColB, bool reverse)
{
    int8_t ButtonRow = buttonRow - 1;
    int8_t ButtonCol = buttonCol - 1;
    int Row = rotaryRow - 1;
    int Column = rotaryColA - 1;
    int Number = buttonNumber[rotaryRow][rotaryColA];

    int bCol = rotaryColB - 1;
    
    int8_t Reverse = reverse;

    //Button logics
    if (pushState[ButtonRow][ButtonCol] != rawState[ButtonRow][ButtonCol] && (globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        switchTimer[ButtonRow][ButtonCol] = globalClock;
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if ((globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }


    //Encoder logics
    if (!rawState[Row][Column] && !rawState[Row][bCol])
    {
        pushState[Row][Column] = 1;
    }
    else if (!rawState[Row][Column] && rawState[Row][bCol])
    {
        pushState[Row][Column] = 2;
        latchLock[Row][Column] = 1; //Fetching 01
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

    if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
    {
        if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
        {
            switchTimer[Row][Column] = globalClock;

            if (brakeMagicOn)
            {
                brakeMagicValue = brakeMagicValue + 10 - (20 * Reverse);
            }
            else if (pushState[ButtonRow][ButtonCol] == 1)
            {
                throttleHoldValue = throttleHoldValue + 10 - (20 * Reverse);
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
            if (brakeMagicOn)
            {
                brakeMagicValue = brakeMagicValue - 10 + (20 * Reverse);
            }
            else if (pushState[ButtonRow][ButtonCol] == 1)
            {
                throttleHoldValue = throttleHoldValue - 10 + (20 * Reverse);
            }
            
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }
    if (!brakeMagicOn && pushState[ButtonRow][ButtonCol] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }

    //Adjusting 
    if (brakeMagicValue < 0)
    {
      brakeMagicValue = 0;
    }
    else if (brakeMagicValue > 1000)
    {
      brakeMagicValue = 1000;
    }

    if (throttleHoldValue < 0)
    {
      throttleHoldValue = 0;
    }
    else if (throttleHoldValue > 1000)
    {
      throttleHoldValue = 1000;
    }

    
    if (pushState[ButtonRow][ButtonCol] == 1)
    {
        Joystick.setThrottle(throttleHoldValue);
    }
    else
    {
        Joystick.setThrottle(0);
    }

    long push = pushState[ButtonRow][ButtonCol];
    push = push << 5;
    buttonField = buttonField | push;
}

void throttleHoldT(int8_t buttonRow, int8_t buttonCol, int8_t rotaryRow, int8_t rotaryCol, bool reverse)
{
    int8_t ButtonRow = buttonRow - 1;
    int8_t ButtonCol = buttonCol - 1;
    int8_t Row = rotaryRow - 1;
    int8_t Column = rotaryCol - 1;
    int8_t Number = buttonNumber[Row][Column];
    int8_t Reverse = reverse;

    //Button logics
    if (pushState[ButtonRow][ButtonCol] != rawState[ButtonRow][ButtonCol] && (globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        switchTimer[ButtonRow][ButtonCol] = globalClock;
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if ((globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

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
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //Make sure we dont do this again
            latchLock[Row][Column] = false;

            int8_t difference = pushState[Row][Column + 1];
            if ((difference > 0 && difference < 2) || difference < -2)
            {
                if (brakeMagicOn)
                {
                    brakeMagicValue = brakeMagicValue + 10 - (20 * Reverse);
                }
                else if (pushState[ButtonRow][ButtonCol] == 1)
                {
                    throttleHoldValue = throttleHoldValue + 10 - (20 * Reverse);
                }
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                if (brakeMagicOn)
                {
                    brakeMagicValue = brakeMagicValue - 10 + (20 * Reverse);
                }
                else if (pushState[ButtonRow][ButtonCol] == 1)
                {
                    throttleHoldValue = throttleHoldValue - 10 + (20 * Reverse);
                }
            }
        }
    }

    //Adjusting 
    if (brakeMagicValue < 0)
    {
      brakeMagicValue = 0;
    }
    else if (brakeMagicValue > 1000)
    {
      brakeMagicValue = 1000;
    }

    if (throttleHoldValue < 0)
    {
      throttleHoldValue = 0;
    }
    else if (throttleHoldValue > 1000)
    {
      throttleHoldValue = 1000;
    }

    int8_t difference = pushState[Row][Column + 1];
    if (difference != 0 && !brakeMagicOn && pushState[ButtonRow][ButtonCol] == 0)
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

    if (pushState[ButtonRow][ButtonCol] == 1)
    {
        Joystick.setThrottle(throttleHoldValue);
    }
    else
    {
        Joystick.setThrottle(0);
    }

    long push = pushState[ButtonRow][ButtonCol];
    push = push << 5;
    buttonField = buttonField | push;
}

void throttleHoldM(int8_t buttonRow, int8_t buttonCol, int8_t rotaryRow, int8_t rotaryCol, bool reverse)
{
    int8_t ButtonRow = buttonRow - 1;
    int8_t ButtonCol = buttonCol - 1;
    int8_t Row = rotaryRow - 1;
    int8_t Column = rotaryCol - 1;
    int8_t Number = buttonNumber[Row][Column];
    int8_t Reverse = reverse;

    if (pushState[ButtonRow][ButtonCol] != rawState[ButtonRow][ButtonCol] && (globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        switchTimer[ButtonRow][ButtonCol] = globalClock;
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if ((globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if (pushState[ButtonRow][ButtonCol] == 0)
    {
        latchLock[ButtonRow][ButtonCol] = false;
    }

    if (pushState[ButtonRow][ButtonCol] == 1 && !latchLock[ButtonRow][ButtonCol])
    {
        latchLock[ButtonRow][ButtonCol] = true;
        latchState[ButtonRow][ButtonCol] = !latchState[ButtonRow][ButtonCol];
    }

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
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //Make sure we dont do this again
            latchLock[Row][Column] = false;

            int8_t difference = pushState[Row][Column + 1];
            if ((difference > 0 && difference < 2) || difference < -2)
            {
                if (brakeMagicOn)
                {
                    brakeMagicValue = brakeMagicValue + 10 - (20 * Reverse);
                }
                else if (latchState[ButtonRow][ButtonCol])
                {
                    throttleHoldValue = throttleHoldValue + 10 - (20 * Reverse);
                }
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                if (brakeMagicOn)
                {
                    brakeMagicValue = brakeMagicValue - 10 + (20 * Reverse);
                }
                else if (latchState[ButtonRow][ButtonCol])
                {
                    throttleHoldValue = throttleHoldValue - 10 + (20 * Reverse);
                }
            }
        }
    }

    //Adjusting 
    if (brakeMagicValue < 0)
    {
      brakeMagicValue = 0;
    }
    else if (brakeMagicValue > 1000)
    {
      brakeMagicValue = 1000;
    }

    if (throttleHoldValue < 0)
    {
      throttleHoldValue = 0;
    }
    else if (throttleHoldValue > 1000)
    {
      throttleHoldValue = 1000;
    }

    int8_t difference = pushState[Row][Column + 1];
    if (difference != 0 && !brakeMagicOn && !latchState[ButtonRow][ButtonCol])
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

    if (latchState[ButtonRow][ButtonCol])
    {
        Joystick.setThrottle(throttleHoldValue);
    }
    else
    {
        Joystick.setThrottle(0);
    }

    long push = latchState[ButtonRow][ButtonCol];
    push = push << 5;
    buttonField = buttonField | push;
}
