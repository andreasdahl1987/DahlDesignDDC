  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

biteButton(1,2);

modButton(1,1);


dualClutch(ADC11,1,4500,0,ADC12, 2, 4500, 0, true);

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
