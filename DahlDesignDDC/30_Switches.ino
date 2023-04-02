	//--------------------------------------
  //---------PERIPHERALS START HERE-------
  //--------------------------------------

  ADS1115Run(1,4,7,1);
	
  //--------------------------------------
  //---------PERIPHERALS END HERE---------
  //--------------------------------------	
	
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  singleClutch(ADC1,1,17350, 6900);

  refreshRate();

  Serial.println(ADS1115value[0]);



  //--------------------------------------
  //---------SWITCHES END HERE------------
  //--------------------------------------

	Joystick.setZAxis(rotaryField - 32767);
	Joystick.setYAxis(buttonField - 32767);

	Joystick.sendState();

} //LOOP ENDS HERE

#if (BOARDTYPE == 2)
  void loop()
  {
	#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
		processCommands();
	#endif
  }
#endif
