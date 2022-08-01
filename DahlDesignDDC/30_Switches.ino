//------------------------------
//-----------LOOP---------------
//------------------------------

void loop()
{

	//-------------------------
	//-----ESSENTIALS----------
	//-------------------------

	globalClock = millis();

	encoderField = 0;
	buttonField = 0;
	matrix();

	//------------------------------------
	//---------SWITCHES START HERE--------
	//------------------------------------




	//------------------------------------
	//----------SWITCHES END HERE---------
	//------------------------------------


	Joystick.setZAxis(encoderField - 32767);
	Joystick.setYAxis(buttonField - 32767);

	Joystick.sendState();
}
