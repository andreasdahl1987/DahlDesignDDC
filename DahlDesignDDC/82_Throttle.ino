void throttle(int analogChannel, int releasedValue, int fullyPressedValue)
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

    if (readIndex[N] > (reads - 1))
    {
        readIndex[N] = 0;
    }

    average[N] = total[N] / reads;
    if (average[N] > 1000)
    {
        average[N] = 1000;
    }

    //----------------SET AXIS----------------
    Joystick.setThrottle(average[N]);
}

void filteredThrottle(int8_t analogChannel, int releasedValue, int fullyPressedValue, int curvePush, float expFactor)
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

    //----------------SET AXIS----------------
    Joystick.setThrottle(average[N]);
}
