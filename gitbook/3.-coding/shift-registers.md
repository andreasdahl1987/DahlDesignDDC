# Shift registers

Setting up the shift registers is pretty much straight forward, it is all done in 11\_ShiftRegisters.ino

### 11\_ShiftRegisters.ino

```
//----------------------------------------------------------------------------
// ------------------------- SHIFT REGISTER SETUP ----------------------------
//----------------------------------------------------------------------------

#define SRCOUNT 0

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #1 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR1CHAIN 1
#define SR1DATA 2
#define SR1CLOCK 3
#define SR1LATCH 4

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #2 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR2CHAIN 1
#define SR2DATA 2
#define SR2CLOCK 3
#define SR2LATCH 4

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #3 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR3CHAIN 1
#define SR3DATA 2
#define SR3CLOCK 3
#define SR3LATCH 4

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #4 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR4CHAIN 1
#define SR4DATA 2
#define SR4CLOCK 3
#define SR4LATCH 4
```

* `#define SRCOUNT 0` -> How many chains you'll be using. 0 to 4. 0 will inactivate SR reading.
*   Set up as many chaines as stated in SRCOUNT, starting with chain 1.&#x20;

    * CHAIN is the amount of SR chips in this chain
    * DATA is the pin number used for DATA on this chain
    * CLOCK is the pin number used for CLOCK on this chain
    * LATCH is the pin number used for LATCH on this chain.



Example: 2 chains, 6 SR in the first, 1 in the second. Sharing CLOCK and LATCH, not sharing DATA pins (don't share DATA pins, it wont work).

```
//----------------------------------------------------------------------------
// ------------------------- SHIFT REGISTER SETUP ----------------------------
//----------------------------------------------------------------------------

#define SRCOUNT 2

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #1 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR1CHAIN 6
#define SR1DATA 8
#define SR1CLOCK 10
#define SR1LATCH 15

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #2 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR2CHAIN 1
#define SR2DATA 7
#define SR2CLOCK 10
#define SR2LATCH 15

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #3 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR3CHAIN 1
#define SR3DATA 2
#define SR3CLOCK 3
#define SR3LATCH 4

//----------------------------------------------------------------------------
// ---------------------------- CHAIN #4 SETUP -------------------------------
//----------------------------------------------------------------------------

#define SR4CHAIN 1
#define SR4DATA 2
#define SR4CLOCK 3
#define SR4LATCH 4
```
