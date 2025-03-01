# Utility

Here are useful functions for controller maintenance.

#### firmwareUploadMode()

{% tabs %}
{% tab title="Description" %}
This function is RP2040 specific. It will let you set up two buttons to reboot the RP2040 chip into USB storage device mode when held together for a set amount of time. This allows you to quickly update/swap firmware on your controller without having to take it apart to use the BOOTSEL button.&#x20;

This function will not produce any button presses, so you should also use functions like pushButton(), modButton(), biteButton() etc. for these two buttons.
{% endtab %}

{% tab title="Example" %}
`void firmwareUploadMode(int Arow, int Acol, int Brow, int Bcol, int timer)`

For two buttons on row 1 column 3 and row 2 column 2:

`firmwareUploadMode(1,3,2,2,4000);`

These two buttons will behave like normal buttons, but if held together for 4000 ms (4 seconds) you will reboot the controller into USB storage mode.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}
