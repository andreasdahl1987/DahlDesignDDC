void OLEDrun()
{
#if(USING_SSD1306 == 1)
//--------------------------------------------------------------
//------------------DISPLAY COMMANDS START HERE-----------------
//--------------------------------------------------------------

SSD1306clearPush(1,"Test Test", 1, 2, 0, 0, true); //clearPush selects display (1), resets the screen, writes text "" with color (1) and size (2) to coordinates (0,0). Wait set to true. 
SSD1306push(1,"Menu options", 2, 24,12, false); // Pushes more without clearing first. Changable text size (2) and coordinates (24,12). Send result, dont wait for more.

SSD1306clearPush(2,"OLED", 1, 2, 0, 0, true);
SSD1306push(2,"DDC", 2, 24,12, false);

SSD1306clearPush(3,"Scroll", 1, 1.5, 0, 0, true);
SSD1306push(3," \n PIT \n", 2, 24,12, false);

SSD1306clearPush(4,"BBal", 1, 2, 40, 15, false);

SSD1306clearPush(5,"DRS", 1, 2, 48, 18, false);

SSD1306clearPush(6,"OVERTAKE", 1, 2.5, 10, 10, false);








//--------------------------------------------------------------
//------------------DISPLAY COMMANDS ENDS HERE------------------
//--------------------------------------------------------------
#endif
}



void OLEDreactive()
{
#if(USING_SSD1306 == 1)
//--------------------------------------------------------------
//------------------DISPLAY REACTIONS START HERE----------------
//--------------------------------------------------------------














//--------------------------------------------------------------
//------------------DISPLAY REACTIONS ENDS HERE-----------------
//--------------------------------------------------------------
#endif
}
