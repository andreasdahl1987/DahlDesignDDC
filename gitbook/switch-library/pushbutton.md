# Pushbutton

#### pushButton()

{% tabs %}
{% tab title="Description" %}
A simple, momentary pushbutton. The button numer is the one you set in your matrix setup.
{% endtab %}

{% tab title="Example" %}
`void pushButton(int row, int col)`

For a switch on row 3 column 5 -> `pushButton(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### pushButtonL()

{% tabs %}
{% tab title="Description" %}
The button will become a latching button, so hitting it once will turn it on, hitting again will turn it off.
{% endtab %}

{% tab title="Example" %}
`void pushButtonL(int row, int col)`

For a switch on row 3 column 5 -> `pushButtonL(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### pushButtonM()

{% tabs %}
{% tab title="Description" %}
Pushbutton with two modes:

* 0: Momentary
* 1: Latching

Uses the button field.&#x20;
{% endtab %}

{% tab title="Example" %}
`void pushButtonM(int row, int col, int fieldPlacement)`

For a switch on row 3 column 5 -> `pushButtonM(3,5,1);`

Here the field placement is set to 1. So you'll find the mode of this switch in the 1st bit of the button field. Corresponding SimHub property is \[DahlDesign.DDCB1].&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.
* 1 button number
{% endtab %}
{% endtabs %}

#### pulseButton()

{% tabs %}
{% tab title="Description" %}
A button that gives a short pulse on pressing the button. Holding the button will not give a continous button press. Releasing the button will not give a button press. The button numer is the one you set in your matrix setup.
{% endtab %}

{% tab title="Example" %}
`void pulseButton(int row, int col)`

For a switch on row 3 column 5 -> `pulseButton(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

