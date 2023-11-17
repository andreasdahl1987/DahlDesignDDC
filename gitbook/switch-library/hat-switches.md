# Hat switches

These functions are designed to set up a switch with directional inputs as a hat switch. Windows will recognize this as a switch with directional inputs, as opposed to just buttons with numbers.&#x20;

Typical switches are the Alps RKJX - family.&#x20;

Remember stating the amount of hat switches in[ 8\_Joystick](../3.-coding/essentials/08\_joystick.md), or else your hat switch wont be recognized at all.&#x20;

#### funkyHat()

{% tabs %}
{% tab title="Description" %}
Sets up a hat switch. Does not need button numbers.
{% endtab %}

{% tab title="Example" %}
`void funkyHat(int8_t row, int8_t colUp, int8_t colRight, int8_t colDown, int8_t colLeft, int8_t hatNumber)`

Fill in the row all the funky pins go to and then up/right/down/left, in that order. Lastly the hat switch #. If you have two hat-switches, one will have to be #1, and one #2.&#x20;

`funkyHat(2,1,3,4,2,1);`


{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}

