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
    LEDBottom();
      #if(BOARDTYPE == 0)
        processCommands();
      #endif
    if(BOARDTYPE == 0 || (BOARDTYPE == 2 && !LEDlock ))
    {
      LEDTop();
    }
  #endif

  rotaryField = 0;
  buttonField = 0;
  
  EEPROMchanges(); //Look for changes to write to EEPROM

  shiftRegisterScan(); //Scan shift registers if preset

  matrix(); //Scan matrix wired switches

  runningPresets(); //Presets in the loop

  #if (USING_CB1 == 1)
    #if (CB1_PE1 == 1)
    PCA9555CB1(0x21, 16, 1);
    #endif
    #if (CB1_PE2 == 1)
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
  
 
