# DDS

DDS (Dahl Design Switch) switches are tailored for the Dahl Design iRacing [Dashboard](https://app.gitbook.com/o/Gk9mLLIOB4bOKrDCqIdJ/s/49tDWuDHhTQtCQdHWIW5/), but can of course be used any way you like, if it fits your projects. It is a function that takes a rotary switch and two pushbuttons to create a 26-position switch complex that is ideal for a menu system.&#x20;

<figure><img src="../.gitbook/assets/image (1).png" alt=""><figcaption></figcaption></figure>

In the example above, the switch has button numbers 1 to 26. It works like this:

* The rotary switch will scroll through numbers 1-12 OR numbers 13-24. A continous button press is produced.
* The DDButton will toggle between the two rows of 12 numbers. So if you're currently pressing "9" and hit the DDButton, you go to "21". If you're at "14" and press DDButton, you go to "2".&#x20;
* The hybridButton will lock the position the switch is currently in, and rotating the rotary now will give pulses of buttons 26/25 on CW/CCW rotation. Hitting hybridButton again will release back to being able to change the position.&#x20;
  * The state when the position is locked is refered to as "**closed hybrid**".
  * The state when position can move is refered to as "**open hybrid**".&#x20;

The DDS switches all have 4 modes, and this is automatically pushed to the bit fields for SimHub communication. It is available as the property \[DahlDesign.DDCDDSMode]:

* 0: Open hybrid
* 1: Closed hybrid
* 2 and 3 depends on the type of DDS function you use.

If your controller uses a DDS switch, you have to check for this in the properties [plugin menu](https://app.gitbook.com/s/d2E1GdYd97jTQlTu0Drn/introduction/plugin-menu).

The video below you can see how the DDS switch works together with the dashboard. Here, a funky switch alone has all the switches needed for the complex; including the rotary, DDButton and hybridButton.&#x20;

{% embed url="https://www.youtube.com/watch?t=372s&v=LvadQq7CFOc" %}

#### DDS2bit()

{% tabs %}
{% tab title="Description" %}
DDS for an encoder in the rotary2bit category.&#x20;

Modes:

* 0: Open hybrid
* 1: Closed hybrid
* 3: 4-position switch
* 4: Incremental encoder
{% endtab %}

{% tab title="Example" %}
`void DDS2bit(int row, int column, bool reverse)`

For a encoder on row 2 column 4+5 -> `DDS2bit(2,4, true);`

This switch has "reverese" set to true, since it is placed on the rear of the controller. Turning it CCW will not increase the count instead of reducing.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* modButton() if you want to change modes freely. modButton() not needed to change modes across presets.&#x20;
* DDButton() to swap between "layers" of 12 positions.
* hybridButton() to lock position and use rotary as incremental switch.
{% endtab %}
{% endtabs %}

#### b
