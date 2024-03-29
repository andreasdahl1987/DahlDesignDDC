# PEC11

Encoder functions in the PEC11 category. Information on this category [here.](./#pec11)

#### PEC11()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.
{% endtab %}

{% tab title="Example" %}
`void PEC11(int row, int col, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">PEC11Bite()</mark>

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the bite point of your clutches. Works in combination with [biteButton().](../function-button.md#bitebutton) The button presses will not trigger when setting bite point.&#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Bite(int row, int col, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11Bite(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* biteButton() to set bite point
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">PEC11BiteAdjust()</mark>

{% tabs %}
{% tab title="Description" %}
Similar to rotary2Bite above, but instead of changing bitePoint by going through the bite point setting sequence, it will directly increase (CW rotation) or decrease (CCW rotation) the bitepoint by a set amount while biteButton is held.
{% endtab %}

{% tab title="Example" %}
`void PEC11BiteAdjust(int row, int column, bool reverse, int increment)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11BiteAdjust(2, 3, false, 50);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the biteButton() is held, this encoder will increase/decrease the bite point by 5.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* biteButton() to set bite point
{% endtab %}
{% endtabs %}

#### PEC11Throttle()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the throttle hold value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting throttle hold value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Throttle(int row, int column, bool rev)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11Throttle(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the throttle hold value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### PEC11Brake()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the brake magic value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting brake magic value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Brake(int row, int column, bool rev)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11Brake(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the brake magic value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}
