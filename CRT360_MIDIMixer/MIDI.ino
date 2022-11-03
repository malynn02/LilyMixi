// MIDI Functions

// Initialize Bluetooth MIDI Connection with Computer
void initMIDI(){
  BLEMidiServer.begin("lilyMIXI"); // Name the MIDI Connection
}

// Given a channel (ch), control (ct), and value (v), updates the MIDI
void updateMIDI(int ch, int ct, int v){
  if(BLEMidiServer.isConnected()) {
    BLEMidiServer.controlChange(ch, ct, v);
  }
}
