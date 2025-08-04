# Mouse

Since you'll be using your buttons or funky switches to control the mouse cursor, these are already covered earlier in this chapter. The only switch that is somewhat specific to mouse control is the thumbstick. These are also covered under [analog switches](analog/analog-wiring.md), as each switch is just two potentiometers. Each potentiometer will need VCC, GND (these are global, you can wire them together) and a pin for the output signal.&#x20;

<figure><img src="../.gitbook/assets/image (3).png" alt=""><figcaption></figcaption></figure>

This is the RKJXV1220001, which also has a pushbutton. Pins 7-10 are mounting holes. Notice each potentiometer wired to VCC and GND, as well as A1/A2, which should go to analog input pins. When programming this switch, you should set up two [analog channels.](../3.-coding/essentials/10_matrixandanalog.ino/analog-channels.md) This switch also has a pushbutton, it is wired like any other pushbutton, and can be regarded as something completely unrelated to the other features of the switch.&#x20;
