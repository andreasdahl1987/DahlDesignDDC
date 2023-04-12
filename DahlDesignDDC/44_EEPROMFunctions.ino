void write16bitToEEPROM(int page, int line, uint16_t value)
{
#if (USING_CAT24C512 == 1)
    int16_t location = 0;
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

    int16_t location = 0;
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