# 4. Coding

Now that the electronics are sorted, time to build the firmware. You might already have a project where the wiring is set and you're looking to change your firmware to DDC. Then this is where you start.

## Software requirements

* [Arduino IDE](https://www.arduino.cc/en/software)
* [MHeironimus's joystick library](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/v2.0.8)
  * The link above is for version 2.0.8, which is before a bug was introduced to the joystick axis values. At the time of writing this, the bug has not been fixed. Version 2.0.8 works.

## The sketch

Download the repository. You only need the folder called `DahlDesignDDC`. The firmware is organized in many .ino files. The way this works is that Arduino IDE will read these files as a single, big file, starting with the main file `DahlDesignDDC.ino`, and then reading the rest in alphabetical order. Hence the numbering of all the other .ino files.

To open the sketch, open the `DahlDesignDDC.ino` file, Arduino IDE will automatically include all the other files. All the files are now available as **tabs** in Arduino IDE. Only some of these tabs are relevant to building your controller firmware, in fact only 3 of them are needed to adjust, and a few more are optional. We'll go through it step by step, **first the three mandatory ones.**
