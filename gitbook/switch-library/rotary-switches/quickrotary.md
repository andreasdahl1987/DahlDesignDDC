# quickRotary

The quickRotary functions are part of the QuickSwitch system explained [here.](../car-control-functions/quickswitch.md)

#### <mark style="background-color:orange;">quickRotary1Bite()</mark>

{% tabs %}
{% tab title="Description" %}
A switch with 2 modes. In 12 - position mode this switchs' position will be overridden by quickSwitch() and quickSwitch12().&#x20;

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.

In addition, this switch can set the bite point of your clutches. Works in combination with [biteButton().](../function-button.md#bitebutton) The button presses will not trigger when setting bite point.&#x20;
{% endtab %}

{% tab title="Example" %}
`void quickRotary1Bite(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`quickRotary1Bite(`

`2,` <- analog channel

`1,` <- placement in rotary field

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`quickRotary1Bite(2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* quickSwitch() or quickSwitch12() button to override position.
* biteButton() to set bite point.
{% endtab %}
{% endtabs %}

#### quickRotary2()

{% tabs %}
{% tab title="Description" %}
A switch with 2 modes. In 12 - position mode this switchs' position will be overridden by quickSwitch() and quickSwitch12().&#x20;

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.
{% endtab %}

{% tab title="Example" %}
`void quickRotary2(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`quickRotary2(`

`2,` <- analog channel

`1,` <- placement in rotary field

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`quickRotary2(2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* quickSwitch() or quickSwitch12() button to override position.
{% endtab %}
{% endtabs %}

#### quickRotary3()

{% tabs %}
{% tab title="Description" %}
A switch with 2 modes. In 12 - position mode this switchs' position will be overridden by quickSwitch() and quickSwitch34().&#x20;

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.
{% endtab %}

{% tab title="Example" %}
`void quickRotary3(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`quickRotary3(`

`2,` <- analog channel

`1,` <- placement in rotary field

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`quickRotary33(2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* quickSwitch() or quickSwitch34() button to override position.
{% endtab %}
{% endtabs %}

#### quickRotary4()

{% tabs %}
{% tab title="Description" %}
A switch with 2 modes. In 12 - position mode this switchs' position will be overridden by quickSwitch() and quickSwitch34().&#x20;

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.
{% endtab %}

{% tab title="Example" %}
`void quickRotary4(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`quickRotary4(`

`2,` <- analog channel

`1,` <- placement in rotary field

`16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,` <- Switch position values

`false);` <- Direction is not reversed, so CW rotation increasese button number.

* Field placement to 1 in the rotary field, so \[DahlDesign.DDCR1] will show the modes.
* The starting number of the 12-position mode is determined by the number set in the block for `analogButtonNumber[]`. The number for incremental mode is determined by the number set in the block for `analogButtonNumberIncMode[]`.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;

\
So typed out in 30\_Switches.ino:

`quickRotary4(2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* quickSwitch() or quickSwitch34() button to override position.
{% endtab %}
{% endtabs %}
