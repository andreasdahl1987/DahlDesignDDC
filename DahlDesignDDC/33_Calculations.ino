float curveFilter(int input, int releasedValue, int pressedValue, int curvePush, float expFactor)
{
    float Input = input;
    int PressedValue = pressedValue;
    int ReleasedValue = releasedValue;

    if (curvePush == 0)
    {
        return Input;
    }

    if (curvePush < 0)
    {
        if (releasedValue < pressedValue)
        {
            PressedValue = PressedValue - clutchTopDeadzone;
            ReleasedValue = ReleasedValue + clutchBottomDeadzone;
            if (Input < ReleasedValue)
            {
                Input = ReleasedValue;
            }
            if (Input > PressedValue)
            {
                Input = PressedValue;
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
            if (Input < PressedValue)
            {
                Input = PressedValue;
            }
            Input = (ReleasedValue - Input) * pow((1 + ReleasedValue - Input), expFactor);
        }
    }
    else if (curvePush > 0)
    {
        if (ReleasedValue < PressedValue)
        {
            if (Input < ReleasedValue)
            {
                Input = ReleasedValue;
            }
            if (Input > PressedValue)
            {
                Input = PressedValue;
            }
            Input = (PressedValue - Input) * pow((1 + PressedValue - Input), expFactor);
        }
        else if (PressedValue < ReleasedValue)
        {
            if (Input > ReleasedValue)
            {
                Input = ReleasedValue;
            }
            if (Input < PressedValue)
            {
                Input = PressedValue;
            }
            Input = (Input - PressedValue) * pow((1 + Input - PressedValue), expFactor);
        }
    }

    return Input;
}
