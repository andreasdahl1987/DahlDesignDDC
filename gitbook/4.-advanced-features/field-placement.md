# Field placement

This refers to the `int fieldPlacement` that you'll find in many of the switch functions. This is a system for sending information about the controller to SimHub. The way it works:

* Each joystick axis can hold a 16-bit value. Two of the controllers joystick axis (axis Y and Z) are used as a way of sending information about to wheel to the computer through this axis value, thus not being used as real joystick axis. In total 16 + 16 bits of information.
* The 16 bit value is constructed by 16 1's and 0's. Basically 16 slots being on/off. In DDC, you can map things to these slots. You could say that the 4th bit represents the switch mode for one of your 12-position switches. So if the switch is in 12-position mode, the 4th bit should be 0, if it is in incremental mode the 4th bit will be 1. The algorithm takes care of this, but you have to decide which bits you are going to use for each switch. We say that this joysick axis represents a `bit field`.
* The value of these joystick axis are read by SimHub, and then picked up by my plugin. The plugin then splits up all the 16 bits and looks which bits are 0 and which are 1. It creates properties based on this, that you can use in the dashboard editor.

### `14_BitFields.ino`

This file introcudes these fields into the sketch. There is no code to be written here, but you can use this file to plan/organize your switches that has modes.

```
//-------------------------------------
//--BIT FIELDS FOR SIMHUB PROPERTIES---
//-------------------------------------

int rotaryField = 0;

/*
 * First field, pushed to joysick axis Z
 Most significant
 16 - Unused because of bug in joystick library
 15 
 14 - Dual clutches
 13 - Dual clutches
 12 - Bite point setting
 11 - Bite point setting
 10 - DDS switch
 9 - DDS switch
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

int buttonField = 0;

/*
 * Second field, pushed to joysick axis Y
 Most significant
 16 - Unused because of joystick library bug
 15 - Neutral mode
 14 - Presets 4th bit
 13 - Presets 3rd bit
 12 - Presets 2nd bit
 11 - Presets 1st bit
 10 - Handbrake active
 9 - QuickSwitch active
 8 - QuickSwitch mode
 7 - Magic button active
 6 - Throttle Hold active
 5 - Neutral active
 4
 3
 2
 1
 Least significant
 */
```

The two fields are named `rotaryField` and `buttonField`. Typically, a button switch function that asks you to decide a field placement will use the `buttonField` - and for rotary switches/encoders the `rotaryField` will be used.

You can see this file is mosly just comments; a list of the available bits and what they are used for. A lot of the bits are already reserved, only bits 1-4 are available in the `buttonField` and bits 1-8 + 15 in the `rotaryField`. However, the reserved bits are for switches that you're likely to include in your project, and they have defined properties in SimHub. A reseved slot like bit 5 on `buttonField`, is presented as `DahlDesign.DDCNeutralActive`. The non-reserved bits have properties with less descriptive naming; `DahlDesign.DDCB1` to `DahlDesign.DDCB4` for the `buttonField` bits 1 - 4 and `DahlDesign.DDCR1` etc. for the `rotaryField`.

The switch functions for switches which have reserved slots in the bit fields doest not require you to set a field placement. This is done automatically.&#x20;

If your project is running out of bits to use, you can use the bits that are reserved for functions that are not used in your project. So if you're not using neutral button, both bit 5 and bit 15 can be used for something else. Keep in mind though, that the properties representing these bits will be _named as before_; `DahlDesign.DDCNeutralMode`, etc.

A switch function that uses the `buttonField`:

`void pushButtonM(int row, int col, int fieldPlacement)`

Example: `pushButtonM(4,2,2);`

This is set up for a pushbutton on row 4 column 2. The switch function allows for switching between two modes. Which mode this switch is in will be written to the 2nd bit in the `buttonField` and in SimHub you'll find that the property `DahlDesign.DCCB2` can tell you what mode the switch is in.

A switch function that uses the `rotaryField`:

`void rotary2Modes(int row, int col, int fieldPlacement, int hybridPositions, bool reverse)`

Example: `rotary2Modes(3,1,4,12,true)`

This will set up an incremental encoder with 3 different modes on row 3, column 1. What these modes do can be read up on in the function library for this specific function, but the point here is that it has more than 2 modes. The mode number can not be described with a single bit, it needs two bits. Field placement is set to the 4th bit in `rotaryField`, but it will also use the 5th bit. Functions that use more than one bit in the bitfield will have this information in its description in the function library.

It is important to note that a switch with modes will work as intended even if it hasnt been given a field placement. The field placement is just for sending information about the switch mode to SimHub.&#x20;

### Under the hood

If you're running out of slots in your fields, or running out in one of them and have a lot of space in the other - there is usually a way around this. For instance, if you're not intending to use presets, the presets have reserved bits 11-13 in the `buttonField`, you're free to use these. Same goes for DDS switches, bite point setting, etc. If you've filled the `encoderField` and need more slots, and the `buttonField` has spare room, you can change which if the fields your functions will use. Every function that asks for a `fieldPlacement` will typically have few lines like this:

```
//Push switch mode
long push = 0;
push = push | switchMode[Row][Column];
push = push << (FieldPlacement - 1);
buttonField = buttonField | push;
```

Here, the `buttonField` is used. You can just replace `buttonField` with `rotaryField` here to use the `rotaryField` in stead. If you have a lot of the same switch and need more bitfield slots, you can copy the whole function and give it a different name. The new version of the function you alter which field to use.
