# Clutch

Both single clutch and dual clutch are supported. Dual clutch setup has a lot more features. The hallmark feature of a dual clutch system is having quick access to the **bite point**, a predetermined percentage of clutch application that is ideal for a standing start.&#x20;

The bite point can be adjusted in many ways:

* A [biteButton()](../function-button.md#bitebutton) alone
* A [biteButton()](../function-button.md#bitebutton) with a supported rotary switch or encoder function
* Using a [bitePot()](bite-point-and-launch.md)&#x20;
* Using [presets](../../3.-coding/advanced/presets/).
* ++

Clutches use the joystick X axis. The bite point is shown by the RY axis.&#x20;

DDC also allows the use of EEPROM to store clutch calibrations - and thus allowing you to quickly calibrate your clutches without having to map out the analog signals using [checkValue()](../../1.-project-planning/analog-inputs/#reading-a-value). For that, use the _dualClutchCal()_ function instead of _dualClutch()._&#x20;

If you're using a calibration based clutch function, make sure to have a button for **clutchCalibrate().**

There are also [filtered](filtered-curves.md#filteredsingleclutch) versions of all clutch functions.&#x20;

#### singleClutch() or singleClutchCal()

{% tabs %}
{% tab title="Description" %}
A simple single-paddle clutch.

Can be used to set the bite point together with a [biteButton()](../function-button.md#bitebutton)

Can launch when coupled with launchButton()
{% endtab %}

{% tab title="Example" %}
`void singleClutch(int analogChannel, int releasedValue, int fullyPressedValue)`

Type in the channel this clutch is running on, and the values you read out from serial monitor.&#x20;

Example:

`void singleClutch(3, 105, 799);`

`void singleClutchCal(3);`
{% endtab %}

{% tab title="Requirements" %}
* biteButton() or bitePot() to set bite point if desired
* launchButton() to launch, if desired
* clutchCalibration() button if you're using dualClutchCal()
{% endtab %}
{% endtabs %}

#### dualClutch() or dualClutchCal()

{% tabs %}
{% tab title="Description" %}
A dual paddle clutch system. Has 4 modes:

0: Static - The slave paddle only reaches bite point, the master paddle goes to 100%

1: Dynamic low - Either paddle alone only reaches bite point, press both together to reach 100%

2: Dynamic high - Either paddle alone reaches 100%. Press both and release one to get to bite point.

3: Brake/throttle - Using the paddles as brake and throttle. Output now changes from joystick X axis to brake/throttle axis.&#x20;

Changing modes are done by holding the modButton and pressing either paddle all the way in and releasing. If this doesnt work, it is a good indication that your clutch doesnt reach a stable 100% or rest at a stable 0% - which means you should adjust your values.&#x20;

The function defaults to bits 13 and 14 in the rotary field. Will be returned by SimHub as property \[DahlDesign.DDCclutchMode].

_With dualClutchCal() you'll need to set up a clutchCalibrate() button._
{% endtab %}

{% tab title="Example" %}
`void dualClutch(int masterAnalogChannel, int masterReleasedValue, int masterFullyPressedValue, int slaveAnalogChannel, int slaveReleasedValue, int slaveFullyPressedValue, bool throttleMaster)`

Type in analog channels used and the values you read out from serial monitor. This for both switches, decide which is master and slave. Lastly, throttleMaster makes master paddle throttle and slave paddle brake in mode 3. if set to `true`. Opposite if set to `false`.&#x20;

Example:

`void dualClutch(1, 105, 799, 2, 436, 873, true);`

`void dualClutchCal(1, 2, true);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() to change modes
* biteButton() or bitePot() to change the pite point.
* launchButton() if you want 1-handed launches.
* clutchCalibration() button if you're using dualClutchCal()
{% endtab %}
{% endtabs %}

#### clutchCalibrate()

{% tabs %}
{% tab title="Description" %}
A regular pushbutton that also serves as a trigger for clutch calibration sequence:

* Hold the button for 4 seconds, release.
* Completely press and release your clutch(es).
* Press button once.

Now your clutches are fresh and calibrated. The calibration adds a small deadzone on top and bottom. If you want a bigger deadzone, sligthly hold the clutch(es) while doing the 4 second push, and you can also add a deadzone at the end of the travel by not completely pressing the clutch(es) during calibration.&#x20;

The state of the calibration mode is found as SimHub property \[DahlDesign.R8].
{% endtab %}

{% tab title="Example" %}
`void clutchCalibration(int row, int column)`

Example for a pushbutton on row 1 column 3:

`void clutchCalibrate(1,3);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* Something to calibrate, allthough not a must. Firmware will work still.&#x20;
{% endtab %}
{% endtabs %}



