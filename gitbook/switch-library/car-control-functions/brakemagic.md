# BrakeMagic

If you didn't know about it before, everyone got introduced to "brake magic" during the 2021 Azerbaijan Grand Prix where Lewis Hamilton accidentally left his on and locked his front wheels into T1 afer safety car restart.&#x20;

For Lewis, the brake magic is a toggle that does a number of changes to brakes, particularily useful for keeping the front tires and brakes warm during safety car. In DDC, the brake magic is a system that applies a given percent of brake application when on. The amount can be adjusted on the fly, and can be defined in your presets.&#x20;

Brake magic requires the sim to support [secondary brake ](./)inputs. &#x20;

#### brakeMagic()

{% tabs %}
{% tab title="Description" %}
Use a toggle switch to turn brake magic on/off. Has 2 modes.

* 0: Brake magic
* 1: Pulsing toggle switch

The amount of brake application given can be read from the controllers brake axis. Brake magic on/off defaults to button field 7 for SimHub communication. It is returned as property \[DahlDesign.DDCmagicActive].&#x20;

Brake magic % is defined by the variable `brakeMagicValue` found in 41\_Presets.ino. It defaults to all presets with 50, which is 5%.&#x20;

Brake magic % can be adjusted on the fly with a [ThrottleHold](throttlehold.md) switch.&#x20;
{% endtab %}

{% tab title="Example" %}
`void brakeMagic(int row, int col)`

For a switch on row 3 column 5 -> `brakeMagic(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* Sim that supports secondary brake input
* 1 button number
{% endtab %}
{% endtabs %}
