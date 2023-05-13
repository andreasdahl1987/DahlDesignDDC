# Firmware control

DDC offers unlimited customization of LEDs. All 24-bit colors, setting different brightness for each and every LED if you want to.&#x20;

LED commands are written in 3 different tabs:

* 34\_LEDStartup
* 35\_LEDBottom
* 36\_LEDTop

Allowing you to setup LED calls on start up, LED calls that are below (overwritten by) SimHub, and LED calls above SimHub (overwrites SimHub).&#x20;

This is how they relate to eachother and SimHub:

<figure><img src="../../../../.gitbook/assets/image (8) (3).png" alt=""><figcaption></figcaption></figure>

To explain the flowchart above:

* LEDStartup will send all its commands to your LEDs only once - on powering the controller. Never again.
* LEDBottom and LEDTop will refresh constantly, together with input from SimHub (if connected):
  * LEDBottom calls are made first, but no undate of LEDs
  * If SimHub is connected, it will then clear all LEDs it has access to (can be controlled by setting strips to [PRIVATE](../#14\_ledsetup.ino)) It will update LEDs with whetever SImHub has been set up with, but still nothing is actually sent to the LEDs.
  * LEDTop will overwrite any changes made, including what SimHub did, but only affeecting the LEDs you're making calls to.&#x20;
  * In the end the data is sent to the LEDs.&#x20;
* SimHub doesnt sent LED data at the same frequency as your LED data is updated in the frmware. SimHub only sends LED data when there are changes. This means that most loops of LED refreshing will be without the SimHub data. That makes the LEDBottom bleed through. To fix this, DDC sets LEDBottom on a cooldown whenever new data from SimHub arrives. By default this is set to 1000 ms (1 second). The setting is called `DROPOUTTIMER.`It can be adjusted under 12\_GlobalVariables:

<figure><img src="../../../../.gitbook/assets/image (14) (1).png" alt=""><figcaption></figcaption></figure>

### 34\_LEDStartup.ino

```
void LEDStartup()
{

  /*
  *Here goes all LED calls that you only want to run on startup, or calls that only needs to be run on startup. 
  *Best suited for completely static lighting, such as backlighting. 
  *When connecting to SimHub, these LEDs will all be wiped black.
  *Any LED control that is done here instead of in LEDTop or LEDBottom will save a lot of processing power.
  */

   //LED CALLS STARTS HERE

  colorLED(0,5,0xFF08F0, 40);
  colorLED(6,11,0x0000FF,45);
  colorLED(12,17,0x08FF00,37);
  

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

It is clearly shown where the LED calls should be written. The ones written here are covered under [LED functions.](led-functions.md) LEDStartup is great for starting backlights on a controller before/without using SimHub. Keep in mind that since this is only run once, no blinking or conditional coloring is possible.&#x20;

### 35\_LEDBottom.ino

```
void LEDBottom()
{

    /*
   * These LED calls will overwrite LEDStartup, but in turn will be overwritten by SimHub LED control and again by LEDTop.
   * Whenever SimHub sends LED commands, the whole LED strip will be wiped black, not only the LEDs used by SimHub. 
   * When SimHub hasnt send LED commands for 1 second, LEDBottom will start working again
   */

//----------------------------------------------------------------------------
// ------------------------------- STRIP #1-----------------------------------
//----------------------------------------------------------------------------

  #if(LED1COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED1PRIVATE == 1)
    {
    //LED CALLS STARTS HERE

    triggerLED(0,4,true,0x00FF00,60,true,true,200,500);
    triggerLED(5,5,buttonPressed(3,4),0xFF00FF,40);


    //LED CALLS STOP HERE
    }
  #endif

//----------------------------------------------------------------------------
// ------------------------------- STRIP #2-----------------------------------
//----------------------------------------------------------------------------

  #if(LED2COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED2PRIVATE == 1)
    {
    //LED CALLS STARTS HERE

    colorLED2(0,5,0xFF08F0, 40);
    colorLED2(6,11,0x0000FF,45);
    colorLED2(12,17,0x08FF00,37);


    //LED CALLS STOP HERE
    }
  #endif

//----------------------------------------------------------------------------
// ------------------------------- STRIP #3-----------------------------------
//----------------------------------------------------------------------------

  #if(LED3COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED3PRIVATE == 1)
    {
    //LED CALLS STARTS HERE





    //LED CALLS STOP HERE
    }
  #endif

//----------------------------------------------------------------------------
// ------------------------------- STRIP #4-----------------------------------
//----------------------------------------------------------------------------

  #if(LED4COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED4PRIVATE == 1)
    {
    //LED CALLS STARTS HERE





    //LED CALLS STOP HERE
    }
  #endif
}
```

LED\_Bottom() has a slot or every LED strip. This is related to the cooldown SimHub puts this function on, and allowing private LED strips to negate the cooldown. The LED functions written here are covered under [LED functions.](led-functions.md) One of the functions also uses a [trigger.](../../../advanced/conditional-coding/triggers.md)

Out of the three, this is probably the least useful - but it's nice to have options!

### 36\_LEDTop.ino

```
void LEDTop()
{
  
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
  */

   //LED CALLS STARTS HERE

  rotaryLED(1,0,12,0xFF00F0,50,0,false);
  rotaryLED(2,12,12,0x00FF00,50,0,false);
  rotaryLED(3,24,12,0x0000FF,50,0,false);
  rotaryLED(4,36,12,0x00F0FF,50,0,false);
  rotaryLED(5,48,12,0x80F008,50,0,false);


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

LEDTop() is likely the most useful out of the three functions. It starts as soon as the controller is poewred up, and it will overwrite SimHub - only on the LEDs that you write functions to. Functions like triggerLED() will allow you to keep your LED call silent untill you need it, and then it will not be silenced by SimHub. The LED functions written here are covered under [LED functions.](led-functions.md)
