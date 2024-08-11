# Rotary switches

Rotary switches refers to switches with several, isolated switch positions, each with its own pin. The switch has one path in and several paths out, the position of the rotary knob will determine which way the signal goes.&#x20;

<figure><img src="../../.gitbook/assets/image (3) (3).png" alt=""><figcaption></figcaption></figure>

The major strength of these switches is that the physical position of the switch rotation will match the button number. So you can label a switch with ABS 1-12, map it the same way in-game, and the ABS will be 3 when the switch points to 3. Also, they usually have great feel, with solid clicks.&#x20;

The weakness of these switches are the size and the number of pins, but there are solutions to this:

* The size can be worked around by spending more money - Grayhill 56 series is a good example.&#x20;
* The pin numbers can be reduced from 8/10/12/16 to **1** with voltage divider circuit, often referred to as a _"resistor ladder"_. This circuit can be layed out on a PCB which fits the switch pins, and doesn't add anything to the size of the switch.

<figure><img src="../../.gitbook/assets/image (6) (1) (2).png" alt=""><figcaption><p>The Dahl Design SW1 with its two rotary switches. These utilizes a PCB with a resistor ladder circuit.</p></figcaption></figure>

A voltage divider circuit in its simples form below:

<figure><img src="../../.gitbook/assets/image (1) (1) (3).png" alt=""><figcaption></figcaption></figure>

Typically, "Vin" will be your +5V or +3.3V from the microcontroller. The ground symbol to "GND" on the microcontroller. "Vout" is the voltage level that you'll measure. The idea here is to divide a portion of the voltage to ground and a portion to be measured. The voltage at "Vout" depends on the size ratio of the two resistors Z1 and Z2. If Z2 is really big and Z1 small, a higher voltage is meassured at "Vout". If Z1 is big and Z2 small, a lower voltage is measured at "Vout".&#x20;

The equation is like this:&#x20;

<figure><img src="../../.gitbook/assets/image (5) (1) (2) (1).png" alt=""><figcaption></figcaption></figure>

Here is the same voltage divider circuit, now with the rotary switch weaved into it. All the resistors (R) have the same value. At this position, Z1 is 5R and Z2 is 6R. Changing the position of the switch will change the size of Z1 and Z2, and ultimately change the value of "Vout".&#x20;

<figure><img src="../../.gitbook/assets/image (9) (1) (1) (1) (1).png" alt=""><figcaption><p>The resistor ladder</p></figcaption></figure>

All that is left is to [read](../../1.-project-planning/analog-inputs/#reading-a-value) "Vout" with an analog pin in each position of the switch. These values will go into the rotary switch functions. You'll notice the readout isn't 100% stable, it will fluctuate a little bit. It doesn't matter, the functions just need an approximate value. &#x20;
