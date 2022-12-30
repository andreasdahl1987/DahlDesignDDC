# rotaryAnalog

All rotaryAnalog functions are for 12-position switches. The most common are 8, 10, 12 and 16 positions - with 12 being the most common. These functions can be[ edited](editing-functions.md) without too much hassle to match smaller and larger numbers of positions.&#x20;

#### rotaryAnalog()

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

