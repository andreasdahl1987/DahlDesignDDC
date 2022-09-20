//-----------------------------------
//--BIT FIELDS FOR MODE PROPERTIES---
//-----------------------------------

int encoderField = 0;

/*
 * Encoder field, pushed to joysick axis Rx

 Most significant
 8 - DDS switch
 8 - DDS switch
 7 - Dual clutches
 7 - Dual clutches
 6 - Bite point setting
 6 - Bite point setting
 5
 5
 4
 4
 3
 3
 2
 2
 1
 1
 Least significant

 */

int buttonField = 0;

/*
 * Button field, pushed to joysick axis Ry

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
