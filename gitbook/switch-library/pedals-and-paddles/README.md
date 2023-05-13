# Pedals & paddles

Here we'll cover functions suited for the pedals for your feet and the paddles for your hands. Gear shift functions, clutch systems, brake, throttle and more.&#x20;

### Calibration

An important topic is the calibration of an analog axis. While you can calibrate joystick axis in Windows, I cannot recommend it. DDC's algorithms have chackpoints that trigger then pedals/paddles have been pressed to 100% and released to 0%. A lot of the more advanced features like Launch Button, mode changes, the different dual clutch configurations, etc. depend on this. That means the paddles/pedals should be calibrated in the firmware and no calibrations should be done in Windows.&#x20;

To calibrate the clutches, you'll have to read the values from the paddles when fully pressed and fully released, by using the [serial monitor. ](../../1.-project-planning/analog-inputs/#reading-a-value)

The values will often be a bit erratic. Most reliable readings are when the paddles are properly mounted and all elements of the controller that consumes power are powered up. Your readings might still be a bit erratic. The general idea is:

* Use the highest value that your read on your lowest value measurements
* Use the lower value that you read on your highest value measurements

So if your controller fluctuates between 864 - 873 when paddle is not pressed, and 436 - 444 when pressed, use the values 864 for not pressed and 444 for pressed.&#x20;

If one paddle has higher value on pressed than released and the other paddle is the opposide - it does not matter.The algorithms will take care of it.

### Deadzone&#x20;

A small deadzone is added to work as a buffer on both ends of the paddle range. You can increase the deadzone of  the clutches by adjusting the deadzone in 12\_GlobalVariables.ino.&#x20;



