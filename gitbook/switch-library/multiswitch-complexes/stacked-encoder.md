# Stacked encoder

<figure><img src="../../.gitbook/assets/image (62).png" alt=""><figcaption></figcaption></figure>

The idea of the stacked encoder comes from Serkan from [Soelpec](https://soelpec.com/). The Spectra XR steering wheel runs a custom DDC firmware, and amongst the functions designed for Soelpec's wheel is the stacked encoders. The function allows you to use a pushbutton to scroll through a stack of button number layers. How many layers you can decide yourself.&#x20;

<figure><img src="../../.gitbook/assets/image (78).png" alt=""><figcaption><p>Soelpec Spectra XR uses stacked encoders for its thumb rotaries</p></figcaption></figure>

The function will also push the current stack number to the[ rotary field](../../3.-coding/advanced/field-placement.md), which in return will give you SimHub properties that you can use to make your dashboard change as you scroll through the stack. With more layers, more bits are used in the field. For instance 7 layers will use 3 bits, since 3 bits are required to get type the number 7 in binary.&#x20;

In addition, there is a LED function [encoderStack()](../../3.-coding/advanced/conditional-coding/triggers.md#encoderstack-int-row-int-column-int-layer) that you can use to[ trigger LED](../../3.-coding/peripherals/leds-code-and-connection/firmware-control/led-functions.md#triggerled)s depending on which stack you're currently in.&#x20;

For instance, lets say we have a stacked encoder with its stack button on row 3, column 1. We want LEDs 0 to 4 to change color when scrolling through the stack. Writing something like this in 36\_LEDtop.ino would work well:

```
triggerLED(0,4,encoderStack(3,1,0),0x00FF00,25,false);
triggerLED(0,4,encoderStack(3,1,1),0xFF8000,25,false);
triggerLED(0,4,encoderStack(3,1,2),0x08FFA5,25,false);
triggerLED(0,4,encoderStack(3,1,3),0x0000FF,25,false);
```

#### rotary2Stack()

{% tabs %}
{% tab title="Description" %}
Stacked encoder in the rotary2bit [category](../encoders/#rotary2bit).&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary2Stack(int stackButtonRow, int stackButtonColumn, int fieldPlacement, int layers, int row, int column, bool reverse)`

Lets say our encoder is on row 3, columns 2+3, and our stackbutton is on row 1, column 5. We want 4 layers and we push the layer number to field placement 1.&#x20;

`rotary2Stack(1, 5, 1, 4, 3, 2, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 for the first layer, then 17+18, etc. The `reverse` part of the function will switch the button numbers if set to `true`.

In this example, we're using field slot 1, and with 4 layers we'll be using 2 bits. So slot 1 and slot 2 will be used. This is reflected by the properties \[DahlDesign.DDCR1] and \[DahlDesign.DDCR2] properties, which will go 00, 01, 10 and 11 as you scroll through the 4 layers.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 x layers =  button numbers
{% endtab %}
{% endtabs %}

#### rotary4Stack()

{% tabs %}
{% tab title="Description" %}
Stacked encoder in the rotary4bit[ category](../encoders/#rotary4bit).&#x20;
{% endtab %}

{% tab title="Example" %}
`void rotary4Stack(int stackButtonRow, int stackButtonColumn, int fieldPlacement, int layers, int row, int column, bool reverse)`

Lets say our encoder is on row 3, columns 2+3, and our stackbutton is on row 1, column 5. We want 4 layers and we push the layer number to field placement 1.&#x20;

`rotary4Stack(1, 5, 1, 4, 3, 2, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 for the first layer, then 17+18, etc. The `reverse` part of the function will switch the button numbers if set to `true`.

In this example, we're using field slot 1, and with 4 layers we'll be using 2 bits. So slot 1 and slot 2 will be used. This is reflected by the properties \[DahlDesign.DDCR1] and \[DahlDesign.DDCR2] properties, which will go 00, 01, 10 and 11 as you scroll through the 4 layers.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 x layers =  button numbers
{% endtab %}
{% endtabs %}

#### PEC11Stack()

{% tabs %}
{% tab title="Description" %}
Stacked encoder in the PEC11 [category](../encoders/#pec11).&#x20;
{% endtab %}

{% tab title="Example" %}
`void PEC11Stack(int stackButtonRow, int stackButtonColumn, int fieldPlacement, int layers, int row, int col, bool reverse)`

Lets say our encoder is on row 3, columns 2+3, and our stackbutton is on row 1, column 5. We want 4 layers and we push the layer number to field placement 1.&#x20;

`PEC11Stack(1, 5, 1, 4, 3, 2, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 for the first layer, then 17+18, etc. The `reverse` part of the function will switch the button numbers if set to `true`.

In this example, we're using field slot 1, and with 4 layers we'll be using 2 bits. So slot 1 and slot 2 will be used. This is reflected by the properties \[DahlDesign.DDCR1] and \[DahlDesign.DDCR2] properties, which will go 00, 01, 10 and 11 as you scroll through the 4 layers.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 x layers =  button numbers
{% endtab %}
{% endtabs %}

#### funkyRotaryStack()

{% tabs %}
{% tab title="Description" %}
Stacked encoder in the funkyRotary [category](../encoders/#funkyrotary). This is for using a regular pushbutton to change layer, not the funky pushbutton.
{% endtab %}

{% tab title="Example" %}
`void funkyRotaryStack(int stackButtonRow, int stackButtonColumn, int fieldPlacement, int layers, int Arow, int Acol, int Bcol, bool reverse)`

Lets say our encoder is on row 3, columns 2+3, and our stackbutton is on row 1, column 5. We want 4 layers and we push the layer number to field placement 1.&#x20;

`funkyRotaryStack(1, 5, 1, 4, 3, 2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 for the first layer, then 17+18, etc. The `reverse` part of the function will switch the button numbers if set to `true`.

In this example, we're using field slot 1, and with 4 layers we'll be using 2 bits. So slot 1 and slot 2 will be used. This is reflected by the properties \[DahlDesign.DDCR1] and \[DahlDesign.DDCR2] properties, which will go 00, 01, 10 and 11 as you scroll through the 4 layers.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 x layers =  button numbers
{% endtab %}
{% endtabs %}

#### funkyRotaryStackPush()

{% tabs %}
{% tab title="Description" %}
Stacked encoder in the funkyRotary [category](../encoders/#funkyrotary). This is for using the funky pushbutton.
{% endtab %}

{% tab title="Example" %}
`void funkyRotaryStackPush(int pushButtonRow, int pushButtonColumn, int aButton, int bButton, int cButton, int dButton, int fieldPlacement, int layers, int rotRow, int rotAcol, int rotBcol, bool reverse)`

Lets say our encoder is on row 3, columns 2+3, and our funky pushbutton+directional buttons are on row 1, usign columns 3-7, where pushbutton is row 3. We want 4 layers and we push the layer number to field placement 1.&#x20;

`funkyRotaryStackPush(1, 3, 4, 5, 6, 7, 1, 4, 3, 2, 3, false);`

The button numbers used is determined by the number written in the block for the A pin. B pin block will not be read. If button number was set to 15, the switch will use buttons 15 and 16 for the first layer, then 17+18, etc. The `reverse` part of the function will switch the button numbers if set to `true`.

In this example, we're using field slot 1, and with 4 layers we'll be using 2 bits. So slot 1 and slot 2 will be used. This is reflected by the properties \[DahlDesign.DDCR1] and \[DahlDesign.DDCR2] properties, which will go 00, 01, 10 and 11 as you scroll through the 4 layers.&#x20;
{% endtab %}

{% tab title="Requirements" %}
* 2 x layers =  button numbers
{% endtab %}
{% endtabs %}
