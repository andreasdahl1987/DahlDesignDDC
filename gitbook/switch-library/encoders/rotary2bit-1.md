# rotary3Bit

Encoder functions in the rotary3Bit category. Information on this category [here.](./#rotary3bit)

#### rotary3Inc()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.
{% endtab %}

{% tab title="Example" %}
`void rotary3Inc(int row, int column, bool reverse)`

For an encoder with pins 1, 2 and 3 to columns 3, 4 and 5. Common pin to row 2:

`rotary3Inc(2, 3, false);`

The button numbers used is determined by the number written in the block for the 1 pin. 2 pin and 3 pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}

