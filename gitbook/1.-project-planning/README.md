# 1. Project planning

When you have an idea of which and how many switches you're going to use, you'll be best of making a plan for your DDC firmware. All the switches should be organized in a **matrix,** or a table if you will. Because even if you're not wiring the switches in a matrix, your swiches will be organized in a matrix in the firmware. Each switch will have a row and column number, or in some cases several column numbers. Each slot in the matrix has a package of memory that will be exclusive to the switch using this slot. This memory is used for debouncing algorithms, switch modes and much more. The adress to a matrix slot, a row and a column number, is also what you'll be using to set up this switch in the firmware. To make a pushbutton of the switch on row 2, column 3, the code you'll write is`pushButton(2,3);.` More on code later, but the point is that you'll have to get used to this matrix idea, even if you're using direct wiring or shift registers.&#x20;

This also means that the [matrix documentation](matrix.md) is relevant, no matter the wiring you chose.&#x20;

Think of it as placing the switches in an Excel sheet. The switch in <mark style="background-color:green;">green</mark> with number "14" is on row 3, column 3. When refering to the switches in the code, you'll be using these adresses. Don't mind the numbers in these cells, more on that later.&#x20;

<figure><img src="../.gitbook/assets/image (3) (1).png" alt=""><figcaption><p>A matrix, or table if you will, of switches</p></figcaption></figure>

