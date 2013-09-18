// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!
 
#include <Adafruit_NeoPixel.h>
 
#define PIN 4

int inputPin1 = 5;  // A
int inputPin2 = 7;  // B

int val1 = 0, val2 = 0;
int oldVal1 = 0, oldVal2 = 0;
int pos = 0, oldPos = 0;
int turn = 0, oldTurn = 0, turnCount=0;
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);
 
uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFFFFFF; // Start red
uint32_t prevTime;

int  i;

uint32_t
  iColor[16][3];      // Background colors for eyes
int16_t
  hue          =   0; // Initial hue around perimeter (0-1535)
 
void setup() {
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
  prevTime = millis();
  
  pinMode(inputPin1, INPUT);
  digitalWrite(inputPin1, HIGH);
  pinMode(inputPin2, INPUT);
  digitalWrite(inputPin2, HIGH);
  Serial.begin(9600);
  
  pixels.show();
}
 
void sparkle() {
  int sparklepixel = random(30);
  pixels.setPixelColor(sparklepixel, 0x0000ff);
  int sparklepixel2 = random(30);
  pixels.setPixelColor(sparklepixel2, 0xffffff);
  pixels.show();
  pixels.setPixelColor(sparklepixel, 0);
  pixels.setPixelColor(sparklepixel2, 0);
  delay(50);
}

 
void loop() {
  
  sparkle();
  
  val1 = digitalRead(inputPin1);
  val2 = digitalRead(inputPin2);
  
    uint8_t r, g, b1;

  
    // Detect changes
  if ( val1 != oldVal1 || val2 != oldVal2) {
    
      //for each pair there's a position out of four
    if      ( val1 == 1 && val2 == 1 ) // stationary position
      pos = 0;
    else if ( val1 == 0 && val2 == 1 )
      pos = 1;
    else if ( val1 == 0 && val2 == 0 )
      pos = 2;
    else if ( val1 == 1 && val2 == 0 )
      pos = 3;
    
    turn = pos-oldPos;
    
    if (abs(turn) != 2) // impossible to understand where it's turning otherwise.
      if (turn == -1 || turn == 3)
        turnCount++;
      else if (turn == 1 || turn == -3)
        turnCount--;
    
    if (pos == 0){ // only assume a complete step on stationary position
      if (turnCount > 0) {
        Serial.print("<");
        ++i;
      }
      else if (turnCount < 0) {
        Serial.print(">");
        --i;
      }
      turnCount=0;
    }
    
    oldVal1 = val1;
    oldVal2 = val2;
    oldPos  = pos;
    oldTurn = turn;
    
    if (i >= 30) {
      i = 0;
    }
    
    if (i < 0) {
      i = 29;
    }





///////////rotating lights
  pixels.setPixelColor(30 - i, 0xff0000);
  pixels.setPixelColor(29 - i, 0x800000);
  pixels.setPixelColor(28 - i, 0x400000);
  pixels.setPixelColor(27 - i, 0x0d0000);
  pixels.setPixelColor(i, 0xffffff);
  pixels.show();
  pixels.setPixelColor(30 - i, 0);
  pixels.setPixelColor(29 - i, 0);
    pixels.setPixelColor(28 - i, 0);
  pixels.setPixelColor(27 - i, 0);

  pixels.setPixelColor(i, 0);
  }
}


