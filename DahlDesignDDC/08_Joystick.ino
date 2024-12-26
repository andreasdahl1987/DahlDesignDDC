//-----------------------
//-------JOYSTICK--------
//-----------------------

#define BUTTONCOUNT 64
#define HATCOUNT 0

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
    BUTTONCOUNT,   //Button count
    HATCOUNT,      //Hat switch count
    true,          //X axis, used for clutch
    true,          //Y axis, used for button field
    true,          //Z axis, used for rotary field
    true,          //Rx axis, used for version field
    true,          //Ry axis, used for bite point posting
    true,          //Rz axis
	true,          //Slider1
	true,          //Slider2
    false,         //Rudder
    true,          //Throttle, used for dual clutch mode 4
    false,         //Accelerator
    true,          //Brake, used for dual clutch mode 4
    false);        //Steering
