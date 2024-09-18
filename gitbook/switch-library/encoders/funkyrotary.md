# funkyRotary

Encoder functions in the funkyRotary category. Information on this category [here.](./#funkyrotary)

In contrast to the other encoder functions, the funkyRotary category requires you to type in the column numbers for both A and B pin columns. This means you can place them on any column number on the same row.&#x20;

#### funkyRotary()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.
{% endtab %}

{% tab title="Example" %}
`void funkyRotary(int Arow, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyRotary(2, 3, 4, false);`

The "reverse" input is to flip what happens on CW and CCW rotation. Here set to `false`. Set to `true` to flip.&#x20;

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">funkyBite()</mark>

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the bite point of your clutches. Works in combination with [biteButton().](../function-button.md#bitebutton) The button presses will not trigger when setting bite point.
{% endtab %}

{% tab title="Example" %}
`void funkyBite(int row, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyBite(2, 3, 4, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* biteButton() to set bite point
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">funkyBiteAdjust()</mark>

{% tabs %}
{% tab title="Description" %}
Similar to rotary2Bite above, but instead of changing bitePoint by going through the bite point setting sequence, it will directly increase (CW rotation) or decrease (CCW rotation) the bitepoint by a set amount while biteButton is held.
{% endtab %}

{% tab title="Example" %}
`void funkyBiteAdjust(int row, int Acol, int Bcol, bool reverse, int increment)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyBiteAdjust(2, 3, 4, false, 50);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the biteButton() is held, this encoder will increase/decrease the bite point by 5.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* biteButton() to set bite point
{% endtab %}
{% endtabs %}

#### funkyThrottle()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the throttle hold value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting throttle hold value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyThrottle(int row, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyThrottle(2, 3, 4, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the throttle hold value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### funkyBrake()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

In addition, this switch can set the brake magic value when the [modButton()](../function-button.md#modbutton) is held.. The button presses will not trigger when setting brake magic value. Adjustments will be with 1% increments. &#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyBrake(int row, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyBrake(2, 3, 4, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers and increase/decrease bite point if set to `true`.

When the modButton() is held, this encoder will increase/decrease the brake magic value by 1.0%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}
