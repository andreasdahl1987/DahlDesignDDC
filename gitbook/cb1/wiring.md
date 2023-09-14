# Wiring

### Digital

CB1's 64 digital input pins are organized in a switch table, 8 rows and 8 columns. On the board itself you'll see each row with its 8 column pins clustered.&#x20;

By default it is organized like this:&#x20;

<figure><img src="../.gitbook/assets/image (68).png" alt=""><figcaption></figcaption></figure>

The numbers in the boxes are the corresponding button numbers. A button wired to R3C5 will have button number 20 (or 21 in Windows, since DDC starts with 0 and windows starts with 1). You can edit these button numbers, take a look at [advanced](code/settings.md) settings.

When wiring switches to these rows, you do it the same way as with [direct wiring](../2.-wiring/switch-inputs/non-matrix-wiring.md) and [shift register](../2.-wiring/switch-inputs/shift-registers.md#input-pins) wiring; for simple buttons you'll have one pin to ground and the other to a input pin. With multi-pin switches such as encoders or funky-switches, the common pins goes to ground and the rest goes to input pins.&#x20;

The [general rules of the switch table](../1.-project-planning/switch-inputs/matrix.md) has to be followed.&#x20;

### Analog

Analog switches use typical [analog wiring](../2.-wiring/analog/analog-wiring.md) with power, ground and a signal pin. Signal pin goes to any of the 12 analog inputs (labeled ADC1 - ADC12). You can use 3.3V or VAN (**V**cc **AN**alog) to power the analog switches. I recommend VAN, which is designed for analog switches. More about the [VAN pin here.](circuit.md#van-vcc-analog-and-voltage-drop)

### Example

This is an example setup that will be referred to for the remainder of the CB1 manual. This is an example of how things can be done, not how it _has to be done._

This is a fairly feature-rich controller, featuring:

* 8 x pushbuttons wired to Row 1, Columns 1-8
* 1 x funky switch wired to Row 2, Coumn 1-7
* 1 x toggle switch wired to Row 3, Column 3
* 2 x shifters wired to Row 4, Column 5-6
* 2 x PEC11 encoder with pushbuttons wired to Row 5, Column 1-6
* 2 x hall sensor clutches wired to ADC1 an ADC2
* 3 x analog rotary switches wired to ADC5, ADC 9 and ADC10
* A LED strip with 72 WS2812 LEDs&#x20;
* A VoCore screen
* A 6V power supply delivering up to 3A

<figure><img src="../.gitbook/assets/image (76).png" alt=""><figcaption></figcaption></figure>

Note the following:

* USB and LEDs are connected using the XH connectors on the board, so no soldering here.
* Power supply soldered in place and <mark style="background-color:red;">J1 pins are not connected</mark>, which will turn off USB power. The power supply is optional, but in this example - using a VoCore screen and 72 LEDs, we're gonna need more than the 0.5A from USB if we want to crank up the LEDs a little.&#x20;
* All analog switches are using VAN for power.
