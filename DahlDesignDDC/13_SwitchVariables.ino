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

#define reads 10
int readings[analogSwitchCount][reads];        // the readings from the analog input
int8_t readIndex[analogSwitchCount];           // the index of the current reading
int total[analogSwitchCount];                  // the running total
int average[analogSwitchCount];
