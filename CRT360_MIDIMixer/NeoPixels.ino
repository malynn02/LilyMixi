// NeoPixel Functions
Adafruit_NeoPixel strip = Adafruit_NeoPixel(48, 13, NEO_GRB + NEO_KHZ800); // 48 Pixels on Pin 14

// NeoPixel Address Arrays for Buttons
int pixelButtons[6][4]{ // 6 Buttons w/ 4 LEDs Per Button
  {0, 1, 2, 3},         // BUTTON 1    
  {4, 5, 6, 7},         // BUTTON 2     
  {8, 9, 10, 11},       // BUTTON 3      
  {20, 21, 22, 23},     // BUTTON 4       
  {16, 17, 18, 19},     // BUTTON 5       
  {12, 13, 14, 15},     // BUTTON 6       
};

// NeoPixel Address Arrays for Rotary Encoders
int pixelRotary[3][8]{    // 3 Rotary Encoders w/ 8 LEDs Per Encoder           
  {32, 33, 34, 35, 36, 37, 38, 39}, // ROTARY 1    
  {24, 25, 26, 27, 28, 29, 30, 31}, // ROTARY 2    
  {40, 41, 42, 43, 44, 45, 46, 47}, // ROTARY 3    
};

// Initialize NeoPixels
void initPixels(){
  strip.begin();
  strip.setBrightness(100); // WARNING! Do not increase brightness (power issues will occur)
  strip.show();
}

// Clear All NeoPixels
void clearPixels(){
  strip.clear();
  strip.show();
}

// Test All NeoPixels
void testPixels(){
  for (int i = 0; i < 48; i++){strip.clear(); strip.setPixelColor(i, 100, 0, 0); strip.show(); delay(10);} 
  for (int i = 0; i < 48; i++){strip.clear(); strip.setPixelColor(i, 0, 100, 0); strip.show(); delay(10);}
  for (int i = 0; i < 48; i++){strip.clear(); strip.setPixelColor(i, 0, 0, 100); strip.show(); delay(10);}
}

// Light up a given button (b) with a given color (c: 0 - 255 -OR- -1 to White) 
// with a given number of pixels (n)
void lightButton(int b, int c, int n){
  int ledStart = pixelButtons[b][0];                                              // Get Starting LED
  for (int i = ledStart; i < ledStart + 4; i++){strip.setPixelColor(i, 0, 0, 0);} // Clear All Buttons
  for (int i = ledStart; i < ledStart + n; i++){
    if(c == -1){strip.setPixelColor(i, 255, 255, 255);}
    else{strip.setPixelColor(i, Wheel(c));}
  }
  strip.show();
}

// Light up a given rotary encoder (r)
void lightRotary(int rot){
  int thisColor = systemColors[curStatus];
  int r = rWheel(thisColor);
  int g = gWheel(thisColor);
  int b = bWheel(thisColor);
                                                      // Remember to offset by 6 to get right position in system
  int rotaryValue = systemStatus[curStatus][rot + 6]; // Current value of Rotary Encoder (0 - 127)
  int rotMax = 127;                                   // Max Rotary Encoder Value                    
  rotaryValue = constrain(rotaryValue, 0, rotMax);    // Make sure Rotary Value is Constrained

  int numLEDs = 8;                          // 8 LEDs per Rotary Encoder
  int ledStart = pixelRotary[rot][0];       // Which LED to start at
  int ledEnd = ledStart + numLEDs;          // Which LED to end at
  int ledStep = rotMax/numLEDs;             // Propotion of Rotary Encoder values to LEDs
  
  int fullLED = rotaryValue/ledStep;        // How many LEDs to light up
  fullLED = constrain(fullLED, 0, numLEDs); // Constrain fullLED
  int partLED = rotaryValue % ledStep;      // Partial LED
  
  float modifier = mapFloat(float(partLED), 0.0, float(ledStep), 0.0, 1.0); // Percentage Brightness
  float newR = float(r) * modifier;
  float newG = float(g) * modifier;
  float newB = float(b) * modifier;
  
  for (int i = 0; i < numLEDs; i++){
    int ledOffset = i + ledStart;
    if (i < fullLED){strip.setPixelColor(ledOffset, r, g, b);}
    else if (i == fullLED){strip.setPixelColor(ledOffset, newR, newG, newB);}
    else{strip.setPixelColor(ledOffset, 0, 0, 0);}    
  }
  strip.show();
}

// Return Color for Given Position on Color Wheel (WheelPos)
uint32_t Wheel(byte WheelPos){
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);}
  if(WheelPos < 170) {WheelPos -= 85; return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);}
  WheelPos -= 170; return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Return Red Value for Given Position on Color Wheel (WheelPos)
int rWheel(byte WheelPos){
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {return 255 - WheelPos * 3;}
  if(WheelPos < 170) {WheelPos -= 85; return 0;}
  WheelPos -= 170; return WheelPos * 3;
}

// Return Green Value for Given Position on Color Wheel (WheelPos)
int gWheel(byte WheelPos){
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {return 0;}
  if(WheelPos < 170) {WheelPos -= 85; return WheelPos * 3;}
  WheelPos -= 170; return 255 - WheelPos * 3;
}

// Return Blue Value for Given Position on Color Wheel (WheelPos)
int bWheel(byte WheelPos){
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {return WheelPos * 3;}
  if(WheelPos < 170) {WheelPos -= 85; return 255 - WheelPos * 3;}
  WheelPos -= 170; return 0;
}
