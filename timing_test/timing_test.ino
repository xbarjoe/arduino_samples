/**
 * 
 *                   14
 *               6,--"^"--.8     
 *             ,'\         /`.   
 *           ,'   \15____5/   `. 
 *          |2     /       \     |16
 *          |    /         \    |
 *          |  4/           \7  |
 *          3'' `-.       ,-' ``/10
 *           \     `-.18-'     / 
 *            \       |       /  
 *             9-.._  |  _,,19   
 *                  ``"''        
 * 
 * 
 * 
 * 
 */
int pinList[] = {2,3,4,5,6,7,8,9,10,16,14,15,18,19};
int oldIdx = -1;

void startUp(){
  for(int i = 0; i < 14; i++){
    digitalWrite(pinList[i],HIGH);
  }
  
  delay(500);
  
  for(int j = 0; j < 14; j++){
    digitalWrite(pinList[j],LOW);
  }
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  
  startUp();



}


//Returns a """random""" pin for strobing purposes.
//Keeps track of the last pin it activates and deliberatly refrains from choosing that pin twice in a row.
//Makes the pin selection feel more random than a simple rand%14 call; but is, ironically enough, statistically less random...
//
//probability moment 
int getRandomIdx(){
  int idx = rand() % 14;
  if(idx == oldIdx){
    return getRandomIdx();
  } else {
    oldIdx = idx;
    return idx;
  }
}

void ring_strobe(int bpm, double division, double len){
  if(len > 1 || len < 0){
    Serial.print("ERROR: INVALID STROBE LENGTH");
    return;
  }
  double wholeBpm = bpm / 4.0;
  double baseMs = 60000.0 / wholeBpm;
  double stepLength = (baseMs / division) * len;
  double smalldelay = stepLength - (int)stepLength;
  double restDelay = (baseMs / division) * (1 - len);
  double smallrest = restDelay - (int)restDelay;

  while(true){
    int idx = rand() % 3;
    if(idx == 0){
      digitalWrite(15,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(18,HIGH);
      digitalWrite(4,HIGH);
    }
    if(idx == 1){
        digitalWrite(6,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(3,HIGH);
      } 
      if(idx == 2){
        digitalWrite(14,HIGH);
        digitalWrite(16,HIGH);
        digitalWrite(19,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(2,HIGH);
      }
      delay((int)stepLength);
      delayMicroseconds(smalldelay*1000);
      for(int i = 0; i<14; i++){
        digitalWrite(pinList[i],LOW);
      }
      delay((int)restDelay);
      delayMicroseconds(smallrest*1000);
    }
  }

//Randomly activates LEDs according to a given BPM, Note Length, & note duration (Accurate down to the microsecond!).
//Due to potential sync issues, this does go out of sync for after a certain length of time.
//Rough calculations estimate after 4 minutes, the effect is out of sync by about 6 milliseconds.
//Not too shabby if I do say so myself.
//BPM: Integer       | Beats per minute of random strobe
//DIVISION: Double   | Note length (8 = 8th note, 4 = 4th note, etc) 
//LEN: Double        | Percentage of note length where led is HIGH (Reccomended to be below .5 for strobe effects)
void random_strobe(int bpm, double division, double len){
  if(len > 1 || len < 0){
    Serial.print("ERROR: INVALID STROBE LENGTH");
    return;
  }
  double wholeBpm = bpm / 4.0;
  double baseMs = 60000.0 / wholeBpm;
  double stepLength = (baseMs / division) * len;
  double smalldelay = stepLength - (int)stepLength;
  double restDelay = (baseMs / division) * (1 - len);
  double smallrest = restDelay - (int)restDelay;
  
  while(true){
    int idx = getRandomIdx();
    int pin_i = pinList[idx];
    digitalWrite(pin_i, HIGH);
    Serial.print("SHOWING PIN: ");
    Serial.println(pin_i);
    delay((int)stepLength);
    delayMicroseconds(smalldelay*1000);
    digitalWrite(pin_i, LOW);
    delay((int)restDelay);
    delayMicroseconds(smallrest*1000);
  }
  
}

//Virtually identical to random_strobe, but uses 2 LEDs rather than one.

//TODO: REFACTOR TO replace 'random_strobe()' and 'random_twostrobe()' with a single function 'random_nstrobe()'
//Randomly activates 2 LEDs according to a given BPM, Note Length, & note duration (Accurate down to the microsecond!).
//Due to potential sync issues, this does go out of sync for after a certain length of time.
//Rough calculations estimate after 4 minutes, the effect is out of sync by about 6 milliseconds.
//Not too shabby if I do say so myself.
//BPM: Integer       | Beats per minute of random strobe
//DIVISION: Double   | Note length (8 = 8th note, 4 = 4th note, etc) 
//LEN: Double        | Percentage of note length where led is HIGH (Reccomended to be below .5 for strobe effects)
void random_Twostrobe(int bpm, double division, double len){
  if(len > 1 || len < 0){
    Serial.print("ERROR: INVALID STROBE LENGTH");
    return;
  }
  double wholeBpm = bpm / 4.0;
  double baseMs = 60000.0 / wholeBpm;
  double stepLength = (baseMs / division) * len;
  double smalldelay = stepLength - (int)stepLength;
  double restDelay = (baseMs / division) * (1 - len);
  double smallrest = restDelay - (int)restDelay;
  
  while(true){
    int idx1 = getRandomIdx();
    int idx2 = getRandomIdx();
    int pin_i1 = pinList[idx1];
    int pin_i2 = pinList[idx2];
    digitalWrite(pin_i1, HIGH);
    digitalWrite(pin_i2, HIGH);
    Serial.print("SHOWING PIN: ");
    //Serial.println(pin_i);
    delay((int)stepLength);
    delayMicroseconds(smalldelay*1000);
    digitalWrite(pin_i1, LOW);
    digitalWrite(pin_i2, LOW);
    delay((int)restDelay);
    delayMicroseconds(smallrest*1000);
  }
  
}

void loop() {
 random_Twostrobe(175,8,.5);
}
