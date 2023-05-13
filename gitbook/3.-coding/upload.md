# Upload

Now that your switches are set up, your controller is ready to go. Compile and upload the sketch to your microcontroller, if everything is planned and written correctly it should now work.

Select the correct board and port, and remember to set USB stack to Adafruit\_Tiny\_USB for RP2040 based board. Also for RP2040 boards, it might boot up in USB storage device mode - in that case it wont be accessible at a port number, but as a U2F device - they are also found the same place you select port number.&#x20;

Since the Windows USB device interface just shows the first 32 buttons, I suggest using [Pointy's Joystick Tester](http://www.planetpointy.co.uk/joystick-test-application/) for debugging your controller. Also keep in mind that button numbers in DDC are numbered -1 from Windows. So button 15 in DDC is button 16 in Windows, etc.
