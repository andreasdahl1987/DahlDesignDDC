void OLEDrun()
{
#if(USING_OLED == 1)
//--------------------------------------------------------------
//------------------DISPLAY COMMANDS START HERE-----------------
//--------------------------------------------------------------


//backgroundWrite(1, true, false, "THIS SCREEN", 1, 1, 40, 0);
//backgroundWrite(1, false, true, "IS NICE", 1, 1, 50, 30);

//conditionalWrite(1, true, false, rawState[0][0] == 1, "THIS SCREEN", 1, 1, 40, 0);
//conditionalWrite(1, false, true, rawState[0][0] == 1, "IS BETTER", 1, 1, 45, 30);

//DDClogo(1);

backgroundImage(2, cat, 128, 64, 0, 0);
animationFrame(28, 64, 64);
backgroundAnimation(1, skateboard, 1, 0, 0 );

conditionalImage(2, dog, rawState[0][0] == 1, 128, 64, 0, 0);






//--------------------------------------------------------------
//------------------DISPLAY COMMANDS ENDS HERE------------------
//--------------------------------------------------------------
#endif
}
