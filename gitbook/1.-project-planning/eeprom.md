# EEPROM

### What is EEPROM?

EEPROM (Electrically Ereasable Programmable Read Only Memory) is fast read/write memory that doesnt clear on power-down. It can be used to store data like bite point, preset number, LED brightness settings, etc. When you power up the controller, the settings will be what you left them on power down. It will also allow you to adjust your presets with your controller, instead of hardcoding it in the firmware.&#x20;

With EEPROM hooked up, DDC will remember which preset you last selected, and the following settings for all your presets:

* Bite point
* LED brightness
* Throttle hold value
* Brake magic value
* DDS switch position

This will override any global values set in your [presets. ](../3.-coding/advanced/presets/32\_presets.ino.md)But adding fixed per-preset values in the firmware will again overwrite EEPROM.&#x20;

Having EEPROM also allows you to use clutch functions with automatic calibration.&#x20;

### Does my board have EEPROM?

* The **Atmel 32U4** (board such as Pro Micro, Leonardo, etc) natively has 1024 bytes of EEPROM available, which has built-in support from DDC. You just have to turn it on.&#x20;
* The **Dahl Design CB1** has 65 536 bytes of EEPROM available, and EEPROM is automatically activated.&#x20;

All other supported boards _**does not**_ have EEPROM.

There are some libraries that will reserve some of the flash memory of a RP2040 board to be used as EEPROM, but this is far from ideal for a joystick controller - just because of what needs to be activated and deactivated in order to read/write flash memory. It also can't handle as many rewrites as a proper EEPROM IC (100-fold difference), so this is not supported by DDC.&#x20;

The solution is to add a EEPROM device to your project.

### CAT24C512

DDC supports adding EEPROM in the shape of a I2C device called CAT24C512. Since it runs on I2C protocol, it will need to use the SCL and SDA pin on your microcontroller. More on this in the [wiring ](../2.-wiring/eeprom.md)section.

<figure><img src="../.gitbook/assets/image (7) (1).png" alt=""><figcaption></figcaption></figure>



###

