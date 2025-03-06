# Field placement

Some switch functions will ask you to select a field placement. These functions will send info to the DDC bit fields that will end up as properties in SimHub that you can use to build dashboard graphics and other cool things.&#x20;

[Read up on the bit fields in DDC here.](../../4.-advanced-features/connect-to-simhub/)

### Examples

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
