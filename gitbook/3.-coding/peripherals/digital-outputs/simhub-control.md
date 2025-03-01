# SimHub control

We can use the feature rich RGB LED editor in SimHub to control our output hubs. We'll make a virtual LED strip and trick SimHub into sending us data for RGB LEDs, which we will use to feed the output hubs instead.&#x20;

Naturally, SimHub cant change the color or brightness of our analog LEDs. So the way you use the RGB editor is by making the virtual LED _black or brightness 0_ will turn the output off, and any other color or brightness setting will turn it on.&#x20;

<figure><img src="../../../.gitbook/assets/image (100).png" alt=""><figcaption></figcaption></figure>

It doesn't have to be analog LEDs we're controlling with out output pins, the SimHub connection will just give us a very convenient way to control individual outputs, make profiles and use game telemetry to turns things on and off.&#x20;

We'll start off in 14\_LEDSetup.ino:

```
//----------------------------------------------------------------------------
// ---------------------------- STRIP #1 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED1COUNT 0
#define LED1PIN 2  
#define LED1TYPE NEO_GRB + NEO_KHZ800
#define LED1REVERSE 0
#define LED1PRIVATE 0
```

If we're sending LED data to output hubs, STRIP #1 is reserved for that. If you're using real RGB LEDs as well, put those on strip 2, 3 and/or 4.&#x20;

Set <mark style="background-color:yellow;">LED1COUNT</mark> to the total amout of output slots we're using on all of our hubs combined. If we're taking the examples from the [setup](setup.md) chapter, we've got 4 hubs; the first three with 16 active slots and the 4th with 6 slots used. In total 54 outputs.&#x20;

Nothing else needs to be filled out, we don't have a LED pin.&#x20;

For the sake of education, lets say we also have a real RGB LED strip with 40 LEDs wired to pin 25. We'll put those on STRIP #2 then, and the results is like this:

```
//----------------------------------------------------------------------------
// ---------------------------- STRIP #1 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED1COUNT 54
#define LED1PIN 2
#define LED1TYPE NEO_GRB + NEO_KHZ800
#define LED1REVERSE 0
#define LED1PRIVATE 0

//----------------------------------------------------------------------------
// ---------------------------- STRIP #2 SETUP -------------------------------
//----------------------------------------------------------------------------

#define LED2COUNT 40
#define LED2PIN 25
#define LED2TYPE NEO_GRB + NEO_KHZ800
#define LED2REVERSE 0
#define LED2PRIVATE 0
```

Next, we'll have to feed the LED data stream to our output hubs. We'll move on to 45\_OutputHubs.ino:

```
void outputHubRun()
{
//--------------------------------------
//---------CONTROLLING OUTPUT HUBS------
//---------------START HERE-------------
//--------------------------------------





//--------------------------------------
//---------------END HERE---------------
//--------------------------------------
}
```

We'll use the function `outputLEDImport(hub number,  start LED)` to link our hubs to the SimHub LED data stream. One function call for each hub, each continuing on the chain where the other stopped. Keep in mind that when working with LEDs in DDC, we're refering to the first LED in the chain as **0**, while in SimHub the first is **1**. So the first 16 LEDs in DDC are 0 to 15, while in SimHub 1 to 16.

```
void outputHubRun()
{
//--------------------------------------
//---------CONTROLLING OUTPUT HUBS------
//---------------START HERE-------------
//--------------------------------------

outputLEDImport(1,0);
outputLEDImport(2,16);
outputLEDImport(3,32);
outputLEDImport(4,48);


//--------------------------------------
//---------------END HERE---------------
//--------------------------------------
}
```

In SimHub, you'll now have a chain of 94 LEDs, ordered like this:

<figure><img src="../../../.gitbook/assets/image (7).png" alt=""><figcaption></figcaption></figure>

[Read this](../../../4.-advanced-features/simhub-control.md) on making connection between SimHub and your controller.&#x20;
