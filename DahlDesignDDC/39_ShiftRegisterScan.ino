void shiftRegisterScan()
{
    if (SRCOUNT == 0)
    {
        return;
    }
    //SR1
    if (SRCOUNT >= 1)
    {
        digitalWrite(SR1LATCH, 0); //Enable parallel inputs
        digitalWrite(SR1CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR1CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR1LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR1CHAIN; i++)
        {
            uint8_t rowNumber = i / 8; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR1DATA); //Set the bit to rawState
            digitalWrite(SR1CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR1CLOCK, 1); //Clock high to get new bit to SR1DATA
        }
    }

    if (SRCOUNT >= 2)
    {
        digitalWrite(SR2LATCH, 0); //Enable parallel inputs
        digitalWrite(SR2CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR2CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR2LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR2CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR2DATA); //Set the bit to rawState
            digitalWrite(SR2CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR2CLOCK, 1); //Clock high to get new bit to SR2DATA
        }
    }

    if (SRCOUNT >= 3)
    {
        digitalWrite(SR3LATCH, 0); //Enable parallel inputs
        digitalWrite(SR3CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR3CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR3LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR3CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN + SR2CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR3DATA); //Set the bit to rawState
            digitalWrite(SR3CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR3CLOCK, 1); //Clock high to get new bit to SR3DATA
        }
    }

    if (SRCOUNT >= 4)
    {
        digitalWrite(SR4LATCH, 0); //Enable parallel inputs
        digitalWrite(SR4CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR4CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR4LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR4CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN + SR2CHAIN + SR3CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR4DATA); //Set the bit to rawState
            digitalWrite(SR4CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR4CLOCK, 1); //Clock high to get new bit to SR4DATA
        }
    }
}
