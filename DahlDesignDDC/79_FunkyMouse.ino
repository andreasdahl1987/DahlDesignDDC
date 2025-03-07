#if (ENABLE_MOUSE == 1)

#if (MOUSE_LOGCURVE == 0)
float degree2rad(int val, int max)
{
    return val * M_PI / (max << 1);
}
#endif

void setMouseSpeed(int speed)
{
  MOUSESpeed = speed;
}

void funkyMouseScroll(int Arow, int Acol, int Bcol, bool reverse)
{
	int Row = Arow - 1;
	int Column = Acol - 1;

	int bCol = Bcol - 1;

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
			Mouse.move(0, 0, reverse ? -1 : 1); // 1 - Scroll Down, -1 - Scroll Up
		}
		else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
		{
			switchTimer[Row][bCol] = globalClock;
			Mouse.move(0, 0, reverse ? 1 : -1);
		}
	}
	else
	{
		latchLock[Row][bCol] = 0;
		latchLock[Row][Column] = 0;
	}
}

void funkyMouseButton(int row, int column, int aCol, int bCol, int cCol, int dCol, uint8_t b)
{
	int Row = row - 1;
	int Column = column - 1;

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

	//Change switch mode
	if (pushState[Row][Column] == 0)
	{
		switchModeLock[Row][Column] = false;
		latchLock[Row][Column] = false;
	}
	else
	{
		if (pushState[Row][Column] == 1 && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && !switchModeLock[Row][Column])
		{
			switchModeLock[Row][Column] = true;
			switchMode[Row][Column] = !switchMode[Row][Column];
			latchLock[Row][Column] = false;
			latchState[Row][Column] = false;
		}
		if (pushState[Row][Column] == 1 && !latchLock[Row][Column])
		{
			latchLock[Row][Column] = true;
			latchState[Row][Column] = !latchState[Row][Column];
			Mouse.click(b);
		}
	}
}

/*
void funkyMouseMove(int row, int column, int pCol, int Col1, int Col2, int Col3, uint8_t direction)
{
	int Row = row - 1;
	int Column = column - 1;

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

	if(pushState[Row][Column])
	{
		uint8_t pixels = (globalClock - toggleTimer[Row][Column]);
		if(switchTimer[Row][Column] == globalClock) pixels = 1;
		else if(globalClock < switchTimer[Row][Column] + MOUSE_ACCELTIME)
		{
			#if (MOUSE_LOGCURVE == 1)
			pixels = round(pixels * log10(((globalClock - switchTimer[Row][Column]) / (MOUSE_ACCELTIME / 9.)) + 1));
			#else
			pixels = round(pixels * sqrt(sin(degree2rad(globalClock - switchTimer[Row][Column], MOUSE_ACCELTIME))));
			#endif
		}
		if (pixels > 0)
		{
			switch(MOUSESpeed) // Optimization for specific speeds
			{
				case 10:
					break;
				case 20:
					pixels <<= 1;
					break;
				case 40:
					pixels <<= 2;
					break;
				case 80:
					pixels <<= 3;
					break;
				case 160:
					pixels <<= 4;
					break;
				default:
					pixels *= MOUSESpeed / 10.;
			}
			Mouse.move(direction == 1 ? -pixels : (direction == 2 ? pixels : 0), direction == 3 ? -pixels : (direction == 4 ? pixels : 0));
			toggleTimer[Row][Column] = globalClock;
		}
	}
}
*/
void funkyMouseMove(int row, int column, int pCol, int Col1, int Col2, int Col3, uint8_t direction, uint8_t mouseSpeed, uint8_t mouseSpeed2)
{

  uint8_t segment = (globalClock % 100) / 10;

  if (segment != oldSegment)
  {
    int output = 0;

    int Row = row - 1;
	  int Column = column - 1;

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

    if(!pushState[Row][Column])
    {
      toggleTimer[Row][Column] = globalClock;
    }

    if(globalClock - toggleTimer[Row][Column] > 2000)
    {
      output = 127 * pushState[Row][Column] * mouseSpeed2 /100;
    }
    else if(globalClock - toggleTimer[Row][Column] < 1000)
    {
      output = 127 * pushState[Row][Column] * mouseSpeed /100;
    }
    else
    {
      int diff = (mouseSpeed2 - mouseSpeed) * (globalClock - toggleTimer[Row][Column]) / 1000;
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
  
    oldSegment = segment;
  }
} 

#endif
