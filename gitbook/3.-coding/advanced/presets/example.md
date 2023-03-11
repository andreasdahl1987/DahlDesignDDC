# Example

Here is an example of a setup using both preset functions:

What I want to achieve:

* The function multiFunction2Bit24() will use a 2-bit encoder and a 12-position switch (resistor ladder switch) together to make a 24-position complex. Basically the position of the 12-position switch determines the button numbers for the encoder, making it very valuable for setting up in-car adjustments and other things.
*   I want:

    * &#x20;MultiFunction setup in presets 1-4
    * 12-position switch and incremental encoder separated in presets 5-8
    * Both switches work as incremental encoders in  presets 9-11
    * Preset 12 is for rally, so I want my thumb encoders inactive in this preset. I tend to hit them when the wheel goes wild and I dont want any stray button presses. I want the 12 position switch back to a MultiFunction function, but now with two buttons instead of the encoder.&#x20;



The first thought when setting this up would be on the button numbering. Lets say I reserve button numbers 1-24 for the MultiFunction. If the MultiFunction is not used, the 12 position switch only needs the first 12 button numbers, 1-12, and the remaining 13-24 are free. So the 12-position switch can use buttons 13+14 in incremental mode, and the encoder can use button numbers 15+16. The two buttons used in MultiFunction in preset 12 needs to be able to use in presets 1-4 as well, when the encoder is used in MultiFunction - so these buttons need numbers higher than 24.&#x20;

Lets say for this example that:

* 12-position switch is analog switch #1, wired to arduino pin A3
* Encoder is wired to Row 1, Columns 4+5
* The two buttons are on Row 3 Column 3 and Row 4 Column 2.&#x20;

The 10\_MatrixAndAnalog.ino might look a bit like this

```
//------------------------------
//-------MATRIX VARIABLES-------
//------------------------------

uint8_t row[] = {2, 3, 4, 6};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = {10, 15, 14, 16, 5};
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

bool nonMatrixIncluded = false;

uint8_t nonMatrix[] = {0};
const uint8_t nonMatrixCount = sizeof(nonMatrix) / sizeof(nonMatrix[0]);

//---------------------------------------
//--------MATRIX DESCRIPTION-------------
//---------------------------------------

const uint8_t buttonNumber[rowCount][colCount] =
{
  {26, 27, 28, 14, 0},     //ROW 1
  {40, 35, 36, 37, 38},    //ROW 2
  {39, 29, 24, 30, 31},    //ROW 3
  {41, 25, 34, 32, 33}     //ROW 4
};

//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

const uint8_t analogButtonNumber[10] =         //ANALOG BUTTONS 1
{ 0, 42, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint8_t analogButtonNumberIncMode[10] =  //ANALOG BUTTONS 2
{ 12, 54, 0, 0, 0, 0, 0, 0, 0, 0 };
```

Now, for the setup in 30\_Switches.ino, none of these 4 switches that will swap functions should be mentioned there. They should all be sorted out in 31\_RunningPresets.ino, and each preset should handle these switches somehow. If the switches are also given a function in 30\_Switches.ino, that will override anything written in 31\_RunningPresets.ino.

31\_RunningPresets.ino setup:

```
void runningPresets()
{
    /*
    This function runs in the loop, meaning the stuf you write here will be computed continously. Under the presets() function, the changes just
    happens once after you switch preset. This is great for static stuf like switch modes, bite point, etc. But if you set a bite point here, you won't
    be able to change it with your rotary, since it will continously be updated to the value you set here. 
    This area is mainly for changing switch function assignments. If you want your 12-way to have a regular 12-position mode in ACC, but use a 
    multiComplex24 function (which includes other pushbuttons) in another preset, this is where you set it. You might want to use a HybridSwitch in one 
    preset, and since hybrid buttons dont produce a button number, this button is lost in other presets that are meant for sims that dont support 
    this kind of switch. You could then use runningPresets() to set hybridButton(1,2); in all presets except the one you use
    for F1 2022, where it would be pushButton(1,2);. Just examples, use your imagination. Setting up parts of your controller in this function can make 
    your controller very flexible.    
    */

    switch (switchPreset)
    {
    case 0: //PRESET 1 
        multiFunction2Bit24(A3, 1, 1, 4, false, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);
        pushButton(3,3);
        pushButton(4,2);
        break;
        
    case 1: //PRESET 2 
        multiFunction2Bit24(A3, 1, 1, 4, false, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);
        pushButton(3,3);
        pushButton(4,2);
        break;
        
    case 2: //PRESET 3 
        multiFunction2Bit24(A3, 1, 1, 4, false, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);
        pushButton(3,3);
        pushButton(4,2);
        break;
        
    case 3: //PRESET 4 
        multiFunction2Bit24(A3, 1, 1, 4, false, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);
        pushButton(3,3);
        pushButton(4,2);
        break;
    case 4: //PRESET 5 
        rotaryAnalog2Mode(A3, 1, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        pushButton(3,3);
        pushButton(4,2);
        rotary2Inc(1,4);
        
        break;
    case 5: //PRESET 6         
        rotaryAnalog2Mode(A3, 1, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        pushButton(3,3);
        pushButton(4,2);
        rotary2Inc(1,4);
        break;
        
    case 6: //PRESET 7 
        rotaryAnalog2Mode(A3, 1, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        pushButton(3,3);
        pushButton(4,2);
        rotary2Inc(1,4);
        break;
        
    case 7: //PRESET 8 
        rotaryAnalog2Mode(A3, 1, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        pushButton(3,3);
        pushButton(4,2);
        rotary2Inc(1,4);
        break;
        
    case 8: //PRESET 9 
        rotaryAnalog2Mode(A3, 1, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        pushButton(3,3);
        pushButton(4,2);
        rotary2Inc(1,4);
        break;
        
    case 9: //PRESET 10
        rotaryAnalog2Mode(A3, 1, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        pushButton(3,3);
        pushButton(4,2);
        rotary2Inc(1,4);
        break;
        
    case 10: //PRESET 11 
        rotaryAnalog2Mode(A3, 1, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        pushButton(3,3);
        pushButton(4,2);
        rotary2Inc(1,4);
        break;
        
    case 11: //PRESET 12 
        multiFunction2Button24(A3, 1, 3, 3, 4, 2, false, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
        rotary2Inc(1,4);
        break;
    }
}
```

Note that to inactivate the encoder in preset 12, I just had to **not** call the encoder function.&#x20;

Now that the correct **switch functions** are used in each presets, we'll have to use 41\_Presets.ino to set the correct **switch modes** in each preset. When presets(int8\_t presetNumber) is run, all switch modes are set to 0. So only the switches that needs to be in a mode other than 0 needs to be included. In this case that means only the 12-position switch in presets 9-11, where it will be in mode 1.&#x20;

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
        analogSwitchMode1[0] = 1;
        break;
        
    case 9: //PRESET 10
        analogSwitchMode1[0] = 1;
        break;
        
    case 10: //PRESET 11 
        analogSwitchMode1[0] = 1;
        break;
        
    case 11: //PRESET 12 

        break;
    }
}
```

