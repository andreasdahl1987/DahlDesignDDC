# Direct

Direct wiring is the simplest but most pin-consuming way to wire your switches. It is a good option if you have only a few switches and enough microcontroller inputs. You won't need any diodes, pullup resistors or other integrated circuits. When using direct wiring, you can completely disregard your planned matrix. You'll bring the two together later when you start working on the code.&#x20;

For switches that has only two pins (typical pushbuttons or on/off toggles), one will go to a microcontroller input and one will go to ground. These are switches that use 1 block in your planned matrix.&#x20;

For switches that use several blocks, each pin that has a column in the planned matrix  goes to a microcontroller input, and the common pin goes to ground. As seen below with the encoders.



![image](https://user-images.githubusercontent.com/40788634/191907862-0a5fe9f2-273f-4d2e-9bc7-0d32090c1eb1.png)

In this example you can see a button matrix and two direct wired 2-bit encoders.
