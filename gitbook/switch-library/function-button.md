# Function switches

#### modButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton, should be assigned a button number. When held, it will change the mode of switches that are pressed/rotated.

It can also deactivate all [analog injects](../3.-coding/advanced/analog-inject.md) for 20 seconds by hitting the button 3 times quickly. This is to make button mapping/calibration less of a hassle with analog injects.&#x20;
{% endtab %}

{% tab title="Example" %}
`void modButton(int row, int col)`

For a switch on row 2 column 4 -> `modButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### <mark style="background-color:blue;">hybridButton()</mark>

{% tabs %}
{% tab title="Description" %}
Any switch function that uses a hybrid button will be <mark style="background-color:blue;">highlighted blue.</mark>

A switch dedicated to opening/closing switches with hybrid features, such as DDS functions, rotaryAnalog(), rotary2Modes(), and a few more.

Does not have a button number.

Funky switches have their own hybridButton function.
{% endtab %}

{% tab title="Example" %}
`void hybridButton(int row, int col)`

For a switch on row 2 column 4 -> `hybridButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
None
{% endtab %}
{% endtabs %}

#### DDButton()

{% tabs %}
{% tab title="Description" %}
A switch dedicated to swapping between the two "layers" of 12 positions if a DDS switch.

Does not have a button number.

Funky switches have their own DDButton function.
{% endtab %}

{% tab title="Example" %}
`void DDButton(int row, int col)`

For a switch on row 2 column 4 -> `DDButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
None
{% endtab %}
{% endtabs %}

#### presetButton()

{% tabs %}
{% tab title="Description" %}
A switch dedicated to enabling preset switching with a SW1PresetRotary() switch. Will need a button number assigned, as it works as a normal button. Presets can be changed when this button is held.&#x20;

The preset2Bit() function does NOT need a presetButton() to work.
{% endtab %}

{% tab title="Example" %}
`void presetButton(int row, int col)`

For a switch on row 2 column 4 -> `presetButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}
