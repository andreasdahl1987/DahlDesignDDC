# Modded encoder

<figure><img src="../../.gitbook/assets/image (65).png" alt=""><figcaption></figcaption></figure>

"Modded" encoders are standard incremental encoders with two extra button numbers available by holding the [modButton](../function-button.md#modbutton). Lets say your encoders produces button numbers 14 and 15 on CW and CCW rotation. Holding the modButton will change the numbers to 16 and 17.&#x20;

This is just free extra buttons, which could be useful for settings/adjustments that you don't do that often. You could have a rotary with brake balance adjustment, and ABS adjustment when holding modButton. Or a rotary to control your dash pages, and change dash template on holding modButton.&#x20;

If you have a backlit encoder, you could use the [triggerLED()](../../3.-coding/peripherals/leds-code-and-connection/firmware-control/led-functions.md#triggerled) function to change colors when holding modbutton:

```
triggerLED(9,12,!modButtonPressed(),0xFF0000,25,true,false);
triggerLED(9,12,modButtonPressed(),0x00FF00,25,true,false);
```

The first line will color the LEDs 9 to 12 red (0xFF0000) if modButton is not pressed. The second line will color LEDs 9 to 12 green (0x00FF00) if modButton is pressed. Brightness is set to 25% on both, clearing LEDs is set to `TRUE` and blinking is set to `FALSE`.&#x20;

#### rotary2Mod()

{% tabs %}
{% tab title="Description" %}
Modded encoder in the rotary2bit [category](../encoders/#rotary2bit).&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2Mod(int row, int column, bool reverse)`

Lets say our encoder is on row 3, columns 2+3,

`rotary2Mod(3,2,false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 when modButton is NOT pressed, and then 17+18 if the modButton is pressed. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 4  button numbers
* modButton
{% endtab %}
{% endtabs %}

#### rotary4Mod()

{% tabs %}
{% tab title="Description" %}
Modded encoder in the rotary4bit[ category](../encoders/#rotary4bit).&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary4Mod(int row, int column, bool reverse)`

Lets say our encoder is on row 3, columns 2+3,

`rotary4Mod(3,2,false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 when modButton is NOT pressed, and then 17+18 if the modButton is pressed. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 4  button numbers
* modButton
{% endtab %}
{% endtabs %}

#### PEC11Mod()

{% tabs %}
{% tab title="Description" %}
Modded encoder in the PEC11 [category](../encoders/#pec11).&#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Mod(int row, int column, bool reverse)`

Lets say our encoder is on row 3, columns 2+3,

`PEC11Mod(3,2,false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 when modButton is NOT pressed, and then 17+18 if the modButton is pressed. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 4  button numbers
* modButton
{% endtab %}
{% endtabs %}

#### funkyRotaryMod()

{% tabs %}
{% tab title="Description" %}
Modded encoder in the funkyRotary [category](../encoders/#funkyrotary). This is for using a regular pushbutton to change layer, not the funky pushbutton.
{% endtab %}

{% tab title="Example" %}
`void funkyRotaryMod(int row, int aCol, int bCol, bool reverse)`

Lets say our encoder is on row 3, columns 2+3,

`funkyRotaryMod(3,2,3,false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 when modButton is NOT pressed, and then 17+18 if the modButton is pressed. The `reverse` part of the function will switch the button numbers if set to `true`.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 4  button numbers
* modButton
{% endtab %}
{% endtabs %}
