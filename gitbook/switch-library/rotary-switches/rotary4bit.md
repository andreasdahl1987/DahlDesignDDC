# rotarySwitch4Bit

Functions for rotary switches using a [diode maze.](./#id-2.-diode-maze)&#x20;

#### rotarySwitch4Bit()

{% tabs %}
{% tab title="Description" %}
Setup with 2 switch modes. This is the equivalent of rotaryAnalog2Mode()

Modes:

* 0: 12 - position switch. Absolute.
* 1: Incremental

Hold a modButton() and turn the rotary to switch modes.&#x20;

The button numbers for mode 0 is set in the first (leftmost) slot in the switch table. The button numbers for mode 1 is set in the second slot in the switch table.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotarySwitch4Bit(int row, int column, bool reverse)`

Switch setup with explainations:

`rotarySwitch4Bit(3,2,false);`

Switch is set up on row 3, column 2 - 5. (Only the starting column pin is required, DDC will assume the other 3 pins are on row 3 columns 3, 4 and 5). `Reverse` is set to `false`. If you want the switch to count the opposite way, set it to `true`.&#x20;


{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* Minimum 12 button numbers.
{% endtab %}
{% endtabs %}

