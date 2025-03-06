# Dual clutches, 4 encoders, buttons and LED

<figure><img src="../.gitbook/assets/image (111).png" alt=""><figcaption></figcaption></figure>

{% file src="../.gitbook/assets/B15_E4Quarter_Clutch_LED30.uf2" %}

{% file src="../.gitbook/assets/B15_E4Half_Clutch_LED30.uf2" %}

{% file src="../.gitbook/assets/B15_E4Full_Clutch_LED30.uf2" %}

* Hold butt[^1]on 1 and 2 together for 5 seconds to restart the controller and boot as storage device.&#x20;
* LEDs are running on 3.3V data in this diagram, which works up to a certain LED count. Limit is set to 30 because more is unlikely to work. For higher LED counts use a level shifter and set up a full DDC firmware.&#x20;
* Press button 3 for 4 seconds to initiate calibration mode. Release button, then press both clutches all the way in and release. Then press button 3 again once. Calibration completed.&#x20;
* Hold button 4 to adjust the bite point for your dual clutch launch. Encoder 1 will do increments of 10%, encoder 2 for 1% and encoder 3 for 0.1% increments.
* Hold button 4 to change bite point preset with encoder 4, storing 12 different bite points.
* Hold button 4 and pump one of the clutches to cycle through clutch modes.&#x20;
* Master clutch is the paddle that will give 100% clutch input when pressed completely in static mode. Slave paddle will stop at bite point. Master paddle will also work as throttle in brake/throttle mode.&#x20;

[^1]: 
