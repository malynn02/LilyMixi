// System Functions

// Run Startup Animation
void startUp(){
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 48; j++){
      int r = random(10);
      if(r == 0){strip.setPixelColor(j, 255, 0, 255);}
      else if(r == 1){strip.setPixelColor(j, 255, 255, 255);}
      else{strip.setPixelColor(j, 0, 0, 0);}
    }
    strip.show();
    delay(100);
  }
  strip.clear(); strip.show();
  curStatus = 0;  // Advance to Main Menu
}

// Run Main Menu
void mainMenu(){
  // Light All Menu Buttons
  for (int i = 0; i < 5; i++){lightButton(i + 1, systemColors[i + 1], 4);}
  
  // Get Button Press to Change State
  int bPress = getButton();
  if(bPress != -1){curStatus = bPress;}
}

// Run MIDI Menus
void midiMenu(){
  buttonMIDIControls();
  rotaryMIDIControls();
}

// Run DMX Menu
void dmxMenu(){  
  buttonDMXControls();
  //rotaryControls();
}
