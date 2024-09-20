# SimHub control

For SimHub control, there isn't really any additional code to be written, but you have to set things up to allow SimHub to make contact with your controller.&#x20;

First you'll need to[ set up a VID/PID](../../../4.-advanced-features/naming-the-controller.md) for the controller.

When you've [uploaded](../../upload.md) the code, you can connect to SimHub:

* Go to devices and add a new device.

<figure><img src="../../../.gitbook/assets/image (15) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

* Select "Create standard device"

<figure><img src="../../../.gitbook/assets/image (6).png" alt=""><figcaption></figcaption></figure>

* Select standard LED device

<figure><img src="../../../.gitbook/assets/image (3) (1).png" alt=""><figcaption></figcaption></figure>

* Go to USB PID/VID configuration, edit the controllers VID and PID and set the correct LED count. This is all your strips combined. &#x20;

<figure><img src="../../../.gitbook/assets/image (4) (1).png" alt=""><figcaption></figcaption></figure>

* You can also rename the device and change the picture by left-clicking it.



<figure><img src="../../../.gitbook/assets/image (5) (1).png" alt=""><figcaption></figcaption></figure>

* Reboot your controller and/or SimHub for SimHub to find it, press "Edit profile" under LEDs to start working with the RGB editor.  You're all set!
