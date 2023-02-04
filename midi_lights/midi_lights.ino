#include <MIDI.h>

const int pinA = 12;
const int pinB = 11;
const int pinC = 10;

// Create an instance of the MIDI class
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);

  MIDI.begin(MIDI_CHANNEL_OMNI); // Listen to all MIDI channels
}

void loop() {
  if (MIDI.read()) {  // Check if there is incoming MIDI data
    // Get the MIDI message data
    byte type = MIDI.getType();
    byte note = MIDI.getData1();

    // Check the type of MIDI message
    if (type == 0x90) {
      // Check the note value
      if (note == 60) {  // C4
        digitalWrite(pinA, HIGH);
      } else if (note == 62) {  // D4
        digitalWrite(pinB, HIGH);
      } else if (note == 64) {  // E4
        digitalWrite(pinC, HIGH);
      }
    } else if (type == 0x80) {
      // Turn off the pin if the note is released
      if (note == 60) {  // C4
        digitalWrite(pinA, LOW);
      } else if (note == 62) {  // D4
        digitalWrite(pinB, LOW);
      } else if (note == 64) {  // E4
        digitalWrite(pinC, LOW);
      }
    }
  }
}
