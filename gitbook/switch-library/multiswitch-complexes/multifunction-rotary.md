# Multifunction rotary

<figure><img src="../../.gitbook/assets/image (1) (1) (2) (1).png" alt=""><figcaption></figcaption></figure>

* The idea of the multifunction system is that a 12-position switch controls  the button numbers of two buttons (or an encoder that pulses button presses on CW/CCW rotation). The system produces 24 button numbers.
* In the example above, the 12-position switch is in position 8, meaning button 1 is button number 15 and button 2 is button number 16. Flicking the rotary to position 9 will give you different button number outputs from the two buttons; 17 and 18.&#x20;
* The same way as the hybrid system, this is useful for setting up several adjustments to very few switches. You could set up ABS +/- in position 1, TC +/- in position 2, Engine map +/- in position 3, etc.&#x20;
* The main advantages of this approach in comparison to the hybrid system are:
  * There are no simulatneous button presses, so all kinds of sims are supported.
  *   The physical position of the switch matches the button numbers, so you can go ahead and label your controller accordingly, as below.&#x20;

      <figure><img src="../../.gitbook/assets/image (4) (1) (1).png" alt=""><figcaption></figcaption></figure>
*   There are 24 button and **36 button** variants. Really, the product of both are 24 functional buttons. The difference is that in the 36 button variant the 12-position switch is also given button numbers to reflect its position, which is useful if you want information about the switch position in SimHub for dashboard purposes.

    <figure><img src="../../.gitbook/assets/image (6) (1) (1).png" alt=""><figcaption></figcaption></figure>



#### multiFunction2bit24()

{% tabs %}
{% tab title="Description" %}
Multifunction complex using a 12-way switch and an encoder in the rotary2Bit category.

The starting button number for the whole 24-button complex is defined by the button number for the analog switch. The button numbers written in the switch table for the encoder will not be used.&#x20;
{% endtab %}

{% tab title="Example" %}
`void multiFunction2Bit24(int analogPin, int switchNumber, int row, int column, bool reverseAnalog, bool reverse2Bit, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)`



Switch setup with explainations:

multiFunction2Bit24(

A3, <- The analog pin this switch is connected to

4, <- The switch number this analog switch is assigned

5, <- The row the encoder is connected to

2, <- The first of the two columns the encoder is connected to (2 and 3 in this case)

false, <- The effect of rotary switch rotation is not reversed

true, <- The effect of the encoder rotation is reversed

16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023); <- Switch position values



So for a 12-way connected to A3, assigned analog switch# 4 and an encoder on row 5 column 2+3 could look like:

`multiFunction2Bit24(A3, 4, 5, 2, false, true, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);`
{% endtab %}

{% tab title="Requirements" %}
* 24 button numbers
{% endtab %}
{% endtabs %}

#### multiFunction2bit36()

{% tabs %}
{% tab title="Description" %}
Multifunction complex using a 12-way switch and an encoder in the rotary2Bit category.

Also gives button numbers to the 12-way switch.

The starting button number for the whole 36-button complex is defined by the button number for the analog switch. The button numbers written in the switch table for the encoder will not be used.&#x20;
{% endtab %}

{% tab title="Example" %}
`void multiFunction2Bit36(int analogPin, int switchNumber, int row, int column, bool reverseAnalog, reverse2Bit, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)`



Switch setup with explainations:

multiFunction2Bit24(

A3, <- The analog pin this switch is connected to

4, <- The switch number this analog switch is assigned

5, <- The row the encoder is connected to

2, <- The first of the two columns the encoder is connected to (2 and 3 in this case)

false, <- The effect of rotary rotation is not reversed

true, <- The effect of the encoder rotation is reversed

16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023); <- Switch position values



So for a 12-way connected to A3, assigned analog switch# 4 and an encoder on row 5 column 2+3 could look like:

`multiFunction2Bit36(A3, 4, 5, 2, false, true, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);`
{% endtab %}

{% tab title="Requirements" %}
* 36 button numbers
{% endtab %}
{% endtabs %}

#### multiFunction2Button24()

{% tabs %}
{% tab title="Description" %}
Multifunction complex using a 12-way switch and two pushbuttons.

The starting button number for the whole 24-button complex is defined by the button number for the analog switch. The button numbers written in the switch table for the two buttons will not be used.&#x20;
{% endtab %}

{% tab title="Example" %}
`void multiFunction2Button24(int analogPin, int switchNumber,int rowButton1, int columnButton1, int rowButton2, int columnButton2, bool reverse, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)`



Switch setup with explainations:

multiFunction2Bit24(

A3, <- The analog pin this switch is connected to

4, <- The switch number this analog switch is assigned

5, <- The row of button 1

3, <- The column of button 1

2, <- The row of button 2

4, <- The column of button 2

false, <- The effect of rotary rotation is not reversed

16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023); <- Switch position values



So for a 12-way connected to A3, assigned analog switch# 4 and two buttons on row5/col3 and row2/col4 could look like this:

`multiFunction2Button24(A3, 4, 5, 3, 2, 4, false, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);`
{% endtab %}

{% tab title="Requirements" %}
* 24 button numbers
{% endtab %}
{% endtabs %}

#### multiFunction2Button36()

{% tabs %}
{% tab title="Description" %}
Multifunction complex using a 12-way switch and two pushbuttons.

The starting button number for the whole 36-button complex is defined by the button number for the analog switch. The button numbers written in the switch table for the two buttons will not be used.&#x20;
{% endtab %}

{% tab title="Example" %}
`void multiFunction2Button36(int analogPin, int switchNumber,int rowButton1, int columnButton1, int rowButton2, int columnButton2, bool reverse, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)`



Switch setup with explainations:

multiFunction2Bit24(

A3, <- The analog pin this switch is connected to

4, <- The switch number this analog switch is assigned

5, <- The row of button 1

3, <- The column of button 1

2, <- The row of button 2

4, <- The column of button 2

false, <- The effect of rotary rotation is not reversed

16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023); <- Switch position values



So for a 12-way connected to A3, assigned analog switch# 4 and two buttons on row5/col3 and row2/col4 could look like this:

`multiFunction2Button36(A3, 4, 5, 3, 2, 4, false, 16, 107, 200, 291, 383, 474, 566, 657, 749, 841, 932, 1023);`
{% endtab %}

{% tab title="Requirements" %}
* 36 button numbers
{% endtab %}
{% endtabs %}
