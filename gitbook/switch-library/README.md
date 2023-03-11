# Switch library

## Functions

Every switch needs a function to work. There are simple and more complex functions for different kinds of switches available. The way these functions work:

* The function usually requires you to give it a matrix adress
* It will have a look at this adress to see if the button is pressed or not
* It will squeeze whatever information it gets through some debouncing algorithms
* Some more algorithms will give the desired effect of the button press, whether it be a simple button press, a toggle, modifying other switches, overriding clutch paddles, etc.

The simplest function might be for a pushbutton:

`void pushbutton(int row, int col)`

If you have no experience with coding, you probably wouldn't know how to use this, but it is fairly straight forward:

* In essence, a function is a fixed way to calculate something. Often a function is written in a way that it requires some inputs; it will do something with/to these inputs, and sometimes even give back some kind of result.
* For the function above, "pushbutton" is the name that the function has been given, just to describe what it does or what it is meant for. The brackets `()` that comes after explains what kind of input this function needs to work. The "int" means integer, so a whole number goes here. "row" is just a description to tell you what kind of information goes here; the row number.
* "void" means that this function is a kind of function that shuffles things around, but doesn't give back any value or information of sorts.

As a real world example:

`void houseVacuum(int salary)`

would be your kid vacuuming the house if you insert a few dollars. A job is done, but no product is returned. On the other hand,

`int pizza(int flour, int water, int yeast, int salt)`

could be a function that calculates how many pizzas you can make, requiring you to feed the function the amount of flour, water, yeast and salt you've got available. It returns an interger, the number of pizzas you can make.

* So the `void pushbutton (int row, int col)` wants the row number and the column number of your switch. Its job is to make that switch work. In your code it will look like this: `pushButton(3,2);` Given that we're talking about the switch on row 3, column 2. The ";" behind is sort of an "execute" command.

Have a look at a different function:

`void funkyPush(int row, int column, int aCol, int bCol, int cCol, int dCol)`

This is a function for the pushbutton on a 7-way switch (funky switch). It wants to know the row and column number for the pushbutton, as well as the column number for all the directional pushbuttons. Here you can see why there are some rules to follow when constructing the matrix; the function only asks for one row value. It assumes all of these buttons have the same row number. Example:

`funkyPush(2, 5, 1, 2, 4, 5);`

All of the switch functions are found in the various .ino files, somewhat categorized after type of switches they support. Not all switches are supported, there are bound to be some switches that mechanically work differently than what is currently supported; in that case contact me and we'll figure it out.

While you could go look for functions in the .ino files, it might be hard to see what they do unless you have some experience with coding. This library will list all the functions, what they do and how to use them.

Many of the switch functions ask for a `fieldPlacement`, see [here](../3.-coding/advanced/field-placement.md) for the use of field placement.

### Switch modes

Many of the function will give a switch 2 or more _**modes.**_ An example is `toggleM(int row, int column, int fieldPlacement)`This switch will have two modes:

* 0 : Toggle on/off
* 1: Pulse -> A short button press when the toggle is flicked on or off

A more complex example would be `void DDS2bit(int row, int col, bool reverse),` which has 4 modes:

* 0: Open DDS -> 24 position switch, which has two layers of 12 positions that can be swapped between with a different button.
* 1: Closed DDS -> The position of the switch is locked, but the switch now works as an incremental encoder while still holding the button press from one of the 24 positions.
* 2: 4-position switch -> The switch is now an absolute 4-position encoder.
* 3: Incremental -> The switch works as a regular incremental encoder, producing a short button press on CW/CCW rotation

To change a switch mode you need to have a designated **mode button,** which is set with `modButton(int row, int column).` Typically you will just hold the mode button and use the press/rotate the switch that you want to change the mode for.&#x20;

The information about a switch mode can be found and set in the variable `switchMode.` As mentioned before, when reading/writing directly from/to variables of the matrix, the column and row numbers start with 0, so row 4 in that case is "3", and column 5 is "4". The switch mode for a switch on row 1 column 4 is found in switchMode\[0]\[3]. Most relevant use of this is when making [presets](../3.-coding/advanced/presets/). All switches default to starting mode 0 on boot.&#x20;

When using the above examples:

* I want my toggle using toggleM(3,1,5); to start in mode 1 in preset 4 . I'll write `switchMode[2][0]  = 1;` in the slot for preset 4.&#x20;
* I want my `DDS2bit(3,2,true);` to boot in mode 2. I'll write `switchMode[2][2] = 1;` in the slot for preset 1.  This might be confusing, but I'll explain:
  * Switches with 4 modes uses two switchMode adresses in order to get enough bits to make a number going from 0-3. In this case the switch is on row 3 column 2. Meaning also column 3 is used by this encoder (A and B pin of an encoder are always on columns next to eachother on the row, only the first column used in included in the function, the second is just assumed to be there).&#x20;
  * The two bits can make numbers 00 = 0, 01 = 1, 10 = 2, 11 = 3. This representing the modes.&#x20;
  * The bit for the last column comes first. The bit for the first colum comes last. So in order to get to mode 2 (10), the first bit needs to be 1, the last bit needs to be zero. The last bit is already 0, so we just need to change the first bit. This is the switchMode for row 3 column 3, which is switchMode\[2]\[2].&#x20;

When using switches with modes available, the mode of the switch can be communicated to SimHub using the[ field placements](../3.-coding/advanced/field-placement.md).&#x20;

