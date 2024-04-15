void shiftRegisterScan()
{
    if (SRCOUNT == 0)
    {
        return;
    }
    //SR1
    if (SRCOUNT >= 1)
    {
        digitalWrite(SR1LATCH, 0); //Enable parallel inputs
        digitalWrite(SR1CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR1CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR1LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR1CHAIN; i++)
        {
            uint8_t rowNumber = i / 8; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR1DATA); //Set the bit to rawState
            digitalWrite(SR1CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR1CLOCK, 1); //Clock high to get new bit to SR1DATA
        }
    }

    if (SRCOUNT >= 2)
    {
        digitalWrite(SR2LATCH, 0); //Enable parallel inputs
        digitalWrite(SR2CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR2CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR2LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR2CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR2DATA); //Set the bit to rawState
            digitalWrite(SR2CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR2CLOCK, 1); //Clock high to get new bit to SR2DATA
        }
    }

    if (SRCOUNT >= 3)
    {
        digitalWrite(SR3LATCH, 0); //Enable parallel inputs
        digitalWrite(SR3CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR3CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR3LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR3CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN + SR2CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR3DATA); //Set the bit to rawState
            digitalWrite(SR3CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR3CLOCK, 1); //Clock high to get new bit to SR3DATA
        }
    }

    if (SRCOUNT >= 4)
    {
        digitalWrite(SR4LATCH, 0); //Enable parallel inputs
        digitalWrite(SR4CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR4CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR4LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR4CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN + SR2CHAIN + SR3CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR4DATA); //Set the bit to rawState
            digitalWrite(SR4CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR4CLOCK, 1); //Clock high to get new bit to SR4DATA
        }
    }
}

#if (USING_PCA9555 == 1)
void PCA9555Run(int address, int interruptPin, int row)
{
  #if (PCA9555_I2C_NUMBER == 0)
  if (digitalRead(interruptPin) == 0)
  {
    Wire.beginTransmission(address);
    Wire.write(0x01);
    Wire.endTransmission();
    
    Wire.requestFrom(address,2);
    int firstByte = Wire.read();
    int lastByte = Wire.read();
    
    for ( int i = 0; i < 8; i++)
    {
      rawState[row][i] = !bitRead(firstByte,i);
      rawState[row-1][i] = !bitRead(lastByte, i);
    }
  }
  #else
  if (digitalRead(interruptPin) == 0)
  {
    Wire1.beginTransmission(address);
    Wire1.write(0x01);
    Wire1.endTransmission();
    
    Wire1.requestFrom(address,2);
    int firstByte = Wire1.read();
    int lastByte = Wire1.read();
    
    for ( int i = 0; i < 8; i++)
    {
      rawState[row][i] = !bitRead(firstByte,i);
      rawState[row-1][i] = !bitRead(lastByte, i);
    }
  }
  #endif
}
#endif

#if (USING_CB1 == 1)
void PCA9555CB1(int address, int interruptPin, int row)
{
  if (digitalRead(interruptPin) == 0)
  {
    Wire.beginTransmission(address);
    Wire.write(0x01);
    Wire.endTransmission();
    
    Wire.requestFrom(address,2);
    int firstByte = Wire.read();
    int lastByte = Wire.read();
    
    for ( int i = 0; i < 8; i++)
    {
      rawState[row][7-i] = !bitRead(firstByte,i);
      rawState[row-1][i] = !bitRead(lastByte, i);
    }
  }
}

