# Setup

### Direct wiring

When using the microcontrollers pins directly (as in the figure above), you'll use 10\_TableAndAnalog.ino.&#x20;

```
//---------------------------------------
//------------DIRECT OUTPUT--------------
//---------------------------------------

#define enableOutput 0
uint8_t outputPins[] = { 99};
const uint8_t outputPinsCount = sizeof(outputPins) / sizeof(outputPins[0]);
```

Set `enableOutput` to **1** to create an output hub.&#x20;

List the pins numbers used in `outputPins[]` below. The first you type in will get slot 1 in the hub, the second gets slot 2, and so on.&#x20;

As mentioned above, this hub is numbered last of all your hubs. So if you only have this hub, it is #1. If you have 3 port expanders set up as output hubs, this is hub #4.&#x20;

To set up the arduino as in the figure above:

```
//---------------------------------------
//------------DIRECT OUTPUT--------------
//---------------------------------------

#define enableOutput 1
uint8_t outputPins[] = { A2, A1, A0, 15, 14, 16};
const uint8_t outputPinsCount = sizeof(outputPins) / sizeof(outputPins[0]);
```

Lets say you've hooked these output pins to LEDs. In the firmware you'll now refer to the 6 LEDs as _**Slot 1 to 6 on Hub #1**_ instead of having to keep track of the arduino pin numbers.&#x20;

### PCA9555

Setting up a PCA9555 as 16 output pins and building an output hub for it is done in 2\_Board.ino.  Set up your [I2C channels](../i2c-devices/), then scroll down to this secton:

```
//PORT EXPANDER PCA9555
#define USING_PCA9555 0
#define PCA9555_I2C_NUMBER 0
uint8_t PCA9555interruptPins [] = {99};
#define PCA9555_OUTPUT 0

#if (PCA9555_OUTPUT== 1)
uint8_t PCA9555outputAddress [] = {0x20};
```

<mark style="background-color:purple;">USING\_PCA0555</mark> is to disable/enable support for this IC. Set it to 1 to enable.&#x20;

<mark style="background-color:purple;">PCA9555\_I2C\_NUMBER</mark> lets to chose between I2C channel 0 or 1 on a RP2040 board. If you're not using a RP2040 board, just leave this at 0.

<mark style="background-color:green;">PCA9555interruptPins</mark> is an array where you put in the pin numbers for the pins used for [interrupt.](../../../2.-wiring/switch-inputs/port-expander.md#input-pins) You only need to list interrupt pins for port expanders used for _inputs._ When setting up as output device, no interrupt pin is needed.&#x20;

<mark style="background-color:blue;">PCA9995\_OUTPUT</mark> is to set up the port expander as an output device. Set it to 1.&#x20;

<mark style="background-color:blue;">PCA9995outputAddress</mark>  needs to know the I2C address of the port expanders you're setting up as output devices and builds output hubs for them. The order in which you list them here will also assign the hub numbers. The first on in the list is your output hub #1.&#x20;

Lets say we're using I2C channel 0 and have 3 x PCA9555 set up:

```
//PORT EXPANDER PCA9555
#define USING_PCA9555 1
#define PCA9555_I2C_NUMBER 0
uint8_t PCA9555interruptPins [] = {99};
#define PCA9555_OUTPUT 1

#if (PCA9555_OUTPUT== 1)
uint8_t PCA9555outputAddress [] = {0x20, 0x21, 0x22};
```

The firmware has now build 3 output hubs, corresponding to the 3 port expanders, with 16 slots each corresponding to the 16 pins on each port expander. If we want to do something with pin 10 on the port expander with address 0x21, well refer to it as _**hub 2, slot 10**_. &#x20;
