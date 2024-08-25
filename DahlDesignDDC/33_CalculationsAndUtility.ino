float curveFilter(int input, int releasedValue, int pressedValue, int curvePush, float expFactor)
{
    float Input = input;
    int PressedValue = pressedValue;
    int ReleasedValue = releasedValue;

    if (curvePush == 0)
    {
        return Input;
    }

    if (curvePush < 0)
    {
        if (releasedValue < pressedValue)
        {
            PressedValue = PressedValue - clutchTopDeadzone;
            ReleasedValue = ReleasedValue + clutchBottomDeadzone;
            if (Input < ReleasedValue)
            {
                Input = ReleasedValue;
            }
            if (Input > PressedValue)
            {
                Input = PressedValue;
            }
            Input = (Input - ReleasedValue) * pow((1 + Input - ReleasedValue), expFactor);
        }
        else if (pressedValue < releasedValue)
        {
            PressedValue = PressedValue + clutchTopDeadzone;
            ReleasedValue = ReleasedValue - clutchBottomDeadzone;
            if (Input > ReleasedValue)
            {
                Input = ReleasedValue;
            }
            if (Input < PressedValue)
            {
                Input = PressedValue;
            }
            Input = (ReleasedValue - Input) * pow((1 + ReleasedValue - Input), expFactor);
        }
    }
    else if (curvePush > 0)
    {
        if (ReleasedValue < PressedValue)
        {
            if (Input < ReleasedValue)
            {
                Input = ReleasedValue;
            }
            if (Input > PressedValue)
            {
                Input = PressedValue;
            }
            Input = (PressedValue - Input) * pow((1 + PressedValue - Input), expFactor);
        }
        else if (PressedValue < ReleasedValue)
        {
            if (Input > ReleasedValue)
            {
                Input = ReleasedValue;
            }
            if (Input < PressedValue)
            {
                Input = PressedValue;
            }
            Input = (Input - PressedValue) * pow((1 + Input - PressedValue), expFactor);
        }
    }

    return Input;
}

void checkValue(int analogChannel)
{

int N = analogChannel - 1;
  if(analogPins[N] < 50)
  {
    Serial.print("Channel ");
    Serial.print(String(analogChannel));
    Serial.print(" reading: ");
    Serial.println(analogRead(analogPins[N]));
  }
  #if (USING_CB1 == 1 || USING_ADS1115 == 1 || ENABLE_OVERSAMPLING == 1)
  else
  {
    Serial.print("Channel ");
    Serial.print(String(analogChannel));
    Serial.print(" reading: ");
    Serial.println(ADS1115value[analogPins[N]-ADC_CORR]);
  }
  #endif
}

#if (PWMENABLED == 1 || ROW6_PWMCOUNT > 0)
void checkPWM(int PWMchannel)
{
    int PWMChannel = PWMchannel - 1;
    int PWMValue = PWMStart[PWMChannel] + (PWMValues[PWMChannel] * (PWMEnd[PWMChannel] - PWMStart[PWMChannel]) / 100);
    Serial.print("Channel ");
    Serial.print(PWMchannel);
    Serial.print(" value: ");
    Serial.println(PWMValue);
}
#endif

void refreshRate()
{
  if(globalCounter == 10)
  {
    Serial.print("Refresh rate: ");
    Serial.print(10000000/(micros()-globalTimer));
    Serial.println(" Hz");
    globalTimer = micros();
    globalCounter = 0;
  }
}

#if (BOARDTYPE == 2)
void firmwareUploadMode(int button1Row, int button1Column, int button2Row, int button2Column, unsigned long timer)
{
    int b1Row = button1Row - 1;
    int b1Col = button1Column -1;
    int b2Row = button2Row - 1;
    int b2Col = button2Column - 1;
    
    if (rawState[b1Row][b1Col] == 0 || rawState[b2Row][b2Col] == 0)
    {
        bootTimer = globalClock;
    }
    
    if (globalClock - bootTimer > timer)
    {
        reset_usb_boot(0,0);
    }
}
#endif

#if (USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)
void CB1Oversampling()
{
  if(oversamples.available() >= 512)
  {
    long val1 = 0;
    long val2 = 0;
    long val3 = 0;
    long val4 = 0;
    for(int i = 0; i < 256; i++)
    {
      val1 += oversamples.read();
      val2 += oversamples.read();
      val3 += oversamples.read();
      val4 += oversamples.read();
    }
    #if (USING_CB1 == 1)
    ADS1115value[8] = val1 / 32;  
    ADS1115value[9] = val2 / 32;
    ADS1115value[10] = val3 / 32;
    ADS1115value[11] = val4 / 32;
    #else
    ADS1115value[0] = val1 / 32;  
    ADS1115value[1] = val2 / 32;
    ADS1115value[2] = val3 / 32;
    ADS1115value[3] = val4 / 32;
    #endif
  } 
}
#endif

void outputPinsSetup()
{
  if (outputPins[0] != 99)
  {
    for(int i = 0; i < outputPinsCount; i++)
    {
      pinMode(outputPins[i], OUTPUT);
      digitalWrite(outputPins[i], LOW);
    }
  }
}
