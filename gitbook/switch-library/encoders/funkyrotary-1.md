# wildEncoder

Encoder functions in the wildEncoder category. Information on this category [here](./#wildencoder).

These encoders are sensitive to swapping A and B pins, which none of  the other encoders are. While other encoders just gets their button numbers swapped on swapping A and B pin, these encoders will work perfectly in one orientation and be a complete mess if the pins are swapped. To make it easier to use these functions, they have a software pin swap included. So you can simply swap pins in the functions instead of taking your controller appart. Try both configurations.&#x20;

#### wildInc()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.
{% endtab %}

{% tab title="Example" %}
`void wildInc(int row, int col, bool pinSwitch, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyRotary(2, 3, 4, false);`

The "reverse" input is to flip what happens on CW and CCW rotation. Here set to `false`. Set to `true` to flip.&#x20;

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}
