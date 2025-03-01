# Firmware control

DDC offers a high degree customization of LEDs, working alone or in harmony with your SimHub LED profile. All 24-bit colors, setting different brightness for each and every LED if you want to. Use the [LED functions](led-functions.md) to control them.&#x20;



{% embed url="https://www.youtube.com/watch?feature=youtu.be&v=dfZJv4_aeNk" %}

There are 3 layers of firmware LED control (Startup, Bottom and Top) and 2 layers of SimHub LED control (Mask and SimHub). The SimHub layers will not be active until SimHub is open and you've made [contact with the controller.](../../../../4.-advanced-features/simhub-control.md)

_The LED system uses a fair bit of dynamic memory. In some cases too much for the 32U4-based boards to handle. You can save a lot of memory by setting `#define ECOLED` to 1 in `2_Boards.ino.` The downside being that LEDBottom() is deactivated._&#x20;



<figure><img src="../../../../.gitbook/assets/image (4).png" alt=""><figcaption></figcaption></figure>

The 5 layers will apply one after the other, the next overwriting the former.

* **LEDStartup** will send all its commands to your LEDs **only once** - on booting the controller. It will also send all commands only once after SimHub is closed.&#x20;
* **LEDBottom** update LEDs constantly, at roughly 60 Hz.
* **Mask** join the party when SimHub is connected, and will by default turn off all LEDs, leaving a blank canvas for the SimHub layer. You can however punch holes in the mask for the layers below to shine through.
* **SimHub** layer is built in the SimHub RGB editor and will along with the mask update at 60 Hz.&#x20;
* **LEDTop** update LEDs constantly, at roughly 60 Hz.

The purpose of LEDStartup over LEDBottom is that you'll be saving a lot of processing power if these LEDs don't need constant updating. A good example is a backlit button box with static colors.&#x20;

Using the figure above, we'll go through the tabs where you set up firmware LED control:

### 15\_LEDMask.ino

```
#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)

//------------------------------------------------------------------
//--------------LIST LEDS THAT SHINE THROUGH THE MASK---------------
//------------------------------------------------------------------


uint8_t LEDMask[] = {0, 3, 7};


//------------------------------------------------------------------
//--------------LIST LEDS THAT SHINE THROUGH THE MASK---------------
//------------------------------------------------------------------


uint8_t LEDMaskCount = sizeof(LEDMask);

#endif
```

This is where you make holes in the mask. Simply list the LED numbers that will shine through the mask. As in the figure above, there are holes in the mask for LEDs 0, 3 and 7.&#x20;

### 34\_LEDStartup.ino

```
void LEDStartup()
{
//----------------------------------------------------------------------------
// ------------------------ LED CALLS START HERE------------------------------
//----------------------------------------------------------------------------


  colorLED(3, 6, 0xFFFF00, 40);
  colorLED(7, 7, 0xADD8E6, 40);
  

//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------

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

[LED functions](led-functions.md) are used in tab 34-36 to manipulate the RGB LEDs. To follow the example at the top of the page we're turning LEDs 3-6 yellow (hex color FFFF00) and LED 7 light blue (hex color ADD8E6). Both are set to 40% relative brightness. Keep in mind that in LEDStartup, colorLED() is the only function that will work, since it is only run once and can't react to anything like triggerLED(), rotaryLED() and biteLED().&#x20;

### 35\_LEDBottom.ino

```
void LEDBottom()
{
  if(LEDCounter == 0)
  {
//----------------------------------------------------------------------------
// ------------------------ LED CALLS START HERE------------------------------
//----------------------------------------------------------------------------


triggerLED(2, 5, true, 0x00FF00, 40, true, true, 750, 250);


//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------
 }
}
```

As in the figure at the top, we're lighting up LEDs 2-5 green (hex color 00FF00). In this case, we're making the LEDs blink, so we're using [triggerLED() ](led-functions.md#triggerled)instead of colorLED().&#x20;

### 36\_LEDTop.ino

```
void LEDTop()
{
  if(LEDCounter == 0)
  {
    SimHubImport(); 
//----------------------------------------------------------------------------
// ------------------------ LED CALLS START HERE------------------------------
//----------------------------------------------------------------------------


colorLED(1, 2, 0xFF00FF, 40);


//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------
  }

  #if(LED1COUNT > 0 && !strip1Block)
    if(LEDCounter == 1)
    {
      LED1.show();
    }
  #endif
  #if(LED2COUNT > 0)
    if(LEDCounter == 2)
    {
      LED2.show();
    }
  #endif
  #if(LED3COUNT > 0)
    if(LEDCounter == 3)
    {
      LED3.show();
    }
  #endif
  #if(LED4COUNT > 0)
    if(LEDCounter == 4)
    {
      LED4.show();
    }
  #endif

}
```

As in the figure at the top, we're making LEDs 1-2 purple (hex color FF00FF).&#x20;
