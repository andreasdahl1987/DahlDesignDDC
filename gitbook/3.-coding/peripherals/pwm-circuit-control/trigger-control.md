# Trigger control

By using `triggerPWM()` you have complete freedom to make anything happening in your firmware affect a PWM channel. Post this in 30\_Switches.ino

#### triggerPWM()

{% tabs %}
{% tab title="Description" %}
Allows you to turn on/off PWM channels and add a blinking effect if a condition is met.

To get access to things happening in the firmware and use this as a condition, there are [triggers](../../advanced/conditional-coding/triggers.md) you can use. These will return `true` under certain conditions.&#x20;
{% endtab %}

{% tab title="Example" %}
`void triggerPWM(PWMchannel, condition,  blinkEnable, blinkOnTimer, blinkOffTimer)`

`Typed out and explained:`

```
triggerPWM(
2, //----------------------Affecting PWM channel 2
analogTravel(1, 10), //-------Checking if analog channel 1 has reached 10% of its range
true, //--------Will blink
100, //---------Will turn on for 100 ms on blinking
900, //---------Will turn off for 900 ms on blinking

```

* This is used to make a potentiometer (set up as a PWMPot() on analog channel 1) turn on the PWM channel as long as its travel is more or similar to 10% of its total travel. If not, PWM is turned of. The effect is that the LEDs we're controlling here will dim down until they abruptly turn off.&#x20;


{% endtab %}

{% tab title="Requirements" %}
* A PWM channel
{% endtab %}
{% endtabs %}

####
