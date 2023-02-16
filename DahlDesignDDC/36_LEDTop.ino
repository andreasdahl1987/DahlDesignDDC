void LEDTop()
{
  
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
  */
  triggerLED(6,7,true,0xFF0000,40,true, true);


  LED1.show();

}
