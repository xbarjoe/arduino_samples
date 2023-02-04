#include <Encoder.h>
#include <Adafruit_NeoPixel.h>
#include<Control_Surface.h>
#include<Wire.h>

#define DISPLAY_ADDRESS1 0x71

using namespace MIDI_Notes;

USBMIDI_Interface midi;

char greeting[14] = {' ',' ',' ',' ', 'S', 'E', 'R', 'A', 'p', 'H',' ',' ',' ',' '};

bool AutoTuneEnabled;
uint32_t ATR;
uint32_t ATG;
uint32_t ATB;

char atKey[4];
char prevKey[2]={' ','C'};
char currKey[2]={' ','C'};

CCAbsoluteEncoder enc = {
  {14, 16}, //pins of encoder
  {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1}, // midi cc adress
  1,     //multiplier
  1,     //4pulses per step
};

CCButtonLatched enc_button = {
  10,
  {MIDI_CC::General_Purpose_Controller_1, CHANNEL_2},
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 9, NEO_GRB + NEO_KHZ800);

void setAtColors(uint32_t post){
  //Cm
  if(post >= 0 && post < 8){
    ATR = 255;
    ATG = 70;
    ATB = 0;
    currKey[0] = ' ';
    currKey[1] = 'C';
  }
  //Dbm
  else if(post >= 8 && post < 20){
    ATR = 0;
    ATG = 255;
    ATB = 50;
    currKey[0]= 'd';
    currKey[1] = 'b';
  }
  //Dm
  else if(post >= 20 && post < 32){
    ATR = 255;
    ATG = 0;
    ATB = 10;
    currKey[0] = ' ';
    currKey[1] = 'D';
    
  }
  //Ebm
  else if(post >= 32 && post < 44){
    ATR = 100;
    ATG = 255;
    ATB = 0;
    currKey[0] = 'E';
    currKey[1] = 'b';
  }
  //Em
  else if(post >= 44 && post < 52){
    ATR = 150;
    ATG = 0;
    ATB = 255;
    currKey[0] = ' ';
    currKey[1] = 'E';
  }
  //Fm
  else if(post >= 52 && post < 64){
    ATR = 255;
    ATG = 235;
    ATB = 0;
    currKey[0] = ' ';
    currKey[1] = 'F';
  }
  //Gbm
  else if(post >= 64 && post < 76){
    ATR = 0;
    ATG = 140;
    ATB = 255;
    currKey[0] = 'g';
    currKey[1] = 'b';
  }
  //Gm
  else if(post >= 76 && post < 88){
    ATR = 255;
    ATG = 35;
    ATB = 0;
    currKey[0] = ' ';
    currKey[1] = 'g';
  }
  //Abm
  else if(post >= 88 && post < 99){
    ATR = 61;
    ATG = 255;
    ATB = 30;
    currKey[0] = 'A';
    currKey[1] = 'b';
  }
  //Am
  else if(post >= 99 && post < 110){
    ATR = 255;
    ATG = 0;
    ATB = 130;
    currKey[0] = ' ';
    currKey[1] = 'A';
  }
  //Bbm
  else if(post >= 110 && post < 121){
    ATR = 125;
    ATG = 255;
    ATB = 10;
    currKey[0] = 'b';
    currKey[1] = 'b';
  }
  //Bm
  else{
    ATR = 30;
    ATG = 0;
    ATB = 255;
    currKey[0] = ' ';
    currKey[1] = 'b';
  }
}

bool arrayEquals(char a[], char b[]){
  if(sizeof(a) != sizeof(b)){
    return false;
  } else {
    for(uint8_t i=0;i<sizeof(a); i++){
      if(a[i] != b[i]){
        return false;
      }
    }
    return true;
  }
}

void updateATlight(uint32_t key_position){
  //uint32_t key = setKey(key_position);
  if(!AutoTuneEnabled){
    for(uint16_t i=0; i<12; i++) {
      strip.setPixelColor(i,strip.Color(0,0,0));
    }
    strip.show(); 
  }
  else {
    setAtColors(key_position);
    if(!arrayEquals(prevKey,currKey)){
      prevKey[0] = currKey[0];
      prevKey[1] = currKey[1];
      Wire.beginTransmission(DISPLAY_ADDRESS1);
      Wire.write(' ');
      Wire.write(' ');
      Wire.write(currKey[0]);
      Wire.write(currKey[1]);
      Wire.endTransmission();
    }
    for(uint16_t i=0; i<12; i++) {
      strip.setPixelColor(i,strip.Color(ATR,ATG,ATB));
    }
    strip.show(); 
  }
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

void printMsg(){
  uint32_t i=0;
  for(i; i<=10; i++){
    Wire.beginTransmission(DISPLAY_ADDRESS1);
    Wire.write(greeting[i]);
    Wire.write(greeting[i+1]);
    Wire.write(greeting[i+2]);
    Wire.write(greeting[i+3]);
    Wire.endTransmission();
    delay(200);
  }
}

void startupLights(){
  for(uint32_t i=0; i<12; i++){
    strip.setPixelColor(i,strip.Color(255,0,0));
    strip.show();
    delay(50);
  }
  for(uint32_t i=0; i<12; i++){
    strip.setPixelColor(i,strip.Color(0,0,0));
    strip.show();
    delay(50);
  }
  strip.clear();
}

void setup() {
  Wire.begin();
  Wire.beginTransmission(DISPLAY_ADDRESS1);
  Wire.write('v');
  Wire.endTransmission();
  strip.begin();
  strip.setBrightness(30); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
  startupLights();
  printMsg();
  Control_Surface.begin();
  

}

void loop() {
  AutoTuneEnabled = bool(enc_button.getState());
  updateATlight(enc.getValue());
  Serial.print(enc.getValue());
  
  Control_Surface.loop();
}
