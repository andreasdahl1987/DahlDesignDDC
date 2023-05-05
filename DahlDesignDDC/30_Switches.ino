  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  rotaryAnalogBrightness(ADC10,1,2,60, 490, 3450,6300, 9270, 12200, 15000, 18000, 20900, 23900, 26800,29700,32600,false);
  analogInjectSingle(ADC10, 3, 1, 10000,14000,10);
  pushButton(3,1);
  presetButton(3,4);
  biteButton(3,3);
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
