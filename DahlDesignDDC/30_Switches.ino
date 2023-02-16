//------------------------------
//-----------LOOP---------------
//------------------------------

void loop()
{
	//-------------------------
	//-----ESSENTIALS----------
	//-------------------------
	globalClock = millis();

  #if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 0)
	processCommands();
  #endif
  
  LEDBottom();
  LEDTop();

	rotaryField = 0;
	buttonField = 0;

	shiftRegisterScan();

	matrix();

	runningPresets();



	//------------------------------------
	//---------SWITCHES START HERE--------
	//------------------------------------

matrixInject(27,1,1);
matrixInject(26,1,2);
matrixInject(22,1,3);
	//------------------------------------
	//----------SWITCHES END HERE---------
	//------------------------------------

biteButton(1,1);
DDSfunky(1,2,3);

	Joystick.setZAxis(rotaryField - 32767);
	Joystick.setYAxis(buttonField - 32767);

	Joystick.sendState();

}

#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 2)
  void loop1()
  {
    processCommands();
  }
#endif
