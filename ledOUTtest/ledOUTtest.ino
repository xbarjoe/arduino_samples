#include <Control_Surface.h> // Include the Control Surface library
 
// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;
 
// Instantiate the LED that will light up when middle C is playing
NoteLED led {
  LED_BUILTIN,                 // Pin of built-in LED
  {MIDI_Notes::C(4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
 
void setup() {
  Control_Surface.begin(); // Initialize Control Surface
}
 
void loop() {
  Control_Surface.loop(); // Update the Control Surface
}
