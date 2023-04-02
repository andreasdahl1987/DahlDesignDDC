	//--------------------------------------
  //---------PERIPHERALS START HERE-------
  //--------------------------------------

ADS1115Run(1,4,7,2);
ADS1115Run(2,4,7,1);
	
  //--------------------------------------
  //---------PERIPHERALS END HERE---------
  //--------------------------------------	
	
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------

if (ADS1115value[0] < 2)
{
  rawState[0][0] = 1;
}
else
{
  rawState[0][0] = 0;
}
if (ADS1115value[1] < 2)
{
  rawState[0][1] = 1;
}
else
{
  rawState[0][1] = 0;
}

funkyRotary(1,1,2,false);

  singleClutch(ADC1,1,23240,13450);

  refreshRate();

  Serial.print( rawState[0][0]);
    Serial.println(rawState[0][1]);



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
