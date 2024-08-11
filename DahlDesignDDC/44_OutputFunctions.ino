#if(enableOutput == 1 || PCA9555_OUTPUT == 1 || CB1_PE1_OUTPUT == 1 || CB1_PE2_OUTPUT == 1)
void setOutput(uint8_t outputHub, int8_t pin, bool value)
{
  int8_t OutputHub = outputHub - 1;
  int8_t Pin = pin - 1;
  
  if(value)
  {
     outputStatus[OutputHub] |= (1 << Pin);
  }
  else
  {
     outputStatus[OutputHub] &=  ~(1 << Pin);
  }
}

void triggerOutput(uint8_t outputHub, int8_t pin, bool condition, bool blinkEnable, int blinkOnTimer, int blinkOffTimer)
{
  int8_t OutputHub = outputHub - 1;
  int8_t Pin = pin - 1;
  
  int timer = globalClock % (blinkOnTimer + blinkOffTimer);

  if(condition)
  {
    if (blinkEnable && timer > blinkOffTimer)
    {
        outputStatus[OutputHub] |= (1 << Pin);
    }
    if (!blinkEnable || (blinkEnable && timer < blinkOffTimer))
    {
        outputStatus[OutputHub] &=  ~(1 << Pin);
     }
  }
  else
  {
    outputStatus[OutputHub] &=  ~(1 << Pin);
  }
}

void rotaryOutput(uint8_t analogChannel, uint8_t hub, uint8_t startPin, uint8_t offset, uint8_t positions, bool reverse)
{
  int StartPin = startPin - 1;
  int Hub = hub - 1;
  uint8_t reference = analogLastCounter[analogChannel-1] + offset;
  if (reference > positions - 1)
  {
    reference = reference - positions;
  }
  if(reverse)
  {
    reference = positions - 1 - reference;
  }

  for(int i = StartPin; i < StartPin + positions; i ++)
  {
    if (i - StartPin == reference)
    {
      outputStatus[Hub] |= (1 << i);
    }
    else
    {
      outputStatus[Hub] &=  ~(1 << i);
    }
  }
}
#endif
