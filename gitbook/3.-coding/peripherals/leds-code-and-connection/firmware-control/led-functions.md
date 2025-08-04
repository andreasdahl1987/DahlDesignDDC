# LED functions

LED functions is the way you control your LEDs. There are two basic functions and some specific functions. The two basic ones are:

* colorLED()
* triggerLED()

These two alone will give you the freedom to do pretty much anything. The more tailored functions are a bit more limiting, but will do in one function what you'd need 20 triggerLED() functions to do.&#x20;

**There are specific functions that act on specific LED strips. colorLED() works on strip one. colorLED3() work on strip 3. triggerLED2() works on strip 2, etc.**&#x20;

Besides from the functions included in DDC, you can address the LED strips with commands from the Neopixel library as well. The LED strips are named LED1, LED2, LED3 and LED4. See list of commands [here.](https://github.com/adafruit/Adafruit_NeoPixel#functions)&#x20;

#### colorLED()

{% tabs %}
{% tab title="Description" %}
Allows you to set the color and brightness of one or more LEDs.&#x20;
{% endtab %}

{% tab title="Example" %}
`void colorLED(startLED, stopLED, color, brightness)`

To make LED 5 to 9 plain blue with a brightnes of 50%:

`colorLED(5,9,0x0000FF,50);` or `colorLED(5,9,BLUE,50);`
{% endtab %}

{% tab title="Requirements" %}
* 1 or more LEDs
{% endtab %}
{% endtabs %}

#### triggerLED()

{% tabs %}
{% tab title="Description" %}
Allows you to set the color and brightness of one or more LEDs under certain conditions. Also has the options of keeping all its LEDs cleared when not used, and to activate blinking.&#x20;

To get access to things happening in the firmware and use this as a condition, there are [triggers](../../../advanced/conditional-coding/triggers.md) you can use. These will return `true` under certain conditions.&#x20;
{% endtab %}

{% tab title="Example" %}
`void triggerLED(startLED, stopLED, condition, color, brightness, clearLEDs, blinkEnable, blinkOnTimer, blinkOffTimer)`

`Typed out and explained:`

```
triggerLED(
0, //------------Starting on LED number 0
4, //------------Ending on LED 4, including LEDs 0-4
modButtonPressed(), //-------------Light the LED of this is true
0xFF0000, //-----Red color
80, //-----------Relative brightness 80%
false, //--------Will not clear LEDs when conditions are not met
true,  //--------Will blink
300,   //--------Will stay lit for 300 ms on blinking
2000); //--------Will turn off LED for 2000 ms on blinking
```

* If you want the function to be always active, simply write `true` for the condition.&#x20;
* As default, brightness is set to 100, clearLEDs and blinkEnable is set to true. blinkOnTime and blinkOffTimer is set to 500 ms. If you dont fill in anything for these values, defaults will be used.&#x20;

So in case you want LEDs 7-10 turn magenta with 100% relative brightness when modButton is pressed:&#x20;

`triggerLED(7,10,modButtonPressed(),MAGENTA);`
{% endtab %}

{% tab title="Requirements" %}
* 1 or more LEDs
{% endtab %}
{% endtabs %}

#### biteLED()

{% tabs %}
{% tab title="Description" %}
Premade solution for using LED indication on setting the bite point, typically the rev light streip. It requres at least 10 LEDs in a chain

* You'll set a single or multiple LEDs to blink at a certain color when bite point setting is active.&#x20;
* A chain of 10 LEDs will represent numbers 0 to 10 (0 being none lit) that changes color as you move through the stages of setting the bite point.&#x20;
{% endtab %}

{% tab title="Example" %}
`void biteLED(`biteEngageStartLED, biteEngageStopLED, engageBrightness, biteChainStartLED, biteBrightness, engageColor, step1Color , step2Color, step3Color, engageBlink)

`Typed out and explained:`

```
biteLED(
3, //------------Bite setting indicator starts on LED number 3
3, //------------Ending on LED number 3, i.e. including only LED number 3.
25, //-----------Relative brightness of indicator set to 25%
24, //-----------The 10-LED chain starts on LED nummber 24. Will include LEDs 24-33.
80, //-----------Relative brightness of bite value LEDs set to 80%
0xFF0000, //------Bite setting indicator is red.
0X00FF00, //------Bite value indicators are green on setting with increments of 10.
0X0000FF, //------Bite value indicators are blue on setting with increments of 1
0X802090, //------Bite value indicators are purple on setting with increments of 0.1
true);  //--------Engage indicator will blink

```

* As a default, engageColor is set to orange, steps 1 -3 are teal - purple - orange and engageBlink is set to true. If you dont fill in anything for these values, defaults will be used:

`biteLED(5,8,30,16,60);`
{% endtab %}

{% tab title="Requirements" %}
* 10 or more LEDs
{% endtab %}
{% endtabs %}

#### rotaryLED()

{% tabs %}
{% tab title="Description" %}
Ties x amount of LEDs to a x-position [rotary switch](../../../../switch-library/rotary-switches/). The idea being that the LED will indicate the position of the switch. As the option to offset and reverse the LED direction, so it should always be able to match the switch position.&#x20;
{% endtab %}

{% tab title="Example" %}
void rotaryLED(switchNumber, startLED,  positions, color, brightness,  offset, reverse, backgroundColor, backgroundBrightness)

Typed out and explained:

```
rotaryLED(
2, //------------Tie to analog switch # 2
0, //------------Starting on LED number 0
12, //-----------This is a 12 position switch. LED numbers 0-11 will be used.
0x0000FF //------Blue color
80, //-----------Relative brightness 80%
0, //------------No offset
true, //---------Direction reversed
0xFF0000, //-----Background color red, optional
40);  //---------Relative background brightness 40%, optional


```

* The offset allows you to match the LED and the switch position. If your first LED surrounding the rotary switch is at the bottom, looping around the top - and the first switch position is at the top, you'll need some offset. Ranges from 0 to \<position -1>. So in the case above, from 0 to 11. A value of 1 will more it 1 position clockwise, a position of 11 will more it 11 positions clockwise (or 1 positions counter-clockwise).&#x20;
* The reverse setting will allow you to change the direction of the LED loop around the rotary switch, in case you circled it the wrong way.&#x20;
* The background color and brightness is optional to fil in, by default black and 25%.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* As many LEDs as positions on your switch.
{% endtab %}
{% endtabs %}
