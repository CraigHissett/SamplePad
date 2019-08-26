void Setup_Interface()
{
  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(digitalPinToInterrupt(2),PinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(3),PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
  
  pinMode (buttonPin, INPUT_PULLUP); // setup the button pin
  pinMode(ROT_LEDG, OUTPUT);
  pinMode(ROT_LEDR, OUTPUT);

  digitalWrite(ROT_LEDR, HIGH);
  digitalWrite(ROT_LEDG, HIGH);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(mIntro1);
  lcd.setCursor(0,1);
  lcd.print(mIntro2); 
  delay(5000);
  DisplayModeLCD(mBank,mVol,BankNo,Volume);
}


void updateMenu() {
  //DisplayModeLCD(mBank,mVol,BankNo,Volume);
  
  byte buttonState = digitalRead (buttonPin); 
  if (buttonState != oldButtonState){
    if (millis () - buttonPressTime >= debounceTime){
      buttonPressTime = millis ();
      oldButtonState =  buttonState;
      if (buttonState == LOW){
        buttonPressed = 1;
      }
      else {
        buttonPressed = 0;  
      }  
    }  
  }

  if (buttonPressed == 1)
  //Change input mode; 0 for volume (default), 1 for Bank No
  {
    if (inputMode == 0) {
      inputMode = 1;
    }
    else{
      inputMode = 0;
    }
    //Setcursor value to show selected
  }
  else
  {
    //Crack on
  }

  SetValueCursor();

    if (rotary_change == true){
      
      ChangeValue(Volume,1);  
      ChangeValue(BankNo,0);
      rotary_change = false;
    }
}


void rotaryIRQ()
{
  // Process input from the rotary encoder.
  // The rotary "position" is held in rotary_counter, increasing for CW rotation (changes by one per detent).
  // If the position changes, rotary_change will be set true. (You may manually set this to false after handling the change).

  // This function will automatically run when rotary encoder input A transitions in either direction (low to high or high to low)
  // By saving the state of the A and B pins through two interrupts, we'll determine the direction of rotation
  // int rotary_counter will be updated with the new value, and boolean rotary_change will be true if there was a value change
  // Based on concepts from Oleg at circuits@home (http://www.circuitsathome.com/mcu/rotary-encoder-interrupt-service-routine-for-avr-micros)
  // Unlike Oleg's original code, this code uses only one interrupt and has only two transition states;
  // it has less resolution but needs only one interrupt, is very smooth, and handles switchbounce well.

  static unsigned char rotary_state = 0; // current and previous encoder states
  rotary_state <<= 2;  // remember previous state
  rotary_state |= (digitalRead(PinA) | (digitalRead(PinB) << 1));  // mask in current state
  rotary_state &= 0x0F; // zero upper nybble

  //Serial.println(rotary_state,HEX);

  if (rotary_state == 0x09) // from 10 to 01, increment counter. Also try 0x06 if unreliable
  {
    //rotary_counter++;
    rotary_change = true;
    if(inputMode==0){
      Volume++;
    }
    else
    {
      BankNo++;
    }
  }
  else if (rotary_state == 0x03) // from 00 to 11, decrement counter. Also try 0x0C if unreliable
  {
    //rotary_counter--;
    rotary_change = true;
    if(inputMode==0){
      Volume--;
    }
    else
    {
      BankNo--;
    }
  }
}


void DisplayModeLCD(char v1[],char v2[],int val1,int val2) 
{
  lcd.clear();
  char val1s[4];
  char val2s[4];
  sprintf(val1s,"%d",val1);
  sprintf(val2s,"%d",val2);
  lcd.home();
  lcd.print(v1);
  if (val1 != -27) {
    lcd.setCursor(13,0);
    lcd.print(val1s);
  }
  lcd.setCursor(0,1);
  lcd.print(v2);
  if (val2 != -27) {
    lcd.setCursor(13,1);
    lcd.print(val2s);
  }
}

void ChangeValue(int val,byte r) //ChangeValue
{
  char str[4];
  lcd.setCursor(13,r);
  lcd.print("   ");
  sprintf(str,"%d",val);
  lcd.setCursor(13,r);
  lcd.print(str);
}

void SetValueCursor() // the ">" sign when changing values 
{
  if (inputMode == 0) {
    lcd.setCursor(12,0);
    lcd.print(" ");
    lcd.setCursor(12,1);
    lcd.print(">");
  }
  else {
    lcd.setCursor(12,1);
    lcd.print(" ");
    lcd.setCursor(12,0);
    lcd.print(">");
  }
}



//Rotary encoder interrupt service routine for one encoder pin
void PinA(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  //if(reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    rotary_change = true;
    if(inputMode==0){
      Volume--;
    }
    else
    {
      BankNo--;
    }
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  //}
  //else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

//Rotary encoder interrupt service routine for the other encoder pin
void PinB(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  //if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    rotary_change = true;
        if(inputMode==0){
      Volume++;
    }
    else
    {
      BankNo++;
    }
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  //}
  //else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}
