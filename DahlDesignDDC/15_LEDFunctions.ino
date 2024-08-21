// ---------------------------------------------------------------------
// -----------------------------GLOBALS---------------------------------
// ---------------------------------------------------------------------

void SimHubImport()
{
  if(simhubActive)
  {
      #if(LED1COUNT > 0)
    for (uint16_t i = 0; i < LED1COUNT; i++) 
    {
      LED1.setPixelColor(i, LED1.Color(SH_R_Valid[i], SH_G_Valid[i], SH_B_Valid[i]));
    }
  #endif
  #if(LED2COUNT > 0)
    for (uint16_t i = 0; i < LED2COUNT; i++) 
    {
      LED2.setPixelColor(i, LED2.Color(SH_R_Valid[LED1COUNT+i], SH_G_Valid[LED1COUNT+i], SH_B_Valid[LED1COUNT+i]));
    }
  #endif
  #if(LED3COUNT > 0)
  for (uint16_t i = 0; i < LED3COUNT; i++) 
  {
    LED3.setPixelColor(i, LED3.Color(SH_R_Valid[LED1COUNT+LED2COUNT+i], SH_G_Valid[LED1COUNT+LED2COUNT+i], SH_B_Valid[LED1COUNT+LED2COUNT+i]));
  }
  #endif
  #if(LED4COUNT > 0)
    for (uint16_t i = 0; i < LED4COUNT; i++) 
    {
      LED4.setPixelColor(i, LED4.Color(SH_R_Valid[LED1COUNT+LED2COUNT+LED3COUNT+i], SH_G_Valid[LED1COUNT+LED2COUNT+LED3COUNT+i], SH_B_Valid[LED1COUNT+LED2COUNT+LED3COUNT+i]));
    }
  #endif
  }
}


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

