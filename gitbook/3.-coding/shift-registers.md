# Shift registers

Setting up the shift registers is pretty much straight forward, it is all done in 11\_ShiftRegisters.ino

### 11\_ShiftRegisters.ino

```
//Shift register setup

#define SRCOUNT 0

//Shift register chain 1
#define SR1CHAIN 1
#define SR1DATA 2
#define SR1CLOCK 3
#define SR1LATCH 4

//Shift register chain 2
#define SR2CHAIN 1
#define SR2DATA 2
#define SR2CLOCK 3
#define SR2LATCH 4

//Shift register chain 3
#define SR3CHAIN 1
#define SR3DATA 2
#define SR3CLOCK 3
#define SR3LATCH 4

//Shift register chain 4
#define SR4CHAIN 1
#define SR4DATA 2
#define SR4CLOCK 3
#define SR4LATCH 4
```

* `#define SRCOUNT 0` -> How many chains you'll be using. 0 to 4. 0 will inactivate SR reaading.
*   Set up as many chaines as stated in SRCOUNT, starting with chain 1.&#x20;

    * SRxCHAIN is the amount of SR chips in this chain
    * SRxDATA is the pin number used for DATA on this chain
    * SRxCLOCK is the pin number used for CLOCK on this chain
    * SRxLATCH is the pin number used for LATCH on this chain.



Example: 2 chains, 6 SR in the first, 1 in the second. Sharing CLOCK and LATCH, not sharing DATA pins (don't share DATA pins, it wont work).

```
//Shift register setup

#define SRCOUNT 2

//Shift register chain 1
#define SR1CHAIN 6
#define SR1DATA 10
#define SR1CLOCK 9
#define SR1LATCH 14

//Shift register chain 2
#define SR2CHAIN 1
#define SR2DATA 6
#define SR2CLOCK 9
#define SR2LATCH 14

//Shift register chain 3
#define SR3CHAIN 1
#define SR3DATA 2
#define SR3CLOCK 3
#define SR3LATCH 4

//Shift register chain 4
#define SR4CHAIN 1
#define SR4DATA 2
#define SR4CLOCK 3
#define SR4LATCH 4
```
