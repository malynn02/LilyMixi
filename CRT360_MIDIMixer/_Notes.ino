/*

ISSUE --- Main menu red ring issue
TODO ---- rotaries for DMX

States                     Buttons                                                     Rotary
#   Name      Color        0         1         2         3         4         5         0         1         2
0   Loading   N/A         Batt      Drums     Tone      Bass      Samples   Lights    Volume    Balance   ???
1   Drums     Pink        Loading   Bass      Snare     Kick      Clap      Crash     
2   Tone      Yellow      Loading
3   Bass      Green       Loading
4   Samples   Blue        Loading
5   Lights    Cyan        Loading   Blackout  Strobe    Chase     Fade      Bright    Stobe Spd Chase Spd Bright

  Implement Battery Level in updateBattery()
  
  Red / Orange / Yellow / Green / Blue / Pink --- Make multidimensional states for all instruments


*****************************************************************************************
* DMX SETTINGS
*****************************************************************************************

MINI BEAM - Rotating Strobes
CH#   Value Range   Function
1     0 - 255       Pan Control
2     0 - 255       16-Bit Pan Control
3     0 - 255       Tilt Control
4     0 - 255       16-Bit Tilt Control
5     0 - 255       Movement Speed (Slow->Fast)
6     0 - 255       Master Dimming
7     0 - 255       Strobe (Slow->Fast)
8     0 - 255       Red Dimming
9     0 - 255       Green Dimming
10    0 - 255       Blue Dimming
11    0 - 255       White Dimming
12    0 - 30        No Effect
12    31 - 125      Fast Automatic Color Change Mode
12    126 - 249     Slow Automatic Color Change Mode
12    250 - 255     Sound Activated Color Change Mode
13    0 - 149       No Effect
13    150 - 255     Reset Unit

*****************************************************************************************

*/
