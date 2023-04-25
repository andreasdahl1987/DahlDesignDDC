void write16bitToEEPROM(uint16_t location, uint16_t value)
{
#if (USING_CAT24C512 == 1)

    uint8_t reg1 = location >> 8;
    uint8_t reg2 = location & 0xff;

    Wire.beginTransmission(CAT24C512_ADDRESS);

    Wire.write(reg1);
    Wire.write(reg2); 

    uint8_t firstByte = value >> 8;
    uint8_t lastByte = value & 0xff;
    Wire.write(firstByte);
    Wire.write(lastByte);
    Wire.endTransmission();
    
#endif
 }

uint16_t read16bitFromEEPROM(uint16_t location)
{
#if (USING_CAT24C512 == 1)

    uint8_t reg1 = location >> 8;
    uint8_t reg2 = location & 0xff;

    Wire.beginTransmission(CAT24C512_ADDRESS);

    Wire.write(reg1);
    Wire.write(reg2);

    Wire.endTransmission();

    uint16_t value = 0;

    Wire.requestFrom(CAT24C512_ADDRESS, 2);
    value = Wire.read();
    value = value << 8;
    value |= Wire.read();

    return value;
#endif
}

void EEPROMfirst()
{
#if (USING_CAT24C512 == 1)
    uint8_t virgin = read16bitFromEEPROM(UTIL, UTIL_INIT);
    if (virgin == 1)
    {
        write16bitToEEPROM(UTIL, 0);
        write16bitToEEPROM(PRESET, 0);
        for(int i = 0; i < 12; i++)
        {
            write16bitToEEPROM(BITEPOINT+(2 * i), 300);         
        }
    }
#endif
}

void EEPROMinit()
{
#if (USING_CAT24C512 == 1)
    switchPreset = read16bitFromEEPROM(PRESET);
    oldPreset = switchPreset;
    bitePoint = read16bitFromEEPROM(BITEPOINT+(switchPreset*2));
    oldBitePoint = bitePoint;
#endif
}

void EEPROMchanges()
{
#if (USING_CAT24C512 == 1)

    //Bite point
    if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 0 && (biteButtonBit1 + biteButtonBit2 == 0) && oldBitePoint != bitePoint)
    {
        oldBitePoint = bitePoint;
        write16bitToEEPROM(BITEPOINT+(switchPreset * 2), bitePoint);
    }

    //Preset
    if (oldPreset != switchPreset)
    {
        oldPreset = switchPreset;
        write16bitToEEPROM(PRESET, switchPreset);
    }
#endif
}

void EEPROMpresetChange()
{
    bitePoint = read16bitFromEEPROM(BITEPOINT + switchPreset * 2);
}
