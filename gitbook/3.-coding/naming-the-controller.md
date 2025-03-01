# Naming the controller

Naming the controller, or more importantly assigning a VID and PID number to it, is required for SimHub LED control to work. It is also nice to see your computer recognize your controller as _"Ferrari 488 EVO"_ and not _"Arduino Pro Micro"_.&#x20;

Currently possible for:

* ATMEGA32U4
* RP2040

#### VID/PID

Vendor ID (VID) and Product ID (PID) are USB product indentifiers, where Windows already has a register to look at. If a product, such as a USB keyboard for instance, is registered with a VID/PID, Windows already knows its name when you plug it in. If your computer has never seen this VID/PID, it will take the name you have given it in the firmware. If you then change the name and don't change the VID/PID, your computer will still remember it as the name you first gave it.&#x20;

VID/PIDs cost a lot of money. Using a random VID/PID for your private projects is fine, but if you're selling a product, you're not entirely lawful if you're using random IDs. What the risk is, I'm not sure, but I can't imagine there is a USB police sniffing out sim gear shops.&#x20;

Both VID and PID are 16-bit numbers. Commonly typed as a 4-digit hexadecimal number.&#x20;

DDC has two VID/PID's, one for the 32U4 and one for the RP2040. You're free to use the DDC VID/PIDs for your personal projects:

* ATMEGA 32U4
  * VID: 0x35f9
  * PID: 0xDDC
* RP2040
  * VID: 0x2E8A
  * PID: 0x1053

SimHub uses the VID/PID to grab controllers for custom LED protocols, which is why knowing the VID/PID you give your controller is essential for LED setups. Next we'll look at how to do this for ATMEGA 32U4 boards and RP2040 boards.

### ATMEGA 32U4

The approach is using a custom `boards.txt` file, which Arduino IDE will use to flash your controller instead of the Arduino Leonardo / Pro Micro board core.&#x20;

The DDC folder has these files, you'll have to move them to the right place:

* Move the folder "hardware" to your Arduino folder in "My Documents".&#x20;

<figure><img src="../.gitbook/assets/image (1) (5) (1).png" alt=""><figcaption></figcaption></figure>

* It includes two board files, MyController and DDC.&#x20;

If you fire up Arduino IDE, you'll see that these are now available as board cores.

<figure><img src="../.gitbook/assets/image (1) (1) (2).png" alt=""><figcaption></figcaption></figure>

You can either use the DDC core, which will give you the DDC VID/PID straight away, and naming your controller "Dahl Design Controller". Or you can customize your own to give the controller any name and PIV/VID you want. In that case, lets have a look at the `boards.txt` file in the MyController folder:

```
MyController.name=My Controller
        
MyController.upload.tool=arduino:avrdude
MyController.upload.protocol=avr109
MyController.upload.maximum_size=28672
MyController.upload.maximum_data_size=2560
MyController.upload.speed=57600
MyController.upload.disable_flushing=true
MyController.upload.use_1200bps_touch=true
MyController.upload.wait_for_upload_port=true
MyController.bootloader.tool=arduino:avrdude
MyController.bootloader.low_fuses=0xff
MyController.bootloader.high_fuses=0xd8
MyController.bootloader.extended_fuses=0xcb
MyController.bootloader.file=caterina/Caterina-Leonardo.hex
MyController.bootloader.unlock_bits=0x3F
MyController.bootloader.lock_bits=0x2F     
MyController.build.mcu=atmega32u4
MyController.build.f_cpu=16000000L

MyController.build.vid=0x8123
MyController.build.pid=0x8234
MyController.build.usb_product="My Controller"

MyController.build.usb_manufacturer="Author"
MyController.build.board=AVR_LEONARDO
MyController.build.core=arduino:arduino
MyController.build.variant=arduino:leonardo
MyController.build.extra_flags={build.usb_flags}
```

* Anything called "MyController" or similar can be renamed to whatever you want your controller to be named. The actual name that your computer will display is set here:

```
MyController.build.usb_product="My Controller"
```

* VID and PID:

```
MyController.build.vid=0x8123
MyController.build.pid=0x8234
```



### RP2040

Setting up name and VID/PID for RP2040 is quite simple. Go to `04_USB.ino`:

```
//This only relevant for RP2040 LED support

#define VID_PI 0x2E8A
#define PID_PI 0x1053
#define MAKER "Andreas Dahl"
#define CONTROLLER_NAME "Dahl Design Controller"
```

This is fairly self explainatory. Default is the DDC VID/PID. If you don't have your own, you can use this.&#x20;



