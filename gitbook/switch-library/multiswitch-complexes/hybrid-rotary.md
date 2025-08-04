# Hybrid rotary

<figure><img src="../../.gitbook/assets/image (2) (2) (1).png" alt=""><figcaption></figcaption></figure>

* The idea if the hybrid system is a switch that makes a continuous button press while at the same time giving button pulses when rotating CW / CCW. You can swap between using the encoder to select the continuous button input (hybrid open state) and to produce button pulses (hybrid closed state) by using a hybridButton(). In the example above, the switch outputs button 4 continuously and will pulse button 16 and 17 on CW and CCW rotation.&#x20;
* You can decide yourself how many different continuous outputs the switch should have.&#x20;
* In iRacing, which allows key combinations as bindings, you can use this to map several adjustments that are typically increase/decrease to this switch. In the case above, the switch has 30 combinations. 1+16, 1+17, 2+16, 2+17, 3+16, 3+17, etc.&#x20;
* The function works really elegantly with a encoder that has integrated push button.&#x20;
* The biggest downside is that the position of the physical switch will not be in sync with button numbers pressed, so there is no point in labeling the controller with switch positions. You can however make a graphic in your dashboard (at least when using SimHub) that reflects the switch position, using the joystick button number properties.&#x20;

The various hybrid functions are listed under their respective encoder/rotary categories, <mark style="background-color:blue;">highlighted blue.</mark>&#x20;
