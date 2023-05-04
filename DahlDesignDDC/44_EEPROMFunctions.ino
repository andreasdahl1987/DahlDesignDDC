void write16bitToEEPROM(uint16_t location, uint16_t value)
{
#if (USING_CAT24C512 == 1 || USING_CB1 == 1 || USING_32U4EEPROM == 1)

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
 }

uint16_t read16bitFromEEPROM(uint16_t location)
{
#if (USING_CAT24C512 == 1 || USING_CB1 == 1 || USING_32U4EEPROM == 1)

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
}

void EEPROMfirst()
{
#if (USING_CAT24C512 == 1 || USING_CB1 == 1 || USING_32U4EEPROM == 1)

    if (RESET_EEPROM == 1)
    {
      write16bitToEEPROM(UTIL, 1);
    }
  
    uint8_t virgin = read16bitFromEEPROM(UTIL);
    if (virgin == 1)
    {
        write16bitToEEPROM(UTIL, 0);
        for(int i = 0; i < 12; i++)
        {
            write16bitToEEPROM(BITEPOINT+(2 * i), 300);
            write16bitToEEPROM(LEDSLOT, 25);
            write16bitToEEPROM(BRAKESLOT, 50);
            write16bitToEEPROM(THROTTLESLOT, 1000);
        }
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
