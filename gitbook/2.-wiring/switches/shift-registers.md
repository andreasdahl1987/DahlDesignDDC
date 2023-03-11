# Shift registers

The supported shift registers (SR) are 8-bit parallel input/serial output devices. The go-to SR is 74HC165 or 74HC166.&#x20;

The wiring here will be a bit more complex, as we need to set up pull-up resistors and control the various pins of the SR to make work like we want it to work. I'll go over the whole thing in detail. You don't need to fully understand this to use SRs, you can just follow the schematics.

### Pull-up resistors

An essential part of reading button states is using pull-up resistors. For direct wiring and matrix wiring we can use the integrated pull-up resistors in the microcontroller, so that becomes part of the software. For SR wiring we don't have that option, as the SR does not have internal pull-up resistors.&#x20;

This is how it works:

<figure><img src="../../.gitbook/assets/image (17) (1).png" alt=""><figcaption></figcaption></figure>

* When the button is _**not pressed**_, there is no way for current to get to ground. The voltage at the level of RECIEVER, which in our case is the SR, is the same as VCC (typically +5 volt in Arduino projects).&#x20;
* When the button is _**pressed,**_ current will flow to ground and voltage will drop from VCC before the 10K resistor to 0 at ground level. Pratically 100% of the voltage drop will be across the resistor. So measuring the voltage after the resistor, it will be essentially equal to ground.&#x20;
* The end result is a system where we can measure the voltage to VCC when button is not pressed and GND when button is pressed. In digital terms that would be "1" and "0", respectively.&#x20;

### Input pins

Below is the wiring explained for the **74HC165 chip.** The pin numbers are different on the 74HC166.

&#x20;The inputs are labeled D0 to D7, but can also be labeled "a" to "h". In the same way as the example above, every input pin has gotten its button which is connected to ground on one side and pulled up to VCC on the other side - via a 10K ohm resistor.&#x20;

<figure><img src="../../.gitbook/assets/image (15).png" alt=""><figcaption></figcaption></figure>

For encoders, common pin goes to ground and A/B pins get each their input. As with the rules in the matrix planning, encoder inputs should be adjacent to each other.

In the example below, the 3 buttons on D0-D2 has been replaced with an encoder with pushbutton. Note the C pin (common pin) of the encoder goes to ground, and the A/B pins goes to adjacent inputs on the SR.

<figure><img src="../../.gitbook/assets/image (30).png" alt=""><figcaption></figcaption></figure>

Below is an example with a funky switch. It uses 7/8 inputs, so a pushbutton is added to the 8th input. Notice the common for the pushbuttons (pin 6) and the common for the encoder (9) are both connected to ground.&#x20;

<figure><img src="../../.gitbook/assets/image (7).png" alt=""><figcaption></figcaption></figure>

To make it more structured and readable, we can use net flags (words instead of wires) and resistor arrays (basically a chip that is built up of many resistors of the same size side by side).

<figure><img src="../../.gitbook/assets/image (24) (1).png" alt=""><figcaption><p>This is the same as the first example</p></figcaption></figure>

### VCC and GND

<figure><img src="../../.gitbook/assets/image (16).png" alt=""><figcaption></figcaption></figure>

The chip needs power. So it needs to be connected to VCC and GND. Common practice with any power consuming IC that you add a small capacitor next to the VCC pin, connected to VCC and GND. This is called a "decoupling" capacitor, and works like a micro battery to ensure steady voltage and current to the VCC pin.&#x20;

### Pins to microcontroller

There are 6 pins left, these are for controlling the SR. Three of these needs to be connected to the microcontroller's digital pins. Those are pins 9, 2 and 1.

#### Pin 9: Q7 (DATA)

Q7 or QH. This is the pin that the microcontroller will read to get data from the SR.  It is referred to as DATA.&#x20;

#### Pin 2: CP (CLOCK)

CP or CLK. This is the pin where the microcontroller can manipulate the SR's clock. Explained in more detail below. Referred to as CLOCK.&#x20;

#### **Pin 1: PL# (LATCH)**

PL#, SH, LD#, PE#. This pin has many names. It is referred to as **LATCH.** It is pin 1, and it is used to swap between recieving parallell data and sending serial data. This might sound confusing, but it isn't all that complex.&#x20;

When this pin is **low** (connected to GND), the SR will read the inputs from every input port. Making up a 8-bit value. To read the input pins, the clock must toggle off/on once.

<figure><img src="../../.gitbook/assets/image (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

In this case, a button on pin D0, D1, D2, D5 and D7 is pressed. Recieving data from 8 inputs at the same time is what makes it "8-bit parallel in..."

When this pin is **high** (connected to VCC), the SR will switch to sending serial data. In other words, a single bit of data is presented to the data pin to be read by the microcontroller. To present the next bit, the clock must toggle off/on once.&#x20;

<figure><img src="../../.gitbook/assets/image (21) (1).png" alt=""><figcaption></figcaption></figure>

So in essence, there is a cycle of:

* LATCH **low** to enable reading inputs and disable sending data.
* Toggle the CLOCK **low-high** to read the inputs
* LATCH **high** to enable sending data and disable reading inputs.
  * Read the value on the DATA pin with microcontroller
  * Toggle CLOCK **low-high** to push in the next bit to the DATA pin
  * Repeat untill all bits have been read by the microcontroller
* Repeat forever

### Remaining pins

3 pins left: Pin 7, 10 and 15.

#### **Pin 7: Q7#**&#x20;

This pin gives the same info as the DATA pin (pin 9), but inverted. So 0's are 1' and 1's are 0's. Actually, using this pin for data would be better than pin 9 if you're using pullup resistors, since you'd get 1's when pressing buttons, instead of 0's - which translates directly to a button press in the library. But, since most projects use pin 9, DDC also uses pin 9. It is common to leave this pin **floating** (not connected to anything).

**Pin 10: DS**

DS or SER is the serial input. This is used for chaining SR's together. Through this pin, the SR can recieve the datastream from the serial output (pin 9) from another SR. This way, multiple SR can be chained together. It should be connected to **ground** when not used.

**Pin 15: CE#**&#x20;

CE# or CLK INH can be used to inhibit the clock. If pulled high, the clock will stop working. It can also be used as a clock interchangably with pin 2: If pin 2 is low, pin 15 works as clock. If pin 15 is low, pin 2 works as clock. But since most projects use pin 2 as clock, DDC uses pin 2 as clock. CE# should be connected to **ground** to allow the clock to work.&#x20;

### Put it together

<figure><img src="../../.gitbook/assets/image (28).png" alt=""><figcaption></figcaption></figure>

All in all, it could look like this. Here, using a Pro Micro board and using pins 2, 3 and 4.&#x20;

### Chaining shift registers

<figure><img src="../../.gitbook/assets/image (32).png" alt=""><figcaption></figcaption></figure>

As described above, you can chain as many SRs as you like together by just connecting pin 10 to pin 9 on the next SR. The first SR in the chain connects pin 9 to the microcontroller. The last SR has its pin 10 pulled low.&#x20;

### 74HC166

The 74HC166 has a completely different pin setup:

<figure><img src="../../.gitbook/assets/image (2) (5).png" alt=""><figcaption></figcaption></figure>

The reversed serial data output from pin 7 on 165 does not exist on 166. Instead it has pin 9, MR#. This is a master reset. When this pin is low, the shift register is reset to all 0s. So this pin has to be pulled high with a pullup resistor to make the SR work.&#x20;
