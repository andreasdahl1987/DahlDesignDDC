---
icon: microchip
---

# CB1

<figure><img src="../.gitbook/assets/image (4) (1) (1) (1) (1) (1).png" alt=""><figcaption><p>CB1 version 1.0</p></figcaption></figure>

The Dahl Design CB1 board is an all-in-one microcontroller board designed for simple to complex projects. It is extremely compact with all its features, is flexible in layout and connectivity, and has build-in support for DDC to make it easy to set up.&#x20;

All design files are free to use and abuse. You'll order your own CB1 through the PCB editor using the steps in this manual.

### Main features

* RP2040 microcontroller processor.
* Up to <mark style="background-color:green;">64 digital pins</mark>
  * 21 directly from the RP2040
  * 32 from 2 x PCA9555 port expanders
  * 8 from 2 x ADS1115 external ACD which can be used as digital inputs
  * 3 additional pins available from the RP2040 if you deactivate some other features
* Up to <mark style="background-color:blue;">12 analog pins</mark>
  * 4 x 16-bit inputs (oversampled from 12 bit) from the onboard RP2040 ADC with a stable voltage reference.&#x20;
  * 8 x 16-bit inputs from 2 x ADS1115 external ADC ICs with adjustable refresh rates and gain.
* Additional <mark style="background-color:orange;">2 USB inputs</mark> for screens or other controllers, using a high quality MTT hub IC to ensure the best performance of USB screens.&#x20;
* Onboard voltage converter to allow inputs of 5-17 volts up to 3 A to drive screens and LEDs.
* LED connector for 5V and a level-shifted data line.
* Super stable 3.2V voltage supply for analog sensors, essentially <mark style="background-color:purple;">immune to voltage drop</mark>.
* <mark style="background-color:green;">EEPROM IC</mark> to store preset choice, as well as bite point, LED brightness and more settings for every preset. This will not be cleared on power-down. You'll get back your settings as they were when you power back up.&#x20;
* All wire holes with 2.54 mm spacing to use pin headers or 2.5-2.54 mm connectors.&#x20;
* Micro-USB plug for programming as well as wire holes/connector for a rigid connection for the final controller assembly.&#x20;
* 4 x M2 mounting holes
* Miniature size: 58.4 mm x 41.1 mm, fits inside standard 70 mm QR bolt pattern.&#x20;
* All components has been chosen with quality and availability in mind.&#x20;

All hardware features are pre-programmed in DDC, making the coding part for CB1 simpler than other microcontroller boards.&#x20;

### Add to your own designs

The full schematics are available through the project page on [OSHWLabs.](https://oshwlab.com/andreasdahl1987/dahl-design-cb1) You can copy these schematics to make your own version of this board. Also, a CB1 device is available in EasyEDA. With this you can add the board as an add-on to your main PCB for buttons, LEDs and switches:

<figure><img src="../.gitbook/assets/image (79).png" alt=""><figcaption></figcaption></figure>

<figure><img src="../.gitbook/assets/image (16) (1) (1).png" alt=""><figcaption></figcaption></figure>

