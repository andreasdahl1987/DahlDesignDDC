# Encoders

There are thousands of encoders out there. DDC supports a bunch of them. So far in my tests I've identified and added support for 5 categories of encoders, that have different mechanical properties and thus need different algorithms to determine the direction of rotation. These categories should cover MOST encoders. You'll have to figure out which category your encoder belongs to, and use the switch functions for that encoder. If none of the categories work for you, contact me and we'll find a way to add support.&#x20;

Common to almost all encoders is that the switch has 2 or more paths to a common.&#x20;

You can measure the continuity between A->C and B->C and get the following outcomes:

<figure><img src="../.gitbook/assets/image.png" alt=""><figcaption></figcaption></figure>

As you rotate the switch, it will scroll through these states: 00, 10, 11, 01, 00, 10, 11, 01, 00, and so on. Rotating the other way and the order will be different: 00, 01, 11, 10, 00, etc. That way we can tell CW from CCW rotation.&#x20;

## Categories

### rotary2Bit

These functions are for encoders that move one step on each detent. You can test the encoder and see that it moves through 00, 10, 11, 01 as you turn it.

Encoders:

* CTS288
* CTS 12CE/11CE

### funkyRotary

These functions are for encoders that move 2 steps on each detent. They stop at 00 and 11. The 01 and 10 are in between the detents, and you'll need to wire up the encoder and use a serial monitor to find these states. Named after the funky switch, Alps RKJXT1F42001.

Encoders:

* Alps RKJXT1F42001
* Alps EC11
* TT Electronics EN11 (20 pulse)
* Bourns PEC11R

### **PEC11**

These functions are for encoders that move 4 steps on each detent. They stop at 00. The 01, 11 and 10 are all in between the detents, and you'll need to wire up the encoder and use a serial monitor to find these states. Named after the first switch I tested that works like this: Bourns PEC11H.

Encoders:

* Bourns PEC11H
* TT Electronics EN11 (15 pulse)

### rotary2Pulse

These functions are for encoders that mechanically works the way that the software usually tries to make an encoder work. Rotating CW will briefly close A->C and rotating CCW will briefly close B ->C. The switch is steady at 00 and can never be 11 since you can't turn it CW and CCW at the same time. It would actually work to code this switch as two pushbuttons. The switch very bounce-proof and only needs a lightweight algorithm to work.&#x20;

* Alps SRBM

### rotary4Bit

These functions are for 4-bit encoders. The way they work are identical to the rotary2Bit encoders, but they have 4 paths to a common
