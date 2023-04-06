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
  
  #if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
    LEDBottom();
      #if(BOARDTYPE == 0)
        processCommands();
      #endif
    LEDTop();
  #endif

  rotaryField = 0;
  buttonField = 0;
  
  shiftRegisterScan();

  matrix();

  runningPresets();

  #if (USING_CB1 == 1)
    #if (CB1_PE1 == 1)
    PCA9555CB1(0x21, 16, 1);
    #endif
    #if (CB1_PE2 == 1)
    PCA9555CB1(0x20, 8, 3);
    #endif
    #if (CB1_ADC1 == 1)
    ADC1_CB1(0);
    #endif
    #if (CB1_ADC2 == 2)
    ADC2_CB1(0);
    #endif
    CB1switchTable();
  #endif
  
  globalCounter ++;
