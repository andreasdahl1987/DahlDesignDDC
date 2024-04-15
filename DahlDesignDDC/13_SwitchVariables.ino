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

//ADC defines
#define ADC1 50
#define ADC2 51
#define ADC3 52
#define ADC4 53
#define ADC5 54
#define ADC6 55
#define ADC7 56
#define ADC8 57
#define ADC9 58
#define ADC10 59
#define ADC11 60
#define ADC12 61
#define ADC13 62
#define ADC14 63
#define ADC15 64
#define ADC16 65
#define ADC_CORR 50

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
