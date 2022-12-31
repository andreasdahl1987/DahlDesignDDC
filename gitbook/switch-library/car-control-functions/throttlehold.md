# ThrottleHold

ThrottleHold utilized a [secondary throttle ](./)input to control the cars throttle. ThrottleHold can be turned on/off to hold the throttle at a certain %. The purpose:

* Give your foot a brake on long straights or in oval racing where 100% throttle application is held for most of the race.
* Set to just under 100% it can help you get a steady and reproducable fuel save on long straights.&#x20;

ThrottleHold is set up as a button+encoder complex. The encoder will adjust the throttle hold value when throttle hold is active. When throttle hold is inactive the encoder will adjust the[ brake magic ](brakemagic.md)value.&#x20;

This feature was designed for the SW1 steering wheel, so the functions so far only supports a certain encoder category. Others can be added on request.&#x20;

#### throttleHoldT()

{% tabs %}
{% tab title="Description" %}
Use a toggle switch to turn throttleHold on/off. Paired with an encoder of the[ rotary2Bit ](../encoders/#rotary2bit)category. Neither button nor encoder will produce any button number press.&#x20;

The amount of throttle application given can be read from the controllers throttle axis. Throttle hold on/off defaults to button field 6 for SimHub communication. It is returned as property \[DahlDesign.DDCthrottleHoldActive].&#x20;

Throttle hold % is defined by the variable `throttleHoldValue` found in 41\_Presets.ino. It defaults to all presets with 1000, which is 100%.&#x20;

The rotary encoder will adjust the throttle hold % when throttle hold is active.&#x20;
{% endtab %}

{% tab title="Example" %}
`throttleHoldT(int8_t buttonRow, int8_t buttonCol, int8_t rotaryRow, int8_t rotaryCol, bool reverse)`

For a button on row 2 column 3 and encoder on row 3 column 2+3:

`throttleHoldT(2, 3, 3, 2, true);`

In this case, "reverse" is set to true, so the actions of CW and CCW rotation will be flipped.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* Sim that supports secondary throttle input
{% endtab %}
{% endtabs %}

#### throttleHoldM()

{% tabs %}
{% tab title="Description" %}
Use a momentary switch to toggle throttleHold on/off. Paired with an encoder of the[ rotary2Bit ](../encoders/#rotary2bit)category. Neither button nor encoder will produce any button number press.&#x20;

The amount of throttle application given can be read from the controllers throttle axis. Throttle hold on/off defaults to button field 6 for SimHub communication. It is returned as property \[DahlDesign.DDCthrottleHoldActive].&#x20;

Throttle hold % is defined by the variable `throttleHoldValue` found in 41\_Presets.ino. It defaults to all presets with 1000, which is 100%.&#x20;

The rotary encoder will adjust the throttle hold % when throttle hold is active.&#x20;
{% endtab %}

{% tab title="Example" %}
`throttleHoldM(int8_t buttonRow, int8_t buttonCol, int8_t rotaryRow, int8_t rotaryCol, bool reverse)`

For a button on row 2 column 3 and encoder on row 3 column 2+3:

`throttleHoldM(2, 3, 3, 2, true);`

In this case, "reverse" is set to true, so the actions of CW and CCW rotation will be flipped.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* Sim that supports secondary throttle input
{% endtab %}
{% endtabs %}
