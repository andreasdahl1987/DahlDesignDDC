# Collaboration

Help to improve and develop is very welcome. Please submit any suggestions as issue rapports or pull requests on the [DDC GitHub](https://github.com/andreasdahl1987/DahlDesignDDC) page.&#x20;

### Support for new boards

DDCs joystick rapport is made with libraries based on [Matt Heironimus's joystick library. ](https://github.com/MHeironimus/ArduinoJoystickLibrary)Some adjustments are made for the different boards and to avoid some existing bugs. Adding support for new boards will not require you to use this library, but will require you the use the same API naming.

Here is a list of APIs used:

#### Joystick\_(...)

Constructor used to initialize and setup the Joystick. The following optional parameters are available:

* `uint8_t hidReportId` - Default: `0x03` - Indicates the joystick's HID report ID. This value must be unique if you are creating multiple instances of Joystick. Do not use `0x01` or `0x02` as they are used by the built-in Arduino Keyboard and Mouse libraries.
* `uint8_t joystickType` - Default: `JOYSTICK_TYPE_JOYSTICK` or `0x04` - Indicates the HID input device type. Supported values:
  * `JOYSTICK_TYPE_JOYSTICK` or `0x04` - Joystick
  * `JOYSTICK_TYPE_GAMEPAD` or `0x05` - Gamepad
  * `JOYSTICK_TYPE_MULTI_AXIS` or `0x08` - Multi-axis Controller
* `uint8_t buttonCount` - Default: `0` - Indicates how many buttons will be available on the joystick.
* `uint8_t hatSwitchCount` - Default: `0` - Indicates how many hat switches will be available on the joystick. Range: `0` - `2`
* `bool includeXAxis` - Default: `true` - Indicates if the X Axis is available on the joystick.
* `bool includeYAxis` - Default: `true` - Indicates if the Y Axis is available on the joystick.
* `bool includeZAxis` - Default: `true` - Indicates if the Z Axis (in some situations this is the right X Axis) is available on the joystick.
* `bool includeRxAxis` - Default: `false` - Indicates if the X Axis Rotation (in some situations this is the right Y Axis) is available on the joystick.
* `bool includeRyAxis` - Default: `true` - Indicates if the Y Axis Rotation is available on the joystick.
* `bool includeRzAxis` - Default: `false` - Indicates if the Z Axis Rotation is available on the joystick.
* `bool includeRudder` - Default: `false` - Indicates if the Rudder is available on the joystick.
* `bool includeThrottle` - Default: `true` - Indicates if the Throttle is available on the joystick.
* `bool includeAccelerator` - Default: `false` - Indicates if the Accelerator is available on the joystick.
* `bool includeBrake` - Default: `true` - Indicates if the Brake is available on the joystick.
* `bool includeSteering` - Default: `false` - Indicates if the Steering is available on the joystick.

For the above, `includeRxAxis, includeRzAxis, includeRudder, includeAccelerator` and `includeSteering` are `false` in DDC. So these will have to be included in the function, but they dont have to lead to anything.&#x20;

HID adresses for the joystick axis:

* X -> 0x30
* Y -> 0x31
* Z -> 0x32
* Ry -> 0x34
* Throttle -> 0xBB
* Brake -> 0xC5

The joystick axis should be 16bit, but adjustable with Joystick.Set<>Range(), example: **Joystick.setXAxisRange(int32\_t minimum, int32\_t maximum)**

And to set the value: **Joystick.setXAxis(int32\_t value)**

#### Joystick.begin(bool initAutoSendState)

* Starts emulating a game controller connected to a computer. By default, all methods update the game controller state immediately. If `initAutoSendState` is set to `false`, the `Joystick.sendState` method must be called to update the game controller state. The value used in DDC is `false` so it doesn't have to lead to anything.&#x20;

#### Joystick.setButton(uint8\_t button, uint8\_t value)

* Sets the state (`0` or `1`) of the specified button (range: `0` - (`buttonCount - 1`)). The button is the 0-based button number (i.e. button #1 is `0`, button #2 is `1`, etc.). The value is `1` if the button is pressed and `0` if the button is released.

#### Joystick.sendState()

Sends the updated joystick state to the host computer.&#x20;
