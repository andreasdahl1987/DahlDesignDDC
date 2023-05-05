  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  
  rotaryAnalog2Mode(ADC10,1,1, 490, 3450,6300, 9270, 12200, 15000, 18000, 20900, 23900, 26800,29700,32600,false);
  //rotaryInject(1,3,1,1);
  //rotaryInject(1,4,1,6);
  //pushButton(1,1);
  //pushButton(1,6);
  modButton(3,2);
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
