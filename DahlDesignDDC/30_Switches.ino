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

	//------------------------------------
	//---------SWITCHES START HERE--------
	//------------------------------------







	//------------------------------------
	//----------SWITCHES END HERE---------
	//------------------------------------

	Joystick.setZAxis(rotaryField - 32767);
	Joystick.setYAxis(buttonField - 32767);

	Joystick.sendState();

}

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 2)
  void loop()
  {
    processCommands();
  }
#endif
