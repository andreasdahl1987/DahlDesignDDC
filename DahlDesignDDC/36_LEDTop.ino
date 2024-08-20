void LEDTop()
{
  
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
  */
SimHubImport();

  //LED CALLS STARTS HERE


colorLED(8,24, 0xff00ff, 8);


  //LED CALLS STOP HERE

delayMicroseconds(200);

  #if(LED1COUNT > 0 && !strip1Block)
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
