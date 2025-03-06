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

#### <mark style="background-color:orange;">rotary2Bite()</mark>

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

#### <mark style="background-color:orange;">rotary2BiteAdjust()</mark>

{% tabs %}
{% tab title="Description" %}
Similar to rotary2Bite above, but instead of changing bitePoint by going through the bite point setting sequence, it will directly increase (CW rotation) or decrease (CCW rotation) the bitepoint by a set amount while biteButton is held.
{% endtab %}

{% tab title="Example" %}
`void rotary2BiteAdjust(int row, int column, bool reverse, int increment)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotary2BiteAdjust(2, 3, false, 50);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the biteButton() is held, this encoder will increase/decrease the bite point by 5.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* biteButton() to set bite point
{% endtab %}
{% endtabs %}

#### rotary2Throttle()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the throttle hold value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting throttle hold value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2Throttle(int row, int column, bool rev)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotary2Throttle(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the throttle hold value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### rotary2Brake()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the brake magic value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting brake magic value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2Brake(int row, int column, bool rev)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotary2Brake(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the brake magic value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### <mark style="background-color:blue;">rotary2Modes()</mark>

{% tabs %}
{% tab title="Description" %}
Setup with several switch modes, including a [hybrid switch.](../multiswitch-complexes/#hybrid) You can set the amount of positions of the hybrid switch to any number.&#x20;

Modes:

* 0: 4-position switch
* 1: Incremental (similar to `rotary2Inc()`)
* 2: Open hybrid, X positions
* 3: Closed hybrid

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 4 modes it uses 2 slots in the field.
{% endtab %}

{% tab title="Example" %}
`void rotary2Modes(int row, int column, int fieldPlacement, int hybridPositions, bool reverse)`

For a encoder on row 2 column 4+5 -> `rotary2Modes(2,4,2,18,true);`

* Field placement to 2. Uses two slots in the bit field (2 and 3). So \[DahlDesign.DDCR2] and \[DahlDesign.DDCR3] and will show the modes.
* Hybrid switch has 18 positions. The starting number of the hybrid switch is determined by the number set in the block for encoder pin A. The number for incremental mode is determined by the number set in the block for encoder pin B. So "10" in pin A block will give numbers 10-27 for the hybrid switch. "28" in pin B block will give numbers 28 and 29 for incremental mode.&#x20;
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* hybridButton() to lock position and use rotary as incremental switch.
* X button numbers, minimum 4, determined by the hybrid switch positions.
* Two slots in the rotary field.&#x20;
{% endtab %}
{% endtabs %}

#### rotary2Multi()

{% tabs %}
{% tab title="Description" %}
A counting multiposition switch. You can set the amount of positions to any number. The physical position of the switch will not be in sync with button number.
{% endtab %}

{% tab title="Example" %}
`void rotary2Multi(int row, int column, int positions, bool reverse)`

For a encoder on row 2 column 4+5 -> `rotary2Multi(2,4,9,false);`

* This will make a 9-position switch. Starting number is the number set in the block for encoder A pin.
* &#x20;The `reverse` refers to increasing/decreasing button number on CW/CCW rotation, can be flipped by setting to `true.`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* X button numbers.


{% endtab %}
{% endtabs %}

#### rotary2Multis()

{% tabs %}
{% tab title="Description" %}
Switch with several multiposition modes, including a 4-position switch and 3 instances of rotary2Multi().&#x20;

Modes:

* 0: 4-position switch. Absolute, but the 4 positions are repeated several times during a full 360 degree rotation of the switch.
* 1: Counting multiposition switch, any amount of positions.
* 2: Counting multiposition switch, any amount of positions.
* 3: Counting multiposition switch, any amount of positions.

Uses the rotary field for [field placement.](../../3.-coding/advanced/field-placement.md) Since is has 4 modes it uses 2 slots in the field.
{% endtab %}

{% tab title="Example" %}
`void rotary2Multis(int row, int column, int fieldPlacement, int positions1, int positions2, int positions3, bool reverse)`

For a encoder on row 2 column 4+5 -> `rotary2Multis(2,4,2,8,12,18,true);`&#x20;

* Mode 1 -> 8 position switch
* Mode 2 -> 12 position switch
* Mode 3 -> 18 position switch
* The starting number is determined by the number set in the block for encoder pin A.&#x20;
* Field placement to 2. Uses two slots in the bit field (2 and 3). So \[DahlDesign.DDCR2] and \[DahlDesign.DDCR3] and will show the modes.
* This switch has "reverse" set to true, which can be a good idea if it is placed horizontally on the right side. Turning it CCW will now increase the count instead of reducing.
{% endtab %}

{% tab title="Requirements" %}
* X button numbers, minumum 4. Determined by the highest number of positions used.
* modButton() to change switch modes.
* Two slots in the rotary field.
{% endtab %}
{% endtabs %}

