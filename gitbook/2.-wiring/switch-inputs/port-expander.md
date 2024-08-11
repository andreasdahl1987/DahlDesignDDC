# Port expander

Wiring the PCA9555 is fairly straight forward. It has 24 pins. 8 of these are to make the chip work, and the remaining 16 are the input/output pins.

#### Power

<figure><img src="../../.gitbook/assets/image (92).png" alt=""><figcaption></figcaption></figure>

* First of all, this thing needs power and ground connection, as well as a 100 nF decoupling cap.&#x20;
* It can be powered with 2.3 - 5.5 V.&#x20;

#### Communication

Next up is connecting it to a microcontroller:

<figure><img src="../../.gitbook/assets/image (93).png" alt=""><figcaption></figcaption></figure>

* The SDA and SCL pins on PCA9555 needs to go to the SDA and SCL pins on the microcontroller. These are not random pins. On many microcontrollers there are dedicated pins for SDA and SCL.
* On RP2040 you have a lot more freedom, and you also have two sets of SDA/SCL pins to chose from; I2C0 and I2C1. Have a look at a [pico pinout](https://microcontrollerslab.com/wp-content/uploads/2021/01/Raspberry-Pi-Pico-pinout-diagram.svg) to see which pins can do what.&#x20;
* Both SCL and SDA pins needs to be [pulled up](shift-registers.md#pull-up-resistors) with a 2.2K resistor. I recommend placing that resistor close to the microcontroller, not close to the port expander.&#x20;
* Lastly, the INT# pin, which is the interrupt. You can wire this to any digital pin on the microcontroller. Pin 4 is used in the example above. The PCA9555 is constantly checking if any inputs have changed. It if detects a change, the INT# pin will be grounded, and we can read a "0" on this line. The DDC software will only take in new input values from the port expander if there is a "0" here. So unless anything has changed, no processing power is used on reading the port expander.&#x20;
* When adding more port expanders, or even other I2C devices, wire them to the same SDA and SCL lines. No additional pullup resistors requred. Every PCA9555 will need its own interrupt pin though.&#x20;

#### I2C address

Next up are the A0-A2 pins. These are not **A**nalog pins, they are **A**ddress pins. In order for the microcontroller and the port expander to find eachother, the port expander needs a name. This is the I2C address. In a circuit design, **devices on the same I2C lines need to have different addresses.** There are 128 different addresses a I2C device can have, but they are hardware determined, and usually a I2C device will only give you the option to choose between a few addresses for your chip. I guess the manufacturer talk with eachother, because rarely will you have the issue that you can't have the devices you need for your design because the I2C addresses crash.&#x20;

The 3 pins A0-A2 offer a way for you to change the address of the port expander. An I2C address is a 7-bit value. For the PCA9555 it is `0100XXX` where XXX is A2, A1 and A0. Like this:&#x20;

<figure><img src="../../.gitbook/assets/image (81).png" alt=""><figcaption></figcaption></figure>

This figure is from the PCA9555 datasheet. It says the last 3 bits in the address are "programmable", but in practice it is hardware wired. If course, you could connect these pins to your microcontroller and adjust the address on the fly, but that doesnt make much sense.&#x20;

The 3 pins, representing 3 bits in the address gives you 8 possible addresses, which means you can connect up to 8 PCA9555, a total of 128 inputs. We typically write these addresses in hexadecimal format; for the PCA9555 these are addreses 0x20 to 0x27, where 0x20 have all 3 pins grounded and 0x27 have all 3 pins connected to VCC.&#x20;

<figure><img src="../../.gitbook/assets/image (85).png" alt=""><figcaption></figcaption></figure>

In the example above, all 3 pins are grounded. The I2C address will be 0x20.&#x20;

#### Input pins

What we're left with are the 16 input pins. You wire switches to these as you would with [direct wiring](non-matrix-wiring.md) or with [shift registers](shift-registers.md). Common pins to ground and input pins directly to the port expander pins. The example below shows 3 encoders with pushbutton. Knowing that pins 1-8 and 9-16 are on seperate rows, and knowin the [switch table rules](../../1.-project-planning/switch-inputs/matrix.md#rules), we should keep encoder pins next to eachother and on the same row.&#x20;

<figure><img src="../../.gitbook/assets/image (95).png" alt=""><figcaption></figcaption></figure>
