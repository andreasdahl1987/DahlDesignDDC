# Pushbutton

#### Simple pushbutton

`void pushButton(int row, int col)`

A simple, momentary pushbutton. The buttonnumer is the one you set in your matrix setup.

#### Toggle button

`void pushButtonL(int row, int col)`

The button will become a latching button, so hitting it once will turn it on, hitting again will turn it off.

#### Button with modes

`void pushButtonM(int row, int col, int fieldPlacement)`

Pushbutton that can swap between being momentary (mode 0) and latching (mode 1).

_Project requirements: Function button_
