#if (USING_OLED == 1)

void tcaselect(uint8_t i) 
{
  Wire.beginTransmission(TCAADDR);  // TCA9548A address
  Wire.write(1 << i);               // send byte to select bus
  Wire.endTransmission();
}

void OLEDcleanup()
{
for (int i = 0; i < DISPLAYCOUNT; i++)
{
  //Writing to displays
  if (writeToDisplay[i])
  {
    displays[i].display();
    writeToDisplay[i] = false;
    Serial.println("Printing to screen");
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
Serial.println("");
}

void backgroundWrite(uint8_t screenNumber, const char* text, uint8_t cursorX = 0, uint8_t cursorY = 0, bool clear = true, uint8_t color = 1, float textSize = 1)
{
  int index = screenNumber-1;

  if(!OLEDgenLock[index] && OLEDcondiLock[index] == 0) //Checking for genlock open and all condilocks being unlocked
  {
    tcaselect(index);
      
    if(clear)
    {
      displays[index].clearDisplay();
    }    

    displays[index].setTextColor(color); //0 is black, 1 is white, 2 is inverted
    displays[index].setCursor(cursorX, cursorY);
    displays[index].setTextSize(textSize);
    displays[index].println(text);

    writeToDisplay[index] = true;
    backgroundSet[index] = true;
  }
}

void conditionalWrite(uint8_t screenNumber, const char* text, bool condition, uint8_t cursorX = 0, uint8_t cursorY = 0, bool clear = true, int ChangeTimer = 0, float textSize = 1, uint8_t color = 1) 
{
  int index = screenNumber - 1;
  bool condiLock = (OLEDcondiLock[index] >> OLEDcondiIndex[index]) & 1; //Finding condiLock state for this line
  bool condiForce = OLEDcondiForce[index] & 1; //Finding an active condiForce
  
  bool condiChanged = true; //Detecting changed timer within threshold
  int changeTimer = ChangeTimer;

  if(condition && !condiLock)
  {
    OLEDcondiTimer[index] = globalClock;
  }

  if (changeTimer > 0 && globalClock - OLEDcondiTimer[index] > changeTimer)
  {
    condiChanged = false;
  }

  Serial.print("  |  Condi line ");
  Serial.print(OLEDcondiIndex[index]);
  Serial.print(": ");
  Serial.print(condiChanged);

  if (condition && condiChanged && (!condiLock || condiForce)) //Write to display if lock is open, meaning first time we're seeing it open. OR if condiForce is active
  {
    tcaselect(index);
    if (clear) 
    {
      displays[index].clearDisplay();
    }
    displays[index].setTextColor(color);  //0 is black, 1 is white, 2 is inverted
    displays[index].setCursor(cursorX, cursorY);
    displays[index].setTextSize(textSize);
    displays[index].println(text);

    unsigned long writeMask = 1 << OLEDcondiIndex[index];
    OLEDcondiLock[index] = OLEDcondiLock[index] | writeMask;

    writeToDisplay[index] = true;

  }
  else if((!condition || !condiChanged) && condiLock) //If condiLock is on, but condition is no longer met, this is the first time we're seeing condition not met after being met before. 
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

void backgroundImage(uint8_t screenNumber, const uint8_t image[], uint8_t imageWidth, uint8_t imageHeight, uint8_t offsetX, uint8_t offsetY)
{
  int index = screenNumber-1;

  if(!OLEDgenLock[index])
  {
    tcaselect(index);
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
    tcaselect(index);
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

    tcaselect(index);

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
    tcaselect(index);
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
#if (OLED_I2C_NUMBER == 1)
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
}

void displayInitiate(int number)
{
  int index = number - 1;
  tcaselect(index);
  displays[index].begin(SSD1306_SWITCHCAPVCC, OLED_Address); 
  displays[index].clearDisplay();
  displays[index].display();
}
#endif //OLED using
