void brakeMagic(int row, int column)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int FieldPlacement = 4;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    //Change switch mode
    if (pushState[Row][Column] == 0)
    {
        switchModeLock[Row][Column] = false;
    }

    if (((globalClock - switchTimer[Row][Column]) < buttonCooldown) && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && !switchModeLock[Row][Column])
    {
        switchModeLock[Row][Column] = true;
        switchMode[Row][Column] = !switchMode[Row][Column];
        latchLock[Row][Column] = false;
        latchState[Row][Column] = false;
        Joystick.setButton(Number, 0);
    }

    //Push switch mode
    long push = 0;
    push = push | switchMode[Row][Column];
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;

    brakeMagicOn = false;

    //SWITCH MODE 1: Brake magic
    if (!switchMode[Row][Column])
    {
        if (pushState[Row][Column] == 1)
        {
            brakeMagicOn = true;
        }
        else
        {
            brakeMagicOn = false;
        }

        if (pushState[Row][Column] == 1 && !latchState[Row][Column])
        {
            latchLock[Row][Column] = true;
        }

        if (pushState[Row][Column] == 1 && latchLock[Row][Column])
        {
            Joystick.setBrake(brakeMagicValue);
            latchState[Row][Column] = true;

            long push = 1;
            push = push << 6;
            buttonField = buttonField | push;
        }

        if (pushState[Row][Column] == 0 && latchState[Row][Column])
        {
            Joystick.setBrake(0);
            latchState[Row][Column] = false;
            latchLock[Row][Column] = false;

            long push = 0;
            push = push << 6;
            buttonField = buttonField | push;
        }
    }

    //SWITCH MODE 2: PULSE
    if (switchMode[Row][Column])
    {
        if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
        {
            toggleTimer[Row][Column] = globalClock;
        }

        if ((globalClock - toggleTimer[Row][Column]) < togglePulse)
        {
            Joystick.setButton(Number, 1);
        }
        else
        {
            Joystick.setButton(Number, 0);
        }
    }
}

