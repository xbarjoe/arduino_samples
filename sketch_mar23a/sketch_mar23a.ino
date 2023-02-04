int red_guess = 0;
int blue_guess = 0;
int red_score = 0;
int blue_score = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}
void flash(int p){
  digitalWrite(p, HIGH);
  delay(500);
  digitalWrite(p, LOW);
  delay(500);
  digitalWrite(p, HIGH);
  delay(500);
  digitalWrite(p, LOW);
  delay(500);
  digitalWrite(p, HIGH);
  delay(500);
  digitalWrite(p, LOW);
  delay(500);
}
void tie(){
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(500);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(500);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(500);
}
void loop() {
  int num = random(0, 1024);
  flash(5);
  red_guess = analogRead(A1);
  blue_guess = analogRead(A0);
  red_score = abs(red_guess - num);
  blue_score = abs(blue_guess - num);
  if(blue_score > red_score){
    flash(4);
  } 
  else if(blue_score < red_score){
    flash(3);
  }
  else{
    tie();
  }
  
}
