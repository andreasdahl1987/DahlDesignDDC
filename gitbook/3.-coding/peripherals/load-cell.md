# Load cell

Setting up the load cell amplifier in DDC is not a lot of code, but there is some calibration involved. Since the amplifier outputs a 24 bit value that can be both positive and negative we'll need to turn this into something that fits the analog channels.

### 1. Setup

Start by going to `2_Board.ino` scroll down to and adjust these parameters:

```
//------------------------------
//----------LOAD CELL-----------
//------------------------------

#define LOADCELL_ENABLED 0
#define LOADCELL_DATA_PIN 0
#define LOADCELL_CLOCK_PIN 1
#define LOADCELL_OVERSAMPLING 5
```

* Set `LOADCELL_ENABLED` to 1 to start using the load cell.
* Set up `DATA_PIN` and `CLOCK_PIN` to match your wiring.
* Adjust `LOADCELL_OVERSAMPLING` to set the amount of samples to average. A high number will give very smooth but less responsive outputs. A lower number will give very responsive outputs but can be more noisy. Set it as low as possible while still experiencing a clean signal output. Defaults to 5, but can likely be set lower. Set to 1 to have no oversampling at all.&#x20;

Next set up an analog channel for the loadcell in `10_TableAndAnalog.ino`:

```
//---------------------------------------
//--------ANALOG CHANNEL SETUP-----------
//---------------------------------------

#define analogChannelCount 1                             //Number of analog channels

uint8_t analogPins[analogChannelCount] =                 //Pin number for your analog channels
{ ADC1 };

uint8_t analogButtonNumber[analogChannelCount] =         //Button number for your analog channels
{ 0 };

uint8_t analogButtonNumberIncMode[analogChannelCount] =  //Button number for alternate modes
{ 0 };

```

As with other external ADCs, we don't have a pin number here, so we'll use the key word **"ADC"** and the channel number we're using. In this case we're only using 1 analog channel, so we'll set the pin number to ADC1. We likely wont need any button numbers for this load cell, so let's keep that as is.&#x20;

In a scenario where we'd activated [oversampling of the RP2040 ADC](../essentials/dahldesignddc.ino.md#activate-oversampling), the first 4 analog channels will be occupied. In that case we'd set `analogChannelCount` to 5 and use ADC5 for our load cell.&#x20;

```
//---------------------------------------
//--------ANALOG CHANNEL SETUP-----------
//---------------------------------------

#define analogChannelCount 5                             //Number of analog channels

uint8_t analogPins[analogChannelCount] =                 //Pin number for your analog channels
{ ADC1, ADC2, ADC3, ADC4, ADC5 };

uint8_t analogButtonNumber[analogChannelCount] =         //Button number for your analog channels
{ 0 };

uint8_t analogButtonNumberIncMode[analogChannelCount] =  //Button number for alternate modes
{ 0 };

```

### 2. Raw loadcell output

So we've enabled the load cell system and reserved an analog channel, but the load cell data is not being sent to the analog channel. The reason is that the load cell data is 24 bit,  and both negative and positive values. The analog channels have room for 15 bit values which can only be positive. On other words, the load cell amplifier sends us numbers between -8&#x20;388&#x20;608 and 8388 608, but the analog channels only know how to count to 32 768.

To hook the load cell amplifiers data stream up to an analog channel:

* Read the loadcell values from the serial monitor by adding `checkLoadcell();` to `30_Switches.ino.`&#x20;

```
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------


checkLoadcell();


  //--------------------------------------
  //---------SWITCHES END HERE------------
  //--------------------------------------
```

Note the range of values that makes sense to use. In my case, the values we're hovering at around -78 000 in resting position, and reaching 400 000 under the highest load I needed for my project.&#x20;

* Inject the data to an analog channel with `loadcellInject().` This function will turn a set range of loadcell amplifier data into a number between 0 and 32 768, and sent it to an analog channel.&#x20;

```cpp
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------


checkLoadcell();
loadcellInject(1,-80000,420000);


  //--------------------------------------
  //---------SWITCHES END HERE------------
  //--------------------------------------
```

The function wants you to plot in the analog channel number, the smallest value in your range and the largest value in your range, in that order. In this example I'm using the values I found using `checkLoadcell();` and adding a little bit of range on both ends. Sending it to analog channel 1.&#x20;

_Remember to remove `checkLoadcell();` from your code after you're done using it. It can cause issues with USB communication._&#x20;

### 3. Start using the analog channel

Now that we've got the analog channel working, we can start using it in the same way we would when hooking a potentiometer, rotary switch or hall sensor chip to an analog input. The obvious usage would be `brake()`, but we could also make a throttle, clutch or handbrake. We could mount our seat to a load cell and make a warning if we gained too much weight over christmas, or have it switch presets according to who's in the seat. You could add an LED warning light that triggers when someone pulls your flimsy DIY handbrake too hard.&#x20;

Lets have a look at a simple brake example:

```cpp
  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------


loadcellInject(1,-80000,420000);
brake(1, 800, 31500);

  //--------------------------------------
  //---------SWITCHES END HERE------------
  //--------------------------------------
```

Building on the examples above, the brake() function wants to know which analog channel to use, the signal value in resting position and when fully pressed. We'll find these values by [reading the analog channel with checkValue()](../essentials/10_matrixandanalog.ino/analog-channels.md#reading-a-value). I found that resting my foot lightly on the brake pedal gave values around 400-600, so I set the start range of the brake pedal to 800. When pressing as hard as I can, I was maxing out at 32 200, but this felt a bit too much for 100% brake input, so I dialed it back a little to 31 500.&#x20;



