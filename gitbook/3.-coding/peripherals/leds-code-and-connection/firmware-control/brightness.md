# Brightness

DDC allows for full customization of LED brightness. Every LED function requires you to set a brightness level. This is used to adjust brightness relative to the other LEDs in the project. In addition there is a master brightness level, which affects all LEDs equally, keepign the relative difference between them.

The brightness setting in SimHub will not have any effect on the brightness of LED calls from the firmware.&#x20;

The global brightness is set to 100 by default, ranging from 0 to 100., meaning the controller will start with this setting on powerup.This can be changed by editing the parameter `LEDBrightness` in 12\_GlobalVariables.ino

<figure><img src="../../../../.gitbook/assets/image (14) (1).png" alt=""><figcaption></figcaption></figure>

To adjust brightness on the fly, there are [switch functions](../../../../switch-library/led-control.md) that control brightness.
