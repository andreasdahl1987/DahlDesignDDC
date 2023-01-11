# Naming the controller

If your controller is based on a Atmel 32U4 chip, you can name our controller using this guide. If you're adding LEDs to the controller, this is a requirement.&#x20;

You do this by making a custom `boards.txt` file, which Arduino IDE will use to flash your controller instead of the Arduino Leonardo / Pro Micro board core.&#x20;

Here is how you do it:

* Move the folder "hardware" to your Arduino folder in "My Documents".&#x20;

<figure><img src="../.gitbook/assets/image (1).png" alt=""><figcaption></figcaption></figure>

* In this folder, the folder called __ named "My Controller" or similar, can be renamed to whatever you like.&#x20;
* Find the `boards.txt` file:

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

* Here as well, anything called "MyController" or similar can be renamed to whatever you want your controller to be named
* Two key parameters here is the vendor ID (VID) and the product ID (PID):

```
MyController.build.vid=0x8123
MyController.build.pid=0x8234
```

These are USB product indentifiers, where Windows already has a register to look at. If a product, such as a USB keyboard for instance, is registered with a VID/PID, Windows already knows its name when you plug it in. If your computer has never seen this VID/PID, it will take the name you have given it. If you then change the name under `MyController.build.usb_product="My Controller"` and dont change the VID/PID, your computer will still remember it as the name you first gave it.&#x20;

The number written here by default is a random number. You should edit this and keep track of the numbers you use if you have several controllers.&#x20;

* Now, when you open Arduino IDE, your custom board should show up in the boards list:

<figure><img src="../.gitbook/assets/image (9).png" alt=""><figcaption><p>I've made a custom board file for my SW1 wheel</p></figcaption></figure>

Use this board when flashing your controller.

#### Disclaimer

VID/PIDs cost a lot of money. Using a random VID/PID for your private projects is fine, but if you're selling a product, you're not entirely lawful if you're using random IDs. What the risk is, I'm not sure, but I can't imagine there is a USB police sniffing out sim gear shops.&#x20;

