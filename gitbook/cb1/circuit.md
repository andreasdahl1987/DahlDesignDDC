# Circuit

In case you'd like to copy some/all of the CB1 circuit to your own projects, or are just curious how this works, I'll go through my thoughts around the circuit design. The whole circuit and board design is avaiable at[ OSHWLab.com.](https://oshwlab.com/andreasdahl1987/dahl-design-cb1)

### RP2040

<figure><img src="../.gitbook/assets/image (24).png" alt=""><figcaption></figcaption></figure>

The RP2040 wiring follows a recommended design according to [this document.](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf) I'm using both I2C lines and pull up I2C pins with 2.2K resistors for a bit stronger pullup.&#x20;

<figure><img src="../.gitbook/assets/image (34).png" alt=""><figcaption></figcaption></figure>

The choise of flash IC and the wiring is also accoring to recommended design, with an optional resistor R4 in case the internal pullup on CS# isn't there/not working as expected. I haven't placed this resistor in my assemblies.&#x20;

<figure><img src="../.gitbook/assets/image (74).png" alt=""><figcaption></figcaption></figure>

The USB boot button allows you to start up the board as a USB storage device. Hold this button on power-up.&#x20;

<figure><img src="../.gitbook/assets/image (45).png" alt=""><figcaption></figcaption></figure>

Standard 12 MHz crystal and capacitor size calculated from crystal's load capacitance and estimated stray capacitance.

### USB and HUB

<figure><img src="../.gitbook/assets/image (71).png" alt=""><figcaption></figcaption></figure>

USB in can arrive through the micro connector (USB\_MAIN) or through 4 wire holes (USB\_IN). The data lines go through a filter (L1) and an ESD protection device (ESD), which also has a transient voltage suppression diode for the VBUS. Resistors R17, R18, R24 and R25 are not supposed to  be assembled, but are pads for the option to bypass these filters. The filters are great, but in case of poor/long wires you might experience signal deterioration - and in that case you could bypass the filters, which also deteriorate the signal a bit. Just a "nice to have".&#x20;

<figure><img src="../.gitbook/assets/image (11).png" alt=""><figcaption></figcaption></figure>

UP\_+ and UP\_- arrives at the USB hub, which is a USB2514 from Microchip. This is a circuit largely built on the recommended setup from the datasheet, and has been built and tested by Serkan from [Soelpec](https://soelpec.com/), who uses this in his products. The circuit is a copy of his well-proven design, which has shown itself superior to the standard FE1.1s and SL2.1a hubs you'll see in DIY projects. It should be more stable and give better results with USB screens with less tearing because it is an MTT hub.&#x20;

<figure><img src="../.gitbook/assets/image (43).png" alt=""><figcaption></figcaption></figure>

One port on the hub is used for the RP2040, two are used for 4-pin connectors, typically used for screens. The last port is unused. I'm using 100 µF caps next to the connector placement to give a steady supply for power hungry screens.

### Power

<figure><img src="../.gitbook/assets/image (58).png" alt=""><figcaption></figcaption></figure>

VBUS (power from USB) and VIN (power from external power supply 5-17 volts) meet up here, at the TPS62130, a switching voltage converter **rated for 3A**. Instead of dropping voltage to ground and generating heat, it switches on/off really fast to produce the desired voltage. The positives of this is little power loss, little heat generated and small size. The negatives is the noise it introduces. The inductor (L2) can produce a fair bit of EMI, and is therefore placed a the far corner of the board. Also, the EMI will be a bigger issue the higher the voltage from VIN and the higher the load.&#x20;

Ideally, if using an external power supply, keep the voltage as close to 5V as you can, to make the least amount of EMI.&#x20;

This circuit design was made and tested by Dan Suzuki before I implemented it and did my own tests.&#x20;

The jumper J1 should be open if using VIN to avoid backwards current on USB.&#x20;

<figure><img src="../.gitbook/assets/image (5).png" alt=""><figcaption></figcaption></figure>

We're using a AMS1117 drop-down converter to produce a stable 3.3V line which powers all the ICs in this design. Overall it is very low current on the 3.3V line, so a drop-down converter is fine, and will generate litte heat. **It is rated for 1A.** Screens and LEDs will all be on 5V.&#x20;

### VAN (Vcc Analog) and voltage drop

<figure><img src="../.gitbook/assets/image (25).png" alt=""><figcaption></figcaption></figure>

#### VAN

This is an exciting part of the circuit, and is designed to deal with the complications of the dreaded _**voltage drop.**_ The idea is a power line that stays perfectly stable no matter the load on the circuit. This is to be used for analog switches, such as hall sensors and resistor ladder rotaries. It is also used as the reference voltage for the RP2040.&#x20;

The circuit has two parts; on the left a reference voltage diode, set up to give 3.2V. This works as a reference voltage, but you can't power anything with this. That is where the right side of the circuit comes in; a voltage buffer op-amp, which will use the 5V line to "mimic" the reference voltage. The result is a stable 3.2V line that can be used both as a reference voltage and a power supply (VCC\_SENSOR).&#x20;

I've been getting some good advice from Dan Suzuki on this design.&#x20;

#### Voltage drop

If you haven't already encountered issues with voltage drop, the drop is a natural consequence of increased load on the circuit. The more power it requires, the more your 5V line will drop. Poor quality/long/coiled USB cables will also introduce resistance and consequently voltage drop. When in closes in on 4V, processors like Atmel 32U4 are starting to fail, but you might be getting other complications long before that. Particulary with hall sensors, which will output lower voltages if the input voltage drops, but not in a linear fashion. The problem looks like this:

* You can calibrate your clutch to give a steady 0 - 100% range on paddle movement
* Turn on screen/increase LED brightness
* Load increases and voltage drops
* Hall sensor output changes without the actual magnet positions changing
* Clutch is still steady at 0%, but has a big deadzone at the start and only reaches 75% when pressed.&#x20;

<figure><img src="../.gitbook/assets/image (31).png" alt=""><figcaption></figcaption></figure>

Above is the observed voltage drop on the three power lines of the CB1: 5V, 3.3V and VAN. This is under ideal test conditions with power comming from a power supply with high gauge wires. You'll likely see a bigger drop that starts earlier with a regular USB cable - and even worse with long cables.&#x20;

* Note the 5V line starts dropping well before the 500 mA mark, which is the max output from a USB 2.0 port.&#x20;
* Note that the 3.3V line is stable untill 2000 mA, where the 5V line has dropped so much that the AMS1117 can't do its job properly anymore.
* Note the VAN line staying perfectly stable, just a small upswing around 3000 mA.&#x20;
* Around 3000 mA is where the 3.3V line drops to 2.9V, and the RP2040 shuts down.

_If we increase the voltage of the power supply to 5.5V, we get a completely different picture:_

<figure><img src="../.gitbook/assets/image (51).png" alt=""><figcaption></figcaption></figure>

The extra 0.5V input to the switching converter will give the headroom it needs to hold the voltage steady all the way up to 2000 mA load. And the 3.3V line never drops because the 5V line doesn't go low enough to give the AMS1115 any trouble. As expected, VAN is also stable.&#x20;

Further increasing the input voltage to 9V:

<figure><img src="../.gitbook/assets/image (56).png" alt=""><figcaption></figcaption></figure>

You'll see the voltage drop is eliminated alltogether, however, we're intruducing a new potential issue - which is EMI. 3000 mA with 9V supply gives off a lot of EMI, potentially messing with your magnetic sensors.&#x20;

While this is unlikel to ever be a scenario, the VAN line is also more stable than 3.3V line if the load is on the 3.3V line. Here going up to 1000 mA, which is the max rating for the AMS1115:

<figure><img src="../.gitbook/assets/image (41).png" alt=""><figcaption></figcaption></figure>

Conclusion:

* 5.5V - 6.0V power supply is ideal to avoid voltage drop and avoid EMI.
* Higher voltage power supplies work well as long as you're not pushing heavy load.
* Most DIY designs uses a powered hub for a boosted 5V line. The VAN will give you a steady power supply for analog sensors in these cases.
* Because VAN is used as the reference voltage for the RP2040, you should use VAN for analog switches even if you dont have any voltage drop on the 3.3V line. At least if you're using ADC9-12 pins.&#x20;

### LED

<figure><img src="../.gitbook/assets/image (73).png" alt=""><figcaption></figcaption></figure>

The level shifter IC changes the voltage on the LED data line from 3.3V to 5V to harmonize with the 5V power supply for the LEDs. It ends up in a connector/wire holes with access to VCC/LED PIN/GND for a tidy connection for your LED strip.&#x20;

### I2C devices

#### EEPROM

<figure><img src="../.gitbook/assets/image (29).png" alt=""><figcaption></figcaption></figure>

RP2040 does not have EEPROM built-in. This IC give us the option to store useful stuff like bite point, LED brightness, presets, etc. on power-down. Full explaination [here.](../2.-wiring/eeprom.md)

#### ADC

<figure><img src="../.gitbook/assets/image (37).png" alt=""><figcaption></figcaption></figure>

These two ADCs provides the board with additional 8 analog inputs, with high accuracy and resolution. Full explaination [here.](../2.-wiring/analog/external-adc.md#a-ds1115)

#### Port expander

<figure><img src="../.gitbook/assets/image (42).png" alt=""><figcaption></figcaption></figure>

These two port expanders provides the board with additional 32 digital inputs. Full explaination [here.](../2.-wiring/switch-inputs/port-expander.md)

### I/O

<figure><img src="../.gitbook/assets/image (21).png" alt=""><figcaption></figcaption></figure>

This device doesn't exist physically. It is just a symbol to organize all the pins on the board and make the schematic easier to read.&#x20;
