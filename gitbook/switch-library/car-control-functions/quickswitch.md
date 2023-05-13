# QuickSwitch

Have you noticed the toggles at the back of F1 wheels? &#x20;

<figure><img src="../../.gitbook/assets/image (1) (3).png" alt=""><figcaption></figcaption></figure>

Drives use these to quickly change a number of settings. For instance engine braking and bias before a hard braking zone, or differential settings before a corner complex.&#x20;

The QuickSwitch system uses a [quickRotary](../rotary-switches/quickrotary.md) and a quickSwitch to do the same thing. The quickRotary is a multiposition switch that you'll map to an in-car setting. Lets say you map it to traction control. If the quickSwitch is pressed, the position of the multiposition switch will be software overridden, and it will be set to the value you have set up the quickSwitch to. This can be adjusted per [preset. ](../../3.-coding/advanced/presets/)Press again and you'll to back to the physical position of the quickRotary. For example, by having the quick switch setting the TC and ABS to full, you can use the quickSwitch as a "WET" button.&#x20;

#### quickSwitch()

{% tabs %}
{% tab title="Description" %}
Overrides **quickRotary1 - 4** with their respective quickValues (found in 41\_Presets.ino).&#x20;

Modes:

* 0: QuickSwitch
* 1: Normal momentary button

QuickSwitch mode defaults to button field 8 -> \[DahlDesign.DDCquickSwitchMode]

QuickSwitch on/off defaults to buttion field 9 -> \[DahlDesign.DDCquickSwitchActive]
{% endtab %}

{% tab title="Example" %}
`void quickSwitch(int row, int col)`

For a switch on row 3 column 5 -> `quickSwitch(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* modButton() to change modes
{% endtab %}
{% endtabs %}

#### quickSwitch12()

{% tabs %}
{% tab title="Description" %}
Overrides **quickRotary1** and **quickRotary2** with their respective quickValues (found in 41\_Presets.ino).&#x20;

Modes:

* 0: QuickSwitch
* 1: Normal momentary button

QuickSwitch mode defaults to button field 8 -> \[DahlDesign.DDCquickSwitchMode]

QuickSwitch on/off defaults to buttion field 9 -> \[DahlDesign.DDCquickSwitchActive]
{% endtab %}

{% tab title="Example" %}
`void quickSwitch12(int row, int col)`

For a switch on row 3 column 5 -> `quickSwitch12(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* modButton() to change modes
{% endtab %}
{% endtabs %}

#### quickSwitch34()

{% tabs %}
{% tab title="Description" %}
Overrides **quickRotary3** and **quickRotary4** with their respective quickValues (found in 41\_Presets.ino).&#x20;

Modes:

* 0: QuickSwitch
* 1: Normal momentary button

QuickSwitch mode defaults to button field 8 -> \[DahlDesign.DDCquickSwitchMode]

QuickSwitch on/off defaults to buttion field 9 -> \[DahlDesign.DDCquickSwitchActive]
{% endtab %}

{% tab title="Example" %}
`void quickSwitch34(int row, int col)`

For a switch on row 3 column 5 -> `quickSwitch34(3,5);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* modButton() to change modes
{% endtab %}
{% endtabs %}
