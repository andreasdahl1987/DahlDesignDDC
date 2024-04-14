//------------------------------
//------PWM FUNCTIONS----------
//------------------------------

#if (PWMENABLED == 1)

void PWMToggle(int8_t row, int8_t column, int8_t PWMChannel)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t PWMchannel = PWMChannel - 1;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if(pushState[Row][Column])
    {
      PWMIsOff[PWMchannel] = true;
    }
    else
    {
      PWMIsOff[PWMchannel] = false;
    }
}

void rotary2PWM(int8_t row, int8_t col, bool reverse, int8_t PWMChannel, int8_t stepSize)
{
    int8_t Row = row - 1;
    int8_t Column = col - 1;
    int8_t Number = buttonNumber[Row][Column];

    int8_t PWMchannel = PWMChannel -1;

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];

    bool array[2] = { Pin1, Pin2 };

    int pos = 0;

    for (int i = 0; i < 2; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > (encoder2Wait + encoder2Pulse + encoderCooldown))
        {
            switchTimer[Row][Column] = globalClock;
            latchLock[Row][Column] = true;
        }
        else if ((globalClock - switchTimer[Row][Column] > encoder2Wait) && latchLock[Row][Column])
        {
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //Make sure we dont do this again
            latchLock[Row][Column] = false;

            int8_t difference = pushState[Row][Column + 1];
            if ((difference > 0 && difference < 2) || difference < -2)
            {
                if (pushState[modButtonRow-1][modButtonCol-1] == 1)
                {
                    PWMValues[PWMchannel] = PWMValues[PWMchannel] + stepSize - (2 * stepSize * reverse);
                }
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                if (pushState[modButtonRow-1][modButtonCol-1] == 1)
                {
                    PWMValues[PWMchannel] = PWMValues[PWMchannel] - stepSize + (2 * stepSize * reverse);
                }
            }
        }
    }

    //Adjusting 
    if (PWMValues[PWMchannel] < 0)
    {
      PWMValues[PWMchannel] = 0;
    }
    else if (PWMValues[PWMchannel] > 100)
    {
      PWMValues[PWMchannel] = 100;
    }

    int8_t difference = pushState[Row][Column + 1];
    if (difference != 0 && pushState[modButtonRow-1][modButtonCol-1] == 0)
    {
        if (globalClock - switchTimer[Row][Column + 1] < encoder2Pulse + encoder2Wait)
        {
            if ((difference > 0 && difference < 2) || difference < -2)
            {
                Joystick.setButton(Number + reverse, 1);
                Joystick.setButton(Number + 1 - reverse, 0);
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                Joystick.setButton(Number + reverse, 0);
                Joystick.setButton(Number + 1 - reverse, 1);
            }
            else
            {
                pushState[Row][Column + 1] = 0;
            } 
        }
        else
        {
            pushState[Row][Column + 1] = 0;
            pushState[Row][Column] = result;
            Joystick.setButton(Number, 0);
            Joystick.setButton(Number + 1, 0);
        }
    }
}

void PWMPot(int analogPin, int analogChannel, int startValue, int endValue, int8_t PWMchannel)
{

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

    int pinValue;
    if (analogPin > 49)
    {
      pinValue = ADS1115value[analogPin - ADC_CORR];
    }
    else
    {
      pinValue = analogRead(analogPin);
    }
    
    #else

    int pinValue = analogRead(analogPin);
    
    #endif

    int8_t PWMChannel = PWMchannel - 1;
    int N = analogChannel - 1;
    float normalized = 0;

    if (endValue > startValue)
    {
        endValue = endValue - clutchTopDeadzone;
        startValue = startValue + clutchBottomDeadzone;
        float gap = endValue - startValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (pinValue - startValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }
    else if (endValue < startValue)
    {
        endValue = endValue + clutchTopDeadzone;
        startValue = startValue - clutchBottomDeadzone;
        float gap = startValue - endValue;
        float normFactor = 1000 / gap;
        normalized = normFactor * (startValue - pinValue);
        if (normalized < 0)
        {
            normalized = 0;
        }
    }

    total[N] = total[N] - readings[N][readIndex[N]];
    readings[N][readIndex[N]] = normalized;
    total[N] = total[N] + readings[N][readIndex[N]];

    readIndex[N]++;

    if (readIndex[N] > (reads - 1))
    {
        readIndex[N] = 0;
    }

    average[N] = total[N] / reads;
    if (average[N] > 1000)
    {
        average[N] = 1000;
    }

    //----------------SET PWM----------------
    PWMValues[PWMChannel] = average[N]/10;
}

void setPWM(int8_t PWMchannel, uint8_t value)
{
  int8_t PWMChannel = PWMchannel - 1;

  PWMStart[PWMChannel] = 0;
  PWMEnd[PWMChannel] = value;
  PWMIsOff[PWMChannel] = false;
  PWMValues[PWMChannel] = 100;
}

void triggerPWM(int8_t PWMchannel, bool condition, bool blinkEnable, int blinkOnTimer, int blinkOffTimer)
{

  int8_t PWMChannel = PWMchannel - 1;

  int timer = globalClock % (blinkOnTimer + blinkOffTimer);

  if(condition)
  {
    if (blinkEnable && timer < blinkOffTimer)
    {
        PWMIsOff[PWMChannel] = true;
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        PWMIsOff[PWMChannel] = false;
     }
  }
  else
  {
    PWMIsOff[PWMChannel] = true;
  }
}


//Under the hood


void PWMrun()
{
  for(int i = 0; i < PWMCount; i ++)
  {
    int PWMValue = PWMStart[i] + (PWMValues[i] * (PWMEnd[i] - PWMStart[i]) / 100);

    if(PWMIsOff[i])
      {
        analogWrite(PWMChannelPins[i], 0);
      }
    else
      {
        analogWrite(PWMChannelPins[i], PWMValue);
        Serial.println(PWMValue);
      }
  }
}

void PWMSetup(int8_t PWMchannel, bool isOff, uint8_t minValue, uint8_t maxValue, int16_t volume)
{
  int8_t PWMChannel = PWMchannel - 1;

  PWMStart[PWMChannel] = minValue;
  PWMEnd[PWMChannel] = maxValue;
  PWMIsOff[PWMChannel] = isOff;
  PWMValues[PWMChannel] = volume;
}


#endif
