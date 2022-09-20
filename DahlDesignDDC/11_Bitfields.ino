//-----------------------------------
//--BIT FIELDS FOR SIMHUB PROPERTIES---
//-----------------------------------

int encoderField = 0;

/*
 * First field, pushed to joysick axis Z

 Most significant
 16 - DDS switch
 15 - DDS switch
 14 - Dual clutches
 13 - Dual clutches
 12 - Bite point setting
 11 - Bite point setting
 10 - Handbrake active
 9 - QuickSwitch active
 8 - QuickSwitch mode
 7 - Magic button active
 6 - Throttle Hold active
 5
 4
 3
 2
 1
 Least significant

 */

int buttonField = 0;

/*
 * Second field, pushed to joysick axis Y

 Most significant
 16 - Neutral active
 15 - Neutral mode
 14 - Presets 4th bit
 13 - Presets 3rd bit
 12 - Presets 2nd bit
 11 - Presets 1st bit
 10
 9
 8
 7
 6
 5
 4
 3
 2
 1
 Least significant

 */
