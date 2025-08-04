# Digital outputs

<figure><img src="../.gitbook/assets/image (1) (1) (1) (1).png" alt="" width="480"><figcaption></figcaption></figure>

DDC supports setting up pins as digital output pins. "Digital" in this sense means they are either on or off (being connected to VCC or ground). Typically, output pins can only supply a low amount of current (up to 50 mA), and can only power tiny devices. The most relevant application would be analog LEDs, but in that regard you can also use PWM control. Here are some differences:

<figure><img src="../.gitbook/assets/image (2) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

There are pros and cons of each method, and they have different applications. PWM requires only a single pin, but more external hardware like transistors and capacitors. A PWM controlled circuit is possible to dim up and down, and you can use any voltage you want. You can also power things like fans or a lightbulb, that require a fair bit of current. Using digital outputs however will give you controll over individual devices (such as LEDs), and you can use SimHub to make an LED profile and control them with telemetry.&#x20;

If you need static backlight for a button box, use PWM. If you want to make revlights for a wheel or dashboard using analog LEDs, use digital outputs.&#x20;

Lets say you have 20 LEDs in your project. That requires 20 output pins. You'll have no pins left for your switches at this point. You can add a [port expander ](switch-inputs/port-expander.md)to your project, and use this either as an output device, or use it for your switches. Each port expander gives you 16 more pins for your project!

The [CB1 board](../cb1/code/settings.md) has its own settings for setting up outputs.
