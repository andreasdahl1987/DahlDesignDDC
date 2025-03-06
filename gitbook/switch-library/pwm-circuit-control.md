# PWM / Circuit control

These functions control [PWM channels](../1.-project-planning/pwm-circuit-control.md).&#x20;

Generally, these functions will adjust the channel volume (0 - 100% within the set PWM range on the channel) or turn the channel on/off (switching between the set volume and outputting 0V on the PWM channel).&#x20;

#### PWMToggle()

{% tabs %}
{% tab title="Description" %}
Use a toggle switch to turn a PWM channel on/off, or just use a regular button (will have to be held pressed unless it is a physically latching button).&#x20;
{% endtab %}

{% tab title="Example" %}
`void PWMToggle(int row, int column, int PWMChannel)`

Example:

* A toggle switch on row 4 column 2.
* Controlling PWM channel 3.&#x20;

`PWMToggle(4, 2, 3);`
{% endtab %}

{% tab title="Requirements" %}
* 1 PWM channel
{% endtab %}
{% endtabs %}

#### PWMPot()

{% tabs %}
{% tab title="Description" %}
Set up a potentiometer to adjust the volume of a PWM channel.
{% endtab %}

{% tab title="Example" %}
`void PWMPot(int analogChannel, int startValue, int endValue, int PWMChannel )`

Example:

* Potentiometer on analog channel 2.
* Using checkValue(2) in 30\_switches we've found the range of the potentiometers values to be 0 to 1021.
* Controlling PWM channel 3 volume.&#x20;

`PWMPot(2, 0, 1021, 3);`
{% endtab %}

{% tab title="Requirements" %}
* 1 PWM channel
{% endtab %}
{% endtabs %}

#### rotary2PWM()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the rotary2bit [category](encoders/#rotary2bit). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the PWM volume up and down by a custom increment.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2PWM(int row, int column, bool reverse, int8_t PWMChannel, int8_t stepSize)`

Example:

* Encoder with pins A and B to columns 3 and 4. Common pin to row 2.
* Controlling PWM channel 3 volume with increments of 5%.&#x20;

`rotary2PWM(2, 3, false, 3, 5);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
* 1 PWM channel
{% endtab %}
{% endtabs %}

#### funkyPWM()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the funkyRotary [category](encoders/#funkyrotary). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the PWM volume up and down by a custom increment.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyPWM(int Arow, int Acolumn, int Bcol, bool reverse, int8_t PWMChannel, int8_t stepSize)`

Example:

* Encoder with pins A and B to columns 3 and 4. Common pin to row 2.
* Controlling PWM channel 3 volume with increments of 5%.&#x20;

`funkyPWM(2, 3, 4, false, 3, 5);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
* 1 PWM channel
{% endtab %}
{% endtabs %}

#### PEC11PWM()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the PEC11 [category.](encoders/#pec11) Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the PWM volume up and down by a custom increment.&#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11PWM(int row, int column, bool reverse, int8_t PWMChannel, int8_t stepSize)`

Example:

* Encoder with pins A and B to columns 3 and 4. Common pin to row 2.
* Controlling PWM channel 3 volume with increments of 5%.&#x20;

`PEC11PWM(2, 3, false, 3, 5);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
* 1 PWM channel
{% endtab %}
{% endtabs %}

#### rotaryPulsePWM()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the rotaryPulse [category](encoders/#rotarypulse). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the PWM volume up and down by a custom increment.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotaryPulsePWM(int row, int column, bool reverse, int8_t PWMChannel, int8_t stepSize)`

Example:

* Encoder with pins A and B to columns 3 and 4. Common pin to row 2.
* Controlling PWM channel 3 volume with increments of 5%.&#x20;

`rotaryPulsePWM(2, 3, false, 3, 5);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
* 1 PWM channel
{% endtab %}
{% endtabs %}

#### rotaryAnalogPWM()

{% tabs %}
{% tab title="Description" %}
12 - position switch. Absolute.&#x20;

Produces no button presses, but the position of the switch is still detected by the firmware and can be used for [conditional coding](../3.-coding/advanced/conditional-coding/) or [rotaryInject](../3.-coding/advanced/analog-inject.md#rotaryinject). The switch works like a volume knob for a PWM channel.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalogPWM(int analogChannel, int PWMChannel, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalogPWM(`

`2,` <- The analog channel this switch is set up on

`2,` <- The PWM channel it controls

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the brightness instead of reducing. \
  So typed out in 30\_Switches.ino:

`rotaryAnalogPWM(2, 2, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`

This switch will set the volume to 0% in position 1 and 100% in position 12. The positions in between will be a gradual increase from 0 to 100%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 1 PWM channel
{% endtab %}
{% endtabs %}

#### rotaryAnalogPWM12()

{% tabs %}
{% tab title="Description" %}
12 - position switch. Absolute.&#x20;

Works similar to[ rotaryAnalogSimple()](rotary-switches/rotaryanalog.md#rotaryanalogsimple), but with the added feature of producing button presses in each position. To adjust PWM volume you'l have to hold a modButton. Adjustments are with a custom increment.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalogPWM12(int analogChannel, int PWMChannel, int stepSize, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalogPWM12(`

`2,` <- The analog channel this switch is set up on

`2,` <- The PWM channel it controls

`5,` <- The increments of volume adjustment

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the brightness instead of reducing. \
  So typed out in 30\_Switches.ino:

`rotaryAnalogPWM12(2, 2, 5, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* 12 button numbers
* modButton()
* 1 PWM channel
{% endtab %}
{% endtabs %}
