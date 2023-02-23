void dualClutch(int masterPin, int masterSwitchNumber, int masterReleasedValue, int masterFullyPressedValue, int slavePin, int slaveSwitchNumber, int slaveReleasedValue, int slaveFullyPressedValue, bool throttleMaster)
{
    //--------------------------------
    //---Master paddle calculations----
    //--------------------------------

    int masterValue = analogRead(masterPin);
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

    if (readIndex[M] > (reads - 1))
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

    int slaveValue = analogRead(slavePin);
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

    if (readIndex[S] > (reads - 1))
    {
        readIndex[S] = 0;
    }

    average[S] = total[S] / reads;
    if (average[S] > 1000)
    {
        average[S] = 1000;
    }

    //------------------------------------------
    //------SETTING BITE POINT WITH BUTTON------
    //------------------------------------------

    if (max(average[S], average[M]) > 0 && pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
    {
        bitePoint = max(average[S], average[M]);
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

        if ((average[S] == 0 || average[M] == 0 || (average[S] > bitePoint && average[M] < bitePoint)) || (average[M] > bitePoint && average[S] < bitePoint))
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

    if (neutralButtonRow != -1)
    {
        if (latchState[neutralButtonRow - 1][neutralButtonCol - 1])
        {
            Joystick.setXAxis(1000);
        }
    }
    
    long push = 0;
    push = push | analogSwitchMode1[M];
    push = push | (analogSwitchMode2[M] << 1);
    push = push << (2 * (FieldPlacement - 1));
    rotaryField = rotaryField | push;

}

void filteredDualClutch(int masterPin, int masterSwitchNumber, int masterReleasedValue, int masterFullyPressedValue, int masterCurvePush, float masterExpFactor, int slavePin, int slaveSwitchNumber, int slaveReleasedValue, int slaveFullyPressedValue, int slaveCurvePush, float slaveExpFactor, bool throttleMaster)
{

    int FieldPlacement = 7;

    //--------------------------------
    //---Master paddle calculations----
    //--------------------------------

    int masterRaw = analogRead(masterPin);
    int M = masterSwitchNumber - 1;
    float masterNormalized = 0;
    float MasterFullyPressedValue = curveFilter(masterFullyPressedValue, masterReleasedValue, masterFullyPressedValue, masterCurvePush, masterExpFactor);
    float MasterReleasedValue = curveFilter(masterReleasedValue, masterReleasedValue, masterFullyPressedValue, masterCurvePush, masterExpFactor);
    float MasterValue = curveFilter(masterRaw, masterReleasedValue, masterFullyPressedValue, masterCurvePush, masterExpFactor);

    if (MasterFullyPressedValue > MasterReleasedValue)
    {
        float gap = MasterFullyPressedValue - MasterReleasedValue;
        float normFactor = 1000 / gap;
        masterNormalized = normFactor * (MasterValue - MasterReleasedValue);
        if (masterNormalized < 0)
        {
            masterNormalized = 0;
        }
    }
    else if (MasterFullyPressedValue < MasterReleasedValue)
    {
        MasterValue = MasterReleasedValue - MasterValue;

        float gap = MasterReleasedValue - MasterFullyPressedValue;
        float normFactor = 1000 / gap;
        masterNormalized = normFactor * MasterValue;
        if (masterNormalized < 0)
        {
            masterNormalized = 0;
        }
    }

    total[M] = total[M] - readings[M][readIndex[M]];
    readings[M][readIndex[M]] = masterNormalized;
    total[M] = total[M] + readings[M][readIndex[M]];

    readIndex[M]++;

    if (readIndex[M] > (reads - 1))
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

    int slaveRaw = analogRead(slavePin);
    int S = slaveSwitchNumber - 1;
    float slaveNormalized = 0;

    float SlaveFullyPressedValue = curveFilter(slaveFullyPressedValue, slaveReleasedValue, slaveFullyPressedValue, slaveCurvePush, slaveExpFactor);
    float SlaveReleasedValue = curveFilter(slaveReleasedValue, slaveReleasedValue, slaveFullyPressedValue, slaveCurvePush, slaveExpFactor);
    float SlaveValue = curveFilter(slaveRaw, slaveReleasedValue, slaveFullyPressedValue, slaveCurvePush, slaveExpFactor);

    if (SlaveFullyPressedValue > SlaveReleasedValue)
    {
        float gap = SlaveFullyPressedValue - SlaveReleasedValue;
        float normFactor = 1000 / gap;
        slaveNormalized = normFactor * (SlaveValue - SlaveReleasedValue);
        if (slaveNormalized < 0)
        {
            slaveNormalized = 0;
        }
    }
    else if (SlaveFullyPressedValue < SlaveReleasedValue)
    {
        SlaveValue = SlaveReleasedValue - SlaveValue;

        float gap = SlaveReleasedValue - SlaveFullyPressedValue;
        float normFactor = 1000 / gap;
        slaveNormalized = normFactor * SlaveValue;
        if (slaveNormalized < 0)
        {
            slaveNormalized = 0;
        }
    }

    total[S] = total[S] - readings[S][readIndex[S]];
    readings[S][readIndex[S]] = slaveNormalized;
    total[S] = total[S] + readings[S][readIndex[S]];

    readIndex[S]++;

    if (readIndex[S] > (reads - 1))
    {
        readIndex[S] = 0;
    }

    average[S] = total[S] / reads;
    if (average[S] > 1000)
    {
        average[S] = 1000;
    }

    //------------------------------------------
    //------SETTING BITE POINT WITH BUTTON------
    //------------------------------------------

    if (max(average[S], average[M]) > 0 && pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
    {
        bitePoint = max(average[S], average[M]);
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

        if ((average[S] == 0 || average[M] == 0 || (average[S] > bitePoint && average[M] < bitePoint)) || (average[M] > bitePoint && average[S] < bitePoint))
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
        if (throttleMaster)
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
    push = push << (2 * (FieldPlacement - 1));
    rotaryField = rotaryField | push;

}
