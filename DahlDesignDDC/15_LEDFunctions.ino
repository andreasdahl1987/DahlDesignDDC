// ---------------------------------------------------------------------
// ------------------------------LED STRIP 1----------------------------
// ---------------------------------------------------------------------

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

  #if(LED1REVERSE == 1)
  
  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED1.setPixelColor(LED1COUNT - 1 - i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED1.setPixelColor(LED1COUNT - 1 - i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED1.setPixelColor(LED1COUNT - 1 - i, 0, 0, 0);
    }
  }
  
  #else
  
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
    }
  }

  #endif

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

  #if(LED1REVERSE == 1)

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED1.setPixelColor(LED1COUNT - 1 - i, R, G, B);
  }

  #else

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED1.setPixelColor(i, R, G, B);
  }

  #endif
  
}

void biteLED (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t biteChainStartLED, uint8_t brightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED1REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED1.setPixelColor(LED1COUNT - 1 - i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED1.setPixelColor(LED1COUNT - 1 - i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED1.setPixelColor(LED1COUNT - 1 - i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED1.setPixelColor(LED1COUNT - 1 - i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED1.setPixelColor(LED1COUNT - 1 - i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED1.setPixelColor(LED1COUNT - 1 - i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED1.setPixelColor(LED1COUNT - 1 - i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED1.setPixelColor(LED1COUNT - 1 - i, 0,0,0);
  }
 }

 #else

 
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED1.setPixelColor(i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED1.setPixelColor(i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED1.setPixelColor(i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED1.setPixelColor(i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED1.setPixelColor(i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED1.setPixelColor(i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED1.setPixelColor(i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED1.setPixelColor(i, 0,0,0);
  }
 }
 
 #endif
 
}

void rotaryLED(uint8_t switchNumber, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse)
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

  uint8_t reference = analogLastCounter[switchNumber-1] + offset;
  if (reference > positions - 1)
  {
    reference = reference - positions;
  }
  if(reverse)
  {
    reference = positions - 1 - reference;
  }

  for(int i = startLED; i < startLED + positions; i ++)
  {
    if (i - startLED == reference)
    {
      LED1.setPixelColor(i, R, G, B);
    }
    else
    {
      LED1.setPixelColor(i, 0, 0, 0);
    }
  }
}
#endif

// ---------------------------------------------------------------------
// ------------------------------LED STRIP 2----------------------------
// ---------------------------------------------------------------------


#if(LED2COUNT > 0)

void triggerLED2 (uint8_t startLED, uint8_t stopLED, bool condition, uint32_t color, uint8_t brightness, bool clearLEDs = true, bool blinkEnable = false, int blinkOnTimer = 500, int blinkOffTimer = 500)
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

  #if(LED2REVERSE == 1)
  
  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED2.setPixelColor(LED2COUNT - 1 - i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED2.setPixelColor(LED2COUNT - 1 - i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED2.setPixelColor(LED2COUNT - 1 - i, 0, 0, 0);
    }
  }
  
  #else
  
  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED2.setPixelColor(i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED2.setPixelColor(i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED2.setPixelColor(i, 0, 0, 0);
    }
  }

  #endif

}

void colorLED2 (uint8_t startLED, uint8_t stopLED, uint32_t color, uint8_t brightness)
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

  #if(LED2REVERSE == 1)

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED2.setPixelColor(LED2COUNT - 1 - i, R, G, B);
  }

  #else

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED2.setPixelColor(i, R, G, B);
  }

  #endif
  
}

void biteLED2 (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t biteChainStartLED, uint8_t brightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED2REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED2.setPixelColor(LED2COUNT - 1 - i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED2.setPixelColor(LED2COUNT - 1 - i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED2.setPixelColor(LED2COUNT - 1 - i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED2.setPixelColor(LED2COUNT - 1 - i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED2.setPixelColor(LED2COUNT - 1 - i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED2.setPixelColor(LED2COUNT - 1 - i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED2.setPixelColor(LED2COUNT - 1 - i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED2.setPixelColor(LED2COUNT - 1 - i, 0,0,0);
  }
 }

 #else

 
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED2.setPixelColor(i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED2.setPixelColor(i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED2.setPixelColor(i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED2.setPixelColor(i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED2.setPixelColor(i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED2.setPixelColor(i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED2.setPixelColor(i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED2.setPixelColor(i, 0,0,0);
  }
 }
 
 #endif
 
}

void rotaryLED2 (uint8_t switchNumber, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse)
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

  uint8_t reference = analogLastCounter[switchNumber-1] + offset;
  if (reference > positions - 1)
  {
    reference = reference - positions;
  }
  if(reverse)
  {
    reference = positions - 1 - reference;
  }

  for(int i = startLED; i < startLED + positions; i ++)
  {
    if (i - startLED == reference)
    {
      LED2.setPixelColor(i, R, G, B);
    }
    else
    {
      LED2.setPixelColor(i, 0, 0, 0);
    }
  }
}
#endif


// ---------------------------------------------------------------------
// ------------------------------LED STRIP 3----------------------------
// ---------------------------------------------------------------------


#if(LED3COUNT > 0)

void triggerLED3 (uint8_t startLED, uint8_t stopLED, bool condition, uint32_t color, uint8_t brightness, bool clearLEDs = true, bool blinkEnable = false, int blinkOnTimer = 500, int blinkOffTimer = 500)
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

  #if(LED3REVERSE == 1)
  
  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED3.setPixelColor(LED3COUNT - 1 - i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED3.setPixelColor(LED3COUNT - 1 - i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED3.setPixelColor(LED3COUNT - 1 - i, 0, 0, 0);
    }
  }
  
  #else
  
  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED3.setPixelColor(i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED3.setPixelColor(i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED3.setPixelColor(i, 0, 0, 0);
    }
  }

  #endif

}

void colorLED3 (uint8_t startLED, uint8_t stopLED, uint32_t color, uint8_t brightness)
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

  #if(LED3REVERSE == 1)

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED3.setPixelColor(LED3COUNT - 1 - i, R, G, B);
  }

  #else

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED3.setPixelColor(i, R, G, B);
  }

  #endif
  
}

void biteLED3 (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t biteChainStartLED, uint8_t brightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED3REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED3.setPixelColor(LED3COUNT - 1 - i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED3.setPixelColor(LED3COUNT - 1 - i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED3.setPixelColor(LED3COUNT - 1 - i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED3.setPixelColor(LED3COUNT - 1 - i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED3.setPixelColor(LED3COUNT - 1 - i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED3.setPixelColor(LED3COUNT - 1 - i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED3.setPixelColor(LED3COUNT - 1 - i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED3.setPixelColor(LED3COUNT - 1 - i, 0,0,0);
  }
 }

 #else

 
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED3.setPixelColor(i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED3.setPixelColor(i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED3.setPixelColor(i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED3.setPixelColor(i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED3.setPixelColor(i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED3.setPixelColor(i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED3.setPixelColor(i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED3.setPixelColor(i, 0,0,0);
  }
 }
 
 #endif
 
}

void rotaryLED3 (uint8_t switchNumber, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse)
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

  uint8_t reference = analogLastCounter[switchNumber-1] + offset;
  if (reference > positions - 1)
  {
    reference = reference - positions;
  }
  if(reverse)
  {
    reference = positions - 1 - reference;
  }

  for(int i = startLED; i < startLED + positions; i ++)
  {
    if (i - startLED == reference)
    {
      LED3.setPixelColor(i, R, G, B);
    }
    else
    {
      LED3.setPixelColor(i, 0, 0, 0);
    }
  }
}
#endif


// ---------------------------------------------------------------------
// ------------------------------LED STRIP 4----------------------------
// ---------------------------------------------------------------------


#if(LED4COUNT > 0)

void triggerLED4 (uint8_t startLED, uint8_t stopLED, bool condition, uint32_t color, uint8_t brightness, bool clearLEDs = true, bool blinkEnable = false, int blinkOnTimer = 500, int blinkOffTimer = 500)
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

  #if(LED4REVERSE == 1)
  
  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED4.setPixelColor(LED4COUNT - 1 - i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED4.setPixelColor(LED4COUNT - 1 - i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED4.setPixelColor(LED4COUNT - 1 - i, 0, 0, 0);
    }
  }
  
  #else
  
  if(condition)
  {
    if (clearLEDs || (blinkEnable && timer < blinkOffTimer))
    {
      for (int i = startLED; i < stopLED+1; i++)
      {
        LED4.setPixelColor(i, 0, 0, 0);
      }
    }
    if (!blinkEnable || (blinkEnable && timer > blinkOffTimer))
    {
        for (int i = startLED; i < stopLED+1; i++)
        {
          LED4.setPixelColor(i, R, G, B);
        }
     }
  }
  
  else if (clearLEDs)
  {
    for (int i = startLED; i < stopLED+1; i++)
    {
      LED4.setPixelColor(i, 0, 0, 0);
    }
  }

  #endif

}

void colorLED4 (uint8_t startLED, uint8_t stopLED, uint32_t color, uint8_t brightness)
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

  #if(LED4REVERSE == 1)

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED4.setPixelColor(LED4COUNT - 1 - i, R, G, B);
  }

  #else

  for (int i = startLED; i < stopLED+1; i++)
  {
    LED4.setPixelColor(i, R, G, B);
  }

  #endif
  
}

void biteLED4 (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t biteChainStartLED, uint8_t brightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED4REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED4.setPixelColor(LED4COUNT - 1 - i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED4.setPixelColor(LED4COUNT - 1 - i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED4.setPixelColor(LED4COUNT - 1 - i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED4.setPixelColor(LED4COUNT - 1 - i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED4.setPixelColor(LED4COUNT - 1 - i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED4.setPixelColor(LED4COUNT - 1 - i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED4.setPixelColor(LED4COUNT - 1 - i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED4.setPixelColor(LED4COUNT - 1 - i, 0,0,0);
  }
 }

 #else

 
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || engageBlink && timer > 500)
    {
      for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED4.setPixelColor(i, R, G, B);
      }
    }
    else if (engageBlink && timer < 500)
    {
       for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
      {
        LED4.setPixelColor(i ,0, 0, 0);
      }
    }

    for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
    {
      LED4.setPixelColor(i, 0,0,0);
    }
  }

  if (biteButtonBit1 && !biteButtonBit2)
  {
    int R = (step1Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;

    uint8_t ledCount = BitePoint/100; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED4.setPixelColor(i, R, G, B);
    }
   }
  }

  else if (!biteButtonBit1 && biteButtonBit2)
  {
    int R = (step2Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = (BitePoint % 100)/10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED4.setPixelColor(i, R, G, B);
    }
   }
  }

    else if (biteButtonBit1 && biteButtonBit2)
  {
    int R = (step3Color & 0xFF0000) >> 16;
    R = R * brightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * brightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * brightness / 100;
    B = B * LEDBrightness / 100;
    
    uint8_t ledCount = BitePoint % 10; 

   if(ledCount != 0)
   {
    for(int i = biteChainStartLED; i < biteChainStartLED + ledCount; i++)
    {
      LED4.setPixelColor(i, R, G, B);
    }
   }
  }
 //Resetting all LEDs in the end
 if (biteRefresh)
 {
  for(int i = biteEngageStartLED; i < biteEngageStopLED+1; i++)
    {
      LED4.setPixelColor(i ,0, 0, 0);
    }
  for(int i = biteChainStartLED; i < biteChainStartLED + 10; i++)
  {
    LED4.setPixelColor(i, 0,0,0);
  }
 }
 
 #endif
 
}

void rotaryLED4 (uint8_t switchNumber, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse)
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

  uint8_t reference = analogLastCounter[switchNumber-1] + offset;
  if (reference > positions - 1)
  {
    reference = reference - positions;
  }
  if(reverse)
  {
    reference = positions - 1 - reference;
  }

  for(int i = startLED; i < startLED + positions; i ++)
  {
    if (i - startLED == reference)
    {
      LED4.setPixelColor(i, R, G, B);
    }
    else
    {
      LED4.setPixelColor(i, 0, 0, 0);
    }
  }
}
#endif

