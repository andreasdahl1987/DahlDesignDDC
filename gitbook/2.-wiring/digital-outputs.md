# Digital outputs

Wiring digital outputs is fairly straight forward. One pin for each device, a resistor to limit the current. You can use both the microcontrollers digital pins and/or a port expander (PCA9555).&#x20;

* Microcontroller output pins can supply a maximum of 50 mA
*   PCA9555 can supply a maximum of 25 mA per pin

    * However, the first 8 and last 8 pins on the expander are seperated in terms of power draw, and you can only supply a maximum of 100 mA across the 8 pins in pair. Meaning maximum 12.5 mA for each pin if all 8 are used.
    * The total current supply of the whole expander is not 100 mA + 100 mA, but 160 mA. So if all 16 pins are used, 10 mA is the maximum current per pin.



Select the correct resistor size to match the current you want. Higher current means brighter light for LEDs. The max current rating might be too bright, so do some tests to see what feels right.&#x20;

The size of the resistor has to be calculated. The equation is like this:

$$
r = {VCC - V^f \over I}
$$

* _**r**_ is the size of the resistor you need
* _**VCC**_ is the operating voltage of the microcontroller board (typically 5V or 3.3V)
* _**Vf**_ is the forward voltage of the LED, or the "voltage drop". Typically 1.8V for a red LED, increasing through the rainbow colors with purple at 3.0V.&#x20;
* _**I**_ is the desired current through the LED. Typically 20 mA is maximum and quite bright. 5-10 mA gives a comfortable brightness.&#x20;

You can also use an [online calculator](https://ledcalculator.net/) to find the resistor size.

### Microcontroller wiring

<figure><img src="../.gitbook/assets/image (4) (1) (1) (1).png" alt="" width="347"><figcaption></figcaption></figure>

Here we're wiring 5 red LEDs directly to our microcontroller.&#x20;

If we use a Pro Micro board that runs at 5V, and want to drive an LED with 2.2 V forward voltage with 8 mA current, the equation looks like this:

$$
{5V - 2.2V \over 0.008A} =  350 Ω
$$

The closest available resistor value would be 360 Ω.&#x20;

DDC allows you to use up to **16 microcontroller pins** as output pins, more on this under the [coding section.](../3.-coding/peripherals/digital-outputs/)

### Port expander wiring

<figure><img src="../.gitbook/assets/image (9) (1).png" alt=""><figcaption></figcaption></figure>

Here we have 16 LEDs wired to our PCA9555 port expander. They're wired exactly like the example above with the microcontroller. Resistor size is calculated the same way.&#x20;

The other parts of this circuit is explained under [PCA9555's own documentation](switch-inputs/port-expander.md), the only difference is the interupt pin **INT#** is not used, since it is only needed when using the port expander for inputs. **It is pulled up to VCC with a 10k resistor.**&#x20;

Keep in mind the [maximum pin current](../1.-project-planning/digital-outputs.md) from a port expander.
