# 3. Coding

Now that the electronics are sorted, time to build the firmware. You might already have a project where the wiring is set and you're looking to change your firmware to DDC. Then this is where you start.

Here are the things you need:

## Applications

* [Arduino IDE](https://www.arduino.cc/en/software) (Legacy or IDE2)
* Since the Windows USB device interface just shows the first 32 buttons, I suggest using [Pointy's Joystick Tester](http://www.planetpointy.co.uk/joystick-test-application/) for debugging your controller (naturally not a requirement).

## Libraries

* You don't have to search GitHub for libraries. All libraries needed are included in the repository. They will however have to be moved over to your Arduino library folder. Usually found under documents/Arduino/libraries.&#x20;

<figure><img src="../.gitbook/assets/image (24) (2).png" alt=""><figcaption></figcaption></figure>

## The sketch

Download the repository. The folder called `DahlDesignDDC` holds the "sketch". The piece of code that eventually will become your custom firmware. The firmware is organized in many .ino files. The way this works is that Arduino IDE will read these files as a single, big file, starting with the main file `DahlDesignDDC.ino`, and then reading the rest in alphabetical order. Hence the numbering of all the other .ino files. They are simply split into many files to get a better overview.&#x20;

To open the sketch, open the `DahlDesignDDC.ino` file, Arduino IDE will automatically include all the other files. All the files are now available as **tabs** in Arduino IDE.

<figure><img src="../.gitbook/assets/image (6) (1) (1) (1) (1).png" alt=""><figcaption><p>Note the tabs at the top</p></figcaption></figure>

&#x20;Only some of these tabs are relevant to building your controller firmware, in fact only 4 of them are needed to get your firmware going, and a few more are optional.&#x20;

##

## Board cores

Before uploading any code to your controller, the IDE needs to know what board you're using. A board core is a guide for the IDE to talk to the controller. Many cores are already installed in the IDE. You chose your board under tools-->boards.

* For Atmel 32U4 boards, the Arduino Leonardo board core will do fine. Sparkfun Pro Micro is a very popular board, they have their own cores which can be installed. [Guide here](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide). As mentioned, also these boards work fine with the Arduino Leonardo core.&#x20;
* For SAMD21/51 boards, you actually need to roll back the core to an earlier version in order for it to work as a joystick. Version 1.6.19 or earlier is needed. I'm using 1.6.19. This is done in the boards manager.
*

    <figure><img src="../.gitbook/assets/image (3) (1) (1) (1) (1) (1) (1).png" alt=""><figcaption></figcaption></figure>
* For RP2040, the [Earle Philhower board cores](https://github.com/earlephilhower/arduino-pico) are used. Installation guide on that GitHub page. Also set the USB stack to Adafruit TinyUSB.

<figure><img src="../.gitbook/assets/image (19) (2).png" alt=""><figcaption></figcaption></figure>
