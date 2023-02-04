#include <Encoder.h>
#include<Control_Surface.h>

USBMIDI_Interface midi;  // Instantiate a MIDI Interface to use

CCRotaryEncoder rot = {
  {3, 5},                                   // Analog pin connected to potentiometer
   MCU::V_POT_1,
   1,// Channel volume of channel 1
};

void setup() {
  RelativeCCSender::setMode(relativeCCmode::MACKIE_CONTROL_RELATIVE);
  Control_Surface.begin(); // Initialize Control Surface
}
 
void loop() {
  Control_Surface.loop(); // Update the Control Surface
}
