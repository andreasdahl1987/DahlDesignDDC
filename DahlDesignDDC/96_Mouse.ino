#if(ENABLE_MOUSE == 1)

void funkyMouseScroll(int Arow, int Acol, int Bcol, bool reverse)
{
	int Row = Arow - 1;
	int Column = Acol - 1;
	int bCol = Bcol - 1;
  int Number = buttonNumber[Row][Column];

	if (!rawState[Row][Column] && !rawState[Row][bCol])
	{
		pushState[Row][Column] = 1;
	}
	else if (!rawState[Row][Column] && rawState[Row][bCol])
	{
		pushState[Row][Column] = 2;
		latchLock[Row][Column] = 1; //Fetching 01
	}
	else if (rawState[Row][Column] && rawState[Row][bCol])
	{
		pushState[Row][Column] = 3;
	}
	else if (rawState[Row][Column] && !rawState[Row][bCol])
	{
		pushState[Row][Column] = 4;
		latchLock[Row][bCol] = 1; //Fetching 10
	}

	if ((globalClock - switchTimer[Row][Column] > funkyCooldown) && (globalClock - switchTimer[Row][bCol] > funkyCooldown))
	{
		if ((latchLock[Row][bCol] && pushState[Row][Column] == 1) || (latchLock[Row][Column] && pushState[Row][Column] == 3))
		{
			switchTimer[Row][Column] = globalClock;
      if(MOUSE_ALWAYS_ACTIVE == 1 || pushState[mouseRow-1][mouseCol-1] == 1)
      {
			  Mouse.move(0, 0, reverse ? -1 : 1); // 1 - Scroll Down, -1 - Scroll Up
      }
		}
		else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
		{
			switchTimer[Row][bCol] = globalClock;
      if(MOUSE_ALWAYS_ACTIVE == 1 || pushState[mouseRow-1][mouseCol-1] == 1)
      {
			  Mouse.move(0, 0, reverse ? 1 : -1);
      }
		}
	}
	else
	{
		latchLock[Row][bCol] = 0;
		latchLock[Row][Column] = 0;
	}

  if(MOUSE_ALWAYS_ACTIVE == 0 && pushState[mouseRow-1][mouseCol-1] == 0)
  {
    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
  }
}

void funkyMouseButton(int row, int column, int aCol, int bCol, int cCol, int dCol, uint8_t button)
{
	int Row = row - 1;
	int Column = column - 1;
  int Number = buttonNumber[Row][Column];

	int Acol = aCol - 1;
	int Bcol = bCol - 1;
	int Ccol = cCol - 1;
	int Dcol = dCol - 1;

	if (!pushState[Row][Acol] && !pushState[Row][Bcol] && !pushState[Row][Ccol] && !pushState[Row][Dcol])
	{
		if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
		{
			if (pushState[Row][Column] != rawState[Row][Column])
			{
				switchTimer[Row][Column] = globalClock;
			}
			pushState[Row][Column] = rawState[Row][Column];
		}
	}

  if(MOUSE_ALWAYS_ACTIVE || pushState[mouseRow-1][mouseCol-1] == 1)
  {
    if(pushState[Row][Column] == 1)
    {
      Mouse.press(button);
    }
    else
    {
      Mouse.release(button);
    }
  }
  else
  {
    Joystick.setButton(Number, pushState[Row][Column]);
  }
}

