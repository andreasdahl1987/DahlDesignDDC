# LEDs

<figure><img src="../.gitbook/assets/image (18).png" alt=""><figcaption></figcaption></figure>

DDC supports full RGB LED integration with SimHub for Atmel 32U4 boards. You can use the RGB editor in SimHub to set up you LEDs and have them react to game telemetry.&#x20;

DDC supports up to 4 chains of LEDs. Normally, a single chain would suffice, but in some cases it can be practical to split them up; for instance for having an option to expand with more LEDs later, or you're using LED strips and chaining them leads to wiring obstacles.&#x20;

The four chains will be summized before reaching the LED editor in SimHub. So If chain 1 has 11 LEDs, the first LED in chain two is LED number 12, etc.

Each chain needs a single digital pin, VCC and GND. So you'll likely get away with spending just 1 digital pin on your LEDs.&#x20;
