# Conditional coding

You might feel like the biggest disadvantage of using DDC is the lack of a GUI setup tool. I can agree. However, it is also one of the biggest advantages. You're _**in**_ the firmware, and you can make it jump and dance the way you ask it to.&#x20;

Since we're in the IDE, writing in the firmware code, we can use all sorts of code around the existing switch functions to enhance the controller. [Conditional statements](https://en.wikipedia.org/wiki/Conditional\_\(computer\_programming\)) is a fairly straight forward system to approach even with no coding experience. The end result will be a setup where the controller will work like **this** - if certain conditions are met, and work in **another way** if other conditions are met.&#x20;

To make conditional statements easier to work with in the firmware, I've made [trigger ](triggers.md)and [editor](editors.md) functions.&#x20;

* Triggers will look for certain things in the firmware and return `true` or `false`.&#x20;
* Editors will allow you to change values, such as switch modes and button numbers.&#x20;

The most relevant place to use conditional statements, triggers and editors is in 30\_Switches.ino.&#x20;

_**Here are some examples:**_

### Using 12-position switch to change the function of a pushbutton

```
//------------------------------------
//---------SWITCHES START HERE--------
//------------------------------------

rotaryAnalogSimple(A3, 1, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);
rotaryAnalogSimple(A0, 2, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023, false);

if (rotaryPosition(1,12))
{
    modButton(1,3);
}
else if (rotaryPosition(1,11))
{
    biteButton(1,3);
}
else if (rotaryPosition(1,10))
{
    launchButton(1,3);
}
else
{
    pushButton(1,3);
}

//------------------------------------
//----------SWITCHES END HERE---------
//------------------------------------

Joystick.setZAxis(rotaryField);
Joystick.setYAxis(buttonField);

Joystick.sendState();

}

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 2)
  void loop()
  {
    processCommands();
  }
#endif

```

In this example we've got 3 switches:

* 12-position rotary switch connected to pin A3, assigned switch number 1
* 12-position rotary switch connected to pin A0, assigned switch number 2
* Pushbutton on row 1 column 3

The rotary on A0 will just do its thing, but we'll be using the rotary on pin A3 to modify the pushbutton.&#x20;

The _**if - statement**_ looks like this:

```
if (statement)
{
    Whatever is between these backets will be executed if statement is true
}
If statement is fase, whatever is between the bracket will be ignored.
```

The [trigger](triggers.md) `rotaryPosition()` will require the switch number of the rotary and a position of that rotary. For instance `rotaryPosition(2,11).` This will look at switch number 2 and check if the switch is in position 11. It is either true or false.

So :

```
if(rotaryPosition(2,11))
{
    This will be executed if rotary switch with switch number 2 is in position 11.
}
```

Next the _**else if - statement**_ looks like this:

<pre><code><strong>if (statement1)
</strong>{
    Whatever is between these backets will be executed if statement is true.
    In that case, all following else if or else - statements are ignored.
}
else if (statement2)
{
    If statement1 was false, we'll move on to the else if and check statement2.
}
else if (statement3)
{
    If statement1 AND statement2 were false, we'll end up here checking statement3.
}
</code></pre>

To finish it off, we can add an _**else - statement**_ in the end if we feel like it:

```
if (statement1)
{
    Whatever is between these backets will be executed if statement is true.
    In that case, all following else if or else - statements are ignored.
}
else if (statement2)
{
    If statement1 was false, we'll move on to the else if and check statement2.
}
else if (statement3)
{
    If statement1 AND statement2 were false, we'll end up here checking statement3.
}
else
{
    If all prior statements were false, we'll end up here at the bottom of the pile.
    No statement is needed here, this will be executed as long as all prior
    statements were false.
}
```

Taking what we learned from this, we can see that the example with the rotary and the pushbutton will do the following:

* If the rotary is in position 12, the pushbutton will be a modButton
* If the rotary is in position 11, the pushbutton will be a biteButton
* If the rotary is in position 10, the pushbutton will be a launchButton
* In every other position (1 - 9) the pushbutton will be a regular pushbutton.

### Using modButton to duplicate a switch

Using what we learned from the example above, the following should be possible to understand:

```
//------------------------------------
//---------SWITCHES START HERE--------
//------------------------------------

modButton(2,3);

if(modButtonPressed())
{
  setButtonNumber(1,4,25);
}
else
{
  setButtonNumber(1,4,23);
}

rotary2Inc(1,4,false);

//------------------------------------
//----------SWITCHES END HERE---------
//------------------------------------

Joystick.setZAxis(rotaryField);
Joystick.setYAxis(buttonField);

Joystick.sendState();

}

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 2)
  void loop()
  {
    processCommands();
  }
#endif
```

The example above creates a duplicate of the rotary2Inc switch when the modButton is pressed:

* First, switch on row 2 column 3 is made modButton
* Then, we're checking of modbutton is pressed.&#x20;
* setButtonNumber() will change the button number that is associated with a switch on a given row/column. Here, we're looking at the switch on row 1 column 4, setting button number to 25 if mod button is pressed. If not pressed, it is set to 23.
* The switch on row 1 column 4 is a rotary encoder, which is using columns 4 and 5 on that row. It also uses two button numbers; the button number set on row 1 column 4, as well as that button number + 1.&#x20;
* In the end, the switch function for the rotary encoder is called; rotary2Inc()

The end result is that the rotary2Inc will send the button pressed produced by the switch to buttons 23/24 when modButton is not pressed, and to buttons 25/26 when modButton is pressed. You can do the same with pushbutton and even multiposition switches - making two or more 12-position switches out of the same switch.&#x20;

### Making neutral button work only on when holding downshift paddle

This might be a good safety feature, or it might be a dediculous example. None the less, it is an example:

<pre><code>//------------------------------------
//---------SWITCHES START HERE--------
//------------------------------------

<strong>pushButton(3,1);
</strong>
if(buttonPressed(3,1))
{
  setSwitchMode(2,2,0);
}
else
{
  setSwitchMode(2,2,1);
}

neutralButton(2,2);

//------------------------------------
//----------SWITCHES END HERE---------
//------------------------------------

Joystick.setZAxis(rotaryField);
Joystick.setYAxis(buttonField);

Joystick.sendState();

}

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 &#x26;&#x26; BOARDTYPE == 2)
  void loop()
  {
    processCommands();
  }
#endif
</code></pre>

In this example our downshift paddle is on row 3 column 1, and our neutral button is on row 2 column 2. The neutral button fuction has two modes. In mode 0 it is a neutral button, in mode 1 it works like a regular pushbutton.&#x20;

This setup first makes the paddle a pushbutton, then looks of the paddle is pressed. If it is pressed, it will set the switch mode of the switch we're using for neutral button to 0, meaning it will be in neutral button mode. If the paddle is not pressed, it will be in mode 1 - the regular button mode.

The end result is a neutral button that only works if the downshift paddle is held. If not held, the neutral button will work like a regular button, and can be mapped to other things in the sim.&#x20;
