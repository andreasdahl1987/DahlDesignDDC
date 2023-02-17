//------------------------------
//------ROTARY 2-BIT SWITCH-----
//------------------------------

void rotary2Modes(int row, int column, int fieldPlacement, int hybridPositions, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = fieldPlacement;
    int HyPos = hybridPositions;
    int Reverse = reverse;
    int maxPos = max(4, HyPos);

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
            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                for (int i = 0; i < maxPos + 1; i++) //Remove the remnants from SWITCH MODE 1
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                if (switchMode[Row][Column] && switchMode[Row][Column + 1]) //EXIT from switch mode 4
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = false;
                }
                else //Rotate between switch modes 1-3
                {
                    switchMode[Row][Column] = !switchMode[Row][Column];
                    if (!switchMode[Row][Column]) //Moving into hybrid mode, set hybrid button to 0
                    {
                        switchMode[Row][Column + 1] = true;
                        latchState[hybridButtonRow - 1][hybridButtonCol - 1] = 0;
                    }
                    else
                    {
                        if (switchMode[Row][Column + 1])
                        {
                            switchMode[Row][Column + 1] = false;
                            switchMode[Row][Column] = false;
                        }
                    }
                }
            }

            //If we're in open hybrid, change counter
            if (!switchMode[Row][Column] && switchMode[Row][Column + 1])
            {
                int8_t difference = pushState[Row][Column + 1];
                if ((difference > 0 && difference < 2) || difference < -2)
                {
                    toggleTimer[Row][Column] = toggleTimer[Row][Column] + 1 - (2 * Reverse);
                }
                else if ((difference < 0 && difference > -2) || difference > 2)
                {
                    toggleTimer[Row][Column] = toggleTimer[Row][Column] - 1 + (2 * Reverse);
                }
                if (toggleTimer[Row][Column] < 0)
                {
                    toggleTimer[Row][Column] = HyPos;
                }
            }

            //If we're not in hybrid at all, reset counter
            else if (!switchMode[Row][Column + 1])
            {
                toggleTimer[Row][Column] = 0;
            }
        }
    }

    //If we're in hybrid, able to set open/closed hybrid
    if (switchMode[Row][Column + 1])
    {
        switchMode[Row][Column] = latchState[hybridButtonRow - 1][hybridButtonCol - 1];
    }

    //SWITCH MODE 1: 4 - position switch

    if (!switchMode[Row][Column] && !switchMode[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 0; //Refreshing encoder mode difference

        for (int i = 0; i < 5; i++)
        {
            if (i == pushState[Row][Column])
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
        }
    }

    //SWITCH MODE 2/4: Incremental encoder or closed hybrid

    else if (switchMode[Row][Column])
    {
        Number = buttonNumber[Row][Column + 1];
        int8_t difference = pushState[Row][Column + 1];
        if (difference != 0)
        {
            if (globalClock - switchTimer[Row][Column + 1] < (encoder2Pulse + encoder2Wait))
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

    //SWITCH MODE 3: OPEN HYBRID
    if (!switchMode[Row][Column] && switchMode[Row][Column + 1])
    {

        for (int i = 1; i < HyPos + 1; i++)
        {
            int e = toggleTimer[Row][Column] % HyPos;
            if (e == 0)
            {
                e = HyPos;
            }
            if (i == e)
            {
                Joystick.pressButton(i - 1 + Number);
            }
            else
            {
                Joystick.releaseButton(i - 1 + Number);
            }
        }
    }

    //Push switch mode
    long push = 0;
    push = push | switchMode[Row][Column];
    push = push | (switchMode[Row][Column + 1] << 1);
    push = push << (FieldPlacement - 1);
    rotaryField = rotaryField | push;
}

void rotary2Inc(int row, int column, bool reverse)
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
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //Make sure we dont do this again
            latchLock[Row][Column] = false;
        }
    }

    int difference = pushState[Row][Column + 1];
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

