# Triggers

These are simple functions that can be used with the LEDtrigger() function to set the condition to something happening in the firmware. These functions will return `true` or `false.`

#### buttonFieldBit()

Type in a field placement to check if this bit is 1. Use this to check for switch modes. If you've got a toggleM() switch using field placement 3, you can write `buttonFieldBit(3).` It will return TRUE for switch mode 1 and FALSE for switch mode 0.&#x20;

#### rotaryFieldBit();

Type in a field placement to check if this bit is 1. Use this to check for switch modes. If you've got a rotaryAnalog2Mode switch using field placement 6, you can write `rotaryFieldBit(6).` It will return TRUE for switch mode 1 and FALSE for switch mode 0.&#x20;

#### **buttonPressed()**

Check of a button or toggle on a given row and column number is pressed. Example: `buttonPressed(3,4)` to check a switch on row3 column4.

#### **togglePressed()**

Check of a momentary button using a latching mode on a given row and column number is pressed. Example:`togglePressed(3,4)` to check a switch on row3 column4.

#### presetSearch ()

Returns true if you're in the preset in question. Example: `presetSearch(4)` will return TRUE of you're in preset 4, otherwise it returns FALSE.

**modButtonPressed ()**

Returns TRUE if modbutton is pressed, otherwise FALSE. Doesnt require any input.&#x20;
