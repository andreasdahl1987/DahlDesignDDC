void write16bitToEEPROM(int page, int line, uint16_t value)
{
#if (USING_CAT24C512 == 1)
    uint16_t location = 0;
    location |= (page << 7);
    location |= line;

    uint8_t reg1 = location >> 8;
    uint8_t reg2 = location & 0xff;

    Wire.beginTransmission(CAT24C512_ADDRESS);

    Wire.write(reg1);
    Wire.write(reg2); 

    uint8_t first = value >> 8;
    uint8_t last = value & 0xff;
    Wire.write(first);
    Wire.write(last);
    Wire.endTransmission();
#endif
 }

uint16_t read16bitFromEEPROM(int page, int line)
{
#if (USING_CAT24C512 == 1)

    uint16_t location = 0;
    location |= (page << 7);
    location |= line;

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
        write16bitToEEPROM(UTIL, UTIL_INIT, 0);
        write16bitToEEPROM(PRESET, 0x00, 0);
        write16bitToEEPROM(BITEPOINT, 0x00, 300);
        write16bitToEEPROM(BITEPOINT, 0x02, 300);
        write16bitToEEPROM(BITEPOINT, 0x04, 300);
        write16bitToEEPROM(BITEPOINT, 0x06, 300);
        write16bitToEEPROM(BITEPOINT, 0x08, 300);
        write16bitToEEPROM(BITEPOINT, 0x0a, 300);
        write16bitToEEPROM(BITEPOINT, 0x0c, 300);
        write16bitToEEPROM(BITEPOINT, 0x0e, 300);
        write16bitToEEPROM(BITEPOINT, 0x10, 300);
        write16bitToEEPROM(BITEPOINT, 0x12, 300);
        write16bitToEEPROM(BITEPOINT, 0x14, 300);
        write16bitToEEPROM(BITEPOINT, 0x16, 300);
        write16bitToEEPROM(BITEPOINT, 0x18, 300);
        write16bitToEEPROM(BITEPOINT, 0x1a, 300);
        write16bitToEEPROM(BITEPOINT, 0x1c, 300);
        write16bitToEEPROM(BITEPOINT, 0x1e, 300);
    }
#endif
}

void EEPROMinit()
{
#if (USING_CAT24C512 == 1)
    switchPreset = read16bitFromEEPROM(PRESET, 0x00);
    oldPreset = switchPreset;
    bitePoint = read16bitFromEEPROM(BITEPOINT, switchPreset<<1);
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
        write16bitToEEPROM(BITEPOINT, switchPreset<<1, bitePoint);
    }

    //Preset
    if (oldPreset != switchPreset)
    {
        oldPreset = switchPreset;
        write16bitToEEPROM(PRESET, 0x00, switchPreset);
    }

#endif
}
