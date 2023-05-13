# LED control

These functions control [LED brightness.](../3.-coding/peripherals/leds-code-and-connection/firmware-control/brightness.md)

#### rotary2Brightness()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the rotary2bit [category](encoders/#rotary2bit). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the LED brightness level up and down by increments of 2%.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2Brightness(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotary2Brightness(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### funkyBrightness()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the funkyRotary [category](encoders/#funkyrotary). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the LED brightness level up and down by increments of 2%.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyBrightness(int Arow, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyBrightness(2, 3, 4, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### PEC11Brightness()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the PEC11 [category.](encoders/#pec11) Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the LED brightness level up and down by increments of 2%.&#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Brightness(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11Brightness(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### rotaryPulseBrightness()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the rotaryPulse [category](encoders/#rotarypulse). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the LED brightness level up and down by increments of 2%.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotaryPulseBrightness(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotaryPulseBrightness(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### rotaryAnalogBrightness()

{% tabs %}
{% tab title="Description" %}
12 - position switch. Absolute.&#x20;

Produces no button presses, but the position of the switch is still detected by the firmware and can be used for [conditional coding](../3.-coding/advanced/conditional-coding/) or [rotaryInject](../3.-coding/advanced/analog-inject.md#rotaryinject). The switch works like a volume knob for your LEDs, and you can adjust how big impact is has on the brightness.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalogBrightness(int analogPin, int switchNumber, int startBrightness, endBrightness int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalogMute(`

`A3,` <- The analog pin this switch is connected to

`2,` <- The switch number this analog switch is assigned

`5,` <- The lowest brightness setting (position 1 on the switch)

`70,` <- The highest brightness setting (position 12 on the switch)

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the brightness instead of reducing. \
  So typed out in 30\_Switches.ino:

`rotaryAnalogBrightness(A3, 2, 5, 70, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`

This switch will set the brightness to 5% in position 1 and 70% in position 12. The positions in between will be a gradual increase from 5 to 70%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}

#### rotaryAnalogBrightness12()

{% tabs %}
{% tab title="Description" %}
12 - position switch. Absolute.&#x20;

Works similar to[ rotaryAnalogSimple()](rotary-switches/rotaryanalog.md#rotaryanalogsimple), but with the added feature of setting the LED brightness if rotating this switch while the modButton is held. Adjustments with increments of 2%.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalogBrightness12(int analogPin, int switchNumber, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalogMute(`

`A3,` <- The analog pin this switch is connected to

`2,` <- The switch number this analog switch is assigned

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the brightness instead of reducing. \
  So typed out in 30\_Switches.ino:

`rotaryAnalogBrightness12(A3, 2, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* 12 button numbers
* modButton()
{% endtab %}
{% endtabs %}

r
