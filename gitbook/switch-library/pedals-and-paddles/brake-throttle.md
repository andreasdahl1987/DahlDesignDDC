# Brake/throttle

#### brake()

{% tabs %}
{% tab title="Description" %}
Set up a device that output variable voltages, typically a load cell, hall sensor or potentiometer, to controll the brake joystick axis. Should be wired [like this](../../2.-wiring/analog-wiring.md). It is considered an analog switch, and will have to be assigned a[ switch number](../../1.-project-planning/analog-inputs.md) and you'll have to[ read out](../../1.-project-planning/analog-inputs.md#reading-a-value) some values to [calibrate](./) it.&#x20;

Is also available with a [filter](filtered-curves.md).
{% endtab %}

{% tab title="Example" %}
`void brake(int analogPin, int switchNumber, int releasedValue, int fullyPressedValue)`

For a potentiometer with its center pin connected to A3, assigned switch# 4, it could look like this:

`brake(A3, 4, 0, 1023);`
{% endtab %}

{% tab title="Requirements" %}
* None


{% endtab %}
{% endtabs %}

#### throttle()

{% tabs %}
{% tab title="Description" %}
Set up a device that output variable voltages, typically a hall sensor or potentiometer, to controll the throttle joystick axis. Should be wired [like this](../../2.-wiring/analog-wiring.md). It is considered an analog switch, and will have to be assigned a[ switch number](../../1.-project-planning/analog-inputs.md) and you'll have to[ read out](../../1.-project-planning/analog-inputs.md#reading-a-value) some values to [calibrate](./) it.&#x20;

Is also available with a [filter](filtered-curves.md).
{% endtab %}

{% tab title="Example" %}
`void throttle(int analogPin, int switchNumber, int releasedValue, int fullyPressedValue)`

For a potentiometer with its center pin connected to A3, assigned switch# 4, it could look like this:

`throttle(A3, 4, 0, 1023);`
{% endtab %}

{% tab title="Requirements" %}
* None


{% endtab %}
{% endtabs %}
