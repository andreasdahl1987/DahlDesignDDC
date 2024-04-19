# Funky switch

<figure><img src="../../.gitbook/assets/image (1) (1) (4).png" alt=""><figcaption></figcaption></figure>

Alps RKJXT1F42001, or just "funky switch". It has an encoder, covered under [funkyRotary](../encoders/funkyrotary.md), 4 directional button presses and 1 center pushbutton.

<figure><img src="../../.gitbook/assets/image (8) (2).png" alt=""><figcaption></figcaption></figure>

As you can see from the schematic above, no directional input (A,B,C,D) will find its way to common pin unless pushbutton also i pressed. This is how this switch works. The pushbutton is pressed together with every directional input. It serves as a pushbutton, but is also designed to prevent bouncing, by only closing the circuit to common when the switch is properly in place. This gives us a problem to solve however, since you can't tell if the center push button is pressed alone by only reading the value from that button. We'll need an algorithm that avoids producing a button press if the pushbutton is pressed together with a directional button press. That is why funky switches have their own pushbutton functions.&#x20;

There are different algorithms for the center push button and the directional buttons, so they are listed seperately.&#x20;

When setting up a funky switch in 30\_Switches.ino, you should list the directinonal functions first, and the center push button function last:

<figure><img src="../../.gitbook/assets/image (11) (1) (1).png" alt=""><figcaption><p><mark style="color:green;"><strong>Correct</strong></mark></p></figcaption></figure>

<figure><img src="../../.gitbook/assets/image (7) (1) (2) (1).png" alt=""><figcaption><p><mark style="color:red;"><strong>Incorrect</strong></mark></p></figcaption></figure>
