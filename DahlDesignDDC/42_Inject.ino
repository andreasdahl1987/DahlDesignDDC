void switchTableInject(int8_t pin, int8_t row, int8_t column)
{
	int8_t Pin = pin;
	int8_t Row = row - 1;
	int8_t Column = column - 1;

	rawState[Row][Column] = !digitalRead(Pin);
}

void analogInject(int8_t pin, int8_t row, int8_t column, int pressed, int released, uint8_t threshold)
{
  int value = analogRead(pin);
  int diff; 

  if (pressed > released)
  {
    diff = pressed-released;
    if (value > (released + (diff * threshold / 100)))
    {
      rawState[row-1][column-1] = 1;
    }
    else
    {
      rawState[row-1][column-1] = 0;
    }
  }
  else
  {
    diff = released - pressed;
    if (value < (released - (diff * threshold / 100)))
    {
      rawState[row-1][column-1] = 1;
    }
    else
    {
      rawState[row-1][column-1] = 0;
    }
  }
}
