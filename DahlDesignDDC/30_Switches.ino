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
