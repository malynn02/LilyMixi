// MIDI Mixer
// RainbowPCB
// MIDI-Enabled MIDI Device

#include <Adafruit_NeoPixel.h>      // NeoPixel Library
#include <Bounce2.h>                // Bounce2 Library
#include "AiEsp32RotaryEncoder.h"   // Rotary Encoder Library
#include "Arduino.h"                // Arduino Library
#include <BLEMidi.h>                // Bluetooth MIDI Library
#include <esp_dmx.h>                // DMX Library

// Button & Rotary Arrays
int curStatus = -1;                      // System starts with a BOOT UP ANIMATION (curStatus -1)
int systemStatus[6][9] = {               // Tracks current status of each menu
// B0 B1 B2 B3 B4 B5 R1 B2 R3            // Button and Rotary Encoder States
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},  // MAIN MENU  (curStatus 0)
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},          // DRUMS      (curStatus 1)
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},          // TONES      (curStatus 2)
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},          // BASS       (curStatus 3)
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},          // SAMPLES    (curStatus 4)
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},          // LIGHTS     (curStatus 5)
};

int systemColors[6]{-1, 0, 50, 100, 150, 200};  // Menu Colors (Uses HSB Color Wheel 0 - 255)

void setup() {
  initPixels();   // Initialize LEDs
  initButtons();  // Initialize Buttons
  initRotary();   // Initialize Rotary Encoders
  initMIDI();     // Initialize MIDI
  initDMX();      // Initialize DMX
}

void loop() {
  switch(curStatus){
    case -1: startUp(); break;  // Start Up Animation
    case 0: mainMenu(); break;  // MAIN MENU
    case 1: midiMenu(); break;  // DRUMS
    case 2: midiMenu(); break;  // TONES
    case 3: midiMenu(); break;  // BASS
    case 4: midiMenu(); break;  // SAMPLES
    case 5: dmxMenu(); break;   // LIGHTS
  }
  runDMX();                     // Always be updating lights
}
