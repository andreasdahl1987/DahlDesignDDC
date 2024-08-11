//------------------------------
//-----------SETUP--------------
//------------------------------
#if(BOARDTYPE == 2)
void setup1()
{
#else
void setup()
{
#endif
 
    //RP2040
    #if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
    // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
      TinyUSB_Device_Init(0);
    #endif

    #if (BOARDTYPE == 2)
      USBDevice.setID(VID_PI, PID_PI);
      USBDevice.setManufacturerDescriptor(MAKER);
      USBDevice.setProductDescriptor(CONTROLLER_NAME);
    #endif
  
    //LED setup
    Serial.begin(115200);

    #if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0 && BOARDTYPE == 0)
    setupLeds();
    LEDStartup();
    #endif

    //Set up joystick axis
    Joystick.setXAxisRange(0, 1000);
    Joystick.setThrottleRange(0, 1000);
    Joystick.setBrakeRange(0, 1000);

    //Shift register setup
    if (SRCOUNT > 0)
    {
        shiftRegisterSetup();
    }

    #if (USING_CB1 == 1)
      CB1Setup();
      startI2C();
      CB1Alert();
      #if(CB1_PE1_OUTPUT == 1)
      CB1_OUTPUTSETUP1();
      #endif
      #if(CB1_PE2_OUTPUT == 1)
      CB1_OUTPUTSETUP2();
      #endif
    #else
    
      #if (USING_ADS1115 == 1)
        ADS1115Setup();
      #endif
      
      #if (USING_PCA9555 == 1)
        PCA9555Setup();
      #endif
      
      #if (USING_ADS1115 == 1 || USING_PCA9555 == 1)
      startI2C();
      #endif

      //I2C that required .begin first
      #if (USING_ADS1115 == 1 && ADS1115_ALERT == 1)
        ADS1115Alert();
      #endif
      #if (USING_PCA9555 == 1)
        PCA9555OutputSetup();
      #endif
      
    #endif

    //Filling some arrays
    for (int i = 0; i < rowCount; i++)
    {
        for (int a = 0; a < colCount; a++)
        {
            rawState[i][a] = 0;
            pushState[i][a] = 0;
            latchLock[i][a] = 0;
            latchState[i][a] = 0;
            switchModeLock[i][a] = 0;
            switchTimer[i][a] = 0;
            toggleTimer[i][a] = 0;
        }
    }

    for (int u = 0; u < analogChannelCount; u++)
    {
        analogLastCounter[u] = 0;
        analogTempState[u] = 0;
        analogLatchLock[u] = 0;
        analogTimer1[u] = 0;
        analogTimer2[u] = 0;
        analogRotaryCount[u] = 0;
        readIndex[u] = 0;
        total[u] = 0;
        average[u] = 0;

        for (int i = 0; i < reads; i++)
        {
            readings[u][i] = 0;
        }
    }


    //Ready the matrix
    #if (USING_CB1 == 0)
    for (int i = 0; i < colCount; i++)
    { //  All pins pulled up unless told otherwise
        if (col[i] != 99)
        {
            pinMode(col[i], INPUT_PULLUP);
        }
        
    }

    for (int i = 0; i < rowCount; i++)
    { //  All pins pulled up unless told otherwise
        if (row[i] != 99)
        {
            pinMode(row[i], INPUT_PULLUP);
        }  
    }

    //Pull up direct pins

    for (int i = 0; i < directPinsCount; i++)
    {
        if (directPins[i] < 99)
        {
            pinMode(directPins[i], INPUT_PULLUP);
        }
    }
    
    #endif


    //PWM Setup
    #if (ROW6_PWMCOUNT > 0)
      for (int i = 0; i < ROW6_PWMCOUNT; i++)
      {
        PWMValues[i] = 25;
        PWMIsOff[i] = true;
        PWMStart[i] = 0;
        PWMEnd[i] = 255;
      }
    #elif(PWMENABLED == 1)
      for (int i = 0; i < PWMCount; i++)
      {
        PWMValues[i] = 25;
        PWMIsOff[i] = true;
        pinMode(PWMChannelPins[i], OUTPUT);
        PWMStart[i] = 0;
        PWMEnd[i] = 255;
      }

    PWMSetup();
    
    #endif

    //Setting up output device
    outputPinsSetup();
    
    EEPROMfirst();
    EEPROMinit(); //Fetch values from EEPROM
    presets(switchPreset); //Preset startup

    
    Joystick.begin(0); //Start joystick library magic

    Joystick.setZAxisRange(-32768, 32767); //Making bit fields 16 bit
    Joystick.setYAxisRange(-32768, 32767);
}

#if (BOARDTYPE == 2)
void setup()
{
    #if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
    setupLeds();
    LEDStartup();
    #endif

    #if(USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)
      oversamples.setBuffers(4,2048);
      oversamples.setFrequency(400000);
      oversamples.begin();
    #endif
}
#endif
