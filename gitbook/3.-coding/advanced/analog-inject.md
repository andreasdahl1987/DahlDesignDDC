# Analog inject

Analog inject is a bridge between the two switch systems in DDC; the switch table and the analog switches.&#x20;

It will create a virtual switch in the row/column location of your choice. You'll set up a range of values and a threshold within this range that will turn the switch on/off when crossed.

<figure><img src="../../.gitbook/assets/image (4) (2).png" alt=""><figcaption></figcaption></figure>

When this is set up, you can use this switch like any other switch in the firmware; set it ut as modButton(), pushButton(), pushPull() or anything else.

Because these features can cause some issues when mapping or calibrating controllers in the sim, there is the option to <mark style="background-color:red;">deactivate all analog injects for 20 seconds by hitting the</mark> [<mark style="background-color:red;">modButton()</mark>](../../switch-library/function-button.md#modbutton) <mark style="background-color:red;">quickly 3 times.</mark>&#x20;

There are three versions:

### analogInject()

`analogInject(int8_t analogChannel, int8_t row, int8_t column, int startValue, int endValue, uint8_t threshold)`

analogChannel -> The analog channel this switch is tied to

row -> The row to build the virtual switch on

column -> The column to build the virtual switch on

startValue -> The starting value in the valid switch range

endValue -> The ending value in the valid switch range

threshold -> The placement of the threshold within the range. 0 - 100. A value of 20 will place the threshold close to the startValue. A value of 80 will place the threshold close to the endValue

The startValue can be higher than the endValue, that doesn't matter. The switch will be considered "on" when the value read from the pin is between the threshold value and the endValue.&#x20;

An example:

`analogInject(2, 5, 5, 242, 634, 25);`

<figure><img src="../../.gitbook/assets/image (2) (1) (1) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

In this case we're looking at a specific range in a potentiometer's rotation. The maximum and minimum values from the potmeter are 1022 and 3, respectively.  The function will place the switch on row 5 column 5, as in the top figure on this page. The values will be read from pin A1.&#x20;

### analogInjectSingle()

`analogInjectSingle(int8_t analogChannel, int8_t row, int8_t column, int startValue, int endValue, uint8_t threshold)`

<figure><img src="../../.gitbook/assets/image (86).png" alt=""><figcaption></figcaption></figure>

analogInjectSingle() is used exactly like analogInject() above, the difference being that the function will not look at the upper limit to determine whether the switch is on or not. This function is easier to use whenever you're making a single on/off switch, and not exploiting a part of the range in the analog signal. A good usage would be for hall sensor shifters.&#x20;

### rotaryInject()

`rotaryInject(int8_t analogChannel, int8_t switchPosition, int8_t row, int8_t column)`

While it is possible to use `analogInject()` to extract the positions of a multiposition switch and inject them into the switch table, the rotaryInject() function will make this a lot easier. The function takes the analog channel number for the switch, the desired position, and where to put it in the switch table.&#x20;

For instance, we could use a 12-position switch with [quickRotary1Bite()](../../switch-library/rotary-switches/quickrotary.md#quickrotary1bite) and inject the last two positions to the switch table. In this example row 6, columns 1 and 2. We'll them be using these two for [brakeMagic() ](../../switch-library/car-control-functions/brakemagic.md#brakemagic)for position 11 and [quickSwitch()](../../switch-library/car-control-functions/quickswitch.md#quickswitch) for position 12.&#x20;

<figure><img src="../../.gitbook/assets/image (57).png" alt=""><figcaption></figcaption></figure>

This way we can make an ABS rotary which is bound to ABS 1-9 in positions 1 to 9, ABS off in position 10, brake magic active in position 11, and position 12 a WET mode that uses the quickSwitch system to set your ABS, TC1, TC2 and engine map rotaries to predetermined values. The rotaryInject() really allows you to mix and match the features of the analog and digital switch systems to make hybrid solutions.&#x20;

### In the sketch

These functions are called in 30\_Switches.ino. And as with the [switchTableInject()](../essentials/30_switches.md#direct-wiring), it is recommended to call this function before calling the switch functions that will use the virtual switch. Like this:

```
//------------------------------------
//---------SWITCHES START HERE--------
//------------------------------------


analogInject(2, 5, 5, 242, 634, 25);
pushButton(5,5);

analogInjectSingle(3, 4, 2, 242, 634, 25);
modButton(4,2);

rotaryInject(4, 12, 4, 3);
brakeMagic(4,3);


//------------------------------------
//----------SWITCHES END HERE---------
//------------------------------------

Joystick.setZAxis(rotaryField - 32767);
Joystick.setYAxis(buttonField - 32767);

Joystick.sendState();

} //LOOP ENDS HERE

#if (BOARDTYPE == 2)
  void loop()
  {
	#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
		processCommands();
	#endif
  }
#endif
```



### What is it for?

These features gives a lot of freedom for creative solutions. Here are some ideas:

* Hall sensor button/paddle.
* Push/pull shifter using a single hall sensor set up with two analogInject() functions.
* Making a button that is pressed when your slave clutch is completely pressed. The button will toggle a launch screen on your dashboard. That way this will not trigger when only master clutch is pressed, and will only show up for launches.
* Making buttons out of specific switch positions on a multiposition rotary switch. For instance having modButton on position 12, brake magic on position 11, etc.
* Resistor ladder button chain; allowing to wire 20+ buttons to a single analog pin. Though, they can't be pressed simultaneously.&#x20;
* Automatic launch with a single clutch, setting it up to fire a launch button at the end of the travel.
* Make a potentiometer pulse a button press on rotation.
* Use a potentiometer as a multiposition switch without detents
* Use a slider potentiometer as a toggle swich.
* Incorporating touch, light and temperature sensors into your rig.&#x20;

