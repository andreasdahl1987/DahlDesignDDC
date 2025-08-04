void bitePot(int analogChannel, int startValue, int endValue)
{
    Joystick.setRyAxisRange(0, 1000);

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

    if (endValue > startValue)
    {
        endValue = endValue - clutchTopDeadzone;
        startValue = startValue + clutchBottomDeadzone;
        float gap = endValue - startValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (pinValue - startValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }
    else if (endValue < startValue)
    {
        endValue = endValue + clutchTopDeadzone;
        startValue = startValue - clutchBottomDeadzone;
        float gap = startValue - endValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (startValue - pinValue);
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
    bitePoint = average[N];

    if (!bitePotLock)
    {
      Joystick.setRyAxis(bitePoint);
    }

}

void filteredBitePot(int8_t analogChannel, int startValue, int endValue, int curvePush, float expFactor)
{
    Joystick.setRyAxisRange(0, 1000);

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
    float EndValue = curveFilter(endValue, startValue, endValue, curvePush, expFactor);
    float StartValue = curveFilter(startValue, startValue, endValue, curvePush, expFactor);
    float pinValue = curveFilter(raw, startValue, endValue, curvePush, expFactor);

    if (EndValue > StartValue)
    {
        float gap = EndValue - StartValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (pinValue - StartValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }
    else if (EndValue < StartValue)
    {
        pinValue = StartValue - pinValue;

        float gap = StartValue - EndValue;
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
    bitePoint = average[N];
    
    if (!bitePotLock)
    {
      Joystick.setRyAxis(bitePoint);
    }
}
