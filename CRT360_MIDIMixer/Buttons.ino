// Button Functions

int numButtons = 6;                                       // Number of Buttons
const uint8_t buttonPins[6] = {2, 18, 22, 23, 19, 15};    // Pin Assignments for Buttons (in order)
Bounce * buttons = new Bounce[6];                         // Bounce Array for Buttons

// Initializes All Buttons
void initButtons(){
  for (int i = 0; i < numButtons; i++){
    buttons[i].attach(buttonPins[i], INPUT);
    buttons[i].interval(25);
  }
}

// Returns the Value of the Button Pressed
int getButton(){
  int whichButton = -1;
  for (int i = 0; i < numButtons; i++){
    buttons[i].update();
    if (buttons[i].rose() ) {
      whichButton = i;
    }
  }
  return whichButton;
}

// Shows Button Controls in MIDI Menus
void buttonMIDIControls(){
  lightButton(0, systemColors[0], 4);                                 // Set Home Button to its color
  int bPress = getButton();                                           // Get Any Button Presses
  if(bPress == -1){}                                                  // Do Nothing if No Buttons Pressed
  if(bPress == 0){curStatus = 0;}                                     // Return Home
  else{                                                               // Change Button State
    int curButtonStatus = systemStatus[curStatus][bPress];            // Get Current State of Button Pressed
    if(curButtonStatus == 0){systemStatus[curStatus][bPress] = 127;}  // If Current Value is 0, Change to 127
    else{systemStatus[curStatus][bPress] = 0;}                        // Otherwise, Change to 0

    int newButtonStatus = systemStatus[curStatus][bPress];            // Get New Button Status
    updateMIDI(curStatus, bPress, newButtonStatus);                   // Send New Button Status to MIDI
  }

  // Light Up All Buttons
  for (int i = 0; i < 5; i++){
    int thisButton = i + 1;                                                    // Skip Button 0 (Menu Button)
    int curState = systemStatus[curStatus][thisButton];                        // Get State of the Button
    if(curState == 0){lightButton(thisButton, systemColors[curStatus], 1);}    // If 0, Only Light up 1 LED
    else{lightButton(thisButton, systemColors[curStatus], 4);}                 // If 127, Light up 4 LEDs
  }
}

// Shows Button Controls in DMX Menu
void buttonDMXControls(){
  lightButton(0, systemColors[0], 4);                           // Set Home Button to its color
  int bPress = getButton();                                     // Get Any Button Presses
  if(bPress == -1){}                                            // Do Nothing if No Buttons Pressed
  else if(bPress == 0){curStatus = 0;}                          // Return Home
  else{                                                         // Change Button State
    for(int i = 1; i < 6; i++){systemStatus[curStatus][i] = 0;} // Set All States to 0
    systemStatus[curStatus][bPress] = 1;                        // Set Button State to 1
  }
  
  // Light Up All Buttons
  for (int i = 0; i < 5; i++){
    int thisButton = i + 1;                                                    // Skip Button 0 (Menu Button)
    int curState = systemStatus[curStatus][thisButton];                        // Get State of the Button
    if(curState == 0){lightButton(thisButton, systemColors[curStatus], 1);}    // If 0, Only Light up 1 LED
    else{lightButton(thisButton, systemColors[curStatus], 4);}                 // If 127, Light up 4 LEDs
  }
}
