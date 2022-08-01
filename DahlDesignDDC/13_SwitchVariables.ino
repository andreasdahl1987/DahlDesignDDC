//Matrix variables

int8_t rawState[rowCount][colCount];
int8_t pushState[rowCount][colCount];
bool latchLock[rowCount][colCount];
bool latchState[rowCount][colCount];
bool switchModeLock[rowCount][colCount];
long switchTimer[rowCount][colCount];
long toggleTimer[rowCount][colCount];

//Analog variables

int8_t analogLastCounter[10];
int8_t analogTempState[10];
bool analogLatchLock[10];
long analogTimer1[10];
long analogTimer2[10];
int8_t analogRotaryCount[10];


//Smoothing of analog signal

#define reads 10
int readings[10][reads];         // the readings from the analog input
int8_t readIndex[10];              // the index of the current reading
int total[10];                  // the running total
int average[10];
