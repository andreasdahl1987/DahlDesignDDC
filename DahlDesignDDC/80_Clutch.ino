
//----------------------------
//----ANALOG CLUTCH-----------
//----------------------------
float corrected(int input, int releasedValue, int pressedValue, int linearFix, float expFactor)
{
    float Input = input;
    int PressedValue = pressedValue;
    int ReleasedValue = releasedValue;

    if (linearFix == 0)
    {
        return Input;
    }

    if (linearFix < 0)
    {
        if (releasedValue < pressedValue)
        {
            PressedValue = PressedValue - clutchTopDeadzone;
            ReleasedValue = ReleasedValue + clutchBottomDeadzone;
            if (Input < ReleasedValue)
            {
                Input = ReleasedValue;
            }
            Input = (Input - ReleasedValue) * pow((1 + Input - ReleasedValue), expFactor);
        }
        else if (pressedValue < releasedValue)
        {
            PressedValue = PressedValue + clutchTopDeadzone;
            ReleasedValue = ReleasedValue - clutchBottomDeadzone;
            if (Input > ReleasedValue)
            {
                Input = ReleasedValue;
            }
            Input = (ReleasedValue - Input) * pow((1 + ReleasedValue - Input), expFactor);
        }
    }
    else if (linearFix > 0)
    {
        if (ReleasedValue < PressedValue)
        {
            if (Input < ReleasedValue)
            {
                Input = ReleasedValue;
            }
            Input = (PressedValue - Input) * pow((1 + PressedValue - Input), expFactor);
        }
        else if (PressedValue < ReleasedValue)
        {
            if (Input > ReleasedValue)
            {
                Input = ReleasedValue;
            }
            Input = (Input - PressedValue) * pow((1 + Input - PressedValue), expFactor);
        }
    }

    return Input;
}

