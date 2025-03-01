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

If you're using a Atmel 32U4 processor board, you can activate [EEPROM](../../1.-project-planning/eeprom.md) by editing `USING_32U4EEPROM` from `0` to `1.` This is all you need to activate EEPROM for this board. This will take some additional storage memory and dynamic memory. So if you've activated EEPROM and is stuck using too much memory, this is a feature you could consider turning off.&#x20;

If you're rocking an RP2040 processor board, you can activate [EEPROM](../../1.-project-planning/eeprom.md) by editing `USING_RP2040EEPROM` from `0` to `1.` This will reserve a tiny fraction of the board's storage memory for EEPROM purposes.&#x20;

For other boards; coding a peripheral EEPROM device is [done like this.](../peripherals/i2c-devices/cat24c512.md)&#x20;

#### Performance

`#define ECOLED` will let you set the LED system to a memory economic mode, using far less dynamic memory. This can be key for the 32U4 MCU. Setting this to 1 will enable eco-mode. The drawback is that LEDBottom() will no longer be active.&#x20;

#### **Activate oversampling**

For RP2040 boards, DDC can oversample the analog input readings.&#x20;

Oversampling is a common way to use processing power to improve the resolution of analog signal measurements. DDC will use the RP2040's DMA (kind of a processor that works in parallell with the two processor cores) to store samples from the ADC, and the 2nd processor core to go through all the samples and average them. The result is that your analog readings are an average of 256 samples instead of just the most recent measurement. Since the RP2040 makes 500 000 measurements per second, using these averages wont cause any lags.&#x20;

Rule of thumb when using oversampling to improve resolution is that every 2 bits of oversampling transfers to 1 bit of resolution gain. 256 samples means 8 bits oversamping, taking the RP2040s ADCs from 12-bit to 16-bit resoution, which is a massive gain.&#x20;

The output values will go from 0-4096 to 0-65536. However, DDC will cut this value it half for memory reasons, meaning values of 0-32768. Since the signal noise of these ADCs is much higher than a value of 2 on the output, cutting the value in half doesnt take away any resolution.&#x20;

I suggest activating oversampling for any RP2040 board, it is done by setting `ENABLE_OVERSAMPLING` from `0` to `1.`

**Important to note,** when you activate oversampling, you cant refer to your analog pins as A0 to A3 anymore. You'll also have to build at least 4 analog channels to store data from these four pins. More on this in the chapter on [10\_TableAndAnalog.ino](10_matrixandanalog.ino/)
