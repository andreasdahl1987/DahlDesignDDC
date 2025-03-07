#if(ENABLE_MOUSE == 1)

void leftMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(pushState[Row][Column] == 1)
  {
    Mouse.press(1);
  }
  else
  {
    Mouse.release(1);
  }
}

void middleMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(pushState[Row][Column] == 1)
  {
    Mouse.press(4);
  }
  else
  {
    Mouse.release(4);
  }
}

void rightMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(pushState[Row][Column] == 1)
  {
    Mouse.press(2);
  }
  else
  {
    Mouse.release(2);
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

#endif