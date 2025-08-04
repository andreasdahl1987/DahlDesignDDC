# Brightness

DDC allows for full customization of LED brightness. Every LED function allows you to set a brightness level. This is used to adjust brightness relative to the other LEDs in the project. In addition there is a master brightness level, which affects all LEDs equally, keeping the relative difference between them. The relative brightness defaults to 100% for the colorLED and triggerLED functions, so you don't have to type in any brightness for those unless you want it lower than 100%.&#x20;

The brightness setting in SimHub will not have any effect on the brightness of LED calls from the firmware.&#x20;

The global brightness is set to 25 by default, ranging from 0 to 100, meaning the controller will start with this setting on powerup. If you're using EEPROM, each of your presets will have an individual brightness setting. These also all default to 25. Whenever brightness is adjusted, the new value will be stored in EEPROM only for the current preset.&#x20;

You can edit the global brightness with [switch functions](../../../../switch-library/led-control.md) or editor function [setBrightness()](../../../advanced/conditional-coding/editors.md#setbrightness-int-brightness).&#x20;

A nice place to use this function is in 32\_Presets.ino, specifying a volume for each preset:

```
switch (presetNumber)
{
case 0: //PRESET 1 
    setBrightness(15);
    break;
case 1: //PRESET 2 
    setBrightness(40);
    break;
case 2: //PRESET 3 
    setBrightness(60);
    break;
case 3: //PRESET 4 
    setBrightness(0);
    break;
case 4: //PRESET 5 
    setBrightness(90);
    break;
case 5: //PRESET 6 
    setBrightness(10);
    break;
case 6: //PRESET 7 

    break;
case 7: //PRESET 8 

    break;
case 8: //PRESET 9 

    break;
case 9: //PRESET 10

    break;
case 10: //PRESET 11 

    break;
case 11: //PRESET 12 

    break;
}
```

In this case, brightness for preset 1 will be 15%, for preset 2 40%, etc. Preset 4 has brightness set to 0%, which basically turns off the LEDs. Presets 7-12 have no set value, and will use the default 25%.&#x20;
