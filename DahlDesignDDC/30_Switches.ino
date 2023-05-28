  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

  pushButton(1,3);

  pushButton(3, 1);
  pushButton(3, 2);

  pushButton(4, 3);
  pushButton(4, 4);
  pushButton(4, 6);
  pushButton(4, 7);

  pushButton(6, 4);
  pushButtonM(6, 7, 1);

  launchButton(7, 1, 3); //Lower right side button (LIM) is launch
  pushButton(7, 3);

  pushPull(3, 3, 3, 4, 6, 6, 6, 5, 7);

  toggleM(3, 5, 5);
  toggleM(6, 3, 6);
  brakeMagic(7, 2);

  //SPECIALS

  modButton(1, 7);
  neutralButton(4, 5);
  biteButton(1, 5);
  presetButton(1, 6);
  quickSwitch(1, 4);
  throttleHoldSW1(7,6,7,4,5, true);

  //ENCODERS

  rotary2Inc(1, 1, false);
  rotary2Inc(4, 1, false);

  rotary2Inc(3, 6, true);
  rotary2Inc(6, 1, false);


  //FUNKY SWITCHES
  funkyButtonDDButton(5, 4, 5, 1, 6, 7);
  funkyButtonHybrid(5, 6, 5, 1, 4, 7);
  funkyButton(5, 1, 5, 4, 6, 7);
  funkyButton(5, 7, 5, 1, 4, 6);
  funkyPush(5, 5, 1, 4, 6, 7);

  DDSfunky(5, 2, 3);

  funkyButton(2, 1, 5, 2, 4, 7);
  funkyButton(2, 2, 5, 1, 4, 7);
  funkyButton(2, 4, 5, 1, 2, 7);
  funkyButton(2, 7, 5, 1, 2, 4);
  funkyPush(2, 5, 1, 2, 4, 7);
  funkyRotary(2, 3, 6, false);

  //ANALOG INPUTS


  SW1BiteRotary(
      A2,                                                           //Analog pin to read
      1,                                                            //Analog switch #
      3,                                                            //Field placement
      16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,   //Switch position values
      false);                                                        //Rotation direction

  SW1PresetRotary(
      A1,                                                           //Analog pin to read
      2,                                                            //Analog switch #
      2,                                                            //Field placement
      16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023,   //Switch position values
      false);                                                        //Rotation direction

  filteredDualClutch(
      A0,                                                           //Analog pin to read (Master)
      3,                                                            //Analog switch # (Master)
      571,                                                          //Released value (Master
      173,                                                          //Fully pressed value (Master)
      -1,                                                           //Curve push (Master)
      1,                                                            //Exponential factor (Master
      A3,                                                           //Analog pin to read (Slave)
      4,                                                            //Analog switch # (Slave)
      527,                                                          //Released value (Slave)
      878,                                                          //Fully pressed value (Slave)
      -1,                                                           //Curve push (Slave)
      0.7,                                                          //Exponential factor (Salve)
      true);                                                        //True = Master/Slave paddle is Throttle/Brake in mode 4. False is opposite.


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
