# Essentials

## Setup prerequisites

This is a RP2040-type board, and you'll essentially treat it as a Raspberry Pi Pico board. Follow [these instructions](../../3.-coding/) to get ready to code.

## Board setup

The only thing you need to set up is in 2\_Board.ino. Have a look at the very top:

```
/*
 * Chose your board. Default is to 32U4-based boards. 
 */

//------------------------------
//-----------BOARD MCU----------
//------------------------------

#define BOARDTYPE 0

// 0 -> Atmel 32U4 based boards. (Leonardo, Pro Micro, Feather, Teensy 2.0, etc) SAM3X based boards. (Due)

// 1 -> SAMD21 or SAMD51 based boards. (Arduino Zero and many more)

// 2 -> RP2040 based boards. (Raspberry Pi Pico, Pico W, Pro Micro RP2040, and many more)


//------------------------------
//-------DAHL DESIGN CB1--------
//------------------------------

#define USING_CB1 0

```

To activate the pre-programmed features for you CB1, set the following:

`BOARDTYPE` to <mark style="background-color:green;">2</mark>

`USING_CB1` to <mark style="background-color:green;">1</mark>

That is all. Now, if you have removed components from the board or in general have some advanced setup for switches, have a look at [advanced settings.](settings.md)

### Analog switches

If you're using analog switches that will produce button numbers (typically rotary switches), you'll have to assign some button numbers to it. More on this in the [complete project example.](complete-project.md)

## Switch functions

We can move directly to start using switch functions now. This is all done in 30\_Switches.ino. The various functions used to add firmware code for our switches are found in the [library.](../../switch-library/)&#x20;

Lets say we have 4 [pushbuttons ](../../switch-library/pushbutton.md#pushbutton)wired to row 1, column pins 1-4. Open 30\_Switches tab and you'll find the area between "Switches start here" and "Switches end here" to be empty. The following is all you need:

```
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  pushButton(1,1);
  pushButton(1,2);
  pushButton(1,3);
  pushButton(1,4);

  //--------------------------------------
  //---------SWITCHES END HERE------------
  //--------------------------------------

	Joystick.setZAxis(rotaryField - 32767);
	Joystick.setYAxis(buttonField - 32767);

	Joystick.sendState();

} //LOOP ENDS HERE

#if (BOARDTYPE == 2)
  void loop()
  {
	#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
		processCommands();
	#endif
  #if(USING_CB1 == 1)
  CB1Oversampling();
  #endif
  }
#endif
```

You've now edited two numbers and written 4 lines of code, your firmware is ready to [upload.](../../3.-coding/upload.md)

Next, look at the [complete project ](complete-project.md)guide for a more comprehensive firmware setup.&#x20;
