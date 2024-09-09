# PWM / Circuit control

DDC allows you to use PWM to control analog circuits, including motors, fans, generic LEDs, buzzers, etc. You can also use it as a on/off switch for a different circuit.&#x20;

<figure><img src="../.gitbook/assets/image (4) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

PWM (Pulse Width Modulation) is a way for you digital microcontroller to emulate an analog signal. It can't really produce any voltages other than 0V and 5V (or 3.3V in some cases), but it can do some magic with those voltages. Switching the voltage from 0 to 5 and back again, repeatedly, really fast, will mimic something inbetween 0 and 5 volts.&#x20;

Think of it like a spinning ball which is half blue and half yellow. If it spins fast enough it looks green. At the same time, if the ball is 1/4 yellow and 3/4 blue, it will appear as teal. And if it is 3/4 yellow and 1/4 blue it will appear as moss green.&#x20;

To mimic 2.5V, the PWM signal will be 0 half of the time and 5V half of the time (50% duty cycle). To mimic 3.75V, the PWM signal will be 0 25% of the time, and 5V 75% of the time (75% duty cycle).&#x20;

<figure><img src="../.gitbook/assets/image (18).png" alt="" width="375"><figcaption></figcaption></figure>

In DDC you'll set up PWM channels, one PWM compatible microcontroller pin per channel. You'll be able to manipulate the PWM signal with your buttons, toggles, rotary encoders and just plain software - having the PWM change or trigger when certain conditions are met. Not all microcontroller pins can offer PWM, so read the pinout for your controller.&#x20;
