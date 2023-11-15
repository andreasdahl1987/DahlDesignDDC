void E18Inc(int row, int col, bool reverse) 
{

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    pushState[Row][Column] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if(globalClock - switchTimer[Row][Column+1] > E18Pulse && !latchLock[Row][Column + 1]) //Pulse is finished, reset checkpoints
    {
      toggleTimer[Row][Column] = 0;
      toggleTimer[Row][Column + 1] = 0;
      latchLock[Row][Column + 1] = true; //Locking checkpoint resets
    }

    if(globalClock - switchTimer[Row][Column] > E18Cooldown && !latchState[Row][Column] && (toggleTimer[Row][Column] + toggleTimer[Row][Column + 1] == 0 )) //Switch has cooled down, ready to record the next steady state
    {
      latchState[Row][Column] = true;
    }

    if(latchState[Row][Column] && (pushState[Row][Column] == 0 || pushState[Row][Column] == 3)) //Record previous steady state when button press was not engaged. 
    {
      pushState[Row][Column + 1] = pushState[Row][Column]; //Record steady state
      latchState[Row][Column+1] = true; //Ready to check for change
    }

    if(pushState[Row][Column + 1] != pushState[Row][Column] && latchState[Row][Column+1]) //Something happened and we're ready to go. 
    {
      latchState[Row][Column] = false; //Record marker set to false, no recording of steady state on rotation
      latchState[Row][Column+1] = false; //Change marker set to false to prevent looking for change on rotation
      switchTimer[Row][Column] = globalClock; //Timer starts

      //Now lets look at what did change

      //CW rotation: Either difference between new and old (new - old) is 2 or -2
      if (abs(pushState[Row][Column]-pushState[Row][Column + 1]) ==  2) 
      {
        toggleTimer[Row][Column] = 1; //CW rotation pass step 1
        latchLock[Row][Column] = false; //Open lock to step 2
      }
      else
      //CCW rotation: Either difference between new and old is 1 or -1
      {
        toggleTimer[Row][Column + 1] = 1; //CW rotation pass step 1
        latchLock[Row][Column] = false; //Open lock to step 2
      }
    }

    if ((toggleTimer[Row][Column] + toggleTimer[Row][Column+1] > 0) && abs(pushState[Row][Column] - pushState[Row][Column + 1]) == 3 && !latchLock[Row][Column]) //Check for end of rotation rotation for going to step 2
    {
      latchLock[Row][Column] = true; //Locking step 2 entry
      switchTimer[Row][Column+1] = globalClock; //Start pulse duration      
      latchLock[Row][Column + 1] = false; //Opening for checkpoint reset after pulse;
      toggleTimer[Row][Column] ++;
      toggleTimer[Row][Column + 1] ++;

      if(toggleTimer[Row][Column] == 2)
      {
        toggleTimer[Row][Column + 1] = 0;
        //Adjustments added here 
      }
      else if(toggleTimer[Row][Column + 1] == 2)
      {
        toggleTimer[Row][Column] = 0;
        //Adjustments added here
      }    
    }

    if (toggleTimer[Row][Column] == 2)
    {
      Joystick.setButton(Number + Reverse, 1);
    }
    else
    {
      Joystick.setButton(Number + Reverse, 0);
    }

    if (toggleTimer[Row][Column + 1] == 2)
    {
      Joystick.setButton(Number + 1 - Reverse, 1);
    }
    else
    {
      Joystick.setButton(Number + 1 - Reverse, 0);
    }
}
