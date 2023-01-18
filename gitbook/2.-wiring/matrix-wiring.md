# Matrix

Matrix wiring has the advantage of using few microcontroller inputs to gather input from many switches. For instance, you can wire up 64 buttons to 16 microcontroller inputs, as opposed to just 16 buttons with direct wiring. The disadvantage is the required diodes for every switch and more complex wiring.

### Find your pins

DDC is built around planning a matrix of switches, so naturally, when wiring the switches as a matrix, you'll just follow the the way you've planned it. Lets say your matrix consists of 4 rows and 5 columns. First thing is to determine which pins you're using. For these 4 rows and 5 columns, that's 9 pins.

![image](https://user-images.githubusercontent.com/40788634/191264509-81f46a6d-717b-4161-877f-08c584dd9ce1.png)

This is an example if how to set it up.

* Row 1 to 4: 15, 14, 16, 10
* Column 1 to 5: 3, 4, 5, 6, 7

Of course, you're free to chose whichever pin as row/column. I usually wire my switches first, and then see where the wires will end up when they reach the microcontroller.

### Wiring the switches

A button matrix can look complex, an even worse if you're including encoders, encoders with pushbuttons and hat-switches/7-way switches. However, in practice it is quite simple. It is the same connection repeated for each block in the matrix:

![image](https://user-images.githubusercontent.com/40788634/191262015-658fc547-e9ee-4291-8eb0-72de5b9070e2.png)

A wire goes from a column pin on the microcontroller --> to a diode --> to a switch --> back to a row pin on the microcontroller.

* A switch with the matrix adress (1,2), or Row 1 Column 2, will be wired like this:

![image](https://user-images.githubusercontent.com/40788634/191910415-400648b6-02d5-4a40-98cd-4a8acdd2fb4b.png)

* Adding switch with matrix adress (2,2) or Row 2 Column 2:

![image](https://user-images.githubusercontent.com/40788634/191911791-0806dfa1-8cc0-46e5-9e9a-5c34201ae337.png)

* Adding switch with matrix adress (2,3) or Row 2 Column 1:

![image](https://user-images.githubusercontent.com/40788634/191918120-692afc6a-0ccd-4189-ba54-98712ffb21ce.png)

#### Switch pins

* For any switch that only uses a single block in the matrix; a pushbutton, toggle switch, etc., which pin on the switch is connected to the row/column does not matter. Just pick something. Of course, if your button has more than one throw (for instance SPDT switch), make sure you pick pins that are actually connected when you press the button.
* For all switches that uses more than 1 block in the matrix (with few exceptions) the general idea is that the switch has many paths to a common end point. For instance, with a 2-bit encoder, pins often labled as A, B and C (common). Where A and B are the two individual paths to C, which both can be open or closed, independently. As below.

![image](https://user-images.githubusercontent.com/40788634/191294795-0d567703-327c-414a-9746-c89d22e52d15.png)

As a general rule, all COMMON pins should go to a row. So pin A and B are on the column side (with a diode between column pin and the switch pins) and C goes to a row pin. This is why an encoder in the matrix setup take up two blocks (two columns) on the same row. And since no switches have more than one common (except encoders with pushbutton and 7-way switches, but these can also be regarded as two seperate switches), no switches can have more than one pin that goes to a row.

![image](https://user-images.githubusercontent.com/40788634/191298094-966a7953-8e6e-41c3-9f93-18c4c783eafe.png)

In the case of a 4-bit encoder, it is much the same, just that there now are 4 individual paths to the common pin. Here, pins 1-4 should each have their column pin, and pin 5 to a row. This kind of encoder takes up 4 blocks on the same row in the matrix setup.

![image](https://user-images.githubusercontent.com/40788634/191768504-7ad86032-3f37-48e6-9b90-a47784a84b07.png)

Above is the button matrix used in the Dahl Design SW1 steering wheel. It includes pushbuttons, 2-way toggles, 3-way toggles, 2-bit encoders and 7-way switches. Note that the two commons on the 7-way switches (for the buttons and encoder) go to same row. They dont have to, but it makes the wiring easier. That also means all the blocks from this switch must be on that row, requiring the matrix to be 7 columns wide.

![image](https://user-images.githubusercontent.com/40788634/191919809-fac6f981-5273-4585-8ed8-f02e005c351f.png)

Here is an alternative way to wire the same 7-way switch, with the commons from the hat switch and the encoder going to different rows. The hat switch uses columns 1-5 on row 2, the encoder uses columns 1-2 on row 3. Essentially splitting the switch into two individual switches. This is better for a smaller matrix, in this case the project uses a 6 row 5 column matrix. The same wiring is possible for an encoder with a pushbutton.
