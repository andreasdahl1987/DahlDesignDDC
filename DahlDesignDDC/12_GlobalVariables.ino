//------------------------------
//--------OTHER VARIABLES-------
//------------------------------

//Function buttons
int8_t hybridButtonRow;
int8_t hybridButtonCol;
int8_t modButtonRow;
int8_t modButtonCol;
int8_t ddButtonRow;
int8_t ddButtonCol;
int8_t neutralButtonRow;
int8_t neutralButtonCol;
int8_t biteButtonRow;
int8_t biteButtonCol;

bool biteButtonBit1 = false;
bool biteButtonBit2 = false;

int8_t switchPreset = 0;

//Clock and counter
unsigned long globalClock;

//Debouncing
#define buttonCooldown 25
#define analogWait 50
#define analogPulse 100
#define encoderWait 5
#define encoderPulse 50
#define encoder2Wait 2
#define encoder2Pulse 50
#define encoderCooldown 0
#define togglePulse 50
#define funkyPulse 60
#define funkyCooldown 70

//--------------------------------
//----DEFAULT BITE POINT----------
float bitePoint = 400;
//--------------------------------

//Clutch deadzones
#define clutchTopDeadzone 10
#define clutchBottomDeadzone 10
