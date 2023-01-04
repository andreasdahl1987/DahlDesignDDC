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

d
