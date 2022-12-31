# Handbrake

The handbrake functions utilized a [secondary brake input](./) to control the brakes of the car. They will apply 100% brake application. The [push/pull shifter](pushbutton.md#pushpull) function also has a way to apply handbrake, but it not listed here.&#x20;

It is recommended to add the handbrake functions towards the end of your list of switch functions in 30\_Switches.ino for best performance.&#x20;

#### handbrakeM()

{% tabs %}
{% tab title="Description" %}
Apply handbrake momentarily. Handbrake will be applied as long as you hold the button.

Does not produce any button number press.

Handbrake on/off defaults to button field 10 for SimHub communication. It is returned as property \[DahlDesign.DDChandbrakeActive].&#x20;
{% endtab %}

{% tab title="Example" %}
`void handbrakeM(int row, int col)`

For a switch on row 3 column 5 -> `handbrakeM(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* Sim that supports secondary brake input
{% endtab %}
{% endtabs %}

#### handbrakeL()

{% tabs %}
{% tab title="Description" %}
Apply a latching handbrake. Pressing the button will toggle the handbrake on/off.&#x20;

Does not produce any button number press.

Handbrake on/off defaults to button field 10 for SimHub communication. It is returned as property \[DahlDesign.DDChandbrakeActive].&#x20;
{% endtab %}

{% tab title="Example" %}
`void handbrakeL(int row, int col)`

For a switch on row 3 column 5 -> `handbrakeL(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* Sim that supports secondary brake input
{% endtab %}
{% endtabs %}
