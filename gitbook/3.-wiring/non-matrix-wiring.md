# Non-matrix wiring

In case of non-matrix switches, these go directly to the microcontroller. The switch pins that would have gone to a column if in matrix, will go to a microcontroller pin, and no sharing pins with other switches. The pin that would have gone to a row will go to ground. No diodes are needed.

![image](https://user-images.githubusercontent.com/40788634/191907862-0a5fe9f2-273f-4d2e-9bc7-0d32090c1eb1.png)

In this example you can see a button matrix and two non-matrix 2-bit encoders.
