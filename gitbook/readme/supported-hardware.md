# Supported hardware

### **Microcontrollers**

* Dahl Design CB1
* Atmel 32U4 (Pro Micro, Leonardo, Feather, Micro, Yùn, and many more)
* Atmel SAM3X8E\* (Arduino Due or similar)
* Atmel SAMD21\* (Zero, MKR Zero, M0, SAMD21 Mini)
* Atmel SAMD51\* (Adafruit Metro M4)
* Raspberry Pi RP2040 (Raspberry Pi Pico, Pro Micro RP2040, Feather RP2040, and many more)

\*These microcontrollers currenly dont have LED support.

### Switches

* Most, if not all, commonly used switches in sim racing DIY. That goes for multiposition switches, rotary switches, encoders, buttons, toggles, potentiometers, hall sensors, etc.&#x20;

If you have a switch that doesnt work with DDC, make an[ issue rapport ](https://github.com/andreasdahl1987/DahlDesignDDC/issues)and I'll add support.&#x20;

### **LED**

* Any addressable RGB (not RGBW) LED that is supported by the [Adafruit Neopixel library. ](https://github.com/adafruit/Adafruit\_NeoPixel)
* Analog LEDs using PWM or digital output.

### Integrated circuits

* Shift registers
  * 74HC165
  * 74HC166
  * Other 8-bit parallell in/serial out shift registers might work.&#x20;
* Port expanders
  * PCA9555
* ADC (analog to digital converter)
  * ADS1115
* EEPROM
  * CAT24C512

### Circuit control

* Controlling other circuits, DC motors and more using PWM.

