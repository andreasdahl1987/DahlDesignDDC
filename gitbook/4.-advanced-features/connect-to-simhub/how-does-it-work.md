# How does it work?

### Bit fields

The controller settings are sent over USB as two _bit fields._&#x20;

To explain what a bit field is, I'll have to explain a few other things first.

_Bits_ are the building blocks, the currency and the language in computing. A single bit is essentially an on/off-switch. The bit is a logical state 0 or 1. On or off. Often, it represents a physical component, such as the charge of a capacitor or the conduction properties of a transistor. A flash memory drive has millions of transistors, each representing a _bit,_ each possible to change between two states.&#x20;

In programming, a single bit is usually too small to work with. If you want to express a number of a certain size, you'll need a bunch of bits. So we're working with several bits at the time.&#x20;

<figure><img src="../../.gitbook/assets/image (121).png" alt="" width="375"><figcaption></figcaption></figure>

When programming microcontrollers, typically the smallest package of bits is 8 (such as a byte). When programming applications it is usually 16. Everything is built around using these different sized packages of bits. Think of it like buying a pack of cigarettes. Buying single sigarettes is not possible (at least not where I'm from), you'll have to adhere to the system and buy 20 at the time.&#x20;

<figure><img src="../../.gitbook/assets/image (124).png" alt="" width="375"><figcaption></figcaption></figure>

This means that if I have eight different settings in my firmware that is either on or off, and I want to express this in code, I'll have to pop an 8-pack of bits (byte) for each one. Since I'm only trying to express on/off (1 or 0), I'll only be using the first bit in each byte. The remaining 7 bits are never used.  The equivalent in cigarettes is that if you need 8 cigarettes, you'll buy 8 packets of cigarettes and only take a single cigarette from each. Sounds crazy? Well this is how it works. It is more convenient this way, and trying to make use of every bit in every byte will require more processing power.&#x20;

However, if we're going to send information somewhere, it is not necessarily convenient anymore. We'd like the information to be as condensed as possible, since sending stuff both takes time and processing power. In that case it might be worth trying to make use of every bit. Instead of using 8 bytes for my 8 on/off-settings, I'll try to use every bit of a single byte.

Before I had 8 bytes that had a value of either 1 or 0. Now I have a single byte who's value doesn't make much sense anymore. Lets say that setting number 1, 4 and 8 are on, and the others are off. The bits in the byte would spell out like 10001001. In decimal number this is **137.** But in this context, the number 137 doesn't mean anything. This byte is only useful if it comes with an explaination:

<figure><img src="../../.gitbook/assets/image (123).png" alt="" width="375"><figcaption></figcaption></figure>

And now we have a bit field; a package of bits with more information that just the total value of the package. Bit fields have to come with an explaination, or else you wont know which bit means what.&#x20;

### Bit fields in DDC

DDC sends controller settings in two 16-bit packages. 32 bits total, 32 settings on/off. These two fields are named _**rotaryField**_ and _**buttonField.**_ Don't mind the names, they don't mean anything. You can have a look at 19\_Bitfields to see how they are structured:

````
//-------------------------------------
//--BIT FIELDS FOR SIMHUB PROPERTIES---
//-------------------------------------

int rotaryField = 0;

/*
 * First field, pushed to joysick axis Z

 Most significant
 16 - Unused because of bug in joystick library
 15 - Bite button pressed
 14 - Dual clutches
 13 - Dual clutches
 12 - Bite point setting
 11 - Bite point setting
 10 - DDS switch
 9 -- DDS switch
 8 -- Calibration active
 7
 6
 5
 4
 3
 2
 1
 Least significant

 */
 

int buttonField = 0;

/*
 * Second field, pushed to joysick axis Y

 Most significant
 16 - Unused because of joystick library bug
 15 - Neutral mode
 14 - Presets 4th bit
 13 - Presets 3rd bit
 12 - Presets 2nd bit
 11 - Presets 1st bit
 10 - Handbrake active
 9 -- QuickSwitch active
 8 -- QuickSwitch mode
 7 -- Magic button active
 6 -- Throttle Hold active
 5 -- Neutral active
 4
 3
 2
 1
 Least significant

 */

```
````

The top one is rotaryField, the bottom one is buttonField. As you can see, many of the bits in each field is already in use. Only 4 bits available in buttonField and 7 in rotaryField. This is because many of the DDC functions will automatically send info to these fields. Such as magic button activation, dual clutches modes and current preset selected. However, if you're not using any of these functions, you can overwrite their place in the fields. Feel free to edit these comments in 19\_Bitfields and set up the fields the way you like.&#x20;

In the plugin, the fields are displayed at the bottom:

<figure><img src="../../.gitbook/assets/image (109).png" alt=""><figcaption></figcaption></figure>

The colored boxes are the ones that are reserved for specific functions.&#x20;
