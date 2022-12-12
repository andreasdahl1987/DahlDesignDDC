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

Many of the switch functions ask for a `fieldPlacement`, see [here](../5.-advanced-features/field-placement.md) for the use of field placement.

### Switch modes

Many of the function will give a switch 2 or more _**modes.**_ An example is `toggleM(int row, int column, int fieldPlacement)`This switch will have two modes:

* 0 : Toggle on/off
* 1: Pulse -> A short button press when the toggle is flicked on or off

Another example would be `void DDSfunky(int Arow, int Acol, int Bcol)`&#x20;



