void rotaryPulse(int row, int column, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Column2 = column;
    int Number = buttonNumber[Row][Column];
    int Number2 = Number+1;
    
    if(reverse)
    {
      Column = column;
      Column2 = column - 1;
    }

    //Pulse arm 1
    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        if(rawState[Row][Column] == 1)
        {
          switchTimer[Row][Column] = globalClock;          
        }
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
    {
        toggleTimer[Row][Column] = globalClock;
    }

    if ((globalClock - toggleTimer[Row][Column]) < pulseEncCD)
    {
        Joystick.setButton(Number, 1);
    }
    else
    {
        Joystick.setButton(Number, 0);
    }

    //Pulse arm 2
    if (pushState[Row][Column2] != rawState[Row][Column2] && (globalClock - switchTimer[Row][Column2]) > buttonCooldown)
    {
        if(rawState[Row][Column2] == 1)
        {
          switchTimer[Row][Column2] = globalClock;          
        }
        pushState[Row][Column2] = rawState[Row][Column2];
    }

    if ((globalClock - switchTimer[Row][Column2]) > buttonCooldown)
    {
        pushState[Row][Column2] = rawState[Row][Column2];
    }

    if ((globalClock - switchTimer[Row][Column2]) < buttonCooldown)
    {
        toggleTimer[Row][Column2] = globalClock;
    }

    if ((globalClock - toggleTimer[Row][Column2]) < pulseEncCD)
    {
        Joystick.setButton(Number2, 1);
    }
    else
    {
        Joystick.setButton(Number2, 0);
    }
}

void rotaryPulseBite(int row, int column, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Column2 = column;
    int Number = buttonNumber[Row][Column];
    int Number2 = Number+1;
    
    if(reverse)
    {
      Column = column;
      Column2 = column - 1;
    }

    //Pulse arm 1
    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        if(rawState[Row][Column] == 1)
        {
          switchTimer[Row][Column] = globalClock;
          
          //Engage bite mode
          if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
          {
              if (!biteButtonBit1 && !biteButtonBit2)
              {
                  biteButtonBit1 = true;
              }
          }
          else if (biteButtonBit1 && !biteButtonBit2)
          {
              bitePoint = bitePoint + 100;
          }
          else if (!biteButtonBit1 && biteButtonBit2)
          {
              bitePoint = bitePoint + 10;
          }
          else if (biteButtonBit1 && biteButtonBit2)
          {
              bitePoint = bitePoint + 1;
          }
          if (bitePoint > 1000)
          {
              bitePoint = 1000;
          }
        }
        pushState[Row][Column] = rawState[Row][Column];
    }

    if (!biteButtonBit1 && !biteButtonBit2)
    {
      if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
      {
          pushState[Row][Column] = rawState[Row][Column];
      }
  
      if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
      {
          toggleTimer[Row][Column] = globalClock;
      }
  
      if ((globalClock - toggleTimer[Row][Column]) < pulseEncCD)
      {
          Joystick.setButton(Number, 1);
      }
      else
      {
          Joystick.setButton(Number, 0);
      }
    }


    //Pulse arm 2
    if (pushState[Row][Column2] != rawState[Row][Column2] && (globalClock - switchTimer[Row][Column2]) > buttonCooldown)
    {
        if(rawState[Row][Column2] == 1)
        {
          switchTimer[Row][Column2] = globalClock;
          //Engage bite mode
          if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
          {
              if (!biteButtonBit1 && !biteButtonBit2)
              {
                  biteButtonBit1 = true;
              }
          }
          else if (biteButtonBit1 && !biteButtonBit2)
          {
              bitePoint = bitePoint - 100;
          }
          else if (!biteButtonBit1 && biteButtonBit2)
          {
              bitePoint = bitePoint - 10;
          }
          else if (biteButtonBit1 && biteButtonBit2)
          {
              bitePoint = bitePoint - 1;
          }
          if (bitePoint < 0)
          {
              bitePoint = 0;
          }
        }
        pushState[Row][Column2] = rawState[Row][Column2];
    }

    if (!biteButtonBit1 && !biteButtonBit2)
    {
      if ((globalClock - switchTimer[Row][Column2]) > buttonCooldown)
      {
          pushState[Row][Column2] = rawState[Row][Column2];
      }
  
      if ((globalClock - switchTimer[Row][Column2]) < buttonCooldown)
      {
          toggleTimer[Row][Column2] = globalClock;
      }
  
      if ((globalClock - toggleTimer[Row][Column2]) < pulseEncCD)
      {
          Joystick.setButton(Number2, 1);
      }
      else
      {
          Joystick.setButton(Number2, 0);
      }
    }
}

void rotaryPulseBrightness(int row, int column, bool reverse)
{
    int Row = row - 1;
    int Column = column - 1;
    int Column2 = column;
    int Number = buttonNumber[Row][Column];
    int Number2 = Number+1;
    
    if(reverse)
    {
      Column = column;
      Column2 = column - 1;
    }

    //Pulse arm 1
    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        if(rawState[Row][Column] == 1)
        {
          switchTimer[Row][Column] = globalClock;
          if (pushState[modButtonRow-1][modButtonCol-1] == 1)
          {
              LEDBrightness = LEDBrightness + 2;
          }          
        }
        pushState[Row][Column] = rawState[Row][Column];
    }
    if (pushState[modButtonRow-1][modButtonCol-1] == 0)
    {
      if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
      {
          pushState[Row][Column] = rawState[Row][Column];
      }
  
      if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
      {
          toggleTimer[Row][Column] = globalClock;
      }
  
      if ((globalClock - toggleTimer[Row][Column]) < pulseEncCD)
      {
          Joystick.setButton(Number, 1);
      }
      else
      {
          Joystick.setButton(Number, 0);
      }
    }

    //Pulse arm 2
    if (pushState[Row][Column2] != rawState[Row][Column2] && (globalClock - switchTimer[Row][Column2]) > buttonCooldown)
    {
        if(rawState[Row][Column2] == 1)
        {
          switchTimer[Row][Column2] = globalClock; 
          if (pushState[modButtonRow-1][modButtonCol-1] == 1)
          {
              LEDBrightness = LEDBrightness - 2;
          }           
        }
        pushState[Row][Column2] = rawState[Row][Column2];
    }
    
    if (pushState[modButtonRow-1][modButtonCol-1] == 0)
    {
      if ((globalClock - switchTimer[Row][Column2]) > buttonCooldown)
      {
          pushState[Row][Column2] = rawState[Row][Column2];
      }
  
      if ((globalClock - switchTimer[Row][Column2]) < buttonCooldown)
      {
          toggleTimer[Row][Column2] = globalClock;
      }
  
      if ((globalClock - toggleTimer[Row][Column2]) < pulseEncCD)
      {
          Joystick.setButton(Number2, 1);
      }
      else
      {
          Joystick.setButton(Number2, 0);
      }
    }

    //Adjusting 
    if (LEDBrightness < 0)
    {
      LEDBrightness = 0;
    }
    else if (LEDBrightness > 100)
    {
      LEDBrightness = 100;
    }
}
