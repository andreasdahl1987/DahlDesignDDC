//------------------------------
//--------OTHER VARIABLES-------
//------------------------------

long globalTimer = 0;
uint8_t globalCounter = 0;

//Handbrake
bool handbrake = false;
bool handbrakeLock = false;
bool handbrakeRelease = false;
long handbrakeTimer = 0;

//Specials
bool bitePotLock = false;
bool brakeMagicOn;
float brakeMagicValue;
float throttleHoldValue;
float bitePoint;
bool biteRefresh;
uint8_t quickValue1;
uint8_t quickValue2;
uint8_t quickValue3;
uint8_t quickValue4;
bool quickSwitchState;
bool quickSwitch12State;
bool quickSwitch34State;

//Function buttons
int8_t hybridButtonRow;
int8_t hybridButtonCol;
int8_t modButtonRow;
int8_t modButtonCol;
int8_t ddButtonRow;
int8_t ddButtonCol;
int8_t neutralButtonRow = -1;
int8_t neutralButtonCol = -1;
int8_t biteButtonRow;
int8_t biteButtonCol;
int8_t presetButtonRow;
int8_t presetButtonCol;

//Clutch calibration
int16_t slaveReleasedLow = 0;
int16_t slaveReleasedHigh = 0;
int16_t slavePressed = 0;
int16_t slaveCompare = 0;
int16_t masterReleasedLow = 0;
int16_t masterReleasedHigh = 0;
int16_t masterPressed = 0;
int16_t masterCompare = 0;
int16_t masterRaw = 0;
int16_t slaveRaw = 0;
long clutchCalibrationTimer = 0;
bool clutchCalibrationLatch = true;
bool clutchCalibrationState = true;
uint8_t clutchCalibrationMode = 0;
uint16_t MFP = 0;
uint16_t MFR = 0;
uint16_t SFP = 0;
uint16_t SFR = 0;

//Analog inject
long injectMuteTimer = -20000;
uint8_t injectMuteCounter = 0;
bool injectMute = false;

//Bite and launch
bool biteButtonBit1 = false;
bool biteButtonBit2 = false;
bool launchButtonLatch = false;
uint8_t first = 0;
uint8_t second = 0;

uint8_t switchPreset = 0;
bool bootPreset = true;

//Clock and counter
unsigned long globalClock;

//Debouncing
#define PEC11Cooldown 70
#define PEC11Pulse 50
#define E18Cooldown 50
#define E18Pulse 30
#define pulseEncCD 20
#define pulseEncDuration 50
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

//Clutch deadzones
#define clutchTopDeadzone 10
#define clutchBottomDeadzone 10

//LED setup
int8_t LEDBrightness = 25;
