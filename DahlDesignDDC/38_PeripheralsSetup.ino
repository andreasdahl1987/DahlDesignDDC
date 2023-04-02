void shiftRegisterSetup()
{
    if (SRCOUNT >= 1)
    {
        pinMode(SR1LATCH, OUTPUT);
        pinMode(SR1CLOCK, OUTPUT);
        pinMode(SR1DATA, INPUT);
    }
    if (SRCOUNT >= 2)
    {
        pinMode(SR2LATCH, OUTPUT);
        pinMode(SR2CLOCK, OUTPUT);
        pinMode(SR2DATA, INPUT);
    }
    if (SRCOUNT >= 3)
    {
        pinMode(SR3LATCH, OUTPUT);
        pinMode(SR3CLOCK, OUTPUT);
        pinMode(SR3DATA, INPUT);
    }
    if (SRCOUNT >= 4)
    {
        pinMode(SR4LATCH, OUTPUT);
        pinMode(SR4CLOCK, OUTPUT);
        pinMode(SR4DATA, INPUT);
    }
}


#if (USING_PCA9555 == 1)
void PCA9555Setup()
{
  for (int i = 0; i < sizeof(PCA9555interruptPins)/sizeof(PCA9555interruptPins[0]); i++)
  {
    pinMode(PCA9555interruptPins[i], INPUT_PULLUP);
  }
  #if (BOARDTYPE == 2)
    #if (PCA9555_I2C_NUMBER == 1 && USING_PCA9555 == 1)
    {
      Wire1.setSDA(SDA1PIN);
      Wire1.setSCL(SCL1PIN);
      wire1Init = true;
    }
    #elif (USING_PCA9555 == 1)
    {
      Wire.setSDA(SDA0PIN);
      Wire.setSCL(SCL0PIN);
      wire0Init = true;
    }
    #endif
  #else
    wire0Init = true;
  #endif
}
#endif

#if (USING_ADS1115 == 1)
void ADS1115Alert()
{
    Wire.beginTransmission();
    Wire.write(0b00000011); //Write to high threshold register
    Wire.write(0b10000000);
    Wire.write(0b00000000);
    Wire.endTransmission();

    Wire.beginTransmission();
    Wire.write(0b00000010); //Write to low threshold register
    Wire.write(0b00000000);
    Wire.write(0b00000000);
    Wire.endTransmission();
}


void ADS1115Setup()
{
  for(int i = 0; i<ADS1115_CHIPS; i++)
  {
    ADS1115sentReq[i] = false;  
    ADS1115channelCounter[i] = 0;
  }

  for(int i = 0 ; i<4*ADS1115_CHIPS; i++)
  {
    ADS1115value[i] = 0;  
  }
  
  
  #if (BOARDTYPE == 2)
    #if (ADS1115_I2C_NUMBER == 1 && USING_ADS1115 == 1)
      Wire1.setSDA(SDA1PIN);
      Wire1.setSCL(SCL1PIN);
      wire1Init = true;
    #elif(USING_ADS1115 == 1)
    {
      Wire.setSDA(SDA0PIN);
      Wire.setSCL(SCL0PIN);
      wire0Init = true;
    }
    #endif
  #else
    wire0Init = true;
  #endif
}
#endif


#if (USING_CB1 == 1 || USING_PCA9555 == 1 || USING_ADS1115 == 1)
void startI2C()
{
  #if(BOARDTYPE == 2)
  if(wire1Init)
  {
    Wire1.begin();
  }
  #endif
  if(wire0Init)
  {
    Wire.begin();
  }
}
#endif
