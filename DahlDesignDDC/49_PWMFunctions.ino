//------------------------------
//------PWM FUNCTIONS----------
//------------------------------

#if (PWMENABLED == 1 || ROW6_PWMCOUNT > 0)

void PWMAdjustButtonSolo(int row, int column, int increment, int8_t PWMChannel, bool loop)
{
    int Row = row - 1;
    int Column = column - 1;
    int8_t PWMchannel = PWMChannel - 1;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
        if(rawState[Row][Column] == 1)
        {
          latchState[Row][Column] = true;          
        }
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }


    if(latchState[Row][Column])
    {
      PWMValues[PWMchannel] += increment;
      latchState[Row][Column] = false;
      if (PWMValues[PWMchannel] > 100)
      {
        if(loop){PWMValues[PWMchannel] = 0;}
        else {PWMValues[PWMchannel] = 100;}
      }
      else if (PWMValues[PWMchannel] < 0)
      {
        if(loop){PWMValues[PWMchannel] = 100;}
        else {PWMValues[PWMchannel] = 0;}
      }
    }
    else
    {
      latchState[Row][Column] = false;
    }
}

void PWMAdjustButton(int row, int column, int increment, int8_t PWMChannel, bool loop)
{
    int Row = row - 1;
    int Column = column - 1;
    int8_t PWMchannel = PWMChannel - 1;
    uint8_t Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
        if(rawState[Row][Column] == 1)
        {
          latchState[Row][Column] = true;          
        }
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }


    if(latchState[Row][Column] && pushState[modButtonRow-1][modButtonCol-1] == 1)
    {
      PWMValues[PWMchannel] += increment;
      latchState[Row][Column] = false;
      if (PWMValues[PWMchannel] > 100)
      {
        if(loop){PWMValues[PWMchannel] = 0;}
        else {PWMValues[PWMchannel] = 100;}
      }
      else if (PWMValues[PWMchannel] < 0)
      {
        if(loop){PWMValues[PWMchannel] = 100;}
        else {PWMValues[PWMchannel] = 0;}
      }
    }
    else
    {
      latchState[Row][Column] = false;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
      Joystick.setButton(Number, pushState[Row][Column]);
    }
}

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

void funkyPWM(int Arow, int Acol, int Bcol, bool reverse, int8_t PWMChannel, int8_t stepSize) {

    int Row = Arow - 1;
    int Column = Acol - 1;
    int Number = buttonNumber[Row][Column];
    int8_t PWMchannel = PWMChannel -1;
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
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              PWMValues[PWMchannel] = PWMValues[PWMchannel] + stepSize - (2 * stepSize * reverse);
            }
        }

        else if ((latchLock[Row][bCol] && pushState[Row][Column] == 3) || (latchLock[Row][Column] && pushState[Row][Column] == 1))
        {
            switchTimer[Row][bCol] = globalClock;
            if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
              PWMValues[PWMchannel] = PWMValues[PWMchannel] - stepSize + (2 * stepSize * reverse);
            }
        }
    }

    else
    {
        latchLock[Row][bCol] = 0;
        latchLock[Row][Column] = 0;
    }

    //Adjustment
    if (PWMValues[PWMchannel] < 0)
    {
      PWMValues[PWMchannel] = 0;
    }
    else if (PWMValues[PWMchannel] > 100)
    {
      PWMValues[PWMchannel] = 100;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
    Joystick.setButton(Number + reverse, (globalClock - switchTimer[Row][Column] < funkyPulse));
    Joystick.setButton(Number + 1 - reverse, (globalClock - switchTimer[Row][bCol] < funkyPulse));
    }
}

void PEC11PWM(int row, int col, bool reverse, int8_t PWMChannel, int8_t stepSize) {

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];
    int8_t PWMchannel = PWMChannel -1;

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          PWMValues[PWMchannel] = PWMValues[PWMchannel] + stepSize - (2 * stepSize * reverse);
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          PWMValues[PWMchannel] = PWMValues[PWMchannel] - stepSize + (2 * stepSize * reverse);
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Adjustment
    if (PWMValues[PWMchannel] < 0)
    {
      PWMValues[PWMchannel] = 0;
    }
    else if (PWMValues[PWMchannel] > 100)
    {
      PWMValues[PWMchannel] = 100;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
    }

}

