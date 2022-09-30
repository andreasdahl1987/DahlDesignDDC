//------------------------------
//-----------LOOP---------------
//------------------------------

void loop()
{

	//-------------------------
	//-----ESSENTIALS----------
	//-------------------------

	globalClock = millis();

	rotaryField = 0;
	buttonField = 0;
	matrix();

	runningPresets();

	//------------------------------------
	//---------SWITCHES START HERE--------
	//------------------------------------




	//------------------------------------
	//----------SWITCHES END HERE---------
	//------------------------------------


	Joystick.setZAxis(rotaryField - 32768);
	Joystick.setYAxis(buttonField - 32768);

	Joystick.sendState();
}
