# Mouse

Mouse control needs two kinds of switches set up:&#x20;

* Mouse Active button/toggle to enable mouse control momentarily
* Mouse fuctions that move, click, scroll, etc. as long as mouse control is active.&#x20;

### 1. Mouse active

#### mouseActiveButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton, should be assigned a button number. When held, it will open up for other switches to control the mouse cursor.
{% endtab %}

{% tab title="Example" %}
`void mouseActiveButton(int row, int col)`

For a switch on row 2 column 4 -> `mouseActiveButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
{% endtab %}
{% endtabs %}

#### mouseActiveButtonMute()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton, doesn't output any joystick button press. When held, it will open up for other switches to control the mouse cursor.
{% endtab %}

{% tab title="Example" %}
`void mouseActiveButtonMute(int row, int col)`

For a switch on row 2 column 4 -> `mouseActiveButtonMute(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* None
{% endtab %}
{% endtabs %}

#### mouseActiveLatch()

{% tabs %}
{% tab title="Description" %}
Use a momentary pushbutton to toggle "Mouse Active" on/off. Doesn't output any joystick button press. When toggled, will open up for other switches to control the mouse cursor.

The status of the toggle will be sent to the buttonField, allowing you to get SimHub properties indicating if mouse contol is active or not.&#x20;
{% endtab %}

{% tab title="Example" %}
`void mouseActiveLatch(int row, int col, int fieldPlacement)`

For a switch on row 2 column 4 -> `mouseActiveLatch(2,4,3);`

The toggle status will in this case be on position 3 in the buttonField, propery name \[DDC.B3] in SimHub. &#x20;
{% endtab %}

{% tab title="Requirements" %}
* 1 slot in buttonField
{% endtab %}
{% endtabs %}

### 2. Mouse control

#### leftMouseButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton. When "Mouse Active", it will work as the left mouse button. Otherwise work like a normal joystick pushbutton.
{% endtab %}

{% tab title="Example" %}
`void leftMouseButton(int row, int col)`

For a switch on row 2 column 4 -> `leftMouseButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### rightMouseButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton. When "Mouse Active", it will work as the right mouse button. Otherwise work like a normal joystick pushbutton.
{% endtab %}

{% tab title="Example" %}
`void rightMouseButton(int row, int col)`

For a switch on row 2 column 4 -> `rightMouseButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### middleMouseButton()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton. When "Mouse Active", it will work as the middle mouse button. Otherwise work like a normal joystick pushbutton.
{% endtab %}

{% tab title="Example" %}
`void middleMouseButton(int row, int col)`

For a switch on row 2 column 4 -> `middleMouseButton(2,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### mouseMove()

{% tabs %}
{% tab title="Description" %}
Momentary pushbutton. Will works as a normal joystick button, but when "Mouse Active" it will move the mouse cursor in the direction and with the speed you set it to.\
\
Mouse directions:

* Left: `1` or `MOUSE_LEFT`
* Right: `2` or `MOUSE_RIGHT`
* Up: `3` or `MOUSE_UP`
* Down: `4` or `MOUSE_DOWN`

Mouse speed is a value between 1 and 100. This is a very large range of mouse speed, with 1 barely moving and 100 way too fast. This speed is in pixels/second, so large high resolution displays will need higher mouse speed for the same relative speed.&#x20;

You'll be able to set two mouse speeds; `mouseSpeed1` and `mouseSpeed2`. When holding the button, you'll be at mouseSpeed1 for the first 500 ms, then accelerate to mouseSpeed2 between 500-750 ms, and from 750 ms and out be at mouseSpeed2. This is to allow fine and coarse mouse movement with the same button. If you want a constant speed, just set mouseSpeed1 and mouseSpeed2 to the same value.
{% endtab %}

{% tab title="Example" %}
`void mouseMove(int row, int column, int direction, int mouseSpeed1, int mouseSpeed2)`

Setup explained:&#x20;

`void mouseMove(` &#x20;

`int row,`                 <— Row for this input

`int column,`           <— Column for this input

`int direction,`     <— Direction of mouse movement (1-4, see description tab)

`int mouseSpeed1,` <— Initial mouse speed

`int mouseSpeed2)`   <— Mouse speed after 750 ms of holding the button

For a button on row 2/column 5 moving mouse upwards (MOUSE\_UP or 3) with speed 15/25:

`mouseMove(2,5,MOUSE_UP,15,25);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### rotary2Scroll()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher. When "Mouse Active", it will let you scroll up and down.
{% endtab %}

{% tab title="Example" %}
`void rotary2Scroll(int row, int col, bool reverse)`

For an encoder wired to row 4, columns 2 and 3:

`rotary2Scroll(4, 2, false);`

The "reverse" input is to flip what happens on CW and CCW rotation. Here set to `false`. Set to `true` to flip.&#x20;

When "Mouse Active", it will let you scroll up/down, reverse it by setting reverse to `true.`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### E18Scroll()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher. When "Mouse Active", it will let you scroll up and down.
{% endtab %}

{% tab title="Example" %}
`void E18Scroll(int row, int col, bool reverse)`

For an encoder wired to row 4, columns 2 and 3:

`E18Scroll(4, 2, false);`

The "reverse" input is to flip what happens on CW and CCW rotation. Here set to `false`. Set to `true` to flip.&#x20;

When "Mouse Active", it will let you scroll up/down, reverse it by setting reverse to `true.`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### PEC11Scroll()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher. When "Mouse Active", it will let you scroll up and down.
{% endtab %}

{% tab title="Example" %}
`void PEC11Scroll(int row, int col, bool reverse)`

For an encoder wired to row 4, columns 2 and 3:

`PEC11Scroll(4, 2, false);`

The "reverse" input is to flip what happens on CW and CCW rotation. Here set to `false`. Set to `true` to flip.&#x20;

When "Mouse Active", it will let you scroll up/down, reverse it by setting reverse to `true.`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### funkyMouseButton()

{% tabs %}
{% tab title="Description" %}
Intended for funky center push button, but will also work for the directional input. When "Mouse Active", it will work as the left mouse button. Otherwise work like a normal joystick pushbutton.
{% endtab %}

{% tab title="Example" %}
`void funkyMouseButton(int row, int column, int pCol, int Col1, int Col2, int Col3)`

Fill in the row all the funky pins go to, the column of pushButton and then all the directional buttons.&#x20;

For a funkyswitch on row 2 with center push on column 5 and the directional inputs on columns 1-4:

`funkyMouseButton(2,5,1,2,3,4);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### funkyMouseMove()

{% tabs %}
{% tab title="Description" %}
Intended for funky directional inputs. Will work as a normal joystick button, but when "Mouse Active" it will move the mouse cursor in the direction and with the speed you set it to.\
\
Mouse directions:

* Left: `1` or `MOUSE_LEFT`
* Right: `2` or `MOUSE_RIGHT`
* Up: `3` or `MOUSE_UP`
* Down: `4` or `MOUSE_DOWN`

Mouse speed is a value between 1 and 100. This is a very large range of mouse speed, with 1 barely moving and 100 way too fast. This speed is in pixels/second, so large high resolution displays will need higher mouse speed for the same relative speed.&#x20;

You'll be able to set two mouse speeds; `mouseSpeed1` and `mouseSpeed2`. When holding the button, you'll be at mouseSpeed1 for the first 500 ms, then accelerate to mouseSpeed2 between 500-750 ms, and from 750 ms and out be at mouseSpeed2. This is to allow fine and coarse mouse movement with the same button. If you want a constant speed, just set mouseSpeed1 and mouseSpeed2 to the same value.&#x20;
{% endtab %}

{% tab title="Example" %}
`void funkyMouseMove(int row, int column, int pCol, int Col1, int Col2, int Col3, int direction, int mouseSpeed1, int mouseSpeed2)`

Setup explained:&#x20;

`void funkyMouseMove(` &#x20;

`int row,`                 <— Row for  the funky switch

`int column,`           <— Column for this input

`int pCol,`               <— Column for center push button

`int Col1,`               <— Column for the other 3 directional inputs

`int Col2,`&#x20;

`int Col3,`&#x20;

`int direction,`     <— Direction of mouse movement (1-4, see description tab)

`int mouseSpeed1,` <— Initial mouse speed

`int mouseSpeed2)`   <— Mouse speed after 750 ms of holding the button

For a funkyswitch on row 2 with center push on column 5 and the directional inputs on columns 1-4, moving mouse upwards (MOUSE\_UP or 3) with speed 15/25:

`funkyMouseMove(2,5,1,2,3,4,MOUSE_UP,15,25);`
{% endtab %}

{% tab title="Requirements" %}
* 1 button number
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### funkyMouseScroll()

{% tabs %}
{% tab title="Description" %}
Standard incremental encoder setup. Rotating CW will give a button pulse, rotating CCW will give a button pulse with a button number 1 value higher. When "Mouse Active", it will let you scroll up and down.
{% endtab %}

{% tab title="Example" %}
`void funkyMouseScroll(int Arow, int Acol, int Bcol, bool reverse)`

For an encoder with pins A and B to columns 3 and 4. Common pin to row 2:

`funkyMouseScroll(2, 3, 4, false);`

The "reverse" input is to flip what happens on CW and CCW rotation. Here set to `false`. Set to `true` to flip.&#x20;

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16.&#x20;

When "Mouse Active", it will let you scroll up/down, reverse it by setting reverse to `true.`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 button numbers
* mouseActive button or MOUSE\_ALWAYS\_ACTIVE set to 1.&#x20;
{% endtab %}
{% endtabs %}

#### analogMouse()

{% tabs %}
{% tab title="Description" %}
Set up a thumb stick to control the mouse cursor. This will require a whole lot of plotting values, since both axis of the switch should be calibrated for center, extreme negative and extreme positive positions. Any pushbutton built into the switch should be programmed with functions like pushButton(), biteButton(), etc., and are not included in this function.&#x20;

You can[ read values](../3.-coding/essentials/10_matrixandanalog.ino/analog-channels.md#reading-a-value) from your analog channels using the serial monitor.&#x20;

_This switch does not require a mouseActive-button._&#x20;
{% endtab %}

{% tab title="Example" %}
`void analogMouse (int xChannel, int yChannel, int xLeft, int xMiddle, int xRight, int yUp, int yMiddle, int yDown, int mouseSpeed)`

Setup explained:&#x20;

`analogMouse`&#x20;

`(int xChannel,`     <— Channel # for x axis

&#x20;`int yChannel,`       <— Channel # for y axis

&#x20;`int xLeft,`             <— Value for x axis pushed left

&#x20;`int xMiddle,`         <— Value for x axis in resting position

&#x20;`int xRight,`           <— Value for x axis pushed right

&#x20;`int yUp,`                 <— Value for y axis pushed up

&#x20;`int yMiddle,`         <— Value for y axis in resting position

&#x20;`int yDown,`             <— Value for y axis pushed down

&#x20;`int mouseSpeed)`   <— Mouse speed (1 - 100)

An `analogMouse()` set up on analog channels 3 and 4 with mouse speed of `15` could look like this:

`analogMouse (3,4,14,510,1020,1018,505,10,15);`&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 analog channels
{% endtab %}
{% endtabs %}

#### dualClutchAndMouse()

{% tabs %}
{% tab title="Description" %}
This is the same as [dualClutchCal()](pedals-and-paddles/clutch.md#dualclutch-or-dualclutchcal), but with mouse control built in.&#x20;

This is probably the worst way to control the mouse cursor, out of all available options. But if clutch paddles is all you have, this will work fine with some practice!&#x20;

The idea is that the slave paddle will controll the direction of the mouse movement and the master paddle will controll the mouse speed. So in essence the slave paddle is the steering wheel and the master paddle is the throttle for racing the mouse cursor across the screen.&#x20;

Mouse features are unlocked by holding/toggling a `mouseActive` button, or setting `MOUSE_ALWAYS_ACTIVE` to `1` in 2\_Boards.ino.

**Clutch features:**

4 modes:

0: Static - The slave paddle only reaches bite point, the master paddle goes to 100%

1: Dynamic low - Either paddle alone only reaches bite point, press both together to reach 100%

2: Dynamic high - Either paddle alone reaches 100%. Press both and release one to get to bite point.

3: Brake/throttle - Using the paddles as brake and throttle. Output now changes from joystick X axis to brake/throttle axis.&#x20;

Changing modes are done by holding the modButton and pressing either paddle all the way in and releasing. If this doesnt work, it is a good indication that your clutch doesnt reach a stable 100% or rest at a stable 0% - which means you should adjust your values.&#x20;

The function defaults to bits 13 and 14 in the rotary field. Will be returned by SimHub as property \[DahlDesign.DDCclutchMode].

_With to calibrate the output from your paddles you'll need to set up a clutchCalibrate() button._
{% endtab %}

{% tab title="Example" %}
`void dualClutchAndMouse(int masterAnalogChannel, int slaveAnalogChannel, bool throttleMaster, int mouseSpeed)`

Type on the analog channels used, throttleMaster is either `true` or `false`. When set to `true`, you'll use master paddle for throttle and slave for brake, if `false` it is the opposite. Mouse speed between 1 and 100 where 1 is barely moving and 100 is incredibly sensitive.&#x20;

Example:

`void dualClutchAndMouse(1, 2, true, 15);`
{% endtab %}

{% tab title="Requirements" %}
* modButton() to change modes
* biteButton() or bitePot() to change the pite point.
* launchButton() if you want 1-handed launches.
* clutchCalibration() button.
* Two analog channels
* Enabling mouse features in 2\_Boards.ino
{% endtab %}
{% endtabs %}
