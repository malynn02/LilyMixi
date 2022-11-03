// Rotary Encoder Functions

// Initialize Rotary Encoders (First Two Values are Rotary Pin A and Rotary Pin B 
AiEsp32RotaryEncoder rot1 = AiEsp32RotaryEncoder(27, 26, 13, -1, 4);     
AiEsp32RotaryEncoder rot2 = AiEsp32RotaryEncoder(25, 33, 13, -1, 4);    
AiEsp32RotaryEncoder rot3 = AiEsp32RotaryEncoder(35, 32, 13, -1, 4);   

int rotaryPrev[] = {0, 0, 0}; // Previous Global Value of Rotary Encoder

// Reads Rotary Encoder State
void IRAM_ATTR readEncoderISR(){
  rot1.readEncoder_ISR();
  rot2.readEncoder_ISR();
  rot3.readEncoder_ISR();
}

// Initialize Rotary Encoders
void initRotary(){
  rot1.begin();
  rot1.setup(readEncoderISR);
  rot1.setAcceleration(250);           // 0/1 Disable, 250 - High Acceleration

  rot2.begin();
  rot2.setup(readEncoderISR);
  rot2.setAcceleration(250);           // 0/1 Disable, 250 - High Acceleration

  rot3.begin();
  rot3.setup(readEncoderISR);
  rot3.setAcceleration(250);           // 0/1 Disable, 250 - High Acceleration
}


// Update and Light Rotary Controls
void rotaryMIDIControls(){
  // Update Rotary Controls
  if (rot1.encoderChanged()){
    int newRotary = rot1.readEncoder();         // Get Current Rotary
    int lastRotary = rotaryPrev[0];             // Get Last Rotary
    int diffRotary = newRotary - lastRotary;    // Get Difference Between Both
    rotaryPrev[0] = newRotary;                  // Update Last Rotary w/ New

    int saveRotary = constrain(systemStatus[curStatus][6] + diffRotary, 0, 127);
    systemStatus[curStatus][6] = saveRotary;
    updateMIDI(curStatus, 6, saveRotary);
  }

  if (rot2.encoderChanged()){
    int newRotary = rot2.readEncoder();         // Get Current Rotary
    int lastRotary = rotaryPrev[1];             // Get Last Rotary
    int diffRotary = newRotary - lastRotary;    // Get Difference Between Both
    rotaryPrev[1] = newRotary;                  // Update Last Rotary w/ New

    int saveRotary = constrain(systemStatus[curStatus][7] + diffRotary, 0, 127);
    systemStatus[curStatus][7] = saveRotary;
    updateMIDI(curStatus, 7, saveRotary);
  }  

  if (rot3.encoderChanged()){
    int newRotary = rot3.readEncoder();         // Get Current Rotary
    int lastRotary = rotaryPrev[2];             // Get Last Rotary
    int diffRotary = newRotary - lastRotary;    // Get Difference Between Both
    rotaryPrev[2] = newRotary;                  // Update Last Rotary w/ New

    int saveRotary = constrain(systemStatus[curStatus][8] + diffRotary, 0, 127);
    systemStatus[curStatus][8] = saveRotary;
    updateMIDI(curStatus, 8, saveRotary);
  }
    
  for (int i = 0; i < 3; i++){lightRotary(i);}          // Light Up Rotary Conrols
}
