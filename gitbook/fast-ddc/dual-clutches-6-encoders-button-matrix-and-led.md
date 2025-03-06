# Dual clutches, 6 encoders, button matrix and LED

<figure><img src="../.gitbook/assets/image (118).png" alt=""><figcaption></figcaption></figure>

<figure><img src="../.gitbook/assets/image (119).png" alt=""><figcaption></figcaption></figure>

You can wire buttons without using diodes, but you'll likely get ghosting issues when pressing multiple buttons at the same time. Diodes with the anode facing column pin and cathode facing row pin.&#x20;

<figure><img src="../.gitbook/assets/image (115).png" alt="" width="375"><figcaption></figcaption></figure>

{% file src="../.gitbook/assets/B30_E6Quarter_Clutch_LED30 (1).uf2" %}

{% file src="../.gitbook/assets/B30_E6Half_Clutch_LED30 (1).uf2" %}

{% file src="../.gitbook/assets/B30_E6Full_Clutch_LED30 (1).uf2" %}

* Hold buttons on row1 column1 and row1 column2 together for 5 seconds to restart the controller and boot as storage device.&#x20;
* LEDs are running on 3.3V data in this diagram, which works up to a certain LED count. Limit is set to 30 because more is unlikely to work. For higher LED counts use a level shifter and set up a full DDC firmware.&#x20;
* Press button on row1 column4  for 4 seconds to initiate calibration mode. Release button, then press both clutches all the way in and release. Then press button 3 again once. Calibration completed.&#x20;
* Hold button on row1 column3 to adjust the bite point for your dual clutch launch. Encoder 1 will do increments of 10%, encoder 2 for 1% and encoder 3 for 0.1% increments.
* Hold button on row1 column3 to change bite point preset, storing 12 different bite points.&#x20;
* Hold button 4 and pump one of the clutches to cycle through clutch modes.&#x20;
* Master clutch is the paddle that will give 100% clutch input when pressed completely in static mode. Slave paddle will stop at bite point. Master paddle will also work as throttle in brake/throttle mode.&#x20;