void singleClutch(int analogPin, int switchNumber, int releasedValue, int fullyPressedValue)
{
    int inputPin = analogPin;
    int pinValue = analogRead(inputPin);
    int N = switchNumber - 1;
    float normalized = 0;

    if (fullyPressedValue > releasedValue)
    {
        fullyPressedValue = fullyPressedValue - clutchTopDeadzone;
        releasedValue = releasedValue + clutchBottomDeadzone;
        float gap = fullyPressedValue - releasedValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (pinValue - releasedValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }
    else if (fullyPressedValue < releasedValue)
    {
        fullyPressedValue = fullyPressedValue + clutchTopDeadzone;
        releasedValue = releasedValue - clutchBottomDeadzone;
        float gap = releasedValue - fullyPressedValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (releasedValue - pinValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }

    total[N] = total[N] - readings[N][readIndex[N]];
    readings[N][readIndex[N]] = normalized;
    total[N] = total[N] + readings[N][readIndex[N]];

    readIndex[N]++;

    if (readIndex[N] > (reads-1))
    {
        readIndex[N] = 0;
    }

    average[N] = total[N] / reads;
    if (average[N] > 1000)
    {
        average[N] = 1000;
    }
    
    //Launch button

    if (launchButtonLatch)
    {
        average[N] = average[N] * bitePoint / 1000;
    }

    if (average[N] == 0)
    {
        analogLatchLock[N] = true;
    }

    if (average[N] == 1000 && analogLatchLock[N])
    {
        analogLatchLock[N] = false;
    }

    if (latchState[neutralButtonRow - 1][neutralButtonCol - 1])
    {
        Joystick.setXAxis(1000);
    }
    //Set axis
    Joystick.setXAxis(average[N]);
}

void dualClutch(int masterPin, int masterSwitchNumber, int masterReleasedValue, int masterFullyPressedValue, int slavePin, int slaveSwitchNumber, int slaveReleasedValue, int slaveFullyPressedValue, bool throttleMaster)
{

    //--------------------------------
    //---Master paddle calculations----
    //--------------------------------

    int MasterPin = masterPin;
    int masterValue = analogRead(MasterPin);
    int M = masterSwitchNumber - 1;
    float masterNormalized = 0;
    int FieldPlacement = 7;
    bool ThrottleMaster = throttleMaster;


    if (masterFullyPressedValue > masterReleasedValue)
    {
        masterFullyPressedValue = masterFullyPressedValue - clutchTopDeadzone;
        masterReleasedValue = masterReleasedValue + clutchBottomDeadzone;
        float gap = masterFullyPressedValue - masterReleasedValue;
        float normFactor = 1000 / gap;
        masterNormalized = normFactor * (masterValue - masterReleasedValue);
        if (masterNormalized < 0)
        {
            masterNormalized = 0;
        }
    }

    else if (masterFullyPressedValue < masterReleasedValue)
    {
        masterFullyPressedValue = masterFullyPressedValue + clutchTopDeadzone;
        masterReleasedValue = masterReleasedValue - clutchBottomDeadzone;
        float gap = masterReleasedValue - masterFullyPressedValue;
        float normFactor = 1000 / gap;
        masterNormalized = normFactor * (masterReleasedValue - masterValue);
        if (masterNormalized < 0)
        {
            masterNormalized = 0;
        }
    }

    total[M] = total[M] - readings[M][readIndex[M]];
    readings[M][readIndex[M]] = masterNormalized;
    total[M] = total[M] + readings[M][readIndex[M]];

    readIndex[M]++;

    if (readIndex[M] > (reads-1))
    {
        readIndex[M] = 0;
    }

    average[M] = total[M] / reads;
    if (average[M] > 1000)
    {
        average[M] = 1000;
    }

      //--------------------------------
      //---Slave paddle calculations----
      //--------------------------------

    int SlavePin = slavePin;
    int slaveValue = analogRead(SlavePin);
    int S = slaveSwitchNumber - 1;
    float slaveNormalized = 0;

    if (slaveFullyPressedValue > slaveReleasedValue)
    {
        slaveFullyPressedValue = slaveFullyPressedValue - clutchTopDeadzone;
        slaveReleasedValue = slaveReleasedValue + clutchBottomDeadzone;
        float gap = slaveFullyPressedValue - slaveReleasedValue;
        float normFactor = 1000 / gap;
        slaveNormalized = normFactor * (slaveValue - slaveReleasedValue);
        if (slaveNormalized < 0)
        {
            slaveNormalized = 0;
        }
    }

    else if (slaveFullyPressedValue < slaveReleasedValue)
    {
        slaveFullyPressedValue = slaveFullyPressedValue + clutchTopDeadzone;
        slaveReleasedValue = slaveReleasedValue - clutchBottomDeadzone;
        float gap = slaveReleasedValue - slaveFullyPressedValue;
        float normFactor = 1000 / gap;
        slaveNormalized = normFactor * (slaveReleasedValue - slaveValue);
        if (slaveNormalized < 0)
        {
            slaveNormalized = 0;
        }
    }

    total[S] = total[S] - readings[S][readIndex[S]];
    readings[S][readIndex[S]] = slaveNormalized;
    total[S] = total[S] + readings[S][readIndex[S]];

    readIndex[S]++;

    if (readIndex[S] > (reads-1))
    {
        readIndex[S] = 0;
    }

    average[S] = total[S] / reads;
    if (average[S] > 1000)
    {
        average[S] = 1000;
    }


    //------------------------
    //------MODE CHANGE-------
    //------------------------
    int maxValue = max(average[S], average[M]);

    if (maxValue == 0)
    {
        analogLatchLock[M] = true;
    }

    if (maxValue == 1000 && analogLatchLock[M])
    {
        analogLatchLock[M] = false;
        if (pushState[modButtonRow - 1][modButtonCol - 1] == 1) //Changig clutch modes
        {
            if (!analogSwitchMode1[M] && !analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = true;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
            else if (analogSwitchMode1[M] && !analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = false;
                analogSwitchMode2[M] = true;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
            else if (!analogSwitchMode1[M] && analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = true;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
            else if (analogSwitchMode1[M] && analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = false;
                analogSwitchMode2[M] = false;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
        }
    }

    //Launch button logic
    if (launchButtonLatch)
    {
        average[M] = average[M] * bitePoint / 1000;
        average[S] = average[S] * bitePoint / 1000;
    }

    //------------------------
    //------CLUTCH MODES------
    //------------------------

    //MODE 1: STATIC
    if (!analogSwitchMode1[M] && !analogSwitchMode2[M])
    {
        average[S] = average[S] * bitePoint / 1000;
        Joystick.setXAxis(max(average[S], average[M]));
    }
    //MODE 2: DYNAMIC LOW
    else if (analogSwitchMode1[M] && !analogSwitchMode2[M])
    {

        if ((average[S] == 0 || average[M] == 0 || average[S] > bitePoint && average[M] < bitePoint) || (average[M] > bitePoint && average[S] < bitePoint))
        {
            average[S] = average[S] * bitePoint / 1000;
            average[M] = average[M] * bitePoint / 1000;
            Joystick.setXAxis(max(average[S], average[M]));
        }
        else if (average[M] > bitePoint && average[S] > bitePoint)
        {
            Joystick.setXAxis(max(average[S], average[M]));
        }
        else if ((average[S] == 1000 && average[M] < 1000 && average[M] > bitePoint) || (average[M] == 1000 && average[S] < 1000 && average[S] > bitePoint))
        {
            Joystick.setXAxis(min(average[S], average[M]));
        }
    }
    //MODE 3: DYNAMIC HIGH
    else if (!analogSwitchMode1[M] && analogSwitchMode2[M])
    {
        if (average[S] == 1000 && average[M] == 1000)
        {
            analogLatchLock[S] = true;
        }
        if (average[S] == 0 && average[M] == 0)
        {
            analogLatchLock[S] = false;
        }

        if (analogLatchLock[S])
        {
            if (average[S] == 1000 && average[M] > bitePoint)
            {
                Joystick.setXAxis(average[M]);
            }
            else if (average[M] == 1000 && average[S] > bitePoint)
            {
                Joystick.setXAxis(average[S]);
            }
            else
            {
                Joystick.setXAxis(max(average[S], average[M]) * bitePoint / 1000);
            }
        }
        else
        {
            Joystick.setXAxis(max(average[S], average[M]));
        }
    }
    //MODE 4: BRAKE AND THROTTLE
    else
    {
        Joystick.setXAxis(0);
        if (ThrottleMaster)
        {
            Joystick.setThrottle(average[M]);
            Joystick.setBrake(average[S]);
        }
        else
        {
            Joystick.setThrottle(average[S]);
            Joystick.setBrake(average[M]);
        }
    }

    if (latchState[neutralButtonRow - 1][neutralButtonCol - 1])
    {
        Joystick.setXAxis(1000);
    }


    long push = 0;
    push = push | analogSwitchMode1[M];
    push = push | (analogSwitchMode2[M] << 1);
    push = push << (2*(FieldPlacement - 1));
    rotaryField = rotaryField | push;

}
