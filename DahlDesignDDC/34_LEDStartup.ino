void LEDStartup()
{

  /*
  *Here goes all LED calls that you only want to run on startup, or calls that only needs to be run on startup. 
  *Best suited for completely static lighting, such as backlighting. 
  *When connecting to SimHub, these LEDs will all be wiped black.
  *Any LED control that is done here instead of in LEDTop or LEDBottom will save a lot of processing power.
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
