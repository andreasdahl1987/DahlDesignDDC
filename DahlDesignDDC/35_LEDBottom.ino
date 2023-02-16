void LEDBottom()
{
  if (!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER)
  {
  /*
   * These LED calls will overwrite LEDStartup, but in turn will be overwritten by SimHub LED control and again by LEDTop.
   * Whenever SimHub sends LED commands, the whole LED strip will be wiped black, not only the LEDs used by SimHub. 
   * When SimHub hasnt send LED commands for 1 second, LEDBottom will start working again
   */
   //LED CALLS STARTS HERE





  //LED CALLS STOP HERE

  #if(LED1COUNT > 0)
    LED1.show();
  #endif
  #if(LED2COUNT > 0)
    LED2.show();
  #endif
  #if(LED3COUNT > 0)
    LED3.show();
  #endif
  #if(LED4COUNT > 0)
    LED4.show();
  #endif
  
  }
}
