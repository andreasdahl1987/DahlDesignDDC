#if (USING_OLED == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))

void tcaselect(uint8_t i) 
{
  #if (OLED_I2C1 == 1)
  Wire1.beginTransmission(TCAADDR);  // TCA9548A address
  Wire1.write(1 << i);               // send byte to select bus
  Wire1.endTransmission();
  #else
  Wire.beginTransmission(TCAADDR);  // TCA9548A address
  Wire.write(1 << i);               // send byte to select bus
  Wire.endTransmission();
  #endif 
}

void OLEDcleanup()
{
  #if(USING_CB1 == 1 && ROBIN_OLED == 1)
  for (int i = 0; i < 6; i++)
  {
  #else
  for (int i = 0; i < DISPLAYCOUNT; i++)
  {
  #endif
    //Writing to displays
    if (writeToDisplay[i])
    {
      #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
      tcaselect(i);
      #endif
      displays[i].display();
      writeToDisplay[i] = false;
      printCounter++;
      Serial.println(printCounter);
    }
    //Resetting conditional write line index
    OLEDcondiIndex[i] = 0;

    //Filtering out condiForce write this loop
    OLEDcondiForce[i] = OLEDcondiForce[i] & 2;
    //Checking if any condi lines has triggered condiForce, then setting condiForce active on 1st bit if there are still conditions that are true (active condiLocks)
    if(OLEDcondiForce[i] == 2 && OLEDcondiLock[i] > 0)
    {
      OLEDcondiForce[i] = 1;
    }
    else
    {
      OLEDcondiForce[i] = 0;
    }

    //Locking background from running again
    if(backgroundSet[i])
    {
      OLEDgenLock[i] = true;  //Prevent writing background untill genlock is off again (from condi being met and un-met again)
      backgroundSet[i] = false;
    }
  }

}

void backgroundWrite(uint8_t screenNumber, const char* text = "", bool clear = true, int16_t cursorX = 0, int16_t cursorY = 12)
{
  int index = screenNumber-1;

  if(!OLEDgenLock[index] && OLEDcondiLock[index] == 0) //Checking for genlock open and all condilocks being unlocked
  { 
    if(clear)
    {
      #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
      tcaselect(index);
      #endif
      displays[index].clearDisplay();
    }    
    textGraphics[index].setCursor(cursorX, cursorY);                // start writing at this position
    textGraphics[index].print(text);

    writeToDisplay[index] = true;
    backgroundSet[index] = true;
  }
}

void backgroundWrite(const char* text = "", bool clear = true, int16_t cursorX = 0, int16_t cursorY = 12)
{
  int index = 0;

  if(!OLEDgenLock[index] && OLEDcondiLock[index] == 0) //Checking for genlock open and all condilocks being unlocked
  { 
    if(clear)
    {
      #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
      tcaselect(index);
      #endif
      displays[index].clearDisplay();
    }    
    textGraphics[index].setCursor(cursorX, cursorY);                // start writing at this position
    textGraphics[index].print(text);

    writeToDisplay[index] = true;
    backgroundSet[index] = true;
  }
}

void conditionalWrite(uint8_t screenNumber, const char* text, bool condition, bool clear = true, uint8_t cursorX = 0, uint8_t cursorY = 12, int ChangeTimer = 0) 
{
  int index = screenNumber - 1;
  bool condiLock = (OLEDcondiLock[index] >> OLEDcondiIndex[index]) & 1; //Finding condiLock state for this line
  bool condiForce = OLEDcondiForce[index] & 1; //Finding an active condiForce
  
  if (condition && (!condiLock || condiForce)) //Write to display if lock is open, meaning first time we're seeing it open. OR if condiForce is active
  {
    if (clear) 
    {
      #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
      tcaselect(index);
      #endif
      displays[index].clearDisplay();
    }
    textGraphics[index].setCursor(cursorX, cursorY);                // start writing at this position
    textGraphics[index].print(text);

    unsigned long writeMask = 1 << OLEDcondiIndex[index];
    OLEDcondiLock[index] = OLEDcondiLock[index] | writeMask;

    writeToDisplay[index] = true;

  }
  else if(!condition && condiLock) //If condiLock is on, but condition is no longer met, this is the first time we're seeing condition not met after being met before. 
  {
    OLEDgenLock[index] = false; //Background is ready to run again

    //Turning off condilock, meaning we're ready to fire this condition again. 
    unsigned long clearMask = 1 << OLEDcondiIndex[index];
    clearMask = ~clearMask;
    OLEDcondiLock[index] = OLEDcondiLock[index] & clearMask;
    //Currently we're at no condition met and condilock off. Meaning on the next loop we'll neither write to screen or change condilock/genlock. 

    //Setting up condiForce, forcing a rewrite of all conditional lines on the next loop. Write this state to the 2nd bit
    OLEDcondiForce[index] = 2;
  }

  OLEDcondiIndex[index]++; //Increasing condi index by one for next line. 
}

void changeFont(uint8_t screenNumber, const uint8_t* font)
{
  textGraphics[screenNumber-1].setFont(font);
}

void clearOnChange(uint8_t screenNumber) 
{
  int index = screenNumber - 1;
  bool condiLock = (OLEDcondiLock[index] >> OLEDcondiIndex[index]) & 1; //Finding condiLock state for this line
  bool condiForce = OLEDcondiForce[index] & 1; //Finding an active condiForce
  
  if (!condiLock || condiForce) //Write to display if lock is open, meaning first time we're seeing it open. OR if condiForce is active
  {
    #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
    tcaselect(index);
    #endif
    displays[index].clearDisplay();

    unsigned long writeMask = 1 << OLEDcondiIndex[index];
    OLEDcondiLock[index] = OLEDcondiLock[index] | writeMask;

    writeToDisplay[index] = true;

  }

  OLEDcondiIndex[index]++; //Increasing condi index by one for next line. 
}

void backgroundImage(uint8_t screenNumber, const uint8_t image[], uint8_t imageWidth, uint8_t imageHeight, uint8_t offsetX, uint8_t offsetY)
{
  int index = screenNumber-1;

  if(!OLEDgenLock[index])
  {
    #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
    tcaselect(index);
    #endif
    displays[index].clearDisplay();
    displays[index].drawBitmap(offsetX, offsetY, image, imageWidth,imageHeight,1);
    displays[index].display();
    OLEDgenLock[index] = true;
    OLEDcondiLock[index] = false;
  }
}

void conditionalImage(uint8_t screenNumber, const uint8_t image[], bool condition, uint8_t imageWidth, uint8_t imageHeight, uint8_t offsetX, uint8_t offsetY)
{
  int index = screenNumber - 1;
  if (condition && !OLEDcondiLock[index]) 
  {
    #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
    tcaselect(index);
    #endif
    displays[index].clearDisplay();
    displays[index].drawBitmap(offsetX, offsetY, image, imageWidth,imageHeight,1);
    displays[index].display();
    OLEDcondiLock[index] = true;
  }
  else if(!condition)
  {
    if (OLEDcondiLock[index]) 
    {
      OLEDgenLock[index] = false;
    }
  }
}

void animationFrame(uint16_t frameCount, uint8_t animationWidth, uint8_t animationHeigth)
{
  currentAniWidth = animationWidth;
  currentAniHeight = animationHeigth;
  currentFrameCount = frameCount;
}

void backgroundAnimation(uint8_t screenNumber, const byte animation[][512], float speed, uint8_t offsetX, uint8_t offsetY)
{
  int index = screenNumber-1;

  float timeBetween = speed * 50;

  if(!OLEDgenLock[index] && globalClock - OLEDtimer[index] > timeBetween)
  {
    OLEDtimer[index] = globalClock;

    #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
    tcaselect(index);
    #endif

    displays[index].clearDisplay();
    displays[index].drawBitmap(offsetX, offsetY, animation[OLEDframes[index]], currentAniWidth, currentAniHeight,1);
    displays[index].display();

    OLEDframes[index] ++;

    if(OLEDframes[index] >= currentFrameCount)
    {
      OLEDframes[index] = 0;
    }

    OLEDcondiLock[index] = false;
  }
}

void DDClogo(uint8_t screenNumber)
{
  int index = screenNumber-1;
  if(!OLEDgenLock[index])
  {
    #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
    tcaselect(index);
    #endif
    displays[index].clearDisplay();
    displays[index].drawBitmap(0, 3, DDCimage, 128,59,1);
    displays[index].display();
    OLEDgenLock[index] = true;
    OLEDcondiLock[index] = false;
  }
}

void OLEDSetup()
{
#if (BOARDTYPE == 2)
  #if (OLED_I2C1 == 1 && OLED_I2C0 == 1 && DISPLAYCOUNT == 2)
    Wire1.setSDA(SDA1PIN);
    Wire1.setSCL(SCL1PIN);
    Wire.setSDA(SDA0PIN);
    Wire.setSCL(SCL0PIN);
    wire0Init = true;
    wire1Init = true;
  #elif (OLED_I2C1 == 1)
    Wire1.setSDA(SDA1PIN);
    Wire1.setSCL(SCL1PIN);
    wire1Init = true;
  #else
    {
      Wire.setSDA(SDA0PIN);
      Wire.setSCL(SCL0PIN);
      wire0Init = true;
    }
  #endif
#else
  wire0Init = true;
#endif
}

void OLED_Init ()
{
#if((USING_CB1 == 1 && ROBIN_OLED ==1))
  displayInitiate(1);
  displayInitiate(2);
  displayInitiate(3);
  displayInitiate(4);
  displayInitiate(5);
  displayInitiate(6);
#elif(USING_MUX == 1)
  #if(DISPLAYCOUNT > 7 )
    displayInitiate(1);
    displayInitiate(2);
    displayInitiate(3);
    displayInitiate(4);
    displayInitiate(5);
    displayInitiate(6);
    displayInitiate(7);
    displayInitiate(8);
  #elif(DISPLAYCOUNT > 6 )
    displayInitiate(1);
    displayInitiate(2);
    displayInitiate(3);
    displayInitiate(4);
    displayInitiate(5);
    displayInitiate(6);
    displayInitiate(7);
  #elif(DISPLAYCOUNT > 5 )
    displayInitiate(1);
    displayInitiate(2);
    displayInitiate(3);
    displayInitiate(4);
    displayInitiate(5);
    displayInitiate(6);
  #elif(DISPLAYCOUNT > 4)
    displayInitiate(1);
    displayInitiate(2);
    displayInitiate(3);
    displayInitiate(4);
    displayInitiate(5);
  #elif(DISPLAYCOUNT > 3)
    displayInitiate(1);
    displayInitiate(2);
    displayInitiate(3);
    displayInitiate(4);
    #elif(DISPLAYCOUNT > 2)
    displayInitiate(1);
    displayInitiate(2);
    displayInitiate(3);
    #elif(DISPLAYCOUNT > 1)
    displayInitiate(1);
    displayInitiate(2);
  #elif(DISPLAYCOUNT > 0)
    displayInitiate(1);
  #endif
#elif (OLED_I2C1 == 1 && OLED_I2C0 == 1 && DISPLAYCOUNT == 2 && BOARDTYPE == 2)
  displayInitiate(1);
  displayInitiate(2);
#else
  displayInitiate(1);
#endif
}

void displayInitiate(int number)
{
  int index = number - 1;
  #if(USING_MUX == 1 || (USING_CB1 == 1 && ROBIN_OLED == 1))
  tcaselect(index);
  #endif
  displays[index].begin(SSD1306_SWITCHCAPVCC, OLED_Address); 
  displays[index].clearDisplay();
  displays[index].display();

  textGraphics[index].begin(displays[index]); 
  textGraphics[index].setFontMode(1);                
  textGraphics[index].setFontDirection(0);            
  textGraphics[index].setFont(u8g2_font_helvB12_tf);
  textGraphics[index].setForegroundColor(WHITE); 
}
#endif //OLED using
