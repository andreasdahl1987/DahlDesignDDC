# Shift register

The advantage of using shift registers is that you can use a silly amount of switches with only a few input pins on the microcontroller. DDC supports 8-bit parallel in/serial out shift registers, typically 74HC165/74HC166 or similar. These take 8 switch inputs each, and they can be cascaded, or "daisy chained" together. DDC can handle up to 4 chains, each chain having as many shift register chips as you want. Each chain needs 3 microcontroller pins, and a single chain can give you hundreds of inputs, far more efficient than matrix wiring. The wiring is also a lot more structured. Performance-wise the matrix wired switches will be read a little faster than the shift register wired switches, but not a difference that matters at all.&#x20;

The downside of using shift registers is the extra hardware required, and that a PCB in some shape or form is a must.&#x20;

<figure><img src="../../.gitbook/assets/image (29) (1).png" alt=""><figcaption><p>74HC166N</p></figcaption></figure>

### Shifts in the matrix

As with [direct wired](non-matrix-switches.md) switches, your switches in shift registers also needs to be in the switch table. So if you haven't already, read [this part. ](matrix.md)

DDC will dictate how SRs fit in the table, so it is more a matter of moving all the switches that aren't in the shift registers out of the way.&#x20;

* Adding shift registers to the project will automatically force column count to 8. You can add more columns, but you can't have less.&#x20;
* Shift registers will always start at column 1, where columns 1-8 represents inputs 1-8 on the shift register.
* Shift registers will always start at row 1, and use as many rows as there are shift register ICs in your project.&#x20;
  *   If you have 1 chain of 4, that will be row 1-4. Row 1 being the first in the chain - the one that is wired to the microcontroller.&#x20;

      <figure><img src="../../.gitbook/assets/image (13) (1) (1).png" alt=""><figcaption></figcaption></figure>
  *   If you have 1 chain of 3, 1 chain of 2 and 1 chain of 4:

      * Shift register chain #1 -> row 1-3
      * Shift register chain #2 -> row 4-5
      * Shift register chain #3 -> row 6-9



      <figure><img src="../../.gitbook/assets/image (35) (1).png" alt=""><figcaption></figcaption></figure>
* In case of a mix of different types of wiring, the matrix wired switches and direct wired switches are placed below the shift registers. Direct wired switches can share columns and rows with shift registers.&#x20;

<figure><img src="../../.gitbook/assets/image (2) (4).png" alt=""><figcaption></figcaption></figure>

In the example above, the matrix wired switches are on row 6-8 and columns 5-8, note that even if the planned matrix is 8 columns wide, the switches in the wired matrix doesn't have to be. You can still shape the matrix to use the least amount of pins. The open slots in the planned matrix are filled with 4 direct wired switches (red).&#x20;

In theory, the direct wired switches could be placed in the unused matrix adresses for the shift registers (for instance row 5, columns 3 - 6), but it would just look messy and wont save you any processing power or memory.&#x20;

### Pins

Each chain of SRs will need three pins digital pins from the microcontroller. One for DATA, one for LATCH and one for CLOCK. More on this in the [wiring](../../2.-wiring/switch-inputs/shift-registers.md) and [coding](../../3.-coding/peripherals/shift-register.md) chapters. Since you can make a chain as long as you want, three pins would be all you need. If you want to split up into several chains, only the DATA pin needs to be unique to each chain. LATCH and CLOCK pin can be shared by all SRs in your project. You can, however, use 3 unique pins for each chain if you want. &#x20;
