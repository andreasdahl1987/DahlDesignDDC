# Processing and memory

A big project, using a big switch table, many analog inputs, topping out at 128 buttons, adding peripherals like LEDs, external ADCs, EEPROM and more...it will become heavy for the processor to handle. I've made an effort in making all peripheral support as light as possible, usually making my own algorithms instead of using libraries - in order to save processing and memory usage. The Atmel 32U4 is particulary vulnerable, as it is both slow and memory light compared to modern microcontroller ICs. For the RP2040, memory is never an issue, neither should processing be - however it is wise to be aware of the limitations, and how your project looks with regards to these limits.

### **Memory**

Types of memory:

* Storage memory: The largest, doesnt change after upload. Your program is stored here.
* Dynamic memory: Smaller than storage memory. Fast memory can be written to or read when your program is running. Filled with informatiom from storage memory when the controller turns on, cleared when controller turns off.&#x20;
* EEPROM: Something in between; relatively quick memory that you can read/write to while program is running, but doesnt get cleared on power down. Typically endures a lot more read/write cycles than regular storage memory.&#x20;

DDC doesnt really use all that much dynamic memory, but it uses quite a bit of storage memory. That being said, I've written the sketch in a way that you'll never use memory for anything that your project isnt using. Allthough the sketch is massive, with several files - when it is all compiled, it will only use what is needed. When you upload or just compile the sketch, you'll get a rapport on memory usage:

<figure><img src="../.gitbook/assets/image (72).png" alt=""><figcaption></figcaption></figure>

* It is safe to use up to 100% of storage memory.
* It is not save to use 100% of dynamic memory. Ideally keep this below 80%. I have not yet been able to make a sketch using 80% of dynamic memory. For my own experience, moving towards 90% dynamic memory will start causing trouble; crashes and unprediced behaviour.

### Processing

When talking about processing of a joystick controller code, I mean how quickly it can read through its program. How many times per second it can scan all the buttons, do all its tasks, update the switch states and then be ready to start over again.

The practical impact of slow/fast processing is its responsiveness and how well the buttons work.&#x20;

* If your microcontroller can only update the button states 5 times per second, you'll experience a massive lag.&#x20;
* Some switches (encoders in particular) work in a way that you might only have a few milliseconds to catch it turning/switching. If your code spends 200 milliseconds updating all button states, it will only very rarely be able to "see" the switch turning.&#x20;

It is hard to tell exactly what refresh rate you'll need, but typically encoders that require the PEC11() or funkyRotary() functions will need a pretty fast refresh rate. At least 150 Hz. Some encoders, like the Elma E33, will need around 300 Hz to work optimally. So it all depends on your project. If you have only pushbuttons, you'd do fine with 50 Hz - lag being the limiting factor. However, a setup with only pushbuttons will likely run at 800-900 Hz just because it is so light on the processor.&#x20;

You can check the refresh rate by adding `refreshRate()` to 30\_switches.ino and read it out on the serial monitor after uploading.&#x20;

