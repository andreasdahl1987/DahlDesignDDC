#if(LED1COUNT > 0)

void triggerLED(uint8_t startLED, uint8_t stopLED, bool condition, uint32_t color, uint8_t brightness, bool clearLEDs = true, bool blinkEnable = false, int blinkOnTimer = 500, int blinkOffTimer = 500)
{
  
  int R = (color & 0xFF0000) >> 16;
  R = R * brightness / 100;
  R = R * LEDBrightness / 100;

  int G = (color & 0x00FF00) >> 8;
  G = G * brightness / 100;
  G = G * LEDBrightness / 100;

  int B = color & 0x0000FF;
  B = B * brightness / 100;
  B = B * LEDBrightness / 100;

  int timer = globalClock % (blinkOnTimer + blinkOffTimer);

  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED1.setPixelColor(i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED1.setPixelColor(i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED1.setPixelColor(i, 0, 0, 0);
      Serial.println("wasnt here");
    }
  }
}

void colorLED (uint8_t startLED, uint8_t stopLED, uint32_t color, uint8_t brightness)
{
  int R = (color & 0xFF0000) >> 16;
  R = R * brightness / 100;
  R = R * LEDBrightness / 100;

  int G = (color & 0x00FF00) >> 8;
  G = G * brightness / 100;
  G = G * LEDBrightness / 100;

  int B = color & 0x0000FF;
  B = B * brightness / 100;
  B = B * LEDBrightness / 100;

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED1.setPixelColor(i, R, G, B);
  }
}

#endif