void funkyMouseMove(int row, int column, int pCol, int Col1, int Col2, int Col3, uint8_t direction, uint8_t mouseSpeed, uint8_t mouseSpeed2)
{
  int output = 0;

  int Row = row - 1;
  int Column = column - 1;
  int Number = buttonNumber[Row][Column];

  int pcol = pCol - 1;
  int col1 = Col1 - 1;
  int col2 = Col2 - 1;
  int col3 = Col3 - 1;

  if (!pushState[Row][pcol] && !pushState[Row][col1] && !pushState[Row][col2] && !pushState[Row][col3])
  {
    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
      if (pushState[Row][Column] != rawState[Row][Column])
      {
        switchTimer[Row][Column] = globalClock;
        toggleTimer[Row][Column] = globalClock;
      }
      pushState[Row][Column] = rawState[Row][Column];
    }
  }

  if(MOUSE_ALWAYS_ACTIVE == 0 && pushState[mouseRow-1][mouseCol-1] == 0)
  {
    Joystick.setButton(Number, pushState[Row][Column]);
  }
  else if(mouseRun)
  {
    if(!pushState[Row][Column])
    {
      toggleTimer[Row][Column] = globalClock;
    }

    if(globalClock - toggleTimer[Row][Column] > 750)
    {
      output = 127 * pushState[Row][Column] * mouseSpeed2 /100;
    }
    else if(globalClock - toggleTimer[Row][Column] < 500)
    {
      output = 127 * pushState[Row][Column] * mouseSpeed /100;
    }
    else
    {
      int diff = (mouseSpeed2 - mouseSpeed) * (globalClock - toggleTimer[Row][Column] - 250) / 500;
      output = 127 * pushState[Row][Column] * (mouseSpeed+diff) /100;
    }

    if(output < 0)
    {
      output = 0;
    }
    if(output > 127)
    {
      output = 127;
    }

    switch(direction)
    {
      case MOUSE_LEFT: 
        Mouse.move(-output,0);
        break;
      case MOUSE_RIGHT:
        Mouse.move(output,0);
        break;
      case MOUSE_UP:
        Mouse.move(0,-output);
        break;
      case MOUSE_DOWN:
        Mouse.move(0,output);
        break;
    }
    mouseRan = true;
  }
} 

void mouseMove(int row, int column, uint8_t direction, uint8_t mouseSpeed, uint8_t mouseSpeed2)
{
  int output = 0;

  int Row = row - 1;
  int Column = column - 1;
  int Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }


  if(MOUSE_ALWAYS_ACTIVE == 0 && pushState[mouseRow-1][mouseCol-1] == 0)
  {
    Joystick.setButton(Number, pushState[Row][Column]);
  }
  else if(mouseRun)
  {
    if(!pushState[Row][Column])
    {
      toggleTimer[Row][Column] = globalClock;
    }

    if(globalClock - toggleTimer[Row][Column] > 750)
    {
      output = 127 * pushState[Row][Column] * mouseSpeed2 /100;
    }
    else if(globalClock - toggleTimer[Row][Column] < 500)
    {
      output = 127 * pushState[Row][Column] * mouseSpeed /100;
    }
    else
    {
      int diff = (mouseSpeed2 - mouseSpeed) * (globalClock - toggleTimer[Row][Column] - 250) / 500;
      output = 127 * pushState[Row][Column] * (mouseSpeed+diff) /100;
    }

    if(output < 0)
    {
      output = 0;
    }
    if(output > 127)
    {
      output = 127;
    }

    switch(direction)
    {
      case MOUSE_LEFT: 
        Mouse.move(-output,0);
        break;
      case MOUSE_RIGHT:
        Mouse.move(output,0);
        break;
      case MOUSE_UP:
        Mouse.move(0,-output);
        break;
      case MOUSE_DOWN:
        Mouse.move(0,output);
        break;
    }
    mouseRan = true;
  }
} 

void leftMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;
  int8_t Number = buttonNumber[Row][Column];

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(MOUSE_ALWAYS_ACTIVE || pushState[mouseRow-1][mouseCol-1] == 1)
  {
    if(pushState[Row][Column] == 1)
    {
      Mouse.press(1);
    }
    else
    {
      Mouse.release(1);
    }
  }
  else
  {
    Joystick.setButton(Number, pushState[Row][Column]);
  }
}

void middleMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;
  int8_t Number = buttonNumber[Row][Column];

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  
  if(MOUSE_ALWAYS_ACTIVE || pushState[mouseRow-1][mouseCol-1] == 1)
  {
    if(pushState[Row][Column] == 1)
    {
      Mouse.press(4);
    }
    else
    {
      Mouse.release(4);
    }
  }
  else
  {
    Joystick.setButton(Number, pushState[Row][Column]);
  }
}

void rightMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;
  int8_t Number = buttonNumber[Row][Column];

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(MOUSE_ALWAYS_ACTIVE || pushState[mouseRow-1][mouseCol-1] == 1)
  {
    if(pushState[Row][Column] == 1)
    {
      Mouse.press(2);
    }
    else
    {
      Mouse.release(2);
    }
  }
  else
  {
    Joystick.setButton(Number, pushState[Row][Column]);
  }
}


