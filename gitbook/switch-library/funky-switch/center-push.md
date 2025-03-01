# Center push

#### funkyPush()

{% tabs %}
{% tab title="Description" %}
A simple, momentary pushbutton. The button numer is the one you set in your matrix setup.
{% endtab %}

{% tab title="Example" %}
`void funkyPush(int row, int column, int aCol, int bCol, int cCol, int dCol)`

Fill in the row all the funky pins go to, the column for the center push button and then the columns for all the directional buttons.&#x20;

`funkyPush(2,1,5,2,3,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### funkyPushL()

{% tabs %}
{% tab title="Description" %}
A simple, latching pushbutton. The button numer is the one you set in your matrix setup.
{% endtab %}

{% tab title="Example" %}
`void funkyPushL(int row, int column, int aCol, int bCol, int cCol, int dCol)`

Fill in the row all the funky pins go to, the column for the center push button and then the columns for all the directional buttons.&#x20;

`funkyPushL(2,1,5,2,3,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### funkyPushM()

{% tabs %}
{% tab title="Description" %}
Pushbutton with two modes:

* 0: Momentary
* 1: Latching

Uses the button field.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyPushM(int row, int column, int fieldPlacement, int aCol, int bCol, int cCol, int dCol)`

Fill in the row all the funky pins go to, the column for the center push button and then the columns for all the directional buttons.&#x20;

`funkyPushM(2,1,3,5,2,3,4);`

Here the field placement is set to 3. So you'll find the mode of this switch in the 3rd bit of the button field. Corresponding SimHub property is \[DahlDesign.DDCB3].&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.
* 1 button number
{% endtab %}
{% endtabs %}

#### funkyPushModButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton, should be assigned a button number. When held, it will change the mode of switches that are pressed/rotated.

It can also deactivate all [analog injects](../../3.-coding/advanced/analog-inject.md) for 20 seconds by hitting the button 3 times quickly. This is to make button mapping/calibration less of a hassle with analog injects.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyPushModButton(int row, int col, int Acol, int Bcol, int Ccol, ing Dcol);`

For a switch on row 2 column 5, with the directional inputs on columns 1-4 -> `funkyPushModButton(2,5,1,2,3,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### <mark style="background-color:orange;">'unkyPushBite()</mark>

{% tabs %}
{% tab title="Description" %}
The bite point button can either:

* Quickly but less accurately set the bite point by holding the clutch paddle at the desired bite point and then pressing the button.&#x20;
* Together with a supported switch set the bite point with a 0.1% accuracy.

Any switch function that requires a bite button will be <mark style="background-color:orange;">highlighted orange.</mark>

Normally works as a simple pushbutton that can be used to anything in-game. In addition, when held, the controller is primed to enter bite point setting. Hold + rotate a bite point compatible rotary (a rotary using a function that includes bite point setting, these are named rotary2Bite, PEC11Bite, etc.) to enter bite point setting mode. At this point, you can release the bite button. Further presses of the button will go through the stages of setting the bite point (mode 1-3), before in the end going out of bite point setting (back to mode 0).&#x20;

SimHub property -> \[DahlDesign.DDCbiteSetting]

Defaults to bit 11 and 12 in the rotary field, you dont have to assign a field placement.&#x20;

Also, the state of the biteButton itself as a property \[DahlDesign.R15].

**Modes:**

* 0: Bite point setting inactive
* 1: Bite point setting active. Adjust with steps of +/- 10
* 2: Bite point setting active. Adjust with steps of +/- 1
* 3: Bite point setting active. Adjust with steps of +/- 0.1

As stated above, this button's modes are not changed by using a modButton(), but by the biteButton() itself.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyPushBite(int row, int column, int aCol, int bCol, int cCol, int dCol)`

Fill in the row all the funky pins go to, the column for the center push button and then the columns for all the directional buttons.&#x20;

`funkyPushBite(2,1,5,2,3,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### <mark style="background-color:blue;">funkyPushHybrid()</mark>

{% tabs %}
{% tab title="Description" %}
Any switch function that uses a hybrid button will be <mark style="background-color:blue;">highlighted blue.</mark>

A switch dedicated to opening/closing switches with hybrid features, such as DDS functions, rotaryAnalog(), rotary2Modes(), and a few more.

Does not have a button number.
{% endtab %}

{% tab title="Example" %}
`void funkyPushHybrid(int row, int column, int aCol, int bCol, int cCol, int dCol)`

Fill in the row all the funky pins go to, the column for the center push button and then the columns for all the directional buttons.&#x20;

`funkyPushHybrid(2,1,5,2,3,4);`
{% endtab %}

{% tab title="Requirements" %}
None
{% endtab %}
{% endtabs %}

#### funkyPushDDButton()

{% tabs %}
{% tab title="Description" %}
A switch dedicated to swapping between the two "layers" of 12 positions if a DDS switch.

Does not have a button number.
{% endtab %}

{% tab title="Example" %}
`void funkyPushDDButton(int row, int column, int aCol, int bCol, int cCol, int dCol)`

Fill in the row all the funky pins go to, the column for the center push button and then the columns for all the directional buttons.&#x20;

`funkyPushDDButton(2,1,5,2,3,4);`
{% endtab %}

{% tab title="Requirements" %}
None


{% endtab %}
{% endtabs %}
