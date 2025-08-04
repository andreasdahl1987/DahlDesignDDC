# Mouse

### 1. Setup

You'll activate mouse control in `2.Boards.ino`  :

```
//------------------------------
//-----------MOUSE--------------
//------------------------------

#define ENABLE_MOUSE 0
#define MOUSE_ALWAYS_ACTIVE 0

```

`ENABLE_MOUSE` should be set to `1` to access the mouse controll switch functions and load relevant libraries.&#x20;

`MOUSE_ALWAYS_ACTIVE` can be set to `1` to have mouse control always active. Any switch with mouse control features will then always be affecting the mouse cursor, and you won't need to hold or toggle a `mouseActiveButton`. The downside being that these switches now are completely dedicated to mouse control, and wont output any joystick button presses.&#x20;

### 2. Switch functions to use in 30\_Switches.ino

Have a look at the various[ switch functions here.](../../switch-library/mouse.md) These functions will let your switches control the mouse cursor when a `mouseActiveButton()`is held or `mouseActiveLatch()` is toggled. You chose one of your buttons to be the mouseActive button the same way you set up modButton, biteButton, etc. Alternatively you can, as explained above, set `MOUSE_ALWAYS_ACTIVE` to `1.`&#x20;
