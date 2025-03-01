# Preset

Have a look at [this page](../3.-coding/advanced/presets/) for info on the preset system.&#x20;

There are fuctions that can be used to change preset. Not included here is [SW1PresetRotary](rotary-switches/sw1.md#sw1presetrotary)(), which has a seperate page.&#x20;

#### preset2Bit()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Added function is the ability to change presets. If holding the [modButton()](function-button.md#modbutton), rotating this switch will more to a higher/lower preset.&#x20;
{% endtab %}

{% tab title="Example" %}
`void preset2Bit(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`preset2Bit(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton() to be able to change presets
{% endtab %}
{% endtabs %}

#### E18Preset()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Added function is the ability to change presets. If holding the [modButton()](function-button.md#modbutton), rotating this switch will more to a higher/lower preset.&#x20;
{% endtab %}

{% tab title="Example" %}
`void E18Preset(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`E18Preset(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton() to be able to change presets
{% endtab %}
{% endtabs %}

#### PEC11Preset()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Added function is the ability to change presets. If holding the [modButton()](function-button.md#modbutton), rotating this switch will more to a higher/lower preset.&#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Preset(int row, int column, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`PEC11Preset(2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton() to be able to change presets
{% endtab %}
{% endtabs %}

#### funkyPreset()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher.

Added function is the ability to change presets. If holding the [modButton()](function-button.md#modbutton), rotating this switch will more to a higher/lower preset.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyPreset(int row, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyPreset(2, 3, 4, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16. The `reverse` part of the function will switch the button numbers if set to `true`.
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* modButton() to be able to change presets
{% endtab %}
{% endtabs %}

#### presetNext()

{% tabs %}
{% tab title="Description" %}
A simple, momentary push button that goes to next preset when hit. Does not produce a button number press.&#x20;
{% endtab %}

{% tab title="Example" %}
`void presetNext(int row, int col)`

For a switch on row 3 column 5 -> `presetNext(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}

#### presetPrevious()

{% tabs %}
{% tab title="Description" %}
A simple, momentary push button that goes to prevous preset when hit. Does not produce a button number press.&#x20;
{% endtab %}

{% tab title="Example" %}
`void presetPrevious(int row, int col)`

For a switch on row 3 column 5 -> `presetPrevious(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}
