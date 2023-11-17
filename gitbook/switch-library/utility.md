# Utility

Here are useful functions for controller maintenance.

#### firmwareUploadMode()

{% tabs %}
{% tab title="Description" %}
This function is RP2040 specific. It will let you set up two regular pushbuttons so that when they are held together for a speficied amount of time, you will reboot the RP2040 chip into USB storage device mode. This allows you to quickly update/swap firmware on your controller without having to take it appart to use the BOOTSEL button.&#x20;

The two buttons used will work like regular pushbuttons as well. You could for instance use you shifters for this function. &#x20;
{% endtab %}

{% tab title="Example" %}
`void firmwareUploadMode(int Arow, int Acol, int Brow, int Bcol, int timer)`

For two buttons on row 1 column 3 and row 2 column 2:

`firmwareUploadMode(1,3,2,2,4000);`

These two buttons will behave like normal buttons, but if held together for 4000 ms (4 seconds) you will reboot the controller into USB storage mode.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
{% endtab %}
{% endtabs %}
