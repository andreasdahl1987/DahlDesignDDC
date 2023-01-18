
void matrix()
{

    //Beginning with matrix logics, checking status on all button connectors.
    //Based on monitoring the flow to each row pin, setting the pin to GND

    for (uint8_t i = 0; i < rowCount; i++) //Engaging row pin after row pin
    {
        if (row[i] < 99)
        {
            pinMode(row[i], OUTPUT);
            digitalWrite(row[i], LOW);

            for (uint8_t u = 0; u < colCount; u++) //Checking all column pins on this row pin
            {
                if (col[u] < 99)
                {
                    rawState[i][u] = !digitalRead(col[u]);
                }
            }
            pinMode(row[i], INPUT_PULLUP); //Disengage the row pin
        }
    }
}