void analogMouse(int xChannel, int yChannel, int xLeft, int xMiddle, int xRight, int yUp, int yMiddle, int yDown, uint8_t mouseSpeed)
{
  if (mouseRun)
  {
    //--------------------------------
    //-----X AXIS CALCULATIONS--------
    //--------------------------------

    int X = xChannel - 1;

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

    int xValue;
    if (analogPins[X] > 49)
    {
      xValue = ADS1115value[analogPins[X] - ADC_CORR];
    }
    else
    {
      xValue = analogRead(analogPins[X]);
    }

    #else

    int xValue = analogRead(analogPins[X]);

    #endif

    //Converting value to 8bit mouse value, adding deadzone

    int deadZone = abs(xLeft - xRight)*0.025;

    int xOutput = 0;

    if (abs(xValue - xMiddle) > deadZone)
    {
      if(xLeft < xMiddle)
      {
        if(xValue < xMiddle)
        {
          xOutput = 127 * (xValue - xMiddle - deadZone) / (xMiddle - xLeft);
        }
        else
        {
          xOutput = 127 * (xValue - xMiddle + deadZone) / (xRight - xMiddle);
        }

      }
      else
      {
        if(xValue > xMiddle)
        {
          xOutput = 127 * (xMiddle - xValue - deadZone) / (xLeft - xMiddle);
        }
        else
        {
          xOutput = 127 * (xMiddle - xValue + deadZone) / (xMiddle - xRight);
        }
      }
    }

    if(xOutput < -127)
    {
      xOutput = -127;
    }
    if(xOutput > 127)
    {
      xOutput = 127;
    }

    //--------------------------------
    //-----Y AXIS CALCULATIONS--------
    //--------------------------------

    int Y = yChannel - 1;

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

    int yValue;
    if (analogPins[Y] > 49)
    {
      yValue = ADS1115value[analogPins[Y] - ADC_CORR];
    }
    else
    {
      yValue = analogRead(analogPins[Y]);
    }

    #else

    int yValue = analogRead(analogPins[Y]);

    #endif

    //Converting value to 8bit mouse value, adding deadzone

    deadZone = abs(yDown - yUp)*0.025;

    int yOutput = 0;

    if (abs(yValue - yMiddle) > deadZone)
    {
      if(yUp < yMiddle)
      {
        if(yValue < yMiddle)
        {
          yOutput = 127 * (yValue - yMiddle - deadZone) / (yMiddle - yUp);
        }
        else
        {
          yOutput = 127 * (yValue - yMiddle + deadZone) / (yDown - yMiddle);
        }

      }
      else
      {
        if(yValue > yMiddle)
        {
          yOutput = 127 * (yMiddle - yValue - deadZone) / (yUp - yMiddle);
        }
        else
        {
          yOutput = 127 * (yMiddle - yValue + deadZone) / (yMiddle - yDown);
        }
      }
    }

    if(yOutput < -127)
    {
      yOutput = -127;
    }
    if(yOutput > 127)
    {
      yOutput = 127;
    }

    Mouse.move((xOutput*mouseSpeed)/100,(yOutput*mouseSpeed)/100);

    mouseRan = true;
  }
} 

void mouseActiveButton(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];

    mouseRow = row;
    mouseCol = column;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    Joystick.setButton(Number, pushState[Row][Column]);
}

void mouseActiveButtonMute(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;

    mouseRow = row;
    mouseCol = column;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

}

void mouseActiveLatch(int row, int column, int fieldPlacement)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;

    mouseRow = row;
    mouseCol = column;

    if (latchState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        latchState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        latchState[Row][Column] = rawState[Row][Column];
    }

    //Scrolling through bite point setting
    if (!latchState[Row][Column])
    {
        latchLock[Row][Column] = true;
    }

    if (latchState[Row][Column] && latchLock[Row][Column])
    {
        latchLock[Row][Column] = false;
        pushState[Row][Column] = !pushState[Row][Column];
    }

    //Push mouse active state
    long pesh = 0;
    pesh = pesh | pushState[Row][Column] << (fieldPlacement-1);
    buttonField = buttonField | pesh;
}

void mouseUpdates()
{
  uint8_t segment = (globalClock % 100) / 10;

  if(segment != oldMouseSegment)
  {
    mouseRun = true;
  }

  if (mouseRan)
  {
    oldMouseSegment = segment;
    mouseRun = false;
    mouseRan = false;
  }
}

