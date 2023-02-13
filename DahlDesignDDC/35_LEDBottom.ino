void LEDBottom()
{
  /*
   * These LED calls will overwrite LEDStartup, but in turn will be overwritten by SimHub LED control and again by LEDTop.
   * Whenever SimHub sends LED commands, the whole LED strip will be wiped black, not only the LEDs used by SimHub. 
   * When SimHub hasnt send LED commands for 1 second, LEDBottom will start working again
   */

   triggerLED(3,5,true,0xFF0000,30, false, false, 200, 1000);

   
}
