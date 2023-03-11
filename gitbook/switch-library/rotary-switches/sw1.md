# SW1

The SW1 steering wheel has some special features for its 12-position switches. These functions could be useful for other projects as well, which is why they're included in DDC.&#x20;

<figure><img src="../../.gitbook/assets/image (4) (4).png" alt=""><figcaption><p>The two 12-position switches on SW1 has several features.</p></figcaption></figure>

#### <mark style="background-color:orange;">SW1BiteRotary()</mark>

{% tabs %}
{% tab title="Description" %}
A switch with 2 modes. Also included in the [quickSwitch ](../car-control-functions/quickswitch.md)system. When in 12 - position mode this switchs' position will be overridden by quickSwitch().&#x20;

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.

In addition, this switch can set the bite point of your clutches. Works in combination with [biteButton().](../function-button.md#bitebutton) The button presses will not trigger when setting bite point.&#x20;

This switch uses the same general approach as other switches setting bite point, moving through the 10, 1 and 0.1 increments. However, instead of increasing/decreasing on rotation, the actual position of the switch will determine what the bite point is set to. So if we're in the first step of bite point setting and in position 4, we're setting bite point to 40. In the next step, if switch is in position 8, we're at bite point 48, etc. This way, using the absolute nature of the 12-position switch, we can set a bite point with 0.1% accuracy without any visual feedback other than the switchs' position.
{% endtab %}

{% tab title="Example" %}
`SW1BiteRotary(int analogPin, int switchNumber, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`SW1BiteRotary(`

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

`SW1BiteRotary(A3, 2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* quickSwitch() to override position.
* biteButton() to set bite point.
{% endtab %}
{% endtabs %}

#### SW1PresetRotary()

{% tabs %}
{% tab title="Description" %}
A switch with 2 modes. Also included in the [quickSwitch ](../car-control-functions/quickswitch.md)system. When in 12 - position mode this switchs' position will be overridden by quickSwitch().&#x20;

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 2 modes it uses 1 slot in the field.

In addition, the switch can be used to change presets. When holding a [presetButton()](../function-button.md#presetbutton), the position of the switch will determine which preset you're selecting.&#x20;

When powering up the controller, it will start in the preset corresponding to the position of this switch.
{% endtab %}

{% tab title="Example" %}
`SW1PresetRotary(int analogPin, int switchNumber, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)`

Switch setup with explainations:

`SW1BiteRotary(`

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

`SW1PresetRotary(A3, 2, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
* One slot in the rotary field.&#x20;
* quickSwitch() to override position.
* presetButton() to be able to change presets


{% endtab %}
{% endtabs %}
