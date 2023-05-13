# External ADC

If you're running out of analog inputs, or just want more accurate analog readouts, you can add external ADCs.&#x20;

<figure><img src="../../.gitbook/assets/image (84).png" alt=""><figcaption></figcaption></figure>

An ADC (analog to digital converter) measures voltage and turns it into a value. It is required to make sense if data from sensors and potentiometers, and is used widely in consumer electronics for microphones, cameras, meassuring tools, etc. Anything that takes something _physical,_ like a distance/temperature/weight/brightness_,_ and turns it into a value for the computer to use, needs an ADC. Needless to say, any microcontroller should have an ADC - and they have. The analog inputs on a Pro Micro or Pico board sends the signal to the ADC. Typically, the ADCs that are built into the microcontroller chips are noisy and inaccurate. However, fairly quick and usually more and good enough for controller purposes.&#x20;

Think about it; how tall are you? You could say you're 181.5 cm tall, but that is not accurate. With a better measuring tool you could find out that you're 1.8178 meters tall. With an even better tool you get 1.81776342235 meters. However, you'll never get 100% accuracy, you can never get an _exact_ measurement. This is the trade-off with ADCs. The accuracy is measured in bits. A 10-bit ADS can describe the range of 0 - 5 volts in 1023 steps. A 16-bit ADC has 65 536 steps, which will make it more accurate. However, it will also be more expensive and slower. So what do you need? Accuracy? Speed? Cheap? High-end?&#x20;

## Supported ADCs

### ADS1115

* 16-bit
* 4 inputs
* I2C
* Fairly slow, but fast enough for joystick controller purposes.

This is a popular chip, and its selling point is its accuracy - with 16-bit resolution and a stable onboard referance voltage. Fairly quick for being 16-bit, but mega slow compared to 10-12-bit ADCs. High in stock on JLCPCB and relatively inexpensive. It has 4 channels and connects via I2C, so it will need 2 pins from the microcontroller. More on this under [wiring.](../../2.-wiring/analog/external-adc.md) You can add up to 4 of these for 16 additional analog inputs.

A big effort has gone into optimizing the readouts from this ADC. The existing, popular libraries for this IC are extremely slow and memory heavy - making them not suited for DDC. Instead I've made my own algorithms, which are a lot more efficient in both processing and memory usage.&#x20;





