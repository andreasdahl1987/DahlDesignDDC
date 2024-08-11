# RGB LED

The LEDs supported are the ones supported by the [Adafruit Neopixel library. ](https://github.com/adafruit/Adafruit\_NeoPixel) Most commonly used are WS2812, also knows as Neopixel.&#x20;

Common for adressable RGB LEDs is that you daisy-chain them. Each LED needs power, ground and a signal in. If the chain is going to continue, you pass the signal on from this LED to the next.

<figure><img src="../.gitbook/assets/image (8) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

It is common to add a 100 nF capacitor between VCC and GND next to each LED, but it is not needed for all types of LEDs. Some of them have them built-in, **check the datasheet for the LEDs you're using.** It is also common to add a small resistor on the data line.&#x20;

The last LED in the chain does not need its OUT pin wired to anything.

Some will use LED strips that are already wired together. These can usually be chained together as well, just wired the whole strip as you would a single LED.&#x20;

## 3.3V Boards

Boards with 3.3V logic (such as RP2040-based boards) are generally outside the voltage demands of addressable RGB LEDs. There are a few solutions:

#### Fark it, I'll go 3.3V anyways

This will probably work with a small amount of LEDs on a board with little voltage drop (few things going on) and brightness not set very high. Power the LEDs with 3.3V and use a data pin directly from the controller to controll the LEDs.

**Cheap pullup-resistor trick**

* Power the LEDs with 5V from USB, use a pullup resistor on the LED data pin from microcontroller to pull the signal up to 5V. Though RP2040 is not rated for 5V on its GPIO pins, this has been tested with good results over time. I still wouldn't recommend this for a final design, it works well for testing/prototyping.&#x20;

<figure><img src="../.gitbook/assets/image (17) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

#### Level shifter

* The proper way to do it is using a level shifter. An inexpensive IC that changes to voltage of the data line to whatever to put into it.&#x20;

<figure><img src="../.gitbook/assets/image (31) (1).png" alt=""><figcaption></figcaption></figure>

The circuit above will take the 3.3V data line and increase the voltage to 5V. "LED5" is the lead that will connect to the first LED in the chain. The resistor R13 is the recommended resistor on the data line before the first LED in the chain. Here at 33 ohm. Recommended for WS2812 is 330-500 ohm, but less will work well.&#x20;
