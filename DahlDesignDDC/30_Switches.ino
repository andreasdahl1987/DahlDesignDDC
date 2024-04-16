  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------


  switchTableInject(21,1,1);
  switchTableInject(27,1,2);
  switchTableInject(26,1,3);
  switchTableInject(22,1,4);


  pushButtonL (1,3);
  PWMPot(1, 0, 1023, 1);
  triggerPWM(1,analogTravel(1,50),false,100,500);


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
  #if(USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)
    CB1Oversampling();
  #endif
  }
#endif
