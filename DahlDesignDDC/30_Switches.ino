  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  singleClutch(ADC9,1,14600, 8900);
  rotaryAnalog2Mode(ADC10,2, 1, 490, 3450,6300, 9270, 12200, 15000, 18000, 20900, 23900, 26800,29700,32600,false);


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
  #if(USING_CB1 == 1)
  CB1Oversampling();
  #endif
  }
#endif