void rotary2Multi(int row, int column, int positions, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int Pos = positions;
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
                toggleTimer[Row][Column] = toggleTimer[Row][Column] + 1 - (2 * Reverse);
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                toggleTimer[Row][Column] = toggleTimer[Row][Column] - 1 + (2 * Reverse);
            }
            if (toggleTimer[Row][Column] < 0)
            {
                toggleTimer[Row][Column] = Pos - 1;
            }

            for (int i = 0; i < Pos + 1; i++)
            {
                int e = toggleTimer[Row][Column] % Pos;
                if (e == 0)
                {
                    e = Pos;
                }
                if (i == e)
                {
                    Joystick.pressButton(i - 1 + Number);
                }
                else
                {
                    Joystick.releaseButton(i - 1 + Number);
                }
            }
        }
    }
}

void rotary2Multis(int row, int column, int fieldPlacement, int positions1, int positions2, int positions3, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = fieldPlacement;
    int Reverse = reverse;

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];

    int maxPos = max(positions3, (max(positions2, max(16, positions1))));

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


            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.
            //If you want to avoid pushing mode, set fieldPlacement to 0.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1 && FieldPlacement != 0)
            {
                for (int i = 0; i < maxPos + 1; i++) //Remove the remnants from SWITCH MODE 1
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                if (!switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Going to mode 2
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = true;
                    toggleTimer[Row][Column + 1] = positions1; //Using toggle timer pin 2 to store info on how many positionson multi-position switch
                }
                else if (switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Going to mode 3
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = false;
                    toggleTimer[Row][Column + 1] = positions2;
                }
                else if (!switchMode[Row][Column] && switchMode[Row][Column + 1]) //Going to mode 4
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = true;
                    toggleTimer[Row][Column + 1] = positions3;
                }
                else if (switchMode[Row][Column] && switchMode[Row][Column + 1]) //Going to mode 1
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = false;
                }
            }


            //If we're in pseudomulti, change counter
            if (!(!switchMode[Row][Column] && !switchMode[Row][Column + 1]))
            {
                int8_t difference = pushState[Row][Column + 1];
                if ((difference > 0 && difference < 2) || difference < -2)
                {
                    toggleTimer[Row][Column] = toggleTimer[Row][Column] + 1 - (2 * Reverse);
                }
                else if ((difference < 0 && difference > -2) || difference > 2)
                {
                    toggleTimer[Row][Column] = toggleTimer[Row][Column] - 1 + (2 * Reverse);
                }
                if (toggleTimer[Row][Column] < 0)
                {
                    toggleTimer[Row][Column] = toggleTimer[Row][Column + 1] - 1; //Col pin 4 push state holds info on how many positions on multiposition switch
                }
            }

            //If we're not in multipos at all, reset counter
            else
            {
                toggleTimer[Row][Column] = 0;
            }
        }

        //SWITCH MODE 1: 4 - position switch

        if (!switchMode[Row][Column] && !switchMode[Row][Column + 1])
        {
            pushState[Row][Column + 1] = 0; //Refreshing encoder mode difference

            for (int i = 0; i < 5; i++)
            {
                if (i == pushState[Row][Column])
                {
                    Joystick.pressButton(i + Number);
                }
                else
                {
                    Joystick.releaseButton(i + Number);
                }
            }
        }
        else
        {
            //SWITCH MODE 2-4: Multiposititon switches

            for (int i = 0; i < toggleTimer[Row][Column + 1] + 1; i++) //Col pin 4 push state holds info on how many positions on multiposition switch
            {
                int e = toggleTimer[Row][Column] % toggleTimer[Row][Column + 1];
                if (e == 0)
                {
                    e = toggleTimer[Row][Column + 1];
                }
                if (i == e)
                {
                    Joystick.pressButton(i - 1 + Number);
                }
                else
                {
                    Joystick.releaseButton(i - 1 + Number);
                }
            }
        }
    }

    //Push switch mode
    long push = 0;
    push = push | switchMode[Row][Column];
    push = push | (switchMode[Row][Column + 1] << 1);
    push = push << (FieldPlacement - 1);
    rotaryField = rotaryField | push;
}

