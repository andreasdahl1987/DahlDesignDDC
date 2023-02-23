# Presets

Having LED control follow your [presets](../../../4.-advanced-features/presets/) is not included in DDC, because it will steal some memory from all those two arent using it, and it is very simple to add.&#x20;

Simply copy some of the content of 32\_Presets.ino to the LED  tab that you'll use. Here, moved over to 36\_LEDTop:

```
void LEDTop()
{
  
  /*
  *Here goes LED calls that you want to refresh constantly, and will overwrite both LEDStartup and LEDBottom calls as well as SimHub LED control. 
  */

   //LED CALLS STARTS HERE


    //----------------------------------------
    //-----------GLOBAL LED CALLS-------------
    //----------------------------------------

     

    //----------------------------------------
    //---------PRESET SPECIFIC CALLS----------
    //----------------------------------------

    switch (presetNumber)
    {
    case 0: //PRESET 1 

        break;
    case 1: //PRESET 2 

        break;
    case 2: //PRESET 3 

        break;
    case 3: //PRESET 4 

        break;
    case 4: //PRESET 5 

        break;
    case 5: //PRESET 6 

        break;
    case 6: //PRESET 7 

        break;
    case 7: //PRESET 8 

        break;
    case 8: //PRESET 9 

        break;
    case 9: //PRESET 10

        break;
    case 10: //PRESET 11 

        break;
    case 11: //PRESET 12 

        break;
    }



  //LED CALLS STOP HERE

  #if(LED1COUNT > 0)
    LED1.show();
  #endif
  #if(LED2COUNT > 0)
    LED2.show();
  #endif
  #if(LED3COUNT > 0)
    LED3.show();
  #endif
  #if(LED4COUNT > 0)
    LED4.show();
  #endif

}
    

```
