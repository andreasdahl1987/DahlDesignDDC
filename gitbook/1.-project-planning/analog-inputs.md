# Analog inputs

DDC supports up to 10 analog switches (clutches, multiposition switches). It has been set to 10 since that would cover it for most people, but the number can be increased with some tinkering. When adding an analog switch to your project, it has to be assigned a number from 1-10. **This has nothing to do with button numbers.** This number is the key to a package of variables that the switch need to function properly. So each switch needs its own number, no sharing with other switches.

![image](https://user-images.githubusercontent.com/40788634/191258151-246e2b10-8bd2-43ac-b9f1-520d17a065c2.png)

The same way as with matrix buttons, I organise these in a spreadsheet. Here, switch #1 and #2 (the blue ones) are 12-position switches, and switch #3 and #4 are my left and right clutch paddles. Switch numbers 5 to 10 are not used.

Notice there are two rows here. These don't represent rows, but a pair of boxes for each switch# where you can type button numbers for the respective switches. The clutch paddles naturally dont need a button number, so they are left blank. For the multi-position switches, the same rule applies as with **encoders:**

* If your multiposition switch is used solely as an incremental switch, the starting button number goes in the top box. "0" in bottom box.
* If your multiposition switch is used solely as a multiposition switch, the starting button number goes in the top box. "0" in bottom box.
* If your multiposition switch uses a function with both multiposition mode and incremental mode, the starting button number for multiposition mode goes in the top box and starting button number for incremental mode goes in the bottom box.

This means that in the example above:

* Switch #1 will use button numbers 69-80 in 12-position mode and button numbers 81 and 82 in incremental mode.
* Switch #2 will use button numbers 83-94 in 12-position mode and button numbers 95 and 96 in incremental mode.

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
