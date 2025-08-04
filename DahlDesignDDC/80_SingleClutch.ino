
void singleClutch(int analogChannel, int releasedValue, int fullyPressedValue)
{
    int N = analogChannel - 1;
  
    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1 || LOADCELL_ENABLED == 1)

    int pinValue;
    if (analogPins[N] > 49)
    {
      pinValue = ADS1115value[analogPins[N] - ADC_CORR];
    }
    else
    {
      pinValue = analogRead(analogPins[N]);
    }
    
    #else

    int pinValue = analogRead(analogPins[N]);
    
    #endif
    

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


    //----SETTING BITE POINT WITH BUTTON------

    if (average[N] > 0 && pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
    {
        bitePoint = average[N];
    }

    
    //----------LAUNCH BUTTON------------------

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

    //----------------SET AXIS----------------
    Joystick.setXAxis(average[N]);
}

void singleClutchCal(int analogChannel)
{
    int M = analogChannel - 1;
  
    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1 || LOADCELL_ENABLED == 1)

    uint16_t pinValue;
    if (analogPins[M] > 49)
    {
      pinValue = ADS1115value[analogPins[M] - ADC_CORR];
    }
    else
    {
      pinValue = analogRead(analogPins[M]);
    }
    
    #else

    uint16_t pinValue = analogRead(analogPins[M]);
    
    #endif
    
    
    float normalized = 0;
    masterRaw = pinValue;
    
    if (MFP > MFR)
    {
        float gap = MFP - MFR;
        float normFactor = 1000 / gap;
        if (pinValue < MFR)
        {
          pinValue = MFR;
        }
        normalized = normFactor * (pinValue - MFR);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }


    else if (MFP < MFR)
    {
        float gap = MFR - MFP;
        float normFactor = 1000 / gap;
        if (pinValue > MFR)
        {
          pinValue = MFR;
        }
        normalized = normFactor * (MFR - pinValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }


    total[M] = total[M] - readings[M][readIndex[M]];
    readings[M][readIndex[M]] = normalized;
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


    //----SETTING BITE POINT WITH BUTTON------

    if (average[M] > 0 && pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
    {
        bitePoint = average[M];
    }

    
    //----------LAUNCH BUTTON------------------

    if (launchButtonLatch)
    {
        average[M] = average[M] * bitePoint / 1000;
    }

    if (average[M] == 0)
    {
        analogLatchLock[M] = true;
    }

    if (average[M] == 1000 && analogLatchLock[M])
    {
        analogLatchLock[M] = false;
    }

    if (latchState[neutralButtonRow - 1][neutralButtonCol - 1])
    {
        Joystick.setXAxis(1000);
    }

    //----------------SET AXIS----------------
    Joystick.setXAxis(average[M]);
}

void filteredSingleClutch(int8_t analogChannel, int releasedValue, int fullyPressedValue, int curvePush, float expFactor)
{
    int N = analogChannel - 1;
  
    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1 || LOADCELL_ENABLED == 1)

    int raw;
    if (analogPins[N] > 49)
    {
      raw = ADS1115value[analogPins[N] - ADC_CORR];
    }
    else
    {
      raw = analogRead(analogPins[N]);
    }
    
    #else

    int raw = analogRead(analogPins[N]);
    
    #endif
    

    float normalized = 0;
    float FullyPressedValue = curveFilter(fullyPressedValue, releasedValue, fullyPressedValue, curvePush, expFactor);
    float ReleasedValue = curveFilter(releasedValue, releasedValue, fullyPressedValue, curvePush, expFactor);
    float pinValue = curveFilter(raw, releasedValue, fullyPressedValue, curvePush, expFactor);

    if (FullyPressedValue > ReleasedValue)
    {
        float gap = FullyPressedValue - ReleasedValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (pinValue - ReleasedValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }
    else if (FullyPressedValue < ReleasedValue)
    {
        pinValue = ReleasedValue - pinValue;

        float gap = ReleasedValue - FullyPressedValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * pinValue;
        if (normalized < 0)
        {
            normalized = 0;
        }
    }


    total[N] = total[N] - readings[N][readIndex[N]];
    readings[N][readIndex[N]] = normalized;
    total[N] = total[N] + readings[N][readIndex[N]];

    readIndex[N]++;

    if (readIndex[N] > (reads - 1))
    {
        readIndex[N] = 0;
    }

    average[N] = total[N] / reads;
    if (average[N] > 1000)
    {
        average[N] = 1000;
    }


    //----SETTING BITE POINT WITH BUTTON------

    if (average[N] > 0 && pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
    {
        bitePoint = average[N];
    }


    //----------LAUNCH BUTTON------------------

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

    //----------------SET AXIS----------------
    Joystick.setXAxis(average[N]);
}
