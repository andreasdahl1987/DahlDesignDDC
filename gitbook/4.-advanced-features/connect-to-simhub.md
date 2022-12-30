# Connect to SimHub

This step is not at all necessary for controller function.

A DDC controller can send information about switch modes, bite point, and really anything you put in the [bit fields](field-placement.md) to SimHub via the Dahl Design Properties plugin. Allthough the plugin is iRacing specific, this part of the plugin works regardless of which sim you are using.&#x20;

[Here is the list of available properties.](https://dahl-design.gitbook.io/properties/properties/ddc)

**1:** [**Download SimHub**](https://www.simhubdash.com/download-2/)****

**2:** [**Install Dahl Design Properties plugin**](https://dahl-design.gitbook.io/properties/introduction/install)****

**3: Enable controller input plugin**

<figure><img src="../.gitbook/assets/image (1) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>

#### 4: Find your controller name

<figure><img src="../.gitbook/assets/image (2).png" alt=""><figcaption></figcaption></figure>

#### 5: Type controller name in the plugin menu

Just the name of the controller, don't include the ending "\_". Also check for DDC Enabled, and also DDS and clutch if relevant.

<figure><img src="../.gitbook/assets/image (4).png" alt=""><figcaption></figcaption></figure>

## Known issues

* DDC properties aren't working/loading
  * Make sure you wrote the controller name correctly.
  *   Make sure none of the wheels axis have been calibrated by Windows. Got to USB controller settings and reset controller to default.

      <figure><img src="../.gitbook/assets/image (5).png" alt=""><figcaption></figcaption></figure>
  * Try flashing with a different board core. For instance, some boards like Pro Micro I've seen just wont be registered by Simhub. Try selecting Arduino Leonardo board when uploading the sketch
  * Make sure "SW1 Enabled" isn't checked under LED plugin settings. Unless you're actually using an SW1.&#x20;
  * Make sure you have the latest version of the plugin.
* Switch modes go crazy when changing switch more of a single switch.
  * The latest version of the joystick library gives inaccurate values for integers using the 15th and 16 bit of the joystick axis. Even when stating that the joystick axis should be 60 708, it might be 60 707 in windows. This causes the whole communication system to collapse.&#x20;
    * Make sure you're using Joystick library version 2.0.8 or older, where at least bit 15 is available.
    * Don't ever map anything to bit field 16 (field placement 16).&#x20;
  * Have a look at your switch functions, make sure you havent assigned a field placement higher than 15 anywhere.&#x20;