void ADC1_CB1(int alertPin)
{
#if (DISABLE_ALERT_PINS == 0)
    
  if (!sentReq1)
  {
    Wire1.beginTransmission(0x48);
    Wire1.write(0b00000001);
    Wire1.write(0b11000001 | (channelCount1 << 4) | CB1_ADC1_GAIN << 1);
    Wire1.write(0b00000100 | (CB1_ADC1_RATE << 5));
    Wire1.endTransmission();

    sentReq1 = true;
  }

  if (sentReq1 && digitalRead(alertPin) == 0)
  {
    Wire1.beginTransmission(0x48);
    Wire1.write(0b00000000);
    Wire1.endTransmission();

    uint8_t valAddress = channelCount1;
    
    Wire1.requestFrom(0x48, 2);
    ADS1115value[valAddress]= Wire1.read()<<8;
    ADS1115value[valAddress] |= Wire1.read();
    if (ADS1115value[valAddress] > 32767)
    {
      ADS1115value[valAddress] = 0;
    }
    sentReq1 = false;

    channelCount1 ++;

    if (channelCount1 >= CB1_ADC1_CHANNELS)
    {
      channelCount1 = 0;
    }
  }

  #else

  if (!sentReq1)
  {
    Wire1.beginTransmission(0x48);
    Wire1.write(0b00000001);
    Wire1.write(0b11000001 | (channelCount1 << 4) | CB1_ADC1_GAIN << 1);
    Wire1.write(0b00000011 | (CB1_ADC1_RATE << 5));
    Wire1.endTransmission();

    sentReq1 = true;
  }

  if (sentReq1)
  {
    Wire1.requestFrom(0x48, 2);
    int convStatus = (Wire1.read()>>7);
    if (convStatus == 1)
    {
      Wire1.beginTransmission(0x48);
      Wire1.write(0b00000000);
      Wire1.endTransmission();

      uint8_t valAddress = channelCount1;
      
      Wire1.requestFrom(0x48, 2);
      ADS1115value[valAddress]= Wire1.read()<<8;
      ADS1115value[valAddress] |= Wire1.read();
      if (ADS1115value[valAddress] > 32767)
      {
        ADS1115value[valAddress] = 0;
      }
      sentReq1 = false;

      channelCount1 ++;

      if (channelCount1 >= CB1_ADC1_CHANNELS)
      {
        channelCount1 = 0;
      }
    }
  }
  #endif
}

void ADC2_CB1(int alertPin)
{
#if (DISABLE_ALERT_PINS == 0)
    
  if (!sentReq2)
  {
    Wire1.beginTransmission(0x49);
    Wire1.write(0b00000001);
    Wire1.write(0b11000001 | (channelCount2 << 4) | CB1_ADC2_GAIN << 1);
    Wire1.write(0b00000100 | (CB1_ADC2_RATE << 5));
    Wire1.endTransmission();

    sentReq2 = true;
  }

  if (sentReq2 && digitalRead(alertPin) == 0)
  {
    Wire1.beginTransmission(0x49);
    Wire1.write(0b00000000);
    Wire1.endTransmission();

    uint8_t valAddress = 4 + channelCount2;
    
    Wire1.requestFrom(0x49, 2);
    ADS1115value[valAddress]= Wire1.read()<<8;
    ADS1115value[valAddress] |= Wire1.read();
    if (ADS1115value[valAddress] > 32767)
    {
      ADS1115value[valAddress] = 0;
    }
    sentReq2 = false;

    channelCount2 ++;

    if (channelCount2 >= CB1_ADC2_CHANNELS)
    {
      channelCount2 = 0;
    }
  }

  #else

  if (!sentReq2)
  {
    Wire1.beginTransmission(0x49);
    Wire1.write(0b00000001);
    Wire1.write(0b11000001 | (channelCount2 << 4) | CB1_ADC2_GAIN << 1);
    Wire1.write(0b00000011 | (CB1_ADC2_RATE << 5));
    Wire1.endTransmission();

    sentReq2 = true;
  }

  if (sentReq2)
  {
    Wire1.requestFrom(0x49, 2);
    int convStatus = (Wire1.read()>>7);
    if (convStatus == 1)
    {
      Wire1.beginTransmission(0x49);
      Wire1.write(0b00000000);
      Wire1.endTransmission();

      uint8_t valAddress = 4+channelCount2;
      
      Wire1.requestFrom(0x49, 2);
      ADS1115value[valAddress]= Wire1.read()<<8;
      ADS1115value[valAddress] |= Wire1.read();
      if (ADS1115value[valAddress] > 32767)
      {
        ADS1115value[valAddress] = 0;
      }
      sentReq2 = false;

      channelCount2 ++;

      if (channelCount2 >= CB1_ADC2_CHANNELS)
      {
        channelCount2 = 0;
      }
    }
  }
  #endif
}

