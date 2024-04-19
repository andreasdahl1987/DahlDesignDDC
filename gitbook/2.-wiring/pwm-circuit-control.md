# PWM / Circuit control

Typicaly, the maximum current from a microcontroller pin as around 50 mA. This is not enough to power motors and fans, not even more than a few LEDs. So we can't really power anything meaningful directly from our PWM pin. Instead we'll use the PWM pin to control a gate, which in turn will control a different circuit that can do some more heavy lifting.&#x20;

Think of it as PWM controlling the tap; pushing water through the pipes is hard work, often done by a water pump. Controlling the tap is much lighter, but the effect is essentially the same as turning the pump on and off.&#x20;

<figure><img src="../.gitbook/assets/image (14).png" alt="" width="319"><figcaption></figcaption></figure>

### Wiring

Lets start with a simple analog circuit using a 9V battery, an LED and a resistor.

<figure><img src="../.gitbook/assets/image (15).png" alt="" width="227"><figcaption></figcaption></figure>

The resistor is there to limit the current through the LED. Without the the current would be too big and the LED will burn out. A bigger resistor will make the LED less bright, and an even bigger resistor will prevent the LED from lighting up at all. Typically you'll find the resistor that lights up the LED as bright as you need it to be; trial and error. Now, lets add the PWM control:

<figure><img src="../.gitbook/assets/image (7).png" alt=""><figcaption></figcaption></figure>

We added a transistor (BJT, or bipolar junction transistor) to the circuit, a 2N2222, which is a very common transistor that can handle up to 800 mA, enough for most DIY applications. It has 3 pins, the **BASE**, the **COLLECTOR** and the **EMITTER.** The deal is, depending on the current applied at the **BASE,** the path from **COLLECTOR** to **EMITTER** is everything from completely closed to completely open. And the current needed to fully open the transistor is very low, so we can easily control it with PWM. Infact, we need to limit the current of our PWM line, using a sizable resistor R2. 1000 ohm works well for a 2N2222, other transistors might need other values. Here we are using pin 16 from a Pico board.&#x20;

We're not completely done yet. The circuit we're controlling needs to have the same reference as our microcontroller, meaning they have to share ground connection:

<figure><img src="../.gitbook/assets/image (8).png" alt=""><figcaption></figcaption></figure>

Lastly, we'll add some just-in-case; a pull-down resistor on the PWM line to make sure there is no PWM signal being sent if this pin is floating (on startup or if our code has some flaws), and a diode parallel to the resistor to prevent backwards current, typically an issue you can encounter on DC motors. Make sure you put the pull-down resistor before the series resistor on the PWM line, or else you'll be making a voltage divider and wont be able to fully open the transistor.&#x20;

<figure><img src="../.gitbook/assets/image (9).png" alt=""><figcaption></figcaption></figure>

### MOSFET

For higher power applications, you might want to be using a MOSFET instead. Simply putting it, the MOSFET is voltage controlled, not current controlled like the BJTs, and thus uses less power and generates less heat. It is more suited for high power and high frequency circuits. The circuit with a MOSFET will look just a little bit different. The BASE is called **GATE**, the COLLECTOR is called **DRAIN** and EMITTER is called **SOURCE.** These also often have a diode included, so you don't need to add one. You also generally don't need a big resistor in series on the PWM line, but 100 ohm is good to protect the MOSFET from spikes.&#x20;

<figure><img src="../.gitbook/assets/image (10).png" alt=""><figcaption></figcaption></figure>

### Multiple LEDs

Wiring multiple analog LEDs isn't as straight forward as it might seem. Wire them in series and you'll get voltage drop untill the LEDs eventually wont even light up. Wire them in parallell and you'll get current hogging issues (the components aren't physically 100% identical, current will take the path of least resistance), having some LEDs shining brighter and some LEDs turning off before the others when dimming down.&#x20;

In practice however, the voltage drop across each LED is so big (roughly 1.5V to 3V depending on color) that wiring them in series is only an option if you have a pretty high voltage power supply, and current hogging is not really an issue. I recommend wiring the LEDs in parallel, each with their own resistor - the same value as you would with one single LED. If you do have a power supply that can handle your full LED count in series however, that is likely the best way to do it, since you'll be sure every LED gets the same current. In that case you'll have to adjust the size of the resistor according to the total voltage drop.

[Here](https://ledcalculator.net/) is a calculator that will actually set up your LEDs for you, using a mix of series and parallel wiring.&#x20;

#### Parallel

<figure><img src="../.gitbook/assets/image (5).png" alt=""><figcaption></figcaption></figure>

#### Series

<figure><img src="../.gitbook/assets/image (6).png" alt=""><figcaption></figcaption></figure>

Note the 12V power supply; 9V would not be enough to power this chain of LEDs. The value of the resistor would have to be found either by trial and error, or calculated from the LED forward voltage found in the datasheet.&#x20;

### Control switches

Switches to control the PWM channels will be wired like any other switch in your project. They should either in the switch table or in an analog channel.&#x20;
