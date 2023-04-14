  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------
checkValue(ADC1);
checkValue(ADC2);
checkValue(ADC3);
checkValue(ADC4);
checkValue(ADC5);
checkValue(ADC6);
checkValue(ADC7);
checkValue(ADC8);
  biteButton(3,3);
  modButton(7,5);
  preset2Bit(3,1,false);

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
