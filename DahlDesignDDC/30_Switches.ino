	//--------------------------------------
  //---------PERIPHERALS START HERE-------
  //--------------------------------------
	  
	
  //--------------------------------------
  //---------PERIPHERALS END HERE---------
  //--------------------------------------	
	
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  pushButton(1,1);
  pushButton(1,2);
  pushButton(1,3);
  pushButton(1,4);
  pushButton(1,5);
  pushButton(1,6);
  pushButton(1,7);
  pushButton(1,8);

  pushButton(2,1);
  pushButton(2,2);
  pushButton(2,3);
  pushButton(2,4);
  pushButton(2,5);
  pushButton(2,6);
  pushButton(2,7);
  pushButton(2,8);

  PEC11(3,1,false);
  
  pushButton(3,3);
  pushButton(3,4);
  pushButton(3,5);
  pushButton(3,6);
  pushButton(3,7);
  pushButton(3,8);
  
  pushButton(4,1);
  pushButton(4,2);
  pushButton(4,3);
  pushButton(4,4);
  pushButton(4,5);
  pushButton(4,6);
  pushButton(4,7);
  pushButton(4,8);


  refreshRate();
  checkValue(A0);


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
