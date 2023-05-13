# Hybrid rotary

<figure><img src="../../.gitbook/assets/image (2) (2) (1).png" alt=""><figcaption></figcaption></figure>

* The idea if the hybrid system is a rotary that holds a button number. Rotating CW or CCW will increase or decrease the button number. The In the case above, it counts to 15, but any number of positions can be set. Then, a button set up with a hybridButton() function can be pressed to lock the position of the rotary, and then the rotary can be used to make button pulses on CW and CCW rotation - while still holding the button number it was holding before hybridButton was pressed.&#x20;
* In the example above, the rotary has been rotated to position 4, then hybrid button pressed. The switch is still producing a continous button 4 press, but will in addition give pulses of button number 16 on CCW rotation and 17 on CW rotation.&#x20;
* In iRacing, which allows key combinations as bindings, you can use this to map several adjustments that are typically increase/decrease to this switch. In the case above, the switch has 30 combinations. 1+16, 1+17, 2+16, 2+17, 3+16, 3+17, etc.&#x20;
* The function works really elegantly with a encoder that has integrated push button.&#x20;
* The biggest downside is that the position of the physical switch will not be in sync with button numbers pressed, so there is no point in labeling the controller with switch positions. You can however make a graphic in your dashboard (at least when using SimHub) that reflects the switch position, using the joystick button number properties.&#x20;

The various hybrid functions are listed under their respective encoder/rotary categories, <mark style="background-color:blue;">highlighted blue.</mark>&#x20;
