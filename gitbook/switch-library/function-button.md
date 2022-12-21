# Function button

#### modButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton, should be assigned a button number. When held, it will change the mode of switches that are pressed/rotated.
{% endtab %}

{% tab title="Example" %}
`void modButton(int row, int col)`

For a switch on row 2 column 4 -> `modButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### biteButton()

{% tabs %}
{% tab title="Description" %}
Normally works as a simple pushbutton. In addition, when held, the controller is primed to enter bite point setting. Hold + rotate a bite point compatible rotary (a roatry using a function that includes bite point setting) to enter bite point setting mode. At this point, you can release the bite button. Further presses of the button will go through the stages of setting the bite point (mode 1-3), before in the end going out of bite point setting (back to mode 0).&#x20;

SimHub property -> \[DahlDesign.DDCbiteSetting]

Defaults to bit 11 and 12 in the rotary field, you dont have to assign a field placement.&#x20;

**Modes:**

* 0: Bite point setting inactive
* 1: Bite point setting active. Adjust with steps of +/- 10
* 2: Bite point setting active. Adjust with steps of +/- 1
* 3: Bite point setting active. Adjust with steps of +/- 0.1

As stated above, this button's modes are not changed by using a modButton(), but by the biteButton() itself.&#x20;
{% endtab %}

{% tab title="Example" %}
`void biteButton(int row, int col)`

For a switch on row 2 column 4 -> `biteButton(2,4);`


{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### neutralButton()

{% tabs %}
{% tab title="Description" %}
Pushbutton with two modes:

* 0: Toggle on/off NEUTRAL, which sets the clutch to 100%. Info on this switch state is available as properties in SimHub. In addition, the property DahlDesign.SmoothGear will show “N” when this is active. 1: Regular momentary pushbutton.
* 1: Momentary pushbutton

SimHub property -> \[DahlDesign.NeutralActive]

SimHub property -> \[DahlDesign.NeutralMode]

Defaults to bit 5 and bit 15 in button field, you dont have to assign a field placement.

\[DahlDesign.SmoothGear] will show "N" when neutral is active.&#x20;
{% endtab %}

{% tab title="Example" %}
`void neutralButton(int row, int col)`

For a switch on row 2 column 4 -> `neutralButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to swap modes.
* 1 button number
{% endtab %}
{% endtabs %}

#### hybridButton()

{% tabs %}
{% tab title="Description" %}
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

__
