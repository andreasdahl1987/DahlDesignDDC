# Toggle switches

#### toggle()

{% tabs %}
{% tab title="Description" %}
A simple, latching toggle. The button numer is the one you set in your matrix setup.
{% endtab %}

{% tab title="Example" %}
`void toggle(int row, int col)`

For a switch on row 3 column 5 -> `toggle(3,5);`
{% endtab %}

{% tab title="Requirements" %}
None
{% endtab %}
{% endtabs %}

#### toggleP()

{% tabs %}
{% tab title="Description" %}
The toggle switch will give a short button pulse upon moving from on->off or from off->on position. When standing still in on or off position, no button is pressed.
{% endtab %}

{% tab title="Example" %}
`void toggleP(int row, int col)`

For a switch on row 3 column 5 -> `toggleP(3,5);`
{% endtab %}

{% tab title="Requirements" %}
None
{% endtab %}
{% endtabs %}

#### toggleM()

{% tabs %}
{% tab title="Description" %}
Toggle switch with two modes:

* 0: Latching toggle
* 1: Pulse toggle

Uses the button field.&#x20;
{% endtab %}

{% tab title="Example" %}
`void toggleM(int row, int col, int fieldPlacement)`

For a switch on row 3 column 5 -> `pushButtonM(3,5,4);`

Here the field placement is set to 4. So you'll find the mode of this switch in the 4th bit of the button field. Corresponding SimHub property is \[DahlDesign.DDCB4].&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.
{% endtab %}
{% endtabs %}

__

__
