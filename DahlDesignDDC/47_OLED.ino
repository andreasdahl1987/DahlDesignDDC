void OLEDrun()
{
#if(USING_OLED == 1)
//--------------------------------------------------------------
//------------------DISPLAY COMMANDS START HERE-----------------
//--------------------------------------------------------------


//backgroundWrite(1, true, false, "THIS SCREEN", 1, 1, 40, 0);
//backgroundWrite(1, false, true, "IS NICE", 1, 1, 50, 30);
DDClogo(1);

conditionalWrite(1, true, false, rawState[0][0] == 1, "THIS SCREEN", 1, 1, 40, 0);
conditionalWrite(1, false, true, rawState[0][0] == 1, "IS BETTER", 1, 1, 45, 30);




//--------------------------------------------------------------
//------------------DISPLAY COMMANDS ENDS HERE------------------
//--------------------------------------------------------------
#endif
}
