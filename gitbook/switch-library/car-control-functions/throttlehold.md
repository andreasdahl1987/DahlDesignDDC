# ThrottleHold

ThrottleHold utilized a [secondary throttle ](./)input to control the cars throttle. ThrottleHold can be turned on/off to hold the throttle at a certain %. The purpose:

* Give your foot a brake on long straights or in oval racing where 100% throttle application is held for most of the race.
* Set to just under 100% it can help you get a steady and reproducable fuel save on long straights.&#x20;

ThrottleHold is set up as a button+encoder complex. The encoder will adjust the throttle hold value when throttle hold is active. When throttle hold is inactive the encoder will adjust the[ brake magic ](brakemagic.md)value.&#x20;

This feature was designed for the SW1 steering wheel, so the functions so far only supports a certain encoder category. Others can be added on request.&#x20;

#### throttleHoldT()

{% tabs %}
{% tab title="Description" %}
Use a toggle switch to turn throttleHold on/off. Paired with an encoder of the[ rotary2Bit ](../encoders/#rotary2bit)category. .

The amount of throttle application given can be read from the controllers throttle axis. Throttle hold on/off defaults to button field 6 for SimHub communication. It is returned as property \[DahlDesign.DDCthrottleHoldActive].&#x20;

Throttle hold % is defined by the variable `throttleHoldValue` found in 41\_Presets.ino. It defaults to all presets with 1000, which is 100%.&#x20;

The rotary encoder will adjust the throttle hold % when throttle hold is active.&#x20;
{% endtab %}
{% endtabs %}

#### throttleHoldT()

{% tabs %}
{% tab title="Description" %}
Use a toggle switch to turn throttleHold on/off. Paired with an encoder of the[ rotary2Bit ](../encoders/#rotary2bit)category. .

The amount of throttle application given can be read from the controllers throttle axis. Throttle hold on/off defaults to button field 6 for SimHub communication. It is returned as property \[DahlDesign.DDCthrottleHoldActive].&#x20;

Throttle hold % is defined by the variable `throttleHoldValue` found in 41\_Presets.ino. It defaults to all presets with 1000, which is 100%.&#x20;

The rotary encoder will adjust the throttle hold % when throttle hold is active.&#x20;
{% endtab %}

{% tab title="Example" %}
`void throttleHoldT(int row, int col)`

For a switch on row 3 column 5 -> `brakeMagic(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* Sim that supports secondary brake input
* 1 button number
{% endtab %}
{% endtabs %}

d
