# rotary4Bit

Encoder functions in the rotary4Bit category. Information on this category [here.](./#rotary4bit)

#### rotary4Inc()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.
{% endtab %}

{% tab title="Example" %}
`void rotary4Inc(int row, int column, bool reverse)`

For an encoder on row 1, columns 2-5:`rotary4Inc(1, 2, false);`

The button numbers used is determined by the number written in the block for the 1st pin. 2nd to 4th pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}

#### rotary4Modes()

{% tabs %}
{% tab title="Description" %}
Setup with several switch modes, including a [hybrid switch.](../multiswitch-complexes.md#hybrid) You can set the amount of positions of the hybrid switch to any number.&#x20;

Modes:

* 0: 16 - position switch (absolute)
* 1: Incremental (similar to `rotary4Inc()`)
* 2: Open hybrid, X positions
* 3: Closed hybrid

Uses the rotary field for [field placement.](../../4.-advanced-features/field-placement.md) Since is has 4 modes it uses 2 slots in the field.
{% endtab %}

{% tab title="Example" %}
`void rotary4Modes(int row, int column, int fieldPlacement, int hybridPositions, bool reverse)`

For a encoder on row 1 column 2-5 -> `rotary4Modes(1,2,2,13,true);`

* Field placement to 2. Uses two slots in the bit field (2 and 3). So \[DahlDesign.DDCR2] and \[DahlDesign.DDCR3] and will show the modes.
* Hybrid switch has 13 positions. The starting number of the 16-position mode and hybrid switch is determined by the number set in the block for encoder 1st pin. The number for incremental mode is determined by the number set in the block for encoder 2nd pin. So "10" in 1st pin block will give numbers 10-25 for the 16-position switch, and numbers 10-22 for the hybrid switch. "26" in 2nd pin block will give numbers 26 and 27 for incremental mode.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* hybridButton() to lock position and use rotary as incremental switch.
* X button numbers, minimum 16, determined by the highest amount of switch positions in any mode.
* Two slots in the rotary field.&#x20;
{% endtab %}
{% endtabs %}

#### rotary4Multi()

{% tabs %}
{% tab title="Description" %}
A counting multiposition switch. You can set the amount of positions to any number. The physical position of the switch will not be in sync with button number.
{% endtab %}

{% tab title="Example" %}
`void rotary2Multi(int row, int column, int positions, bool reverse)`

For a encoder on row 2 column 2-5 -> `rotary4Multi(2,2,9,false);`

* This will make a 9-position switch. Starting number is the number set in the block for encoder 1st pin.
* &#x20;The `reverse` refers to increasing/decreasing button number on CW/CCW rotation, can be flipped by setting to `true.`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* X button numbers.


{% endtab %}
{% endtabs %}

#### rotary4Multis()

{% tabs %}
{% tab title="Description" %}
Switch with several multiposition modes, including a 16-position switch and 3 instances of rotary4Multi().&#x20;

Modes:

* 0: 16-position switch. Absolute.
* 1: Counting multiposition switch, any amount of positions.
* 2: Counting multiposition switch, any amount of positions.
* 3: Counting multiposition switch, any amount of positions.

Uses the rotary field for [field placement.](../../4.-advanced-features/field-placement.md) Since is has 4 modes it uses 2 slots in the field.
{% endtab %}

{% tab title="Example" %}
`void rotary4Multis(int row, int column, int fieldPlacement, int positions1, int positions2, int positions3, bool reverse)`

For a encoder on row 2 column 2-5 -> `rotary4Multis(2,2,2,8,12,18,true);`&#x20;

* Mode 1 -> 8 position switch
* Mode 2 -> 12 position switch
* Mode 3 -> 18 position switch
* The starting number is determined by the number set in the block for encoder 1st pin.&#x20;
* Field placement to 2. Uses two slots in the bit field (2 and 3). So \[DahlDesign.DDCR2] and \[DahlDesign.DDCR3] and will show the modes.
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the left side. Turning it CCW will now increase the count instead of reducing.
{% endtab %}

{% tab title="Requirements" %}
* X button numbers, minumum 16. Determined by the highest number of positions used.
* modButton() to change switch modes.
* Two slots in the rotary field.
{% endtab %}
{% endtabs %}
