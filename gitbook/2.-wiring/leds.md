# LEDs

The LEDs supported are the ones supported by the [FastLED](https://github.com/FastLED/FastLED) library. Most commonly used are WS2812, also knows as Neopixel.&#x20;

Common for adressable RGB LEDs is that you daisy-chain them. Each LED needs power, ground and a signal in. If the chain is going to continue, you pass the signal on from this LED to the next.

<figure><img src="../.gitbook/assets/image (8).png" alt=""><figcaption></figcaption></figure>

It is common to add a 100 nF capacitor between VCC and GND next to each LED, but it is not needed for all types of LEDs. Some of them have them built-in. It is also common to add a small resistor on the data line.&#x20;

The last LED in the chain does not need its OUT pin wired to anything.

Some will use LED strips that are already wired together. These can usually be chained together as well, just wired the whole strip as you would a single LED.&#x20;
