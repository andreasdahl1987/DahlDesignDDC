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

This is how we've planned and  wired the switches:

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

### External ADCs and oversampling

The output channels wants to know a pin number. However, when you're using external ADCs you don't really have pin numbers. And when we activate oversampling for the RP2040, the ADC meassurements are piled up in a buffer and averaged, we're not reading them directly. So which pin numbers do we type in?

In these cases, we'll use the keyword **"ADC",** which makes all the functions for analog switches look for data in the right places.&#x20;

#### Oversampling

When oversampling is enabled, you need to add a minimum of 4 analog channels, one for each pin (A0 - A3). Even if you're not using all 4 pins, you should still add 4 analog channels, since the process of oversampling requires some place to store the data - which would be in an analog channel. As mentioned above, we'll be using the keyword **"ADC":**

* A0 -> ADC1
* A1  -> ADC2
* A2 -> ADC3
* A3 -> ADC4

So, if we're looking at the case further up, an imagine this being an RP2040 board with oversampling enabled, it would look like this instead:

```
//---------------------------------------
//--------ANALOG CHANNEL SETUP-----------
//---------------------------------------

#define analogChannelCount 4                             //Number of analog channels

uint8_t analogPins[analogChannelCount] =                 //Pin number for your analog channels
{ ADC1, ADC2, ADC3, ADC4 };

uint8_t analogButtonNumber[analogChannelCount] =         //Button number for your analog channels
{ 11,  0,  0,  0 };

uint8_t analogButtonNumberIncMode[analogChannelCount] =  //Button number for alternate modes
{ 23,  0,  0,  0 };

```

Lets say you're only using the A2 pin; you'd still have to set up all 4 channels like this and you'd be refering to channel 3 (ADC3) when using switch functions.&#x20;

#### External ADC

When using external ADCs (ADS1115), you should set up 4 analog channels for each ADC chip. These will correspond to the A0 - A3 pins. With several ADCs you'll just have to keep adding 4 channels.&#x20;

ADS1115 # 1:

* A0 -> ACD1
* A1 -> ADC2
* A2 -> ADC3
* A3 -> ADC4

ADS1115 #2:

* A0 -> ADC5
* A1 -> ADC6
* A2 -> ADC7
* A3 -> ADC8

..and so on.

Now, if you have **enabled oversamling** as well, the first 4 channels will be reserved, and your external ADCs will start on channel 5 with pin number "ADC5".&#x20;

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
