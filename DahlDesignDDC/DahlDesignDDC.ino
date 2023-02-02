//------------------------
//---------BOARD----------
//------------------------

#define BOARDTYPE 0

#if (BOARDTYPE == 0)
  #include <DDC32U4.h>
#elif (BOARDTYPE == 1)
  #include <DDCSAMD.h>
#elif (BOARDTYPE == 2)
  #include <DDCPI.h>
#endif

//-----------------------
//-------JOYSTICK--------
//-----------------------

#define BUTTONCOUNT 0
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

#define VID_PI 0x35f9
#define PID_PI 0x0DDC
#define MAKER "Andreas Dahl"
#define CONTROLLER_NAME "Dahl Design Controller"
    