void CB1switchTable()
{
  //Row 5 & 6

  if (ROW5_ACTIVE == 1)
  {
    for(int i = 0; i < 8; i++)
    {
      rawState[4][i] = !digitalRead(row5Pins[i]);
    }
  }

  if (ROW6_ACTIVE == 1)
  {
    for(int i = ROW6_PWMCOUNT; i < 8; i++)
    {
      rawState[5][i] = !digitalRead(row6Pins[i]);
    }
  }

  
  //Row 7
  if(CB1_ADC1 == 1)
  {
    if(globalClock > 1000) //Preventing button pressed on boot
    {
       for (int i = 0; i<CB1_ADC1_CHANNELS; i++)
      {
        if (ADS1115value[i] < GROUND_CALIBRATION)
        {
          rawState[6][i] = 1;
        }
        else
        {
          rawState[6][i] = 0;
        }
      }
    }
    else
    {
      for (int i = 0; i<CB1_ADC1_CHANNELS; i++)
      {
        rawState[6][i] = 0;
      }
    }
  }
  
  if(CB1_ADC2 == 1)
  {
    if(globalClock > 1000) //Preventing button pressed on boot
    {
      for (int i = 4; i<4+CB1_ADC2_CHANNELS; i++)
      {
        if (ADS1115value[i] < GROUND_CALIBRATION)
        {
          rawState[6][i] = 1;
        }
        else
        {
          rawState[6][i] = 0;
        }
      }    
    }
    else
    {
      for (int i = 4; i<4+CB1_ADC2_CHANNELS; i++)
      {
        rawState[6][i] = 0;
      }
    }
  }

  //ROW 8 COL 1
  rawState[7][0] = !digitalRead(0);

  //LED pin

  if(DISABLE_LED_PIN == 1)
  {
    rawState[7][7] = !digitalRead(25);
  }

  //Analog pins

  if(DISABLE_ANALOG == 1)
  {
    rawState[7][3] = !digitalRead(A0);
    rawState[7][4] = !digitalRead(A1);
    rawState[7][5] = !digitalRead(A2);
    rawState[7][6] = !digitalRead(A3);
  }

  //ALERT pins

  if (DISABLE_ALERT_PINS == 1)
  {
    rawState[7][1] = !digitalRead(14);
    rawState[7][2] = !digitalRead(15);
  }
  
}

#endif

