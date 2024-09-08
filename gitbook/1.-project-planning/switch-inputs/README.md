# Switch inputs

When you have an idea of which and how many switches you're going to use, you'll be best of making a plan for your DDC firmware. All the switches should be organized in a **switch talbe.** No matter how you wire your switches, they will end up in a table in the firmware. And when giving functions and features to your switches, you're be referring to them by their table address; a row and a column number. Or in some cases several column numbers. To make a pushbutton of the switch on row 2, column 3, the code you'll write is`pushButton(2,3);`. More on code later.

Each slot in the table has a package of memory that will be exclusive to the switch using this slot. This memory is used for debouncing algorithms, switch modes and much more. This is why every switch needs to find its place in the table.

Think of it as placing the switches in an Excel sheet. The switch in <mark style="background-color:green;">green</mark> with number "14" is on row 3, column 3. When refering to the switches in the code, you'll be using these adresses. Don't mind the numbers in these cells, more on that later.&#x20;

<figure><img src="../../.gitbook/assets/image (3) (1) (1) (1) (1) (1) (1).png" alt=""><figcaption><p>A matrix, or table if you will, of switches</p></figcaption></figure>

Some exeptions; switches/sensors/potentiometers that require an analog inputs are not part of the table. They are part of the analog input system, built on using [analog channels.](../analog-inputs/)
