#if (ENABLE_MOUSE == 1)

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
      case 1: 
        Mouse.move(output,0);
        break;
      case 2:
        Mouse.move(-output,0);
        break;
      case 3:
        Mouse.move(0,output);
        break;
      case 4:
        Mouse.move(0,-output);
        break;
    }
    mouseRan = true;
  }
} 

#endif
