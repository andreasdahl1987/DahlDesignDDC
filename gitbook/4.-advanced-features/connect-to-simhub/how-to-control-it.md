# How to control it?

How can you have an impact on what it sent through [these two 16-bit fields](how-does-it-work.md#bit-fields-in-ddc)? &#x20;

### 1: Through switch functions

As mentioned in the previous chapter, many switch functions will automatically send info to pre-defined slots in the fields. Such as current preset selected is sent to buttonField bits 11-14 (or 10-13 if we're being strict, but in DDC we're not counting from 0 to be more user friendly). Using 4 bits, we can make a number between 0 and 15. DDC being capped at 12 presets will need 4 bits to express this number. 3 bits would only get us to 7.&#x20;

If you have dual clutches set up, you're already getting info on:

* Bite button pressed
* Dual clutch modes
* Bite point setting sequence
* Clutch calibration active

Some switch functions however, does not have a reserved slot in any of the fields. You'll have to select a slot in one of the fields when you use that function in 30\_Switches. For instance [rotaryAnalog2Modes()](../../switch-library/rotary-switches/rotaryanalog.md#description-4). This function lets you use a rotary switch as an absolute 12-position switch OR as a pulsing incremental switch. You can swap between these two settings, and you'll send info to rotaryField about which mode you're in. 0 is for 12-position mode, 1 is for incremental mode. This function only needs one bit in the field. This function forces you to use rotaryField, others will force you to use buttonField. I've tried to balance this out so you'll end up using both and having enough bits to use.&#x20;

### 2: Direct control

You can manipulate values in the bit fields directly by using [editors](../../3.-coding/advanced/conditional-coding/editors.md). Editors are functions that lets you manually change a lot of things running under the hood. This  moves us over to the more advanced parts of DDC, but it unlocks a whole bunch of possibilities for creative minds.&#x20;

The functions [sendToButtonField()](../../3.-coding/advanced/conditional-coding/editors.md#sendtobuttonfield-int-fieldposition-bool-condition) and [sendToRotaryField()](../../3.-coding/advanced/conditional-coding/editors.md#sendtorotaryfield-int-fieldposition-bool-condition) can be used in 30\_Switches to edit the fields however you like.&#x20;



