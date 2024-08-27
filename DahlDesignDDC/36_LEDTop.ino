void LEDTop()
{
  if(LEDCounter == 0)
  {
    SimHubImport(); 
//----------------------------------------------------------------------------
// ------------------------ LED CALLS START HERE------------------------------
//----------------------------------------------------------------------------


triggerLED(0,14,modButtonPressed(),0x000000,0,false);
triggerLED(5,9,modButtonPressed(),0xff8000,30,false,true,500,500);



//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------

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
