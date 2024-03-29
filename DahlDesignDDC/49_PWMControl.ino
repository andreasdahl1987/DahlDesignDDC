//------------------------------
//------PWM FUNCTIONS----------
//------------------------------

#if (PWMENABLED == 1)

void PWMtoggle(int8_t row, int8_t column, int8_t PWMChannel)
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

void rotary2PWM(int8_t row, int8_t col, bool reverse, int8_t PWMChannel)
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
                    PWMValues[PWMchannel] = PWMValues[PWMchannel] + 10 - (20 * reverse);
                }
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                if (pushState[modButtonRow-1][modButtonCol-1] == 1)
                {
                    PWMValues[PWMchannel] = PWMValues[PWMchannel] - 10 + (20 * reverse);
                }
            }
        }
    }

    //Adjusting 
    if (PWMValues[PWMchannel] < 0)
    {
      PWMValues[PWMchannel] = 0;
    }
    else if (PWMValues[PWMchannel] > 255)
    {
      PWMValues[PWMchannel] = 255;
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


//Under the hood

void PWMrun()
{
  for(int i = 0; i < PWMCount; i ++)
  {
    if(PWMIsOff[i])
      {
        analogWrite(PWMChannelPins[i], 0);
      }
    else
      {
        analogWrite(PWMChannelPins[i], PWMValues[i]);
      }
  }
}


#endif
