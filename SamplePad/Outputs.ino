void Setup_Outputs()
{
  SoftwareSerial Output1(22,23); // RX, TX
DFRobotDFPlayerMini DFPlayer1;
  SoftwareSerial Output2(24,25); // RX, TX
DFRobotDFPlayerMini DFPlayer2;
  SoftwareSerial Output3(26,27); // RX, TX
DFRobotDFPlayerMini DFPlayer3;
  SoftwareSerial Output4(28,29); // RX, TX
DFRobotDFPlayerMini DFPlayer4;

  Output1.begin(9600);
  Output2.begin(9600);
  Output3.begin(9600);
  Output4.begin(9600);

  Serial.println();
  Serial.println(F("SamplePad Controller"));
  Serial.println(F("Initializing DFPlayers ... (May take 3~5 seconds each)"));

  if (!DFPlayer1.begin(Output1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Output1 Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("Output1 online."));

  if (!DFPlayer2.begin(Output2)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Output2 Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("Output2 online."));

  if (!DFPlayer3.begin(Output3)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Output3 Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("Output3 online."));

  if (!DFPlayer3.begin(Output3)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Output3 Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("Output3 online."));
    
  DFPlayer1.setTimeOut(500); //Set serial communictaion time out 500ms
  DFPlayer2.setTimeOut(500);
  DFPlayer3.setTimeOut(500);
  DFPlayer4.setTimeOut(500);
  
  //----Set volume----
  DFPlayer1.volume(29);  //Set volume value (0~30).
  DFPlayer2.volume(29);
  DFPlayer3.volume(29);
  DFPlayer4.volume(29);
  //myDFPlayer.volumeUp(); //Volume Up
  //myDFPlayer.volumeDown(); //Volume Down

  //----Set different EQ----
//  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
//  myDFPlayer.EQ(DFPLAYER_EQ_POP);
//  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
//  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
//  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
//  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

  //----Set device we use SD as default----
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
  DFPlayer1.outputDevice(DFPLAYER_DEVICE_SD);
  DFPlayer2.outputDevice(DFPLAYER_DEVICE_SD);
  DFPlayer3.outputDevice(DFPLAYER_DEVICE_SD);
  DFPlayer4.outputDevice(DFPLAYER_DEVICE_SD);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);

  //----Mp3 control----
//  myDFPlayer.sleep();     //sleep
//  myDFPlayer.reset();     //Reset the module
  DFPlayer1.enableDAC();  //Enable On-chip DAC
  DFPlayer2.enableDAC();
  DFPlayer3.enableDAC();
  DFPlayer4.enableDAC();
//  myDFPlayer.disableDAC();  //Disable On-chip DAC
//  myDFPlayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15


//----Read imformation----
// Serial.println(myDFPlayer.readState()); //read mp3 state
// Serial.println(myDFPlayer.readVolume()); //read current volume
//  Serial.println(myDFPlayer.readEQ()); //read EQ setting
//  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
//  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
//  Serial.println(myDFPlayer.readFileCountsInFolder(3)); //read fill counts in folder SD:/03

}



void PlaySound (String PadName, int velocity) {
  //Get BankNo from Global variable
  //String to play - BankNo & "_" & PadName & ".wav"
  //Velocity will be used to determine % of Main volume to hit it at.
  //If Main Volume is 100 and pad is hit at half strength (map pad velocity against 0-100) resulting volume of hit will be 50.
  
  //myDFPlayer.play(ServerValue);
  
}
