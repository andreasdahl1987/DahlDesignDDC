void LEDTop()
{
#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
  if(LEDCounter == 0 || ecoTrig)
  {
    #if (ECOLED == 0)
    SimHubImport(); 
    #endif
//----------------------------------------------------------------------------
// ------------------------ LED CALLS START HERE------------------------------
//----------------------------------------------------------------------------

triggerLED(0, 1, RPM > 4500, 0x00ff00, 25);
triggerLED(2, 3, RPM > 5500, 0xffff00, 25);
triggerLED(4, 5, RPM > 6500, 0xffa500, 25);
triggerLED(6, 7, RPM > 7500, 0xff0000, 25);
triggerLED(0, 7, RPM > 8200, 0x0000ff, 25, false, true, 250, 250);

//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------

  }

  if (ecoTrig)
  {
    ecoTrig = false;
  }
#endif
  
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
