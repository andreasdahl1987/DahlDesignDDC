void shiftRegisterSetup()
{
    if (SRCOUNT >= 1)
    {
        pinMode(SR1IO, OUTPUT);
        pinMode(SR1CLOCK, OUTPUT);
        pinMode(SR1DATA, INPUT);
    }
    if (SRCOUNT >= 2)
    {
        pinMode(SR2IO, OUTPUT);
        pinMode(SR2CLOCK, OUTPUT);
        pinMode(SR2DATA, INPUT);
    }
    if (SRCOUNT >= 3)
    {
        pinMode(SR3IO, OUTPUT);
        pinMode(SR3CLOCK, OUTPUT);
        pinMode(SR3DATA, INPUT);
    }
    if (SRCOUNT >= 4)
    {
        pinMode(SR4IO, OUTPUT);
        pinMode(SR4CLOCK, OUTPUT);
        pinMode(SR4DATA, INPUT);
    }
}
