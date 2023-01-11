void throttle(int analogPin, int switchNumber, int releasedValue, int fullyPressedValue)
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

void filteredThrottle(int analogPin, int8_t switchNumber, int releasedValue, int fullyPressedValue, int curvePush, float expFactor)
{
    int inputPin = analogPin;
    int raw = analogRead(inputPin);
    int N = switchNumber - 1;
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