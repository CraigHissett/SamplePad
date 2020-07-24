#include <SoftwareSerial.h>

//SoftwareSerial mySerial(5, 6); // Change to whatever you hooked
                                 // RX, TX up to

void setup() {
 //mySerial.begin(115200);
 Serial.begin(115200);
 pinMode(A1, INPUT);
}

void loop() {

  Serial.print("Pad1: ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.println(0); 

  Serial.print("Pad2: ");
  Serial.print(analogRead(A2));
  Serial.print(" ");
  Serial.println(0);
    
  Serial.print("Pad3: ");
  Serial.print(analogRead(A3));
  Serial.print(" ");
  Serial.println(0);
   
  Serial.print("Pad4: ");
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.println(0);  
  delay(100);
}