#if (USING_ADS1115 == 1)
void ADS1115Run(int chipNumber, int channelCount, int rate, int gain)
{
  #if (ADS1115_I2C_NUMBER == 1)
  uint8_t Chip = chipNumber - 1;
  uint8_t address = ADS1115_chipAddress[Chip];
  #if (ADS1115_ALERT == 1)
    
    if (!ADS1115sentReq[Chip])
    {
      Wire1.beginTransmission(address);
      Wire1.write(0b00000001);
      Wire1.write(0b11000001 | (ADS1115channelCounter[Chip] << 4) | gain << 1);
      Wire1.write(0b00000100 | (rate << 5));
      Wire1.endTransmission();
  
      ADS1115sentReq[Chip] = true;
    }
 
    if (ADS1115sentReq[Chip] && digitalRead(ADS1115_alertPins[Chip]) == 0)
    {
      Wire1.beginTransmission(address);
      Wire1.write(0b00000000);
      Wire1.endTransmission();
  
      uint8_t valAddress = (4*Chip)+ADS1115channelCounter[Chip];
      
      Wire1.requestFrom(address, 2);
      ADS1115value[valAddress]= Wire1.read()<<8;
      ADS1115value[valAddress] |= Wire1.read();
      if (ADS1115value[valAddress] > 32767)
      {
        ADS1115value[valAddress] = 0;
      }
      ADS1115sentReq[Chip] = false;
  
      ADS1115channelCounter[Chip] ++;
  
      if (ADS1115channelCounter[Chip] >= channelCount)
      {
        ADS1115channelCounter[Chip] = 0;
      }
    }

  #else

    if (!ADS1115sentReq[Chip])
    {
      Wire1.beginTransmission(address);
      Wire1.write(0b00000001);
      Wire1.write(0b11000001 | (ADS1115channelCounter[Chip] << 4) | gain << 1);
      Wire1.write(0b00000011 | (rate << 5));
      Wire1.endTransmission();
  
      ADS1115sentReq[Chip] = true;
    }
  
    if (ADS1115sentReq[Chip])
    {
      Wire1.requestFrom(address, 2);
      int convStatus = (Wire1.read()>>7);
      if (convStatus == 1)
      {
        Wire1.beginTransmission(address);
        Wire1.write(0b00000000);
        Wire1.endTransmission();
  
        uint8_t valAddress = (4*Chip)+ADS1115channelCounter[Chip];
        
        Wire1.requestFrom(address, 2);
        ADS1115value[valAddress]= Wire1.read()<<8;
        ADS1115value[valAddress] |= Wire1.read();
        if (ADS1115value[valAddress] > 32767)
        {
          ADS1115value[valAddress] = 0;
        }
        ADS1115sentReq[Chip] = false;
  
        ADS1115channelCounter[Chip] ++;
  
        if (ADS1115channelCounter[Chip] >= channelCount)
        {
          ADS1115channelCounter[Chip] = 0;
        }
      }
    }
  #endif
  
 #else
  
  uint8_t Chip = chipNumber - 1;
  uint8_t address = ADS1115_chipAddress[Chip];
  
  #if (ADS1115_ALERT == 1)
  
    if (!ADS1115sentReq[Chip])
    {
      Wire.beginTransmission(address);
      Wire.write(0b00000001);
      Wire.write(0b11000001 | (ADS1115channelCounter[Chip] << 4) | gain << 1);
      Wire.write(0b00000100 | (rate << 5));
      Wire.endTransmission();
  
      ADS1115sentReq[Chip] = true;
    }
 
    if (ADS1115sentReq[Chip] && digitalRead(ADS1115_alertPins[Chip]) == 0)
    {
      Wire.beginTransmission(address);
      Wire.write(0b00000000);
      Wire.endTransmission();
  
      uint8_t valAddress = (4*Chip)+ADS1115channelCounter[Chip];
      
      Wire.requestFrom(address, 2);
      ADS1115value[valAddress]= Wire.read()<<8;
      ADS1115value[valAddress] |= Wire.read();
      if (ADS1115value[valAddress] > 32767)
      {
        ADS1115value[valAddress] = 0;
      }
      ADS1115sentReq[Chip] = false;
  
      ADS1115channelCounter[Chip] ++;
  
      if (ADS1115channelCounter[Chip] >= channelCount)
      {
        ADS1115channelCounter[Chip] = 0;
      }
    }

  #else

    if (!ADS1115sentReq[Chip])
    {
      Wire.beginTransmission(address);
      Wire.write(0b00000001);
      Wire.write(0b11000001 | (ADS1115channelCounter[Chip] << 4) | gain << 1);
      Wire.write(0b00000011 | (rate << 5));
      Wire.endTransmission();
  
      ADS1115sentReq[Chip] = true;
    }
  
    if (ADS1115sentReq[Chip])
    {
      Wire.requestFrom(address, 2);
      int convStatus = (Wire.read()>>7);
      if (convStatus == 1)
      {
        Wire.beginTransmission(address);
        Wire.write(0b00000000);
        Wire.endTransmission();
  
        uint8_t valAddress = (4*Chip)+ADS1115channelCounter[Chip];
        
        Wire.requestFrom(address, 2);
        ADS1115value[valAddress]= Wire.read()<<8;
        ADS1115value[valAddress] |= Wire.read();
        if (ADS1115value[valAddress] > 32767)
        {
          ADS1115value[valAddress] = 0;
        }
        ADS1115sentReq[Chip] = false;
  
        ADS1115channelCounter[Chip] ++;
  
        if (ADS1115channelCounter[Chip] >= channelCount)
        {
          ADS1115channelCounter[Chip] = 0;
        }
      }
    }
    
  #endif //Alert versions
  
#endif //I2C lines

}

#endif //Using ADS1115
