# Collaboration

Help to improve and develop is very welcome. Please submit any suggestions as pull requests on the [DDC GitHub](https://github.com/andreasdahl1987/DahlDesignDDC) page.&#x20;

Likely, the most used MCU for this firmware will be the 32U4. There are two bottlenecks whne writing firmware to this controller.

* The processor is slow, so adding calculations and libraries that require a lot of processing will slow down the code a lot and will make the contoller less responsive. Some of the functions, the encoder functions in particular, will stop working if the refresh rate is too slow. The loop should be run at at least 150 Hz to be safe, migh work as low as 100 Hz. Ideally > 300 Hz.&#x20;
* There is storage memory limitations. Up to 100% of storage memory can be used safely. Dynamic memory should be below 80%, and I havent come close to that with the current version. Adding libraries or code with a lot of stored variables can cause limitations to project size. At the moment - a wheel with a large amount of inputs (50 buttons/encoders + LED support + 5 analog axis) will use close to 100% storage memory when using a wide variety of functions. Keep it simple and add new features in a way that it wont be compiled if it is not in use.

### Support for new boards

For now, I'd like to keep using the Joystick library from Matt Heironimus, as it works great for the supported microcontrollers. It would be difficult to add support for completely different boards to this library (for me at least). Such as ESP32, STM32 and RP2040. I believe the simplest approach would be to modify existing libraries for said boards to match the naming and execution of the APIs used in Heironimus' joystick library.&#x20;

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
