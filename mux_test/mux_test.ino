#include <Control_Surface.h> // Include the Control Surface library
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#define DISPLAY_ADDRESS1 0x71


// How many NeoPixels are attached to the Arduino?


// Declare our NeoPixel strip object:

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;
 
//using namespace MIDI_Notes;
int cycles = 0;
CD74HC4067 mux1 = {8, {15,14,16,10}};
CCPotentiometer pots[] = {
  { mux1.pin(0), {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1} },
  { mux1.pin(1), {MIDI_CC::General_Purpose_Controller_1, CHANNEL_2} },
  { mux1.pin(2), {MIDI_CC::General_Purpose_Controller_1, CHANNEL_3} },
  { mux1.pin(3), {MIDI_CC::General_Purpose_Controller_1, CHANNEL_4} },
  };
  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 5, NEO_GRB + NEO_KHZ800);
uint32_t pot1Val;
uint32_t pot2Val;
uint32_t pot3Val;
uint32_t pot4Val;
uint32_t curr_potVal;

void setup() {
  Wire.begin();
  Wire.beginTransmission(DISPLAY_ADDRESS1);
  Wire.write('v');
  Wire.endTransmission();
  
  strip.begin();
  strip.setBrightness(30); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(255, 0, 0), 50);
  colorWipe(strip.Color(255, 100, 0), 50);
  colorWipe(strip.Color(255, 255, 0), 50);
  colorWipe(strip.Color(0, 255, 0), 50);
  colorWipe(strip.Color(0, 255, 255), 50);
  colorWipe(strip.Color(0, 0, 255), 50);
  colorWipe(strip.Color(255, 0, 255), 50);
  strip.clear();
  Control_Surface.begin(); // Initialize Control Surface
  pot1Val = pots[0].getValue();
  pot2Val = pots[1].getValue();
  pot3Val = pots[2].getValue();
  pot4Val = pots[3].getValue();
}
 
void loop() {
  Control_Surface.loop(); // Update the Control Surface
  //Serial.print(potVal);
  Serial.print("\n");
  progWheel(pots[0].getValue());

  //FIGURE OUT WHICH KNOB IS CURRENTLY BEING TURNED, DISPLAY ONLY THAT NEW MIDI VALUE
  uint32_t newval_1 = pots[0].getValue();
  if(newval_1 != pot1Val){
    pot1Val = newval_1;
    curr_potVal = newval_1; 
  }
  uint32_t newval_2 = pots[1].getValue();
  if(newval_2 != pot2Val){
    pot2Val = newval_2;
    curr_potVal = newval_2; 
  }
  uint32_t newval_3 = pots[2].getValue();
  if(newval_3 != pot3Val){
    pot3Val = newval_3;
    curr_potVal = newval_3; 
  }
  uint32_t newval_4 = pots[3].getValue();
  if(newval_4 != pot4Val){
    pot4Val = newval_4;
    curr_potVal = newval_4; 
  }
  i2cSendValue(curr_potVal); //Send the four characters to the display
  
}
void i2cSendValue(int tempCycles)
{
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
  Wire.write(tempCycles / 1000); //Send the left most digit
  tempCycles %= 1000; //Now remove the left most digit from the number we want to display
  Wire.write(tempCycles / 100);
  tempCycles %= 100;
  Wire.write(tempCycles / 10);
  tempCycles %= 10;
  Wire.write(tempCycles); //Send the right most digit
  Wire.endTransmission(); //Stop I2C transmission
}

float midiToLedNum(uint32_t val){
  return ((val/127.0)*12.0);
}
//12 LEDS
uint16_t getR(uint32_t led){
  if(led < 8){
    return(255);
  }
  else{
    return(0);
  }
}
uint16_t getG(uint32_t led){
  if(led >= 4){
    return(255);
  } else {
    return(0);
  }
}
uint16_t getB(uint32_t led){
  if(led >= 8){
    return(30);
  } else {
    return(0);
  }
}

void progWheel(uint32_t c){
  uint32_t normValue = uint32_t(midiToLedNum(c));
  Serial.print(normValue);
  strip.clear();
  for(uint16_t i=0; i<normValue; i++) {
    strip.setPixelColor(i,strip.Color(getR(i),getG(i),getB(i)));
  }
  strip.show();
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
 /**
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
**/
