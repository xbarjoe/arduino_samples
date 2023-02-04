#include <Control_Surface.h> // Include the Control Surface library
 
// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;
 
using namespace MIDI_Notes;
 
// Instantiate a NoteButton object
NoteButton button = {
  5,                       // Push button on pin 5
  {note(C, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
 
void setup() {
  Control_Surface.begin(); // Initialize Control Surface
}
 
void loop() {
  Control_Surface.loop(); // Update the Control Surface
}
