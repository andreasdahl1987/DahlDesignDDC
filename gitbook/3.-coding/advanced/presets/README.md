# Presets

Presets is one of the key features of DDC. Since this firmware gives so much freedom with regards to customization, it would be nice to quickly swap between highly customized and car/sim-specific setups. This is what presets are for, and you have 12 of them. _**Any relevant thing can be put into a preset**_. A preset can fundamentally change the way the controller works. You can have one preset with loads of fancy functions, using 100 + button numbers, and one preset where none of the buttons work. And everything in between.

**By default the controller will boot in preset 1.** However, some switch functions will allow you to boot to the  preset corresponding to the physical position of that switch.&#x20;

There are two files related to the preset system:

`31_RunningPresets.ino`, holding the `runningPresets()` function

`32_Presets.ino`, holding the `presets(int presetNumber)` function

These are both relevant, and work in completely different ways.

### Changing preset

Presets are changed with a various switch functions. Examples are:

* [_preset2Bit()_](../../../switch-library/encoders/rotary2bit.md#preset2bit)_,_ which works like any other incremental encoder, but scrolls through presets when mode button is held.
* [_SW1PresetRotary()_](../../../switch-library/rotary-switches/sw1.md#sw1presetrotary), which has several modes, and therefore doesn't change preset when holding the mode button, but needs the controller to have a presetButton(), which is held to set the preset. This function is for a 12-position switch, so the preset will be set to the physical position of the switch. The boot preset will also be the physical position of this switch.
