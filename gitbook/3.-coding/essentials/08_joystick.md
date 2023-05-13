# 08\_Joystick

```
//-----------------------
//-------JOYSTICK--------
//-----------------------

#define BUTTONCOUNT 64
#define HATCOUNT 0

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
    BUTTONCOUNT,   //Button count
    HATCOUNT,      //Hat switch count
    true,          //X axis, used for clutch
    true,          //Y axis, used for button mode field
    true,          //Z axis, used for encoder mode field
    false,         //Rx axis 
    true,          //Ry axis, used for bite point posting
    false,         //Rz axis 
    false,         //Rudder
    true,          //Throttle, used for dual clutch mode 4
    false,         //Accelerator
    true,          //Brake, used for dual clutch mode 4
    false);        //Steering
```

The **only thing** you need to think about here is setting the `BUTTONCOUNT` to the amount of buttons you controller will output and setting `HATCOUNT` to the number of hat switches you're planning to use (a typical hat switch like the Alps multi-direction switches dont have to be set up as a hat switch, it can be set up as a collection of pushbuttons if you prefer).&#x20;

The button count by default is set to 64. If not using all 64 button numbers, that's not a problem. However, your controller will be identified as a 64 button controller by windows, so there will be a bunch of buttons that are never used. Again, doesn't matter, it is just a bit untidy. Feel free to set the button count to whatever your actual count is. If you have more than 64 button numbers used and don't increase the count, those buttons are pressed out in space somewhere and will never be registered by Windows. 128 is maximum.&#x20;

If you have a 12-way switch and 8 buttons that will typically be 20 buttons. But depends on how you let DDC use them. You could have the 12-way switch use 36 button numbers, and your pushbuttons not using any - just be used for features and functions. The point is, this number does not reflect how many switches you controller has, just how many button numbers is uses.&#x20;



Example:&#x20;

`#define BUTTONCOUNT 20`&#x20;

`#define HATCOUNT 0`
