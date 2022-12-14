# Non-matrix switches

You can also include switches that are not wired in a matrix. The requirement here is that each switch has its own pin on the microcontroller. Or in the case of a 2-bit encoder -> two pins. For a funky switch -> 7 pins, you get the idea.

_<mark style="color:red;">Shift registers are currently not supported, but definitely will be in the future.</mark>_

### Planning with non-matrix switches

While these switches won't be wired in a matrix, they still need a matrix adress in order to work. This means you **plan these switches as if they are part of the matrix.** Follow the guide and rules for building a matrix above.

There are also some extra rules to follow:

* In case of a hybrid project, where some switches are wired in a matrix, and some switches aren't (typically pushbuttons in matrix and encoders directly to the microcontroller), don't mix non-matrix switches and real matrix switches on the same row. The example below has three non-matrix 2-bit encoders (red) and a button matrix.

![INCORRECT](https://user-images.githubusercontent.com/40788634/191729875-a353279d-7340-45fb-a222-6958eaf2f20b.png)

![CORRECT](https://user-images.githubusercontent.com/40788634/191730157-69d9b169-6e9b-4105-8dec-a67582de91f0.png)

The rows with non-matrix switches aren't real matrix wired rows, and there is no microcontroller pin associated with them. Putting real matrix switches on these rows won't work, as they won't be registered.

* In the case of a project with no real button matrix at all, you might as well just make a single row with loads of columns, as that will give you the best fit without any open slots. However, that might not give you a very good overview.

![image](https://user-images.githubusercontent.com/40788634/191734742-cfe7cc50-ccb9-4b57-901b-5e2c24d5b56a.png)

The example above has three 2-bit encoders and 10 pushbuttons, none of them are wired in a matrix. It can be organized in a 1 x 16 or a 4 x 4 matrix, or anything in between. It doesn't matter much, as no actual pins are associated with this matrix.

#### Pins

Non-matrix switches require as many pins as blocks it uses in the matrix planning. In the example just above, 16 pins are needed. In a hybrid solution, you need the pins required for the real part of the matrix + a pin for each block of non-matrix switches.

![image](https://user-images.githubusercontent.com/40788634/191730157-69d9b169-6e9b-4105-8dec-a67582de91f0.png)

In this example, you need 2 + 2 + 2 pins for non-matrix switches, and since row 1 and row 2 are "fake" rows, you only need pins for row 3-5 and columns 1 - 4. A total of 13 pins.

### Coding with non-matrix switches

A little bit of extra attention to the code is required, more on that [here](https://github.com/andreasdahl1987/DahlDesignDDC/wiki/4.-Coding#pins) and [here](https://github.com/andreasdahl1987/DahlDesignDDC/wiki/4.-Coding#non-matrix-switches).
