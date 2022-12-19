# Shifter

Normally, you'll just use pushButton() for shifters. Here I'll list special shifter functions which have some added features.

#### pushPull()

{% tabs %}
{% tab title="Description" %}
A function that sets up 4 buttons as a pair of push/pull shifters. Can also of course be used with two shifter paddles and 2 pushbuttons, or 4 shifter paddles (as the SW1 wheel uses it).&#x20;

* 2 modes:
  * 0: Complex -> The 4 buttons only controls 2 button numbers. For instance, right shifter has button numbers 4 on pull, 5 on push. The left shifter will then have 5 on pull, 4 on push. This allows you to gear up/down with either hand on the wheel.
  * 1: Individual -> The 4 buttons are split up and uses 4 button numbers.&#x20;

The button numbers will start with whatever is set up in the slot for the right side pull button in the matrix, and count 3 more from there. So for the other 3 buttons used you dont need to set up a button number in the matrix (can be set to 0, or anything else, it wont be read).&#x20;

In addition, it has a **handbrake feature.** Pressing left and right **pull** buttons together for 1 second will engage "handbrake", which is 100% brake force from the controllers brake axis. Works great with sims that allow you to map a secondary brake axis (iRacing). The controller doesn't need clutch paddles for this to work. To **release** the handbrake, simply hold the left and right **push** buttons for 1 second.&#x20;

* If handbrake is active or not is shown in property \[DahlDesign.DDChandbrakeActive]
* The mode uses the button field.&#x20;
{% endtab %}

{% tab title="Example" %}
`void pushButton(int row, int col)`

For a switch on row 3 column 5 -> `pushButton(3,5);`
{% endtab %}

{% tab title="Requirements" %}
None
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
None
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
modButton()
{% endtab %}
{% endtabs %}

__

__
