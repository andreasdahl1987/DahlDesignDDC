# Load cell

The center point of a load cell schematic is a load cell amplifier. This IC will power the loadcell, measure its output, boost the output and convert it to a digital number, and lastly send this number to the microcontroller. Lets start with wiring the HX711 chip.&#x20;

### 1. Power and data

<figure><img src="../.gitbook/assets/image (126).png" alt=""><figcaption></figcaption></figure>

The HX711 will be powered by the logic voltage of your microcontroller. So that will be 5V for a 32U4 board and 3.3V for a RP2040 board. You should add a 100nF decoupling capacitor next to both DVDD pin and VSUP pins, as well as a 10µF filtering capacitor next to VSUP pin.&#x20;

DOUT is the serial data pin and PD\_SCK is the serial clock. The data pin is where the data is sent, the clock is used to drive and organize data transfer. You can use any digital pins on your microcontroller for these.&#x20;

### 2. Samples and sample rate

<figure><img src="../.gitbook/assets/image (127).png" alt=""><figcaption></figcaption></figure>

HX711 has two channels for recieving load cell signals, channel A and channel B. Both channels have a positive and negative input. Channel A is a high resolution, low noise channel. Channel B is less accurate, and typically used for crude measurements. We will not be using channel B, so INPB (in, positive, B) and INNB (in, negative, B) will be grounded. Pins INPA and INNA will have each their lead with a spike protection resistor  (R2 and R3) and a capacitor (C4) that together with the resistors makes an RC filter. The A- and A+ leads will be connected to the load cell eventually.&#x20;

The chip has an internal clock, but you can also use an external clock if you want. Pins XO and XI are for connecting an external crystal oscillator. If you want to use the internal clock just wire XI to ground and leave XO floating. _The clock is only used for adjusting and stabilizing the sample rate_ (how fast the HX711 is reading new values from the loadcell).&#x20;

The internal clock is running at 11 MHz. This will give you a sample rate of 10 Hz or 80 Hz, depending on how you set up the RATE pin. RATE pin grounded will give you slow sampling, RATE pin pulled up (R1) to VCC will give you fast sampling. The latter is recommended, 10 Hz is too slow. If you want even faster sample rates, you can use an external crystal oscillator wired to XI and XO. For instance, a 20 MHz crystal oscillator will give you a sample rate of 144 Hz if RATE pin is pulled up.&#x20;

### 3. Powering the load cell

The HX711 is comparing the load cell output signal to the voltage powering the load cell. And with the extremely low voltages returned by the loadcell, the smallest amount of noise can make a big impact on signal quality. This means you need a clean and steady power supply, and that is _**not**_ VCC. Luckily, HX711 has a built in regulator that supplies a clean and stable voltage by using a voltage reference (VBF) and feedback pin (VFB) together with a voltage divider (R4 and R5) that can manipulate a transistor (Q1) to control the voltage level. After that we add a ferrite bead (L1) and filtering/decoupling caps (C6 and C7) to further clean and stabilize the signal.&#x20;

R4 and R5 values set the voltage for the load cell at roughly 85% of VCC. According to the datasheet, the voltage should not be above VCC - 0.1 V, so this gives us some margins without going too low. VBG is feeding a 1.25V reference for VFB pin to compare to, but this is done internally. On the outside we just need to decouple this pin with a 100 nF cap to ground. The result is a clean power source for the load cell, **E+.**&#x20;

Recommend S8550 for Q1 and MLF1608A3R3JT000 for L1.&#x20;

<figure><img src="../.gitbook/assets/image (129).png" alt=""><figcaption></figcaption></figure>

### 4. Connecting the load cell

Load cells typically have four wires and a shield.&#x20;

* Red wire --> E+
* White wire --> A-
* Green wire --> A+
* Black wire --> Ground plane
* Shield:
  * Suboptimal: Leave unconnected
  * Optimal: Wire to ground plane close to HX711 AGND pin with an RC filter circuit.

<figure><img src="../.gitbook/assets/image (130).png" alt=""><figcaption></figcaption></figure>
