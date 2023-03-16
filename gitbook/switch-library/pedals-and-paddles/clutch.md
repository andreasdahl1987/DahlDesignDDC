# Clutch

Both single clutch and dual clutch are supported. Dual clutch setup has a lot more features. The hallmark feature of a dual clutch system is having quick access to the **bite point**, a predetermined percentage of clutch application that is ideal for a standing start.&#x20;

The bite point can be adjusted in many ways:

* A [biteButton()](../function-button.md#bitebutton) alone
* A [biteButton()](../function-button.md#bitebutton) with a supported rotary switch or encoder function
* Using a [bitePot()](bite-point-and-launch.md)&#x20;
* Using [presets](../../3.-coding/advanced/presets/).

Clutches use the joystick X axis. The bite point is shown by the RY axis.&#x20;

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

0: Static - The slave paddle only reaches bite point, the master paddle goes to 100%

1: Dynamic low - Either paddle alone only reaches bite point, press both together to reach 100%

2: Dynamic high - Either paddle alone reaches 100%. Press both and release one to get to bite point.

3: Brake/throttle - Using the paddles as brake and throttle. Output now changes from joystick X axis to brake/throttle axis.&#x20;

Changing modes are done by holding the modButton and pressing either paddle all the way in and releasing. If this doesnt work, it is a good indication that your clutch doesnt reach a stable 100% or rest at a stable 0% - which means you should adjust your values.&#x20;

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
