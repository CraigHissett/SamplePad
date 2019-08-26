void Init_Definitions()
{
  // Rotary encoder declarations
static int pinA = 2; // Our first hardware interrupt pin is digital pin 2
static int pinB = 3; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent
// Button reading, including debounce without delay function declarations
const byte buttonPin = 4; // this is the Arduino pin we are connecting the push button to
byte oldButtonState = HIGH;  // assume switch open because of pull-up resistor
const unsigned long debounceTime = 80;  // milliseconds - was 10
unsigned long buttonPressTime;  // when the switch last changed state
boolean buttonPressed = 0; // a flag variable
// Menu and submenu/setting declarations
byte Mode = 0;   // This is which menu mode we are in at any given time (top level or one of the submenus)
const byte modeMax = 2; // This is the number of submenus/settings you want
/* Note: you may wish to change settingN etc to int, float or boolean to suit your application. 
 Remember to change "void setADisplayModeLCDn(byte name,*BYTE* setting)" to match and probably add some 
 "modeMax"-type overflow code in the "if(Mode == N && buttonPressed)" section*/

#define ROT_LEDG 5
#define ROT_LEDR 6

  // some other similar stuff:
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address is 0x27, migh need to change that and/or other arguments

int BankNo = 1;
int Volume = 100;

char mIntro1[]="Hello Dave";
char mIntro2[]="Flytes FTW";  
char mBank[]="Bank:";
char mVol[]= "Volume:";
// above are constant strings used on the LCD 

volatile byte inputMode = 0;              // some flag connected to changing the user input values
volatile boolean rotary_change = false;   // will turn true if rotary_counter has changed

const byte Pad1m = A0;                  // Pad 1, main pad
const byte Pad1r = A1;                  // Pad 1, rim shot
const byte Pad2m = A2;
const byte Pad2r = A3;
const byte Pad3m = A4;
const byte Pad3r = A5;
}

void Setup_Config()
{
  
}
