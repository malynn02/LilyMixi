// DMX Functions

int devices[] = {13, 13};  // List number of channels per device
                           // Device 0 set to channel 1, Device 1 set to channel 14
dmx_port_t dmxPort = 1;
byte data[DMX_MAX_PACKET_SIZE];

// Initialize DMX
void initDMX(){
  dmx_config_t dmxConfig = DMX_DEFAULT_CONFIG;
  dmx_param_config(dmxPort, &dmxConfig);
  dmx_set_pin(dmxPort, 17, 16, 21);       // TX Pin 17, RX Pin 16, EN Pin 21
  dmx_driver_install(dmxPort, DMX_MAX_PACKET_SIZE, 0, NULL, 1);
  dmx_set_mode(dmxPort, DMX_MODE_WRITE);
  data[0] = 0;  // Set Initial Data Value to Zero
}

// Sends a given value to a given channel on a given address
void setDMX(int addr, int channel, int val){
  int offset = 0;
  for (int i = 0; i < addr; i++){offset += devices[i];}
  int reg = offset + channel;
  data[reg] = val;
  dmx_write_packet(dmxPort, data, DMX_MAX_PACKET_SIZE);
}

void writeDMX(){
  dmx_send_packet(dmxPort, DMX_MAX_PACKET_SIZE);
  dmx_wait_send_done(dmxPort, DMX_PACKET_TIMEOUT_TICK);
}

int lastScene = -1;

// Find Current Lighting Scene and Run It
void runDMX(){
  int whichScene = -1;
  for(int i = 1; i < 6; i++){
    int thisScene = systemStatus[5][i];
    if(thisScene == 1){whichScene = i;}
  }
  if(whichScene != lastScene){clearDMX(); lastScene = whichScene;}
  
  switch(whichScene){
    case 1: blackout(); break;
    case 2: green(); break;
    case 3: blue(); break;
    case 4: sound(); break;
    case 5: strobe(); break;
  }
}

// SCENES
void blackout(){
  setDMX(0, 6, 0); // Set Device 0 Master Fade to 255
  setDMX(1, 6, 0); // Set Device 1 Master Fade to 255
  writeDMX();        // Send Configuration
}

void red(){
  setDMX(0, 6, 255); // Set Device 0 Master Fade to 255
  setDMX(1, 6, 255); // Set Device 1 Master Fade to 255
  setDMX(0, 8, 255); // Set Device 0 Red to 255
  setDMX(1, 8, 255); // Set Device 1 Red to 255
  writeDMX();        // Send Configuration
}

void green(){
  setDMX(0, 6, 255); // Set Device 0 Master Fade to 255
  setDMX(1, 6, 255); // Set Device 1 Master Fade to 255
  setDMX(0, 9, 255); // Set Device 0 Green to 255
  setDMX(1, 9, 255); // Set Device 1 Green to 255
  writeDMX();        // Send Configuration
}

void blue(){
  setDMX(0, 6, 255); // Set Device 0 Master Fade to 255
  setDMX(1, 6, 255); // Set Device 1 Master Fade to 255
  setDMX(0, 10, 255); // Set Device 0 Blue to 255
  setDMX(1, 10, 255); // Set Device 1 Blue to 255
  writeDMX();        // Send Configuration
}

void sound(){
  setDMX(0, 6, 255); // Set Device 0 Master Fade to 255
  setDMX(1, 6, 255); // Set Device 1 Master Fade to 255
  setDMX(0, 12, 100); // Set Device 0 Master Fade to 255
  setDMX(1, 12, 100); // Set Device 1 Master Fade to 255
  writeDMX();        // Send Configuration
}

void strobe(){
  setDMX(0, 6, 255); // Set Device 0 Master Fade to 255
  setDMX(1, 6, 255); // Set Device 1 Master Fade to 255
  setDMX(0, 11, 255); // Set Device 0 Master Fade to 255
  setDMX(1, 11, 255); // Set Device 1 Master Fade to 255
  setDMX(0, 7, 255); // Set Device 0 Master Fade to 255
  setDMX(1, 7, 255); // Set Device 1 Master Fade to 255
  writeDMX();        // Send Configuration
}

void clearDMX(){
  for (int i = 0; i < 13; i++){
    setDMX(0, i, 0);
    setDMX(1, i, 0);
  }
}
