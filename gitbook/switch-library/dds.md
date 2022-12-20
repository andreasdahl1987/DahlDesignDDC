# DDS

DDS (Dahl Design Switch) switches are tailored for the Dahl Design iRacing [Dashboard](https://app.gitbook.com/o/Gk9mLLIOB4bOKrDCqIdJ/s/49tDWuDHhTQtCQdHWIW5/), but can of course be used any way you like, if it fits your projects. It is a function that takes a rotary switch and two pushbuttons to create a 26-position switch complex that is ideal for a menu system.&#x20;

<figure><img src="../.gitbook/assets/image (1).png" alt=""><figcaption></figcaption></figure>

In the example above, the switch has button numbers 1 to 26. It works like this:

* The rotary switch will scroll through numbers 1-12 OR numbers 13-24. A continous button press is produced.
* The DDButton will toggle between the two rows of 12 numbers. So if you're currently pressing "9" and hit the DDButton, you go to "21". If you're at "14" and press DDButton, you go to "2".&#x20;
* The hybridButton will lock the position the switch is currently in, and rotating the rotary now will give pulses of buttons 26/25 on CW/CCW rotation. Hitting hybridButton again will release back to being able to change the position.&#x20;
  * The state when the position is locked is refered to as "**closed hybrid**".
  * The state when position can move is refered to as "**open hybrid**".&#x20;

The DDS switches all have 4 modes, and this is automatically pushed to the bit fields for SimHub communication. It is available as the property \[DahlDesign.DDCDDSMode]

If your controller uses a DDS switch, you have to check for this in the properties [plugin menu](https://app.gitbook.com/s/d2E1GdYd97jTQlTu0Drn/introduction/plugin-menu).
