//-----------------------
//-------JOYSTICK--------
//-----------------------

#define BUTTONCOUNT 32
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
