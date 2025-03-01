# Complete project

### Setup

To get a practical approach to learning DDC, we'll be making the firmware for the [example setup](../wiring.md#example).

Looking through the switch library, we've found the following functions that could be nice to have:

* Buttons
  * [modButton() ](../../switch-library/function-button.md#modbutton)to change clutch modes and rotary switch modes
  * [launchButton()](../../switch-library/pedals-and-paddles/bite-point-and-launch.md#launchbutton) for an optional 1-handed launch
  * [presetButton()](../../switch-library/function-button.md#presetbutton) to change presets with one of our rotary switches
  * [biteButton()](../../switch-library/pedals-and-paddles/bite-point-and-launch.md#launchbutton) to adjust the bite point of the dual clutches
  * [neutralButton()](../../switch-library/pedals-and-paddles/bite-point-and-launch.md#neutralbutton) to be able to set the car in neutral with a button press
  * [upshift()](../../switch-library/pedals-and-paddles/pushbutton.md#upshift) for the upshift paddle, extra double-shift safety
  * [pushButton()](../../switch-library/pushbutton.md#pushbutton) for the remaining buttons
* [toggleM() ](../../switch-library/pushbutton-1.md#togglem)for the toggle switch
* Funky
  * [funkyButton()](../../switch-library/funky-switch/directional.md#funkybutton) for funky directions
  * [funkyPush()](../../switch-library/funky-switch/center-push.md#funkypush) for funky center push
  * [funkyRotary() ](../../switch-library/encoders/funkyrotary.md#funkyrotary)for funky encoder
* Rotary switches
  * [rotaryAnalog2Mode()](../../switch-library/rotary-switches/rotaryanalog.md#rotaryanalog2mode) for two of the rotaries
  * [SW1PresetRotary()](../../switch-library/rotary-switches/sw1.md#sw1presetrotary) for one of them, being able to select presets
* [PEC11Brightness()](../../switch-library/led-control.md#pec11brightness) for one of the PEC11s, allowing it to change LED brightness
* [PEC11Bite()](../../switch-library/encoders/pec11.md#pec11bite) for the other PEC11, allowing it to change bite point
* [dualClutch() ](../../switch-library/pedals-and-paddles/clutch.md#dualclutch)for the two clutches

With this setup, all the buttons and switches will work like regular joystick switches on their own. All buttons will produce a button press with their designated number, the encoders will pulse button presses on CW and CCW rotation, and the rotary switches will have 12 button numbers each. The only exception being the neutral button which defaults to have no button number.&#x20;

**The special features** of these functions are "hidden" behind button/switch combinations, such as:

* Holding modButton and -&#x20;
  * pressing neutralButton will take it out of neutral mode and turn it into a regular button
  * rotating any of the 3 rotaries will toggle them between multiposition mode and incremental mode
  * turning the PEC11Brightness switch will turn up/down the brightness of the LEDs
  * pumping one of the clutches will scroll through the 4 clutch paddle modes
  * flicking the toggle switch will change the toggle between being a latching toggle or producing a short button pulse when changing position.&#x20;
* Launch button pressed while holding either clutch paddle completely pressed will drop the clutch output immediately to the bite point.
* Holding the Preset button while rotating the SW1PresetRotary switch will change preset. The position of the 12-position switch will reflect the selected preset.
* Pressing biteButton -&#x20;
  * while a clutch paddle is held will set the bite point to the current clutch output value
  * while rotating PEC11Bite will set the controller in bite setting mode, where you'll adjust the bite point with the encoder and click though more and more accurate settings with the biteButton; first 10's, then 1's and lastly 0.1\`s

### Digital switches

#### The switch table

Have a look at the switch table in the example project. Lets put our switches in there:

<figure><img src="../../.gitbook/assets/image (75).png" alt=""><figcaption></figcaption></figure>

**Now, we could leave it like this, no problem**. But a bit unsatisfactory to have a lot of unused button numbers. Lets tidy it up a bit. All unused button numbers we can set to anything we want. I'll set it to 0 just to make it more clean looking. Then I'll also mush the button numbering together to fill the gaps:

<figure><img src="../../.gitbook/assets/image (22).png" alt=""><figcaption></figcaption></figure>

Now, I'm not totally happy with the numbering. I want my shifters to be buttons 0 and 1 (1 and 2 in Windows), and then the toggle, then the 8 pushbuttons on row 1 + encoder push buttons. Then funky buttons and lastly the funky encoder and rotary encoders. So I'll flip it around a little like this:

<figure><img src="../../.gitbook/assets/image (33).png" alt=""><figcaption></figcaption></figure>

If you're familiar with DDC from before, the switch table setup is in **`10_TableAndAnalog.ino`**. The table here has no effect on your CB1 board, it has its own setup in **`9_CB1_Table.ino`**.

Now, in **`9_CB1_Table.ino`** you'll find the place to update this button numbering:

```
uint8_t buttonNumber[rowCount][colCount] =
{
  
  { 0, 1, 2, 3, 4, 5, 6, 7 },             //ROW 1, COLUMN 1-8

  { 8, 9, 10, 11, 12, 13, 14, 15 },       //ROW 2, COLUMN 1-8

  { 16, 17, 18, 19, 24, 25, 22, 23 },     //ROW 3, COLUMN 1-8

  { 24, 25, 26, 27, 28, 29, 30, 31 },     //ROW 4, COLUMN 1-8

  { 32, 33, 34, 35, 36, 37, 38, 39 },     //ROW 5, COLUMN 1-8

  { 40, 41, 42, 43, 44, 45, 46, 47 },     //ROW 6, COLUMN 1-8

  { 48, 49, 50, 51, 52, 53, 54, 55 },     //ROW 7, COLUMN 1-8

  { 56, 57, 58, 59, 60, 61, 62, 63 }      //ROW 8, COLUMN 1-8  
  
};
```

This table is the same as your spreadsheet table. Edit to match:

```
uint8_t buttonNumber[rowCount][colCount] =
{
  
  { 3, 4, 5, 6, 7, 8, 9, 10 },             //ROW 1, COLUMN 1-8

  { 18, 19, 13, 14, 15, 16, 17, 0 },       //ROW 2, COLUMN 1-8

  { 0, 0, 2, 0, 0, 0, 0, 0 },              //ROW 3, COLUMN 1-8

  { 0, 0, 0, 0, 0, 1, 0, 0 },              //ROW 4, COLUMN 1-8

  { 11, 20, 21, 12, 22, 23, 0, 0 },        //ROW 5, COLUMN 1-8

  { 0, 0, 0, 0, 0, 0, 0, 0 },              //ROW 6, COLUMN 1-8

  { 0, 0, 0, 0, 0, 0, 0, 0 },              //ROW 7, COLUMN 1-8

  { 0, 0, 0, 0, 0, 0, 0, 0 },              //ROW 8, COLUMN 1-8  
  
};
```

#### Switch functions

Following the examples in the switch library, lets set up our buttons and encoders with some switch functions to bring them to life. This is done in 30\_Switches.ino.&#x20;

```
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------
  
  modButton(1,1);
  biteButton(1,2);
  neutralButton(1,3);
  launchButton(1,4,1);
  presetButton(1,5);
  
  pushButton(1,6);
  pushButton(1,7);
  pushButton(1,8);
  
  funkyRotary(2,1,2,false);
  funkyButton(2,3,7,4,5,6);
  funkyButton(2,4,7,3,5,6);
  funkyButton(2,5,7,3,4,6);
  funkyButton(2,6,7,3,4,5);
  funkyPush(2,7,3,4,5,6);
  
  toggleP(3,3);
  
  upshift(4,5,300);
  pushbutton(4,6);
  
  pushButton(5,1);
  PEC11Brightness(5,2,false);
  pushButton(5,4);
  PEC11Bite(5,5,true);

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

### Analog switches

#### Switch numbers

Now that we've set up our buttons and encoders, we're got some analog switches left. Namely two clutches and three 12-position rotary switches. Each will need an analog channel. Analog channels corresponds to the ADC pins on a CB1 board. So ADC1 is analog channel 1. We're wired them like this:

* \#1: Left clutch paddle
* \#2: Right clutch paddle
* \#10: Left 12-position switch
* \#9: Center 12-position switch
* \#5: Right 12-position switch

Channels used in the software for a bunch of internal stuff; like calculations, timings, switch modes, button numbers, etc. But they can also be used by you to refer to a switch. Such as the **launchButton()** function in this project need to know which analog channel it should affect. It currencly affects switch analog channel 1 to get in touch with the left clutch paddle.&#x20;

#### Button numbers

There are no default button numbering for analog switches. In our project it is the three 12-position switces that will need button numbers. All three of them have two switch modes; a 12-position mode and a incremental mode where it will just produce a pulse on rotation CW / CCW. The 12-positions will all need a button number, and the incremental mode needs two button numbers. So each of these three switches need 14 button numbers assigned. You can overlap the 12-position numbering and the incremental numbering (to use 12 numbers instead of 14), but I'll keep them seperated for this example.&#x20;

Our digital switches stopped at button 23, so we'll continue at button 24 (naturally, you could make your analog switches come first, starting at 0, and place the digital switches after, if you want to).&#x20;

I'd like it to be like this:

<figure><img src="../../.gitbook/assets/image (49).png" alt=""><figcaption></figcaption></figure>

At the bottom of 9\_CB1\_Table.ino you'll find the spot to put in the button numbers. We only need to add the _starting_ button number for each mode and swicth. These ones:

<figure><img src="../../.gitbook/assets/image (13) (1) (1).png" alt=""><figcaption></figcaption></figure>

Lets see how they fit in the code:

```
//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

#define analogSwitchCount 12

uint8_t analogPins[analogChannelCount] =              
{ ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7, ADC8, ADC9, ADC10, ADC11, ADC12 };

uint8_t analogButtonNumber[analogSwitchCount] =         //ANALOG BUTTONS 1
{ 0, 0, 0, 0, 54, 0, 0, 0, 42, 30, 0, 0 };

uint8_t analogButtonNumberIncMode[analogSwitchCount] =  //ANALOG BUTTONS 2
{ 0, 0, 0, 0, 28, 0, 0, 0, 26, 24, 0, 0 };

```

The two lists of numbers represent button numbers for up to 12 analog channels. We decided earlier that the left, center and right rotary switches are on channels 10, 9 and 5. The two clutches are on 1 and 2, but don't need any button number assigned. The unused channels can be left with 0.&#x20;

#### Switch functions

All analog switches need some sort of calibration. The whole deal with this switches is that they dont output 0 or 1, they have a range of values. So the firmware will need some reference points.

We need to know the value our clutches produce when in released and fully pressed positions, and we need to know the values we get from the rotary switches in every position.&#x20;

Read this [guide](../../1.-project-planning/analog-inputs/#reading-a-value) to read out the values.

Lets say we found the following:

* Left clutch: 8530 -> 21530
* Right clutch: 8510 -> 20950
* Rotary switches: 150, 2450, 4930, 7480, 10510, 13250, 16830, 20310, 22930, 25790, 28840, 31200.

The values don't have to be super accurate, and might also be difficult to get completely accurate because the readout is not 100% stable. For the clutches, adjsut the values so that the clutches are 100% stable at both 0% when not pressed and 100% when pressed.

Now we have what we need to finalize our `30_Switches` tab:

```
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------
  
  modButton(1,1);
  biteButton(1,2);
  neutralButton(1,3);
  launchButton(1,4,1);
  presetButton(1,5);
  
  pushButton(1,6);
  pushButton(1,7);
  pushButton(1,8);
  
  funkyRotary(2,1,2,false);
  funkyButton(2,3,7,4,5,6);
  funkyButton(2,4,7,3,5,6);
  funkyButton(2,5,7,3,4,6);
  funkyButton(2,6,7,3,4,5);
  funkyPush(2,7,3,4,5,6);
  
  toggleP(3,3);
  
  upshift(4,5,300);
  pushbutton(4,6);
  
  pushButton(5,1);
  PEC11Brightness(5,2,false);
  pushButton(5,4);
  PEC11Bite(5,5,true);
  
  dualClutch(1, 8530, 21530, 2, 8510, 20950, false);
  
  SW1PresetRotary(10, 1,  150, 2450, 4930, 7480, 10510, 13250, 16830, 20310, 22930, 25790, 28840, 31200, false);
  rotaryAnalog2Mode(9, 2,  150, 2450, 4930, 7480, 10510, 13250, 16830, 20310, 22930, 25790, 28840, 31200, false);
  rotaryAnalog2Mode(5, 3,  150, 2450, 4930, 7480, 10510, 13250, 16830, 20310, 22930, 25790, 28840, 31200, false);
  
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

Note that the three rotary switches are set up with [field placement ](../../3.-coding/advanced/field-placement.md)1, 2 and 3, which will give you some SimHub properties (DDC.R1, DDC.R2, DDC.R3) to tell which mode the switches are in.&#x20;

### Edit button count

Our controller is now using button number 0-65 for a total of 66 buttons. Default setting is 64 buttons, so we'll have to adjust. You can adjust this also if using less than the default 64 buttons, to make it match the actual button count. See [here ](../../3.-coding/essentials/08_joystick.md)how to do it.&#x20;

### Edit the board name

If you want a specific name for your controller you can adjust this in `4_USB.ino`

```
#define VID_PI 0x2E8A
#define PID_PI 0x1053
#define MAKER "Andreas Dahl"
#define CONTROLLER_NAME "Dahl Design Controller"
```

If you have your own PID/VID you can also edit that here.&#x20;

### LED

Our project also has a 72 LED strip. They numbered 0 to 71 in DDC and are distributed as follows:

* 0 - 3 : Button backlight (for launch button, should be green)
* 4 - 7: Button backlight (for bite button, should be orange)
* 8 - 11: Button backlight (for mod button, should be blue)
* 12 - 15: Button backlight (for neutral button, should be red)
* 16 - 27: Left rotary switch position markers (green position, white background)
* 28 - 39: Center rotary switch position markers (purple position, white background)
* 40 - 51: Right rotary switch position markers (blue position, white background)
* 52 - 55: Left side warning lights
* 56 - 67: Rev lights
* 68 - 71: Right side warning lights

I suggest reading through the chapter on [LED control](../../3.-coding/peripherals/leds-code-and-connection/) before you go on.

The idea now is that SimHub will control LEDs 52 to 71, and we'll be adding the backlighting and rotary switch positions marking in the `36_LEDTop.ino` tab.&#x20;

First though, we'll need to set it up in `14_LEDSetup.ino`. As printed on the CB1 board, the LED pin is pin 25 in the code:

```
//----------------------------------------------------------------------------
//-----------------------------LED COLOR AND TYPES----------------------------
//----------------------------------------------------------------------------
//   NEO_KHZ800  800 KHz bitstream (WS2812 LEDs and similar)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ---------------------------- STRIP #1 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED1COUNT 80
#define LED1PIN 25 
#define LED1TYPE NEO_GRB + NEO_KHZ800
#define LED1REVERSE 0
#define LED1PRIVATE 0
```

Next, we'll use [colorLED()](../../3.-coding/peripherals/leds-code-and-connection/firmware-control/led-functions.md#colorled) for backlighting and [rotaryLED() ](../../3.-coding/peripherals/leds-code-and-connection/firmware-control/led-functions.md#rotaryled)for switch positions. We're also gonna use [biteLED()](../../3.-coding/peripherals/leds-code-and-connection/firmware-control/led-functions.md#biteled) to use the rev lights to display the bite point when setting it with PEC11Bite. Since the controller has 12 rev lights, we're gonna use the first 10 (56 to 67) for biteLED(). The biteLED() function also allows some other LEDs to indicate bite setting is active. We're gonna use the 4 LEDs that is backlighting the bite button for that (4 to 7).&#x20;

#### Relative brightness

DDC has a global brightness setting which can be adjusted. But the various LEDs can be set to different levels relative to eachother as well, this is done in the LED functions for each.&#x20;

We're gonna have to set the relative backlight brightness for buttons to 100%, since the button caps are quite opaque and these will be the reference for the brightnest LEDs.  For the rotary switches, there is just a thin diffuser film used, so setting brightness to 35% for the indicator light and 20% for the background. The rev lights are have almost no diffusion, just masked with tinted acrylic, so setting brightness to 15% for those.&#x20;

The global brightness setting by default is 25%, this is what we'll adjust with PEC11Brightness().&#x20;

#### LED functions

This is how `36_LEDTop.ino` ends up:

```
void LEDTop()
{
  
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
  */

   //LED CALLS STARTS HERE

  colorLED(0, 3, 0x00FF00, 100);
  colorLED(4, 7, 0xFFA500, 100);
  colorLED(8, 11, 0x0000FF, 100);
  colorLED(12, 15, 0xFF0000, 100);
  
  rotaryLED(3, 16, 12, 0x0000FF, 35, 0, false, 0xFFFFFF, 20);
  rotaryLED(4, 28, 12, 0xA020F0, 35, 0, false, 0xFFFFFF, 20);
  rotaryLED(5, 40, 12, 0xFFA500, 35, 0, false, 0xFFFFFF, 20);
  
  biteLED(4, 7, 100, 56, 15);
  
  //LED CALLS STOP HERE

  #if(LED1COUNT > 0)
    LED1.show();
  #endif
  #if(LED2COUNT > 0)
    LED2.show();
  #endif
  #if(LED3COUNT > 0)
    LED3.show();
  #endif
  #if(LED4COUNT > 0)
    LED4.show();
  #endif

}
```

### Connect to SimHub

We're going to have SimHub control the warning lights (52 - 55 + 68 - 71) and rev lights (56 - 67). Follow [this guide](../../4.-advanced-features/simhub-control.md) to get SimHub hooked into your LEDs.&#x20;

If you want properties from your wheel to use for dashboard graphics, follow[ these instructions.](../../4.-advanced-features/connect-to-simhub/)

