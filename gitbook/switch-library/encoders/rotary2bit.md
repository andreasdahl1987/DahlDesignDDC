# rotary2Bit

Encoder functions in the rotary2Bit category. Information on this category [here.](./#rotary2bit)

#### rotary2Inc()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.
{% endtab %}

{% tab title="Example" %}
`void rotary2Inc(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotary2Inc(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}

#### rotary2Bite()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the bite point of your clutches. Works in combination with [biteButton().](../function-button.md#bitebutton) The button presses will not trigger when setting bite point.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2Bite(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotary2Bite(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* biteButton() to set bite point
{% endtab %}
{% endtabs %}

#### rotary2Modes()

{% tabs %}
{% tab title="Description" %}
Setup with several switch modes, including a [hybrid switch.](../multiswitch-complexes.md#hybrid) You can set the amount of positions of the hybrid switch to any number.&#x20;

Modes:

* 0: 4-position switch
* 1: Incremental (similar to `rotary2Inc()`)
* 2: Open hybrid, X positions
* 3: Closed hybrid

Uses the rotary field for [field placement.](../../4.-advanced-features/field-placement.md) Since is has 4 modes it uses 2 slots in the field.
{% endtab %}

{% tab title="Example" %}
`void rotary2Modes(int row, int column, int fieldPlacement, int hybridPositions, bool reverse)`

For a encoder on row 2 column 4+5 -> `rotary2Modes(2,4,2,18,true);`

* Field placement to 2. Uses two slots in the bit field (2 and 3). So \[DahlDesign.DDCR2] and \[DahlDesign.DDCR3] and will show the modes.
* Hybrid switch has 18 positions. The starting number of the hybrid switch is determined by the number set in the block for encoder pin A. The number for incremental mode is determined by the number set in the block for encoder pin B. So "10" in pin A block will give numbers 10-27 for the hybrid switch. "28" in pin B block will give numbers 28 and 29 for incremental mode.&#x20;
* This switch has "reverese" set to true, which can be a good idea if it is placed horizontally on the left side. Turning it CCW will now increase the count instead of reducing.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* hybridButton() to lock position and use rotary as incremental switch.
* X button numbers, minimum 4, determined my the hybrid switch positions.
* Two slots in the rotary field.&#x20;
{% endtab %}
{% endtabs %}

#### D
