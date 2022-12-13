# 41\_Presets.ino

In contrast to `runningPresets(),` the `presets(int8_t presetNumber)` function is not in the loop. It will only be performed under special circumstances, and you dont have to worry about writing this function anywhere in the code. It will automatically run when changing from one preset to another. It that case it will be run **once.** So here goes everything that you want your presets to start with, and unlike `runningPresets(),` it will not stick this way. So you'll set up bite point values, switch modes and many other things here. Likely, this is where most of your preset setup will happen.

```
void presets(int8_t presetNumber)
{
    int8_t PresetNumber = presetNumber;

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
    for (int i = 0; i < 4; i++)
    {
        analogSwitchMode1[i] = 0;
        analogSwitchMode2[i] = 0;
    }

    //Default values set

    bitePoint = 300;
    brakeMagicValue = 50;
    throttleHoldValue = 1000;
    quickValue4 = 11;
    quickValue3 = 11;
    quickValue2 = 11;
    quickValue1 = 11;

    //----------------------------------------
    //-----BUILD YOUR PRESETS HERE------------
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
```

As an example, setting up bite points would be a simple thing to do. Lets say you make your presets 1-4 for your favourite cars; Dallara F3, Porsche 992 Cup, Mercedes AMG GT3 and Formula 4. You know the bite points for these cars and want it in the wheel. As a default, bite point is set to "300", which is 30.0%. And unless you change it in a preset it will stay at that value.&#x20;

This is how I'd set it up:

```
void presets(int8_t presetNumber)
{
    int8_t PresetNumber = presetNumber;

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
    for (int i = 0; i < 4; i++)
    {
        analogSwitchMode1[i] = 0;
        analogSwitchMode2[i] = 0;
    }

    //Default values set

    bitePoint = 300;
    brakeMagicValue = 50;
    throttleHoldValue = 1000;
    quickValue4 = 11;
    quickValue3 = 11;
    quickValue2 = 11;
    quickValue1 = 11;

    //----------------------------------------
    //-----BUILD YOUR PRESETS HERE------------
    //----------------------------------------

    switch (presetNumber)
    {
    case 0: //PRESET 1 - Dallara F3
        bitePoint = 285;
        break;
    case 1: //PRESET 2 - Porsche 992 Cup Car
        bitePoint = 360;
        break;
    case 2: //PRESET 3 - Mercedes AMG GT3
        bitePoint = 425;
        break;
    case 3: //PRESET 4 - iR Formula 4
        bitePoint = 225;
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
```
