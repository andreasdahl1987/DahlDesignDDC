//Matrix variables

int8_t rawState[rowCount][colCount];
int8_t pushState[rowCount][colCount];
bool latchLock[rowCount][colCount];
bool latchState[rowCount][colCount];
bool switchModeLock[rowCount][colCount];
long switchTimer[rowCount][colCount];
long toggleTimer[rowCount][colCount];
bool switchMode[rowCount][colCount];

//Analog variables

int8_t analogLastCounter[analogChannelCount];
int8_t analogTempState[analogChannelCount];
bool analogLatchLock[analogChannelCount];
long analogTimer1[analogChannelCount];
long analogTimer2[analogChannelCount];
int8_t analogRotaryCount[analogChannelCount];
int8_t analogSwitchMode1[analogChannelCount];
int8_t analogSwitchMode2[analogChannelCount];

//Smoothing of analog signal

#define reads 10
int readings[analogChannelCount][reads];        // the readings from the analog input
int8_t readIndex[analogChannelCount];           // the index of the current reading
int total[analogChannelCount];                  // the running total
int average[analogChannelCount];


//PWM Control
#if(ROW6_PWMCOUNT > 0)

  int16_t PWMValues [ROW6_PWMCOUNT];
  bool PWMIsOff [ROW6_PWMCOUNT];
  uint8_t PWMStart[ROW6_PWMCOUNT];
  uint8_t PWMEnd[ROW6_PWMCOUNT];

#elif(PWMENABLED == 1)
  const int8_t PWMCount = sizeof(PWMChannelPins) / sizeof(PWMChannelPins[0]);
  int16_t PWMValues [PWMCount];
  bool PWMIsOff [PWMCount];
  uint8_t PWMStart[PWMCount];
  uint8_t PWMEnd[PWMCount];
#endif

//OUTPUT DEVICES
#if ((PCA9555_OUTPUT == 1 || (USING_CB1 == 1 && (CB1_PE1_OUTPUT == 1 || CB1_PE2_OUTPUT == 1))) && enableOutput == 1)
  uint16_t outputStatus[PCA9555outputCount + 1];
#elif (PCA9555_OUTPUT == 1 || (USING_CB1 == 1 && (CB1_PE1_OUTPUT == 1 || CB1_PE2_OUTPUT == 1)))
  uint16_t outputStatus[PCA9555outputCount];
#elif (enableOutput == 1)
  uint16_t outputStatus[1];
#endif
