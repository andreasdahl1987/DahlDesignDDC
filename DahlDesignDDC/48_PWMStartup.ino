#if (PWMENABLED == 1 || ROW6_PWMCOUNT > 0)
void PWMSetup()
{

  /*
  *Here you'll typically use PWMSetup() for all channels that you want to change from default values.
  *Default values are:
  * - Volume set to 25%
  * - Full range PWM (0-255)
  * - Channel is set to OFF
  * This will be set on boot, and wont overwrite anything that happens while the firmware is running. 
  */

   //PWM setup CALLS STARTS HERE





  //PWM setup CALLS STOP HERE

}
#endif
