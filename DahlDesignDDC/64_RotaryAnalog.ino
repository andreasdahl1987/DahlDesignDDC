//------------------------------
//------ROTARY SWITCH-----------
//---WITH RESISTOR LADDER-------
//------------------------------


void rotaryAnalog(int analogPin, int switchNumber, int fieldPlacement, int hybridPositions, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;

    int N = switchNumber - 1;
    bool Reverse = reverse;

    int Number = analogButtonNumber[N];
    int FieldPlacement = fieldPlacement;
    int HyPos = hybridPositions;

    int maxPos = max(12, HyPos);


    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }

    result--;

    if (Reverse)
    {
        result = 11 - result;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
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

                if (analogSwitchMode1[N] && analogSwitchMode2[N]) //EXIT from switch mode 4
                {
                    analogSwitchMode2[N] = false;
                    analogSwitchMode1[N] = false;
                }
                else //Rotate between switch modes 1-3
                {
                    analogSwitchMode1[N] = !analogSwitchMode1[N];
                    if (!analogSwitchMode1[N]) //Moving into hybrid mode, set hybrid button to 0
                    {
                        analogSwitchMode2[N] = true;
                        latchState[hybridButtonRow - 1][hybridButtonCol - 1] = 0;
                    }
                    else
                    {
                        if (analogSwitchMode2[N])
                        {
                            analogSwitchMode2[N] = false;
                            analogSwitchMode1[N] = false;
                        }
                    }
                }
            }

            //Engage encoder pulse timer
            analogTimer2[N] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            analogTempState[N] = result - analogLastCounter[N];

            //Give new value to pushState
            analogLastCounter[N] = result;

            //If we're in open hybrid, change counter
            if (!analogSwitchMode1[N] && analogSwitchMode2[N])
            {
                if ((analogTempState[N] > 0 && analogTempState[N] < 5) || analogTempState[N] < -5)
                {
                    analogRotaryCount[N] ++;
                }
                else
                {
                    analogRotaryCount[N] --;
                }
                if (analogRotaryCount[N] < 0)
                {
                    analogRotaryCount[N] = HyPos - 1;
                }
            }

            //If we're not in hybrid at all, reset counter
            else if (!analogSwitchMode2[N])
            {
                analogRotaryCount[N] = 0;
            }
        }
    }

    //If we're in hybrid, able to set open/closed hybrid
    if (analogSwitchMode2[N])
    {
        analogSwitchMode1[N] = latchState[hybridButtonRow - 1][hybridButtonCol - 1];
    }

    //SWITCH MODE 1: 12 - position switch

    if (!analogSwitchMode1[N] && !analogSwitchMode2[N])
    {
        analogTempState[N] = 0; //Refreshing encoder mode difference

        for (int i = 0; i < 12; i++)
        {
            if (i == analogLastCounter[N])
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

    else if (analogSwitchMode1[N])
    {
        Number = analogButtonNumberIncMode[N];
        int difference = analogTempState[N];
        if (difference != 0)
        {
            if (globalClock - analogTimer2[N] < encoderPulse)
            {
                if ((difference > 0 && difference < 5) || difference < -5)
                {
                    Joystick.setButton(Number, 1);
                    Joystick.setButton(Number + 1, 0);
                }
                else
                {
                    Joystick.setButton(Number, 0);
                    Joystick.setButton(Number + 1, 1);
                }
            }
            else
            {
                analogTempState[N] = 0;
                Joystick.setButton(Number, 0);
                Joystick.setButton(Number + 1, 0);
            }
        }
    }

    //SWITCH MODE 3: OPEN HYBRID
    if (!analogSwitchMode1[N] && analogSwitchMode2[N])
    {

        for (int i = 1; i < HyPos + 1; i++)
        {
            int e = analogRotaryCount[N] % HyPos;
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
    push = push | analogSwitchMode1[N];
    push = push | (analogSwitchMode2[N] << 1);
    push = push << (FieldPlacement - 1);
    rotaryField = rotaryField | push;
}

void rotaryAnalogSimple(int analogPin, int switchNumber, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;

    bool Reverse = reverse;

    int N = switchNumber - 1;

    int Number = analogButtonNumber[N];

    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }

    result--;

    if (Reverse)
    {
        result = 11 - result;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
        {
          //Engage encoder pulse timer
          analogTimer2[N] = globalClock;

          //Update difference, storing the value in pushState on pin 2
          analogTempState[N] = result - analogLastCounter[N];

          //Give new value to pushState
          analogLastCounter[N] = result;
        }
    }

            
    //12 - position switch

    if (!analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2)
    {
        analogTempState[N] = 0; //Refreshing encoder mode difference

        for (int i = 0; i < 12; i++)
        {
            if (i == analogLastCounter[N])
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
        }
    }
}

void rotaryAnalog2Mode(int analogPin, int switchNumber, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;

    bool Reverse = reverse;

    int N = switchNumber - 1;

    int Number = analogButtonNumber[N];
    int FieldPlacement = fieldPlacement;

    int maxPos = 12;


    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }

    result--;

    if (Reverse)
    {
        result = 11 - result;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
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

            else if (pushState[modButtonRow - 1][modButtonCol - 1] == 1 && FieldPlacement != 0)
            {
                for (int i = 0; i < maxPos + 1; i++) //Remove the remnants from SWITCH MODE 1
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                analogSwitchMode1[N] = !analogSwitchMode1[N]; //SWAP MODE
            }

            if (!biteButtonBit1 && !biteButtonBit2) //Standard
            {
                //Engage encoder pulse timer
                analogTimer2[N] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                analogTempState[N] = result - analogLastCounter[N];

                //Give new value to pushState
                analogLastCounter[N] = result;
            }

            else //Bite point setting
            {
                //Engage encoder pulse timer
                analogTimer2[N] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                analogTempState[N] = result - analogLastCounter[N];

                //Give new value to pushState
                analogLastCounter[N] = result;

                //Adjusting bite up/down
                if ((analogTempState[N] > 0 && analogTempState[N] < 5) || analogTempState[N] < -5)
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

    //SWITCH MODE 1: 12 - position switch

    if (!analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2)
    {
        analogTempState[N] = 0; //Refreshing encoder mode difference

        for (int i = 0; i < 12; i++)
        {
            if (i == analogLastCounter[N])
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

    else if (analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2)
    {
        Number = analogButtonNumberIncMode[N];
        int difference = analogTempState[N];
        if (difference != 0)
        {
            if (globalClock - analogTimer2[N] < encoderPulse)
            {
                if ((difference > 0 && difference < 5) || difference < -5)
                {
                    Joystick.setButton(Number, 1);
                    Joystick.setButton(Number + 1, 0);
                }
                else
                {
                    Joystick.setButton(Number, 0);
                    Joystick.setButton(Number + 1, 1);
                }
            }
            else
            {
                analogTempState[N] = 0;
                Joystick.setButton(Number, 0);
                Joystick.setButton(Number + 1, 0);
            }
        }
    }

    //Push switch mode
    long push = 0;
    push = push | analogSwitchMode1[N];
    push = push << (FieldPlacement - 1);
    rotaryField = rotaryField | push;
}
void DDSanalog(int analogPin, int switchNumber, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;


    int N = switchNumber - 1;
    int HyPos = 12;

    int Number = analogButtonNumber[N];
    int FieldPlacement = 5;
    bool Reverse = reverse;

    if (latchState[ddButtonRow - 1][ddButtonCol - 1] && !analogSwitchMode2[N])  //Jumping 
    {
        Number = Number + 12;
    }

    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }
    result--;

    if (Reverse)
    {
        result = 11 - result;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
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

            else if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                for (int i = 0; i < 24; i++) //Remove the remnants from SWITCH MODE 3
                {
                    Joystick.releaseButton(i + Number);
                }

                if (analogSwitchMode1[N] && analogSwitchMode2[N]) //EXIT from switch mode 4, entering DDS mode
                {
                    analogSwitchMode2[N] = false;
                    analogSwitchMode1[N] = false;
                    latchState[hybridButtonRow - 1][hybridButtonCol - 1] = 0; //Moving into hybrid mode, set hybrid button to 0
                }
                else if (!analogSwitchMode1[N] && !analogSwitchMode2[N]) //Jump from mode 1 (DDS) to mode 3
                {
                    analogSwitchMode2[N] = true;
                    analogSwitchMode1[N] = false;
                }
                else if (!analogSwitchMode1[N] && analogSwitchMode2[N]) //Move from mode 3 to mode 4
                {
                    analogSwitchMode2[N] = true;
                    analogSwitchMode1[N] = true;
                }
            }

            if (!biteButtonBit1 && !biteButtonBit2) //Standard
            {
                //Engage encoder pulse timer
                analogTimer2[N] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                analogTempState[N] = result - analogLastCounter[N];

                //Give new value to pushState
                analogLastCounter[N] = result;

                //If we're in DDS, change counter
                if (!analogSwitchMode1[N] && !analogSwitchMode2[N])
                {
                    if ((analogTempState[N] > 0 && analogTempState[N] < 5) || analogTempState[N] < -5)
                    {
                        analogRotaryCount[N] ++;
                    }
                    else
                    {
                        analogRotaryCount[N] --;
                    }
                    if (analogRotaryCount[N] < 0)
                    {
                        analogRotaryCount[N] = HyPos;
                    }
                }

                //If we're not in hybrid at all, reset counter
                else if (analogSwitchMode2[N])
                {
                    analogRotaryCount[N] = 0;
                }
            }
            else //Bite point setting
            {
                //Engage encoder pulse timer
                analogTimer2[N] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                analogTempState[N] = result - analogLastCounter[N];

                //Give new value to pushState
                analogLastCounter[N] = result;

                //Adjusting bite up/down
                if ((analogTempState[N] > 0 && analogTempState[N] < 5) || analogTempState[N] < -5)
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
    if (!analogSwitchMode2[N])
    {
        analogSwitchMode1[N] = latchState[hybridButtonRow - 1][hybridButtonCol - 1];
    }
    //If we're not in hybrid, reset ddButton
    if (analogSwitchMode2[N])
    {
        latchLock[ddButtonRow - 1][ddButtonCol - 1] = false;
        latchState[ddButtonRow - 1][ddButtonCol - 1] = false;
    }

    if (!biteButtonBit1 && !biteButtonBit2) //Only goin through button presses if not setting bite point
    {
        //SWITCH MODE 3: 12 - position switch

        if (!analogSwitchMode1[N] && analogSwitchMode2[N])
        {
            analogTempState[N] = 0; //Refreshing encoder mode difference

            for (int i = 0; i < 24; i++)
            {
                if (i == analogLastCounter[N])
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

        else if (analogSwitchMode1[N])
        {

            Number = analogButtonNumberIncMode[N];
            int difference = analogTempState[N];
            if (difference != 0)
            {
                if (globalClock - analogTimer2[N] < analogPulse)
                {
                    if ((difference > 0 && difference < 5) || difference < -5)
                    {
                        Joystick.setButton(Number, 1);
                        Joystick.setButton(Number + 1, 0);
                    }
                    else
                    {
                        Joystick.setButton(Number, 0);
                        Joystick.setButton(Number + 1, 1);
                    }
                }
                else
                {
                    analogTempState[N] = 0;
                    Joystick.setButton(Number, 0);
                    Joystick.setButton(Number + 1, 0);
                }
            }
        }

        //SWITCH MODE 1: OPEN HYBRID
        if (!analogSwitchMode1[N] && !analogSwitchMode2[N])
        {

            for (int i = 1; i < HyPos + 13; i++)
            {
                int e = (analogRotaryCount[N] % HyPos);
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
        if (latchState[ddButtonRow - 1][ddButtonCol - 1] && !(analogSwitchMode1[N] && !analogSwitchMode2[N]))
        {

            for (int i = 0; i < 12; i++) //Remove the remnants from SWITCH MODE 1
            {
                Joystick.releaseButton(i + analogButtonNumber[N]);
            }
        }
    }


    //Push switch mode
    long push = 0;
    push = push | analogSwitchMode1[N];
    push = push | (analogSwitchMode2[N] << 1);
    push = push << (2*(FieldPlacement - 1));
    rotaryField = rotaryField | push;
}
