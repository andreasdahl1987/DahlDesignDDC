# Calibrate

In 47\_PWMStartup.ino you'll calibrate your PWM channels to make them behave just like you want them on startup:

```
//#if (PWMENABLED == 1)
void PWMSetup()
{

  /*
  *Here you'll typically use PWMSetup() for all channels that you want to change from default values.
  *Default values are:
  * - Volume set to 25%
  * - Full range PWM (0-255)
  * - Channel is set to OFF
  * This will be set on boot, and wont overwrite anything that happens while the firmware is running. 
  */

   //PWM setup CALLS STARTS HERE






  //PWM setup CALLS STOP HERE

}
#endif
```

The only function you'll use here is:

`void PWMSetup(PWMchannel, isOff, minValue, maxValue, volume)`

Here, we'll decide if the channel should be OFF on startup, its range and its startup volume.

### Signal range

PWM signal strength is given in the software by a value between 0 and 255. 0 being 0V and 255 being the microcontrollers logic voltage (5V for a 32U4, 3.3V for a RP2040). A PWM value of 1 might not be enough to turn on a LED. A PWM value of 50 might not be enough to turn on a DC motor. Also, you might not want your LED to turn completely off when you dim it all the way down. Or you dont want you DC motor to run at 100% ever. So DDC has the option to set the lowest and highest PWM signal for each channel.

To evaluate the optimal range you can use **`setPWM(channel, value)`** in 30\_Switches.ino to try different values. If you set up a channel with a way to adjust the volume (with an encoder or potentiometer), you can set the channel to the full range, adjust the volume and check the raw PWM values currently running with **`checkPWM(channel)`** in 30\_Switch.ino. The values will show up in the serial monitor.&#x20;

### Startup volume

By default, the volume of each PWM channel is set to 25%. When working with PWM in DDC you'll typically be changing the volume of the channel. The volume being a fraction of the signal range. So you'll only be working with raw PWM values (0-255) when setting the range. After that it is just volume, a value of 0-100. 0 being the minimum PWM value, 100 being the maximum PWM value.&#x20;

### Default off&#x20;

For safety reasons, the PWM channels are default OFF on startup. OFF meaning 0V (ground), even if you set your minimum PWM signal strength to 150, OFF means 0 V. When a channel is ON, the PWM signal strength is defined by the volume of the channel.&#x20;



Setting up our 3 channels:

```
#if (PWMENABLED == 1)
void PWMSetup()
{

  /*
  *Here you'll typically use PWMSetup() for all channels that you want to change from default values.
  *Default values are:
  * - Volume set to 25%
  * - Full range PWM (0-255)
  * - Channel is set to OFF
  * This will be set on boot, and wont overwrite anything that happens while the firmware is running. 
  */

   //PWM setup CALLS STARTS HERE


  PWMSetup(1,false,10,255,60);
  PWMSetup(2,true,40,220,10);
  PWMSetup(3,false,10,180,60);



  //PWM setup CALLS STOP HERE

}
#endif
```

* Channel 1 is for a group of LEDs, isOff is set to false, so it is ON on startup. Range is 10 to 255, using the maximum brightness and preventing the LED to turn off when dimming all the way down. Startup volume is set to 60%.
* Channel 2 is for a fan. isOff is set to true, so the fan doesnt start blowing on startup. Range starts at 40, since this fan wont work at a lower value, and maximum value is set to 220, since it starts making a lot more noise going faster than that. Volume of 10% makes for a comfortable fan speed then it is turned on.&#x20;
* Channel 3 is for another group of LEDs, but these have a much thinner diffuser than the LEDs on channel 1, so the maximum value is set to 180 to have them match the brightness of the other LEDs.&#x20;
