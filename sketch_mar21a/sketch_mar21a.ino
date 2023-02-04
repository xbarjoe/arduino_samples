#include <Control_Surface.h>
USBMIDI_Interface midi; 

CCPotentiometer pot = { A0, MIDI_CC::General_Purpose_Controller_1 };
CCPotentiometer pot2 = { A1, MIDI_CC::General_Purpose_Controller_2 };
 
void setup() {
Control_Surface.begin();
}
void loop() {
Control_Surface.loop();
}
