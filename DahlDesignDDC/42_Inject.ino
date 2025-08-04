void switchTableInject(int8_t pin, int8_t row, int8_t column)
{
	int8_t Pin = pin;
	int8_t Row = row - 1;
	int8_t Column = column - 1;

	rawState[Row][Column] = !digitalRead(Pin);
}

void analogInject(int8_t analogChannel, int8_t row, int8_t column, int startValue, int endValue, uint8_t threshold)
{

  int N = analogChannel - 1;

  #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1 || LOADCELL_ENABLED == 1)

  int value;
  if (analogPins[N] > 49)
  {
    value = ADS1115value[analogPins[N] - ADC_CORR];
  }
  else
  {
    value = analogRead(analogPins[N]);
  }
  
  #else

  int value = analogRead(analogPins[N]);
  
  #endif

  int diff; 

  if (injectMute)
  {
    rawState[row-1][column-1] = 0;
  }
  else
  {
    if (endValue > startValue)
    {
      diff = endValue-startValue;
      if (value > (startValue + (diff * threshold / 100)) && value <= endValue)
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
      diff = startValue - endValue;
      if (value < (startValue - (diff * threshold / 100)) && value >= endValue)
      {
        rawState[row-1][column-1] = 1;
      }
      else
      {
        rawState[row-1][column-1] = 0;
      }
    }
  }
}

void analogInjectSingle(int8_t analogChannel, int8_t row, int8_t column, int startValue, int endValue, uint8_t threshold)
{
  int N = analogChannel - 1;
  
  #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1 || LOADCELL_ENABLED == 1)

  int value;
  if (analogPins[N] > 49)
  {
    value = ADS1115value[analogPins[N] - ADC_CORR];
  }
  else
  {
    value = analogRead(analogPins[N]);
  }
  
  #else

  int value = analogRead(analogPins[N]);
  
  #endif
  
  int diff; 

  if (injectMute)
  {
    rawState[row-1][column-1] = 0;
  }
  else
  {
    if (endValue > startValue)
    {
      diff = endValue-startValue;
      if (value > (startValue + (diff * threshold / 100)))
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
      diff = startValue - endValue;
      if (value < (startValue - (diff * threshold / 100)))
      {
        rawState[row-1][column-1] = 1;
      }
      else
      {
        rawState[row-1][column-1] = 0;
      }
    }
  } 
}

void rotaryInject(int8_t analogChannel, int8_t switchPosition, int8_t row, int8_t column)
{
    rawState[row-1][column-1] = (analogLastCounter[analogChannel-1] + 1 == switchPosition) * !injectMute;
}
