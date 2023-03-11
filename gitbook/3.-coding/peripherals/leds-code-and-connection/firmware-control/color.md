# Color

The LED functions will ask you to fill in a color of choice. The RGB LEDs will take an 8 bit value (0 to 255) for all three colors (red, green, blue), which in total gives 24 bits of color choices, 16.7 million colors in total.&#x20;

In practice, a good palette is the [140 HTLM colors.](https://htmlcolorcodes.com/color-names/)

Typing out 24 bits is a bit impractical. "Dark Orchid" would be `100110010011001011001100.` As a decimal number: 10,040,012. Neither are easy to imagine any color from. Instead, DDC uses hexadecimal, where "Dark Orchid" is `0x9932CC.`

``

<figure><img src="../../../../.gitbook/assets/image (21).png" alt=""><figcaption></figcaption></figure>

The `0x` is just there to tell Arduino that a hexadecimal number is comming. Next comes 6 numbers, two for each color. The deal with hexadecimal is that each number can be 16 values instead of 10, ranging from 0 to F (0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f). The advantage of this being a single number represents 4 bits. So two numbers are 8 bits (decimal values 0-255), 00 being 0, FF being 255, and 80 being in the middle. Knowing this, we can tell that the color above has a lot of blue, a fair bit of red and a little bit of green. &#x20;
