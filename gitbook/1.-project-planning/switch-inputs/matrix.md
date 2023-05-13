# Switch table

This section will explain how to plan the switch table. No matter how you chose to wire your switches to the microcontroller, they have to end up in the table in the firmware. You'll have to plan you controllers switches accordingly, and there are some rules to follow. For matrix wiring, the wiring will naturally match the firmware table. For switches that are wired [directly](non-matrix-switches.md) to the microcontroller, or through [shift registers](shift-register.md) or [port expanders](port-expander.md), there are some additional things to pay attention to.&#x20;

### Planning the switch table

I use a spreadsheet to plan the switch table for my projects, with the switches represented as **blocks**. I will refer to **blocks** for the remainder of this guide. I also give blocks different colors according to what I'm going to use the switch for; neutral button, bite point button, modifier button, etc. This is not need, it is just to get an overview.

The numbers in the cells are [button numbers](../../3.-coding/essentials/10\_matrixandanalog.ino.md#button-numbers), more on this later.&#x20;

![image](https://user-images.githubusercontent.com/40788634/191767001-6133685e-d7a5-4eef-9de6-aea218732961.png)

This table is from an early edition of the Dahl Design SW1 steering wheel, which uses DDC to build its firmware.

![image](https://user-images.githubusercontent.com/40788634/191212291-7e49c0ff-8039-435d-b81b-752512a5e36d.png)

Every block is an **adress** in the table. Most switches just need 1 block. As an example, the brown block on Row 1, Column 5 represents a standard simple pushbutton used to set the bite point. Its adress is R1C5, or (1,5) in the code. _If you dive deeper into the algorithms, its adress in the table is actually \[0]\[4], since the tables in the code starts with 0, and not 1._ Along with this adress, the sketch gives this button a whole bunch of variables connected to this adress; used for debouncing, determining how the switch works, storing information, duration of trigger pulses and much more.

#### Block demand

**1 block**

* Simple pushbutton
* On-off toggle

**2 block**

* 2-bit encoders
  * CTS 288
  * CTS 12CE/11CE
  * Bourns PEC11
  * Alps EC11
  * TT Electronics EN11
  * Alps SRBM
  * Encoder on Alps RKJXT1F42001
  * Many more..
* 3-way toggles (typically on-off-on)

**3 block**

* 2-bit encoder with pushbutton (2 + 1 blocks)

**4 block**

* 4-bit encoders
  * Grayhill Series 26
  * Bourns PAC18R
  * Panasonic EVQV9
  * Many more..
* Hat switch without center pushbutton

**5 block**

* 4-bit encoder with pushbutton
* Alps RKJXM1015004
* Any other hat switch with center pushbutton

**7 block**

* Alps RKJXT1F42001 (5 + 2 blocks)

### Pins (in case of matrix wiring)

![image](https://user-images.githubusercontent.com/40788634/191212291-7e49c0ff-8039-435d-b81b-752512a5e36d.png)

**Each row and column in the matrix needs 1 digital pin from your microcontroller.** The example above has 7 rows and 7 columns, and uses a total of 14 pins.

![image](https://user-images.githubusercontent.com/40788634/191214679-a6bf93db-3b8a-4dcb-85d8-b50004addcc5.png)

In this example, the project has a bit fewer switches, and can do fine with a smaller matrix. 5 rows and 6 columns for a total of 11 pins needed.

### &#x20;Rules

In order to make the algorithms more memory- and processing friendly, they will make some assumptions regarding switch placement in the table. This means you have to follow some rules:

* As a general rule, a switch needs all its blocks on the same row.
* Rotary encoders, 2-bit (2 blocks) or 4-bit (4 blocks) will require you to put all the switch blocks next to eachother. As in this example, 2-bit encoders marked in red.

![image](https://user-images.githubusercontent.com/40788634/191216527-024504bc-e566-44d3-bea8-28d1dfe44cff.png)

* The rotary encoder on "funky" switches can have their blocks seperated, but still needs to be on the same row. Encoder blocks on row 2 are seperated, on row 5 next to eachother. Both are fine.

![image](https://user-images.githubusercontent.com/40788634/191217205-40ebc624-d074-4ecf-a8e6-daeaa2efaa36.png)

* For 7-way switches, the position+push buttons (light blue and purple) all need to be on the same row, reserving 5 blocks. They **don't** need to be next to eachother or in any order. The encoder (orange) can be placed on a different row, and regarded as an individual switch. This means that if you include a 7-way switch into your project, you'll need at least 5 columns.

![image](https://user-images.githubusercontent.com/40788634/191218912-43284af8-672b-4cc9-aefe-2ec046dae25d.png)

* Encoders with pushbuttons can be regarded as two individual switches; an encoder and a simple pushbutton. This means the two can be placed on different rows. If you wired one of the pushbutton pins to the encoder common, they must be on the same row.
* Unused spaces in the table is perfectly fine, but try to plan it so that you can use the smallest matrix possible - as these slots will still be processed and will take up memory.

### Assigning button numbers

* Button numbers go from 0 to 127. **Button 0 in DDC is regarded as button 1 by Windows**, returned as B0 by SimHub. Button 23 in DDC is button 24 in Windows, etc.
* The following special buttons will not need a button number:
  * Hybrid button
  * DDButton
  * ThrottleHold button
  * Handbrake button
  * Preset next/previous
  * Bite pot locker
* Any unused button/open slot in the table can safely be assigned 0.
* Buttons and toggles that uses a single block simply uses the number assigned to that block.
* Encoders:
  * An incremental encoder uses two button numbers (one for CW rotation, one for CCW). You just need to write the first of these numbers in the first encoder block in the matrix (leftmost).

![image](https://user-images.githubusercontent.com/40788634/191233513-278b9395-3fc9-4564-b6a8-f66b5f787926.png)

This 2-bit encoder will use button numbers 23 and 24, and the 4-bit encoder use button numbers 10 and 11.

* If you use a switch function that gives the encoder a multi-position mode, the starting number of the multi position mode goes in the first block. If this function also includes an incremental mode, the starting number of the incremental mode goes into the second block.

![image](https://user-images.githubusercontent.com/40788634/191234054-4e2c514d-a6e6-4b8d-a2be-9f9d150e7b80.png)

This 2-bit encoder has been used in a function that has a 8-position mode and an incremental mode. It will then use button numbers 23-30 in the 8-position mode and button numbers 31 and 32 in the incremental mode. If the 4-bit encoder is set up the same way, it will use button numbers 10-17 for the 8-position mode and button numbers 10 and 11 in the incremental mode.

* For funky switch encoders, the same principle applies, just that the two blocks arent necessarily next to eachother.
* Any encoder blocks that dont need a number in them must be assigned a 0.
