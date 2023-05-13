# 02\_Board.ino

02\_Boards is a controlpanel for setting up type of microprocessor, external hardware, the CB1 board, and a few other things. For the essential setup, only to top part of this page is relevant:

```
/*
 * Chose your board. Default is to 32U4-based boards. 
 */

//------------------------------
//-----------BOARD MCU----------
//------------------------------

#define BOARDTYPE 0

// 0 -> Atmel 32U4 based boards. (Leonardo, Pro Micro, Feather, Teensy 2.0, etc) SAM3X based boards. (Due)

// 1 -> SAMD21 or SAMD51 based boards. (Arduino Zero and many more)

// 2 -> RP2040 based boards. (Dahl Design CB1, Raspberry Pi Pico, Pico W, Pro Micro RP2040, and many more)

//------------------------------
//-----------EEPROM-------------
//------------------------------

#define RESET_EEPROM 0
#define USING_32U4EEPROM 0
```

The only thing you _need_ to touch here is `#define BOARDTYPE 0`, which is where you select your microcontroller board. 0 is default, which is for Atmel 32U4 boards.&#x20;

Example:

`#define BOARDTYPE 2`

This will switch to set up DDC for a RP2040 board, such as Raspberry Pi Pico.

#### Activate EEPROM

If you're rocking a Atmel 32U4 processor board, you can activate [EEPROM](../../1.-project-planning/eeprom.md) by editing `USING_32U4EEPROM` from `0` to `1.` This is all you need to activate EEPROM for this board. This will take some additional storage memory and dynamic memory. So if you've activated EEPROM and is stuck using too much memory, this is a feature you could consider turning off.&#x20;

For other boards; coding a peripheral EEPROM device is [done like this.](../peripherals/i2c-devices/cat24c512.md)&#x20;
