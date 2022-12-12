# 30\_Switches

This is where you add all your switches. Go to the [Switch Library](https://github.com/andreasdahl1987/DahlDesignDDC/wiki/Switch-functions#library) and find something that suits your needs. Anything you write here should be between the hard-to-miss warnings **"SWITCHES START HERE"** and **"SWITCHES END HERE"**

```
//------------------------------
//-----------LOOP---------------
//------------------------------

void loop()
{

    //-------------------------
    //-----ESSENTIALS----------
    //-------------------------

    globalClock = millis();
    
    rotaryField = 0;
    buttonField = 0;
    matrix();

    runningPresets();

    //------------------------------------
    //---------SWITCHES START HERE--------
    //------------------------------------




    //------------------------------------
    //----------SWITCHES END HERE---------
    //------------------------------------


    Joystick.setZAxis(rotaryField - 32768);
    Joystick.setYAxis(buttonField - 32768);

    Joystick.sendState();
}
```

* A full steering wheel could look like this:

```
//------------------------------
//-----------LOOP---------------
//------------------------------

void loop()
{

    //-------------------------
    //-----ESSENTIALS----------
    //-------------------------

    globalClock = millis();

    encoderField = 0;
    buttonField = 0;
    matrix();

    runningPresets();

    //------------------------------------
    //---------SWITCHES START HERE--------
    //------------------------------------


    //WHEEL BUTTONS

    pushButton(1, 3);

    pushButton(3, 1);
    pushButton(3, 2);

    pushButton(4, 3);
    pushButton(4, 4);
    pushButton(4, 6);
    pushButton(4, 7);

    pushButton(6, 4);
    pushButton(6, 7);

    pushButton(7, 1);
    pushButton(7, 3);

    pushPull(3, 3, 3, 4, 6, 6, 6, 5, 7);

    toggleM(6, 3, 6);
    brakeMagic(7, 2, 4);

    //SPECIALS

    modButton(1, 7);
    neutralButton(4, 5);
    biteButton(1, 5);
    presetButton(1, 6);
    quickSwitch(1, 4);
    throttleHold(3, 5, 7, 4, true);

    //ENCODERS

    rotary2Inc(1, 1, false);
    rotary2Inc(4, 1, false);

    rotary2Inc(3, 6, true);
    rotary2Inc(6, 1, false);


    //FUNKY SWITCHES
    funkyButtonDDButton(5, 4, 5, 1, 6, 7);
    funkyButtonHybrid(5, 6, 5, 1, 4, 7);
    funkyButton(5, 1, 5, 4, 6, 7);
    funkyButton(5, 7, 5, 1, 4, 6);
    funkyPush(5, 5, 1, 4, 6, 7);

    DDSfunky(5, 2, 3);

    funkyButton(2, 1, 5, 2, 4, 7);
    funkyButton(2, 2, 5, 1, 4, 7);
    funkyButton(2, 4, 5, 1, 2, 7);
    funkyButton(2, 7, 5, 1, 2, 4);
    funkyPush(2, 5, 1, 2, 4, 7);
    funkyRotary(2, 3, 6);

    //ANALOG INPUTS


    rotaryLeft(
        A3,                                                           //Analog pin to read
        1,                                                            //Analog switch #
        3,                                                            //Field placement
        16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,   //Switch position values
        false);                                                        //Rotation direction

    rotaryRight(
        A1,                                                           //Analog pin to read
        2,                                                            //Analog switch #
        2,                                                            //Field placement
        16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,   //Switch position values
        false);                                                        //Rotation direction

    dualClutch(
        A2,                                                           //Analog pin to read (Master)
        3,                                                            //Analog switch # (Master)
        571,                                                          //Released value (Master
        169,                                                          //Fully pressed value (Master)
        A5,                                                           //Analog pin to read (Slave)
        4,                                                            //Analog switch # (Slave)
        527,                                                          //Released value (Slave)
        882,                                                          //Fully pressed value (Slave)
        true);                                                        //True = Master/Slave paddle is Throttle/Brake in mode 4. False is opposite.

   
    //------------------------------------
    //----------SWITCHES END HERE---------
    //------------------------------------


    Joystick.setZAxis(encoderField - 32768);
    Joystick.setYAxis(buttonField - 32768);

    Joystick.sendState();
}
```

#### Non-matrix switches

* You might have asked yourself how your non-matrix switches has found their way to the matrix so far. They haven't, they're still floating around. Your non-matrix switches needs to have their values read and that value conveyed to a dedicated matrix adress. From there, the switch now behaves as any switch in the button matrix, and allows you to use any fuction that works with a matrix-wired button.
* The `matrixInject()` function shold be used for every pin on the Arduino that is used for non-matrix switches.
* The function needs to know the pin number to read, the matrix row and the matrix column. Like this:

`matrixInject(pin, row, column);`

* If you planned with an encoder on row 1, using column 1 and 2, and using physical Arduino pins 10 and 14, add this:

`matrixInject(10, 1, 1);`

`matrixInject(14, 1, 2);`

* If you planned with a button on row 2, using column 5, and using physical Arduino pin 9, add this:

`matrixInject(9, 2, 5);`

* All instances of `matrixInject()` should be called **before** any switch functions.
