void LEDBottom()
{

    /*
   * These LED calls will overwrite LEDStartup, but in turn will be overwritten by SimHub LED control and again by LEDTop.
   * Whenever SimHub sends LED commands, the whole LED strip will be wiped black, not only the LEDs used by SimHub. 
   * When SimHub hasnt send LED commands for 1 second, LEDBottom will start working again
   */

//----------------------------------------------------------------------------
// ------------------------ LED CALLS STARTS HERE-----------------------------
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------



 
}
