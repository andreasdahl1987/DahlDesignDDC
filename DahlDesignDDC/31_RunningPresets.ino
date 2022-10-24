void runningPresets()
{
    /*
    This function runs in the loop, meaning the stuf you write here will be computed continously. Under the presets() function, the changes just
    happens once after you switch preset. This is great for static stuf like switch modes, bite point, etc. But if you set a bite point here, you won't
    be able to change it with your rotary, since it will continously be updated to the value you set here. 

    This area is mainly for changing switch function assignments. If you want your 12-way to have a regular 12-position mode in ACC, but use a multiComplex24 
    function (which includes other pushbuttons) in another preset, this is where you set it. You might want to use a HybridSwitch in one preset, 
    and since hybrid buttons dont produce a button number, this button is lost in other presets that are meant for sims that dont support 
    this kind of switch. You could then use runningPresets() to set hybridButton(1,2); in all presets except the one you use
    for F1 2022, where it would be pushButton(1,2);. Just examples, use your imagination. Setting up parts of your controller in this function can make 
    your controller very flexible.    
    */

    switch (switchPreset)
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
}

