//------------------------------
//-----------SETUP--------------
//------------------------------

void setup()
{
    //Filling some arrays
    for (int i = 0; i < rowCount; i++)
    {
        for (int a = 0; a < colCount; a++)
        {
            rawState[i][a] = 0;
            pushState[i][a] = 0;
            latchLock[i][a] = 0;
            latchState[i][a] = 0;
            switchModeLock[i][a] = 0;
            switchTimer[i][a] = 0;
            toggleTimer[i][a] = 0;
        }
    }

    for (int u = 0; u < 10; u++)
    {
        analogLastCounter[u] = 0;
        analogTempState[u] = 0;
        analogLatchLock[u] = 0;
        analogTimer1[u] = 0;
        analogTimer2[u] = 0;
        analogRotaryCount[u] = 0;
        readIndex[u] = 0;
        total[u] = 0;
        average[u] = 0;

        for (int i = 0; i < reads; i++)
        {
            readings[u][i] = 0;
        }
    }



    //Ready the matrix

    for (int i = 0; i < colCount; i++)
    { //  All pins pulled up unless told otherwise
        pinMode(col[i], INPUT_PULLUP);
    }

    for (int i = 0; i < rowCount; i++)
    { //  All pins pulled up unless told otherwise
        pinMode(row[i], INPUT_PULLUP);
    }

    Joystick.begin(0); //Start joystick library magic

    Joystick.setZAxisRange(-32768, 32767); //Making bit fields 16 bit
    Joystick.setYAxisRange(-32768, 32767);

}
