# LED control

These functions control [LED brightness.](../3.-coding/leds-code-and-connection/firmware-control/brightness.md)

#### rotary2Brightness()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the rotary2bit [category](encoders/#rotary2bit). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the LED brightness level up and down by increments of 2.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2Brightness(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`rotary2Brightness(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### funkyBrightness()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the funkyRotary [category](encoders/#funkyrotary). Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the LED brightness level up and down by increments of 2.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyBrightness(int Arow, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyBrightness(2, 3, 4, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}

#### PEC11Brightness()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder in the PEC11 [category.](encoders/#pec11) Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Holding the modButton will make this encoder adjust the LED brightness level up and down by increments of 2.&#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Brightness(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11Brightness(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton()
{% endtab %}
{% endtabs %}



