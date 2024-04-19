void write16bitToEEPROM(uint16_t location, uint16_t value)
{
#if ((USING_CAT24C512 == 1 && CAT24C512_I2C_NUMBER == 0) || USING_CB1 == 1 || USING_32U4EEPROM == 1)
  
  #if (USING_32U4EEPROM)
    uint8_t firstByte = value >> 8;
    uint8_t lastByte = value & 0xff;
    EEPROM.write(location,firstByte);
    delay(5);
    EEPROM.write(location+1,lastByte);
    delay(5);   
  #else
    uint8_t reg1 = location >> 8;
    uint8_t reg2 = location & 0xff;

    Wire.beginTransmission(CAT24C512_ADDRESS);
    delayMicroseconds(200);
    
    Wire.write(reg1);
    Wire.write(reg2); 

    uint8_t firstByte = value >> 8;
    uint8_t lastByte = value & 0xff;
    Wire.write(firstByte);
    Wire.write(lastByte);
    Wire.endTransmission();
    delayMicroseconds(200);
  #endif  
#elif (USING_CAT24C512 == 1 && CAT24C512_I2C_NUMBER == 1)
  
    uint8_t reg1 = location >> 8;
    uint8_t reg2 = location & 0xff;

    Wire1.beginTransmission(CAT24C512_ADDRESS);
    delayMicroseconds(200);
    
    Wire1.write(reg1);
    Wire1.write(reg2); 

    uint8_t firstByte = value >> 8;
    uint8_t lastByte = value & 0xff;
    Wire1.write(firstByte);
    Wire1.write(lastByte);
    Wire1.endTransmission();
    delayMicroseconds(200); 
#else
  EEPROMdump = location + value;  
#endif
 }

uint16_t read16bitFromEEPROM(uint16_t location)
{
#if ((USING_CAT24C512 == 1 && CAT24C512_I2C_NUMBER == 0) || USING_CB1 == 1 || USING_32U4EEPROM == 1)
  
  #if (USING_32U4EEPROM)
    uint16_t value = 0;
    value = EEPROM.read(location);
    delay(5);
    value = value << 8;
    value |= EEPROM.read(location+1);
    delay(5);
    return value;
  #else
    uint8_t reg1 = location >> 8;
    uint8_t reg2 = location & 0xff;

    Wire.beginTransmission(CAT24C512_ADDRESS);
    delayMicroseconds(200);
    
    Wire.write(reg1);
    Wire.write(reg2);
    Wire.endTransmission();

    uint16_t value = 0;

    Wire.requestFrom(CAT24C512_ADDRESS, 2);
    value = Wire.read();
    value = value << 8;
    value |= Wire.read();
    delayMicroseconds(200);
    
    return value;
  #endif

#elif (USING_CAT24C512 == 1 && CAT24C512_I2C_NUMBER == 1)

    uint8_t reg1 = location >> 8;
    uint8_t reg2 = location & 0xff;

    Wire1.beginTransmission(CAT24C512_ADDRESS);
    delayMicroseconds(200);
    
    Wire1.write(reg1);
    Wire1.write(reg2);
    Wire1.endTransmission();

    uint16_t value = 0;

    Wire1.requestFrom(CAT24C512_ADDRESS, 2);
    value = Wire1.read();
    value = value << 8;
    value |= Wire1.read();
    delayMicroseconds(200);
    
    return value;
    
#else

  return location * 0;
  
#endif
}

void EEPROMfirst()
{
#if (USING_CAT24C512 == 1 || USING_CB1 == 1 || USING_32U4EEPROM == 1)

    resetEEPROM = read16bitFromEEPROM(UTIL);
    delay(5);
    if (resetEEPROM > 0 || RESET_EEPROM == 1)
    {
        write16bitToEEPROM(UTIL, 0);
        delay(5);
        for(int i = 0; i < 12; i++)
        {
            write16bitToEEPROM(BITEPOINT+(i*2), 300);
            delay(5);
            write16bitToEEPROM(LEDSLOT+(i*2), 25);
            delay(5);
            write16bitToEEPROM(BRAKESLOT+(i*2), 50);
            delay(5);
            write16bitToEEPROM(THROTTLESLOT+(i*2), 1000);
            delay(5);
        }
        write16bitToEEPROM(DDS_b, 0);
        delay(5);
    }
#endif
}

void EEPROMinit()
{
#if (USING_CAT24C512 == 1 || USING_CB1 == 1 || USING_32U4EEPROM == 1)
    switchPreset = read16bitFromEEPROM(PRESETSLOT);
    bitePoint = read16bitFromEEPROM(BITEPOINT+(switchPreset*2));
    LEDBrightness = read16bitFromEEPROM(LEDSLOT+(switchPreset*2));
    brakeMagicValue = read16bitFromEEPROM(BRAKESLOT+(switchPreset*2));
    throttleHoldValue = read16bitFromEEPROM(THROTTLESLOT+(switchPreset*2));

    MFP = read16bitFromEEPROM(MASTERPRESSED);
    MFR = read16bitFromEEPROM(MASTERRELEASED);
    SFP = read16bitFromEEPROM(SLAVEPRESSED);
    SFR = read16bitFromEEPROM(SLAVERELEASED);
    
    oldBitePoint = bitePoint;
    oldLED = LEDBrightness;
    oldBrake = brakeMagicValue;
    oldThrottle = throttleHoldValue;
#endif
}

void EEPROMchanges()
{
#if (USING_CAT24C512 == 1 || USING_CB1 == 1 || USING_32U4EEPROM == 1)

    //PRESET
    if (oldPreset != switchPreset)
    {
      oldPreset = switchPreset;
      write16bitToEEPROM(PRESETSLOT,switchPreset);
    }
  
    //BITE POINT
    if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 0 && (biteButtonBit1 + biteButtonBit2 == 0) && oldBitePoint != bitePoint)
    {
        oldBitePoint = bitePoint;
        write16bitToEEPROM(BITEPOINT+(switchPreset * 2), bitePoint);
    }
    //LED
    if (oldLED != LEDBrightness)
    {
      oldLED = LEDBrightness;
      write16bitToEEPROM(LEDSLOT+(switchPreset * 2), LEDBrightness);
    }
    //BRAKE MAGIC
    if (oldBrake != brakeMagicValue)
    {
      oldBrake = brakeMagicValue;
      write16bitToEEPROM(BRAKESLOT+(switchPreset * 2), brakeMagicValue);
    }
    //THROTTLE HOLD
    if (oldThrottle != throttleHoldValue)
    {
      oldThrottle = throttleHoldValue;
      write16bitToEEPROM(THROTTLESLOT+(switchPreset * 2), throttleHoldValue);
    }    

#endif
}

void EEPROMpresetChange()
{
    #if (USING_CAT24C512 == 1 || USING_CB1 == 1 || USING_32U4EEPROM == 1)
    bitePoint = read16bitFromEEPROM(BITEPOINT + switchPreset * 2);
    LEDBrightness = read16bitFromEEPROM(LEDSLOT + switchPreset * 2);
    brakeMagicValue = read16bitFromEEPROM(BRAKESLOT + switchPreset * 2);
    throttleHoldValue = read16bitFromEEPROM(THROTTLESLOT + switchPreset * 2);
    #endif
}
