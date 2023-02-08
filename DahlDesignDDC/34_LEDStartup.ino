void LEDStartup()
{

/*
*Here goes all LED calls that you only want to run on startup, or calls that only needs to be run on startup. 
*This could be a startup animation sequence, or it could be backlighting from LEDs that will never change as longs as the wheel is powered. 
*Any LED control that is done here instead of in LEDRunning will save a lot of processing power.
*/
colorMe(10,19,0x008b8b,15);
pixels1.show();

}
