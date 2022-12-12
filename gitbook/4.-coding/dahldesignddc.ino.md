# DahlDesignDDC.ino

```
/*
 Name:		DahlDesignDDC.ino
 Author:	Andreas Dahl
*/

#include <Joystick.h>

#define BUTTONCOUNT 0
//Defining joystick parameters

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
    BUTTONCOUNT,    //Button count
    0,              //Hat switch count
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

The **only thing** you need to think about here is setting the `BUTTONCOUNT` to the amount of buttons you controller will output. If you have a 12-way switch and 8 buttons that will typically be 20 buttons. But depends on how you let DDC use them. Imporant to update this if you add more button numbers, or the buttons will not be included in the controller. 128 is the maximum amount.

Example: `#define BUTTONCOUNT 20`
