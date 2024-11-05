void OLEDrun()
{
#if(USING_OLED == 1)
//--------------------------------------------------------------
//------------------DISPLAY COMMANDS START HERE-----------------
//--------------------------------------------------------------

//SSD1306clearWrite(1, false, "Test Test", 1, 2, 0, 0, true); //clearPush selects display (1), resets the screen, writes text "" with color (1) and size (2) to coordinates (0,0). Wait set to true. 
//SSD1306add(1,"Menu options", 2, 24,12, false); // Pushes more without clearing first. Changable text size (2) and coordinates (24,12). Send result, dont wait for more.

SSD1306DDClogo(2,0,3);
SSD1306DDClogo(1,0,3);
/*
if(rawState[0][0] == 0)
{
  SSD1306clearWrite(2,true,"BUTTON", 1, 2, 0, 0, true);
  SSD1306add(2,"LONELY", 2, 24,12, false);
}
else
{
  SSD1306add(2,"lel", 2, 24,12, false);
}
*/





//--------------------------------------------------------------
//------------------DISPLAY COMMANDS ENDS HERE------------------
//--------------------------------------------------------------
#endif
}



void OLEDreactive()
{
#if(USING_OLED == 1)
//--------------------------------------------------------------
//------------------DISPLAY REACTIONS START HERE----------------
//--------------------------------------------------------------














//--------------------------------------------------------------
//------------------DISPLAY REACTIONS ENDS HERE-----------------
//--------------------------------------------------------------
#endif
}
