# External ADC

### ADS1115

#### Power

<figure><img src="../../.gitbook/assets/image (88).png" alt=""><figcaption></figcaption></figure>

* First of all, this thing needs power and ground connection, as well as a 100 nF decoupling cap.&#x20;
* It can be powered with 2.0 - 5.5 V.&#x20;

#### Communication

<figure><img src="../../.gitbook/assets/image (96).png" alt=""><figcaption></figcaption></figure>

* The SDA and SCL pins on ADS1115 needs to go to the SDA and SCL pins on the microcontroller. These are not random pins. On many microcontrollers there are dedicated pins for SDA and SCL.
* On RP2040 you have a lot more freedom, and you also have two sets of SDA/SCL pins to chose from; I2C0 and I2C1. Have a look at a [pico pinout](https://microcontrollerslab.com/wp-content/uploads/2021/01/Raspberry-Pi-Pico-pinout-diagram.svg) to see which pins can do what.&#x20;
* Both SCL and SDA pins needs to be [pulled up](../switch-inputs/shift-registers.md#pull-up-resistors) with a 2.2K resistor. I recommend placing that resistor close to the microcontroller, not close to the port expander.&#x20;

#### I2C Address

<figure><img src="../../.gitbook/assets/image (94).png" alt=""><figcaption></figcaption></figure>

Next up is the ADDR pin. This is the **ADDR**ess pin. In order for the microcontroller and the ADC to find eachother, the ADC needs a name. This is the I2C address. In a circuit design, **devices on the same I2C lines need to have different addresses.** There are 128 different addresses a I2C device can have, but they are hardware determined, and usually a I2C device will only give you the option to choose between a few addresses.

The I2C address for ADS1115 is 10010XX, where "XX" can be configured by you; 00, 01, 10 or 11. This means you can make 4 different addresses, allowing you to wire up 4 ADS1115 to your I2C lines:

* ADDR wired to GND -> 00 -> address 1001000 which is 0x48 in hexadecimal.
* ADDR wired to VCC -> 01 -> address 1001001 which is 0x49 in hexadecimal.
* ADDR wired to SDA -> 10 -> address 1001010 which is 0x4A in hexadecimal.
* ADDR wired to SCL -> 11 -> address 1001011 which is 0x4B in hexadecimal.

_You dont need any pull-up or pull-down resistors for this pin._

#### ALERT/RDY

This is the general idea of how DDC handles the ADS1115:

1. Microcontroller tells the ADC which channel it should look at, how fast it should take a sample, and asks it to do it right away.
2. ADS1115 starts working on the meassurement, while the microcontroller carries on with the rest of its program.
3. Microcontroller comes back to check if the ADC is finished with its sample, or _conversion_, and this is where we have two options.
   1. Read the ALERT/RDY pin, it will be low if conversion is finished.
   2. Call up the ADC over I2C, ask for it to flip into configuration mode, ask for it to send a copy of its configuration register, read out a single bit of the configuration register that will be "1" of the ADC has finished its conversion.
4. If the conversion is not finished, carry on with the program. If the it is finished, ask for the results and tell the ADC to start working on a conversion on the next channel ---> repeat.

As you can see from point #3, using the ALERT/RDY pin to quickly tell if a conversion is ready or not will speed things up quite a bit. However, not using this pin is also completely acceptable. If you're adding 2 or more ADS1115 ICs to your project, I strongly advice to use the ALERT/RDY pin.&#x20;

We'll pull it up with a 10k resistor and connect to any digital pin on the microcontroller. If you dont want to use the ALERT/RDY pin, then do the same - but drop the connection to the microcontroller.&#x20;

<figure><img src="../../.gitbook/assets/image (70).png" alt=""><figcaption></figcaption></figure>

#### Inputs

Lastly, we're got the 4 inputs. Use as many of them as you need, and couple with a 100nF capacitor to filter the signal a bit. Any unused inputs should be grounded.&#x20;

In the example below we'll be using inptuts AIN0 to AIN2, and grounding AIN3 since we're not going to use it. We'll use AIN0 and AIN1 for some hall sensors and AIN2 for a potentiometer.&#x20;

<figure><img src="../../.gitbook/assets/image (1) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>
