# Triggers

These are simple functions that can be used with conditional coding, or the LEDtrigger() function. These functions will return `true` or `false.`

#### buttonFieldBit(int bit)

Type in a field placement to check if this bit is 1. Use this to check for switch modes. If you've got a toggleM() switch using field placement 3, you can write `buttonFieldBit(3).` It will return TRUE for switch mode 1 and FALSE for switch mode 0.&#x20;

#### rotaryFieldBit(int bit);

Type in a field placement to check if this bit is 1. Use this to check for switch modes. If you've got a rotaryAnalog2Mode switch using field placement 6, you can write `rotaryFieldBit(6).` It will return TRUE for switch mode 1 and FALSE for switch mode 0.&#x20;

#### **buttonPressed(int row, int column)**

Check if a button or toggle on a given row and column number is pressed. Example: `buttonPressed(3,4)` to check a switch on row3 column4. This data is generated after debouncing algorithms, so this button needs to have a `pushButton(3,4)` or similar called in 30\_Switches.ino.&#x20;

#### **switchPressed(int row, int column)**

Check of a button or toggle on a given row and column number is pressed. Example: `switchPressed(3,4)` to check a switch on row3 column4. This differs from buttonPressed() is that this function looks at the raw data input from the switch, not the processed and debounced button press. The advantage of this is that you can check for the state of a switch that isn't using any switch funtion, and thus not generating any button press in windows.&#x20;

#### **togglePressed(int row, int column)**

Check of a momentary button using a latching mode on a given row and column number is pressed. Example:`togglePressed(3,4)` to check a switch on row3 column4.

#### presetSearch (int presetNumber)

Returns true if you're in the preset in question. Example: `presetSearch(4)` will return TRUE of you're in preset 4, otherwise it returns FALSE.

#### **modButtonPressed ()**

Returns TRUE if modbutton is pressed, otherwise FALSE. Doesnt require any input, simply write `modButtonPressed()`.&#x20;

#### **biteSettingMode (int biteSettingMode)**

Returns TRUE if the current bite setting mode (0 -3) is the same as you typed in the function. Otherwise FALSE.&#x20;

#### **rotaryPosition(int analogChannelNumber, int switchPosition)**

This function will check a rotary switch for a given position. Give it the channel number your switch is set up on, well as a switch position. Will return TRUE if this switch is in that position, otherwise FALSE. Example: `rotaryPosition(3,9)` will check if the switch on analog channel 3 is in position 9 or not.&#x20;

#### **rotary4BitPosition(int row, int column, int switchPosition)**

This function will check a 4 bit absolute encoder switch for a given position. Give it the row and column your switch is set up on, well as a switch position. Will return TRUE if this switch is in that position, otherwise FALSE. Example: `rotary4BitPosition(2,1,9)` will check if the switch on row 2 column 1 is in position 9 or not.&#x20;

#### **analogTravel(int analogChannel, int threshold)**

Check if an analog switch has travled at least to the set threshold of its total travel. For instance, if you want something to happen when a clutch paddle is pressed completely, use its channel number and set threshold to 100(%). &#x20;

#### **encoderStack(int row, int column, int layer)**

This function will check a stacked encoder for which layer it is currently in. Type in the row and column number for the stack button and which layer you want to check for. Stack layers start on 0.&#x20;