void rotary2Bite(int row, int column, bool reverse)
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
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;


            //Make sure we dont do this again
            latchLock[Row][Column] = false;


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

            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.
            //If you want to avoid switching mode, set fieldPlacement to 0.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                if (switchMode[Row][Column] && switchMode[Row][Column + 1]) //EXIT from switch mode 4, entering DDS mode
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = false;
                    latchState[hybridButtonRow - 1][hybridButtonCol - 1] = 0; //Moving into hybrid mode, set hybrid button to 0
                }
                else if (!switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Jump from mode 1 (DDS) to mode 3
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = false;
                }
                else if (!switchMode[Row][Column] && switchMode[Row][Column + 1]) //Move from mode 3 to mode 4
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = true;
                }
            }

            if (biteButtonBit1 || biteButtonBit2)
            {
                int8_t difference = pushState[Row][Column + 1];

                if ((((difference > 0 && difference < 2) || difference < -2) && Reverse == 0) || (!((difference > 0 && difference < 2) || difference < -2) && Reverse == 1))
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
                }
                else if ((((difference < 0 && difference > -2) || difference > 2) && Reverse == 0) || (!((difference < 0 && difference > -2) || difference > 2) && Reverse == 1))
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
                }
            }
        }
    }


    if (!biteButtonBit1 && !biteButtonBit2) //Only goin through button presses if not setting bite point
    {
        int8_t difference = pushState[Row][Column + 1];
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
}

