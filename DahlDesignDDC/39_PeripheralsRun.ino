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
