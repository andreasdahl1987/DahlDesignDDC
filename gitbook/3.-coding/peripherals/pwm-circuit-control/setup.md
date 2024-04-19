# Setup

First, enable PWM and set up your PWM channels in 2\_Boards.ino

Scroll down to this part:

```
//------------------------------
//---------PWM CONTROL----------
//------------------------------
#define PWMENABLED 0

#if (ROW6_PWMCOUNT > 0)
  int8_t PWMChannelPins [ROW6_PWMCOUNT];
#elif (PWMENABLED == 1)
  int8_t PWMChannelPins [] = {99};
#endif

```

Set `PWMENABLED` to `1` and add your microcontroller pins used for PWM to create PWM channels.&#x20;

In this case we're using pins 16, 17 and 18, they will be on PWM channels 1, 2 and 3, respectively:

```
//------------------------------
//---------PWM CONTROL----------
//------------------------------
#define PWMENABLED 1

#if (ROW6_PWMCOUNT > 0)
  int8_t PWMChannelPins [ROW6_PWMCOUNT];
#elif (PWMENABLED == 1)
  int8_t PWMChannelPins [] = {16, 17, 18};
#endif
```

Don't mind the `ROW6_PWMCOUNT` stuff, it is related to an automatic PWM setup for the CB1 board.&#x20;
