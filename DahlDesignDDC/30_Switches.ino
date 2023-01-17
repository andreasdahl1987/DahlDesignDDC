//------------------------------
//-----------LOOP---------------
//------------------------------

void loop()
{
	//-------------------------
	//-----ESSENTIALS----------
	//-------------------------
  #if (STRIP1_RGBLEDCOUNT + STRIP2_RGBLEDCOUNT + STRIP3_RGBLEDCOUNT + STRIP4_RGBLEDCOUNT > 0)
	processCommands();
  #endif

	globalClock = millis();

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
