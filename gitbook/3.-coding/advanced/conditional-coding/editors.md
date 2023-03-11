# Editors

These are simple functions that can be used with conditional coding to edit stuff that is more deeply rooted in the firmware.&#x20;

#### setButtonNumber(int row, int column, int number)

Changing the button number for a switch in the switch table. Chose the row and column and what to update the button number with. Example: `setButtonNumber(2,3,13);` will set the button number to switch on row 2 column 3 to 13 (shown as 14 in Windows).

#### setAnalogButtonNumber(int switchNumber, int layer, int number)

Changing the button number for a analog switch. Chose the switch number and which "layer" to put the number in - refering to the two arrays with button numbers under 10\_TableAndAnalog. Layer 1 is the top one, Layer 2 is the bottom one. These are the only two options.&#x20;

* Layer 1 is typically for multiposition button numbers
* Layer 2 is typically for the two button numbers used in incremental switch mode

Example: `setAnalogButtonNumber(2,1,42);` will set the button number to analog switch number 2 in the upper layer to 42 (shown as 43 in Windows).

#### setSwitchMode(int row, int column, int mode)

Changing the switch mode for a switch in the switch table. Mode can only be 0 or 1. For switches with 4 modes, typically two adresses in the switch table are used - both the column adresses for the switch (only encoders that have 4 switch modes, they have at least two column adresses).&#x20;

Example: `setSwitchMode(1,1,0);` will set the mode of the switch on row 1 column 1 to 0.&#x20;

#### setAnalogSwitchMode(int switchNumber, int modeBit, int modeValue)

Changing the switch more for an analog switch, starts at 0. Some of the analog switch functions have more than 2 modes - using more than 1 bit. Dual clutch for instance has 4 modes (0-3), using 2 bits. So to change into clutch modes 2 and 3 you need to make two of these functions. Lets see how to set a clutch into mode 3, which is binary 11:

`setAnalogSwitchMode(5,1,1);`

`setAnalogSwitchMode(5,2,1);`

Both act on switch number 5. We're setting the 1st bit to 1 and the 2nd bit to 1. That would be 11, switch mode 3.&#x20;
