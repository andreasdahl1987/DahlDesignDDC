void presets(int8_t presetNumber)
{

    //Clear all buttons
    for (int i = 0; i < BUTTONCOUNT; i++)
    {
        Joystick.setButton(i, 0);
    }

    //Clear all switch modes
    for (int i = 0; i < rowCount; i++)
    {
        for (int a = 0; a < colCount; a++)
        {
            switchMode[i][a] = 0;
        }
    }
    for (int i = 0; i < analogSwitchCount; i++)
    {
        analogSwitchMode1[i] = 0;
        analogSwitchMode2[i] = 0;
    }

    //----------------------------------------
    //-----------GLOBAL VALUES----------------
    //----------------------------------------

    bitePoint = 300;
    brakeMagicValue = 50;
    throttleHoldValue = 1000;
    quickValue4 = 11;
    quickValue3 = 11;
    quickValue2 = 11;
    quickValue1 = 11;

    //----------------------------------------
    //---------INDIVIDUAL VALUES--------------
    //----------------------------------------

    switch (presetNumber)
    {
    case 0: //PRESET 1 

        break;
    case 1: //PRESET 2 

        break;
    case 2: //PRESET 3 

        break;
    case 3: //PRESET 4 

        break;
    case 4: //PRESET 5 

        break;
    case 5: //PRESET 6 

        break;
    case 6: //PRESET 7 

        break;
    case 7: //PRESET 8 

        break;
    case 8: //PRESET 9 

        break;
    case 9: //PRESET 10

        break;
    case 10: //PRESET 11 

        break;
    case 11: //PRESET 12 

        break;
    }
}
