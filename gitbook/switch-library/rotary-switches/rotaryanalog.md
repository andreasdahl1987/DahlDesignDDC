# rotaryAnalog

All rotaryAnalog functions are for 12-position switches. The most common are 8, 10, 12 and 16 positions - with 12 being the most common. These functions can be[ edited](editing-functions.md) without too much hassle to match larger numbers of positions.&#x20;

For fewer than 12 positions, simply use a dummy value for the unused positions, a value the switch will never be close to reaching. For instance:

`rotaryAnalogSimple(2, 58, 209, 342, 462, 565, 680, 848, 1023, 10000, 10000, 10000, 10000, false);`\
Here, a 8 position switch is used, and the last 4 positions are given the value "10 000".&#x20;

#### <mark style="background-color:blue;">rotaryAnalog()</mark>

{% tabs %}
{% tab title="Description" %}
Setup with several switch modes, including a [hybrid switch.](../multiswitch-complexes/#hybrid) You can set the amount of positions of the hybrid switch to any number.&#x20;

Modes:

* 0: 12-position switch. Absolute.
* 1: Incremental
* 2: Open hybrid, X positions
* 3: Closed hybrid

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 4 modes it uses 2 slots in the field.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalog(int analogChannel, int fieldPlacement, int hybridPositions, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalog(`

`2,` <- analog channel

`1,` <- placement in rotary field

`7,` <- Switch positions in hybrid mode

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1. Uses two slots in the bit field (1 and 2). So \[DahlDesign.DDCR1] and \[DahlDesign.DDCR2] and will show the modes.
* Hybrid switch has 7 positions. The starting number of the hybrid switch and 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`rotaryAnalog(2, 1, 7, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* hybridButton() to lock position and use rotary as incremental switch.
* X button numbers, minimum 12, determined by the largest number of positions in any mode.
* Two slots in the rotary field.&#x20;
{% endtab %}
{% endtabs %}

#### rotaryAnalogSimple()

{% tabs %}
{% tab title="Description" %}
12 - position switch. Absolute.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalogSimple(int analogChannel, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalogSimple(`

`2,` <- analog channel

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* The starting number of the 12-positions is determined by the number set in the block for `analogButtonNumber[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`rotaryAnalogSimple(2, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* 12 button numbers
{% endtab %}
{% endtabs %}

#### rotaryAnalogMute()

{% tabs %}
{% tab title="Description" %}
12 - position switch. Absolute.&#x20;

Produces no button presses, but the position of the switch is still detected by the firmware and can be used for [conditional coding](../../3.-coding/advanced/conditional-coding/) or [rotaryInject](../../3.-coding/advanced/analog-inject.md#rotaryinject).&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalogMute(int analogChannel, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalogMute(`

`2,` <- analog channel

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing. \
  So typed out in 30\_Switches.ino:

`rotaryAnalogMute(2, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}

#### rotaryAnalogPartial()

{% tabs %}
{% tab title="Description" %}
12 - position switch. Absolute.&#x20;

Mix between rotaryAnalogSimle() and rotaryAnalogMute(). You can select a range of positions which will be muted. The remaining positions will produce a button press. The position of the switch is still detected in the muted positions and can be used for [conditional coding](../../3.-coding/advanced/conditional-coding/) or [rotaryInject](../../3.-coding/advanced/analog-inject.md#rotaryinject).&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalogPartial(int analogChannel, int muteStart, int muteEnd, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalogPartial(`

`2,` <- analog channel

`5,` <- The first position in the muted range

`9,` <- The last position in the muted range

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* The starting number of the 12-positios is determined by the number set in the block for `analogButtonNumber[]`. In the example above, positions 5, 6, 7, 8 and 9 are muted. The button numbers used will not automatically compress, there will be unused button numbers in the middle of the switch range.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing. \
  So typed out in 30\_Switches.ino:

`rotaryAnalogPartial(2, 5, 9, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* 12 button numbers
{% endtab %}
{% endtabs %}

#### rotaryAnalog2Mode()

{% tabs %}
{% tab title="Description" %}
Setup with 2 switch modes.

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalog2Mode(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalog2Mode(`

`2,` <- analog channel

`1,` <- placement in rotary field

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`rotaryAnalog2Mode(2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">rotaryAnalogBite()</mark>

{% tabs %}
{% tab title="Description" %}
Setup with 2 switch modes. Identical to rotaryAnalog2Mode(), but with the option to set the bitepoint together with a biteButton().&#x20;

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalog2Mode(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalog2Mode(`

`2,` <- analog channel

`1,` <- placement in rotary field

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`rotaryAnalog2Mode(2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* biteButton() to set the bite point
{% endtab %}
{% endtabs %}
