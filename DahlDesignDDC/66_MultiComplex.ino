void multiFunction2Bit24(int analogPin, int switchNumber, int row, int column, bool reverseAnalog, bool reverse2Bit, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;

    int N = switchNumber - 1;

    int Number;

    int Row = row - 1;
    int Column = column - 1;

    //READ POSITION OF 12-POS ANALOG SWITCH

    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int resultAnalog = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            resultAnalog++;
            differ = abs(positions[i] - value);
        }
    }

    resultAnalog--;

    if (reverseAnalog)
    {
      resultAnalog = 11 - resultAnalog;
    }

    analogLastCounter[N] = resultAnalog;

    //Update button number to use

    Number = analogButtonNumber[N] + (resultAnalog * 2);

    //ENCODER POSITION AND DEBOUNCE

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];

    bool array[2] = { Pin1, Pin2 };

    int pos = 0;

    for (int i = 0; i < 2; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > (encoder2Wait + encoder2Pulse + encoderCooldown))
        {
            switchTimer[Row][Column] = globalClock;
            latchLock[Row][Column] = true;
        }
        else if ((globalClock - switchTimer[Row][Column] > encoder2Wait) && latchLock[Row][Column])
        {
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //Make sure we dont do this again
            latchLock[Row][Column] = false;
        }
    }

    int difference = pushState[Row][Column + 1];
    if (difference != 0)
    {
        if (globalClock - switchTimer[Row][Column + 1] < encoder2Pulse + encoder2Wait)
        {
            if ((difference > 0 && difference < 2) || difference < -2)
            {
                Joystick.setButton(Number + reverse2Bit, 1);
                Joystick.setButton(Number + 1 - reverse2Bit, 0);
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                Joystick.setButton(Number + reverse2Bit, 0);
                Joystick.setButton(Number + 1 - reverse2Bit, 1);
            }
            else
            {
                pushState[Row][Column + 1] = 0;
            }
        }
        else
        {
            pushState[Row][Column + 1] = 0;
            pushState[Row][Column] = result;
            Joystick.setButton(Number, 0);
            Joystick.setButton(Number + 1, 0);
        }
    }

}
void multiFunction2Bit36(int analogPin, int switchNumber, int row, int column, bool reverseAnalog, bool reverse2Bit, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;

    int N = switchNumber - 1;

    int Number = analogButtonNumber[N];

    int Row = row - 1;
    int Column = column - 1;

    //READ POSITION OF 12-POS ANALOG SWITCH

    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int resultAnalog = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            resultAnalog++;
            differ = abs(positions[i] - value);
        }
    }

    resultAnalog--;

    if (reverseAnalog)
    {
      resultAnalog = 11 - resultAnalog;
    }

    analogLastCounter[N] = resultAnalog;

    analogTempState[N] = 0; //Refreshing encoder mode difference

    for (int i = 0; i < 12; i++)
    {
        if (i == resultAnalog)
        {
            Joystick.pressButton(i + Number + 24);
        }
        else
        {
            Joystick.releaseButton(i + Number + 24);
        }
    }

    //Update button number to use

    Number = Number + (resultAnalog * 2);

    //ENCODER POSITION AND DEBOUNCE

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];

    bool array[2] = { Pin1, Pin2 };

    int pos = 0;

    for (int i = 0; i < 2; i++)
    {
        if (array[i])
        {
            pos |= (1 << i);
        }
    }

    pos = pos ^ (pos >> 1);

    int result = pos;

    //Short debouncer on switch rotation

    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > (encoder2Wait + encoder2Pulse + encoderCooldown))
        {
            switchTimer[Row][Column] = globalClock;
            latchLock[Row][Column] = true;
        }
        else if ((globalClock - switchTimer[Row][Column] > encoder2Wait) && latchLock[Row][Column])
        {
            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //Make sure we dont do this again
            latchLock[Row][Column] = false;
        }
    }

    int difference = pushState[Row][Column + 1];
    if (difference != 0)
    {
        if (globalClock - switchTimer[Row][Column + 1] < encoder2Pulse + encoder2Wait)
        {
            if ((difference > 0 && difference < 2) || difference < -2)
            {
                Joystick.setButton(Number + reverse2Bit, 1);
                Joystick.setButton(Number + 1 - reverse2Bit, 0);
            }
            else if ((difference < 0 && difference > -2) || difference > 2)
            {
                Joystick.setButton(Number + reverse2Bit, 0);
                Joystick.setButton(Number + 1 - reverse2Bit, 1);
            }
            else
            {
                pushState[Row][Column + 1] = 0;
            }
        }
        else
        {
            pushState[Row][Column + 1] = 0;
            pushState[Row][Column] = result;
            Joystick.setButton(Number, 0);
            Joystick.setButton(Number + 1, 0);
        }
    }

}
void multiFunction2Button24(int analogPin, int switchNumber, int rowButton1, int columnButton1, int rowButton2, int columnButton2, bool reverse, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;

    int N = switchNumber - 1;

    int Number = analogButtonNumber[N];

    int RowButton1 = rowButton1 - 1;
    int ColumnButton1 = columnButton1 - 1;
    int RowButton2 = rowButton2 - 1;
    int ColumnButton2 = columnButton2 - 1;

    //READ POSITION OF 12-POS ANALOG SWITCH

    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int resultAnalog = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            resultAnalog++;
            differ = abs(positions[i] - value);
        }
    }

    resultAnalog--;

    if (reverse)
    {
        resultAnalog = 11 - resultAnalog;
    }

    analogLastCounter[N] = resultAnalog;

    //Update button number to use

    Number = analogButtonNumber[N] + (resultAnalog * 2);

    //Button logics

    //Button1
    if (pushState[RowButton1][ColumnButton1] != rawState[RowButton1][ColumnButton1] && (globalClock - switchTimer[RowButton1][ColumnButton1]) > buttonCooldown)
    {
        switchTimer[RowButton1][ColumnButton1] = globalClock;
        pushState[RowButton1][ColumnButton1] = rawState[RowButton1][ColumnButton1];
    }

    if ((globalClock - switchTimer[RowButton1][ColumnButton1]) > buttonCooldown)
    {
        pushState[RowButton1][ColumnButton1] = rawState[RowButton1][ColumnButton1];
    }

    Joystick.setButton(Number, pushState[RowButton1][ColumnButton1]);

    //Button2
    if (pushState[RowButton2][ColumnButton2] != rawState[RowButton2][ColumnButton2] && (globalClock - switchTimer[RowButton2][ColumnButton2]) > buttonCooldown)
    {
        switchTimer[RowButton2][ColumnButton2] = globalClock;
        pushState[RowButton2][ColumnButton2] = rawState[RowButton2][ColumnButton2];
    }

    if ((globalClock - switchTimer[RowButton2][ColumnButton2]) > buttonCooldown)
    {
        pushState[RowButton2][ColumnButton2] = rawState[RowButton2][ColumnButton2];
    }

    Joystick.setButton(Number + 1, pushState[RowButton2][ColumnButton2]);

}
void multiFunction2Button36(int analogPin, int switchNumber, int rowButton1, int columnButton1, int rowButton2, int columnButton2, bool reverse, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12)
{
    int Pin = analogPin;
    int Pos1 = pos1;
    int Pos2 = pos2;
    int Pos3 = pos3;
    int Pos4 = pos4;
    int Pos5 = pos5;
    int Pos6 = pos6;
    int Pos7 = pos7;
    int Pos8 = pos8;
    int Pos9 = pos9;
    int Pos10 = pos10;
    int Pos11 = pos11;
    int Pos12 = pos12;

    int N = switchNumber - 1;

    int Number = analogButtonNumber[N];

    int RowButton1 = rowButton1 - 1;
    int ColumnButton1 = columnButton1 - 1;
    int RowButton2 = rowButton2 - 1;
    int ColumnButton2 = columnButton2 - 1;

    //READ POSITION OF 12-POS ANALOG SWITCH

    int value = analogRead(Pin);

    int positions[12] = { Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8, Pos9, Pos10, Pos11, Pos12 };

    int differ = 0;
    int resultAnalog = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            resultAnalog++;
            differ = abs(positions[i] - value);
        }
    }

    resultAnalog--;

    if (reverse)
    {
        resultAnalog = 11 - resultAnalog;
    }
        
    analogLastCounter[N] = resultAnalog;

    analogTempState[N] = 0; //Refreshing encoder mode difference

    for (int i = 0; i < 12; i++)
    {
        if (i == resultAnalog)
        {
            Joystick.pressButton(i + Number + 24);
        }
        else
        {
            Joystick.releaseButton(i + Number + 24);
        }
    }

    //Update button number to use

    Number = analogButtonNumber[N] + (resultAnalog * 2);

    //Button logics

    //Button1
    if (pushState[RowButton1][ColumnButton1] != rawState[RowButton1][ColumnButton1] && (globalClock - switchTimer[RowButton1][ColumnButton1]) > buttonCooldown)
    {
        switchTimer[RowButton1][ColumnButton1] = globalClock;
        pushState[RowButton1][ColumnButton1] = rawState[RowButton1][ColumnButton1];
    }

    if ((globalClock - switchTimer[RowButton1][ColumnButton1]) > buttonCooldown)
    {
        pushState[RowButton1][ColumnButton1] = rawState[RowButton1][ColumnButton1];
    }

    Joystick.setButton(Number, pushState[RowButton1][ColumnButton1]);

    //Button2
    if (pushState[RowButton2][ColumnButton2] != rawState[RowButton2][ColumnButton2] && (globalClock - switchTimer[RowButton2][ColumnButton2]) > buttonCooldown)
    {
        switchTimer[RowButton2][ColumnButton2] = globalClock;
        pushState[RowButton2][ColumnButton2] = rawState[RowButton2][ColumnButton2];
    }

    if ((globalClock - switchTimer[RowButton2][ColumnButton2]) > buttonCooldown)
    {
        pushState[RowButton2][ColumnButton2] = rawState[RowButton2][ColumnButton2];
    }

    Joystick.setButton(Number + 1, pushState[RowButton2][ColumnButton2]);

}
