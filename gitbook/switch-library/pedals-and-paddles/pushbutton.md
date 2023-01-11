# Shifter

Normally, you'll just use [pushButton()](../pushbutton.md#pushbutton) for shifters. Here are special shifter functions which have some added features.

#### pushPull()

{% tabs %}
{% tab title="Description" %}
A function that sets up 4 buttons as a pair of push/pull shifters. Can also of course be used with two shifter paddles and 2 pushbuttons, or 4 shifter paddles (as the SW1 wheel uses it).&#x20;

* 2 modes:
  * 0: Complex -> The 4 buttons only controls 2 button numbers. For instance, right shifter has button numbers 4 on pull, 5 on push. The left shifter will then have 5 on pull, 4 on push. This allows you to gear up/down with either hand on the wheel.
  * 1: Individual -> The 4 buttons are split up and uses 4 button numbers.&#x20;

The button numbers will start with whatever is set up in the slot for the right side pull button in the matrix, and count 3 more from there. So for the other 3 buttons used you dont need to set up a button number in the matrix (can be set to 0, or anything else, it wont be read).&#x20;

In addition, it has a **handbrake feature.** Pressing left and right **pull** buttons together for 1 second will engage "handbrake", which is 100% brake force from the controllers brake axis. <mark style="background-color:red;">Works great with sims that allow you to map a secondary brake axis (iRacing)</mark>. The controller doesn't need clutch paddles for this to work. To **release** the handbrake, simply hold the left and right **push** buttons for 1 second.&#x20;

* If handbrake is active or not is shown in property \[DahlDesign.DDChandbrakeActive]
* The mode uses the button field. \
  `void pushPull(int rightPullRow, int rightPullCol, int rightPushRow, int rightPushCol, int leftPullRow, int leftPullCol, int leftPushRow, int leftPushCol, int fieldPlacement);`
{% endtab %}

{% tab title="Example" %}
`void pushPull(int rightPullRow, int rightPullCol, int rightPushRow, int rightPushCol, int leftPullRow, int leftPullCol, int leftPushRow, int leftPushCol, int fieldPlacement)`

The buttons we're planning to use:

* Right shifter pull: Row 2 Column 1
* Right shifter push: Row 3 Column 3
* Left shifter pull: Row 3 Column 5
* Left shifter push: Row 1 Coumn 2

Resulting in -> `pushPull(2, 1, 3, 3, 3, 5, 1, 2, 4);`

As you can see, the fieldPlacement is set to 4. This function uses the button field, so you'll find the mode of your push/pull complex in the property \[DahlDesign.DDCB4].&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.
* 4 button numbers
{% endtab %}
{% endtabs %}

#### upshift()

{% tabs %}
{% tab title="Description" %}
A simple, momentary pushbutton. It differs from pushButton() in that is has an adjustable cooldown. You can use this to prevent double upshift caused by holding/releasing the shifter paddle too slowly.&#x20;
{% endtab %}

{% tab title="Example" %}
`void upshift(int row, int col, int cooldown)`

For a switch on row 3 column 5 -> `upshift(3,5,250);`

I this case, the button takes a 250 ms pause after being pushed.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}
