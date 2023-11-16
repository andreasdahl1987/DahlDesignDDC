void clutchCalibrate(int row, int column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;

    // Button logics

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if (pushState[Row][Column] == 0) //Safety on mod button combo
    {      
        clutchCalibrationTimer = globalClock;
        clutchCalibrationLatch = true;
        clutchCalibrationState = true;
    }

    if (globalClock - clutchCalibrationTimer > 3000)
    {
        if(clutchCalibrationLatch)
        {
            clutchCalibrationMode = 1;
            clutchCalibrationLatch = false;
        }
    }
    if (globalClock - clutchCalibrationTimer > 4000)
    {
        if(clutchCalibrationState)
        {
            clutchCalibrationMode = 2;
            clutchCalibrationState = false;
        }
    }

    //Reset and push values
    if (clutchCalibrationMode == 2 && clutchCalibrationState && pushState[Row][Column] == 1)
    {
      clutchCalibrationMode = 0;

      //Calculations
      uint8_t masterDelta = masterReleasedHigh - masterReleasedLow;
      uint8_t slaveDelta = slaveReleasedHigh - slaveReleasedLow;

      if(masterPressed < masterReleasedLow)
      {
        MFP = masterPressed + (3*masterDelta);
        write16bitToEEPROM(MASTERPRESSED, MFP);
        delay(5);
        MFR = masterReleasedLow - masterDelta;
        write16bitToEEPROM(MASTERRELEASED, MFR);
        delay(5);
      }
      else
      {
        MFP = masterPressed - (3*masterDelta);
        write16bitToEEPROM(MASTERPRESSED, MFP);
        delay(5);
        MFR = masterReleasedHigh + masterDelta;
        write16bitToEEPROM(MASTERRELEASED, MFR);
        delay(5);
      }
      if(slavePressed < slaveReleasedLow)
      {
        SFP = slavePressed + (3*slaveDelta);
        write16bitToEEPROM(SLAVEPRESSED, SFP);
        delay(5);
        SFR = slaveReleasedLow - slaveDelta;
        write16bitToEEPROM(SLAVERELEASED, SFR);
        delay(5);
      }
      else
      {
        SFP = slavePressed - (3*slaveDelta);
        write16bitToEEPROM(SLAVEPRESSED, SFP);
        delay(5);
        SFR = slaveReleasedHigh + slaveDelta;
        write16bitToEEPROM(SLAVERELEASED, SFR);
        delay(5);
      }

      masterPressed = 0;
      masterReleasedLow = 0;
      masterReleasedHigh = 0;
      masterCompare = 0;
      slavePressed = 0;
      slaveReleasedLow = 0;
      slaveReleasedHigh = 0;
      slaveCompare = 0;
    }

    //Calibration recording of released clutches
    if (clutchCalibrationMode == 1)
    {
      if (masterReleasedLow == 0 || masterRaw < masterReleasedLow)
      {
        masterReleasedLow = masterRaw; 
      }
      if (masterRaw > masterReleasedHigh)
      {
        masterReleasedHigh = masterRaw;
      }
      if (slaveReleasedLow == 0 || slaveRaw < slaveReleasedLow)
      {
        slaveReleasedLow = slaveRaw; 
      }
      if (slaveRaw > slaveReleasedHigh)
      {
        slaveReleasedHigh = slaveRaw;
      }
    }

    //Calibration recording of pressed clutches
    if (clutchCalibrationMode == 2)
    {
      if (abs(masterReleasedHigh-masterRaw) > masterCompare)
      {
        masterCompare = abs(masterReleasedHigh-masterRaw);
        masterPressed = masterRaw;
      }
      if (abs(slaveReleasedHigh-slaveRaw) > slaveCompare)
      {
        slaveCompare = abs(slaveReleasedHigh-slaveRaw);
        slavePressed = slaveRaw;
      }
    }

    //Joystick
    Joystick.setButton(buttonNumber[Row][Column], pushState[Row][Column]);

    //Push calibration active
    long push = 0;
    uint8_t item = clutchCalibrationMode >> 1;
    push = push | item;
    push = push << 7;
    rotaryField = rotaryField | push;
}
