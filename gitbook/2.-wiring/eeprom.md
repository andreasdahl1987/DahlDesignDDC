# EEPROM

The EEPROM IC that is supported is CAT24C512, which is cheap and has good stock on JLCPCB. It is fast, has plenty of storage and uses I2C protocol to communicate with the microcontroller.&#x20;

#### Power

<figure><img src="../.gitbook/assets/image (10).png" alt=""><figcaption></figcaption></figure>

* First of all, this thing needs power and ground connection, as well as a 100 nF decoupling cap.&#x20;
* It can be powered with 1.8 - 5.5 V.&#x20;

#### Communication

<figure><img src="../.gitbook/assets/image (35).png" alt=""><figcaption></figcaption></figure>

* The SDA and SCL pins on CAT24C512 needs to go to the SDA and SCL pins on the microcontroller. These are not random pins. On many microcontrollers there are dedicated pins for SDA and SCL.
* On RP2040 you have a lot more freedom, and you also have two sets of SDA/SCL pins to chose from; I2C0 and I2C1. Have a look at a [pico pinout](https://microcontrollerslab.com/wp-content/uploads/2021/01/Raspberry-Pi-Pico-pinout-diagram.svg) to see which pins can do what.&#x20;
* Both SCL and SDA pins needs to be [pulled up](switch-inputs/shift-registers.md#pull-up-resistors) with a 2.2K resistor. I recommend placing that resistor close to the microcontroller, not close to the port expander.

#### Write protect

* The WP pin allows you to lock/unlock the IC for writing. DDC doesn't use this, the code itself has a software lock to ensure it is not being used when not needed. This pin is set to GND to leave it always open for writing.&#x20;

<figure><img src="../.gitbook/assets/image (3).png" alt=""><figcaption></figcaption></figure>

#### I2C Address

Next up are the A0-A2 pins. These are not **A**nalog pins, they are **A**ddress pins. In order for the microcontroller and the EEPROM IC to find eachother, the IC needs a name. This is the I2C address. In a circuit design, **devices on the same I2C lines need to have different addresses.** There are 128 different addresses a I2C device can have, but they are hardware determined, and usually a I2C device will only give you the option to choose between a few addresses for your chip. I guess the manufacturer talk with eachother, because rarely will you have the issue that you can't have the devices you need for your design because the I2C addresses crash.&#x20;

The 3 pins A0-A2 offer a way for you to change the address of the EEPROM IC. An I2C address is a 7-bit value. For the CAT24C512 it is `1010XXX` where XXX is A2, A1 and A0. Like this:&#x20;

<figure><img src="../.gitbook/assets/image (36).png" alt=""><figcaption></figcaption></figure>

The 3 pins, representing the last 3 bits in the address gives you 8 possible addresses. DDC default is 1010_**000**_, but you can change this in the sketch. DDC only supports 1 EEPROM IC. I'm pretty sure you wont be needing more.&#x20;

We typically write these addresses in hexadecimal format; for the CAT24C512 these are addreses 0x50 to 0x57, where 0x50 have all 3 pins grounded and 0x57 have all 3 pins connected to VCC.&#x20;

For this example, we'll ground all address pins to get I2C adress 0x50, or 1010000, which is the DDC default:

<figure><img src="../.gitbook/assets/image (28).png" alt=""><figcaption></figcaption></figure>

