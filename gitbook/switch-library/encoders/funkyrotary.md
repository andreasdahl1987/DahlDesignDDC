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
