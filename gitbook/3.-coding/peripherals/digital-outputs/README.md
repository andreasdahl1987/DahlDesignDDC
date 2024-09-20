# Digital outputs

When working with digital outputs, DDC has a system build on _**output hubs.**_ This is a software system, where each hub has 16 slots numbered 1 to 16, each controlling and storing information on _one_ physical output pin. A PCA9555 port expander itself has 16 pins, so it fills a whole hub. Making several hubs, they will be numbered 1, 2, etc.&#x20;

If you're using pins directly from the microcontroller as output pins, this will automatically generate a hub which is the **last in line** of all the hubs in your project. So if you haven't set up any other hub, this is hub #1. If you've set up 3 port expanders as hubs, your output pins from the microcontroller is on hub #4. Since the hubs are limited to 16 slots, you **can only set up 16 pins** directly from the microcontroller as output pins. This should be enough for most projects, and if you need more I suggest using port expanders.

The hub will be controlled by the firmware, and you can set up functions to write its outputs. You can also hook the hub up to **SimHub**, including it in a virtual RGB LED strip, so that you can use the RGB LED editor in SimHub to control the hub.&#x20;

The hub will constantly check if its output slots have had any value change, and if it has it will refresh the value of the actualy physical pins it is associated with (writing to the I/O registers of the microcontroller and the port expander).&#x20;

In many ways this is similar to the [switch table](../../../1.-project-planning/switch-inputs/matrix.md). You explain your wiring to the firmware, which in return gives you a framework to control and manipulate the devices you've wired.&#x20;

<figure><img src="../../../.gitbook/assets/image (3) (1) (1).png" alt=""><figcaption></figcaption></figure>
