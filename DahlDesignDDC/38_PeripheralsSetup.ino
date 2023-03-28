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

void PCA9555Setup()
{
  for (int i = 0; i < sizeof(PCA9555interruptPins)/sizeof(PCA9555interruptPins[0]); i++)
  {
    pinMode(PCA9555interruptPins[i], INPUT_PULLUP);
  }
  #if (BOARDTYPE == 2)
    if (PCA9555_I2C_NUMBER == 1)
    {
      Wire1.setSDA(SDA1PIN);
      Wire1.setSCL(SCL1PIN);
      wire1Init = true;
    }
    else
    {
      Wire.setSDA(SDA0PIN);
      Wire.setSCL(SCL0PIN);
      wire0Init = true;
    }
  #elif (USING_PCA9555 == 1)
    wire0Init = true;
  #endif
}

void startI2C()
{
  if(wire1Init)
  {
    Wire1.begin();
  }
  if(wire0Init)
  {
    Wire.begin();
  }
}
