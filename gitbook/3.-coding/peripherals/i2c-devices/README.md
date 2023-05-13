# I2C devices

Your central hub for setting up your I2C devices is `2_Boards.ino`.

Before going into the particular devices, you have to be aware that I2C communication is done through predetermined pins. This is different from microcontroller to microcontoller. Find the pinout diagram for you board to find the pins. Examples:

* Pro Micro -> Digital pins 2 and 3
* Arduino Zero -> Digital pins 11 and 12
* Arduino Due -> Digital pins 20 and 21&#x20;

The RP2040 is quite flexible, and also has 2 I2C channels. Several different choises of pins for each channel, but default in DDC is set to:

* I2C0 -> Digital pins 0 and 1
* I2C1 -> Digital pins 2 and 3

You can edit these pins for RP2040 if you scroll down a bit in the `2_Board.ino` file:

```
//------------------------------
//---------I2C DEVICES----------
//------------------------------

#define SDA0PIN 0
#define SCL0PIN 1
#define SDA1PIN 2
#define SCL1PIN 3

```

Other than that, all setup options for I2C devices are also done in `2_Board.ino.`