void biteLED (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t engageBrightness, uint8_t biteChainStartLED, uint8_t biteBrightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED1REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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

void rotaryLED(uint8_t analogChannel, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse, uint32_t backgroundColor = 0x000000, uint8_t backgroundBrightness = 25)
{

  //Position
  int R = (color & 0xFF0000) >> 16;
  R = R * brightness / 100;
  R = R * LEDBrightness / 100;

  int G = (color & 0x00FF00) >> 8;
  G = G * brightness / 100;
  G = G * LEDBrightness / 100;

  int B = color & 0x0000FF;
  B = B * brightness / 100;
  B = B * LEDBrightness / 100;

  //Background
  int bR = (backgroundColor & 0xFF0000) >> 16;
  bR = bR * backgroundBrightness / 100;
  bR = bR * LEDBrightness / 100;

  int bG = (backgroundColor & 0x00FF00) >> 8;
  bG = bG * backgroundBrightness / 100;
  bG = bG * LEDBrightness / 100;

  int bB = backgroundColor & 0x0000FF;
  bB = bB * backgroundBrightness / 100;
  bB = bB * LEDBrightness / 100;
  

  uint8_t reference = analogLastCounter[analogChannel-1] + offset;
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
      LED1.setPixelColor(i, bR, bG, bB);
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

void biteLED2 (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t engageBrightness, uint8_t biteChainStartLED, uint8_t biteBrightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED2REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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

void rotaryLED2 (uint8_t analogChannel, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse, uint32_t backgroundColor = 0x000000, uint8_t backgroundBrightness = 25)
{
  //Position
  int R = (color & 0xFF0000) >> 16;
  R = R * brightness / 100;
  R = R * LEDBrightness / 100;

  int G = (color & 0x00FF00) >> 8;
  G = G * brightness / 100;
  G = G * LEDBrightness / 100;

  int B = color & 0x0000FF;
  B = B * brightness / 100;
  B = B * LEDBrightness / 100;

  //Background
  int bR = (backgroundColor & 0xFF0000) >> 16;
  bR = bR * backgroundBrightness / 100;
  bR = bR * LEDBrightness / 100;

  int bG = (backgroundColor & 0x00FF00) >> 8;
  bG = bG * backgroundBrightness / 100;
  bG = bG * LEDBrightness / 100;

  int bB = backgroundColor & 0x0000FF;
  bB = bB * backgroundBrightness / 100;
  bB = bB * LEDBrightness / 100;

  uint8_t reference = analogLastCounter[analogChannel-1] + offset;
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
      LED2.setPixelColor(i, bR, bG, bB);
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

void biteLED3 (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t engageBrightness, uint8_t biteChainStartLED, uint8_t biteBrightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED3REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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

void rotaryLED3 (uint8_t analogChannel, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse, uint32_t backgroundColor = 0x000000, uint8_t backgroundBrightness = 25)
{
  //Position
  int R = (color & 0xFF0000) >> 16;
  R = R * brightness / 100;
  R = R * LEDBrightness / 100;

  int G = (color & 0x00FF00) >> 8;
  G = G * brightness / 100;
  G = G * LEDBrightness / 100;

  int B = color & 0x0000FF;
  B = B * brightness / 100;
  B = B * LEDBrightness / 100;

  //Background
  int bR = (backgroundColor & 0xFF0000) >> 16;
  bR = bR * backgroundBrightness / 100;
  bR = bR * LEDBrightness / 100;

  int bG = (backgroundColor & 0x00FF00) >> 8;
  bG = bG * backgroundBrightness / 100;
  bG = bG * LEDBrightness / 100;

  int bB = backgroundColor & 0x0000FF;
  bB = bB * backgroundBrightness / 100;
  bB = bB * LEDBrightness / 100;

  uint8_t reference = analogLastCounter[analogChannel-1] + offset;
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
      LED3.setPixelColor(i, bR, bG, bB);
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

void biteLED4 (uint8_t biteEngageStartLED, uint8_t biteEngageStopLED, uint8_t engageBrightness, uint8_t biteChainStartLED, uint8_t biteBrightness, uint32_t engageColor = 0xFFA500, uint32_t step1Color = 0x40E0D0, uint32_t step2Color = 0xFF00FF, uint32_t step3Color = 0xFFA500, bool engageBlink = true)
{

  #if (LED4REVERSE == 1)
  
  int BitePoint = bitePoint;

  if (biteButtonBit1 || biteButtonBit2)
  {
    int timer = globalClock % 1000;
    
    int R = (engageColor & 0xFF0000) >> 16;
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * engageBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (engageColor & 0x00FF00) >> 8;
    G = G * engageBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = engageColor & 0x0000FF;
    B = B * engageBrightness / 100;
    B = B * LEDBrightness / 100;

    if (!engageBlink || (engageBlink && timer > 500))
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step1Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step1Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step2Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step2Color & 0x0000FF;
    B = B * biteBrightness / 100;
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
    R = R * biteBrightness / 100;
    R = R * LEDBrightness / 100;
  
    int G = (step3Color & 0x00FF00) >> 8;
    G = G * biteBrightness / 100;
    G = G * LEDBrightness / 100;
  
    int B = step3Color & 0x0000FF;
    B = B * biteBrightness / 100;
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

void rotaryLED4 (uint8_t analogChannel, uint8_t startLED, uint8_t positions, uint32_t color, uint8_t brightness, uint8_t offset, bool reverse, uint32_t backgroundColor = 0x000000, uint8_t backgroundBrightness = 25)
{
  //Position
  int R = (color & 0xFF0000) >> 16;
  R = R * brightness / 100;
  R = R * LEDBrightness / 100;

  int G = (color & 0x00FF00) >> 8;
  G = G * brightness / 100;
  G = G * LEDBrightness / 100;

  int B = color & 0x0000FF;
  B = B * brightness / 100;
  B = B * LEDBrightness / 100;

  //Background
  int bR = (backgroundColor & 0xFF0000) >> 16;
  bR = bR * backgroundBrightness / 100;
  bR = bR * LEDBrightness / 100;

  int bG = (backgroundColor & 0x00FF00) >> 8;
  bG = bG * backgroundBrightness / 100;
  bG = bG * LEDBrightness / 100;

  int bB = backgroundColor & 0x0000FF;
  bB = bB * backgroundBrightness / 100;
  bB = bB * LEDBrightness / 100;

  uint8_t reference = analogLastCounter[analogChannel-1] + offset;
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
      LED4.setPixelColor(i, bR, bG, bB);
    }
  }
}
#endif
