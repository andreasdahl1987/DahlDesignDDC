  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  launchButton(7,3,1);
  biteButton(7,4);
  modButton(3,5);
  toggleP(3,6);
  preset2Bit(3,1,false);
  funkyRotary(7,1,2, false);

  singleClutch(ADC7,1,11550,6850);
  rotaryAnalogSimple(ADC10,2, 490, 3450,6300, 9270, 12200, 15000, 18000, 20900, 23900, 26800,29700,32600,false);
  rotaryAnalogSimple(ADC11,3, 490, 3450,6300, 9270, 12200, 15000, 18000, 20900, 23900, 26800,29700,32600,false);

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
