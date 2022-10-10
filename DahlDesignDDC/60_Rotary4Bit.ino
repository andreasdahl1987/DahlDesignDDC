//------------------------------
//------ROTARY 4-BIT SWITCH-----
//------------------------------

void rotary4Modes(int row, int column, int fieldPlacement, int hybridPositions, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = fieldPlacement;
    int HyPos = hybridPositions;
    int Reverse = reverse;

    int maxPos = max(16, HyPos);

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];
    bool Pin3 = rawState[Row][Column + 2];
    bool Pin4 = rawState[Row][Column + 3];

    bool array[4] = { Pin1, Pin2, Pin3, Pin4 };

    int pos = 0;

    for (int i = 0; i < 4; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 4);
    pos = pos ^ (pos >> 2);
    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > encoderPulse)
        {
            switchTimer[Row][Column] = globalClock;
        }
        else if (globalClock - switchTimer[Row][Column] > encoderWait)
        {
            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.
            //If you want to avoid switching mode, set fieldPlacement to 0.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1 && FieldPlacement != 0)
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

            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //If we're in open hybrid, change counter
            if (!switchMode[Row][Column] && switchMode[Row][Column + 1])
            {
                if ((pushState[Row][Column + 1] > 0 && pushState[Row][Column + 1] < 6) || pushState[Row][Column + 1] < -6)
                {
                    pushState[Row][Column + 2] = pushState[Row][Column + 2] + 1 - (2 * Reverse);
                }
                else
                {
                    pushState[Row][Column + 2] = pushState[Row][Column + 2] - 1 + (2 * Reverse);
                }
                if (pushState[Row][Column + 2] < 0)
                {
                    pushState[Row][Column + 2] = HyPos - 1;
                }
            }

            //If we're not in hybrid at all, reset counter
            else if (!switchMode[Row][Column + 1])
            {
                pushState[Row][Column + 2] = 0;
            }
        }
    }

    //If we're in hybrid, able to set open/closed hybrid
    if (switchMode[Row][Column + 1])
    {
        switchMode[Row][Column] = latchState[hybridButtonRow - 1][hybridButtonCol - 1];
    }

    //SWITCH MODE 1: 16 - position switch

    if (!switchMode[Row][Column] && !switchMode[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 0; //Refreshing encoder mode difference

        for (int i = 0; i < 17; i++)
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
        int difference = pushState[Row][Column + 1];
        if (difference != 0)
        {
            if (globalClock - switchTimer[Row][Column + 1] < encoderPulse)
            {
                if ((difference > 0 && difference < 6) || difference < -6)
                {
                    Joystick.setButton(Number + Reverse, 1);
                    Joystick.setButton(Number + 1 - Reverse, 0);
                }
                else
                {
                    Joystick.setButton(Number + Reverse, 0);
                    Joystick.setButton(Number + 1 - Reverse, 1);
                }
            }
            else
            {
                pushState[Row][Column + 1] = 0;
                Joystick.setButton(Number, 0);
                Joystick.setButton(Number + 1, 0);
            }
        }
    }

    //SWITCH MODE 3: OPEN HYBRID
    if (!switchMode[Row][Column] && switchMode[Row][Column + 1])
    {

        for (int i = 0; i < HyPos + 1; i++)
        {
            int e = pushState[Row][Column + 2] % HyPos;
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

void rotary4Inc(int row, int column, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int Reverse = reverse;

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];
    bool Pin3 = rawState[Row][Column + 2];
    bool Pin4 = rawState[Row][Column + 3];

    bool array[4] = { Pin1, Pin2, Pin3, Pin4 };

    int pos = 0;

    for (int i = 0; i < 4; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 4);
    pos = pos ^ (pos >> 2);
    pos = pos ^ (pos >> 1);

    int result = pos;
    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result && (globalClock - switchTimer[Row][Column] > encoderPulse))
    {
        switchTimer[Row][Column] = globalClock;
    }
    if (globalClock - switchTimer[Row][Column] > encoderWait)
    {
        if (globalClock - switchTimer[Row][Column] < encoderPulse)
        {
            int difference = result - pushState[Row][Column];

            if ((difference > 0 && difference < 6) || difference < -6)
            {
                Joystick.setButton(Number + Reverse, 1);
                Joystick.setButton(Number + 1 - Reverse, 0);
            }
            else
            {
                Joystick.setButton(Number + Reverse, 0);
                Joystick.setButton(Number + 1 - Reverse, 1);
            }
        }
        else
        {
            Joystick.setButton(Number, 0);
            Joystick.setButton(Number + 1, 0);
            pushState[Row][Column] = result;
        }
    }
}

void rotary4Multi(int row, int column, int positions, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int Pos = positions;
    int Reverse = reverse;

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];
    bool Pin3 = rawState[Row][Column + 2];
    bool Pin4 = rawState[Row][Column + 3];

    bool array[4] = { Pin1, Pin2, Pin3, Pin4 };

    int pos = 0;

    for (int i = 0; i < 4; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 4);
    pos = pos ^ (pos >> 2);
    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > encoderPulse)
        {
            switchTimer[Row][Column] = globalClock;
        }
        else if (globalClock - switchTimer[Row][Column] > encoderWait)
        {
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            if ((pushState[Row][Column + 1] > 0 && pushState[Row][Column + 1] < 6) || pushState[Row][Column + 1] < -6)
            {
                pushState[Row][Column + 2] = pushState[Row][Column + 2] + 1 - (2 * Reverse);
            }
            else
            {
                pushState[Row][Column + 2] = pushState[Row][Column + 2] - 1 + (2 * Reverse);
            }

            if (pushState[Row][Column + 2] < 0)
            {
                pushState[Row][Column + 2] = Pos - 1;
            }

            for (int i = 0; i < Pos + 1; i++)
            {
                int e = pushState[Row][Column + 2] % Pos;
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

void rotary4Multis(int row, int column, int fieldPlacement, int positions1, int positions2, int positions3, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = fieldPlacement;
    int Reverse = reverse;

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];
    bool Pin3 = rawState[Row][Column + 2];
    bool Pin4 = rawState[Row][Column + 3];

    int maxPos = max(positions3, (max(positions2, max(16, positions1))));

    bool array[4] = { Pin1, Pin2, Pin3, Pin4 };

    int pos = 0;

    for (int i = 0; i < 4; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 4);
    pos = pos ^ (pos >> 2);
    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > encoderPulse)
        {
            switchTimer[Row][Column] = globalClock;
        }
        else if (globalClock - switchTimer[Row][Column] > encoderWait)
        {

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
                    pushState[Row][Column + 3] = positions1; //Using col 4 pin push state to store info on how many positionson multi-position switch
                }
                else if (switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Going to mode 3
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = false;
                    pushState[Row][Column + 3] = positions2;
                }
                else if (!switchMode[Row][Column] && switchMode[Row][Column + 1]) //Going to mode 4
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = true;
                    pushState[Row][Column + 3] = positions3;
                }
                else if (switchMode[Row][Column] && switchMode[Row][Column + 1]) //Going to mode 1
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = false;
                }
            }

            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //If we're in pseudomulti, change counter
            if (!(!switchMode[Row][Column] && !switchMode[Row][Column + 1]))
            {
                if ((pushState[Row][Column + 1] > 0 && pushState[Row][Column + 1] < 6) || pushState[Row][Column + 1] < -6)
                {
                    pushState[Row][Column + 2] = pushState[Row][Column + 2] + 1 - (2 * Reverse);
                }
                else
                {
                    pushState[Row][Column + 2] = pushState[Row][Column + 2] - 1 + (2 * Reverse);
                }
                if (pushState[Row][Column + 2] < 0)
                {
                    pushState[Row][Column + 2] = pushState[Row][Column + 3] - 1; //Col pin 4 push state holds info on how many positions on multiposition switch
                }
            }

            //If we're not in hybrid at all, reset counter
            else
            {
                pushState[Row][Column + 2] = 0;
            }
        }

        //SWITCH MODE 1: 16 - position switch

        if (!switchMode[Row][Column] && !switchMode[Row][Column + 1])
        {
            pushState[Row][Column + 1] = 0; //Refreshing encoder mode difference

            for (int i = 0; i < 17; i++)
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

            for (int i = 0; i < pushState[Row][Column + 3] + 1; i++) //Col pin 4 push state holds info on how many positions on multiposition switch
            {
                int e = pushState[Row][Column + 2] % pushState[Row][Column + 3];
                if (e == 0)
                {
                    e = pushState[Row][Column + 3];
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

void DDS4bit(int row, int column, bool reverse)
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
    bool Pin3 = rawState[Row][Column + 2];
    bool Pin4 = rawState[Row][Column + 3];

    bool array[4] = { Pin1, Pin2, Pin3, Pin4 };

    int pos = 0;

    for (int i = 0; i < 4; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 4);
    pos = pos ^ (pos >> 2);
    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > encoderPulse)
        {
            switchTimer[Row][Column] = globalClock;
        }
        else if (globalClock - switchTimer[Row][Column] > encoderWait)
        {


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
                //Engage encoder pulse timer
                switchTimer[Row][Column + 1] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                pushState[Row][Column + 1] = result - pushState[Row][Column];

                //Give new value to pushState
                pushState[Row][Column] = result;

                //If we're in DDS, change counter
                if (!switchMode[Row][Column] && !switchMode[Row][Column + 1])
                {
                    if ((pushState[Row][Column + 1] > 0 && pushState[Row][Column + 1] < 6) || pushState[Row][Column + 1] < -6)
                    {
                        toggleTimer[Row][Column] = toggleTimer[Row][Column] + 1 - (2 * Reverse);
                    }
                    else
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
                //Engage encoder pulse timer
                switchTimer[Row][Column + 1] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                pushState[Row][Column + 1] = result - pushState[Row][Column];

                //Give new value to pushState
                pushState[Row][Column] = result;

                if ((((pushState[Row][Column + 1] > 0 && pushState[Row][Column + 1] < 2) || pushState[Row][Column + 1] < -2) && Reverse == 0) || (!((pushState[Row][Column + 1] > 0 && pushState[Row][Column + 1] < 2) || pushState[Row][Column + 1] < -2) && Reverse == 1))
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
                else
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

    if (!biteButtonBit1 && !biteButtonBit2) //Only goin through button presses if not setting bite point
    {
        //SWITCH MODE 3: 16 - position switch

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
            int difference = pushState[Row][Column + 1];
            if (difference != 0)
            {
                if (globalClock - switchTimer[Row][Column + 1] < encoderPulse)
                {
                    if ((difference > 0 && difference < 6) || difference < -6)
                    {
                        Joystick.setButton(Number + Reverse, 1);
                        Joystick.setButton(Number + 1 - Reverse, 0);
                    }
                    else
                    {
                        Joystick.setButton(Number + Reverse, 0);
                        Joystick.setButton(Number + 1 - Reverse, 1);
                    }
                }
                else
                {
                    pushState[Row][Column + 1] = 0;
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