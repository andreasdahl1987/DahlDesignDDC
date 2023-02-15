void LEDTop()
{
  topActive = true;
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
  */
biteLED(0,0,1,50);

}
