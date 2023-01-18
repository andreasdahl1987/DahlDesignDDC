# Supported hardware

### **Microcontrollers**

* Atmel 32U4 (Pro Micro, Leonardo, Micro, Yùn, etc.)
* Atmel SAM3X8E (Arduino Due or similar)
* Atmel SAMD21\* (Zero, MKR Zero, M0, SAMD21 Mini)
* Atmel SAMD51\* (Adafruit Metro M4)

\*These requires you to use a branch of the joystick library and roll back the code drivers for these boards.

I am looking into RP2040, not supported yet. There is an existing library for using this chip, but the API naming is different from the joystick library DDC uses - requires a re-write of the whole sketch. So it will be easier to rewrite the library's API naming. This will be done when there is a motivation to do so.

### Switches

Most, if not all, commonly used switches in sim racing DIY. That goes for multiposition switches, rotary switches, encoders, buttons, toggles, potentiometers, hall sensors, etc.&#x20;

If you have a switch that doesnt work with DDC, make an[ issue rapport ](https://github.com/andreasdahl1987/DahlDesignDDC/issues)and I'll add support.&#x20;

### **LED**

Any RGB LED that is supported by the [FastLED](https://github.com/FastLED/FastLED) library. Only 32U4 boards have SimHub LED support.

### Shift registers

* 74HC165
* 74HC166

Other 8-bit parallell in/serial out shift registers might work.&#x20;

###

