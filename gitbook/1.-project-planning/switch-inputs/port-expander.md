# Port expander

In contrast to shift registers, a port expander will give you actual general purpose input/output pins. Just like the ones already on the microcontroller board -> they work more or less the same way. In fact, you could use a port expander to drive a chain of shift registers. Or you could wire a button matrix to it. The only supported port expander chip is PCA9555, which is fairly cheap, good quality and has good stock on JLCPCB.&#x20;

<figure><img src="../../.gitbook/assets/image (83).png" alt=""><figcaption></figcaption></figure>

While shift registers work more like a puppet controlled by the master (the microcontroller), the port expander works on its own, and can communicate with the microcontroller over a protocol called I2C. You'll need to connect it to the I2C pins of the microcontroller, and you'll need 1 pin for interrupt, more on that under [wiring.](../../2.-wiring/switch-inputs/port-expander.md)

Quick comparison between shift register and port expander:

| Feature                         | Shift register (74HC165)  | Port expander (PCA9555) |
| ------------------------------- | ------------------------- | ----------------------- |
| Input/output                    | Only input                | Input and output        |
| Inputs per chip                 | 8                         | 16                      |
| Inputs maximum                  | Unlimited (chain)         | 128 (8 x PCA9555)       |
| Pullup resistors                | Needs external pullup     | Included                |
| Components needed for 16 inputs | 18                        | 1                       |
| Space needed on PCB             | Managable amount          | Less than half of SR    |
| Processing                      | Continously               | Only when needed        |
| Performance                     | Good                      | Good                    |
| Price                           | 2 USD for two + resistors | 3 USD                   |

&#x20;

In DDC, the default configuration for the PCA9555 is 16 input pins. If you want to use any of the pins as output pins or anything else wild and saucy - contact me and we'll figure it out.

Every PCA9555 you add you'll get two rows with eight columns in the switch table. You can decide where in the switch table to put them yourself. Since it requres eight columns, you need to make your switch table at least eight columns wide.&#x20;

<figure><img src="../../.gitbook/assets/image (89).png" alt=""><figcaption></figcaption></figure>

In the example above, there is a 2 x 4 matrix on rows 1 and 2. The PCA9555 is placed on row 3, taking up two full rows with 8 columns. Row 1 representing input pins IO0 0-7 (in practice pins 1-8) and row 2 representing input pins IO1 0-7 (in practice pins 9-16) on the port expander. Lastly, row 5 has been used for some direct wired switches.&#x20;

You can add up to 8 port expanders to a single I2C line. If you have two I2C lines you can add another 8. However, 8 port expanders are 128 inputs, which is the maximum button count for a Windows controller. So rarely would you need more.&#x20;
