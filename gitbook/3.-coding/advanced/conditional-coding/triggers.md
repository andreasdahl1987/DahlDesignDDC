# Triggers

These are simple functions that can be used with conditional coding, or the LEDtrigger() function. These functions will return `true` or `false.`

#### buttonFieldBit(int bit)

Type in a field placement to check if this bit is 1. Use this to check for switch modes. If you've got a toggleM() switch using field placement 3, you can write `buttonFieldBit(3).` It will return TRUE for switch mode 1 and FALSE for switch mode 0.&#x20;

#### rotaryFieldBit(int bit);

Type in a field placement to check if this bit is 1. Use this to check for switch modes. If you've got a rotaryAnalog2Mode switch using field placement 6, you can write `rotaryFieldBit(6).` It will return TRUE for switch mode 1 and FALSE for switch mode 0.&#x20;

#### **buttonPressed(int row, int column)**

Check if a button or toggle on a given row and column number is pressed. Example: `buttonPressed(3,4)` to check a switch on row3 column4.

#### **switchPressed(int row, int column)**

Check of a button or toggle on a given row and column number is pressed. Example: `switchPressed(3,4)` to check a switch on row3 column4. This differs from buttonPressed() is that this function looks at the raw data input from the switch, not the processed and debounced button press. The advantage of this is that you can check for the state of a switch that isn't using any switch funtion, and thus not generating any button press in windows.&#x20;

#### **togglePressed(int row, int column)**

Check of a momentary button using a latching mode on a given row and column number is pressed. Example:`togglePressed(3,4)` to check a switch on row3 column4.

#### presetSearch (int presetNumber)

Returns true if you're in the preset in question. Example: `presetSearch(4)` will return TRUE of you're in preset 4, otherwise it returns FALSE.

#### **modButtonPressed ()**

Returns TRUE if modbutton is pressed, otherwise FALSE. Doesnt require any input, simply write `modButtonPressed()`.&#x20;

#### **rotaryPosition(int switchNumber, int switchPosition)**

This function check a rotary switch for a given position. Give it the switch# assigned to your switch as well as a switch position. Will return TRUE if this switch is in that position, otherwise FALSE. Example: `rotaryPosition(3,9)` will check if the switch with switch# 3 is in position 9 or not.&#x20;

#### **encoderStack(int row, int column, int layer)**

This function check a stacked encoder for which layer it is currently in. Type in the row and column number for the stack button and which layer you want to check for. Stack layers start on 0.&#x20;

