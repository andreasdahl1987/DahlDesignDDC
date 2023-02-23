# Direct

You can also include switches that are[ wired directly](../../2.-wiring/switches/non-matrix-wiring.md) to the microcontroller. The requirement here is that each switch has its own pin on the microcontroller. Or in the case of a 2-bit encoder -> two pins. For a funky switch -> 7 pins, you get the idea.

### Planning with direct wiring

These swiches will need switch table adress in order to work. This means you **plan these switches as if they are part of the table.** Follow the guide and rules for [building a switch table.](matrix.md)

There are also some extra rules to follow:

* In case of a hybrid project, where some switches are wired in a matrix, and some switches wired directly (typically pushbuttons in matrix and encoders directly to the microcontroller), the direct wired switches should be either on an isolated row or an isolated column (or on a row/column together with shift registers). An isolated row is the most processor friendly solution.

The example below has three non-matrix 2-bit encoders (red) and a button matrix.

![INCORRECT](https://user-images.githubusercontent.com/40788634/191729875-a353279d-7340-45fb-a222-6958eaf2f20b.png)

![CORRECT](https://user-images.githubusercontent.com/40788634/191730157-69d9b169-6e9b-4105-8dec-a67582de91f0.png)

<figure><img src="../../.gitbook/assets/image (22).png" alt=""><figcaption><p><mark style="color:green;"><strong>CORRECT</strong></mark></p></figcaption></figure>

The rows or columns with direct wired switches aren't real matrix wired rows, and there is no microcontroller input pin associated with them. Putting matrix wired switches on these rows won't work, as they won't be registered.

*   In the case of a project with only direct wiring, you might as well just make a single row with loads of columns, as that will give you the best fit without any open slots. However, that might not give you a very good overview.

    <figure><img src="../../.gitbook/assets/image (31) (1).png" alt=""><figcaption></figcaption></figure>

The example above has three 2-bit encoders and 10 pushbuttons, none of them are wired in a matrix. It can be organized in a 1 x 16 or a 4 x 4 table, or anything in between. It doesn't matter much, as no actual pins are associated with the rows and columns.

#### Pins

Direct wired switches require as many pins as blocks it uses in the switch table. In the example just above, 16 pins are needed. In a hybrid solution, you need the pins required for the matrix wired switches + a pin for each block of direct wired switches.

![image](https://user-images.githubusercontent.com/40788634/191730157-69d9b169-6e9b-4105-8dec-a67582de91f0.png)

In this example, you need 2 + 2 + 2 pins for direct wired switches, and since row 1 and row 2 are "fake" rows, you only need pins for row 3-5 and columns 1 - 4. A total of 13 pins.

### Coding with direct wired switches

A little bit of extra attention to the code is required, more on that[ here](../../3.-coding/essentials/30\_switches.md#direct-wiring).
