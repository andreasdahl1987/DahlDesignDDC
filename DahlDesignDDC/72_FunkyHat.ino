void funkyHat(int8_t row, int8_t colUp, int8_t colRight, int8_t colDown, int8_t colLeft, int8_t hatNumber)
{
    int8_t Row = row - 1;

    int8_t ColUp = colUp - 1;
    int8_t ColRight = colRight - 1;
    int8_t ColDown = colDown - 1;
    int8_t ColLeft = colLeft - 1;

    int8_t HatNumber = hatNumber - 1;
    int hatValue = 0;
    int8_t hatCounter = 0;
    int8_t hatCols[4] = { ColUp, ColRight, ColDown, ColLeft };
    int8_t hatPresses[4] = { 0,0,0,0 };

    //Debouncing + hat set

    for (int i = 0; i < 4; i++)
    {
        if (pushState[Row][hatCols[i]] != rawState[Row][hatCols[i]] && (globalClock - switchTimer[Row][hatCols[i]]) > buttonCooldown)
        {
            switchTimer[Row][hatCols[i]] = globalClock;
            pushState[Row][hatCols[i]] = rawState[Row][hatCols[i]];
        }

        if ((globalClock - switchTimer[Row][hatCols[i]]) > buttonCooldown)
        {
            pushState[Row][hatCols[i]] = rawState[Row][hatCols[i]];
        }

        if (pushState[Row][hatCols[i]] == 1)
        {
            hatPresses[i] = (i);
            hatCounter++;
            hatValue = hatValue + (90 * hatPresses[i]);
        }
    }

    if (hatCounter == 0)
    {
        hatValue = -1;
    }
    else if (hatCounter == 2 && hatValue == 270)
    {
        hatValue = 315;
    }
    else
    {
        hatValue = hatValue / hatCounter;
    }

    Joystick.setHatSwitch(HatNumber, hatValue);
}
