void colorMe (uint8_t startLED, uint8_t stopLED, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  int R = r * brightness / 100;
  R = R * LEDBrightness / 100;

  int G = g * brightness / 100;
  G = G * LEDBrightness / 100;

  int B = b * brightness / 100;
  B = B * LEDBrightness / 100;

  for (int i = startLED; i < stopLED+1; i++)
  {
    pixels1.setPixelColor(i, R, G, B);
  }
}
