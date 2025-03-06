---
icon: person-running-fast
---

# Fast DDC

The RP2040 has the handy ability to boot as a USB storage device. You can then simply drag-drop a firmware file into the drive, and it will automatically restart with the new firmware running.&#x20;

There are a few ways to boot as storage device:

* As long as it has no program running it will default to booting as storage device. For instance when coming straight from factory.
* Holding the BOOTSEL button when powering up.&#x20;
* Using [firmwareUploadMode()](../switch-library/utility.md#firmwareuploadmode) function, though this requires you to upload a firmware with this function first.&#x20;

Community legend ZebbeBa has made several ready-to-use firmware files to drop onto your RP2040 boards. No coding required. Just chose the firmware that suits your needs and follow the wiring diagrams.

Naturally, these ready-to-use setups are generalized and aren't feature-packed. But they will do for most projects, and can help you get familiar with using DDC.  &#x20;

For firmwares using encoders there are different options for different types of encoders. You could try them all and see which one works the best.&#x20;
