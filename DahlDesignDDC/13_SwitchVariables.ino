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

int8_t analogLastCounter[analogSwitchCount];
int8_t analogTempState[analogSwitchCount];
bool analogLatchLock[analogSwitchCount];
long analogTimer1[analogSwitchCount];
long analogTimer2[analogSwitchCount];
int8_t analogRotaryCount[analogSwitchCount];
int8_t analogSwitchMode1[analogSwitchCount];
int8_t analogSwitchMode2[analogSwitchCount];

//Smoothing of analog signal

#define reads 3
int readings[analogSwitchCount][reads];        // the readings from the analog input
int8_t readIndex[analogSwitchCount];           // the index of the current reading
int total[analogSwitchCount];                  // the running total
int average[analogSwitchCount];

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
