# Encoders

There are thousands of encoders out there. DDC supports most of them. So far in my tests I've identified and added support for 5 categories of encoders, that have different mechanical properties and thus need different algorithms to determine the direction of rotation. These categories should cover MOST encoders. You'll have to figure out which category your encoder belongs to, and use the switch functions for that encoder. If none of the categories work for you, contact me and we'll find a way to add support.&#x20;

Common to almost all encoders is that the switch has 2 or more paths to a common.&#x20;

You can measure the continuity between A->C and B->C and get the following outcomes:

<figure><img src="../../.gitbook/assets/image (3) (2) (1).png" alt=""><figcaption></figcaption></figure>

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
* Elma E33

### E18

Named after Elma E18, these functions are for encoders that move 2 steps on each detent, just like funkyRotary. Infact, the switch is mechanically very similar, but for the E18 in particular, the encoder is just way too bouncy to work with the funkyRotary algorithm. This algorithm is much stricter, and ensures 0 bouncing - but is also bit heavier on memory and processing power.

* Elma E18 (16 detent)

### wildEncoder

These functions are for encoders with an atypical signal output pattern, which is why I chose the name "wild". Depending on how you wired the A and B pins, it either never outputs 10 or never outputs 01. It will behave much like a **funkyRotary** or **E18**, which rests on a 11 or 00 output state, and going from 11 to 00 is via 10. However, going from 00 to 11 is a direct switch without ever outputting 01. This requires a completely different algorithm to make it work, and the switch is sensitive to swapping A and B pins. That is why the algorithm also has a software pin swap included.&#x20;

* Elma E18 (20 detent)

### **PEC11**

These functions are for encoders that move 4 steps on each detent. They stop at 00. The 01, 11 and 10 are all in between the detents, and you'll need to wire up the encoder and use a serial monitor to find these states. Named after the first switch I tested that works like this: Bourns PEC11H.

Encoders:

* Bourns PEC11H
* TT Electronics EN11 (15 pulse)
* Alps EC16

### rotaryPulse

These functions are for encoders that mechanically works the way that the software usually tries to make an encoder work. Rotating CW will briefly close A->C and rotating CCW will briefly close B ->C. The switch is steady at 00 and can never be 11 since you can't turn it CW and CCW at the same time. It would actually work to code this switch as two pushbuttons. The switch very bounce-proof and only needs a lightweight algorithm to work.&#x20;

Encoders:

* Alps SRBM

### rotary4Bit

These functions are for 4-bit encoders. The way they work are identical to the rotary2Bit encoders, but they have 4 paths to a common. So they will typically scroll through 0000 -> 0001 -> 0011 -> 0010 -> 0110 -> etc. In total 16 different configurations for 16 switch positions. These are _absolute encoders,_ meaning each position of the switch has a different signal output, and the actual physical position of the switch can be determined by reading the signal.&#x20;

All rotary4Bit() functions are for 16-position switches, but can be modified for 4-bit switches that have 8, 10 and 12 positions. With less than 16 positions, some of the 4-bit combinations are simply skipped. To go from 16 to 12 positions, the switch might skip 0100, 0010, 1110 and 0111, as an example.&#x20;

The main advantage of these switches is that they are absolute, so you can label the switch on your controller. In addition, they generally have a heavier detent feel to them. The disadvantage is the space they take in the matrix; 4 blocks.&#x20;

Encoders:

* Bourns PAC18R
* Grayhill 26 series
* Panasonic EVQV9
