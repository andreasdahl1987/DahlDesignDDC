void LEDBottom()
{

    /*
   * These LED calls will overwrite LEDStartup, but in turn will be overwritten by SimHub LED control and again by LEDTop.
   * Whenever SimHub sends LED commands, the whole LED strip will be wiped black, not only the LEDs used by SimHub. 
   * When SimHub hasnt send LED commands for 1 second, LEDBottom will start working again
   */

//----------------------------------------------------------------------------
// ------------------------------- STRIP #1-----------------------------------
//----------------------------------------------------------------------------

  #if(LED1COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED1PRIVATE == 1)
    {
    //LED CALLS STARTS HERE





    //LED CALLS STOP HERE
    }
  #endif

//----------------------------------------------------------------------------
// ------------------------------- STRIP #2-----------------------------------
//----------------------------------------------------------------------------

  #if(LED2COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED2PRIVATE == 1)
    {
    //LED CALLS STARTS HERE





    //LED CALLS STOP HERE
    }
  #endif

//----------------------------------------------------------------------------
// ------------------------------- STRIP #3-----------------------------------
//----------------------------------------------------------------------------

  #if(LED3COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED3PRIVATE == 1)
    {
    //LED CALLS STARTS HERE





    //LED CALLS STOP HERE
    }
  #endif

//----------------------------------------------------------------------------
// ------------------------------- STRIP #4-----------------------------------
//----------------------------------------------------------------------------

  #if(LED4COUNT > 0)
    if ((!Serial.available() && globalClock - LEDSerialDropout > DROPOUTTIMER) || LED4PRIVATE == 1)
    {
    //LED CALLS STARTS HERE





    //LED CALLS STOP HERE
    }
  #endif
}