void rotaryPulsePWM(int row, int column, bool reverse, int8_t PWMChannel, int8_t stepSize)
{
    int Row = row - 1;
    int Column = column - 1;
    int Column2 = column;
    int Number = buttonNumber[Row][Column];
    int Number2 = Number+1;

    int8_t PWMchannel = PWMChannel -1;
    
    if(reverse)
    {
      Column = column;
      Column2 = column - 1;
    }

    //Pulse arm 1
    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        if(rawState[Row][Column] == 1)
        {
          switchTimer[Row][Column] = globalClock;
          if (pushState[modButtonRow-1][modButtonCol-1] == 1)
          {
              PWMValues[PWMchannel] = PWMValues[PWMchannel] + stepSize;
          }          
        }
        pushState[Row][Column] = rawState[Row][Column];
    }
    if (pushState[modButtonRow-1][modButtonCol-1] == 0)
    {
      if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
      {
          pushState[Row][Column] = rawState[Row][Column];
      }
  
      if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
      {
          toggleTimer[Row][Column] = globalClock;
      }
  
      if ((globalClock - toggleTimer[Row][Column]) < pulseEncCD)
      {
          Joystick.setButton(Number, 1);
      }
      else
      {
          Joystick.setButton(Number, 0);
      }
    }

    //Pulse arm 2
    if (pushState[Row][Column2] != rawState[Row][Column2] && (globalClock - switchTimer[Row][Column2]) > buttonCooldown)
    {
        if(rawState[Row][Column2] == 1)
        {
          switchTimer[Row][Column2] = globalClock; 
          if (pushState[modButtonRow-1][modButtonCol-1] == 1)
          {
              PWMValues[PWMchannel] = PWMValues[PWMchannel] - stepSize;
          }           
        }
        pushState[Row][Column2] = rawState[Row][Column2];
    }
    
    if (pushState[modButtonRow-1][modButtonCol-1] == 0)
    {
      if ((globalClock - switchTimer[Row][Column2]) > buttonCooldown)
      {
          pushState[Row][Column2] = rawState[Row][Column2];
      }
  
      if ((globalClock - switchTimer[Row][Column2]) < buttonCooldown)
      {
          toggleTimer[Row][Column2] = globalClock;
      }
  
      if ((globalClock - toggleTimer[Row][Column2]) < pulseEncCD)
      {
          Joystick.setButton(Number2, 1);
      }
      else
      {
          Joystick.setButton(Number2, 0);
      }
    }

    //Adjustment
    if (PWMValues[PWMchannel] < 0)
    {
      PWMValues[PWMchannel] = 0;
    }
    else if (PWMValues[PWMchannel] > 100)
    {
      PWMValues[PWMchannel] = 100;
    }
}


void rotaryAnalogPWM(int analogChannel, int8_t PWMChannel, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
{
    int N = analogChannel - 1;
        
    int8_t PWMchannel = PWMChannel -1;

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

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

    int positions[12] = { pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11, pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }

    result--;

    if (reverse)
    {
        result = 11 - result;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
        {
          //Engage encoder pulse timer
          analogTimer2[N] = globalClock;

          //Update difference, storing the value in pushState on pin 2
          analogTempState[N] = result - analogLastCounter[N];

          //Give new value to pushState
          analogLastCounter[N] = result;
        }
    }

    PWMValues[PWMchannel] = analogLastCounter[N] * 100 / 11;
}

void rotaryAnalogPWM12(int analogChannel, int8_t PWMChannel, int8_t stepSize, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
{
    int N = analogChannel - 1;
    int8_t PWMchannel = PWMChannel -1;
    int Number = analogButtonNumber[N];

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

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

    int positions[12] = { pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11, pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }

    result--;

    if (reverse)
    {
        result = 11 - result;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
        {
            //----------------------------------------------
            //----------------PMW VOLUME--------------------
            //----------------------------------------------

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                //Engage encoder pulse timer
                analogTimer2[N] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                analogTempState[N] = result - analogLastCounter[N];

                //Give new value to pushState
                analogLastCounter[N] = result;

                //Adjusting bite up/down
                if ((analogTempState[N] > 0 && analogTempState[N] < 5) || analogTempState[N] < -5)
                {
                    PWMValues[PWMchannel] = PWMValues[PWMchannel] + stepSize;
                }
                else
                {
                    PWMValues[PWMchannel] = PWMValues[PWMchannel] - stepSize;
                }
            }
            else
            {
                 //Engage encoder pulse timer
                analogTimer2[N] = globalClock;

                //Update difference, storing the value in pushState on pin 2
                analogTempState[N] = result - analogLastCounter[N];

                //Give new value to pushState
                analogLastCounter[N] = result;
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

    //12 - position switch

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
        analogTempState[N] = 0; //Refreshing encoder mode difference

        for (int i = 0; i < 12; i++)
        {
            if (i == analogLastCounter[N])
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
        }
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

void PWMPot(int analogChannel, int startValue, int endValue, int8_t PWMchannel)
{
    int N = analogChannel - 1;
    
    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

    int pinValue;
    
    if (analogPins[N] > 49)
    {
      pinValue = ADS1115value[analogPins[N] - ADC_CORR];
    }
    else
    {
      pinValue = analogRead(analogPins[N]);
    }
    
    #else

    int pinValue = analogRead(analogPins[N]);
    
    #endif

    int8_t PWMChannel = PWMchannel - 1;
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
  #if(ROW6_PWMCOUNT > 0)

  for(int i = 0; i < ROW6_PWMCOUNT; i ++)
  {
    int PWMValue = PWMStart[i] + (PWMValues[i] * (PWMEnd[i] - PWMStart[i]) / 100);

    if(PWMIsOff[i])
      {
        analogWrite(PWMChannelPins[i], 0);
      }
    else
      {
        analogWrite(PWMChannelPins[i], PWMValue);
      }
  }

  #else
  
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
      }
  }
  #endif
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