void DDS2bit(int row, int column, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = 5;
    int HyPos = 12;
    int Reverse = reverse;

    if (latchState[ddButtonRow - 1][ddButtonCol - 1] && !switchMode[Row][Column + 1])  //Jumping 
    {
        Number = Number + 12;
        if (!switchMode[Row][Column])
        {
            for (int i = 0; i < 12; i++) //Clear the low 12-positions when on high
            {
                Joystick.releaseButton(i + Number - 12);
            }
        }

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

            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.
            //If you want to avoid switching mode, set fieldPlacement to 0.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                for (int i = 0; i < 25; i++) //Remove the remnants from SWITCH MODE 3
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                if (switchMode[Row][Column] && switchMode[Row][Column + 1]) //EXIT from switch mode 4, entering DDS mode
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = false;
                    latchState[hybridButtonRow - 1][hybridButtonCol - 1] = 0; //Moving into hybrid mode, set hybrid button to 0
                }
                else if (!switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Jump from mode 1 (DDS) to mode 3
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = false;
                }
                else if (!switchMode[Row][Column] && switchMode[Row][Column + 1]) //Move from mode 3 to mode 4
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = true;
                }
            }

            if (!biteButtonBit1 && !biteButtonBit2) //Standard
            {

                //If we're in DDS, change counter
                int8_t difference = pushState[Row][Column + 1];
                if (!switchMode[Row][Column] && !switchMode[Row][Column + 1])
                {
                    if ((difference > 0 && difference < 2) || difference < -2)
                    {
                        toggleTimer[Row][Column] = toggleTimer[Row][Column] + 1 - (2 * Reverse);
                    }
                    else if ((difference < 0 && difference > -2) || difference > 2)
                    {
                        toggleTimer[Row][Column] = toggleTimer[Row][Column] - 1 + (2 * Reverse);
                    }
                    if (toggleTimer[Row][Column] < 0)
                    {
                        toggleTimer[Row][Column] = HyPos;
                    }
                }

                //If we're not in hybrid at all, reset counter
                else if (switchMode[Row][Column + 1])
                {
                    toggleTimer[Row][Column] = 0;
                }
            }
            else
            {
                int8_t difference = pushState[Row][Column + 1];

                if ((((difference > 0 && difference < 2) || difference < -2) && Reverse == 0) || (!((difference > 0 && difference < 2) || difference < -2) && Reverse == 1))
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
                }
                if ((((difference < 0 && difference > -2) || difference > 2) && Reverse == 0) || (!((difference < 0 && difference > -2) || difference > 2) && Reverse == 1))
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
                }
            }
        }
    }
    if (!biteButtonBit1 && !biteButtonBit2) //Only goin through button presses if not setting bite point
    {
        //If we're in hybrid, able to set open/closed hybrid
        if (!switchMode[Row][Column + 1])
        {
            switchMode[Row][Column] = latchState[hybridButtonRow - 1][hybridButtonCol - 1];
        }

        //If we're not in hybrid, reset ddButton
        if (switchMode[Row][Column + 1])
        {
            latchLock[ddButtonRow - 1][ddButtonCol - 1] = false;
            latchState[ddButtonRow - 1][ddButtonCol - 1] = false;
        }

        //SWITCH MODE 3: 4 - position switch

        if (!switchMode[Row][Column] && switchMode[Row][Column + 1])
        {
            pushState[Row][Column + 1] = 0; //Refreshing encoder mode difference

            for (int i = 0; i < 24; i++)
            {
                if (i == pushState[Row][Column])
                {
                    Joystick.pressButton(i + Number);
                }
                else
                {
                    Joystick.releaseButton(i + Number);
                }
            }
        }

        //SWITCH MODE 2/4: Incremental encoder or closed hybrid

        else if (switchMode[Row][Column])
        {
            Number = buttonNumber[Row][Column + 1];
            int8_t difference = pushState[Row][Column + 1];
            if (difference != 0)
            {
                if (globalClock - switchTimer[Row][Column + 1] < (encoder2Pulse + encoder2Wait))
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

        //SWITCH MODE 1: OPEN HYBRID
        if (!switchMode[Row][Column] && !switchMode[Row][Column + 1])
        {

            for (int i = 1; i < HyPos + 13; i++)
            {
                int e = toggleTimer[Row][Column] % HyPos;
                if (e == 0)
                {
                    e = HyPos;
                }
                if (i == e)
                {
                    Joystick.pressButton(i - 1 + Number);
                }
                else
                {
                    Joystick.releaseButton(i - 1 + Number);
                }
            }
        }

        //Clearing all buttons on mode change
        if (latchLock[ddButtonRow - 1][ddButtonCol - 1] && !(switchMode[Row][Column] && !switchMode[Row][Column + 1]))
        {
            for (int i = 0; i < 13; i++) //Remove the remnants from SWITCH MODE 1
            {
                Joystick.releaseButton(i - 1 + buttonNumber[Row][Column]);
            }
        }
    }



    //Push switch mode
    long push = 0;
    push = push | switchMode[Row][Column];
    push = push | (switchMode[Row][Column + 1] << 1);
    push = push << (2*(FieldPlacement - 1));
    rotaryField = rotaryField | push;
}

void rotary2Brightness(int8_t row, int8_t col, bool reverse)
{
    int8_t Row = row - 1;
    int8_t Column = col - 1;
    int8_t Number = buttonNumber[Row][Column];
    int8_t Reverse = reverse;


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
                if (pushState[modButtonRow-1][modButtonCol-1] == 1)
                {
                    LEDBrightness = LEDBrightness + 2 - (4 * Reverse);
                }
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                if (pushState[modButtonRow-1][modButtonCol-1] == 1)
                {
                    LEDBrightness = LEDBrightness - 2 + (4 * Reverse);
                }
            }
        }
    }

    //Adjusting 
    if (LEDBrightness < 0)
    {
      LEDBrightness = 0;
    }
    else if (LEDBrightness > 100)
    {
      LEDBrightness = 100;
    }

    int8_t difference = pushState[Row][Column + 1];
    if (difference != 0 && pushState[modButtonRow-1][modButtonCol-1] == 0)
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
