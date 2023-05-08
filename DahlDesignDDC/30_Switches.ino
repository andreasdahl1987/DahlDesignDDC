  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------
/*
  DDSanalog(ADC10,1, 490, 3450,6300, 9270, 12200, 15000, 18000, 20900, 23900, 26800,29700,32600,false);

  presetNext(3,1);
  biteButton(3,2);
  modButton(3,3);
*/

 rotaryPulseBite(1, 1, true);
 biteButton(1,3);
 modButton(5,4);
 presetNext(5,3);

  
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
