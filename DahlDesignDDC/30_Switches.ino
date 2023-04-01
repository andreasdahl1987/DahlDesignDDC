	//--------------------------------------
  //---------PERIPHERALS START HERE-------
  //--------------------------------------

  ADS1115Run(0x48,1,4,7);
	
  //--------------------------------------
  //---------PERIPHERALS END HERE---------
  //--------------------------------------	
	
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------



  refreshRate();

  Serial.println(ADS1115value[0]);
  Serial.println(digitalRead(16));

  
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
