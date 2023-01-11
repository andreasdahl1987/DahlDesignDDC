# Clutch

Both single clutch and dual clutch are supported. Dual clutch setup has a lot more features.&#x20;

A [biteButton()](../function-button.md#bitebutton) or [bitePot()](bite-point-and-launch.md) is used to set bite point.

Clutches use the joystick X axis.&#x20;

#### singleClutch()

{% tabs %}
{% tab title="Description" %}
A simple single-paddle clutch.

Can be used to set the bite point together with a [biteButton()](../function-button.md#bitebutton)

Can launch when coupled with launchButton()
{% endtab %}

{% tab title="Example" %}
`void singleClutch(int analogPin, int switchNumber, int releasedValue, int fullyPressedValue)`

Type in the pin that reads the signal, the analog switch number you've given it, and the values you read out from serial monitor.&#x20;

Example:

`void singleClutch(A2, 2, 105, 799);`
{% endtab %}

{% tab title="Requirements" %}
* biteButton() or bitePot() to set bite point if desired
* launchButton() to launch, if desired
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

`void dualClutch(A2, 1, 105, 799, A3, 2, 436, 873, true);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() to change modes
* biteButton() or bitePot() to change the pite point.
* launchButton() if you want 1-handed launches.
{% endtab %}
{% endtabs %}
