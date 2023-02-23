void LEDTop()
{
  
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
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
