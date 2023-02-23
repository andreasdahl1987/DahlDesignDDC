# Bite point & launch

These are functions that goes together with your single or dual clutches. **Bite point** is a certain % of clutch application. Usually the bite point of a car means the optimal amount of clutch % application to use in a standing start launch.&#x20;

With dual clutch systems, you can have one clutch giving you clutch application only to the bite point when the paddle is completely pressed, and the other paddle gives 100% clutch application. When holding them together, you can give full throttle and then abruptly release the 100% clutch, bringing you to the optimal amount of clutch application instantly. The same can be achieved by using a [launchButton()](bite-point-and-launch.md#launchbutton) and a single clutch paddle.&#x20;

The bite point is pushed to joystick axis Ry, so you can access it in windows/SimHub. If you [connect](../../4.-advanced-features/connect-to-simhub.md) you DDC controller to SimHub, you can also access the bite point by the property \[DahlDesign.DDCbitePoint].&#x20;

#### <mark style="background-color:orange;">biteButton()</mark>

{% tabs %}
{% tab title="Description" %}
The bite point button can either:

* Quickly but less accurately set the bite point by holding the clutch paddle at the desired bite point and then pressing the button.&#x20;
* Together with a supported switch set the bite point with a 0.1% accuracy, explained below.

Any switch function that requires a bite button will be <mark style="background-color:orange;">highlighted orange.</mark>

Normally works as a simple pushbutton that can be used to anything in-game. In addition, when held, the controller is primed to enter bite point setting. Hold + rotate a bite point compatible rotary (a rotary using a function that includes bite point setting) to enter bite point setting mode. At this point, you can release the bite button. Further presses of the button will go through the stages of setting the bite point (mode 1-3), before in the end going out of bite point setting (back to mode 0).&#x20;

SimHub property -> \[DahlDesign.DDCbiteSetting]

Defaults to bit 11 and 12 in the rotary field, you dont have to assign a field placement.&#x20;

**Modes:**

* 0: Bite point setting inactive
* 1: Bite point setting active. Adjust with steps of +/- 10
* 2: Bite point setting active. Adjust with steps of +/- 1
* 3: Bite point setting active. Adjust with steps of +/- 0.1

As stated above, this button's modes are not changed by using a modButton(), but by the biteButton() itself.&#x20;
{% endtab %}

{% tab title="Example" %}
`void biteButton(int row, int col)`

For a switch on row 2 column 4 -> `biteButton(2,4);`


{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### launchButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton, should be assigned a button number. Works like a normal pushbutton, but when you hold a clutch paddle completely pressed and hit this button, it will drop the value of the clutch output to the set bite point. The button will not work as a pushbutton untill the clutch is completely released, so you can even map a shifter paddle as launchButton(), and it wont change gears when you use it to launch with.

In esssense this makes it possible to do a single clutch launch and a 1-handed launch. Ideal for wheels with a single clutch paddle or for cars that also use handbrake on launch (rallycross and Supercar).&#x20;
{% endtab %}

{% tab title="Example" %}
`void launchButton(int row, int column, int switchNumberAffected)`

For a switch on row 2 column 4, coupling to clutch that has been assigned[ switch# 3 ](../../1.-project-planning/analog-inputs.md)on master paddle:

`launchButton(2,4,3);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* A analog switch to affect
{% endtab %}
{% endtabs %}

#### neutralButton()

{% tabs %}
{% tab title="Description" %}
Pushbutton with two modes:

* 0: Toggle on/off NEUTRAL, which sets the clutch to 100%. Info on this switch state is available as properties in SimHub. In addition, the property DahlDesign.SmoothGear will show “N” when this is active. 1: Regular momentary pushbutton.
* 1: Momentary pushbutton

SimHub property -> \[DahlDesign.NeutralActive]

SimHub property -> \[DahlDesign.NeutralMode]

Defaults to bit 5 and bit 15 in button field, you dont have to assign a field placement.

\[DahlDesign.SmoothGear] will show "N" when neutral is active.&#x20;
{% endtab %}

{% tab title="Example" %}
`void neutralButton(int row, int col)`

For a switch on row 2 column 4 -> `neutralButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to swap modes.
* 1 button number
{% endtab %}
{% endtabs %}

#### bitePot()

{% tabs %}
{% tab title="Description" %}
Set up a device that output variable voltages, typically a potentiometer, to adjust the bite point. Should be wired [like this](../../2.-wiring/analog-wiring.md).&#x20;

When you add a bitePot() to the code, it will override any other bite point setting method. To prevent this, you can add a toggle or button to lock the bitePot() switch.

As with all analog switches, you will need to [read out ](../../1.-project-planning/analog-inputs.md#reading-a-value)values from the outer positions of the switch.&#x20;
{% endtab %}

{% tab title="Example" %}
`void bitePot(int analogPin, int switchNumber, int startValue, int endValue)`

For a potentiometer with its center pin connected to A3, assigned switch# 4, it could look like this:

`bitePot(A3, 4, 0, 1023);`
{% endtab %}

{% tab title="Requirements" %}
* None


{% endtab %}
{% endtabs %}

#### bitePotLockButton()

{% tabs %}
{% tab title="Description" %}
A toggle button -> toggle on will lock your bitePot() switch, essentially silencing it in the code loop, and allowing you to use other ways to set the bite point on this controller:

* Using presets
* Using biteButton()
* Using rotary switches and encoders

Toggling this off will make the bitepoint from the bitePot() override everything again.&#x20;

This is also useful to prevent unintended changes to bite point.&#x20;

Uses the button field.

Does not produce any button press, and therefore does not need to be assigned a button number.&#x20;
{% endtab %}

{% tab title="Example" %}
`void bitePotLockButton(int row, int col, int fieldPlacement)`

For a switch on row 3 column 5 -> `bitePotLockButton(3,5,1);`

Here using fieldPlacement 1, meaning he 1st bit in the button field. If bite pot lock is on/off will be reflected by the property `[DahlDesign.DDCB1].`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* A bitePot() switch
{% endtab %}
{% endtabs %}

#### bitePotLockToggle()

{% tabs %}
{% tab title="Description" %}
A toggle switch functions -> toggle on will lock your bitePot() switch, essentially silencing it in the code loop, and allowing you to use other ways to set the bite point on this controller:

* Using presets
* Using biteButton()
* Using rotary switches and encoders

Toggling this off will make the bitepoint from the bitePot() override everything again.&#x20;

This is also useful to prevent unintended changes to bite point.&#x20;

Uses the button field.

Does not produce any button press, and therefore does not need to be assigned a button number.&#x20;
{% endtab %}

{% tab title="Example" %}
`void bitePotLockToggle(int row, int col, int fieldPlacement)`

For a switch on row 3 column 5 -> `bitePotLockToggle(3,5,1);`

Here using fieldPlacement 1, meaning he 1st bit in the button field. If bite pot lock is on/off will be reflected by the property `[DahlDesign.DDCB1].`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* A bitePot() switch
{% endtab %}
{% endtabs %}
