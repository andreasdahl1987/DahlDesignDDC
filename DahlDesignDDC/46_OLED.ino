void OLEDrun()
{
#if(USING_OLED == 1)
//--------------------------------------------------------------
//------------------DISPLAY COMMANDS START HERE-----------------
//--------------------------------------------------------------


backgroundWrite(2, "THIS SCREEN");
backgroundWrite(2, "IS NICE", 0,30,false);

conditionalWrite(2, "What??", false);
conditionalWrite(2, "BUT NOW", buttonPressed(1,1));
conditionalWrite(2, "IT IS BETTER", buttonPressed(1,1), 0, 30, false);
conditionalWrite(2, "THIS SHOULD", false);
conditionalWrite(2, "NEVER SHOW UP!", false, 0, 30, false);

//conditionalWrite(1, true, false, rawState[0][0] == 1, "THIS SCREEN", 1, 1, 40, 0);
//conditionalWrite(1, false, true, rawState[0][0] == 1, "IS BETTER", 1, 1, 45, 30);

//DDClogo(1);

/*
backgroundImage(2, cat, 128, 64, 0, 0);
animationFrame(28, 64, 64);
backgroundAnimation(1, skateboard, 1, 0, 0 );

conditionalImage(2, dog, rawState[0][0] == 1, 128, 64, 0, 0);
*/





//--------------------------------------------------------------
//------------------DISPLAY COMMANDS ENDS HERE------------------
//--------------------------------------------------------------

for (int i = 0; i < DISPLAYCOUNT; i++)
{
  //Writing to displays
  if (writeToDisplay[i])
  {
    displays[i].display();
    writeToDisplay[i] = false;
  }
  //Resetting conditional write line index
  OLEDcondiIndex[i] = 0;

  //Locking background from running again
  if(backgroundSet[i])
  {
    OLEDgenLock[i] = true;  //Prevent writing background untill genlock is off again (from condi being met and un-met again)
    backgroundSet[i] = false;
  }
}

#endif
}
