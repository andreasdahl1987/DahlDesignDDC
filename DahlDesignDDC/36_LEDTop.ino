void LEDTop()
{
  if(LEDCounter == 0)
  {
    SimHubImport(); 
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
  */

  //--------------------------------------------------------
  //-----------------LED CALLS STARTS HERE------------------
  //--------------------------------------------------------

colorLED(8,24, 0xff00ff, 8);


  //--------------------------------------------------------
  //-----------------LED CALLS STOP HERE--------------------
  //--------------------------------------------------------

  }

  #if(LED1COUNT > 0 && !strip1Block)
    if(LEDCounter == 1)
    {
      LED1.show();
    }
  #endif
  #if(LED2COUNT > 0)
    if(LEDCounter == 2)
    {
      LED2.show();
    }
  #endif
  #if(LED3COUNT > 0)
    if(LEDCounter == 3)
    {
      LED3.show();
    }
  #endif
  #if(LED4COUNT > 0)
    if(LEDCounter == 4)
    {
      LED4.show();
    }
  #endif

}
