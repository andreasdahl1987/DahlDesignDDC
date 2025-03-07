//------------------------------
//-----------LOOP---------------
//------------------------------

#if(BOARDTYPE == 2)
void loop1()
{
#else
void loop()
{
#endif
  //-------------------------
  //-----ESSENTIALS----------
  //-------------------------
  globalClock = millis();
  globalCounter++; //Counter for refreshRate()
  
  #if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
    refreshLEDcalc();
    #if(BOARDTYPE == 0)
      processCommands();
    #endif
    #if(ECOLED == 0)
    LEDBottom();
    #endif
    LEDTop();
  #endif

  rotaryField = 0;
  buttonField = 0;
  
  EEPROMchanges(); //Look for changes to write to EEPROM

  shiftRegisterScan(); //Scan shift registers if preset

  matrix(); //Scan matrix wired switches

  runningPresets(); //Presets in the loop

  #if(ENABLE_MOUSE == 1)
  mouseUpdates();
  #endif

  #if (PWMENABLED == 1 || ROW6_PWMCOUNT > 0) //PWM Control
  PWMrun();
  #endif

  #if (USING_CB1 == 1)
    #if (CB1_PE1 == 1 && CB1_PE1_OUTPUT == 0)
    PCA9555CB1(0x21, 16, 1);
    #endif
    #if (CB1_PE2 == 1 && CB1_PE2_OUTPUT == 0)
    PCA9555CB1(0x20, 8, 3);
    #endif
    #if (CB1_ADC1 == 1)
    ADC1_CB1(14);
    #endif
    #if (CB1_ADC2 == 1)
    ADC2_CB1(15);
    #endif
    CB1switchTable();
  #endif

  //OUTPUT FEED

  #if (PCA9555_OUTPUT == 1)
  for (int i = 0; i < PCA9555outputCount; i++)
  {
      PCA9555Output(i);
  }
  #elif (USING_CB1 == 1 && (CB1_PE1_OUTPUT == 1 || CB1_PE2_OUTPUT == 1))
    #if(CB1_PE1_OUTPUT == 1)
    CB1_OUTPUT1();
    #endif
    #if(CB1_PE2_OUTPUT == 1)
    CB1_OUTPUT2();
    #endif
  #endif

  #if (enableOutput == 1)
  directOutput();
  #endif
  outputHubRun();

  

 
