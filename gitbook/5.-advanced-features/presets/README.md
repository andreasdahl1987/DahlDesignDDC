# Presets

Presets is one of the key features of DDC. Since this firmware gives so much freedom with regards to customization, it would be nice to quickly swap between highly customized and car/sim-specific setups. This is what presets are for, and you have 12 of them. _**Any relevant thing can be put into a preset**_. A preset can fundamentally change the way the controller works. You can have one preset with loads of fancy functions, using 100 + button numbers, and one preset where none of the buttons work. And everything in between.

**By default the controller will boot in preset 1.** However, some switch functions will allow you to boot to the  preset corresponding to the physical position of that switch.&#x20;

There are two files related to the preset system:

`31_RunningPresets.ino`, holding the `runningPresets()` function

`41_Presets.ino`, holding the `presets(int presetNumber)` function

These are both relevant to you, and work in completely different ways:

###

###

### Combined





