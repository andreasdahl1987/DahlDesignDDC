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
    PCA9555CB1(0x21, 16, 1);
    PCA9555CB1(0x20, 8, 3);
    ADS1115Run(1,4,7,2);
    ADS1115Run(2,4,7,1);
  #endif
