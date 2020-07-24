void Setup_Inputs()
{
    // Initialize initial values.
  for (int i=0; i<ANALOG_PIN_COUNT; ++i) {
    pinMode(analogPins[i], INPUT);
    padValues[i] = readPads(analogPins[i]);
  }
}

int readPads(int pin) {
  // Convert from 10bit value to 7bit.
  return analogRead(pin) >> 3;
}


void CheckPads()
{
  for (int i=0; i<ANALOG_PIN_COUNT; ++i)
    {
      padValues[i] = readPads(analogPins[i]);
      if(padValues[i]>10)
      {
        PlaySound(analogPins[i], padValues[i]);    
      }
    }
}
