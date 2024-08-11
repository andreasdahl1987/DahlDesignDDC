---
description: 'Analog channels are built at the bottom of the 10_TableAndAnalog.ino:'
---

# Analog channels

```
//---------------------------------------
//--------ANALOG CHANNEL SETUP-----------
//---------------------------------------

#define analogChannelCount 1                             //Number of analog channels

uint8_t analogPins[analogChannelCount] =                 //Pin number for your analog channels
{ 99 };

uint8_t analogButtonNumber[analogChannelCount] =         //Button number for your analog channels
{ 0 };

uint8_t analogButtonNumberIncMode[analogChannelCount] =  //Button number for alternate modes
{ 0 };

```

By default only one channel is set up, with a nonsense pin number and button number set to 0. If you don't have any analog switches, you can leave it like this.&#x20;

Lets say we have 4 analog switches; two 12-position rotaries and two clutch paddles. We'll have to set up 4 analog channels.&#x20;

This is how we're planned and  wired the switches:

1. 12-position switch, wired to pin A0, will have both 12-position and incremental mode. Should use button numbers 11-22 in 12-position mode and 23-24 in incremental mode.
2. 12-position switch, wired to pin A5, will have only 12-position mode. Should use button numbers 0-11.
3. Master clutch paddle, wired to pin A3. Doesn't need any button numbers.
4. Slave clutch paddle, wired to pin A2. Doesn't need any button numbers.&#x20;

Our code will look like this:

```
//---------------------------------------
//--------ANALOG CHANNEL SETUP-----------
//---------------------------------------

#define analogChannelCount 4                             //Number of analog channels

uint8_t analogPins[analogChannelCount] =                 //Pin number for your analog channels
{ A0, A5, A3, A2 };

uint8_t analogButtonNumber[analogChannelCount] =         //Button number for your analog channels
{ 11,  0,  0,  0 };

uint8_t analogButtonNumberIncMode[analogChannelCount] =  //Button number for alternate modes
{ 23,  0,  0,  0 };

```

**Note that we increased `analogChannelCount` to 4.** We also had add new elements to the arrays below to fill in the channel details.&#x20;

To help visualize our channels:

<figure><img src="../../../.gitbook/assets/image (13) (1).png" alt=""><figcaption></figcaption></figure>

Pin numbering is fairly straight forward. Button numbers follow the same rules as with encoders:

* If your multiposition switch is used solely as an incremental switch, the starting button number goes in the top box. "0" in bottom box.
* If your multiposition switch is used solely as a multiposition switch, the starting button number goes in the top box. "0" in bottom box.
* If your multiposition switch uses a function with both multiposition mode and incremental mode, the starting button number for multiposition mode goes in the top box and starting button number for incremental mode goes in the bottom box.

Our 12-position switch on channel 2 starts with button number 0, so we'll keep the 0 in the top box. Clutches dont have button numbers, so they'll all stay at default 0. Actually, for a button number that isn't in use you can write anything. So if writing "12345" instead works better for you, go ahead. This goes for both analog channels and the switch table.

### Reading a value

A lot of the functions handeling analog switches need some reference values, these will have to be read from the switch. DDC has a function to read a value from an analog pin or an external ADC channel, `checkValue()`. If you have a pair of dual clutches on analog channels 3 and 4, just the readouts to 30\_Switches.ino like this:

```
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  checkValue(3);
  checkValue(4);
  
  
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

Upload the code and check the serial monitor for the values.&#x20;

_Remember to remove `checkValue()` from your code when you're finishing the project, it can interfere a lot with the controllers communication with the computer._

With all this set up, you can start using your analog channels in 30\_Switches.ino.
