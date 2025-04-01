# 30\_Switches.ino

This is where you add all your switches. Go to the [Switch Library](../../switch-library/) and find something that suits your needs. Anything you write here should be between the hard-to-miss warnings **"SWITCHES START HERE"** and **"SWITCHES END HERE"**

A simple pushbutton on row 3, column 1 would be written as `pushButton(3,1);`

### Direct wiring

With matrix wiring or shift register wiring, you will just use the switch table adresses in the switch functions as explained [below.](30_switches.md#setup) However, with [direct wiring](../../2.-wiring/switch-inputs/non-matrix-wiring.md), you'll have to add some extra lines.

* You might have asked yourself how your direct wired switches has found their way to the switch table so far. They haven't, they're still floating around. Your direct wired switches needs to have their values read and that value conveyed to a dedicated adress in the table. From there, the switch now behaves as any switch in the switch table, and allows you to use any fuction that works with a matrix wired or shift register wired button.
* The `switchTableInject()` function shold be used for every pin on the Arduino that is used for direct wired switches.
* The function needs to know the pin number to read, the table row and the table column. Like this:

`switchTableInject(pin, row, column);`

* If you planned with an encoder on row 1, using column 1 and 2, and using physical Arduino pins 10 and 14, add this:

`switchTableInject(10, 1, 1);`

`switchTableInject(14, 1, 2);`

* If you planned with a button on row 2, using column 5, and using physical Arduino pin 9, add this:

`switchTableInject(9, 2, 5);`

* All instances of `switchTableInject()` should be called **before** any switch functions.

### Setup

This is what the empty 30\_Switches looks like:

```
//------------------------------------
//---------SWITCHES START HERE--------
//------------------------------------




//------------------------------------
//----------SWITCHES END HERE---------
//------------------------------------

Joystick.setZAxis(rotaryField - 32767);
Joystick.setYAxis(buttonField - 32767);

Joystick.sendState();

}

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 2)
  void loop()
  {
    processCommands();
  }
#endif
```

* A full (and rather feature rich) steering wheel could look like this:

```
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


    rotaryAnalog2Mode(
        1                                                             //Analog channel
        3,                                                            //Field placement
        16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,   //Switch position values
        false);                                                       //Rotation direction

    rotaryAnalog2Mode(
        2,                                                            //Analog channel
        2,                                                            //Field placement
        16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,   //Switch position values
        false);                                                       //Rotation direction

    dualClutch(
        3                                                             //Analog channel (Master)
        571,                                                          //Released value (Master
        169,                                                          //Fully pressed value (Master)
        4,                                                            //Analog channel (Slave)
        527,                                                          //Released value (Slave)
        882,                                                          //Fully pressed value (Slave)
        true);                                                        //True = Master/Slave paddle is Throttle/Brake in mode 4. False is opposite.

   
//------------------------------------
//----------SWITCHES END HERE---------
//------------------------------------

Joystick.setZAxis(rotaryField - 32767);
Joystick.setYAxis(buttonField - 32767);

Joystick.sendState();

}

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 2)
  void loop()
  {
    processCommands();
  }
#endif
}
```

