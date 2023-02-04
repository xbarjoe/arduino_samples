#include <Control_Surface.h>

USBMIDI_Interface midi;

using namespace MIDI_Notes;

CCPotentiometer photo = {
 2,
 CHANNEL_1
};
void setup() {
  Control_Surface.begin();

}

void loop() {
  Control_Surface.loop();

}
