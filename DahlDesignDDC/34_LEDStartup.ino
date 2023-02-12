void LEDStartup()
{

/*
*Here goes all LED calls that you only want to run on startup, or calls that only needs to be run on startup. 
*This could be a startup animation sequence, or it could be backlighting from LEDs that will never change as longs as the wheel is powered. 
*When connecting to SimHub, these LEDs will all be wiped black.
*Any LED control that is done here instead of in LEDTop or LEDBottom will save a lot of processing power.
*/

#if(LED1COUNT > 0)
pixels1.show();
#endif

}
