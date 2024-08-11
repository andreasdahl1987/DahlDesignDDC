# Settings

### Board settings

These are the settings for CB1, found in `2_Board.ino`

```
//------------------------------
//-------DAHL DESIGN CB1--------
//------------------------------

//Enable CB1 board
#define USING_CB1 0

//ADC setup
#define CB1_ADC1 1
#define CB1_ADC1_CHANNELS 4
#define CB1_ADC1_RATE 7
#define CB1_ADC1_GAIN 1

#define CB1_ADC2 1
#define CB1_ADC2_CHANNELS 4
#define CB1_ADC2_RATE 7
#define CB1_ADC2_GAIN 1

//Port expander setup
#define CB1_PE1 1
#define CB1_PE2 1
#define CB1_PE1_OUTPUT 0
#define CB1_PE2_OUTPUT 0

//ROW5 and ROW6
#define ROW5_ACTIVE 1
#define ROW6_ACTIVE 1

//ROW6 PWM
#define ROW6_PWMCOUNT 0

//ROW7
#define GROUND_CALIBRATION 10

//ROW8 setup
#define DISABLE_ALERT_PINS 0  //Gives access to COL2 and COL3. Disables ALERT pins for the ADCs, making them heavier to run.
#define DISABLE_ANALOG 0      //Gives access to COL4 - COL 7 by using (and disabling analog function of) ADC9 - ADC12 pins. 
#define DISABLE_LED_PIN 0     //Gives access to COL8, use the dedicated 8-8 pin. The LED pin will no longer work. 
```

#### //Enable CB1 board

This s covered before, simply turning on/off the whole CB1 package in DDC. It will works as a regular Pico board as well, and you can manually add the I2C devices if you wish.&#x20;

#### //ADC setup

These are settings for the two ADS1115 chips, named ADC1 and ADC2 here.&#x20;

ADC1:

* Pins ADC1-ADC4 (or RO7, COLUMN1 - 4 as digital inputs)

ADC2:&#x20;

* Pins ADC5-ADC8 (or ROW7, COLUMN5 - 8 as digital inputs)

You can turn the individial chips off by settings `CB1_ADC1` and `CB1_ADC2` to `0`. This is important if you removed any of these in the Pick\&Place to save costs on your board.&#x20;

You can adjust `CHANNELS`, `RATE` and `GAIN` as well. What these mean are explained [here.](../../3.-coding/peripherals/i2c-devices/ads1115.md#a-ds1115run)

#### //Port expander setup

You can turn the individial chips off by settings `CB1_PE1` and `CB1_PE2` to `0`. This is important if you removed any of these in the Pick\&Place to save costs on your board.  Disabling PE1 will disable ROW1 and ROW2. Disabling PE2 will disable ROW3 and ROW4.&#x20;

You can also chose to use one or both  of these as output devices by setting `CB1_PE1_OUTPUT` and/or `CB1_PE2_OUTPUT` to `1`.  Read [this on output hubs](../../3.-coding/peripherals/digital-outputs/). Your port expanders will be hubs 1 and 2 if both are used. If only one of them are set up as output device, it will be hub number 1. You can also add direct microcontroller pins as output pins in 9\_CB1\_Table.ino. The pin numbers from row 5 to 8 are listed on the back of the board.&#x20;

#### //ROW5 and ROW6

ROW5 and ROW6 uses the RP2040 input pins directly, and are all set up with internal pullups. If you want to use these pins for anything other than digital inputs, you'll have to "disable" a row to turn off the internal pullups. After that they can be used however you want. The pin numbers are written on the back of the CB1 board.&#x20;

Set `ROW5_ACTIVE` to `0` to disable ROW5

Set `ROW6_ACTIVE` to `0` to disable ROW6.

#### //ROW6 PWM

ROW6 pins can be set as PWM pins, building up to 8 PWM channels. Set `ROW6_PWMCOUNT` to any number between 1 - 8 to make up to 8 PWM channels.&#x20;

If you set it to 3, then ROW6, COLUMN 1-3 will be PWM channels 1-3. ROW6, COLUMN 4-8 will work like before. If ROW6 is set to not active, you will still set up PWM channels for the pins you've selected.

#### //ROW7

ROW7 digital inputs uses the ADS1115 readings. When you wire a button to these pins, and the other end of the button to ground, the pin is "floating", and the ADC stabilizes at a certain readout. When you press the button, the ADS1115 will measure 0 volt, and that will be registered as a button press. However, if your setup involves a lot of connectors, some long wires and poor soldering, it might not be exactly 0 volt when the button is pressed. It might be 0.01 volt. In that case, the CB1 wont register the button press.&#x20;

The `GROUND CALIBRATION` is the threshold value at which the CB1 will accept a voltage being "ground". The default value 8 corresponds to 0.001 V at default settings. If you're not getting any response from ROW7 pins or getting jittery responses, increase this value untill it starts working. Rarely will you need it any higher than 20. For a well organized board a value of 1 or 2 should be enough. If you set this very high (> 100), switch inputs on ROW7 will become laggy.&#x20;

#### //ROW8 setup

On ROW8, only column pin 1 is usable without making sacrifices. Column pin 2-8 all require you to disable other functions in order to get more digital inputs.

* `DISABLE_ALERT_PINS` can be set to `1` to make your ADS1115 and your whole controller code a bit slower. In return you'll get access to COLUMN2 - 3. The slowdown should not affect performance at all, which is why this option is even an option.
* `DISABLE_ANALOG` can be set to `1` to disable ADC9-12 and make these pins ROW8 COLUMN4 - 7 instead.&#x20;
* `DISABLE_LED_PIN` can be set to `1` to the LED pin and make this pin ROW8 COLUMN8 instead. Note that the LED pin and 8-8 pin is not the same physical pin on the board. When using this as a digital input you have to get in before the level shifter IC, which is why a different pin is used.&#x20;
