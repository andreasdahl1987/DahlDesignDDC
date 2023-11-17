# E18

Encoder functions in the elma category. Information on this category [here](./#elma).

Switches that work with funkyRotary functions will likely also work with elma functions, but not necessarily the other way around. I'd suggest always trying funkyRotary before elma, since the elma algorithm is much heavier to run - reserved for very bouncy encoders.&#x20;

#### E18Inc()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.
{% endtab %}

{% tab title="Example" %}
`void elmaInc(int row, int col, , bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`elmaInc(2, 3, false);`

The "reverse" input is to flip what happens on CW and CCW rotation. Here set to `false`. Set to `true` to flip.&#x20;

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">E18BiteAdjust()</mark>

{% tabs %}
{% tab title="Description" %}
Similar to rotary2Bite above, but instead of changing bitePoint by going through the bite point setting sequence, it will directly increase (CW rotation) or decrease (CCW rotation) the bitepoint by a set amount while biteButton is held.
{% endtab %}

{% tab title="Example" %}
`void E18BiteAdjust(int row, int column, bool reverse, int increment)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`E18BiteAdjust(2, 3, false, 50);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the biteButton() is held, this encoder will increase/decrease the bite point by 5.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* biteButton() to set bite point
{% endtab %}
{% endtabs %}

#### E18Throttle()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the throttle hold value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting throttle hold value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void E18Throttle(int row, int column, bool rev)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`E18Throttle(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the throttle hold value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### E18Brake()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the brake magic value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting the brake magic value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void E18Brake(int row, int column, bool rev)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`E18Brake(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the brake magic value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