void dualClutchAndMouse(int masterAnalogChannel, int slaveAnalogChannel, bool throttleMaster, int mouseSpeed)
{
    //--------------------------------
    //---Master paddle calculations----
    //--------------------------------

    int M = masterAnalogChannel - 1;

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

    uint16_t masterValue;
    if (analogPins[M] > 49)
    {
      masterValue = ADS1115value[analogPins[M] - ADC_CORR];
    }
    else
    {
      masterValue = analogRead(analogPins[M]);
    }

    #else

    uint16_t masterValue = analogRead(analogPins[M]);

    #endif

    float masterNormalized = 0;
    int FieldPlacement = 7;
    bool ThrottleMaster = throttleMaster;
    masterRaw = masterValue;


    if (MFP > MFR)
    {
        float gap = MFP - MFR;
        float normFactor = 1000 / gap;
        if (masterValue < MFR)
        {
          masterValue = MFR;
        }
        masterNormalized = normFactor * (masterValue - MFR);
        if (masterNormalized < 0)
        {
            masterNormalized = 0;
        }
    }


    else if (MFP < MFR)
    {
        float gap = MFR - MFP;
        float normFactor = 1000 / gap;
        if (masterValue > MFR)
        {
          masterValue = MFR;
        }
        masterNormalized = normFactor * (MFR - masterValue);
        if (masterNormalized < 0)
        {
            masterNormalized = 0;
        }
    }


    total[M] = total[M] - readings[M][readIndex[M]];
    readings[M][readIndex[M]] = masterNormalized;
    total[M] = total[M] + readings[M][readIndex[M]];


    readIndex[M]++;


    if (readIndex[M] > (reads - 1))
    {
        readIndex[M] = 0;
    }


    average[M] = total[M] / reads;
    if (average[M] > 1000)
    {
        average[M] = 1000;
    }


    //--------------------------------
    //---Slave paddle calculations----
    //--------------------------------
    int S = slaveAnalogChannel - 1;

    #if(USING_ADS1115 == 1 || USING_CB1 == 1  || ENABLE_OVERSAMPLING == 1)

    uint16_t slaveValue;
    if (analogPins[S] > 49)
    {
      slaveValue = ADS1115value[analogPins[S] - ADC_CORR];
    }
    else
    {
      slaveValue = analogRead(analogPins[S]);
    }

    #else

    uint16_t slaveValue = analogRead(analogPins[S]);

    #endif

    float slaveNormalized = 0;
    slaveRaw = slaveValue;


    if (SFP > SFR)
    {
        float gap = SFP - SFR;
        float normFactor = 1000 / gap;
        if (slaveValue < SFR)
        {
          slaveValue = SFR;
        }
        slaveNormalized = normFactor * (slaveValue - SFR);
        if (slaveNormalized < 0)
        {
            slaveNormalized = 0;
        }
    }


    else if (SFP < SFR)
    {
        float gap = SFR - SFP;
        float normFactor = 1000 / gap;
        if (slaveValue > SFR)
        {
          slaveValue = SFR;
        }
        slaveNormalized = normFactor * (SFR - slaveValue);
        if (slaveNormalized < 0)
        {
            slaveNormalized = 0;
        }
    }


    total[S] = total[S] - readings[S][readIndex[S]];
    readings[S][readIndex[S]] = slaveNormalized;
    total[S] = total[S] + readings[S][readIndex[S]];


    readIndex[S]++;


    if (readIndex[S] > (reads - 1))
    {
        readIndex[S] = 0;
    }


    average[S] = total[S] / reads;
    if (average[S] > 1000)
    {
        average[S] = 1000;
    }


    //------------------------------------------
    //------SETTING BITE POINT WITH BUTTON------
    //------------------------------------------


    if (max(average[S], average[M]) > 0 && pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
    {
        bitePoint = max(average[S], average[M]);
    }

    //------------------------
    //------MODE CHANGE-------
    //------------------------
    int maxValue = max(average[S], average[M]);

    if (maxValue == 0)
    {
        analogLatchLock[M] = true;
    }

    if (maxValue == 1000 && analogLatchLock[M])
    {
        analogLatchLock[M] = false;
        if (pushState[modButtonRow - 1][modButtonCol - 1] == 1) //Changig clutch modes
        {
            if (!analogSwitchMode1[M] && !analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = true;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
            else if (analogSwitchMode1[M] && !analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = false;
                analogSwitchMode2[M] = true;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
            else if (!analogSwitchMode1[M] && analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = true;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
            else if (analogSwitchMode1[M] && analogSwitchMode2[M])
            {
                analogSwitchMode1[M] = false;
                analogSwitchMode2[M] = false;
                Joystick.setXAxis(0);
                Joystick.setThrottle(0);
                Joystick.setBrake(0);
            }
        }
    }

    //------------------------
    //---------MOUSE----------
    //------------------------

    if((MOUSE_ALWAYS_ACTIVE == 1 || pushState[mouseRow-1][mouseCol-1] == 1) && ENABLE_MOUSE == 1)
    {
      if(mouseRun)
      {
        //X axis position
        int rotation = average[S] % 500;
        int xOutput = 100 - sq(rotation - 250) / 625;
        if(average[S] > 500)
        {
          xOutput *= -1;
        }
        //Y axis position
        int yPos = average[S] + 250;
        if (yPos > 1000)
        {
          yPos -= 1000;
        }
        rotation = yPos % 500;
        int yOutput = 100 - sq(rotation - 250) / 625;
        if(yPos < 500)
        {
          yOutput *= -1;
        }

        xOutput = xOutput * average[M] * 127 * mouseSpeed / 10000000;
        yOutput = yOutput * average[M] * 127 * mouseSpeed / 10000000;

        Mouse.move(xOutput,yOutput);

      }
    }

    //------------------------
    //------CLUTCH MODES------
    //------------------------

    else
    {
      //MODE 1: STATIC
      if (!analogSwitchMode1[M] && !analogSwitchMode2[M])
      {
          average[S] = average[S] * bitePoint / 1000;
          Joystick.setXAxis(max(average[S], average[M]));
      }
      //MODE 2: DYNAMIC LOW
      else if (analogSwitchMode1[M] && !analogSwitchMode2[M])
      {


          if ((average[S] == 0 || average[M] == 0 || (average[S] > bitePoint && average[M] < bitePoint)) || (average[M] > bitePoint && average[S] < bitePoint))
          {
              average[S] = average[S] * bitePoint / 1000;
              average[M] = average[M] * bitePoint / 1000;
              Joystick.setXAxis(max(average[S], average[M]));
          }
          else if (average[M] > bitePoint && average[S] > bitePoint)
          {
              Joystick.setXAxis(max(average[S], average[M]));
          }
          else if ((average[S] == 1000 && average[M] < 1000 && average[M] > bitePoint) || (average[M] == 1000 && average[S] < 1000 && average[S] > bitePoint))
          {
              Joystick.setXAxis(min(average[S], average[M]));
          }
      }
      //MODE 3: DYNAMIC HIGH
      else if (!analogSwitchMode1[M] && analogSwitchMode2[M])
      {
          if (average[S] == 1000 && average[M] == 1000)
          {
              analogLatchLock[S] = true;
          }
          if (average[S] == 0 && average[M] == 0)
          {
              analogLatchLock[S] = false;
          }


          if (analogLatchLock[S])
          {
              if (average[S] == 1000 && average[M] > bitePoint)
              {
                  Joystick.setXAxis(average[M]);
              }
              else if (average[M] == 1000 && average[S] > bitePoint)
              {
                  Joystick.setXAxis(average[S]);
              }
              else
              {
                  Joystick.setXAxis(max(average[S], average[M]) * bitePoint / 1000);
              }
          }
          else
          {
              Joystick.setXAxis(max(average[S], average[M]));
          }
      }
      //MODE 4: BRAKE AND THROTTLE
      else
      {
          Joystick.setXAxis(0);
          if (ThrottleMaster)
          {
              Joystick.setThrottle(average[M]);
              Joystick.setBrake(average[S]);
          }
          else
          {
              Joystick.setThrottle(average[S]);
              Joystick.setBrake(average[M]);
          }
      }
    }
    
    if (neutralButtonRow != -1)
    {
        if (latchState[neutralButtonRow - 1][neutralButtonCol - 1])
        {
            Joystick.setXAxis(1000);
        }
    }

    long push = 0;
    push = push | analogSwitchMode1[M];
    push = push | (analogSwitchMode2[M] << 1);
    push = push << (2 * (FieldPlacement - 1));
    rotaryField = rotaryField | push;
}

#endif