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


	Joystick.setZAxis(encoderField - 32768);
	Joystick.setYAxis(buttonField - 32768);

	Joystick.sendState();
}
