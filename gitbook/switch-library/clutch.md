# Clutch

Both single clutch and dual clutch are supported. Dual clutch setup has a lot more features.&#x20;

To calibrate the clutches, you'll have to read the values from the paddles when fully pressed and fully released, by using the [serial monitor. ](../1.-project-planning/analog-inputs.md#reading-a-value)

The values will often be a bit erratic. Most reliable readings are when the paddles are properly mounted and all elements of the controller that consumes power are powered up. Your readings might still be a bit erratic. The general idea is:

* Use the highest value that your read on your lowest value measurements
* Use the lower value that you read on your highest value measurements

So if your controller fluctuates between 864 - 873 when paddle is not pressed, and 436 - 444 when pressed, use the values 864 for not pressed and 444 for pressed.&#x20;

If one paddle has higher value on pressed than released and the other paddle is the opposide - it does not matter.

A [biteButton()](function-button.md#bitebutton) is used to set bite point in dual clutch systems.&#x20;

Clutches use the joystick X axis.&#x20;

You can increase the deadzone of  the clutches by adjusting the deadzone in 12\_GlobalVariables.ino.

#### singleClutch()

{% tabs %}
{% tab title="Description" %}
A simple single-paddle clutch.
{% endtab %}

{% tab title="Example" %}
`void singleClutch(int analogPin, int switchNumber, int releasedValue, int fullyPressedValue)`

Type in the pin that reads the signal, the analog switch number you've given it, and the values you read out from serial monitor.&#x20;

Example:

`void singleClutch(A2, 2, 1053, 799);`
{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}

#### dualClutch()

{% tabs %}
{% tab title="Description" %}
A dual paddle clutch system. Has 4 modes:

0: Static - The slave paddle is locked at bite point, the master paddle goes to 100%

1: Dynamic low - Either paddle alone is at bite point, press both together to get to 100%

2: Dynamic high - Either paddle alone is at 100%. Press both and release one to get to bite point.

3: Brake/throttle - Using the paddles as brake and throttle. Output now changes from joystick X axis to brake/throttle axis.&#x20;

The function defaults to bits 13 and 14 in the rotary field. Will be returned by SimHub as property \[DahlDesign.DDCclutchMode].
{% endtab %}

{% tab title="Example" %}
`void dualClutch(int masterPin, int masterSwitchNumber, int masterReleasedValue, int masterFullyPressedValue, int slavePin, int slaveSwitchNumber, int slaveReleasedValue, int slaveFullyPressedValue, bool throttleMaster)`

Type in the pin that reads the signal, the analog switch number you've given it, and the values you read out from serial monitor. This for both switches, decide which is master and slave. Lastly, throttleMaster makes master paddle throttle and slave paddle brake in mode 3. if set to `true`. Opposite if set to `false`.&#x20;

Example:

`void dualClutch(A2, 1, 1053, 799, A3, 2, 436, 873, true);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() to change modes
* biteButton() to change the pite point.
{% endtab %}
{% endtabs %}

