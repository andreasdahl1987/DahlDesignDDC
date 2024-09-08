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
