# Presets

Presets is one of the key features of DDC. Since this firmware gives so much freedom with regards to customization, it would be nice to quickly swap between highly customized and car/sim-specific setups. This is what presets are for, and you have 12 of them. _**Any relevant thing can be put into a preset**_. A preset can fundamentally change the way the controller works. You can have one preset with loads of fancy functions, using 100 + button numbers, and one preset where none of the buttons work. And everything in between.

**By default the controller will boot in preset 1.** However, some switch functions will allow you to boot to the  preset corresponding to the physical position of that switch.&#x20;

There are two files related to the preset system:

`31_RunningPresets.ino`, holding the `runningPresets()` function

`41_Presets.ino`, holding the `presets(int presetNumber)` function

These are both relevant to you, and work in completely different ways:

### 31\_RunningPresets.ino

The `runningPresets()` function is added by default, and if you don't want to use it you can just leave it there. It is placed before any other function call. Like so:

```
//-------------------------
//-----ESSENTIALS----------
//-------------------------

globalClock = millis();

encoderField = 0;
buttonField = 0;
matrix();

runningPresets();

//-------------------------
//---------SWITCHES--------
//-------------------------

pushButton(3, 1);
pushButton(3, 2);
pushButton(4, 3);
pushButton(4, 4);
pushButton(4, 6);
pushButton(4, 7);

pushButton(6, 4);
pushButtonM(6, 7, 1);

pushButton(7, 1);
pushButton(7, 3);

....and so on

```

Let's have a look at that `runningPresets` does:

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

There is a desciption in the file itself, but I'll elaborate. Since we're in `30_Switches.ino`, the function is in the `loop()`, meaning whatever is in the function will be read and performed by the microcontroller about 200-1000 times per second, depending on how heavy your DDC sketch is. If you set the bite point to 23% in this function, you can never change it on the controller, because it will be set back to 23% right away. If you set up a switch mode here, you can never change to a different switch mode on that switch, since the switch mode will be set on every loop.

This function basically creates 12 alternative versions of the loop, so only things that belongs to `30_Switches.ino` in the first place goes here, typically the switch functions. If you move a switch function from `30_Switches.ino` to `runningPresets()`, make sure to delete it from `30_Switches.ino`, since `runningPresets()`is now running this switch function.

### 41\_Presets.ino

In contrast to `runningPresets(),` the presets(int8\_t presetNumber) function is not in the loop. It will only be performed under special circumstances. Such as changing from one preset to another. It that case it will be run **once. So here goes everything that you want your presets to start with, and unlike** `runningPresets()` again, it will not stick this way. So you'll set up bite point values, switch modes and many other things here. Likely, this is where most of your preset setup will happen.

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



An example of what you could do with this:

* The function multiComplex24() will use a 2-bit encoder and a 12-position switch (resistor ladder switch) together to make a 24-position complex. Basically the position of the 12-position switch determines the button numbers for the encoder, making it very valuable for setting up in-car adjustments and other things.
* You might not need this setup in all your presets, so you'd want:
  * &#x20;multiComplex setup in presets 1-4
  * 12-position switch and incremental encoder seperated in presets 5-8
  * Both switches work as incremental encoders in  presets 9-12
