#if (BOARDTYPE == 0 && ENABLE_MOUSE == 1)
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

void funkyMouseButton(int row, int column, int aCol, int bCol, int cCol, int dCol, bool RightClick)
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
			Mouse.click(RightClick ? MOUSE_RIGHT : MOUSE_LEFT);
		}
	}
}

void funkyMouseMove(int row, int column, int pCol, int Col1, int Col2, int Col3, bool Up, bool Down, bool Left, bool Right)
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
				toggleTimer[Row][Column] = globalClock - 1;
			}
			pushState[Row][Column] = rawState[Row][Column];
		}
	}

	if(pushState[Row][Column])
	{
		uint8_t pixels = (globalClock - toggleTimer[Row][Column]);
		if(globalClock < switchTimer[Row][Column] + 720)
		{
			float radian = ((globalClock - switchTimer[Row][Column]) << 3) / 3671.;
			pixels = ceil(pixels * sin(radian));
		}
		pixels <<= 1;
		Mouse.move(Right ? pixels : (Left ? -pixels : 0), Up ? -pixels : (Down ? pixels : 0));
		toggleTimer[Row][Column] = globalClock;
	}
}
#endif
