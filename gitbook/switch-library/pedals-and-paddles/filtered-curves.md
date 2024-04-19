# Filtered curves

All pedal/paddle functions that are used to make a joystick axis will have an alternative function with a curve filter included. The purpose of the filter is to adjust the rise of the output curve.

<figure><img src="../../.gitbook/assets/image (2) (3).png" alt=""><figcaption></figcaption></figure>

Particularily with hall sensors, it can be difficult to design a device that has a completely linear output. Either too much happens too soon (above to the left) or to much happens too late (above to the right).&#x20;

The filter functions have an **extra two values** to fill in, but appart from that they are identical to the filter-less versions:

* curvePush -> The direction of curve adjustments. "1" will push the curve flat, "-1" will lift the curve up. "0" wil disable the whole filter. There is nothing inbetween, so really "1" and "-1" are the only values you should be using.
* expFactor -> How hard you're pushing the curve. Decimal values from 0 and up. In practice doesn't reach higher than 10 before the function stops working and you'll get no value at all from your paddle/pedal. This is because the numbers used in the calculations get too big for the arduino to handle. Anyways, expFactor set to 10 is an extreme adjustment. and will not be needed. Likely, you'll use a value between 0 and 1.5.

<figure><img src="../../.gitbook/assets/image (3) (2) (2).png" alt=""><figcaption></figcaption></figure>

The figures above show how curvePush = 1 (left) and curvePush = -1 (right) worrks, and how different values of expFactor (0.5 - 5) will alter the curve. In the case, a value of 2 is needed to reach linearity, which is a pretty big adjustment.&#x20;

While this is useful for improving the linearity of a pedal output, there are many other ways to take advantage of this filter:&#x20;

* For a DIY handbrake, you might want it a bit more responsive, lift the curve a little
* &#x20;You can use this on your DIY brake/throttle pedals to make them more/less responsive. Some prefer to not have a linear pedal response.
* You can make [presets](../../3.-coding/advanced/presets/) for your pedals, ranging from responsive throttle for high-grip conditions to less responsive (flatter curve) for wet conditions and a switch to togle though your throttle shapes.&#x20;

The filter algorithms have been written from bottom-up without using libraries to ensure as little processing power and memory usage as possible. However, these functions will use more memory and processing power than their filter-less versions. So if you don't need a filter, don't use a filter function.

#### filteredBrake()

{% tabs %}
{% tab title="Description" %}
Similar to[ brake()](brake-throttle.md#brake), but with added filter.
{% endtab %}

{% tab title="Example" %}
`void filteredBrake(int analogChannel, int releasedValue, int fullyPressedValue, int curvePush, float expFactor)`

For a load cell on analog channel 4, it could look like this:

`filteredBrake(4, 640, 212, 1, 1.2);`

With a curvePush of 1, this will flatten the response curve, meaning you'll get more braking power towards the end of the travel. ExpFactor of 1.2 is a sizable flattening of the curve.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* None


{% endtab %}
{% endtabs %}

#### filteredThrottle()

{% tabs %}
{% tab title="Description" %}
Similar to [throttle()](brake-throttle.md#throttle), but with added filter.
{% endtab %}

{% tab title="Example" %}
`void filteredThrottle(int analogChannel, int releasedValue, int fullyPressedValue, int curvePush, float expFactor)`

For a potentiometer on analog channel 4, it could look like this:

`filteredThrottle(4, 0, 1023,-1,0.7);`

With a curvePush of -1, this will raise the response curve, meaning you'll get more output of the throttle at the start of the paddle/pedal travel. ExpFactor of 0.7 is a moderate push of the curve.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* None


{% endtab %}
{% endtabs %}

#### filteredBitePot()

{% tabs %}
{% tab title="Description" %}
Similar to bitePot(), but with added filter.
{% endtab %}

{% tab title="Example" %}
`void filteredBitePot(int analogChannel, int startValue, int endValue, int curvePush, float expFactor)`

For a potentiometer on analog channel 2, it could look like this:

`filteredBitePot(2, 0, 1023, -1, 0.3);`

With a curvePush of -1, this will raise the response curve, meaning you'll get more output of the potentiometer at the start of the rotation. ExpFactor of 0.3 is a small adjustment of the curve.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* None


{% endtab %}
{% endtabs %}

#### filteredSingleClutch()

{% tabs %}
{% tab title="Description" %}
Similar to [singleClutch()](clutch.md#singleclutch), but with added filter
{% endtab %}

{% tab title="Example" %}
`void filteredSingleClutch(int analogChannel, int releasedValue, int fullyPressedValue, int curvePush, float expFactor)`

Type in the analog channel that runs the clutch, and the values you read out from serial monitor.&#x20;

Example:

`void filteredSingleClutch(2, 231, 799, 1, 2.8);`

With a curvePush of 1, this will flatten the response curve, meaning you'll get more clutch response towards the end of the travel. ExpFactor of 2.8 is a big push to flatten the curve.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* biteButton() or bitePot() to set bite point if desired
* launchButton() to launch, if desired
{% endtab %}
{% endtabs %}

#### filteredDualClutch()

{% tabs %}
{% tab title="Description" %}
Similar to [dualClutch()](clutch.md#dualclutch), but with added filter.
{% endtab %}

{% tab title="Example" %}
`void filteredDualClutch(int masterAnalogChannel, int masterReleasedValue, int masterFullyPressedValue, int masterCurvePush, float masterExpFactor int slaveAnalogChannel, int slaveReleasedValue, int slaveFullyPressedValue, int slaveCurvePush, float slaveExpFactor, bool throttleMaster)`

Type in the analog channels for the clutches and the values you read out from serial monitor. This for both switches, decide which is master and slave. Lastly, throttleMaster makes master paddle throttle and slave paddle brake in mode 3. if set to `true`. Opposite if set to `false`.&#x20;

Example:

`void dualClutch(1, 105, 799, 1, 1.3, 2, 436, 873, 1, 1.5, true);`

In this example, both master and slave paddles have curvePush "1", which will flatten the response curve, makeing it more responsive towards the end of the paddle travel. Both have a sizable adjustment of 1.3 for the master paddle and 1.5 for the slave paddle.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() to change modes
* biteButton() or bitePot() to change the pite point.
* launchButton() if you want 1-handed launches.
{% endtab %}
{% endtabs %}
