# Firmware control

Output functions is the way you control your outputs through the firmware directly, not using simHub.  There are three functions that should cover most of your needs:

* setOutput()
* triggerOutput()
* rotaryOutput()

triggerOutput alone will give you the freedom to do pretty much anything.

#### setOutput()

{% tabs %}
{% tab title="Description" %}
Allows turn on/off a specific output on a specific hub.
{% endtab %}

{% tab title="Example" %}
`void setOutput(hub, slot, value)`

To turn on output slot 7 on hub 2:

`setOutput(2,7, true);`
{% endtab %}

{% tab title="Requirements" %}
* Set up at least 1 output hub
{% endtab %}
{% endtabs %}

#### triggerOutput()

{% tabs %}
{% tab title="Description" %}
Allows you to turn on/off a specific output on a specific hub under certain conditions. Also allows you to make the output "blink", turning it on/off at given time intervals.&#x20;

To get access to things happening in the firmware and use this as a condition, there are [triggers](../../advanced/conditional-coding/triggers.md) you can use. These will return `true` under certain conditions.&#x20;
{% endtab %}

{% tab title="Example" %}
`void triggerOutput(hub, slot, condition, blinkEnable, blinkOnTimer, blinkOffTimer)`

`Typed out and explained:`

```
triggerOutput(
1, //------------Output hub 1
4, //------------Slot 4
modButtonPressed(), //-------------Turn on if this is true
true,      //-----Blinking enabled
300,       //--------Will stay lit for 300 ms on blinking
2000);     //--------Will turn off LED for 2000 ms on blinking
```

In another example, lets turn on output hub 2, slot 11 and 12 if my button on row4/column5 is pressed, no blinking:

```
triggerOutput(2,11,buttonPressed(4,5),false, 0, 0);
triggerOutput(2,11,buttonPressed(4,5),false, 0, 0);
```
{% endtab %}

{% tab title="Requirements" %}
* Set up at least 1 output hub
{% endtab %}
{% endtabs %}

#### rotaryOutput()

{% tabs %}
{% tab title="Description" %}
Pairs an output hub to a rotary switch to make a single output slot on the hub activate depending on the position of the rotary switch. Will work for any amount of positions (up to 16) and has an offset setting to accurately match the rotary switch.&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotaryOutput`(analogChannel, hub, startPin, offset,  positions, reverse)

`Typed out and explained:`

<pre><code>rotaryOutput(
1, //------------Rotary switch is on analog channel 1
4, //------------Pair to output hub number 4
1, //------------Starting on output hubs first slot
<strong>0, //------------No offset. Can be both positive or negative
</strong><strong>12, //-----------Rotary switch has 12 positions
</strong>false); //-------Switch rotation direction not reversed
</code></pre>

All in all without the comments:

```
rotaryOutput(1,4,1,0,12,false);
```
{% endtab %}

{% tab title="Requirements" %}
* Set up at least 1 output hub
* Rotary switch
{% endtab %}
{% endtabs %}
