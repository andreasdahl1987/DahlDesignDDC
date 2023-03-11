# Analog inputs

DDC supports an unlimited number of analog switches (clutches, potentiometer, multiposition switches). These switches work outside of the switch table.

When adding an analog switch to your project, it has to be assigned a number. Starting at 0, each new switch one number higher. 5 switches should be numbered 1 - 5. **This has nothing to do with button numbers.** This number is the key to a package of variables that the switch need to function properly. So each switch needs its own number, no sharing with other switches.

<figure><img src="../.gitbook/assets/image (16) (1).png" alt=""><figcaption></figcaption></figure>

The same way as with matrix buttons, I organise these in a spreadsheet. Here, switch #1 and #2 (the blue ones) are 12-position switches, and switch #3 and #4 are my left and right clutch paddles. Switch numbers 5 is also a 12-position switch, which I will use as an incremental encoder.

Notice there are two rows here. These don't represent rows, but a pair of boxes for each switch# where you can type button numbers for the respective switches. The clutch paddles naturally dont need a button number, so they are left blank. For the multi-position switches, the same rule applies as with **encoders:**

* If your multiposition switch is used solely as an incremental switch, the starting button number goes in the top box. "0" in bottom box.
* If your multiposition switch is used solely as a multiposition switch, the starting button number goes in the top box. "0" in bottom box.
* If your multiposition switch uses a function with both multiposition mode and incremental mode, the starting button number for multiposition mode goes in the top box and starting button number for incremental mode goes in the bottom box.

This means that in the example above:

* Switch #1 will use button numbers 69-80 in 12-position mode and button numbers 81 and 82 in incremental mode.
* Switch #2 will use button numbers 83-94 in 12-position mode and button numbers 95 and 96 in incremental mode.
* Switch #3 and #4 are clutches, dont need button numbers.
* Switch #5 is only used as an incremental encoder and has its button number written in the top box.

### Reading a value

A lot of the functions handeling analog switches need some reference values, these will have to be read from the switch before the firmware will work. I suggest reading the values when the swith is mounted to the controller in the correct position. A test setup on a breadboard will always give different values.

Use this code and read out the values from the serial monitor:

```
#define pinNumber A3 //Change the pin number here to the actual pin you're using.

void setup()
{
  Serial.begin(9600);
}

void loop() 
{
  int sensorValue = analogRead(pinNumber);
  Serial.println(sensorValue);
  delay(1);
}
```
