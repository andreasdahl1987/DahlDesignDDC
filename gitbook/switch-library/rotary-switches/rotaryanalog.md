# rotaryAnalog

All rotaryAnalog functions are for 12-position switches. The most common are 8, 10, 12 and 16 positions - with 12 being the most common. These functions can be[ edited](editing-functions.md) without too much hassle to match smaller and larger numbers of positions.&#x20;

#### <mark style="background-color:blue;">rotaryAnalog()</mark>

{% tabs %}
{% tab title="Description" %}
Setup with several switch modes, including a [hybrid switch.](../multiswitch-complexes.md#hybrid) You can set the amount of positions of the hybrid switch to any number.&#x20;

Modes:

* 0: 12-position switch. Absolute.
* 1: Incremental
* 2: Open hybrid, X positions
* 3: Closed hybrid

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 4 modes it uses 2 slots in the field.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalog(int analogPin, int switchNumber, int fieldPlacement, int hybridPositions, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalog(`

`A3,` <- The analog pin this switch is connected to

`2,` <- The switch number this analog switch is assigned

`1,` <- placement in rotary field

`7,` <- Switch positions in hybrid mode

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1. Uses two slots in the bit field (1 and 2). So \[DahlDesign.DDCR1] and \[DahlDesign.DDCR2] and will show the modes.
* Hybrid switch has 7 positions. The starting number of the hybrid switch and 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`rotaryAnalog(A3, 2, 1, 7, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
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
`void rotaryAnalogSimple(int analogPin, int switchNumber, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalog2Mode(`

`A3,` <- The analog pin this switch is connected to

`2,` <- The switch number this analog switch is assigned

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`rotaryAnalogSimple(A3, 2, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* 12 button numbers
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">rotaryAnalog2Mode()</mark>

{% tabs %}
{% tab title="Description" %}
Setup with 2 switch modes.

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.
{% endtab %}

{% tab title="Example" %}
`void rotaryAnalog2Mode(int analogPin, int switchNumber, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`rotaryAnalog2Mode(`

`A3,` <- The analog pin this switch is connected to

`2,` <- The switch number this analog switch is assigned

`1,` <- placement in rotary field

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`rotaryAnalog2Mode(A3, 2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* biteButton() to set the bite point
{% endtab %}
{% endtabs %}

