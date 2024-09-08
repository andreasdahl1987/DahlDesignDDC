# Analog inputs

DDC supports an unlimited number of analog switches (clutches, potentiometer, multiposition switches). Analog switches are **not** set up in the [switch table](../switch-inputs/matrix.md#planning-the-switch-table), but instead set up in analog channels.&#x20;

When adding analog switches to your project (potentiometer, resistor ladder rotary, hall sensors, load cells, etc.), you'll build a channel for each switch. A channel will contain all the information related to that switch, including its analog pin, button numbers used, switch modes, readout values, cooldown timers, rotary switch position and more under-the-hood stuff to make the algorithms work.&#x20;

<figure><img src="../../.gitbook/assets/image (12) (1).png" alt=""><figcaption><p>How you can imagine an analog channel holding all the necessary information for an analog switch.</p></figcaption></figure>

When your switch has its own channel, you'll have the freedom of tapping into this channel for various software features, such as having values from this channel trigger RGB LEDs, PWM signal firing, or even build virtual switches in the switch table by using [analogInject. ](../../3.-coding/advanced/analog-inject.md)

When planning your analog channels, there are 3 things you should note for each channel:

* _Pin number:_ The analog pin this switch is wired to.
* _Button number:_ In case this switch needs some buttons numbers, note the starting button number. So if this is a 12-position switch and you want it to use button numbers 25-36, then **25 i**s your number.
* _Alternate button number:_ In case your switch has several switch modes, you can use different button numbers in different modes. For instance, you can have your 12-position switch using button numbers 25-36 in 12-position mode, but when set to incremental mode it uses button number 10 and 11. As above, the starting button number is what you should note, so **10** in this case.

Keep in mind, the RP2040 microcontroller can have its ADC [oversampled,](../../3.-coding/essentials/dahldesignddc.ino.md#activate-oversampling) giving you higher resolution analog signals without any drawback.&#x20;
