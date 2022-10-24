void SW1PresetRotary(int analogPin, int switchNumber, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
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

    if (bootPreset) //Load boot preset on startup
    {
        switchPreset = result;
        presets(switchPreset);
        bootPreset = false;
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

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                for (int i = 0; i < maxPos + 1; i++) //Remove the remnants from SWITCH MODE 1
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                analogSwitchMode1[N] = !analogSwitchMode1[N]; //SWAP MODE
            }

            //Engage encoder pulse timer
            analogTimer2[N] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            analogTempState[N] = result - analogLastCounter[N];

            //Give new value to pushState

            analogLastCounter[N] = result;

            if (pushState[presetButtonRow - 1][presetButtonCol - 1] == 1) //Standard
            {
                //Set the preset value
                switchPreset = result;

                //Set new preset
                presets(switchPreset);
            }
        }
    }

    //SWITCH MODE 1: 12 - position switch

    if (!analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2 && !pushState[presetButtonRow - 1][presetButtonCol - 1])
    {
        analogTempState[N] = 0; //Refreshing encoder mode difference

        uint8_t value = analogLastCounter[N];
        if (quickSwitchState || quickSwitch12State)
        {
            value = quickValue1;
        }

        for (int i = 0; i < 12; i++)
        {
            if (i == value)
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
        }
    }

    //SWITCH MODE 2: Incremental switch

    else if (analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2 && !pushState[presetButtonRow - 1][presetButtonCol - 1])
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

    //Push the switch mode
    long push = 0;
    push = push | analogSwitchMode1[N];
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;

    //Push the preset number
    long pesh = 0;
    pesh = pesh | (switchPreset << 10);
    buttonField = buttonField | pesh;


}

